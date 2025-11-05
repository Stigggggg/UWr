app_offline.htm służy do tymczasowego wyłączenia aplikacji ASP.NET.

Jeśli w katalogu głównym aplikacji (tam gdzie web.config) pojawi się plik app_offline.htm, ASP.NET automatycznie zatrzymuje działanie aplikacji.

Każde żądanie HTTP kierowane do aplikacji nie jest obsługiwane przez normalne strony ASPX czy MVC, tylko serwer zwraca zawartość tego pliku jako statyczną stronę HTML.

Dzięki temu użytkownicy widzą komunikat „aplikacja niedostępna” zamiast błędów serwera.