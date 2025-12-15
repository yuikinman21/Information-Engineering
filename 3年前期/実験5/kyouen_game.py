def available_moves(board):
    """利用可能な手の一覧を返す関数"""
    moves = []
    for i in range(9):
        if board[i] == 0:
            moves.append(i)
    return moves
    
def check(board, turn):
    """ゲーム盤面を評価する関数"""
    for a, b, c, d in kyouen:

        if board[a] == board[b] == board[c] == board[d] == 1:
            return True
    return False

def evaluate(board, turn):
    if check(board, turn):
        return -1  # 直前に置いた手番の負け
    if not available_moves(board):
        return 0   # 引き分け
    return None    # ゲーム続行

def minimax(board, depth, Maximizing, turn):
    """
    ミニマックス法で次の手を決定する
    board: 現在の盤面
    depth: 探索の深さ (完全に探索したい場合は9とする)
    Maximizing: True なら○を置く手番、False なら×を置く手番
    """
    # 終端状態(勝敗がついているまたは引き分け)の場合は評価値を返す
    result = evaluate(board, turn)
    if result is not None:
        return result

    
    for move in available_moves(board):
        board[move] = 1 # 点を置く
        score = minimax(board, depth - 1, True, turn + 1) # 深さ9で完全に探索
        board[move] = 0 # 点を戻す
        if score == -1: # 相手が負ける＝自分の勝ち
            return 1 # 直前に置いた手番の勝ち

    return -1 # どこに置いても相手を負けにできない＝自分の負け

def play_minimax():
    """ミニマックス法でゲームを実行する"""
    board = [0] * 9
    turn = 0

    while True:
        print(board[0], "|", board[1], "|", board[2])
        print("--+--+--")
        print(board[3], "|", board[4], "|", board[5])
        print("--+--+--")
        print(board[6], "|", board[7], "|", board[8])
        
        moves = available_moves(board)
        if not moves:
            print("引き分けです")
            break

        best_move = None
        for move in moves:
            board[move] = 1
            score = minimax(board, 9, False, turn + 1)  # 深さ9で完全に探索
            board[move] = 0
            if score == 1:
                best_move = move
                break
                
        if best_move is None:
            best_move = moves[0]

        board[best_move] = 1 # 石を置く
        
        if turn % 2 == 0:
            print("player0: ", best_move)
            if check(board, turn):
                print("共円ができたので、後手が必ず勝つ")
                break
        else:
            print("player1: ", best_move)
            if check(board, turn):
                print("共円ができたので、先手が必ず勝つ")
                break
            
        turn += 1
        

# ゲームを実行
kyouen = [[0,1,3,4],[1,2,4,5],[3,4,6,7],
          [4,5,7,8],[0,1,6,7],[1,2,7,8],
          [0,2,3,5],[3,5,6,8],[0,2,6,8],
          [1,3,5,7],[0,1,5,8],[1,2,3,6],
          [0,3,7,8],[2,5,6,7]]

play_minimax()