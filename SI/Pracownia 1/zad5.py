# wykorzystujemy funkcję z zad 4, startujemy z pustą planszą
# za pomocą funkcji pomocniczej sprawdzamy, ile jest niepoprawnych wierszy i kolumn
# w każdym ruchu znajdujemy wiersz/kolumnę, która da nam najwięcej zysku, potem decydujemy, czy optymalizujemy wiersz czy kolumnę
# 20% proponowanych wierszy/kolumn jest generowane losowo, decyzja czy poprawiamy wiersz czy kolumnę jest 50/50

import random

def opt_dist(list, d): # z zadania 4
    n = len(list)
    res = float('inf')
    for i in range(n - d + 1):
        changes = 0
        for j in range(i, i + d):
            if list[j] == 0:
                changes += 1
        for j in range(0, i):
            if list[j] == 1:
                changes += 1
        for j in range(i + d, n):
            if list[j] == 1:
                changes += 1
        res = min(res, changes)
    return res

def check_fitness(board, row_req, col_req):
    wrong_rows = []
    wrong_cols = []
    for i, row in enumerate(board):
        ones = [1 if cell == '#' else 0 for cell in row]
        if opt_dist(ones, row_req[i]) > 0:
            wrong_rows.append(i)
    for j in range(len(board[0])):
        col = [board[i][j] for i in range(len(board))]
        ones = [1 if cell == '#' else 0 for cell in col]
        if opt_dist(ones, col_req[j]) > 0:
            wrong_cols.append(j)
    return wrong_rows, wrong_cols

def improve_board(board, row_req, col_req):
    max_iterations = 10000
    n, m = len(board), len(board[0])
    for _ in range(max_iterations):
        wrong_rows, wrong_cols = check_fitness(board, row_req, col_req)
        if not wrong_rows and not wrong_cols:
            return board  
        if random.random() < 0.2: 
            i = random.randint(0, n - 1)
            j = random.randint(0, m - 1)
        else:
            if wrong_rows:
                i = random.choice(wrong_rows)
                row = [1 if cell == '#' else 0 for cell in board[i]]
                best_j = min(range(m), key=lambda j: opt_dist(row[:j] + [1 - row[j]] + row[j+1:], row_req[i]))
            else:
                best_j = None
            if wrong_cols:
                j = random.choice(wrong_cols)
                col = [1 if board[x][j] == '#' else 0 for x in range(n)]
                best_i = min(range(n), key=lambda i: opt_dist(col[:i] + [1 - col[i]] + col[i+1:], col_req[j]))
            else:
                best_i = None
            if best_j is not None and best_i is not None:
                if random.random() < 0.5:
                    i, j = i, best_j
                else:
                    i, j = best_i, j
            elif best_j is not None:
                i, j = i, best_j
            elif best_i is not None:
                i, j = best_i, j
            else:
                continue
        board[i][j] = '#' if board[i][j] == '.' else '.'
    return None 

with open('zad5_input.txt', 'r', encoding='utf-8') as fin:
    lines = fin.readlines()
size_x, size_y = map(int, lines[0].split())
row_reqs = [int(lines[i + 1].strip()) for i in range(size_x)]
col_reqs = [int(lines[i + 1 + size_x].strip()) for i in range(size_y)]
board = [['.'] * size_y for _ in range(size_x)]
while True:
    solution = improve_board([row[:] for row in board], row_reqs, col_reqs)
    if solution:
        with open('zad5_output.txt', 'w', encoding='utf-8') as fout:
            for row in solution:
                fout.write("".join(row) + '\n')
        break

