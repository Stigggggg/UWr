#include <avr/io.h>
#include <util/delay.h>

#define LED PD5
#define LED_DDR DDRD
#define LED_PORT PORTD

int main() {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= _BV(LED);
  while (1) {
    LED_PORT |= _BV(LED);
    _delay_ms(100);
    LED_PORT &= ~_BV(LED);
    _delay_ms(100);
  }
}