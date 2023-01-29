/*
 * buzzer.c
 *
 * Created: 28.01.2023 13:30:53
 *  Author: msi
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "buzzer.h"
#include "notes.h"
#include "song_lose.h"

volatile static uint16_t g_note_idx = 0;

static uint16_t priv_scaleDelay(uint16_t delay_ms);
static void priv_startTimers(void);
static void priv_stopTimers(void);

/**
 * Fast timer, freq generator
 */
ISR(TIMER1_COMPA_vect)
{

    PIND = 1 << PIND5;
}

/**
 * Slow timer, tone changer
 */
ISR(TIMER3_COMPA_vect)
{
    TCNT3 = 0;
    g_note_idx += 2;
}

static uint16_t priv_scaleDelay(uint16_t delay_ms)
{
    return (delay_ms - delay_ms / 32 + delay_ms / 128);
}

static void priv_startTimers(void)
{
    // TIMER1, sound generator, fast timer
    TCCR1A = (1 << WGM10) | (1 << WGM11);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
    TIMSK1 |= 1 << OCIE1A;

    // TIMER3, tone changer, slow timer
    TCCR3A = 0;
    TCCR3B = (0 << WGM32) | (0 << WGM33) | (1 << CS32) | (0 << CS31) | (1 << CS30);
    TIMSK3 |= 1 << OCIE3A;
}

static void priv_stopTimers(void)
{
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;

    TCCR3A = 0;
    TCCR3B = 0;
    TIMSK3 = 0;
}

void buzzer_init(void)
{
    BUZZER_DDR |= 1 << BUZZER_PIN;
    BUZZER_PORT |= 1 << BUZZER_PIN;
}

void buzzer_play_music(void)
{
    priv_startTimers();

    while (g_note_idx < MELODY_SIZE - 1)
    {
        if (melody[g_note_idx])
        {
            TIMSK1 |= 1 << OCIE1A;
            OCR1A = F_CPU / melody[g_note_idx] / 2;
        }
        else
        {
            TIMSK1 &= ~(1 << OCIE1A);
        }

        int16_t note_len = (240000 / tempo) / abs(melody[g_note_idx + 1]) * 2;
        if (melody[g_note_idx + 1] < 0)
            note_len *= 1.5;
        OCR3A = priv_scaleDelay(note_len);
    }

    priv_stopTimers();
    g_note_idx = 0;
}
