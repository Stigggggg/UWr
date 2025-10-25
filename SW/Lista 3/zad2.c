#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
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

// inicjalizacja ADC
void adc_init()
{
  // mamy ADC = V_in/V_ref * 1023, więc V_ref to Vcc, a V_in to ustawione 1.1 bitami 1110
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

#define LED_DDR DDRB
#define LED_PORT PORTB

int main()
{
  // zainicjalizuj UART
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj ADC
  adc_init();
  // mierz napięcie
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    // Vin = 1.1V, Vref = Vcc
    // zatem Vcc = 1.1 * 1023 / ADC
    // float vcc = (1.1 * 1023.0) / v;
    // printf("Napięcie: %.2f V\r\n", vcc);
    // _delay_ms(100);
    // teraz z diodą
    LED_DDR |= (1 << PB5);
    float vcc = (1.1 * 1023.0) / v;
    printf("Napięcie z diodą: %.2f V\r\n", vcc);
    LED_PORT |= (1 << PB5);
    _delay_ms(500);
    LED_PORT &= ~(1 << PB5);
    _delay_ms(500);
  }
}

