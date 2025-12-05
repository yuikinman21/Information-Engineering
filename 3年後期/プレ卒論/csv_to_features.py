import padas as pd
import numpy as np
import os
import time
import warnings

warnings.filterwarnings("ignore")

INPUT_RAW_DIR = r"/home/ken/Documents/プレ卒論/CSV_Tshark"
OUTPUT_FLOW_DIR = r"/home/ken/Documents/プレ卒論/CSV_Flow"

def hex_to_int(x):
    try:
        return int(str(x), 16) if pd.notnull(x) and x != '' else 0
    except:
        return 0

def process_raw_csv(file_path):
    try:
        df = pd.read_csv(file_path)
    except Exception as e:
        print(f"❌ 読み込み失敗: {e}")
        return None

    if df.empty:
        return None

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
    df = df.rename(columns={k: v for k, v in rename_map.items() if k in df.columns})

    # TCPとUDPのポートを 'sport', 'dport' に統合
    if 'tcp_sport' in df.columns and 'udp_sport' in df.columns:
        df['sport'] = df['tcp_sport'].fillna(0).astype(int) + df['udp_sport'].fillna(0)
        df['dport'] = df['tcp_dport'].fillna(0).astype(int) + df['udp_dport'].fillna(0)
    
    else:
        df['src_port'] = df.get('tcp_sport', pd.Series(0)).fillna(0).astype(int) + df.get('udp_sport', pd.Series(0)).fillna(0)
        df['dst_port'] = df.get('tcp_dport', pd.Series(0)).fillna(0).astype(int) + df.get('udp_dport', pd.Series(0)).fillna(0)
        
    df['src_port'] = df['src_port'].astype(int)
    df['dst_port'] = df['dst_port'].astype(int)

    if 'tcp_flags' in df.columns:
        df['tcp_flags'] = df['tcp_flags'].apply(hex_to_int)
    else:
        df['tcp_flags'] = 0

