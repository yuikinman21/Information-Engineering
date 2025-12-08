import pandas as pd
import numpy as np
import os
import time
import warnings
import traceback  # 追加: エラー詳細を表示するために必須

# 警告を非表示
warnings.filterwarnings("ignore")

# ==========================================
# 1. 設定
# ==========================================
INPUT_RAW_DIR = r"D:\CSV_Tshark"    # Tsharkで作ったCSV (入力)
OUTPUT_FLOW_DIR = r"D:\CSV_Flow"    # 特徴量CSVの保存先 (出力)

# ------------------------------------------
# ヘルパー関数: 16進数文字列をintに変換
# ------------------------------------------
def hex_to_int(x):
    try:
        return int(str(x), 16) if pd.notnull(x) and x != '' else 0
    except:
        return 0

# ------------------------------------------
# メイン: 単一ファイルの変換処理
# ------------------------------------------
def process_raw_csv(file_path):
    print(f"   -> 読み込み開始: {os.path.basename(file_path)}")
    
    # 1. 読み込み
    try:
        df = pd.read_csv(file_path)
    except Exception as e:
        print(f"❌ CSV読み込み自体に失敗: {e}")
        return None

    if df.empty:
        print("⚠️ データが空です")
        return None

    # 2. カラム名の正規化
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

    # ★デバッグ用: 必須カラムのチェック
    required_cols = ['timestamp', 'src_ip', 'dst_ip', 'pkt_len']
    missing_cols = [c for c in required_cols if c not in df.columns]
    if missing_cols:
        raise ValueError(f"必須カラムが不足しています: {missing_cols} (現在のカラム: {list(df.columns)})")

    # 3. データ前処理
    # ポート統合
    if 'tcp_sport' in df.columns and 'udp_sport' in df.columns:
        df['src_port'] = df['tcp_sport'].fillna(0) + df['udp_sport'].fillna(0)
        df['dst_port'] = df['tcp_dport'].fillna(0) + df['udp_dport'].fillna(0)
    else:
        # どちらか片方、あるいは両方ない場合
        s_port = df['tcp_sport'] if 'tcp_sport' in df.columns else (df['udp_sport'] if 'udp_sport' in df.columns else 0)
        d_port = df['tcp_dport'] if 'tcp_dport' in df.columns else (df['udp_dport'] if 'udp_dport' in df.columns else 0)
        df['src_port'] = pd.Series(s_port).fillna(0)
        df['dst_port'] = pd.Series(d_port).fillna(0)

    df['src_port'] = df['src_port'].astype(int)
    df['dst_port'] = df['dst_port'].astype(int)

    # TCPフラグ
    if 'tcp_flags' in df.columns:
        df['flags_int'] = df['tcp_flags'].apply(hex_to_int)
    else:
        df['flags_int'] = 0

    # 4. フローID生成
    # Applyが遅い原因になりうるため、ここでのエラーも捕捉したい
    try:
        # ベクトル化準備
        # データ型を強制変換してエラーを防ぐ
        df['proto'] = df['proto'].fillna(0).astype(int)
        
        def get_flow_key(row):
            # 念のためstr変換を入れる
            s_ip = str(row['src_ip'])
            d_ip = str(row['dst_ip'])
            s_p = row['src_port']
            d_p = row['dst_port']
            
            p1 = f"{s_ip}:{s_p}"
            p2 = f"{d_ip}:{d_p}"
            
            if p1 > p2:
                return f"{p2}-{p1}-{row['proto']}"
            else:
                return f"{p1}-{p2}-{row['proto']}"

        df['flow_id'] = df.apply(get_flow_key, axis=1)
        
    except Exception as e:
        print("❌ フローID生成中にエラー")
        raise e

    # 5. 特徴量計算準備
    df = df.sort_values(['flow_id', 'timestamp'])
    df['iat'] = df.groupby('flow_id')['timestamp'].diff().fillna(0)
    
    df['is_syn'] = (df['flags_int'] & 0x02) != 0
    df['is_rst'] = (df['flags_int'] & 0x04) != 0
    df['is_fin'] = (df['flags_int'] & 0x01) != 0

    # 6. 集計 (Aggregation)
    try:
        flow_stats = df.groupby('flow_id').agg(
            src_ip=('src_ip', 'first'),
            dst_ip=('dst_ip', 'first'),
            src_port=('src_port', 'first'),
            dst_port=('dst_port', 'first'),
            protocol=('proto', 'first'),
            start_time=('timestamp', 'min'),
            end_time=('timestamp', 'max'),
            total_packets=('timestamp', 'count'),
            total_bytes=('pkt_len', 'sum'),
            pkt_len_mean=('pkt_len', 'mean'),
            pkt_len_std=('pkt_len', 'std'),
            pkt_len_max=('pkt_len', 'max'),
            pkt_len_min=('pkt_len', 'min'),
            iat_mean=('iat', 'mean'),
            iat_std=('iat', 'std'),
            iat_max=('iat', 'max'),
            iat_min=('iat', 'min'),
            syn_count=('is_syn', 'sum'),
            rst_count=('is_rst', 'sum'),
            fin_count=('is_fin', 'sum')
        ).reset_index()
    except Exception as e:
        print("❌ 集計(groupby)中にエラー")
        raise e

    flow_stats['flow_duration'] = flow_stats['end_time'] - flow_stats['start_time']
    flow_stats.drop(columns=['start_time', 'end_time'], inplace=True)
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
        
        print(f"[{i}/{total_files}] 🔄 変換開始: {filename}")
        file_start = time.time()
        
        try:
            # 処理実行
            df_flow = process_raw_csv(input_path)
            
            if df_flow is not None and not df_flow.empty:
                df_flow.to_csv(output_path, index=False)
                elapsed = time.time() - file_start
                print(f"   ✅ 完了 ({len(df_flow)} flows, {elapsed:.2f}s)")
            else:
                print("   ⚠️ データなし/スキップ")
                
        except Exception:
            # ★ ここが重要: エラーの詳細な内容(スタックトレース)を表示する
            print(f"\n❌ 【重大エラー】ファイル処理中に例外が発生しました: {filename}")
            print("-" * 60)
            traceback.print_exc()  # これで「何行目で何が起きたか」が分かります
            print("-" * 60)

    print("="*40)
    print(f"🎉 全処理完了。合計時間: {time.time() - start_total:.2f}秒")