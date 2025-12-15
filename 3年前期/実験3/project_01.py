import random
import math
import matplotlib.pyplot as plt

# 都市数（例：20）
n = 20

# # 重複のない都市座標（0?199）
# cities = set()
# while len(cities) < n:
#     x = random.randint(0, 199)
#     y = random.randint(0, 199)
#     cities.add((x, y))
# cities = list(cities)

# 固定された、バラけた都市座標
cities = [
    (12, 34), (87, 190), (33, 145), (172, 88), (5, 180),
    (115, 35), (196, 120), (42, 67), (160, 12), (77, 144),
    (190, 199), (134, 38), (56, 122), (25, 99), (180, 50),
    (9, 10), (150, 170), (100, 100), (80, 25), (60, 190)
]
n = len(cities)  # 都市数もこのリストから自動取得

# 距離を計算する関数（ユークリッド距離）
def distance(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

# 座標のプロット
x_vals = [x for x, y in cities]
y_vals = [y for x, y in cities]

plt.figure(figsize=(8, 8))
plt.scatter(x_vals, y_vals, color='blue')

# 各都市にラベル（City 0など）を付ける
for i, (x, y) in enumerate(cities):
    plt.text(x + 2, y + 2, f"City {i}", fontsize=9)

plt.title("2D layout of the city")
plt.xlabel("X-coordinate")
plt.ylabel("Y-coordinate")
plt.grid(True)
plt.xlim(0, 200)
plt.ylim(0, 200)
plt.gca().set_aspect('equal', adjustable='box')
plt.show()
