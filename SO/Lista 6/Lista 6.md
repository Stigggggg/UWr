## Zad. 1

**Tożsamość procesu** - zbiór identyfikatorów i grup powiązanych z danym procesem. Real ID definiuje, kto jest właścicielem procesu. Effective ID używane jest w celu określenia uprawnień procesu przy dostępie do zasobów (np. plików). 

`ruid` - real user ID (my, użytkownik z loginem i hasłem), 

`euid` - effective user ID, 

`suid` - saved user ID.

Na początku `ruid`=1000, `euid`=0, `suid`=0. 

1. setuid(2000) - ustawia wszystkie wartości na 2000, bo `euid` jest równe superuserowi (0),
2. setreuid(-1, 2000) - `ruid` zostaje na 1000, bo -1 w argumencie pozostawia dane ID niezmienione, `euid` ulega zmianie na 2000. Saved user ID ulega zmianie na coś innego niż `ruid`, więc również przyjmuje wartość 2000.
3. seteuid(2000) - zmianie podlega jedynie `euid` na 2000, reszta zostaje jak na początku.
4. setresuid(-1, 2000, 3000) - tak samo jak w 2. tylko mamy 3 argumenty, -1 przy `ruid` go nie zmienia, `euid` zostaje ustawione na 2000, zaś `suid` na 3000.\

Podany w zadaniu proces nie jest uprzywilejowany, bo ma `euid` różniące się od zera.

## Zad. 2
r - można czytać wyłącznie zawartość pliku katalogu,

w - write - można modyfikować zawartość pliku katalogu, 

x - execute - można czytać metadane plików w katalogu, można przeczytać zawartość pliku lub przejść do podkatalogu pod warunkiem, że znamy nazwę.

Dzielimy na 3 grupy: user, grupa i others, każda z tych grup ma te 3 typy uprawnień, co wygląda tak: `rwxrwxrwx`.

`set-gid` sprawia, że wszystkie nowo tworzone pliki i katalogi stają się własnością grupy będącej właścicielem katalogu, ten atrybut jest dziedziczony.

`sticky` - kiedy katalog ma ten bit ustawiony, jego pliki mogą być usuwane lub ich nazwy mogą być zmieniane jedynie przez właściciela pliku, katalogu i roota.

```c
#define MAX_GROUPS_NUMBER 1024

bool my_access(struct stat *sb, int mode) {
    // Jeżeli effective user ID to 0, mamy do czynienia
    // z superuserem i przyznajemy od razu dostęp.
    if (geteuid() == 0)
        return true;

    // Jeżeli effective user ID jest takie samo jak ID
    // właściciela procesu, to dostęp jest przyznany jeśli
    // odpowiedni bit dostępu użytkownika jest ustawiony,
    // w przeciwnym wypadku dostęp nie jest przyznawany.
    // Odpowiedni bit oznacza, że jeśli proces otwiera plik
    // do czytania, to user-read musi być ustawiony, podobnie
    // dla write (user-write) i uruchamiania (user-execute).
    if (getuid() == geteuid()) {
        // Porównaj wszystkie flagi, jeśli (mode >= sb) to przyznaj
        // dostęp, w przeciwnym wypadku sprawdzaj dalej warunki.
        int sb_mode = sb->st_mode;

        uint8_t sb_u_read  = (sb_mode & S_IRUSR);
        uint8_t sb_u_write = (sb_mode & S_IWUSR);
        uint8_t sb_u_exec  = (sb_mode & S_IXUSR);

        uint8_t md_u_read  = (mode & R_OK);
        uint8_t md_u_write = (mode & W_OK);
        uint8_t md_u_exec  = (mode & X_OK);

        bool access_flags[3] = {false, false, false};
        // Oznaczenie x <= y w tym wypadku oznacza tyle, że y ma
        // takie same lub większe uprawnienia (np. x nie wymaga
        // uprawnienia czytania, ale y je posiada, więc dostęp
        // w takim przypadku też zostanie przyznany).
        if (sb_u_read  <= md_u_read)  access_flags[0] = true;
        if (sb_u_write <= md_u_write) access_flags[1] = true;
        if (sb_u_exec  <= md_u_exec)  access_flags[2] = true;

        if (access_flags[0] && access_flags[1] && access_flags[2])
            return true;
        else 
            return false;
    }

    // Sprawdzenie, czy jedno z effective group ID lub supplementary
    // group ID jest równe group ID pliku, jeżeli tak, to dostęp
    // jest przyznawany, w przeciwnym przypadku odrzucany.
    gid_t sb_gid = sb->st_gid;
    gid_t *group;
    group = (gid_t *)malloc(MAX_GROUPS_NUMBER * sizeof(gid_t));
    int groups = getgroups(MAX_GROUPS_NUMBER, group);

    for (int i = 0; i < groups; i++)
        if (sb_gid == group[i])
            return true;

    // Jeśli odpowiedni bit dostępu jest ustawiony dla other,
    // dostęp jest przyznany, w przeciwnym wypadku nie. Proces
    // sprawdzania bardzo podobny do tego, co w przypadku drugiego if'a.

    return false; // jak nie przejdą żadne testy, to nie ma dostępu
}
```

## Zad. 3

Proces uruchamia su z set-uid ustawionym, czyli na początku wykonania programu proces przyjmie efektywną tożsamość użytkownika właściciela pliku programu, czyli roota (euid=0). Dlatego, mimo że przed wykonaniem `euid` wynosiło 1000, po uruchomieniu wynosiło 0, bo kontrolę przejął root. `ruid` tymczasem pozostaje bez zmian (czyli równy 0).

```c
/* su.c - switch user
 *
 * Copyright 2013 CE Strake <strake888@gmail.com>
 *
 * See http://refspecs.linuxfoundation.org/LSB_4.1.0/LSB-Core-generic/LSB-Core-generic/su.html
 * TODO: log su attempts
 * TODO: suid support
 * Supports undocumented compatibility options: -m synonym for -p, - for -l

USE_SU(NEWTOY(su, "^lmpu:g:c:s:[!lmp]", TOYFLAG_BIN|TOYFLAG_ROOTONLY))

config SU
  bool "su"
  default y
  depends on TOYBOX_SHADOW
  help
    usage: su [-lp] [-u UID] [-g GID,...] [-s SHELL] [-c CMD] [USER [COMMAND...]]

    Switch user, prompting for password of new user when not run as root.

    With one argument, switch to USER and run user's shell from /etc/passwd.
    With no arguments, USER is root. If COMMAND line provided after USER,
    exec() it as new USER (bypassing shell). If -u or -g specified, first
    argument (if any) isn't USER (it's COMMAND).

    first argument is USER name to switch to (which must exist).
    Non-root users are prompted for new user's password.

    -s	Shell to use (default is user's shell from /etc/passwd)
    -c	Command line to pass to -s shell (ala sh -c "CMD")
    -l	Reset environment as if new login.
    -u	Switch to UID instead of USER
    -g	Switch to GID (only root allowed, can be comma separated list)
    -p	Preserve environment (except for $PATH and $IFS)
*/

#define FOR_su

// #include "toys.h"

// Wstawiam zamienniki:

#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <termios.h>
#include <signal.h>

#define GLOBALS(x) \
    struct         \
    {              \
        x          \
    } TT;
#define LOG_NOTICE 1
#define FLAG(x) 1
#define FLAG_l 1
#define _PATH_DEFPATH "/"
struct
{
    int optc;
    char *optargs;
    int optflags;
    int exitval;
} toys;
char toybuf[1024];
char m, p, l;

struct passwd
{
    char *pw_name;
    int pw_uid;
    int pw_gid;
    // powłoka użytkownika
    char *pw_shell;
};

struct spwd
{
    // skrót kryptograficzny hasła
    char *sp_pwdp;
};

void generic_signal(int signo)
{
    (void)signo;
}

// Koniec

// Kopia z innych plików

void xsetuser(struct passwd *pwd)
{
    if (initgroups(pwd->pw_name, pwd->pw_gid) || setgid(pwd->pw_uid) || setuid(pwd->pw_uid))
        perror_exit("xsetuser '%s'", pwd->pw_name);
}

struct passwd *xgetpwnam(char *name)
{
    struct passwd *up = getpwnam(name);

    if (!up)
        perror_exit("user '%s'", name);
    return up;
}

int read_password(char *buf, int buflen, char *mesg)
{
    struct termios oldtermio;
    struct sigaction sa, oldsa;
    // tty_fd sprawdza fd0, fd1, fd2, /dev/tty
    int i, tty = tty_fd(), ret = 1;

    // NOP signal handler to return from the read. Use sigaction() instead
    // of xsignal() because we want to restore the old handler afterwards.
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = generic_signal;
    sigaction(SIGINT, &sa, &oldsa);

    // Usuwamy niewczytane jeszcze bajty.
    tcflush(tty, TCIFLUSH);
    // Ustawiamy raw mode przez cfmakeraw(3). https://linux.die.net/man/3/cfmakeraw
    xset_terminal(tty, 1, 0, &oldtermio);
    dprintf(tty, "%s", mesg);

    for (i = 0; i < buflen - 1; i++)
    {
        // 4 - EOT End Of Transmission (Ctrl+D)
        // 3 - ETX End Of Text
        // Ctrl+D przerywa tylko, gdy jest w pustej linii (ale czemu w przeciwnym
        // wypadku bierzemy go jako fragment hasła?).
        if ((ret = read(tty, buf + i, 1)) < 0 || (!ret && !i) || *buf == 4 || buf[i] == 3)
        {
            i = 0;
            ret = 1;

            break;
        }
        else if (!ret || buf[i] == '\n' || buf[i] == '\r')
        {
            ret = 0;

            break;
        }
        // 8 - Backspace
        // 127 - Delete
        else if (buf[i] == 8 || buf[i] == 127)
            // Usuwamy 1 (samo Backspace/Delete), lub 2 znaki.
            i -= 2 - !i;
    }

    // Restore terminal/signal state, terminate string
    sigaction(SIGINT, &oldsa, 0);
    tcsetattr(0, TCSANOW, &oldtermio);
    buf[i] = 0;
    xputc('\n');

    return ret;
}

// Koniec

GLOBALS(
    char *s;
    char *c;)

void su_main()
{
    char *name, *passhash = 0, **argu, **argv;
    struct passwd *up;
    struct spwd *shp;

    // Użytkownik może poprosić o login shell przez -.
    // Np. `su - pzmarzly` wykona (`sh -l` jako pzmarzly).
    if (*toys.optargs && !strcmp("-", *toys.optargs))
    {
        toys.optflags |= FLAG_l;
        toys.optargs++;
    }

    // Pobieranie nazwy użytkownika.
    if (*toys.optargs)
        name = *(toys.optargs++);
    else
        name = "root";

    loggit(LOG_NOTICE, "%s->%s", getusername(getuid()), name);

    // Szukamy wpisu w /etc/shadow.
    if (!(shp = getspnam(name)))
        // Nie ma wpisu.
        perror_exit("no '%s'", name);
    if (getuid())
    {
        if (*shp->sp_pwdp != '$')
            // Hash hasła zwracanego przez crypt zaczyna się na $.
            // Puste sp_pwdp - login bez hasła (nieobsługiwane przez tę wersję)
            // !, !!, * - niedozwolony login. https://unix.stackexchange.com/questions/252016
            goto deny;
        if (read_password(toybuf, sizeof(toybuf), "Password: "))
            // Użytkownik anulował akcję, lub nie da się pobrać wejścia.
            goto deny;
        // Obliczamy skrót (zmodyfikowany DES).
        passhash = crypt(toybuf, shp->sp_pwdp);
        // Czyścimy bufor z czystym tekstem. Niekoniecznie dobrze.
        // Użyj memset_s. https://en.cppreference.com/w/c/string/byte/memset
        memset(toybuf, 0, sizeof(toybuf));
        if (!passhash || strcmp(passhash, shp->sp_pwdp))
            // Błędne hasło.
            goto deny;
    }
    // Zamykamy deskryptory plików.
    closelog();

    // Szukamy wpisu w /etc/passwd.
    xsetuser(up = xgetpwnam(name));

    if (FLAG(m) || FLAG(p))
    {
        // Pozostaw środowisko, poza nieintuicyjnym IFS i groźnym PATH.
        // Choć równie groźne jest np. PYTHONSTARTUP.
        unsetenv("IFS");
        setenv("PATH", _PATH_DEFPATH, 1);
    }
    else
        // Domyślne środowisko.
        reset_env(up, FLAG(l));

    argv = argu = xmalloc(sizeof(char *) * (toys.optc + 4));
    *(argv++) = TT.s ? TT.s : up->pw_shell;
    loggit(LOG_NOTICE, "run %s", *argu);

    // Przygotowujemy flagi dla sh.
    if (FLAG(l))
        *(argv++) = "-l";
    if (FLAG(c))
    {
        *(argv++) = "-c";
        *(argv++) = TT.c;
    }
    while ((*(argv++) = *(toys.optargs++)))
        ;
    xexec(argu);

deny:
    syslog(LOG_NOTICE, "No.");
    puts("No.");
    toys.exitval = 1;
}
```

## Zad. 4

Projektowanie programów powinno opierać się na ich tworzeniu w taki sposób, ponieważ wtedy są bezpieczniejsze. Można ich uprawnienia zwiększać do konkretnych operacji, a potem przywracać program w domyślny tryb (bez zbędnych uprawnień).

Czemu standardowy zestaw funkcji jest niewystarczający? 
39.1 Kerrisk: "If we want to allow a process
to perform some operation that is permitted only to the superuser—for example,
changing the system time—then we must run that process with an effective user ID
of 0. (If an unprivileged user needs to perform such operations, this is typically
implemented using a set-user-ID-root program.) However, this grants the process
privileges to perform a host of other actions as well—for example, bypassing all per-
mission checks when accessing files—thus opening the door for a range of security
breaches if the program behaves in unexpected ways (which may be the conse-
quence of unforeseen circumstances, or because of deliberate manipulation by a
malicious user)."

Jak zdolności to naprawiają? "The Linux capability scheme refines the handling of this problem. Rather than
using a single privilege (i.e., effective user ID of 0) when performing security
checks in the kernel, the superuser privilege is divided into distinct units, called
capabilities. Each privileged operation is associated with a particular capability, and
a process can perform that operation only if it has the corresponding capability
(regardless of its effective user ID) 

``CAP_DAC_READ_SEARCH`` nie sprawdza ustawienia flagi `read` dla plików oraz flag `read` i `execute` dla katalogów,

`CAP_KILL` nie sprawdza uprawnień do wysyłania sygnałów.

Aby proces użytkownika wysłał sygnał do innego procesu, powinien być uprzywilejowany.

## Zad. 5

`exit` służy do zakończenia programu, najpierw opróżnia bufory wszystkich strumieni stdio (przez automatyczne wywołanie fflush), wywołuje funkcje zarejestrowane przez `atexit()` i kończy proces zwracając wartość statusu.

Problemy z buforowaniem plików w strumieniach stdio:
- w przypadku `fork` proces potomny dziedziczy kopię buforów, co może spowodować problem duplikacji danych w plikach lub utraty danych zapisanych tylko w buforach przy `exit`/

Rozwiązanie problemów:
- fflush przed fork, co opróżni bufory,
- `exit(3)` zamiast `_exit(2)` w kodzie potomka, żeby zapewnić opróżnienie,
- ustawienie buforowania na tryb niebuforowany dla strumieni

Domyślne strategie buforowania:
1. Plik terminala - tryb wierszowy, bufor opróżniany przy każdym nowym wierszu,
2. Plik zwykły - tryb pełny, bufor jest opróżniany dopiero po jego zapełnieniu,
3. Standardowe wyjście błędów - tryb niebuforowany - każda operacja zapisu jest natychmiastowa.

```c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t stop_requested = 0;

void sigint_handler(int signum) {
    stop_requested = 1;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Główna pętla programu
    while (!stop_requested) {
        // Kod programu
    }

    // Opróżnianie buforów i zakończenie programu
    fflush(NULL);  // Opróżnia wszystkie otwarte strumienie stdio
    exit(EXIT_SUCCESS);
}
```

