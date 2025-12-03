import pandas as pd
import numpy as np
from scapy.all import rdpcap, IP, TCP, UDP
import warnings

# 警告を非表示
warnings.filterwarnings("ignore")

# ==========================================
# 1. 設定：ここにファイルパスを入力してください
# ==========================================
INPUT_PCAP = r"C:\Users\yuiki\OneDrive - 公立大学法人大阪\3年後期\情報工学実験2\プレ卒論\Aposemat IoT-23(一部)\CTU-Honeypot-Capture-4-1\2018-09-14-13-40-25-Philips-Hue-Bridge.pcap"
OUTPUT_CSV = r"C:\Users\yuiki\OneDrive - 公立大学法人大阪\3年後期\情報工学実験2\プレ卒論\output.csv"
# ==========================================

def extract_features(pcap_path):
    print(f"🔄 読み込み中... (時間がかかる場合があります): {pcap_path}")
    
    try:
        # パケットを一括読み込み
        packets = rdpcap(pcap_path)
    except Exception as e:
        print(f"❌ 読み込みエラー: {e}")
        return None

    print(f"✅ 読み込み完了。パケット数: {len(packets)}")
    print("📊 フロー解析を実行中...")

    flows = {}

    for pkt in packets:
        # IP層を持つパケットのみ対象
        if IP not in pkt:
            continue

        src_ip = pkt[IP].src
        dst_ip = pkt[IP].dst
        proto = pkt[IP].proto
        
        # ポート番号の取得
        sport = 0
        dport = 0
        if TCP in pkt:
            sport = pkt[TCP].sport
            dport = pkt[TCP].dport
        elif UDP in pkt:
            sport = pkt[UDP].sport
            dport = pkt[UDP].dport
        
        # フローを特定するキー (双方向を同一フローとみなすためのソート)
        # A->B と B->A を同じフローとして扱う
        key = tuple(sorted([(src_ip, sport), (dst_ip, dport)]) + [proto])
        
        if key not in flows:
            flows[key] = {
                'src_ip': src_ip,
                'dst_ip': dst_ip,
                'src_port': sport,
                'dst_port': dport,
                'protocol': proto,
                'timestamps': [],
                'lengths': [],
                'flags': []
            }
        
        # データの追加
        flows[key]['timestamps'].append(float(pkt.time))
        flows[key]['lengths'].append(len(pkt))
        
        # TCPフラグの収集
        if TCP in pkt:
            flows[key]['flags'].append(pkt[TCP].flags)

    # --- 特徴量の計算 ---
    dataset = []
    
    for key, flow in flows.items():
        timestamps = np.array(flow['timestamps'])
        lengths = np.array(flow['lengths'])
        
        # 時間関連
        duration = timestamps.max() - timestamps.min()
        
        # IAT (Inter Arrival Time: パケット到着間隔)
        if len(timestamps) > 1:
            iat = np.diff(timestamps)
            iat_mean = np.mean(iat)
            iat_std = np.std(iat)
            iat_max = np.max(iat)
            iat_min = np.min(iat)
        else:
            iat_mean = 0
            iat_std = 0
            iat_max = 0
            iat_min = 0
            
        # TCPフラグカウント (SYN, RST, FIN)
        syn_count = 0
        rst_count = 0
        fin_count = 0
        for f in flow['flags']:
            # Scapyのフラグはオブジェクトなので文字列化してチェック
            s_flag = str(f)
            if 'S' in s_flag: syn_count += 1
            if 'R' in s_flag: rst_count += 1
            if 'F' in s_flag: fin_count += 1

        feature = {
            'src_ip': flow['src_ip'],
            'dst_ip': flow['dst_ip'],
            'src_port': flow['src_port'],
            'dst_port': flow['dst_port'],
            'protocol': flow['protocol'],
            
            # 統計特徴量
            'flow_duration': duration,
            'total_packets': len(lengths),
            'total_bytes': np.sum(lengths),
            'pkt_len_mean': np.mean(lengths),
            'pkt_len_std': np.std(lengths),
            'pkt_len_max': np.max(lengths),
            'pkt_len_min': np.min(lengths),
            'iat_mean': iat_mean,
            'iat_std': iat_std,
            'iat_max': iat_max,
            'iat_min': iat_min,
            
            # セキュリティ分析で重要なフラグ
            'syn_count': syn_count,
            'rst_count': rst_count,
            'fin_count': fin_count
        }
        dataset.append(feature)

    return pd.DataFrame(dataset)

# ==========================================
# 実行処理
# ==========================================
if __name__ == "__main__":
    df = extract_features(INPUT_PCAP)
    
    if df is not None and not df.empty:
        print(f"💾 CSVに保存中: {OUTPUT_CSV}")
        df.to_csv(OUTPUT_CSV, index=False)
        print("🎉 完了しました！")
        print(df.head()) # 先頭を表示
    else:
        print("⚠️ データが空か、エラーが発生しました。")