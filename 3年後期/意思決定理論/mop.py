import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, RadioButtons

# スカラー化関数の定義
def scalarization_function_1(F1, F2, w1, w2):
    return w1 * F1 + w2 * F2

def scalarization_function_2(F1, F2, w1, w2):
    return np.maximum(w1 * F1, w2 * F2)

def scalarization_function_3(F1, F2, w1, w2):
    return np.maximum(w1 * F1, w2 * F2) + 0.1 * (w1 * F1 + w2 * F2)

# 目的関数 f1 と f2 の範囲を [0, 1] に設定
f1_min, f1_max = 0, 1
f2_min, f2_max = 0, 1
num_points = 100

# f1 と f2 の値でグリッドを作成
f1 = np.linspace(f1_min, f1_max, num_points)
f2 = np.linspace(f2_min, f2_max, num_points)
F1, F2 = np.meshgrid(f1, f2)

# 初期の重み
w1_init = 0.5
w2_init = 0.5

# 初期のスカラー化関数
current_function = scalarization_function_1

# 初期のスカラー化値 S を計算
S = current_function(F1, F2, w1_init, w2_init)

# 図と軸を作成
fig, ax = plt.subplots(figsize=(10, 8))
plt.subplots_adjust(left=0.25, bottom=0.3)  # スライダーとボタンのスペースを確保

# 初期のヒートマップをプロット
contour = [ax.contourf(F1, F2, S, levels=50, cmap='viridis')]

# 最小の点とその他の点をプロットするための散布図を作成
scatter_min = ax.scatter([], [], color='blue', edgecolors='black', s=100, zorder=5, label='Min Solution')
scatter_others = ax.scatter([], [], color='red', edgecolors='black', s=100, zorder=5, label='Other Solutions')

ax.set_xlabel('Function f1')
ax.set_ylabel('Function f2')
ax.legend()

# カラーバーを追加
cbar = fig.colorbar(contour[0], ax=ax)
cbar.set_label('Scalar value S')

# 任意の点を定義
#points = np.array([
#    [0.2, 0.8],
#    [0.6, 0.4],
#    [0.7, 0.2],
#    [0.2, 0.9],
#    [0.2, 0.8]  # 最小値が複数になるように同じ点を追加
#])

points = np.array([
    [0.38, 0.13],
    [0.55, 0.56],
    [0.59, 0.13],
    [0.30, 0.50],
    [0.63, 0.67],
    [0.39, 0.70],
    [0.20, 0.91],
    [0.20, 0.71],
    [0.36, 0.37],
    [0.32, 0.76]  # 最小値が複数になるように同じ点を追加
])

# 初期のプロットを更新する関数
def initial_plot():
    global current_function
    # 任意の点でのスカラー化値を計算
    points_S = current_function(points[:, 0], points[:, 1], w1_init, w2_init)

    # スカラー化値の最小値を取得
    min_value = np.min(points_S)

    # 最小値を持つ点のインデックスを取得
    min_indices = np.where(points_S == min_value)[0]

    # 最小値を持つ点とその他の点を分離
    min_points = points[min_indices]
    other_indices = np.where(points_S != min_value)[0]
    other_points = points[other_indices]

    # 散布図を更新
    scatter_min.set_offsets(min_points)
    scatter_others.set_offsets(other_points)

    plt.gca().set_aspect('equal')

# 初期プロットを呼び出し
initial_plot()

# スライダーとラジオボタンの位置を定義
axcolor = 'lightgoldenrodyellow'
ax_w1 = plt.axes([0.25, 0.2, 0.65, 0.03], facecolor=axcolor)
ax_w2 = plt.axes([0.25, 0.15, 0.65, 0.03], facecolor=axcolor)
ax_func = plt.axes([0.025, 0.5, 0.15, 0.15], facecolor=axcolor)

# スライダーを作成
slider_w1 = Slider(ax_w1, 'Weight w1', 0.0, 1.0, valinit=w1_init)
slider_w2 = Slider(ax_w2, 'Weight w2', 0.0, 1.0, valinit=w2_init)

# ラジオボタンを作成（スカラー化関数の選択）
radio = RadioButtons(ax_func, ('Weighted', 'Theby', 'ModTheby'))

# コールバックIDを格納する変数
cid_w1 = None
cid_w2 = None

# 更新関数を定義
def update_w1(val):
    global cid_w2
    w1 = slider_w1.val
    w2 = 1.0 - w1

    # 一時的に slider_w2 のコールバックを無効化
    slider_w2.disconnect(cid_w2)
    slider_w2.set_val(w2)
    # コールバックを再接続
    cid_w2 = slider_w2.on_changed(update_w2)

    update_plot(w1, w2)

def update_w2(val):
    global cid_w1
    w2 = slider_w2.val
    w1 = 1.0 - w2

    # 一時的に slider_w1 のコールバックを無効化
    slider_w1.disconnect(cid_w1)
    slider_w1.set_val(w1)
    # コールバックを再接続
    cid_w1 = slider_w1.on_changed(update_w1)

    update_plot(w1, w2)

def update_plot(w1, w2):
    global current_function
    # 選択されたスカラー化関数を取得
    func_label = radio.value_selected
    if func_label == 'Weighted':
        current_function = scalarization_function_1
    elif func_label == 'Theby':
        current_function = scalarization_function_2
    elif func_label == 'ModTheby':
        current_function = scalarization_function_3

    # ヒートマップ用のスカラー化値を計算
    S = current_function(F1, F2, w1, w2)

    # 任意の点でのスカラー化値を計算
    points_S = current_function(points[:, 0], points[:, 1], w1, w2)

    # スカラー化値の最小値を取得
    min_value = np.min(points_S)

    # 最小値を持つ点のインデックスを取得
    min_indices = np.where(points_S == min_value)[0]

    # 最小値を持つ点とその他の点を分離
    min_points = points[min_indices]
    other_indices = np.where(points_S != min_value)[0]
    other_points = points[other_indices]

    # 散布図を更新
    scatter_min.set_offsets(min_points)
    scatter_others.set_offsets(other_points)

    # 古いヒートマップを削除
    for c in contour[0].collections:
        c.remove()
    # 新しいヒートマップをプロット
    contour[0] = ax.contourf(F1, F2, S, levels=50, cmap='viridis')

    # カラーバーを更新
    cbar.set_clim(S.min(), S.max())
    cbar.draw_all()

    # 図を再描画
    fig.canvas.draw_idle()

def update_radio(label):
    # スライダーから現在の重みを取得
    w1 = slider_w1.val
    w2 = slider_w2.val
    update_plot(w1, w2)

# コールバックを接続
cid_w1 = slider_w1.on_changed(update_w1)
cid_w2 = slider_w2.on_changed(update_w2)
radio.on_clicked(update_radio)

plt.show()
