## Zad. 1
![4.6](https://i.imgur.com/iBH0iar.png)

Stany procesu w systemie Linux:
- **running** - proces albo wykonywany (executing), albo gotowy do wykonania (ready),
- **interruptible** - stan, w którym proces czeka na event taki jak np. I/O, dostępność konkretnego zasobu albo sygnał od innego procesu,
- **uninterruptible** - różnica z poprzednim polega na tym, że w tym stanie proces zależy od urządzenia i nie będzie obsługiwać żadnych sygnałów (**różni się tym od interruptible!**),
- **stopped** - proces został wstrzymany i może być wznowiony jedynie przez akcję ze strony innego procesu, np. proces debugowany,
- **zombie** - proces, który został zakończony, ale nie pogrzebany przez jądro/akcję użytkownika

Zmiany stanu i akcje je wywołujące:

- Akcje jądra:
    - ready -> executing - rozpoczęcie procesu,
    - executing -> ready - zaplanowanie procesu,
    - executing -> stopped - zatrzymanie procesu odpowiednim sygnałem,
    - stopped -> ready - przygotowanie procesu odpowiednim sygnałem (SIGCONT),
    - interruptible -> ready - wybudzenie procesu odpowiednim sygnałem,
    - executing -> zombie - zabicie procesu sygnałem SIGKILL,
- Akcje sterowników:
    - uninterruptible -> ready - wybudzenie procesu za pomocą I/O lub dostępnością zasobów, 
    - interruptible -> ready - w sumie to samo,
- Akcje użytkownika:
    - executing -> interruptible 

**Zablokowanie sygnału** - niedostarczenie sygnału do momentu odblokowania go przez system operacyjny.

**Zignorowanie sygnału** - sytuacja, w której nie została zdefiniowana procedura obsługi konkretnego sygnału. 

SIGKILL nie da się zablokować, zignorowanie go spowoduje zabicie procesu, SIGSEGV nie da się zignorować ani zablokować.

## Zad. 2
Tworzenie nowego procesu w Linuxie: najpierw tworzone są deskryptor procesu i przestrzeń użytkownika, których zawartość jest wypełniana przez rodzica. Następnie nowy proces dostaje swoje PID, mapę pamięci i dzielony dostęp do plików rodzica. Następnie przygotowywane są jego rejestry, po czym proces jest gotowy do uruchomienia.

![linux](https://i.imgur.com/rQMgdZe.png)

Tworzenie nowego procesu w Windowsie: Tworzenie procesu w systemie WinNT różni się znacząco, wywołuje się tam procedurę CreateProcess, która jako argument przyjmuje nazwę pliku wykonywalnego. Procedura ta tworzy zupełnie nowy proces (a nie klonuje, jak w przypadku Linuxa). Stworzony proces (dziecko) nie otrzymuje kopii pamięci swojego rodzica.

Jeśli system posiada wywołanie spawn, które łączy funkcje `fork()` i `execve()` w jedno, powstają problemy z obsługą przekierowań standardowego wejścia/wyjścia oraz tworzenia potoków. Dzieje się tak dlatego, że w klasycznym modelu fork() i execve(), można:
- Wykonać fork() w celu utworzenia procesu dziecka.
- Następnie w dziecku ustawić przekierowania deskryptorów plików (np. standardowe wejście/wyjście do plików lub potoków).
- Dopiero po przekierowaniu deskryptorów plików wywołać execve(), aby uruchomić nowy program, mając pewność, że korzysta on z odpowiednio ustawionych wejść/wyjść.

W przypadku wywołania spawn, które bezpośrednio tworzy nowy proces i uruchamia w nim program, nie ma miejsca na ustawienie przekierowań przed załadowaniem programu. W efekcie nie da się przekierować standardowego wejścia/wyjścia do plików, ponieważ program już jest uruchomiony. Tworzenie potoków między procesami staje się problematyczne, ponieważ procesy muszą mieć skonfigurowane deskryptory plików przed rozpoczęciem wykonywania kodu, co w przypadku spawn jest trudne lub niemożliwe do zrealizowania.

## Zad. 3
Zasoby dziedziczone przez proces potomny (8.3 APUE):
- Real user ID, real group ID, effective user ID, and effective group ID
- Supplementary group IDs
- Process group ID
- Session ID
- Controlling terminal
- The set-user-ID and set-group-ID flags
- Current working directory
- Root directory
- File mode creation mask
- Signal mask and dispositions
- The close-on-exec flag for any open file descriptors
- Environment
- Attached shared memory segments
- Memory mappings
- Resource limits

Zasoby przekazywane do nowego programu załadowanego do przestrzeni adresowej (APUE 8.10):
- Process ID and parent process ID
- Real user ID and real group ID
- Supplementary group IDs
- Process group ID
- Session ID
- Controlling terminal
- Time left until alarm clock
- Current working directory
- Root directory
- File mode creation mask
- File locks
- Process signal mask
- Pending signals
- Resource limits
- Nice value (on XSI-conformant systems; see Section 8.16)
- Values for tms_utime, tms_stime, tms_cutime, and tms_cstime

Przed wywołaniem fork należy opróżnić bufory stdio, ponieważ chcemy uniknąć kilkukrotnego wypisywania danych. Po execve proces nie ma dostępu do poprzedniego kodu, nie może więc odziedziczyć procesów obsługi sygnałów, dlatego wszystkie są resetowane do stanu SIG_DFL (poza SIG_IGN). Nowy proces może stworzyć na nowo swoje własne procesy obsługi.


## Zad. 4
kill [pid] - default signal is TERM

pkill [nazwa procesu] - SIGTERM

xkill - kliknięcie na okno które chcemy zabić

CTRL+Z wysyła SIGSTP, fg wysyła SIGCONT

xeyes & - puszczenie procesu xeyes w tle

```
kill -10 [pid]
cat /proc/[pid]/status
kill -12 [pid]
cat /proc/[pid]/status
kill -1 [pid]
cat /proc/[pid]/status
kill -2 [pid]
cat /proc/[pid]/status
```
Po wpisaniu fg dostajemy komunikat o rozłączeniu xeyes, czyli pierwszy był SIGHUP

## Zad. 5
SIGUSR1 - wyłącza komputer,
SIGCHLD - grzebie dzieci,
SIGALRM - 
SIGINT - resetuje komputer,

sigprocmask - manipuluje maską sygnałów, blokuje i odblokowuje sygnały

sigwait - czeka na wystąpienie sygnału zablokowanego przez sigprocmask

Grzebiemy w funkcji sigreap(), za pomocą waitpid() przeglądamy procesy potomne i je grzebiemy. Flaga WNOHANG sprawia, że waitpid nie blokuje jeśli żaden proces potomny się nie zaczęły.


