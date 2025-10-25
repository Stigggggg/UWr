#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

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

static const char *morse_table[26] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

void dot() {
    LED_PORT |= _BV(LED);
    _delay_ms(200);
    LED_PORT &= ~_BV(LED);
    _delay_ms(200);
}

void dash() {
    LED_PORT |= _BV(LED);
    _delay_ms(600);
    LED_PORT &= ~_BV(LED);
    _delay_ms(600);
}

void space() {
    _delay_ms(400);
}

void long_space() {
    _delay_ms(800);
}

void translate(char c) {
    char *morse = morse_table[c - 'a'];
    for (char *p = morse; *p; p++) {
        if (*p == '.') {
            dot();
        } else if (*p == '-') {
            dash();
        } else if (*p == ' ') {
            long_space();
        }
    }
    space();
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  char c;
  LED_DDR |= _BV(LED);

  // program testowy
  while(1) {
    scanf("%c", &c);
    translate(c);
    printf("%c", c);
  }
}