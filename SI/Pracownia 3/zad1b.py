import itertools
from collections import deque
from functools import lru_cache

@lru_cache(maxsize=None)
def generate_possible_lines(length, pattern_key, current_line_key):
    pattern = list(pattern_key)
    current_line = list(current_line_key)
    results = []

    def dfs(pos, block_idx, line):
        if block_idx == len(pattern):
            if all(current_line[i] in ('.', None) for i in range(pos, length)):
                results.append(tuple(line + ['.'] * (length - len(line))))
            return
        block = pattern[block_idx]
        for start in range(pos, length - block + 1):
            if start > 0:
                if (start - 1 < len(line) and line[start - 1] == '#') or current_line[start - 1] == '#':
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

def update_board_from_domain(board, idx, domain, axis):
    updated = False
    if not domain:
        return updated
    length = len(domain[0])
    for i in range(length):
        possible_values = set(line[i] for line in domain)
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

    row_domains = []
    for i in range(n):
        domain = generate_possible_lines(m, tuple(row_req[i]), tuple(board[i]))
        row_domains.append(set(domain))

    col_domains = []
    for j in range(m):
        col_line = tuple(board[i][j] for i in range(n))
        domain = generate_possible_lines(n, tuple(col_req[j]), col_line)
        col_domains.append(set(domain))

    queue = deque([(i, 'row') for i in range(n)] + [(j, 'col') for j in range(m)])

    while queue:
        idx, typ = queue.popleft()
        if typ == 'row':
            current_line = tuple(board[idx])
            possible_lines = generate_possible_lines(m, tuple(row_req[idx]), current_line)
            new_domain = set()
            for line in possible_lines:
                valid = True
                for j in range(m):
                    if not any(col_line[idx] == line[j] for col_line in col_domains[j]):
                        valid = False
                        break
                if valid:
                    new_domain.add(line)
            if new_domain != row_domains[idx]:
                row_domains[idx] = new_domain
                updated = update_board_from_domain(board, idx, list(new_domain), axis='row')
                if updated:
                    queue.extend((j, 'col') for j in range(m))
        else:
            current_line = tuple(board[i][idx] for i in range(n))
            possible_cols = generate_possible_lines(n, tuple(col_req[idx]), current_line)
            new_domain = set()
            for col in possible_cols:
                valid = True
                for i in range(n):
                    if not any(row[idx] == col[i] for row in row_domains[i]):
                        valid = False
                        break
                if valid:
                    new_domain.add(col)
            if new_domain != col_domains[idx]:
                col_domains[idx] = new_domain
                updated = update_board_from_domain(board, idx, list(new_domain), axis='col')
                if updated:
                    queue.extend((i, 'row') for i in range(n))
    if any(len(domain) != 1 for domain in row_domains):
        return None
    return [list(next(iter(domain))) for domain in row_domains]

with open("zad_input.txt", "r", encoding="utf-8") as fin:
    lines = fin.readlines()
size_x, size_y = map(int, lines[0].split())
row_req = [list(map(int, lines[i + 1].strip().split())) for i in range(size_x)]
col_req = [list(map(int, lines[i + 1 + size_x].strip().split())) for i in range(size_y)]
board = [[None for _ in range(size_y)] for _ in range(size_x)]
solution = ac3(board, row_req, col_req)
if solution:
    with open('zad_output.txt', 'w', encoding='utf-8') as fout:
        for row in solution:
            fout.write("".join(row) + '\n')


