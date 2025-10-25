#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

uint8_t digits[10] = {
    0b10111111,
    0b00000110,
    0b11011011,
    0b01001111,
    0b11100110,
    0b01101101,
    0b11111101,
    0b00000111,
    0b11111111,
    0b01101111
};

int main() {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR = 0b11111111;
  
  while (1) {
    for (int i = 0; i < 10; i++) {
        LED_PORT = ~digits[i];
        _delay_ms(1000);
    }
  }
}