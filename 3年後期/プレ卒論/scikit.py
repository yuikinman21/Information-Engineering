import pandas as pd
import numpy as np
import glob
import os
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score

# ==========================================
# 1. 設定・ファイルリストの定義 (自動取得版)
# ==========================================


NORMAL_DIR = r"D:\CSV_Flow\CSV_Normal\*.csv"
ATTACK_DIR = r"D:\CSV_Flow\CSV_Attacked\*.csv"

print("ファイルを検索中...")
all_normal_files = glob.glob(NORMAL_DIR)
all_attack_files = glob.glob(ATTACK_DIR)

print(f"  -> 正常ファイル: {len(all_normal_files)} 個見つかりました")
print(f"  -> 攻撃ファイル: {len(all_attack_files)} 個見つかりました")

# ★ここを追加: ファイル単位で学習用(70%)とテスト用(30%)にランダム分割
# これにより、特定の攻撃種類が片方に偏るのを防ぎつつ、未知のファイルでテストできます
train_normal_files, test_normal_files = train_test_split(all_normal_files, test_size=0.3, random_state=42)
train_attack_files, test_attack_files = train_test_split(all_attack_files, test_size=0.3, random_state=42)

# 学習・評価に不要な列のリスト
DROP_COLUMNS = [
    'flow_id', 'src_ip', 'dst_ip', 'src_port', 'dst_port', 'timestamp', 'label'
]


# 2. 関数定義


def load_files(file_list, label_value):
    """ 指定されたファイルリストを読み込み、ラベルを付与して結合 """
    df_list = []
    for i, filename in enumerate(file_list):
        try:
            df = pd.read_csv(filename)
            df['label'] = label_value # ラベル付与
            df_list.append(df)
            
            if (i + 1) % 5 == 0: # 5ファイルごとに進捗表示
                print(f"  [{i+1}/{len(file_list)}] 読み込み完了: {os.path.basename(filename)}")
                
        except Exception as e:
            print(f"  Error: {filename} の読み込みエラー -> {e}")

    if not df_list:
        return pd.DataFrame() # 空のデータフレームを返す
    
    return pd.concat(df_list, ignore_index=True)

def preprocess_data(df, is_training=True):
    """ データの前処理（シャッフル、不要列削除、欠損値処理） """
    if df.empty: # データ不足チェック
        return None, None

    # 1. シャッフル
    df = df.sample(frac=1, random_state=42).reset_index(drop=True) # 再現性のためにrandom_stateを固定

    # 2. 不要列削除
    cols_to_drop = [c for c in DROP_COLUMNS if c in df.columns] 
    X = df.drop(columns=cols_to_drop) # 不要な特徴量の削除
    y = df['label']

    # 3. 欠損値処理
    X = X.replace([np.inf, -np.inf], np.nan).fillna(0) # 無限大をNaNに変換し、NaNを0で埋める

    return X, y


# 3. メイン処理


def main():
    print("=== 処理を開始 ===")

    # A. データの読み込み
    print("\n[Step 1] ファイル読み込み")
    print("--- 正常データの読み込み ---")
    train_normal = load_files(train_normal_files, 0) # ラベル0
    test_normal = load_files(test_normal_files, 0) # ラベル0
    
    print("--- 攻撃データの読み込み ---")
    train_attack = load_files(train_attack_files, 1) # ラベル1
    test_attack = load_files(test_attack_files, 1) # ラベル1

    # 結合
    train_full = pd.concat([train_normal, train_attack], ignore_index=True) # 学習データ
    test_full = pd.concat([test_normal, test_attack], ignore_index=True) # テストデータ

    print(f"\n  -> 訓練データ合計: {len(train_full)} 行")
    print(f"  -> テストデータ合計: {len(test_full)} 行")

    if len(train_full) == 0 or len(test_full) == 0: # データ不足チェック
        print("\n[停止] データが不足しています。ファイル名やパスを確認してください。")
        return

    # B. 前処理
    print("\n[Step 2] 前処理")
    X_train, y_train = preprocess_data(train_full, is_training=True)
    X_test, y_test = preprocess_data(test_full, is_training=False)

    # C. 学習
    print("\n[Step 3] 学習 (Random Forest)")
    
    # ★ここを変更: class_weight='balanced' を追加して不均衡データに対処
    # n_jobs=-1 で全CPUコアを使用して高速化
    rf_model = RandomForestClassifier(
        n_estimators=100, 
        class_weight='balanced', 
        random_state=42,
        n_jobs=-1 
    )
    
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
    importances = rf_model.feature_importances_ # 特徴量重要度の取得
    indices = np.argsort(importances)[::-1] # 重要度の高い順にインデックスを取得
    features = X_train.columns # 特徴量名の取得
    for i in range(min(5, len(features))): # 上位5つを表示
        print(f"{i+1}. {features[indices[i]]}: {importances[indices[i]]:.4f}") 

if __name__ == "__main__":
    main()