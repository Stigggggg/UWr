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

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_DDR DDRB
#define BTN_PIN PINB
#define BTN_PORT PORTB

char morse[40] = { // tablicowa reprezentacja drzewa kodów Morsa
  ' ', 
  ' ',
  'e','t',
  'i','a','n','m',  
  's','u','r','w','d','k','g','o', 
  'h','v','f',' ','l',' ','p','j','b','x','c','y','z','q',' ',' '
};

int main()
{
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  LED_DDR |= (1 << LED);
  LED_PORT &= ~(1 << LED);
  BTN_DDR &= ~(1 << BTN);
  BTN_PORT |= (1 << BTN);
  uint8_t pressed = 0, released = 0;
  int i = 1;
  
  while(1) {
    if (!(BTN_PIN & (1 << BTN))) { //czy przycisk wciśnięty
        released = 0;
        pressed++;
        LED_PORT |= (1 << LED);
    } else { //przycisk puszczony
        LED_PORT &= ~(1 << LED);
        if (pressed > 0) {
            if (pressed < 5) { //kropka
                i *= 2;
                printf(".");
            } else { //kreska
                i = i * 2 + 1;
                printf("-");
            }
            pressed = 0;
        }
        released++;
    }
    if (released == 8) { //po dłuższej przerwie wypisujemy znak
        char translated = morse[i];
        printf("%c ", translated);
        LED_PORT |= (1 << LED);
        i = 1; 
        _delay_ms(80);
        LED_PORT &= ~(1 << LED);
        released = 0;
    }
    _delay_ms(100);
  }
}