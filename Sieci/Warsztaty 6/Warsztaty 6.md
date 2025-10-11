## Tutorial 1

![alt text](image-1.png)

Po `host -a www.debian.org` mamy:

![alt text](image.png)

Bierzemy 130.89.148.77.

Po komendach:
```
(while true; do netstat -tan | grep 130.89.148.77; done) | tee tcp_log
trickle -d 10 wget http://130.89.148.77/
```

Dostaliśmy:

![alt text](image-2.png)

Po odpaleniu wiresharka:

![alt text](image-3.png)

Co tu się dzieje:
- klient wysyła SYN,
- dostaje SYN, ACK,
- odpowiada ACK,
- nawiązuje się połączenie,
- wysyła żądanie get pod wskazane IP, żeby pobrać stronę,
- odpowiedź serwera ACK, że otrzymał GET,
- otrzymanie strony w HTML,
- wysłanie serwerowi potwierdzenia otrzymania strony,
- klient wysyła FIN, ACK,
- serwer odpowiada ACK,
- a potem ACK FIN,
- klient przechodzi w TIME_WAIT, wysyła ACK

W tcp_log są widoczne stany SYN_SENT, ESTABLISHED, FIN_WAIT2 i TIME_WAIT. To klient wykonuje otwarcie aktywne i zamknięcie aktywne, bo pierwszy wysyła segmenty do serwera.

![alt text](image-12.png)

## Tutorial 2

![alt text](image-4.png)

Po `dig www.cs.uni.wroc.pl @198.41.0.4` mamy:

![alt text](image-5.png)

Teraz `dig www.cs.uni.wroc.pl @194.0.25.29`:

![alt text](image-6.png)

`dig www.cs.uni.wroc.pl @156.17.254.3`:

![alt text](image-7.png)

`dig www.cs.uni.wroc.pl @156.17.87.193`:

![alt text](image-8.png)

`dig www.cs.uni.wroc.pl @156.17.4.1`:

![alt text](image-9.png)

Czyli dokopaliśmy się do www.cs.uni.wroc.pl.

Po `dig +trace -4 www.cs.uni.wroc.pl @198.41.0.4` jest podobnie, tylko wybierał inne adresy, ale również trafił do celu:

![alt text](image-10.png)

Wireshark:

![alt text](image-11.png)

Dalsze komendy:
```
dig -t a ii.uni.wroc.pl
dig -t ns ii.uni.wroc.pl
dig -t mx ii.uni.wroc.pl
dig -t ptr 11.4.17.156.in-addr.arpa
```

Wyniki 2 pierwszych:

![alt text](image-13.png)

Wyniki pozostałych:

![alt text](image-14.png)

## Tutorial 3

![alt text](image-15.png)

Komendy:
```
nc -u -l -p 10053 | tee dns_request
dig -p 10053 www.wikipedia.pl @127.0.0.1 +tries=1
hexdump -C dns_request 
nc -q 1 -u 8.8.8.8 53 < dns_request
```

![alt text](image-16.png)

## Wyzwanie 1

![alt text](image-17.png)

![alt text](image-19.png)

Po wielowierszowym zapytaniu:

![alt text](image-20.png)

Po zmianach w connection settings:

![alt text](image-21.png)

Nie ma response, bo serwer proxy jest nieznany.

Co zostało zapisane do http_request?

![alt text](image-22.png)

Wszystkie komunikaty są:

![alt text](image-23.png)