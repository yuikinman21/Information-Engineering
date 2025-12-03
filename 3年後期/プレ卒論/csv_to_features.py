import pandas as pd
import numpy as np
import os
import time
import warnings

# 警告を非表示
warnings.filterwarnings("ignore")

# ==========================================
# 1. 設定
# ==========================================
INPUT_RAW_DIR = r"D:\CSV_Tshark"    # Tsharkで作ったCSV (入力)
OUTPUT_FLOW_DIR = r"D:\CSV_Flow" # 特徴量CSVの保存先 (出力)

# ------------------------------------------
# ヘルパー関数: 16進数文字列をintに変換
# ------------------------------------------
def hex_to_int(x):
    try:
        # "0x12" や "12" などを数値に変換。空文字や欠損は0にする
        return int(str(x), 16) if pd.notnull(x) and x != '' else 0
    except:
        return 0

# ------------------------------------------
# メイン: 単一ファイルの変換処理
# ------------------------------------------
def process_raw_csv(file_path):
    # 1. 高速読み込み (データ型を指定してメモリ節約)
    # Tsharkのヘッダ名: frame.time_epoch, ip.src, ip.dst, tcp.srcport, ...
    try:
        df = pd.read_csv(file_path)
    except Exception as e:
        print(f"❌ 読み込み失敗: {e}")
        return None

    if df.empty:
        return None

    # 2. カラム名の正規化
    # ※ Tsharkのコマンドで指定した順序と一致している必要があります
    rename_map = {
        'frame.time_epoch': 'timestamp',
        'ip.src': 'src_ip',
        'ip.dst': 'dst_ip',
        'tcp.srcport': 'tcp_sport',
        'tcp.dstport': 'tcp_dport',
        'udp.srcport': 'udp_sport',
        'udp.dstport': 'udp_dport',
        'ip.proto': 'proto',
        'frame.len': 'pkt_len',
        'tcp.flags': 'tcp_flags'
    }
    # 存在するカラムだけリネーム
    df = df.rename(columns={k: v for k, v in rename_map.items() if k in df.columns})

    # 3. データ前処理 (ポート統合とフラグ変換)
    
    # TCPとUDPのポートを 'sport', 'dport' に統合
    # (例: tcp_sportがNaNならudp_sportの値を使う。両方NaNなら0)
    if 'tcp_sport' in df.columns and 'udp_sport' in df.columns:
        df['src_port'] = df['tcp_sport'].fillna(0) + df['udp_sport'].fillna(0)
        df['dst_port'] = df['tcp_dport'].fillna(0) + df['udp_dport'].fillna(0)
    else:
        # TCPのみ/UDPのみの場合のフォールバック
        df['src_port'] = df.get('tcp_sport', df.get('udp_sport', 0)).fillna(0)
        df['dst_port'] = df.get('tcp_dport', df.get('udp_dport', 0)).fillna(0)

    # ポートを整数型へ
    df['src_port'] = df['src_port'].astype(int)
    df['dst_port'] = df['dst_port'].astype(int)

    # TCPフラグを数値化 (文字列 "0x012" -> 数値 18)
    if 'tcp_flags' in df.columns:
        df['flags_int'] = df['tcp_flags'].apply(hex_to_int)
    else:
        df['flags_int'] = 0

    # 4. 双方向フローIDの生成
    # "小さいIP:Port" と "大きいIP:Port" を常に同じ順序に並べることで、
    # 送信(A->B)と返信(B->A)を同じフローとして扱う
    
    # ベクトル化のために一度numpy配列化
    src_ips = df['src_ip'].astype(str).values
    dst_ips = df['dst_ip'].astype(str).values
    src_ports = df['src_port'].values
    dst_ports = df['dst_port'].values
    protos = df['proto'].fillna(0).astype(int).values

    # 比較して入れ替え (Forward/Backwardの正規化)
    # 文字列比較で src > dst の場合は入れ替えるロジック
    # (完全な実装は複雑になるため、ここでは簡易的に「文字列結合したID」でグループ化)
    
    # Pythonのapplyを使うと遅いので、単純な文字列結合でフローキーを作る
    # A->B も B->A も同じキーにするため、ソート済みのペアを作る
    def get_flow_key(row):
        s_ip, d_ip = row['src_ip'], row['dst_ip']
        s_p, d_p = row['src_port'], row['dst_port']
        
        # IPとポートのペアを作る
        p1 = f"{s_ip}:{s_p}"
        p2 = f"{d_ip}:{d_p}"
        
        # 辞書順でソートして結合
        if p1 > p2:
            return f"{p2}-{p1}-{row['proto']}"
        else:
            return f"{p1}-{p2}-{row['proto']}"

    # ここだけはapplyを使う（数百万行あると数秒かかるが許容範囲）
    df['flow_id'] = df.apply(get_flow_key, axis=1)

    # 5. 特徴量計算のための準備
    
    # 時系列順にソート (IAT計算のため必須)
    df = df.sort_values(['flow_id', 'timestamp'])
    
    # IAT (到着間隔) の計算: フローごとにタイムスタンプの差分をとる
    df['iat'] = df.groupby('flow_id')['timestamp'].diff().fillna(0)
    
    # フラグのBool列を事前作成 (集計高速化のため)
    # SYN=0x02, RST=0x04, FIN=0x01
    df['is_syn'] = (df['flags_int'] & 0x02) != 0
    df['is_rst'] = (df['flags_int'] & 0x04) != 0
    df['is_fin'] = (df['flags_int'] & 0x01) != 0

    # 6. グループ化して一気に集計 (Aggregation)
    # ここがScapy版より圧倒的に速い理由です
    flow_stats = df.groupby('flow_id').agg(
        # 基本情報 (最初のパケットの情報を使う)
        src_ip=('src_ip', 'first'),
        dst_ip=('dst_ip', 'first'),
        src_port=('src_port', 'first'),
        dst_port=('dst_port', 'first'),
        protocol=('proto', 'first'),
        
        # 時間関連
        start_time=('timestamp', 'min'),
        end_time=('timestamp', 'max'),
        
        # パケット数・サイズ
        total_packets=('timestamp', 'count'),
        total_bytes=('pkt_len', 'sum'),
        
        # サイズ統計
        pkt_len_mean=('pkt_len', 'mean'),
        pkt_len_std=('pkt_len', 'std'),
        pkt_len_max=('pkt_len', 'max'),
        pkt_len_min=('pkt_len', 'min'),
        
        # IAT統計 (IAT列を集計)
        iat_mean=('iat', 'mean'),
        iat_std=('iat', 'std'),
        iat_max=('iat', 'max'),
        iat_min=('iat', 'min'),
        
        # フラグカウント (Trueの数を合計)
        syn_count=('is_syn', 'sum'),
        rst_count=('is_rst', 'sum'),
        fin_count=('is_fin', 'sum')
    ).reset_index()

    # Flow Duration (終了時刻 - 開始時刻)
    flow_stats['flow_duration'] = flow_stats['end_time'] - flow_stats['start_time']
    
    # 不要な列を削除 (start/end timeなど)
    flow_stats.drop(columns=['start_time', 'end_time'], inplace=True)
    
    # NaN (標準偏差など計算不能な場合) を0埋め
    flow_stats = flow_stats.fillna(0)

    return flow_stats

# ==========================================
# 実行処理
# ==========================================
if __name__ == "__main__":
    if not os.path.exists(OUTPUT_FLOW_DIR):
        os.makedirs(OUTPUT_FLOW_DIR)

    files = [f for f in os.listdir(INPUT_RAW_DIR) if f.endswith(".csv")]
    total_files = len(files)
    
    print(f"📂 処理対象: {total_files} ファイル")
    
    start_total = time.time()

    for i, filename in enumerate(files, 1):
        input_path = os.path.join(INPUT_RAW_DIR, filename)
        output_path = os.path.join(OUTPUT_FLOW_DIR, f"flow_{filename}")
        
        print(f"[{i}/{total_files}] 🔄 変換中: {filename} ... ", end="")
        file_start = time.time()
        
        try:
            # 処理実行
            df_flow = process_raw_csv(input_path)
            
            if df_flow is not None and not df_flow.empty:
                # CSV保存
                df_flow.to_csv(output_path, index=False)
                elapsed = time.time() - file_start
                print(f"✅ 完了 ({len(df_flow)} flows, {elapsed:.2f}s)")
            else:
                print("⚠️ データなし/スキップ")
                
        except Exception as e:
            print(f"\n❌ エラー: {e}")

    print("="*40)
    print(f"🎉 全処理完了。合計時間: {time.time() - start_total:.2f}秒")