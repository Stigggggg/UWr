#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define BURST_US 600
#define GAP_US 600
#define BURST_COUNT 6
#define FRAME_GAP_MS 100
#define DETECT_HOLD_MS 250
#define F_CPU 16000000UL

void timer1_init() {
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10);
    OCR1A = 210;
    TCNT1 = 0;
}

void ir_on()
{
    TCCR1A |= (1 << COM1A0);
}

void ir_off()
{
    TCCR1A &= ~(1 << COM1A0);
    PORTB &= ~(1 << PB1);
}

uint16_t send_burst()
{
    uint16_t hits = 0;

    for (uint8_t i = 0; i < BURST_COUNT; i++) {
        ir_on();
        _delay_us(100);
        for (uint8_t s = 0; s < 9; s++) {
            if (!(PINB & (1 << PB0)))
                hits++;
            _delay_us(50);
        }

        ir_off();
        _delay_us(GAP_US);
    }

    return hits;
}

int main() {
    DDRB |= (1 << DDB1) | (1 << DDB2); 
    DDRB &= ~(1 << DDB0);              
    PORTB |= (1 << PB0);
    timer1_init();
    while (1) {
        if (send_burst() >= 8) {
            PORTB |= (1 << PB2);
            _delay_ms(DETECT_HOLD_MS);
            PORTB &= ~(1 << PB2);
        }
        _delay_ms(FRAME_GAP_MS);
    }
}
