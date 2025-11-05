**Application** - zakres globalny, współdzielony między wszystkimi użytkownikami i sesjami, przechowuje dane wspólne dla całej aplikacji, ma dostęp współbieżny.

**Session** - każdy użytkownik ma własną sesję, służy do przechowywania stanu użytkownika między żądaniami, nie wymaga synchronizacji, bo nie jest współdzielona.

**Items** - tylko w obrębie pojedynczego żądania HTTP, służy do przekazywania danych między komponentami w ramach jednego żądania, nie wymaga synchronizacji, bo jest lokalne.

Application wymaga locka na get

Items działa jak zmienne lokalne, więc nie musi być w interfejsie


