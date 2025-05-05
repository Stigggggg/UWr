import itertools
from collections import deque
from functools import lru_cache

# generujemy wszystkie możliwe linie długości length, które spełniają pattern
def generate_possible_lines(length, pattern, current_line):
    results = []

    def dfs(pos, block_idx, line): # pos - gdzie jesteśmy, block - który blok, line - dotychczas zbudowana linia
        if block_idx == len(pattern): # jeśli umieściliśmy już wszystkie bloki
            # to wypełniamy resztę linii kropkami
            if all(current_line[i] in ('.', None) for i in range(pos, length)):
                results.append(line + ['.'] * (length - len(line)))
            return
        block = pattern[block_idx]
        for start in range(pos, length - block + 1):
            if start > 0 and (start - 1 < len(line) and line[start - 1] == '#' or (current_line[start - 1] == '#')): # czy możemy zacząć tu blok
                continue # w takiej sytuacji nie, bo musi być oddzielone przerwą
            fits = True
            for k in range(block):
                if current_line[start + k] not in (None, '#'): # jeśli jest kropka, to nie możemy tu postawić
                    fits = False
                    break
            if not fits:
                continue
            new_line = line + ['.'] * (start - len(line)) + ['#'] * block # budujemy linię
            if start + block < length:
                new_line.append('.')
            dfs(start + block + 1, block_idx + 1, new_line)

    dfs(0, 0, [])
    return results

# pomocnicza funkcja, aktualizuje planszę, jeśli na jakimś miejscu jest zawsze ten sam znak w każdej możliwej linii
def update_board_from_domain(board, idx, domain, axis):
    updated = False
    if not domain:
        return updated
    domain_list = list(domain)
    length = len(domain_list[0])
    for i in range(length):
        possible_values = set(line[i] for line in domain_list) # zbiór możliwych znaków w kolumnie/wierszu
        if len(possible_values) == 1: # jeśli jest jeden możliwy element, to go ustawiamy, nie ma innej opcji
            val = possible_values.pop()
            if axis == 'row': # zmieniamy wiersz czy kolumnę
                if board[idx][i] != val:
                    board[idx][i] = val
                    updated = True
            else:
                if board[i][idx] != val:
                    board[i][idx] = val
                    updated = True
    return updated

@lru_cache(maxsize=None)
def ac3(board, row_req, col_req):
    n, m = len(board), len(board[0])
    row_domains = [set(tuple(line) for line in generate_possible_lines(m, row_req[i], board[i])) for i in range(n)]
    col_domains = [set(tuple(line) for line in generate_possible_lines(n, col_req[j], [board[i][j] for i in range(n)])) for j in range(m)]
    queue = deque([(i, 'row') for i in range(n)] + [(j, 'col') for j in range(m)])
    while queue:
        idx, typ = queue.popleft()
        if typ == 'row':
            current_line = board[idx]
            possible_lines = generate_possible_lines(m, row_req[idx], current_line) # filtrujemy linie zgodne z dziedzinami linii w kolumnach dla wiersza 
            new_domain = set(tuple(line) for line in possible_lines if all(any(line[j] == col[idx] for col in col_domains[j]) for j in range(m)))
            if new_domain != row_domains[idx]: # jeśli dziedzina się zmieniła
                row_domains[idx] = new_domain
                # aktualizujemy planszę i dorzucamy do kolejki sąsiadujące wiersze
                updated = update_board_from_domain(board, idx, new_domain, axis='row')
                if updated:
                    queue.extend((j, 'col') for j in range(m))
        else: # to samo dla kolumn
            current_line = [board[i][idx] for i in range(n)]
            possible_cols = generate_possible_lines(n, col_req[idx], current_line)
            new_domain = set(tuple(col) for col in possible_cols if all(any(col[i] == row[idx] for row in row_domains[i]) for i in range(n)))
            if new_domain != col_domains[idx]:
                col_domains[idx] = new_domain
                updated = update_board_from_domain(board, idx, new_domain, axis='col')
                if updated:
                    queue.extend((i, 'row') for i in range(n))
    if any(len(domain) != 1 for domain in row_domains):
        return None
    return [list(next(iter(row_domains[i]))) for i in range(n)]

with open("zad_input.txt", "r", encoding="utf-8") as fin:
    lines = fin.readlines()
size_x, size_y = map(int, lines[0].split())
row_req = [list(map(int, lines[i + 1].strip().split())) for i in range(size_x)]
col_req = [list(map(int, lines[i + 1 + size_x].strip().split())) for i in range(size_y)]
board = [[None for j in range(size_y)] for i in range(size_x)]
solution = ac3(board, row_req, col_req)
if solution:
    with open('zad_output.txt', 'w', encoding='utf-8') as fout:
        for row in solution:
            fout.write("".join(row) + '\n')

