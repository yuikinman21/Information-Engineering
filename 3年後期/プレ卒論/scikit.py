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


RATIO_NORMAL = 1.0
RATIO_ATTACK = 0.001 

# 学習・評価に不要な列
DROP_COLUMNS = [
    'flow_id', 'src_ip', 'dst_ip', 'src_port', 'dst_port', 'timestamp', 'label'
]

# ファイルリストの取得
print("ファイルを検索中...")
all_normal_files = glob.glob(NORMAL_DIR)
all_attack_files = glob.glob(ATTACK_DIR)

print(f"  -> 正常ファイル: {len(all_normal_files)} 個見つかりました")
print(f"  -> 攻撃ファイル: {len(all_attack_files)} 個見つかりました")

# ファイル単位で学習用(70%)とテスト用(30%)にランダム分割
# これにより、特定の攻撃種類が片方に偏るのを防ぎつつ、未知のファイルでテストできます
train_normal_files, test_normal_files = train_test_split(all_normal_files, test_size=0.3, random_state=42)
train_attack_files, test_attack_files = train_test_split(all_attack_files, test_size=0.3, random_state=42)



# 2. 関数定義


def load_and_reduce_files(file_list, label_value, sample_ratio):
    df_list = []
    for i, filename in enumerate(file_list):
        try:
            df = pd.read_csv(filename)
            
            # 1. 不要な列を即座に削除 (メモリ節約)
            cols_to_drop = [c for c in DROP_COLUMNS if c in df.columns]
            df.drop(columns=cols_to_drop, inplace=True)
            
            # 2. ダウンサンプリング (指定した割合だけランダムに抽出)
            if sample_ratio < 1.0:

                df = df.sample(frac=sample_ratio, random_state=42)
            

            float_cols = df.select_dtypes(include=['float64']).columns
            df[float_cols] = df[float_cols].astype('float32')
            
            # int64 -> int32 (大きな桁を使わない場合)
            int_cols = df.select_dtypes(include=['int64']).columns
            df[int_cols] = df[int_cols].astype('int32')

            # ラベル付与
            df['label'] = label_value 
            
            df_list.append(df)
            
            # 進捗表示 (5ファイルごと)
            if (i + 1) % 5 == 0:
                print(f"  [{i+1}/{len(file_list)}] 完了: {os.path.basename(filename)} ({len(df)}行抽出)")
                
        except Exception as e:
            print(f"  Error: {filename} -> {e}")

    if not df_list:
        return pd.DataFrame()
    
    return pd.concat(df_list, ignore_index=True)

def preprocess_data(df):
    """ 前処理（シャッフル、欠損値処理） """
    if df.empty:
        return None, None

    # シャッフル
    df = df.sample(frac=1, random_state=42).reset_index(drop=True)

    # 特徴量(X)とラベル(y)の分離
    y = df['label']
    X = df.drop(columns=['label'])

    # 欠損値処理 (無限大やNaNを0にする)
    X = X.replace([np.inf, -np.inf], np.nan).fillna(0)

    return X, y



# 3. メイン処理


def main():
    print("=== 処理を開始 ===")
    print(f"  [設定] 正常データ採用率: {RATIO_NORMAL*100}%")
    print(f"  [設定] 攻撃データ採用率: {RATIO_ATTACK*100}%")

    # A. データの読み込み
    print("\n[Step 1] ファイル読み込み & 抽出")
    
    # --- 正常データ (100%使用) ---
    print("--- 正常データ読み込み ---")
    train_normal = load_and_reduce_files(train_normal_files, 0, sample_ratio=RATIO_NORMAL)
    test_normal = load_and_reduce_files(test_normal_files, 0, sample_ratio=RATIO_NORMAL)
    
    # --- 攻撃データ (0.01%使用) ---
    print("--- 攻撃データ読み込み ---")
    train_attack = load_and_reduce_files(train_attack_files, 1, sample_ratio=RATIO_ATTACK)
    test_attack = load_and_reduce_files(test_attack_files, 1, sample_ratio=RATIO_ATTACK)

    # 結合
    train_full = pd.concat([train_normal, train_attack], ignore_index=True)
    test_full = pd.concat([test_normal, test_attack], ignore_index=True)

    # メモリ解放
    del train_normal, train_attack, test_normal, test_attack
    import gc
    gc.collect()

    print(f"\n  -> 訓練データ合計: {len(train_full)} 行")
    print(f"  -> テストデータ合計: {len(test_full)} 行")

    if len(train_full) == 0 or len(test_full) == 0:
        print("\n[停止] データが不足しています。パスやサンプリング率を確認してください。")
        return

    # B. 前処理
    print("\n[Step 2] 前処理 (欠損値処理など)")
    X_train, y_train = preprocess_data(train_full)
    X_test, y_test = preprocess_data(test_full)
    
    del train_full, test_full
    gc.collect()

    # C. 学習
    print("\n[Step 3] 学習 (Random Forest)")
    
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