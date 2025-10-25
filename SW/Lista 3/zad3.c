#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define LED_DDR DDRB
#define LED_PORT PORTB

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

uint8_t exp_tab[256];

void exp_func_init() {
    for (int i = 0; i < 256; i++) {
        exp_tab[i] = (i * i) >> 8;
    }
}

int main() {
    LED_DDR |= (1 << PB5);
    adc_init();
    exp_func_init();
    
    while(1) {
        LED_PORT &= ~(1 << PB5); // wyłączamy LED podczas pomiaru
        
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
        uint8_t level = v >> 2;
        uint8_t log = exp_tab[level];

        for (int i = 0; i < 255; i++) {
            if (i < log) {
                LED_PORT |= (1 << PB5);
            } else {
               LED_PORT &= ~(1 << PB5); 
            }
            _delay_us(100);
        }
    }
}


