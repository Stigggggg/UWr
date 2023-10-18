import string
import random
def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    slowa = tekst.split()
    slowa_bez_int = [slowo.strip(string.punctuation) for slowo in slowa]
    for i in slowa_bez_int:
        if len(i) > dl_slowa:
            slowa_bez_int.remove(i)
    ile_usunac = len(slowa_bez_int)-liczba_slow
    do_usuniecia = random.sample(slowa_bez_int, ile_usunac)
    for i in do_usuniecia:
        slowa_bez_int.remove(i)
    wynik = " ".join(slowa_bez_int)
    return wynik

print(uprosc_zdanie("Podział peryklinalny inicjałów wrzecionowatych kambium charakteryzuje się ścianą podziałową inicjowaną w płaszczyźnie maksymalnej.", 10, 5))
with open('tekst.txt', 'r', encoding='utf-8') as plik: tekst = plik.read()
print(uprosc_zdanie(tekst, 10, 15))




