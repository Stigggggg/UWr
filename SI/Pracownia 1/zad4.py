# tworzymy okienko o długości podanej jako 2 argument, za jego pomocą sprawdzamy każdy fragment danej długości
# przy każdym sprawdzeniu liczba zmian to ilość zamian 0->1 (w okienku) albo 1->0 (poza okienkiem), szukamy najmniejszej  

def opt_dist(list, d):
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

with open('zad4_input.txt', 'r', encoding='utf-8') as fin, open('zad4_output.txt', 'w', encoding='utf-8') as fout:
    for line in fin:
        line = line.split(" ")
        fout.write(str(opt_dist([int(x) for x in line[0]], int(line[1]))) + '\n')
            


