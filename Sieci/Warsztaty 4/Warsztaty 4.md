## Konfiguracja początkowa

![alt text](image.png)

V1:
```
sudo ip link set enp0s3 name enp-rem1 & sudo ip link set enp0s8 name enp-rem4 & sudo ip link set enp0s9 name enp-all
sudo ip link set up dev enp-rem1 & sudo ip link set up dev enp-rem4
sudo ip addr add 192.168.1.1/24 dev enp-rem1 & sudo ip addr add 192.168.4.1/24 dev enp-rem4
```

V2:
```
sudo ip link set enp0s3 name enp-rem1 & sudo ip link set enp0s8 name enp-rem2 & sudo ip link set enp0s9 name enp-all
sudo ip link set up dev enp-rem1 & sudo ip link set up dev enp-rem2
sudo ip addr add 192.168.1.2/24 dev enp-rem1 & sudo ip addr add 192.168.2.2/24 dev enp-rem2
```

V3:
```
sudo ip link set enp0s3 name enp-rem2 & sudo ip link set enp0s8 name enp-rem3 & sudo ip link set enp0s9 name enp-all
sudo ip link set up dev enp-rem2 & sudo ip link set up dev enp-rem3
sudo ip addr add 192.168.2.3/24 dev enp-rem2 & sudo ip addr add 192.168.3.3/24 dev enp-rem3
```

V4:
```
sudo ip link set enp0s3 name enp-rem3 & sudo ip link set enp0s8 name enp-rem4 & sudo ip link set enp0s9 name enp-all
sudo ip link set up dev enp-rem3 & sudo ip link set up dev enp-rem4
sudo ip addr add 192.168.3.4/24 dev enp-rem3 & sudo ip addr add 192.168.4.4/24 dev enp-rem4
```

![alt text](image-1.png)

## Tutorial 1

![alt text](image-2.png)

```
V1: sudo ip route add default via 192.168.1.2
V2: sudo ip route add default via 192.168.2.3
V3: sudo ip route add default via 192.168.3.4
V4: sudo ip route add default via 192.168.4.1
```

W tym przypadku jest cykl, bo pingujemy maszynę niepołączoną bezpośrednio:

![alt text](image-3.png)

W tym nie, bo jesteśmy bezpośrednio połączeni:

![alt text](image-4.png)

Po `ping 192.168.3.4` z V1:

![alt text](image-5.png)

## Tutorial 2

![alt text](image-6.png)

```
sudo nano /etc/frr/daemons
sudo systemctl start frr
sudo vtysh
show ip route
```

![alt text](image-7.png)

```
configure terminal
router ospf
network 192.168.x.0/24 area 0
end
show running-config
copy running-config startup-config
```

![alt text](image-8.png)

Po puszczeniu `sudo ip route` dla wszystkich maszyn:

![alt text](image-9.png)

![alt text](image-10.png)

```
sudo ip link set up dev enp-all
sudo ip addr add 172.16.16.x dev enp-all
ip addr
```

![alt text](image-11.png)

Trasy w `frr`:

![alt text](image-12.png)

Trasy w `ip`:

![alt text](image-13.png)

Mamy ścieżkę 300 po komendach:

```
V1: 
sudo ip link set down dev enp-all
sudo ip link set down dev enp-rem4 (tyle starczy do 300)
V2:
sudo ip link set down dev enp-rem2
V3: 
sudo ip link set down dev enp-rem2
V4:
sudo ip link set down dev enp-all
```

![alt text](image-14.png)

I długości 4:

![alt text](image-15.png)

## Wyzwanie

![alt text](image-16.png)

V0:
```
sudo ip link set enp0s3 name enp-ext
sudo ip link set enp0s8 name enp-loc1
sudo ip link set enp0s9 name enp-add1
sudo dhclient enp-ext
sudo ip link set up dev enp-loc1
sudo ip addr add 172.18.0.1/16 dev enp-loc1
sudo ip link set up dev enp-add1
sudo ip addr add 192.168.0.1/24 dev enp-add1
```

V1:
```
sudo ip link set enp0s3 name enp-loc1
sudo ip link set up dev enp-loc1
sudo ip addr add 172.18.0.2/16 dev enp-loc1
sudo ip route add default via 172.18.0.1
```

V2:
```
sudo ip link set enp0s3 name enp-add1
sudo ip link set up dev enp-add1
sudo ip addr add 192.168.0.2/24 dev enp-loc1
```

![alt text](image-17.png)
