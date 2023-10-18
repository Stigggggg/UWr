def kompresja(tekst):
    nowy = []
    wyst = 1
    for i in range(1,len(tekst)):
        if tekst[i] == tekst[i-1]:
            wyst += 1
        else:
            nowy.append((wyst, tekst[i-1]))
            wyst = 1
    nowy.append((wyst, tekst[-1]))
    return nowy

print(kompresja("suuupppeeeeeer"))

def dekompresja(tekst):
    nowy=""
    for i in tekst:
        nowy += i[0] * i[1]
    return nowy

print(dekompresja([(1, 's'), (4, 'u'), (1, 'p'), (1, 'e'), (1, 'r')]))

with open("tekst.txt",'r', encoding='utf-8') as plik: tekst = plik.read()
print(kompresja(tekst))
print(dekompresja(kompresja(tekst)))