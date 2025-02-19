# Tożsamość

**Tożsamość** - mają ją procesy tego użytkownika, który je otworzył. W bloku kontrolnym procesu jądro trzyma **kredencjały**. Potwierdzamy ją za pomocą mechanizmu uwierzytelniania, np. podanie hasła.

**Upoważnienie** - proces sprawdzania, czy proces o danej tożsamości ma dostęp do zasobu.  

Tożsamość procesu uniksowego:
- użytkownik - `getuid`,
- grupa podstawowa - `getgid`,
- grupy rozszerzone - `getgroups`

Jądro przechowuje identyfikatory w postaci numerycznej, root (uid == 0) jest uprzywilejowany.

Jądro utrzymuje trzy identyfikatory użytkownika:
- rzeczywisty (real id),
- obowiązujący (effective id),
- zachowany (saved set-user id)

W trakcie sprawdzania uprawnień brany jest pod uwagę tylko effective id, przy pomocy `setuid` i `setgid` użytkownik:
- root - zmienia wszystkie 3 identyfikatory na dowolny,
- inni - effective id może być ustawione na real albo saved

Bity uprawnień:
- R - można czytać wyłącznie zawartość pliku katalogu,
- W - można modyfikować zawartość pliku katalogu,
- X - można czytać metadane plików w katalogu,
- sticky - plik może usunąć tylko jego właściciel

Przykład jednej funkcji z ćwiczeń (inne podobne):
```c
int setreuid(uid_t ruid, uid_t euid)
```
Ustawia real i effective user id zgodnie z argumentami, jeśli któreś z nich == -1, to aktualne uid jest tam wstawiane. Nieuprzywilejowani użytkownicy mogą zmienić ruid na euid i na odwrót, tylko superuser może robić inne rzeczy. Jeśli ruid != -1 albo euid się od niego różni to saved id będzie ustawione na euid. Zwraca 0 jak git, -1 jak error.