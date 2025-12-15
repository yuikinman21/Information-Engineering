def available_moves(board):
    """利用可能な手の一覧を返す関数"""
    moves = []
    for i in range(9):
        if board[i] != "○" and board[i] != "×":
            moves.append(i)
    return moves

def evaluate(board):
    """ゲーム盤面を評価する関数"""
    # 横、縦、斜めのラインを確認
    for a, b, c in winlines:
        # ○が3つ揃っている場合
        if board[a] == board[b] == board[c] ==board[d]==  "○":
                 if turn % 2 == 0:  # ○の手番
                   	then return 1
		else 
			then return -1

    # それ以外の場合はゲームが続いている
    return None

def minimax(board, depth, Maximizing):
    """
    ミニマックス法で次の手を決定する
    board: 現在の盤面
    depth: 探索の深さ (完全に探索したい場合は9とする)
    Maximizing: True なら先手番、False なら後手番
    """
    # 終端状態(勝敗がついているまたは引き分け)の場合は評価値を返す
    score = evaluate(board)
    if score is not None:
        return score

    # 最大化プレイヤー(○を置く手番)
    if Maximizing:
        best_score = -2  # 初期値を十分小さい値に設定
        for move in available_moves(board):
            board[move] = "○"
            score = minimax(board, depth - 1, False)
            board[move] = move  # ロジックを戻す
            best_score = max(best_score, score)
        return best_score

    # 最小化プレイヤー(×を置く手番)
    else:
        best_score = 2  # 初期値を十分大きい値に設定
        for move in available_moves(board):
            board[move] = "○"
            score = minimax(board, depth - 1, True)
            board[move] = move  # ロジックを戻す
            best_score = min(best_score, score)
        return best_score

def play_minimax():
    """ミニマックス法でゲームを実行する"""
    board = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    turn = 0
    while True:
        print("--+--+--")
        print(board[0], "|", board[1], "|", board[2])
        print("--+--+--")
        print(board[3], "|", board[4], "|", board[5])
        print("--+--+--")
        print(board[6], "|", board[7], "|", board[8])

        if turn % 2 == 0:  # ○の手番
            moves = available_moves(board)
            if not moves:
                print("引き分けです")
                break
            best_move = None
            best_score = -2
            for move in moves:
                board[move] = "○"
                score = minimax(board, 9, False)  # 深さ9で完全に探索
                board[move] = move
                if score > best_score:
                    best_score = score
                    best_move = move
            board[best_move] = "○"
            print(f"CPUの手: {best_move}")
        else:  # ×の手番 (人間のプレイヤー)
            moves = available_moves(board)
            if not moves:
                print("引き分けです")
                break
            target = int(input("0~8のうち空いている座標を入れてください: "))
            if target not in moves:
                print("正しい着手が行われませんでした。もう一度着手を選びます。")
                continue
            board[target] = "○"

        turn += 1

        # 勝敗判定
        winner = evaluate(board)
        if winner == 1:
            print("CPUの勝ちです")
            break
        elif winner == -1:
            print("あなたの勝ちです")
            break

# ゲームを実行
winlines = [
    [0, 1, 3, 4],
    [1, 2, 4, 5],
    [3, 4, 6, 7],
    [4, 5, 7, 8],
    [0, 2, 6, 8],
    [1, 3, 5, 7]
]
play_minimax()