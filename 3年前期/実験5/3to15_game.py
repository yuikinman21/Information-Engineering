import random

def available_moves(board):
    """利用可能な手の一覧を返す関数"""
    moves = []
    for i in range(10):  # 0から9までの数字を使用
        if board[i] != "○" and board[i] != "×":
            moves.append(i)
    return moves

def evaluate(board):
    """ゲーム盤面を評価する関数"""
    # 横、縦、斜めのラインを確認
    for a, b, c in winlines:
        # ○が3つ揃っている場合および、0,6,9と0,7,8が揃っている場合
        if board[a] == board[b] == board[c] == "○":
            return 1  # ○の勝ち
        # ×が3つ揃っている場合および、0,6,9と0,7,8が揃っている場合
        elif board[a] == board[b] == board[c] == "×":
            return -1  # ×の勝ち

    # 空きマスがない場合 (引き分け)
    if not available_moves(board):
        return 0

    # それ以外の場合はゲームが続いている
    return None

def minimax(board, depth, Maximizing):
    """
    ミニマックス法で次の手を決定する
    board: 現在の盤面
    depth: 探索の深さ (完全に探索したい場合は9とする)
    Maximizing: True なら○を置く手番、False なら×を置く手番
    """
    # 終端状態(勝敗がついているまたは引き分け)の場合は評価値を返す
    score = evaluate(board)
    # print(score)
    if score is not None:
        return score

    # 最大化プレイヤー(○を置く手番)
    if Maximizing:
        best_score = -200  # 初期値を十分小さい値に設定
        for move in available_moves(board):
            board[move] = "○"
            score = minimax(board, depth - 1, False)
            if score == 1:
                board[move] = move  # ロジックを戻す
                return 1
            if depth <= 7:
                score = score + 1
            elif depth <= 5:
                score = score + 2
            board[move] = move  # ロジックを戻す
            best_score = max(best_score, score)
        # print(best_score)
        return best_score

    # 最小化プレイヤー(×を置く手番)
    else:
        best_score = 200  # 初期値を十分大きい値に設定
        for move in available_moves(board):
            board[move] = "×"
            score = minimax(board, depth - 1, True)
            if score == -1:
                board[move] = move  # ロジックを戻す
                return -1
            if depth <= 7:
                score = score - 1
            elif depth <= 5:
                score = score - 2
            board[move] = move  # ロジックを戻す
            best_score = min(best_score, score)
        # print(best_score)
        return best_score

def play_minimax():
    """ミニマックス法でゲームを実行する"""
    board = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    turn = 0
    while True:
        print("----------")
        print(board[2], "|", board[9], "|", board[4])
        print("--+---+---")
        print(board[7], "|", board[5], "|", board[3])
        print("--+---+---")
        print(board[6], "|", board[1], "|", board[8])
        print("----------\n")
        print(board[0], "|", board[6], "|", board[9])
        print("----------")
        print(board[0], "|", board[7], "|", board[8])

        if turn % 2 == 0:  # ○の手番
            moves = available_moves(board)
            if not moves:
                print("引き分けです")
                print("よって必ず引き分ける")
                break
            best_move = None
            best_score = -2
            for move in moves:
                board[move] = "○"
                score = minimax(board, 11, False)
                board[move] = move
                if score > best_score:
                    best_score = score
                    best_move = move
            board[best_move] = "○"
            print(f"Player0の手: {best_move}")
            print(f"Player0の手の評価値: {best_score}")
        else:  # ×の手番
            moves = available_moves(board)
            if not moves:
                print("引き分けです")
                print("よって必ず引き分ける")
                break
            best_move = None
            best_score = 2
            for move in moves:
                board[move] = "×"
                score = minimax(board, 11, True)
                board[move] = move
                if score < best_score:
                    best_score = score
                    best_move = move
            board[best_move] = "×"
            print(f"Player1の手: {best_move}")
            print(f"Player1の手の評価値: {best_score}")

        turn += 1

        # 勝敗判定
        winner = evaluate(board)
        if winner == 1:
            print("Player0の勝ちです")
            print("よって必ず先手が勝利する")
            break
        elif winner == -1:
            print("Player1の勝ちです")
            print("よって必ず後手が勝利する")
            break

# ゲームを実行
winlines = [[1,5,9],[1,6,8],[2,6,7],
            [2,5,8],[2,4,9],[3,4,8], 
            [3,5,7],[4,5,6],[0,6,9],
            [0,7,8]]

play_minimax()