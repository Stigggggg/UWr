## Timer1

16-bitowy licznik w AVR, który może być skonfigurowany do pracy w różnych trybach (PWM, CTC, normal itd.). Do sterowania nim używa się rejestrów **TCCR1A**, **TCCR1B** i **TCCR1C**. 

- TCCR1A - ustawia tryb PWM (dolne bity trybu) oraz sposób działania wyjść OC1A/OC1B,
- TCCR1B - ustawia tryb pracy licznika (górne bity trybu), źródło zegara (preskaler), tryb CTC/Input Capture

### TCCR1B
- WGM13:12 - Waveform Generation Mode, razem z WGM11:10 z TCCR1A określa tryb pracy timera,
- CS12:10 - określa źródło zegara i jego podział (preskaler), 
- ICES1, ICNC1 - pomiary czasu na pinie ICP1, nieużywane przy PWM

### TCCR1A
- COM1A1:0, COM1B1:0 - steruje zachowaniem pinów OC1A (PB1) i OC1B (PB2), np. włączenie PWM, inverting/non-inverting,
- WGM11:10 - część ustawienia trybu pracy timera (razem z bitami TCCR1B)

Z **TCCR1A** korzystamy, gdy chcemy włączyć PWM lub zmienić sposób działania wyjść, z **TCCR1B**, gdy chcemy ustawić częstotliwość PWM, taktowanie, tryb licznika. 

## Timer0

8-bitowy licznik w AVR, ma dwa wyjścia PWM: OC0A i OC0B, typowo używany do sterowanie diodami LED, małymi sygnałami PWM, timera systemowego, przez to że mniej bitów, ma mniejszą rozdzielczość PWM. Również ma 2 liczniki: TCCR0A i TCCR0B, których bity działają podobnie jak w Timer1.

## Kiedy jaki tryb?
- **Normal** - liczniki, pomiar czasu, przerwania co overflow,
- **CTC** - generowanie precyzyjnych przerwań lub sygnału prostokątnego,
- **Fast PWM** - LED, silniki, nie migocze,
- **Phase Correct PWM** - minimalizuje zakłócenia dla silników lub audio,
- **Fast PWM z TOP=ICRx/OCRx** - PWM z regulowaną częstotliwością, RGB LED, silniki, modulacja częstotliwości

### OCR vs. ICR
- **OCR** - output compare register, określa wartość przy której licznik timera porównuje się z rejestrem, aby sterować pinem wyjściowym, np. w trybie PWM ustala duty cycle (wypełnienie %) sygnału PWM,
- **ICR** - input capture register, w trubach PWM z regulowanym TOP ICR1 określa maksymalną wartość licznika, dzięki temu możemy ustawiać częstotliwość PWM niezależnie od wypełnienia.

## Przerwania sprzętowe

Przerwanie zatrzymuje standardowy flow programu przy zachowaniu wszystkich zmiennych i wywołuje **interrupt service routine (ISR)**. Po wykonaniu ISR program zaczyna działanie od następnej instrukcji po tej, na której się zatrzymał. 

- **internal interrupts** - odpowiadają na wewnętrzne przerwania sprzętowe, np. puszczają kod ISR gdy licznik osiągnął konkretną wartość lub USART dostał nowe dane,
- **external interrupts** - reagują na zmianę napięcia dowolnego z pinów AVR, na nich się skupimy. 

Mamy 2 mechanizmy: **INT0** i **INT1**. 
- **INT0** - połączony z PD2, ma bardziej wszechstronne możliwości, pozwala triggerować przerwanie na wzroście, spadku napięcia, na low-voltage level.
- **INT1** - połączony z PD3, działa podobnie jak INT0

**ISR** - funkcja, która jest wywoływana automatycznie, gdy zajdzie dane przerwanie, kod powinien być krótki i szybki, żeby nie blokować innych przerwań, przykład w AVR C:
```
ISR(INT0_vect) {
    // kod, który ma wykonać się po wystąpieniu INT0
}
```

### Konfiguracja
- **EIMSK** - włącza przerwanie, np. `EIMSK |= _BV(INT0);` włącza INT0,
- **EICRA** - wybór trybu wyzwalania przerwania, np. `EICRA |= _BV(ISC01) | _BV(ISC00);` wyzwala na narastającym zboczu, możliwe tryby:
    - poziom niski (ISC01=0, ISC00=0) - przerwanie wywoła się, gdy pin jest w stanie 0,
    - zmiana stanu (ISC01=0, ISC00=1) - przerwanie wywoła się na każde przejście z 0->1 albo 1->0, oba zbocza,
    - zbocze opadające (ISC01=1, ISC00=0) - wywoła się tylko na 1->0,
    - zbocze narastające (oba na 1), wywoła się na 0->1.

Analogicznie dla INT1 działają bity ISC11 i ISC10. Ważna jest też funkcja `sei()` i `cli()`, pierwsza włącza, druga wyłącza globalnie przerwania, `sei` musi być użyta, bo nawet jak ustawimy INT0/INT1/EIMSK, to nie zadziała bo mikrokontroler ignoruje przerwania. 

## SPI

**SPI** to 4-przewodowa magistrala, która działa w architekturze **master-slave**:
- MOSI - master out slave in, dane wysyłane z mastera do slave,
- MISO - dane wysyłane ze slave do mastera,
- SCK - master->slave, zegar synchronizujący transmisję,
- SS - slave select - wybór konkretnego urządzenia slave

Master generuje zegar SCK, na każdym takcie przesyłany jest jeden bit MOSI i MISO jednocześnie, gdy master chce rozmawiać z urządzeniem, to ściąga jego SS do 0, slave wtedy zaczyna transmisję. 

W AVR SPI jest obsługiwane sprzętowo przez rejestry:
- **SPCR** - konfiguracja SPI, włączanie, master/slave, prędkość itd,
- **SPSR** - status, flagi (np. SPIF - zakończenie transmisji),
- **SPDR** - rejestr danych, tu się wpisuje bajt do wysłania i odbiera bajt odebrany,

Najważniejsze bity w SPCR:
- **SPE** - włącza SPI, 
- **MSTR** - ustawia mikrokontroler jako master,
- **SPR1/SPR0** - szybkość zegara SPI, 
- **CPOL/CPHA** - tryb pracy SPI, polaryzacja i faza zegara,

SPI używamy do podłączania szybkich urządzeń, wyświetlaczy TFT, OLED, pamięci Flash/EEPROM, przetworniki, czujniki, moduły radiowe, sterowniki LED.

### Piny
- MOSI - PB3/D11,
- MISO - PB4/D12,
- SCK - PB5/D13,
- SS - PB2/D10,

### Różnice między master a slave
- master generuje SCK,
- slave reaguje na zegar z zewnątrz,
- master steruje linią SS,
- master inicjuje transmisję, slave tylko odpowiada,
- MSTR=1 - master, 0 - slave
- master ustawia preskaler,
- master wysyła dane po ustawieniu SPDR, slave musi je przygotować zanim master wygeneruje zegar,
