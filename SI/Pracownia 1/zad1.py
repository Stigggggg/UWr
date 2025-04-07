# zgodnie ze wskazówką, stosuję w tym zadaniu algorytm BFS.
# najważniejsze parametry stanu gry to który gracz ma ruch, pozycje obu królów i wieży
# w trakcie bfs sprawdzane są wszystkie przypadki, takie jak szach, mat, blokowanie wieży przez białego króla i pat

from collections import deque

king_options = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
rook_options = [(-1, 0), (0, -1), (0, 1), (1, 0)]

def is_inside(row, col):
    if 0 <= row < 8 and 0 <= col < 8:
        return True
    else:
        return False
    
def is_adjacent(pos1, pos2):
    if abs(pos1[0] - pos2[0]) <= 1 and abs(pos1[1] - pos2[1]) <= 1:
        return True
    else:
        return False
    
def is_between(pos1, pos2, curr_pos):
    if pos1[0] == pos2[0] == curr_pos[0]:
        if min(pos1[1], pos2[1]) < curr_pos[1] and curr_pos[1] < max(pos1[1], pos2[1]):
            return True
        else:
            return False
    if pos1[1] == pos2[1] == curr_pos[1]:
        if min(pos1[0], pos2[0]) < curr_pos[0] and curr_pos[0] < max(pos1[0], pos2[0]):
            return True
        else:
            return False
    return False

def king_moves(row, col):
    moves = []
    for dr, dc in king_options:
        if is_inside(row + dr, col + dc):
            moves.append((row + dr, col + dc))
    return moves

def legal_white_king(move, rook, black_king):
    if is_inside(*move) and move != rook and not is_adjacent(move, black_king):
        return True
    else: 
        return False

def is_rook_blocked(pos, rook, white_king):
    if rook is None:
        return False
    if pos[0] == rook[0] and not is_between(rook, pos, white_king):
        return True
    if pos[1] == rook[1] and not is_between(rook, pos, white_king):
        return True
    return False

def legal_black_king(new_coords, wk, wr):
    if not is_inside(*new_coords) or is_adjacent(new_coords, wk):
        return False
    if wr is not None and new_coords == wr:
        return True
    return not is_rook_blocked(new_coords, wr, wk)

def rook_moves(row, col, wk, bk):
    moves = []
    for dr, dc in rook_options:
        new_r, new_c = row + dr, col + dc
        while is_inside(new_r, new_c) and (new_r, new_c) not in [wk, bk]:
            moves.append((new_r, new_c))
            new_r += dr
            new_c += dc
    return moves

def is_check(white_king, rook, black_king):
    if rook is None:
        return False
    if (black_king[0] == rook[0] and not is_between(rook, black_king, white_king)) or (black_king[1] == rook[1] and not is_between(rook, black_king, white_king)):
        return True
    else:
        return False   
    
def bfs(turn, wk, wr, bk, debug=False):
    queue = deque([((turn, wk, wr, bk), 0, [])])  
    visited = {(turn, wk, wr, bk)}
    while queue:
        (turn, wk, wr, bk), move_count, path = queue.popleft()
        if turn == "black" and wr is not None and is_check(wk, wr, bk):
            if all(not legal_black_king(move, wk, wr) for move in king_moves(*bk)):
                if debug:
                    for state in enumerate(path + [(turn, wk, wr, bk)]):
                        print(state)
                return move_count
        if turn == "white":
            for new_coords in king_moves(*wk):
                if legal_white_king(new_coords, wr, bk):
                    new_state = ("black", new_coords, wr, bk)
                    if new_state not in visited:
                        visited.add(new_state)
                        queue.append((new_state, move_count + 1, path + [(turn, wk, wr, bk)]))
            if wr is not None:
                for new_coords in rook_moves(*wr, wk, bk):
                    new_state = ("black", wk, new_coords, bk)
                    if new_state not in visited:
                        visited.add(new_state)
                        queue.append((new_state, move_count + 1, path + [(turn, wk, wr, bk)]))
        else:  
            for new_coords in king_moves(*bk):
                if legal_black_king(new_coords, wk, wr):
                    new_state = ("white", wk, wr if new_coords != wr else None, new_coords)
                    if new_state not in visited:
                        visited.add(new_state)
                        queue.append((new_state, move_count + 1, path + [(turn, wk, wr, bk)]))

    return "INF"


def parse_position(pos):
    return 8 - int(pos[1]), ord(pos[0]) - ord("a")

with open("zad1_input.txt", "r") as infile, open("zad1_output.txt", "w") as outfile:
    for line in infile:
        data = line.strip().split()
        turn, w_king, rook, b_king = data[0], parse_position(data[1]), parse_position(data[2]), parse_position(data[3])
        result = bfs(turn, w_king, rook, b_king)
        outfile.write(str(result) + "\n")


