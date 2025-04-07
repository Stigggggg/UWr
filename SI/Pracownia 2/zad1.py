import random

def is_matching(line, pattern): # zmodyfikowana funkcja z P1 sprawdzająca, czy linia pasuje do wzorca
    count = 0
    groups = []
    for i in line:
        if i == "#":
            count += 1
        elif count > 0:
            groups.append(count)
            count = 0
    if count > 0:
        groups.append(count)
    return groups == pattern

def check_fitness(board, row_req, col_req): # funkcja zwracająca zbiór rzędów i kolumn do poprawy
    wrong_rows = []
    wrong_cols = []
    for i, row in enumerate(board):
        if not is_matching(row, row_req[i]):
            wrong_rows.append(i)
    for j in range(len(board[0])):
        col = [board[i][j] for i in range(len(board))]
        if not is_matching(col, col_req[j]):
            wrong_cols.append(j)
    return wrong_rows, wrong_cols

def flip(board, i, j):
    board[i][j] = '#' if board[i][j] == '.' else '.'

def improve_board(board, row_req, col_req, max_iterations=10000): # główna funkcja
    n, m = len(board), len(board[0])
    for i in range(max_iterations):
        wrong_rows, wrong_cols = check_fitness(board, row_req, col_req)
        if not wrong_rows and not wrong_cols: # jeśli nie ma złych rzędów/kolumn, to mamy rozwiązanie
            return board
        if random.random() < 0.9:
            if random.random() < 0.5 and wrong_rows: # poprawiamy rzędy
                i = random.choice(wrong_rows)
                best_j, best_gain = None, -1
                for j in range(m):
                    flip(board, i, j) # zamieniamy jedno pole, sprawdzamy czy jest lepiej
                    new_wrong_rows, new_wrong_cols = check_fitness(board, row_req, col_req)
                    gain = (len(wrong_rows) + len(wrong_cols)) - (len(new_wrong_rows) + len(new_wrong_cols))
                    if gain > best_gain: # szukamy takiej zmiany, która najwięcej nam dała
                        best_gain = gain
                        best_j = j
                    flip(board, i, j) 
                if best_j is not None:
                    flip(board, i, best_j)
            elif wrong_cols: # poprawiamy kolumny, analogicznie
                j = random.choice(wrong_cols)
                best_i, best_gain = None, -1
                for i in range(n):
                    flip(board, i, j)
                    new_wrong_rows, new_wrong_cols = check_fitness(board, row_req, col_req)
                    gain = (len(wrong_rows) + len(wrong_cols)) - (len(new_wrong_rows) + len(new_wrong_cols))
                    if gain > best_gain:
                        best_gain = gain
                        best_i = i
                    flip(board, i, j)  
                if best_i is not None:
                    flip(board, best_i, j)
        else: # 10% losowości, zmniejszone z 20%
            i = random.randint(0, n - 1)
            j = random.randint(0, m - 1)
            flip(board, i, j)
    return None 

with open("zad_input.txt", "r", encoding="utf-8") as fin:
    lines = fin.readlines()
size_x, size_y = map(int, lines[0].split())
board = [['.'] * size_y for i in range(size_x)]
row_req = [list(map(int, lines[i + 1].strip().split())) for i in range(size_x)]
col_req = [list(map(int, lines[i + 1 + size_x].strip().split())) for i in range(size_y)]
while True:
    solution = improve_board([row[:] for row in board], row_req, col_req)
    if solution:
        with open('zad_output.txt', 'w', encoding='utf-8') as fout:
            for row in solution:
                fout.write("".join(row) + '\n')
        break

            

    