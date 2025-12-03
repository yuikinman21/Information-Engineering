import os
import subprocess
import time

# ==========================================
# 設定
# ==========================================

INPUT_DIR = r"/home/ken/Documents/プレ卒論/PCAP"
OUTPUT_DIR = r"/home/ken/Documents/プレ卒論/CSV_Tshark"

# 抽出したいフィールド (以前のPythonコードと同じ分析ができるように選定)

FIELDS = [
    "-e", "frame.time_epoch",  # タイムスタンプ
    "-e", "ip.src",            # 送信元IP
    "-e", "ip.dst",            # 送信先IP
    "-e", "tcp.srcport",       # TCP送信元ポート
    "-e", "tcp.dstport",       # TCP送信先ポート
    "-e", "udp.srcport",       # UDP送信元ポート
    "-e", "udp.dstport",       # UDP送信先ポート
    "-e", "ip.proto",          # プロトコル番号
    "-e", "frame.len",         # パケット長
    "-e", "tcp.flags"          # TCPフラグ (SYN/FIN/RST判定用)
]

def convert_pcap_to_csv(input_file, output_file):
    cmd = [
        "tshark",
        "-r", input_file,
        "-T", "fields",
        "-E", "separator=,",
        "-E", "header=y",
        "-E", "quote=d",
        "-E", "occurrence=f"
    ] + FIELDS

    try:

        result = subprocess.run(cmd, capture_output=True, text=True)
        
        # 実行結果がエラー(0以外)だった場合
        if result.returncode != 0:
            print(f"❌ Tsharkエラー (Exit Code {result.returncode}):")
            print(f"   📂 ファイル: {input_file}")
            print(f"   ⚠️ 詳細メッセージ:\n{result.stderr}") # ここに本当の原因が出る
        else:
            # 成功したらファイルに書き込む
            with open(output_file, "w") as f:
                f.write(result.stdout)
            
    except Exception as e:
        print(f"❌ 予期せぬエラー: {e}")

# ==========================================
# メイン処理
# ==========================================
if __name__ == "__main__":
    
    # 出力フォルダ作成
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    # 処理時間の計測開始
    start_total = time.time()
    
    files = [f for f in os.listdir(INPUT_DIR) if f.endswith(('.pcap', '.cap', '.pcapng'))]
    total_files = len(files)
    
    print(f"📂 対象ファイル数: {total_files}")
    print("="*40)

    for i, filename in enumerate(files, 1):
        pcap_path = os.path.join(INPUT_DIR, filename)
        
        # 出力ファイル名を作成 (例: data.pcap -> data.csv)
        base_name = os.path.splitext(filename)[0]
        csv_path = os.path.join(OUTPUT_DIR, f"{base_name}.csv")
        
        print(f"[{i}/{total_files}] 🚀 変換中: {filename} ...", end="")
        start_time = time.time()
        
        # 変換実行
        convert_pcap_to_csv(pcap_path, csv_path)
        
        elapsed = time.time() - start_time
        print(f" 完了 ({elapsed:.2f}秒)")

    print("="*40)
    print(f"🎉 全処理完了。合計時間: {time.time() - start_total:.2f}秒")