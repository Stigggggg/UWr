#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

const uint8_t breath_table[256] PROGMEM = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,3,3,
  3,3,4,4,5,5,6,6,7,7,8,9,9,10,11,12,12,13,14,15,16,18,19,21,22,24,26,28,30,32,
  34,37,39,42,44,47,50,53,57,60,64,67,71,75,79,84,88,93,97,103,108,113,119,124,130,136,
  142,148,154,161,167,174,181,188,195,202,209,216,223,230,237,242,247,250,253,255,255,255,254,252,249,246,241,235,
  228,221,213,205,196,186,176,166,155,144,133,121,110,99,87,76,65,54,44,34,25,17,9,3,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,3,3,3,3,4,4,5,5,6,6,7,7,
  8,9,9,10,11,12,12,13,14,15,16,18,19,21,22,24,26,28,30,32,34,37,39,42,44,47,50,53,57,60,
  64,67,71,75,79,84,88,93,97,103,108,113,119,124,130,136,142,148,154,161,167,174,181,188,195,202,209,216,223,230,237,242,
  247,250,253,255,255,255,254,252,249,246,241,235,228,221,213,205,196,186,176,166,155,144,133,121,110,99,87,76,65,54,
  44,34,25,17,9,3,0,0,0,0,0,0
};

// bazowane na https://www.rapidtables.com/convert/color/hsv-to-rgb.html
void hsv_to_rgb(uint16_t hue, uint8_t *r, uint8_t *g, uint8_t *b) // wskaźniki po to, żeby zmienić wartość zmiennych wewnątrz funkcji
{
    uint8_t region = (hue / 60) % 6; // region na kole hsv, mamy takich 6
    uint16_t f = (hue % 60) * 255 / 60; // część ułamkowa regionu
    uint8_t p = 0, q = 255 - f, t = f; // zmienne pomocnicze

    switch (region) {
        case 0: *r = 255; *g = t;   *b = p;   break;
        case 1: *r = q;   *g = 255; *b = p;   break;
        case 2: *r = p;   *g = 255; *b = t;   break;
        case 3: *r = p;   *g = q;   *b = 255; break;
        case 4: *r = t;   *g = p;   *b = 255; break;
        default:*r = 255; *g = p;   *b = q;   break;
    }
}

// jak na wykładzie
void adc_init() {
    ADMUX   = _BV(REFS0);                     // referencja AVcc, wejście ADC0
    DIDR0   = _BV(ADC0D);                     // wyłączenie wejścia cyfrowego
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);  // preskaler 128
    ADCSRA |= _BV(ADEN);                      // włączenie ADC
}

void timer_init() {
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
    TCCR1B = _BV(WGM12) | _BV(CS11);
    TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS21);
}

int main() {
    timer_init();
    adc_init();
    ADCSRA |= _BV(ADSC);
    while (ADCSRA & _BV(ADSC));
    uint16_t v = ADC;
    srand(v); // chcemy, żeby sekwencja za każdym razem była inna
    DDRB |= _BV(PB1) | _BV(PB2) | _BV(PB3); 
    uint8_t base_r, base_g, base_b;

    while (1) {
        hsv_to_rgb(rand() % 360, &base_r, &base_g, &base_b); // losujemy kolor
        for (uint16_t i = 0; i < 128; i++) {
            uint8_t bright = pgm_read_byte(&breath_table[i]);
            uint8_t r = (uint16_t)base_r * bright / 255;
            uint8_t g = (uint16_t)base_g * bright / 255;
            uint8_t b = (uint16_t)base_b * bright / 255;
            OCR1A = 255 - r;
            OCR1B = 255 - g;
            OCR2A = 255 - b;
            _delay_ms(10);
        }
    }
}

