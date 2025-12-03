import os
import subprocess
import time

# ==========================================
# 設定
# ==========================================

INPUT_DIR = r"D:\PCAP"  # PCAPが入っているフォルダ
OUTPUT_DIR = r"D:\CSV_RAM_Tshark"  # 変換後のCSVを保存するフォルダ


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
    # エラーログの保存先 (CSVと同じ場所に .log を作る)
    log_file = output_file + ".log"
    
    cmd = [
        "tshark",
        "-r", input_file,
        "-T", "fields",
        "-E", "separator=,",
        "-E", "header=y",
        "-E", "quote=d",
        "-E", "occurrence=f",
        "-o", "tcp.desegment_tcp_streams:FALSE",
    ] + FIELDS

    try:
        print(f"🚀 変換開始: {input_file}")
        
        # ★修正ポイント: stdoutもstderrもファイルに直接つなぐ
        with open(output_file, "w") as out_f, open(log_file, "w") as log_f:
            
            # Pythonはパイプを使わず、OSにファイル書き込みを任せる (メモリ消費ゼロ)
            proc = subprocess.Popen(cmd, stdout=out_f, stderr=log_f, text=True)
            
            # 終了を待つ
            proc.wait()

        # --- 終了後のチェック ---
        
        # ログファイルの中身を少し読んで、エラー判定する
        if os.path.exists(log_file) and os.path.getsize(log_file) > 0:
            with open(log_file, "r") as f:
                log_content = f.read()
                
                # "cut short" (パケット途切れ) は許容する
                if "cut short" in log_content:
                    print(f"⚠️ [部分的成功] パケット途切れがありましたが処理されました。")
                elif proc.returncode != 0:
                    print(f"❌ [エラー] Tsharkが異常終了しました (Code: {proc.returncode})")
                    print(f"   詳細はログを確認: {log_file}")
        
        # 成功チェック (CSVができているか)
        if os.path.exists(output_file) and os.path.getsize(output_file) > 100:
            # 成功したらログファイルは邪魔なら消す（残しておいてもOK）
            # os.remove(log_file) 
            pass
        else:
            print("❌ CSVが生成されませんでした。")

    except Exception as e:
        print(f"❌ Python予期せぬエラー: {e}")

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