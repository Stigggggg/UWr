## Zad. 1
**Zmienne współdzielone** - zmienne, do których co najmniej dwa wątki mają referencję. Tutaj są to:
- strtab, zmienna globalna `static`,
- cnt - statyczna zmienna lokalna, dla której istnieje tylko jedna instancja współdzielona przez wątki,
- argv[0] - przekazujemy 0 jako arg *thread,
- myid (jego adres) - przekazywany w `pthread_create()` i we wszystkich wątkach jest wykonywany dostęp do tej wartości

**Wyścig** - sytuacja, w której co najmniej 2 wątki mają dostęp do zmiennej współdzielonej w tym samym czasie i przynajmniej jeden z wątków próbuje modyfikować tą zmienną, dużo zależy od kolejności. Tutaj:
- cnt, więcej niż 1 wątek może odczytać i zapisać tą samą wartość,
- myid, gdy nowy wątek zostanie przypisany, to możliwe jest, że jego rodzic zmienił id

## Zad. 2
**Sekcja krytyczna** - miejsce w programie współbieżnym, w którym proces wykonuje operacje na współdzielonej pamięci, takie miejsce może być źródłem wyścigów. Rozwiązaniem problemu sekcji krytycznej może być:
- żadne dwa procesy nie mogą przebywać wewnątrz swoich sekcji krytycznych (wyścig),
- nie można przyjmować założeń dotyczących szybkości lub liczby procesorów, 
- proces działający wewnątrz regionu krytycznego nie może blokować innych,
- żaden proces nie może oczekiwać w nieskończoność na dostęp do regionu krytycznego,

**Wyłączenie przerwań** - sposób rozwiązania problemu sekcji krytycznych, polega na wyłączeniu obsługi przerwań, gdy w momencie, gdy proces wchodzi do sekcji krytycznej, a po włączeniu z niej wyjdzie.

**Blokowanie drobnoziarniste** - sposób pracy przy sekcjach krytycznych, polegający na wydzielaniu pojedynczych zmiennych i struktur, a następnie na utworzeniu dla każdej z nich osobnej blokady.

## Zad. 3
**Instrukcja atomowa** - instrukcja, której wykonanie nie może zostać przerwane. Dopóki nie wykona się cała, to nic innego nie może się wydarzyć. 

```c
int compare_and_swap (int* reg, int oldval, int newval) {
  int old_reg_val = *reg;
  if (old_reg_val == oldval) 
    *reg = newval;
  return old_reg_val;
}
```

**Blokada wirująca** - sposób na zatrzymanie wątków czekających na dostanie blokadu w pętli `while`.

```c 
typedef int spin_t;

void lock(spin_t *lock) {
  while (compare_and_swap(lock, 0, 1) == 1); // this semicolon is crucial!
}

void unlock(spin_t *lock) {
  *lock = 0;
}
```

**Blokada sprawiedliwa** - blokada, w której każdy wątek próbujący wejść w sekcję krytyczną i założyć blokadę powinien mieć takie same szansę na wykonanie. 

## Zad. 5
Warunki zakleszczenia:
- wzajemne wykluczanie - wątki przejmują wyłączną kontrolę nad zasobami, których potrzebują, 
- podtrzymanie własności - wątki nie zwalniają zasobów, oczekując na kolejne,
- pierwszeństwo - zasób zostaje przejęty i nie może zostać odebrany,
- wzajemne oczekiwanie - dwa wątki potrzebują zasobu i czekają na zasób. Aby jeden wątek go otrzymał, to musi zwolnić inny zasób, tak samo drugi.