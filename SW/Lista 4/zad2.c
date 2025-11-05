#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE uart_file;

// inicjalizacja ADC
void adc_init() {
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0, mniej szumów
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer1_init() {
    ICR1 = 255; // wartość top
    TCCR1A = _BV(COM1A1) | _BV(WGM11); // non inverting PWM
    TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10); // tryb CTC, bez preskalera
    OCR1A = 0;
} 

static const uint16_t tab[] PROGMEM = {0, 2, 4, 8, 16, 32, 64, 128, 192, 224, 255};

int main() {
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
    timer1_init();
    DDRB |= _BV(PB1);
    uint8_t smooth = 0; // filtr zmiany PWM, unika skoków
    while (1) {
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (ADCSRA & _BV(ADSC)); // czekaj na wynik
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
        uint8_t index = v * 10 / 1024;
        uint8_t pwm_val = ICR1 - pgm_read_word(&tab[index]);
        smooth = (smooth * 7 + pwm_val) / 8;
        OCR1A = smooth;
        printf("Jasność LED: %3u\r\n", OCR1A);
        _delay_ms(50);
    }
}





