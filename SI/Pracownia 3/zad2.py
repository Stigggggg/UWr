import itertools
from collections import deque
import copy

# bez zmian
def generate_possible_lines(length, pattern, current_line):
    results = []

    def dfs(pos, block_idx, line):
        if block_idx == len(pattern):
            if all(current_line[i] in ('.', None) for i in range(pos, length)):
                results.append(line + ['.'] * (length - len(line)))
            return
        block = pattern[block_idx]
        for start in range(pos, length - block + 1):
            if start > 0 and (start - 1 < len(line) and line[start - 1] == '#' or (current_line[start - 1] == '#')):
                continue
            fits = True
            for k in range(block):
                if current_line[start + k] not in (None, '#'):
                    fits = False
                    break
            if not fits:
                continue
            new_line = line + ['.'] * (start - len(line)) + ['#'] * block
            if start + block < length:
                new_line.append('.')
            dfs(start + block + 1, block_idx + 1, new_line)

    dfs(0, 0, [])
    return results

# bez zmian
def update_board_from_domain(board, idx, domain, axis):
    updated = False
    if not domain:
        return updated
    domain_list = list(domain)
    length = len(domain_list[0])
    for i in range(length):
        possible_values = set(line[i] for line in domain_list)
        if len(possible_values) == 1:
            val = possible_values.pop()
            if axis == 'row':
                if board[idx][i] != val:
                    board[idx][i] = val
                    updated = True
            else:
                if board[i][idx] != val:
                    board[i][idx] = val
                    updated = True
    return updated

def ac3(board, row_req, col_req):
    n, m = len(board), len(board[0])
    row_domains = [set(tuple(line) for line in generate_possible_lines(m, row_req[i], [None]*m)) for i in range(n)]
    col_domains = [set(tuple(line) for line in generate_possible_lines(n, col_req[j], [None]*n)) for j in range(m)]
    queue = deque([(i, 'row') for i in range(n)] + [(j, 'col') for j in range(m)])
    while queue:
        idx, typ = queue.popleft()
        if typ == 'row':
            # optymalizacja: zamiast wielokrotnie generować nowe linie, sprawdzamy tylko istniejące możliwe linie
            allowed_in_cols = [] # dla każdej kolumny, co może być na każdej jej pozycji
            for j in range(m):
                allowed = {col[idx] for col in col_domains[j]} # co może być na danej pozycji w kolumnie, patrząc na jej dziedzinę
                allowed_in_cols.append(allowed) 
            # sprawdzamy, czy potencjalne linie wiersza są zgodne z możliwościami dla kolumn
            new_domain = set()
            for line in row_domains[idx]:
                ok = True
                for j in range(m):
                    # warunek 1: jeśli plansza ma wpisaną wartość w tym miejscu, to line musi pasować
                    if board[idx][j] is not None and board[idx][j] != line[j]:
                        ok = False
                        break
                    # warunek 2: ta wartość linii musi być w ogóle dopuszczalna
                    if line[j] not in allowed_in_cols[j]:
                        ok = False
                        break
                # jeśli warunki się nie wywaliły, dodajemy linię do nowej dziedziny
                if ok:
                    new_domain.add(line)
            if not new_domain:
                return None
            if new_domain != row_domains[idx]: # jeśli coś zmieniliśmy, to aktualizacja, sprawdzamy czy jakieś pola można ,,zatwierdzić"
                row_domains[idx] = new_domain
                updated = update_board_from_domain(board, idx, new_domain, axis='row')
                if updated:
                    queue.extend((j, 'col') for j in range(m)) 
        else: # to samo dla kolumn
            allowed_in_rows = []
            for i in range(n):
                allowed = {row[idx] for row in row_domains[i]}
                allowed_in_rows.append(allowed)
            new_domain = set()
            for col in col_domains[idx]:
                ok = True
                for i in range(n):
                    if board[i][idx] is not None and board[i][idx] != col[i]:
                        ok = False
                        break
                    if col[i] not in allowed_in_rows[i]:
                        ok = False
                        break
                if ok:
                    new_domain.add(col)
            if not new_domain:
                return None
            if new_domain != col_domains[idx]:
                col_domains[idx] = new_domain
                updated = update_board_from_domain(board, idx, new_domain, axis='col')
                if updated:
                    queue.extend((i, 'row') for i in range(n))
    return board

# funkcja pomocnicza, sprawdza, czy w każde pole jest zapełnione . lub #
def is_board_complete(board):
    return all(all(cell in ('.', '#') for cell in row) for row in board)

# backtracking
def solve(board, row_req, col_req):
    board = ac3(board, row_req, col_req)
    # 2 corner case
    if board is None:
        return None
    if is_board_complete(board):
        return board
    # jeśli gdzieś na planszy jest None
    n, m = len(board), len(board[0])
    best_i, best_j = None, None
    best_options = None
    for i in range(n):
        for j in range(m):
            if board[i][j] is None:
                # znajdujemy to miejsce i próbujemy podstawić w nie . lub #
                options = ['#', '.']
                if best_options is None or len(options) < len(best_options):
                    best_options = options
                    best_i, best_j = i, j
    if best_i is None:
        return None  
    for val in best_options:
        new_board = [row.copy() for row in board]
        new_board[best_i][best_j] = val
        # wywołujemy się rekurencyjnie z zaaktualizowaną planszą
        attempt = solve(new_board, row_req, col_req)
        if attempt is not None:
            return attempt
    return None

with open("zad_input.txt", "r", encoding="utf-8") as fin:
    lines = fin.readlines()
size_x, size_y = map(int, lines[0].split())
row_req = [list(map(int, lines[i + 1].strip().split())) for i in range(size_x)]
col_req = [list(map(int, lines[i + 1 + size_x].strip().split())) for i in range(size_y)]
board = [[None for j in range(size_y)] for i in range(size_x)]
solution = solve(board, row_req, col_req)
if solution:
    with open('zad_output.txt', 'w', encoding='utf-8') as fout:
        for row in solution:
            fout.write("".join(row) + '\n')
