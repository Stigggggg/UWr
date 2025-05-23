import sys

def V(i,j):
    return 'V%d_%d' % (i,j)

def get_row(i, c):
    return [V(i,j) for j in range(c)] 
            
def get_column(j, r):
    return [V(i,j) for i in range(r)] 

def domains(Vs):
    return [ q + ' in 0..1' for q in Vs ]

# ograniczenia na trójki 1x3 albo 3x1
def triplets(r, c):
    cons = []
    for i in range(r):
        for j in range(2, c-2):
            cons.append('tuples_in([[%s, %s, %s]], [[1,1,1], [0,1,1], [0,0,1], [0,0,0], [1,0,0], [1,1,0], [1,0,1]])' 
                        % (V(i, j-1), V(i, j), V(i, j+1)))
    for j in range(c):
        for i in range(2, r-2):
            cons.append('tuples_in([[%s, %s, %s]], [[1,1,1], [0,1,1], [0,0,1], [0,0,0], [1,0,0], [1,1,0], [1,0,1]])' 
                        % (V(i-1, j), V(i, j), V(i+1, j)))
    return cons

# ograniczenia na kwadraty 2x2
def squares(r, c):
    cons = []
    for i in range(r-1):
        for j in range(c-1):
            cons.append(('tuples_in([[%s, %s, %s, %s]], [[1,1,1,1], [0,0,0,0],'
                         '[0,0,0,1], [0,0,1,0], [0,1,0,0], [1,0,0,0],'
                         '[1,1,0,0], [1,0,1,0], [0,1,0,1], [0,0,1,1]])') 
                         % (V(i, j), V(i+1, j), V(i, j+1), V(i+1, j+1)))
    return cons

def print_constraints(Cs, indent, d):
    position = indent
    print(indent * ' ', end='')
    for c in Cs:
        print(c + ',', end=' ')
        position += len(c)
        if position > d:
            position = indent
            print()
            print(indent * ' ', end='')

# jak w nonogramach, ile jedynek w rzędzie
def ones_in_row(r, rows):
    cons = []
    for i in range(r):
        cons.append('sum([%s], #=, %d)' % (', '.join(get_row(i, len(rows))), rows[i]))
    return cons

# to samo w kolumnie
def ones_in_col(c, cols):
    cons = []
    for j in range(c):
        cons.append('sum([%s], #=, %d)' % (', '.join(get_column(j, len(cols))), cols[j]))
    return cons

def storms(r, c, fills, rows, cols):
    variables = [V(i,j) for i in range(r) for j in range(c)]
    print(':- use_module(library(clpfd)).')
    print('solve([' + ', '.join(variables) + ']) :-')
    cs = domains(variables) + triplets(r, c) + squares(r, c) + ones_in_row(r, rows) + ones_in_col(c, cols)
    for i,j,val in fills:
        cs.append('%s #= %d' % (V(i,j), val))
    print_constraints(cs, 4, 120)
    print()
    print('labeling([ff], [' + ', '.join(variables) + ']).')
    print()
    print(':- solve(X), write(X), nl.')

with open('zad_input.txt', 'r', encoding='utf-8') as fin, open('zad_output.txt', 'w', encoding='utf-8') as fout:
    rows = list(map(int, fin.readline().strip().split()))
    r = len(rows)
    cols = list(map(int, fin.readline().strip().split()))
    c = len(cols)
    fills = []
    for line in fin:
        fills.append(list(map(int, line.strip().split())))
    with open('zad_output.txt', 'w') as sys.stdout:
        storms(r, c, fills, rows, cols)

