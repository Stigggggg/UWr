## Zad. 1

**Punkt montażowy (mount point)** - katalog lub plik, w którym nowy system plików, katalog lub plik otrzymał dostęp. Żeby zamontować system plików lub katalog, mount point musi być katalogiem, a żeby zamontować plik, musi być plikiem. 

Komenda na wypisanie: `mount -l`

Co znajduje się w kolumnach: 
- nazwa urządzenia lub źródła systemu plików,
- punkt montażowy,
- typ systemu plików, 
- jakieś opcje montowania.

**Pseudo systemy plików** - systemy plików, które nie zawierają plików, a wirtualne wejścia, które tworzy sam system. Służą do udostępniania informacji o systemie lub dostarczanie specjalnych funkcji:
- `/proc` - informacje o procesach i stanie systemu,
- `/sys` - informacje o urządzeniach i konfiguracji systemu,
- `/dev` - pliki urządzeń w systemie, 
`tmpfs` - system plików przechowywany w RAM.

Atrybuty:
- relatime - aktualizuje czas ostatniego dostępu do pliku tylko wtedy, gdy jest on starszy niż czas ostatniej modyfikacji lub zmiany metadanych. Scenariusz: na serwerach i laptopach, kiedy zależy nam na wydajności, ale nie chcemy wyłączać atime,
- noexec - blokuje wykonywanie plików binarnych w systemie plików. Scenariusz: przy montowaniu partycji zawierających dane użytkownika, aby uniemożliwić uruchamianie potencjalnie niebezpiecznych skryptów lub execów,
- nodev - ignoruje specjalne pliki urządzeń, dzięki czemu nie można używać ich dostępu do urządzeń. Scenariusz: montowanie partycji użytkowników lub zewnętrznych systemów plików, żeby zablokować możliwość tworzenia i używania urządzeń specjalnych, co zwiększa bezpieczeństwo systemu.

## Zad. 2

**Superblok** - zawiera wszystkie informacje dotyczące konfiguracji systemu plików. Zawiera pola takie jak całkowita liczba inodów, bloków w systemie, ile z nich jest wolnych, ile inodów i bloków jest w każdej grupie, kiedy system plików był zamontowany, kiedy był modyfikowany, jaka jest wersja systemu plików i jaki OS go stworzył. 

**Blok** - partycja, dysk, plik lub urządzenie blokowe formatowane ext2 jest podzielone na małe grupy sektorów zwane blokami, będącymi grupowanymi w większe jednostki zwane grupami bloków.

**Grupa bloków** - połączone bloki w większą strukturę w celu zmniejszenia fragmentacji i ułatwienia przeszukiwania danych.

**Tablica deskryptorów grup bloków** - tablica definiująca parametry grup bloków, przechowywana zaraz po superbloku.

Wzory:
- rozmiar bloku: `1024 << s_log_block_size`,
- liczba inodów w grupie: `s_inodes_per_group`,
- liczba bloków w grupie: `s_blocks_per_group`,
- liczba wpisów: `s_blocks_count / s_blocks_per_group`

Składowe grupy bloków:
- kopia superbloku (1024 B),
- tablica deskryptorów (1 blok),
- bitmapa bloków (1 blok),
- bitmapa inodów (1 blok),
- tablica inodów (23 bloki),
- bloki z danymi (1412 bloki)

Kopie superbloków są przechowywane w grupach 0, 1 i potęgach 3, 5 i 7.

## Zad. 3

**Blok pośredni** - zawiera wskaźniki na następny zbiór bloków, wskaźnik na podwójnie pośredni blok (który zawiera wskaźnik na bloki pośrednie), wskaźnik na potrójnie pośredni blok (zawiera wskaźniki na podwójnie pośrednie).

Aby dopisać n bloków na koniec pliku, musimy wybrać wolne bloki, zapalić ich bity, żeby wiadomo było, że są używane. Następnie zapisać zawartość i dodać je do i-węzła, w razie potrzeby tworzymy bloki pośrednie lub modyfikujemy istniejące, potem aktualizujemy metadane inoda.

**Zapis synchroniczny** - polega na zapisywaniu danych do deskryptora w taki sposób, żeby mogły być odzyskane np. po crashu systemu. 

**Spójność systemu plików** - polega na zapisie plików o podobnym zastosowaniu w tej samej grupie.

## Zad. 4

**Atomowość operacji** - do końca albo wcale, przerwanie operacji unieważnia ją i przywraca do stanu początkowego.

`rename` skończy się błędem `EXDEV`, ponieważ mimo że Linux pozwala systemowi plików być montowanym w kilku punktach, to sam `rename` nie działa na kilku, nawet jeśli jest na nich ten sam system.

Zwiększamy licznik dowiązań w inodzie przenoszonego pliku, jeśli w katalogu docelowym jest wyzerowany wpis, to zmieniamy go na wpis pliku, który akurat przenosimy. Wpp dodajemy do docelowego wpis przenoszonego pliku i modyfikujemy poprzedni tak, żeby nie wskazywał na koniec bloku. W poprzednim katalogu usuwamy wpis zmieniając wartość inode na 0 i zmieniamy licznik dowiązań w inodzie, żeby przed i po przeniesieniu był taki sam.

## Zad. 5

Zaczynamy od usunięcia wpisu z katalogu i dekrementacją licznika dowiązań. Jeśli ten licznik wynosi 0, to zwalniamy inoda i bloki, a jeśli większy, to nie robimy nic. Istnieje ryzyko awarii, gdy nastąpi bezpośrednio po usunięciu pliku, to będziemy mieć zajęty inode bez możliwości zwolnienia. Jeśli uda się zmniejszyć licznik, to zwolnienie będzie możliwe. Jeśli awaria nastąpi przez zwolnieniem bloków, to nie będziemy mogli nic z nimi zrobić.

Plik zostanie usunięty z dysku, gdy jego dane zostaną nadpisane lub gdy wszystkie deskryptory wskazujące na ten plik zostaną usunięte.

## Zad. 6

**Dowiązanie twarde** - wskaźnik na inode pliku wliczający się do licznika referencji do pliku. 

**Dowiązanie symboliczne** - dowiązanie kodujące ścieżkę, do której należy przekierować algorytm rozwiązywania nazw, dane w i-węźle.

Aby stworzyć pętlę, należy stworzyć dowiązanie symboliczne w dowolnym katalogu do katalogu . lub do ../

Pętli nie można stworzyć hardlinkiem, bo struktura danych systemu plików jest skierowanym grafem acyklicznym, a dowiązanie twarde stworzyłoby cykl, więc sprzeczność.

## Zad. 7

**Fragmentacja systemu plików** - sytuacja, gdy dane ułożone są w nieciągły sposób, co spowalnia do nich dostęp

**Odroczony przydział bloków** - zapisuje wszystkie żądania i wykonuje je dopiero w momencie, gdy wykonywany jest flush. W ten sposób zmniejszamy fragmentację.

**Zakresy** - pomagają w ograniczaniu rozmiaru metadanych przechowujących adresy bloków należących do tego samego pliku. Pole zakresu zajmuje 48 bitów i może reprezentować 2^15 bloków. Każdy węzeł w drzewie zaczyna się nagłówkiem z liczbą poprawnych wpisów. Sposób, w jaki zakresy pomagają jest prosty: tworzony jest tymczasowy inode, a następnie alokowany jest w nim ciągły zakres. Następnie dane są kopiowane z oryginalnego węzła do tymczasowego, a na końcu przepinamy wskaźniki. 

