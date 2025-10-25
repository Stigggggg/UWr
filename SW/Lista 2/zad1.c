#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

int main() {
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  uint8_t buf[100] = {0};
  uint8_t i = 0;

  while (1) {
    uint8_t if_pressed = !(BTN_PIN & _BV(BTN));
    buf[i] = if_pressed;
    uint8_t i_before = (i + 1) % 100;
    uint8_t state_before = buf[i_before];
    
    if (state_before) {
        LED_PORT |= _BV(LED);
    } else {
        LED_PORT &= ~_BV(LED);
    }

    i++;
    if (i >= 100) {
        i = 0;
    }
    _delay_ms(10);

  }
}