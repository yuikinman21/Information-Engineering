import pandas as pd
import numpy as np
import os
import gc
from scapy.all import PcapReader, IP, TCP, UDP 
import warnings

warnings.filterwarnings("ignore")

INPUT_DIR = r"/home/ken/Documents/プレ卒論/PCAP"
OUTPUT_DIR = r"/home/ken/Documents/プレ卒論/CSV"
def extract_features(pcap_path):
    print(f"🔄 ストリーミング解析開始: {pcap_path}")
    
    flows = {}
    packet_count = 0


    try:
        with PcapReader(pcap_path) as pcap_reader:
            for pkt in pcap_reader:
                packet_count += 1
                
                # 進捗表示 (例: 10,000パケットごと)
                if packet_count % 10000 == 0:
                    print(f"\r   Processing packet: {packet_count}", end="")

                if IP not in pkt:
                    continue

                src_ip = pkt[IP].src
                dst_ip = pkt[IP].dst
                proto = pkt[IP].proto
                
                sport = 0
                dport = 0
                
                # プロトコル判定
                if TCP in pkt:
                    sport = pkt[TCP].sport
                    dport = pkt[TCP].dport
                elif UDP in pkt:
                    sport = pkt[UDP].sport
                    dport = pkt[UDP].dport
                
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
                
                # データ追加
                flows[key]['timestamps'].append(float(pkt.time))
                flows[key]['lengths'].append(len(pkt))
                
                if TCP in pkt:
                    flows[key]['flags'].append(pkt[TCP].flags)

    except Exception as e:
        print(f"\n❌ エラー発生: {e}")
        return None

    print(f"\n✅ 読み込み完了。パケット数: {packet_count}")
    print("📊 特徴量計算を実行中...")

    # --- 特徴量の計算 (ここは変更なし) ---
    dataset = []
    
    # フロー数が多い場合の対策として、処理済みの辞書を逐次処理するのが理想ですが
    # ここでは構造を維持します
    for key, flow in flows.items():
        timestamps = np.array(flow['timestamps'])
        lengths = np.array(flow['lengths'])
        
        duration = timestamps.max() - timestamps.min()
        
        if len(timestamps) > 1:
            iat = np.diff(timestamps)
            iat_mean = np.mean(iat)
            iat_std = np.std(iat)
            iat_max = np.max(iat)
            iat_min = np.min(iat)
        else:
            iat_mean = 0; iat_std = 0; iat_max = 0; iat_min = 0
            
        syn_count = 0; rst_count = 0; fin_count = 0
        for f in flow['flags']:
            s_flag = str(f)
            if 'S' in s_flag: syn_count += 1
            if 'R' in s_flag: rst_count += 1
            if 'F' in s_flag: fin_count += 1

        feature = {
            'src_ip': flow['src_ip'], 'dst_ip': flow['dst_ip'],
            'src_port': flow['src_port'], 'dst_port': flow['dst_port'],
            'protocol': flow['protocol'], 'flow_duration': duration,
            'total_packets': len(lengths), 'total_bytes': np.sum(lengths),
            'pkt_len_mean': np.mean(lengths), 'pkt_len_std': np.std(lengths),
            'pkt_len_max': np.max(lengths), 'pkt_len_min': np.min(lengths),
            'iat_mean': iat_mean, 'iat_std': iat_std,
            'iat_max': iat_max, 'iat_min': iat_min,
            'syn_count': syn_count, 'rst_count': rst_count, 'fin_count': fin_count
        }
        dataset.append(feature)
    
    # メモリ解放のおまじない
    del flows
    gc.collect()

    return pd.DataFrame(dataset)

# メイン処理は変更なし
if __name__ == "__main__":
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)
        
    for filename in os.listdir(INPUT_DIR):
        if filename.endswith(('.pcap', '.cap', '.pcapng')):
            pcap_file_path = os.path.join(INPUT_DIR, filename)
            base_name = os.path.splitext(filename)[0]
            output_csv_path = os.path.join(OUTPUT_DIR, f"{base_name}_features.csv")
            
            print("="*40)
            df = extract_features(pcap_file_path) # 修正版関数を呼び出し
            
            if df is not None and not df.empty:
                df.to_csv(output_csv_path, index=False)
                print(f"💾 保存完了: {output_csv_path}")
            else:
                print(f"⚠️ データなし: {filename}")
            
            # ループごとにメモリを強制開放
            gc.collect()