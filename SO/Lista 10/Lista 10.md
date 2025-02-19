## Zad. 1

**Przetwarzanie równoległe** - polega na jednoczesnym przetwarzaniu wielu różnych zadań czy obliczeń (np. przez 2 procesory albo więcej).

**Przetwarzanie współbieżne** - polega na współistnieniu wielu wątków lub procesów. Uruchomione wątki na tym samym procesorze są wykonywane naprzemiennie, co sprawia wrażenie, że wykonywane są równolegle.

**Procedura wielobieżna** - procedura, której wykonywanie może zostać przerwane np. przerwaniem lub wywołaniem innej funkcji wewnątrz ciała funkcji, następnie może ona zostać ponownie wywołana, nawet zanim zakończy się poprzednie wywołanie. Po zakończeniu drugiego można wrócić do pierwszego. Nie powinna operować na niestałych zmiennych globalnych i `static`, nie może modyfikować kody i nie może wywoływać procedur wielobieżnych.

Wielobieżna, ale nie wątkowo bezpieczna: swap

Wątkowo bezpieczna, ale nie wielobieżna: increment_counter

## Zad. 2

**Zakleszczenie (deadlock)** - sytuacja, w której wątek A czeka na zakończenie wątku B i na odwrót, przez co żaden nie może się zakończyć, bo czekają na siebie nawzajem. 

**Uwięzienie (livelock)** - sytuacja, w której dwa wątki zatrzymują działanie, aby uniknąć deadlocka, jednak robią to równocześnie, więc nie jest możliwe wykonanie żadnego z nich. W przeciwieństwie do deadlocka, stan wątku może ulec zmianie. 

**Głodzenie (starvation)** - sytuacja, w której wątek nie otrzymuje dostępu do zasobu, na który czeka, przez co nie może rozpocząć działania.  

## Zad. 3

Najmniejsza możliwa wartość tally: jeśli oba procesy pracują współbieżnie i wykonują wszystkie iteracje "niezależnie", to zawsze się nawzajem nadpisują. Czyli tylko jeden proces zwiększa tally.
Zatem najmniejsza wartość to 50.

Największa możliwa wartość ma miejsce, gdy procesy wykonują operacje w sposób rozłączny, czyli inkrementowane są jeden po drugim, zatem oba procesy wpływają na zmianę wartości zmiennej.
Największa wartość dla 2 to 2 * 50 = 100, a dla k: 50*k

Alternatywny rozw: 
- minimum: 2 iteracje
- maksimum: 50 * k 

## Zad. 6

`poll(2)` wprowadzono jako bardziej elastyczną i skalowalną alternatywę dla wcześniejszych metod zarządzania zdarzeniami na deskryptorach plików, takich jak odpytywanie deskryptorów, sygnalizacja za pomocą `SIGIO` i efektywne monitorowanie wielu deskryptorów jednocześnie.

Lepiej użyć `poll`, ponieważ:
- obsługuje dużą liczbę deskryptorów w jednej funkcji, co jest bardziej efektywne niż wielokrotne odpytywanie jednego,
- upraszcza kod przez przekazanie listy gotowych deskryptorów,
- minimalizuje zużycie CPU, 
- nie wymaga konfiguracji sygnałów

`poll` może monitorować zdarzenia na deskryptorach plików, gniazdach sieciowych, deskryptorach urządzeń, FIFO (potoki nazwane), deskryptorach epoll, jeśli są obsługiwane przez system. 

Tryb nieblokujący daje następująca korzyści:
- lepsza kontrola przepływu, `poll` poinformuje program, gdy deskryptor jest gotowy do operacji, zamiast go wstrzymywać,
- uniknięcie deadlocków,
- można przełączać się między zadaniami zamiast czekać na zakończenie operacji

```c
#include <fcntl.h>
int flags = fcntl(fd, F_GETFL, 0);  
fcntl(fd, F_SETFL, flags | O_NONBLOCK); 
```

Funkcja poll(2) zwraca strukturę pollfd, która zawiera pole revents opisujące zdarzenia, które wystąpiły na danym deskryptorze. Aby uniknąć błędu EWOULDBLOCK, należy sprawdzić, czy odpowiedni bit w revents jest ustawiony:
- dla operacji read: pole revents powinno zawierać flagę POLLIN.
- dla operacji write pole revents powinno zawierać flagę POLLOUT.
- dla gniazda gotowego do nawiązania połączenia (connect)pole revents powinno zawierać flagę POLLOUT.

Aby mieć pewność, że dane wywołanie systemowe (np. read, write, connect, accept) nie zwróci EWOULDBLOCK, jądro musi wpisać odpowiednią wartość do pola revents:
- POLLIN, gdy deskryptor jest gotowy do odczytu.
- POLLOUT, gdy deskryptor jest gotowy do zapisu.
- POLLPRI, gdy dostępne są dane o wysokim priorytecie.
- POLLERR/POLLHUP, wskazuje na błędy lub zamknięcie połączenia, w przypadku operacji takich jak accept.
