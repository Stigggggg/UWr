## Zad. 3

- **hyperlink**: po stronie klienta, po kliknięciu linku przez użytkownika, przeglądarka wysyła nowe żądanie GET do serwera, adres w pasku się zmienia, nie można tak przesłać danych,
- **POST między stronami**: po stronie klienta, dane są wysyłane metodą POST, w `body` można wysłać dużo danych, których nie widać w URL,
- **redirect** - po stronie serwera, ale wywołuje GET, mamy dwa żądania tak naprawdę, serwer wysyła 302 (znaleziono), a przeglądarka wysyła nowe żądanie GET,
- **transfer** - po stronie serwera, wewnętrzne przekazanie wykonania, URL w przeglądarce się nie zmienia