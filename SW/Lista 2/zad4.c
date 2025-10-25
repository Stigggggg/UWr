#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD
#define POWER_DDR DDRC
#define POWER_PORT PORTC

uint8_t digits[10] = { //cyfry jak listę temu, ze schematu wyświetlacza
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

void refresh(uint8_t i, uint8_t bit) { //zmiana cyfry
    LED_PORT = ~digits[i]; //bierzemy cyfrę
    POWER_PORT &= ~(1 << bit); //włączamy jej zasilanie
    _delay_ms(5);
    LED_PORT |= 0b11111111;
    POWER_PORT |= (1 << bit); //wyłączamy
}

int main()
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0b11111111;
  LED_PORT |= 0b11111111;
  POWER_DDR |= 0b00000011;
  POWER_PORT |= 0b00000011;
  int8_t mod = 0, d = 0, j = 0;

  while(1) {
    d = mod / 10;
    j = mod % 10;
    for (int i = 0; i < 100; i++) {
        if (d > 0) {
            refresh(d, 0); //bit 0 steruje cyfrą dziesiątek
        }
        else {
            _delay_ms(5);
        }
        refresh(j, 1); //bit 1 cyfrą jedności, wynika ze schematu
    }
    
    mod = (mod + 1) % 60;
  }
  
}