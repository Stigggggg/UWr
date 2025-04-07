import itertools
from collections import deque

def is_matching(line, pattern): # zmieniona funkcja z P1, sprawdza czy rząd/kolumna zgadza się z wzorcem
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

def generate_possible_lines(length, pattern): # pomocnicza funkcja do generowania możliwych ułożeń "#"
    positions = [i for i in range(length)]
    for combs in itertools.combinations(positions, sum(pattern) + len(pattern) - 1): # generujemy możliwe pozycje dla "#"
        # sum + len - 1 daje to, czego chcemy, bo sum to liczba "#", a len - 1 to liczba koniecznych odstępów
        line = ['.'] * length
        block_index = 0 # aktualnie rozmieszczany blok
        for idx in combs:
            if block_index < len(pattern) and (idx == 0 or line[idx - 1] == '.'): # szukamy miejsca, od którego możemy zacząć blok "#"
                for k in range(pattern[block_index]):
                    if idx + k >= length or line[idx + k] == '#': # wyjście poza zakres lub kolizja z innym blokiem
                        break
                    line[idx + k] = '#'
                block_index += 1
        if is_matching(line, pattern):
            yield ''.join(line)

def ac3(board, row_req, col_req):
    n, m = len(board), len(board[0])
    row_domains = [set(generate_possible_lines(m, row_req[i])) for i in range(n)] # zbiory możliwych ustawień dla każdego rzędu
    col_domains = [set(generate_possible_lines(n, col_req[j])) for j in range(m)] # to samo dla kolumn
    queue = deque([(i, 'row') for i in range(n)] + [(j, 'col') for j in range(m)])
    while queue:
        idx, typ = queue.popleft() 
        if typ == 'row': # rozpatrujemy rzędy
            new_row_domain = set()
            for row in row_domains[idx]: # idziemy przez możliwości dla danego rzędu
                if all(any(row[j] == col[idx] for col in col_domains[j]) for j in range(m)): # jeśli istnieje dobra konfiguracja, dodajemy do nowej dziedziny
                    new_row_domain.add(row)
            if new_row_domain != row_domains[idx]: # jeśli zmniejszyła się dziedzina, to jeszcze raz dodajemy do kolejki kolumny, żeby sprawdzić, czy nie trzeba czegoś odrzucić
                row_domains[idx] = new_row_domain
                queue.extend((j, 'col') for j in range(m))
        else: # to samo z kolumnami
            new_col_domain = set()
            for col in col_domains[idx]:
                if all(any(col[i] == row[idx] for row in row_domains[i]) for i in range(n)):
                    new_col_domain.add(col)
            if new_col_domain != col_domains[idx]:
                col_domains[idx] = new_col_domain
                queue.extend((i, 'row') for i in range(n))
    if any(len(domain) != 1 for domain in row_domains) or any(len(domain) != 1 for domain in col_domains):
        return None
    return [list(row_domains[i].pop()) for i in range(n)]

with open("zad_input.txt", "r", encoding="utf-8") as fin:
    lines = fin.readlines()
size_x, size_y = map(int, lines[0].split())
row_req = [list(map(int, lines[i + 1].strip().split())) for i in range(size_x)]
col_req = [list(map(int, lines[i + 1 + size_x].strip().split())) for i in range(size_y)]
solution = ac3([['.'] * size_y for _ in range(size_x)], row_req, col_req)
if solution:
    with open('zad_output.txt', 'w', encoding='utf-8') as fout:
        for row in solution:
            fout.write("".join(row) + '\n')
