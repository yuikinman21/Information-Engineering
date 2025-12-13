import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score

# ==========================================
# 1. 設定・ファイルリストの定義
# ==========================================
# ★ここを「動作確認用」に最小限のファイル数にしています★
# 実際のファイル名に合わせて書き換えてください

# --- 正常データ ---
# 学習用に1つ、テスト用に1つ
normal_files_train = [
    "D:\\CSV_Flow\\CSV_Normal\\flow_normal_2018-09-14-13-40-25-Philips-Hue-Bridge.csv"
]
normal_files_test = [
    "D:\\CSV_Flow\\CSV_Normal\\flow_normal_2018-09-21-capture.csv"
]

# --- 攻撃データ ---
# 学習用に1つ、テスト用に1つ
attack_files_train = [
    "D:\\CSV_Flow\\CSV_Attacked\\flow_attack_2018-10-02-13-12-30-192.168.100.103.csv"
]
attack_files_test = [
    "D:\\CSV_Flow\\CSV_Attacked\\flow_attack_2018-10-03-15-22-32-192.168.100.113.csv"
]

# 学習・評価に不要な列
DROP_COLUMNS = [
    'flow_id', 'src_ip', 'dst_ip', 'src_port', 'dst_port', 'timestamp', 'label'
]

# ==========================================
# 2. 関数定義
# ==========================================

def load_files(file_list, label_value):
    """ 指定されたファイルリストを読み込み、ラベルを付与して結合 """
    df_list = []
    for filename in file_list:
        try:
            df = pd.read_csv(filename)
            df['label'] = label_value
            df_list.append(df)
            print(f"  OK: {filename} を読み込みました (行数: {len(df)})") 
        except FileNotFoundError:
            print(f"  Error: ファイルが見つかりません -> {filename}")
        except Exception as e:
            print(f"  Error: {filename} の読み込みエラー -> {e}")

    if not df_list:
        return pd.DataFrame()
    
    return pd.concat(df_list, ignore_index=True)

def preprocess_data(df, is_training=True):
    """ データの前処理（シャッフル、欠損値処理、不要列削除） """
    if df.empty:
        return None, None

    # 1. シャッフル
    df = df.sample(frac=1, random_state=42).reset_index(drop=True)

    # 2. 特徴量とラベルの分離
    cols_to_drop = [c for c in DROP_COLUMNS if c in df.columns]
    X = df.drop(columns=cols_to_drop)
    y = df['label']

    # 3. 欠損値処理
    X = X.replace([np.inf, -np.inf], np.nan).fillna(0)

    return X, y

# ==========================================
# 3. メイン処理
# ==========================================

def main():
    print("=== [動作検証モード] 処理を開始します ===")

    # A. データの読み込み
    print("\n[Step 1] ファイル読み込み")
    train_normal = load_files(normal_files_train, 0)
    train_attack = load_files(attack_files_train, 1)
    test_normal = load_files(normal_files_test, 0)
    test_attack = load_files(attack_files_test, 1)

    # 結合
    train_full = pd.concat([train_normal, train_attack], ignore_index=True)
    test_full = pd.concat([test_normal, test_attack], ignore_index=True)

    print(f"\n  -> 訓練データ合計: {len(train_full)} 行")
    print(f"  -> テストデータ合計: {len(test_full)} 行")

    if len(train_full) == 0 or len(test_full) == 0:
        print("\n[停止] データが不足しています。ファイル名やパスを確認してください。")
        return

    # B. 前処理
    print("\n[Step 2] 前処理")
    X_train, y_train = preprocess_data(train_full, is_training=True)
    X_test, y_test = preprocess_data(test_full, is_training=False)

    # C. 学習
    print("\n[Step 3] 学習 (Random Forest)")
    # 動作確認用なので木の数(n_estimators)を減らして高速化してもOK（例: 100 -> 10）
    rf_model = RandomForestClassifier(n_estimators=100, random_state=42)
    rf_model.fit(X_train, y_train)
    print("  -> 完了")

    # D. 評価
    print("\n[Step 4] 評価結果")
    y_pred = rf_model.predict(X_test)

    print(f"正解率: {accuracy_score(y_test, y_pred):.4f}")
    print("\n--- 分類レポート ---")
    print(classification_report(y_test, y_pred, target_names=['Normal', 'Attack']))
    
    print("\n--- 混同行列 ---")
    print(confusion_matrix(y_test, y_pred))

    # E. 特徴量重要度
    print("\n[Step 5] 重要な特徴量 Top 5")
    importances = rf_model.feature_importances_
    indices = np.argsort(importances)[::-1]
    features = X_train.columns
    for i in range(min(5, len(features))):
        print(f"{i+1}. {features[indices[i]]}: {importances[indices[i]]:.4f}")

if __name__ == "__main__":
    main()