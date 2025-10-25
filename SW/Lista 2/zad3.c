#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

int main() {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0b11111111;
  LED_PORT &= 0b00000000;
  BTN_DDR &= 0b11111000;
  BTN_PORT |= 0b00000111;

  uint8_t left = 0, mid = 0, right = 0;
  uint8_t n = 0;

  while(1) {
    if (!(PINB & 0b00000001) && !left) { //lewy przycisk zwiększa kod
        n++;
        left = 1;
    } else if ((PINB & 0b00000001) && left) {
        left = 0;
    }
    if (!(PINB & 0b00000100) && !right) { //prawy zmniejsza
        n--;
        right = 1;
    } else if ((PINB & 0b00000100) && right) {
        right = 0;
    }
    if (!(PINB & 0b00000010) && !mid) { //środkowy resetuje
        n = 0;
        mid = 1;
    } else if ((PINB & 0b00000010) && mid) {
        mid = 0;
    }
    LED_PORT = n ^ (n >> 1); //wyliczanie kodu Graya za pomocą XORa
    //https://eduinf.waw.pl/inf/alg/006_bin/0025.php stąd metoda
    _delay_ms(10);
  }
}