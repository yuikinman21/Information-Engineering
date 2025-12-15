
# Information Engineering Archive

大阪公立大学 工学部 情報工学科における講義・演習・実験、および研究活動（プレ卒論）の成果物をまとめたアーカイブです。
プログラミングの基礎から、ネットワークトラフィック解析を行うスクリプトまで、学年ごとの学習過程を記録しています。

## 📂 ディレクトリ構成 (Directory Structure)

リポジトリは学年およびプロジェクトごとに階層化されています。

```text
.
├── 1年/                       # プログラミング入門 (C言語基礎)
│   ├── calculator.c           # 四則演算
│   ├── bmi.c                  # BMI計算
│   ├── matrix.c               # 行列演算
│   ├── numberguess.c          # 数当てゲーム
│   └── ... (その他 基礎演習コード)
│
├── 3年後期/
│   └── プレ卒論/               # ネットワークトラフィック解析ツール
│       ├── PCAP/              # (解析対象のPCAPファイル置き場)
│       ├── CSV_Tshark/        # Tsharkによる中間出力
│       ├── CSV_Flow/          # 特徴量抽出後のフローデータ
│       ├── Tshark.py          # PCAPパケット情報をCSVに変換するスクリプト
│       ├── csv_to_features.py # パケットデータからフロー統計量(IAT等)を算出するスクリプト
│       └── ...
│
├── TeX/                       # レポート・文書作成関連
│   └── test.tex
│
└── README.md
````

## 🚀 主要プロジェクト (Key Projects)

### 🛡️ プレ卒論: ネットワークトラフィック解析ツール(現在研究中)

Wireshark (Tshark) と Python (Pandas) を組み合わせ、PCAPファイルから機械学習用の特徴量を抽出するパイプラインを構築しました。

  * **Tshark.py**:
      * `tshark` コマンドをPythonから呼び出し、大量のPCAPファイルを高速にCSV形式（パケット単位）へ変換。
      * 抽出フィールド: タイムスタンプ, IP(src/dst), Port(src/dst), プロトコル, パケット長, TCPフラグ。
  * **csv\_to\_features.py**:
      * パケット列を「双方向フロー (Flow)」として再構築。
      * **特徴量抽出**: 到着間隔 (IAT) の統計量 (mean, std, max, min)、パケットサイズの統計量、TCPフラグ (SYN, FIN, RST) のカウントなど。
      * **高速化の工夫**: `pandas` のベクトル演算と `groupby` を活用し、ループ処理を極力排除して処理速度を向上。

### 💻 1年次演習: C言語アルゴリズム基礎

情報工学の基礎となるC言語によるアルゴリズム実装。

  * 入出力、条件分岐、ループ処理
  * 関数、ポインタ、構造体
  * 数値計算（行列、階乗、総和など）

## 🛠 使用技術 (Technology Stack)

  * **Languages**: C, Python 3, LaTeX
  * **Libraries (Python)**:
      * `pandas`, `numpy`: データ処理・統計計算
      * `subprocess`: 外部コマンド実行
  * **Tools**:
      * `Wireshark (Tshark)`: パケットキャプチャ解析
      * `GCC`: Cコンパイラ
      * `VS Code`: 開発環境

## 👤 Author

**YUIKI MAKINO**

  * Osaka Metropolitan University
  * Department of Information Engineering

-----

*Note: This repository is for educational and archival purposes.*

```
