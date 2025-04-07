## Zad. 1

S.M.A.R.T - kryteria oceny wymagań:
- szczegółowy (simple - S),
- mierzalny (measurable - M),
- osiągalny (achievable - A), 
- istotny/realistyczny (relevant - R),
- terminowy (time-specific - T)

Analiza wymagań wg FURPS:

1. Funkcjonalność (F):
    - **Wymaganie** - system powinien umożliwiać generowanie raportów finansowych zgodnych z aktualnymi przepisami.
    - **Ocena SMART** - jest szczegółowy, istotny i osiągalny, ale za mało mierzalny i nie ma czasu realizacji.
    - **Pytanie** - jakie konkretnie raporty mają być generowane przez system, czy istnieją jakieś standardowe wzory?
    - **Wymaganie** - system musi wspierać procesy kadrowe, w tym zarządzanie urlopami i ewidencję czasu pracy.
    - **Ocena SMART** - jak powyżej.
    - **Pytanie** - jakie są szczegółowe zasady zarządzania tymi aspektami?
2. Użyteczność (U):
    - **Wymaganie** - interfejs użytkownika powinien być intuicyjny i jasny w obsłudze.
    - **Ocena SMART** - wymaganie jest istotne, osiągalne, ale nie jest mierzalne ani specyficzne.
    - **Pytanie** - czy istnieją wytyczne dot. jasności/intuicyjności, czy interfejs będzie testowany?
    - **Wymaganie** - system powinien umożliwiać personalizację widoków dla różnych ról użytkowników.
    - **Ocena SMART** - brak mierzalnych kryteriów oraz terminu realizacji.
    - **Pytanie** - jakie role użytkowników są brane pod uwagę, czy różne widoki spełniają ich potrzeby?
3. Niezawodność (R):
    - **Wymaganie** - system powinien być dostępny przez 99,5% czasu w skali miesiąca.
    - **Ocena SMART** - wszystko spełnione.
    - **Pytanie** - w jakich godzinach nie będzie on dostępny, czy będzie o tym informacja, czy będą to stałe godziny?
    - **Wymaganie** - czas przywracania systemu po awarii nie powinien przekroczyć 4h.
    - **Ocena SMART** - jak powyżej.
    - **Pytanie** - czy istnieje plan awaryjny, gdyby to się nie udało, jak powiadomić wszystkich o awarii?
4. Wydajność (P):
    - **Wymaganie** - czas odpowiedzi systemu na zapytanie nie powinien przekroczyć 2 sek.
    - **Ocena SMART** - wszystkie kryteria spełnione.
    - **Pytanie** - czy przy dużej liczbie zapytań naraz wymaganie to dalej będzie spełnione?
5. Dostosowanie (S):
    - **Wymaganie** - system powinien umożliwiać administratorowi monitorowanie wydajności i błędów w czasie rzeczywistym.
    **Ocena SMART** - szczegółowe i istotne, ale nie określono jakie parametry będą brane pod uwagę, więc trudno to zmierzyć i powiedzieć, czy będzie osiągalne w konkretnym czasie.
    - **Pytanie** - jakie wskaźniki wydajności i błędów będą wzięte pod uwagę?

## Zad. 2

Dokumentacja pełna dokonania zakupu w sklepie internetowym:

1. Nazwa: zakup towaru
2. Aktor: 
    - główny: klient
    - drugoplanowy: system płatności i magazynu
3. Krótki opis: proces zakupu towaru przez użytkownika od wyboru towaru do potwierdzenia zakupu
4. Warunki wstępne: klient posiada konto w sklepie oraz konto bankowe, z którego dokona płatności
5. Warunki końcowe:
    - sukces - złożenie zamówienia, akceptacja płatności, klient dostaje potwierdzenie
    - porażka - błąd płatności lub dostępności towaru, klient dostaje informację
6. Scenariusz główny:
    - klient dodaje towar do koszyka,
    - klient przechodzi do kasy, uzupełnia konieczne dane (adres, mail, nr telefonu), 
    - klient wybiera metodę płatności i dostawy,
    - klient jest przekierowany na stronę banku, dokonuje płatności,
    - system przetwarza płatność, wysyła potwierdzenie i przekazuje zamówienie do realizacji
7. Scenariusz alternatywny:
    - po dodaniu do koszyka i sprawdzeniu dostępności okazuje się, że towar nie jest dostępny,
    - klient otrzymuje informację o braku towaru w magazynie,
    - klient musi usunąć towar z koszyka, ewentualnie poprosić o powiadomienie, gdy będzie dostępny
8. 2 scenariusz alternatywny:
    - po przekierowaniu na stronę banku i dokonaniu płatności, okazuje się, że zakończyła się ona niepowodzeniem (brak środków, awaria),
    - klient otrzymuje adekwatną informację,
    - klient może ponowić płatność lub zmienić metodę płatności

## Zad. 3

Model pojęciowy zakupów w sklepie internetowym:
1. **Klient** - osoba dokonująca zakupów w sklepie internetowym.
    - Atrybuty: ID, imię, nazwisko, nr telefonu, e-mail, adres
    - Powiązania: może składać wiele zamówień
2. **Zamówienie** - proces zakupu produktów przez klienta w wyniku jednej płatności.
    - Atrybuty: ID, data, status, kwota
    - Powiązania: jeden klient, wiele produktów
3. **Produkt** - przedmiot sprzedawany w sklepie internetowym
    - Atrybuty: ID, nazwa, opis, cena, ilość
    - Powiązania: może wchodzić w skład wielu zamówień
4. **Koszyk** - aktualny zbiór produktów, który klient chce zamówić
    - Atrybuty: ID, ID klienta, data utworzenia,
    - Powiązania: wiele produktów, jeden klient
5. **Płatność** - proces finalizacji transakcji
    - Atrybuty: ID, metoda, status, kwota
    - Powiązania: za jedno zamówienie