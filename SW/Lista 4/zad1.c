#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

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

void timer1_init()
{
  // tryb normalny, preskaler = 1
  TCCR1B = _BV(CS10);
}

FILE uart_file;

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj licznik
  timer1_init();

  // program testowy
  volatile int8_t a1 = 1, a2 = 1;
  volatile int16_t b1 = 1, b2 = 1;
  volatile int32_t c1 = 1, c2 = 1;
  volatile int64_t d1 = 1, d2 = 1;
  volatile float e1 = 1.0f, e2 = 1.0f;

  // 8-bitowe
  printf("8-bitowe:\r\n");
  TCNT1 = 0;
  volatile int8_t a3 = a1 + a2;
  volatile uint16_t a4 = TCNT1;
  printf("Dodawanie: %u\r\n", a4);
  TCNT1 = 0;
  a3 = a1 * a2;
  a4 = TCNT1;
  printf("Mnożenie: %u\r\n", a4);
  TCNT1 = 0;
  a3 = a1 / a2;
  a4 = TCNT1;
  printf("Dzielenie: %u\r\n", a4);

  // 16-bitowe
  printf("16-bitowe:\r\n");
  TCNT1 = 0;
  volatile int16_t b3 = b1 + b2;
  volatile uint16_t b4 = TCNT1;
  printf("Dodawanie: %u\r\n", b4);
  TCNT1 = 0;
  b3 = b1 * b2;
  b4 = TCNT1;
  printf("Mnożenie: %u\r\n", b4);
  TCNT1 = 0;
  b3 = b1 / b2;
  b4 = TCNT1;
  printf("Dzielenie: %u\r\n", b4);

  // 32-bitowe
  printf("32-bitowe:\r\n");
  TCNT1 = 0;
  volatile int32_t c3 = c1 + c2;
  volatile uint16_t c4 = TCNT1;
  printf("Dodawanie: %u\r\n", c4);
  TCNT1 = 0;
  c3 = c1 * c2;
  c4 = TCNT1;
  printf("Mnożenie: %u\r\n", c4);
  TCNT1 = 0;
  c3 = c1 / c2;
  c4 = TCNT1;
  printf("Dzielenie: %u\r\n", c4);

  // 64-bitowe
  printf("64-bitowe:\r\n");
  TCNT1 = 0;
  volatile int64_t d3 = d1 + d2;
  volatile uint16_t d4 = TCNT1;
  printf("Dodawanie: %u\r\n", d4);
  TCNT1 = 0;
  d3 = d1 * d2;
  d4 = TCNT1;
  printf("Mnożenie: %u\r\n", d4);
  TCNT1 = 0;
  d3 = d1 / d2;
  d4 = TCNT1;
  printf("Dzielenie: %u\r\n", d4);

  // floaty
  printf("Floaty:\r\n");
  TCNT1 = 0;
  volatile float e3 = e1 + e2;
  volatile uint16_t e4 = TCNT1;
  printf("Dodawanie: %u\r\n", e4);
  TCNT1 = 0;
  e3 = e1 * e2;
  e4 = TCNT1;
  printf("Mnożenie: %u\r\n", e4);
  TCNT1 = 0;
  e3 = e1 / e2;
  e4 = TCNT1;
  printf("Dzielenie: %u\r\n", e4);
}



