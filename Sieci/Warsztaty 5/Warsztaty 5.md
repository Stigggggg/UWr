## Konfiguracja + Tutorial 1

![alt text](image.png)

Komendy do setupu:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo dhclient enp0
```

![alt text](image-1.png)

Co widzimy? Że zostały wysłane DHCP offer, discover, request i ACK. Źródłowy adres IP to 0.0.0.0, bo nie ma jeszcze przydzielonego.

![alt text](image-3.png)

Dezaktywacja:
```
sudo dhclient -r enp0
```

![alt text](image-2.png)

## Tutorial 2

![alt text](image-4.png)

Setup:
```
sudo ip link set enp0s3 name enp0
sudo ip link set up dev enp0
sudo ip addr add 192.168.0.1/24 dev enp0 (V1)
sudo ip addr add 192.168.0.2/24 dev enp0 (V2)
```

Po `ping 192.168.0.2`:

![alt text](image-5.png)

Po `ping -b 192.168.0.255` z V1:

![alt text](image-6.png)

Po zabawie z `ip neigh`:

![alt text](image-7.png)

Odpowiedzi na pytania:
- stan tablicy ARP w V1 zmienił się ze STALE na REACHABLE, w V2 nie zmienił się, dalej był STALE,
- przekształcone adresy IP na MAC w sieci lokalnej,
- zapytania są wysyłane na adres rozgłoszeniowy, widać na screenie,
- odpowiedzi są wysyłane na adres komputera, również na screenie

## Tutorial 3

![alt text](image-9.png)

```
sudo ip addr del 192.168.0.2/24 dev enp0 && sudo ip addr add 192.168.0.123/24 dev enp0
```

![alt text](image-10.png)

Usuwanie adresów:
```
sudo ip addr flush dev enp0
```

## Wyzwanie

![alt text](image-11.png)

V1:
```
sudo ip addr add 192.168.1.1/24 dev enp0
```

V2:
```
sudo ip addr add 192.168.1.2/24 dev enp0
```

V3:
```
sudo ip link set enp0s3 name enp0
sudo ip link set enp0s8 name enp1
sudo ip link set up dev enp0     
sudo ip link set up dev enp1
sudo ip addr add 192.168.1.3/24 dev enp0
sudo ip addr add 192.168.2.1/24 dev enp1
```

V4:
```
sudo ip link set enp0s3 name enp-out 
sudo ip link set up dev enp-out      
sudo ip addr add 192.168.2.1/24 dev enp-out
```

![alt text](image-12.png)

Trasy:
```
sudo ip route add default via 192.168.1.2 (V1)
sudo ip route add default via 192.168.1.3 (V2)
sudo ip route add default via 192.168.2.1 (V4)
```

![alt text](image-13.png)

Pytania:
- sugerowana modyfikacja to zmiana default na 192.168.1.3,
- ma to sens, bo skracamy ścieżkę,
- wykrywa problem, bo wie, że oba są w tej samej sieci, więc mogą się komunikować bezpośrednio


