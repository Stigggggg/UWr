## Zad. 1
```
ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd - wydruk
man ps | less /STAT - znaczenie znaków w kolumnie STAT
pstree - drzewiasta reprezentacja
```
**Identyfikator procesu (pid)** - unikalny identyfikator danego procesu, używany do jego identyfikacji w Linuxie i innych systemach. Jego wartość jest liczbą całkowitą, ujemną gdy wystąpił błąd w procesie (np. w jego tworzeniu forkiem), zerem gdy proces jest dzieckiem (nowym procesem) lub liczbą dodatnią, gdy proces jest rodzicem (wtedy zwraca pid dziecka),

**Identyfikator grupy procesów (pgid)** - identyfikator zbioru procesów, które mogą razem otrzymywać te same sygnały,

**Identyfikator rodzica (ppid)** - pozwala zidentyfikować rodzica procesu, czyli proces, który za pomocą fork utworzył swoje dzieci, rodzicem init jest kernel o ppid 0,

**Właściciel** - użytkownik, który uruchomił proces i może go np. zatrzymać lub zabić,

**Wątki jądra** - wątki wykonujące kod jądra, niepowiązane z procesami użytkownika (bo inny tryb), po dodaniu vsz to są procesy `root`,

Aby dowiedzieć się, jakie jest znaczenie poszczególnych znaków w kolumnie STAT wystarczy wpisać w terminal `man ps`. Z kolei wątki jądra w drzewie procesów (`pstree`) możemy rozpoznać chociażby po cmd w nawiasach kwadratowych.

## Zad. 2
Gdy proces staje się sierotą, jego rodzicem staje się proces init i to on go grzebie (z wyjątkem long-running procesów (shelle i serwery), wtedy jest grzebanie explicit).

**Zombie** - procesy, których działanie się zakończyło, ale nie zostały zakończone całkowicie przez system (np. nie ma jeszcze kodu powrotu), występują gdy proces rodzic nie obsłużył poprawnie swoich dzieci, przez co zalegają one w systemie. Procesy zombie mają literę Z w kolumnie STAT. Grzebanie procesów może się odbyć komendą `kill -9`, która kończy proces siłą.

Proces nie może sam siebie pogrzebać, ponieważ formalnie został już zakończony, stan zombie jest jedynie informacją, że status wykonania procesu nie został jeszcze odebrany przez proces nadrzędny.

Gdyby nie było ograniczeń na waitpid wystąpiłyby następujące komplikacje:
- zaburzenie integralności i bezpieczeństwa procesu,
- stworzenie niepotrzebnej nieprzewidywalności procesu i trudności z nią związanych,
- race conditions skutkujące utratą danych niektórych procesów,
- zepsucie relacji rodzic-dziecko

## Zad. 3 
proc(5) to system plików, który dostarcza interfejs do struktur danych w jądrze systemu. Zazwyczaj jest zakorzeniany w `/proc`, najczęściej przez system, ale można też użyć komendy:
```
mount -t proc proc /proc
```
**Argumenty programu** - parametry przekazane do programu w momencie wywołania w wierszu poleceń (argc i argv[]). Znajdują się w pliku /proc/[pid]/cmdline.

**Zmienne środowiskowe** - zmienne, których wartości są ustawiane poza programem, np. nazwane wartości przechowywane i zarządzane przez system. Znajdują się w pliku /proc/[pid]/environ

Tłumaczenie znaczenia pól w pliku `status`:
- Uid - identyfikator użytkownika,
- Gid - identyfikator grupy,
- Groups - lista grup dziedziczących po rodzicu, mówiących jakie uprawnienia ma proces,
- VmPeak - największy rozmiar pamięci wirtualnej,
- VmSize - aktualny rozmiar pamięci wirtualnej,
- VmRSS - rozmiar zbioru roboczego procesu (pamięci wirtualnej używanej przez proces),
- Threads - liczba wątków w procesie,
- voluntary_ctxt_switches - liczba dobrowolnych zmian kontekstu (np. proces opuszcza CPU, bo nie ma nic do roboty i np. oczekuje na IO),
- nonvoluntary_ctxt_switches - liczba zmian kontekstu wywołanych przez wywłaszczenie procesu.

```
cd /proc/[pid] - wejście do katalogu
cat cmdline - wypisanie argumentów wywołania
cat environ - wypisanie zmiennych środowiskowych
cat status - wypisanie statusu
```

## Zad. 4
**X-serwer** - system okienkowy do wyświetlania bitmap, często spotykany na systemach Uniksowych.
```
ps ax | grep X
```
Tą komendą znajdujemy procesy X-serwera, następnie pmapem uzyskujemy zawartość przestrzeni adresowej. 

Stos jest na samym dole, można wywołać `sudo less /proc/1957/maps`

Stertę można znaleźć w /proc/[pid]/maps

**Segmenty programu** - spójne bloki pamięci o jednolitym przeznaczeniu i artybutach z punktu widzenia procesu ładowania i uruchamiania programu. Jeden segment może zawierać wiele sekcji. Segmenty są zmapowane do Xorg

**Pamięć anonimowa** - pamięć niebędąca powiązana z żadnym plikiem ani obiektem. Jest oznaczona [anon].

**Pliki odwzorowane w pamięć** - segment pamięci wirtualnej mający bezpośrednie mapowanie co do bajta z jakimś plikiem lub zasobem. Znajdujemy je w `Mapping`.

## Zad. 5
https://hackmd.io/@whiskeyo/SJg5MOoJD

```
pgrep firefox - znalezienie pid firefox
lsof -p [pid] - wyświetlenie zasobów plikopodobnych podpiętych do procesu
```

Znaczenie kolumn wydruku lsof:
- COMMAND - polecenie, które uruchomiło proces,
- PID - identyfikator procesu,
- USER - właściciel procesu,
- FD - numer deskryptora lub jedna z opcji:
    - cwd - bieżący katalog,
    - L[nn] - referencje bibliotek,
    - err - informacja błędu FD,
    - jld - katalog jail,
    - ltx - dzielona biblioteka text (na kod i dane),
    - M[xx]- pamięć mapowana w systemie hex,
    - m86 - plik mapowany przez Merge,
    - mem - plik zmapowany w pamięci,
    - mmap - urządzenie zmapowane w pamięci,
    - pd - katalog rodzica,
    - rtd - katalog roota,
    - tr - plik z trybu jądra,
    - txt - tekst programu,
- TYPE - typ węzła powiązanego z plikiem:
    - DIR - katalog,
    - DEL - usunięty plik zmapowany,
    - REG - plik zwykły,
    itd.
- DEVICE - numer urządzenia,
- SIZE/OFF - rozmiar pliku/offest w bajtach,
- NODE - nr węzła lub pliku lokalnego,
- NAME - nazwa pliku mount i systemu plików

**Plik zwykły** - plik, który ma - w polu trybu, oznaczany jako REG,

**Katalog** - zawiera referencje do innych plików i katalogów, oznaczany jako DIR,

**Plik urządzenia** - służy do komunikacji programu z urządzeniem poprzez sterowniki przy użyciu syscall wejścia/wyjścia,

**Gniazdo** - dwukierunkowy punkt końcowy połączenia, oznaczane jako sock, IPv4, unix itp.

**Potok** - mechanizm komunikacji międzyprocesowej pozwalający na wymianę danych między procesami, oznaczany jako FIFO

```
lsof -p [pid] > before - lsof z jednej otwartej strony
lsof -p [pid] > after - lsof z innej otwartej strony
colordiff before after | grep IPv4 - znalezienie różnic i wyróżnienie kolorami (tak znajdujemy nowe połączenia sieciowe)
```

## Zad. 6
```
time find/usr
```
**User** - ilość czasu spędzonego w trybie użytkownika w trakcie procesu. Inne procesy i czas, kiedy proces jest np. blokowany się do tego nie liczą.

**Sys** - ilość czasu spędzonego w trybie jądra, działa podobnie jak user pod względem podejścia do innych procesów.

**Real** - czas od początku do końca procesu, tu liczą się czasy innych procesów i czas, podczas którego proces był np. blokowany (chociażby czekając na zakończenie I/O)

User może być większy niż real, gdy proces używa kilku rdzeni, wtedy czasy są sumowane (https://stackoverflow.com/questions/15928334/user-time-larger-than-real-time)

Ograniczenie - `ulimit -t [sekundy]`