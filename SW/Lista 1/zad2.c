#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

int main() {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR = 0b11111111;
  uint8_t pattern = 0b00000001;
  int dir = 1;

  while (1) {
    LED_PORT = pattern;
    _delay_ms(100);
    if (dir > 0) {
        pattern <<= 1;
        if (pattern == 0b10000000) {
            dir = -1;
        }
    } else {
        pattern >>= 1;
        if (pattern == 0b00000001) {
            dir = 1;
        }
    }
  }
}