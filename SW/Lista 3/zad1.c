#include <avr/io.h> 
#include <util/delay.h> 
#include <stdint.h> 
#include <avr/pgmspace.h> 
#include <inttypes.h>

#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

// wavelength - połówka fali (niskiej/wysokiej)
// duration_us - czas trwania nuty w mikrosekundach
// inspirowane Make: AVR Programming, strony 98 i 99
void playNote(uint16_t wavelength, uint32_t duration_us) {
    uint32_t elapsed = 0;
    while (elapsed < duration_us) {
        BUZZ_PORT ^= (1 << PB5);
        for (uint16_t i = 0; i < wavelength; i++) {
            _delay_us(1);
        }
        elapsed += wavelength;
    }
}

// 4 oktawa
#define C4 262
#define Cx4 277
#define D4 294
#define Dx4 311
#define E4 330
#define F4 349
#define Fx4 370
#define G4 392
#define Gx4 415
#define A4 440
#define Ax4 466
#define B4 494
// 5 oktawa
#define C5 523
#define Cx5 554
#define D5 587
#define Dx5 622
#define E5 659
#define F5 698
#define Fx5 740
#define G5 784
#define Gx5 831
#define A5 880
#define Ax5 932
#define B5 988

// definicja połówki fali w us
#define convert(note) ((uint16_t)(500000 / (uint32_t)note))

// tempo: ćwierćnuta w us
#define quarter 500000UL
#define half (quarter * 2)

typedef struct {
    uint16_t note;
    uint32_t type;
} Sound;

// marsz imperialny
const Sound song[] PROGMEM = {
    {convert(A4), half},      // A
    {convert(A4), half},      // A
    {convert(A4), half},      // A
    {convert(F4), quarter},   // F
    {convert(C5), quarter},   // C
    {convert(A4), half},      // A

    {convert(F4), quarter},   // F
    {convert(C5), quarter},   // C
    {convert(A4), half},      // A

    {convert(E5), half},      // E
    {convert(E5), half},      // E
    {convert(E5), half},      // E
    {convert(F5), quarter},   // F
    {convert(C5), quarter},   // C
    {convert(Gx4), half},     // G#
    {convert(F4), quarter},   // F
    {convert(C5), quarter},   // C
    {convert(A4), half},      // A

    {convert(A5), half},      // A
    {convert(A4), quarter},   // A
    {convert(A5), half},      // A
    {convert(A4), quarter},   // A
    {convert(A5), half},      // A
    {convert(F5), quarter},   // F
    {convert(C5), quarter},   // C
    {convert(A4), half}       // A
};

void pause(uint8_t length) {
    for (int i = 0; i < length; i++) {
        _delay_ms(100);
    }
}

void play_song() {
    uint16_t length = sizeof(song)/sizeof(song[0]);
    for (int i = 0; i < length; i++) {
        uint16_t note = pgm_read_word(&song[i].note);
        uint32_t type = pgm_read_dword(&song[i].type);
        playNote(note, type);
        pause(1);
    }
}

int main() {
    BUZZ_DDR |= (1 << PB5);
    BUZZ_PORT &= ~(1 << PB5);
    while (1) {
        play_song();
        _delay_ms(2000);
    }
}




