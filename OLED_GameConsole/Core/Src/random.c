/*
 * random.c
 *
 * Created: 29.01.2023 16:45:09
 *  Author: Leonid Tsigrinski
 */
#include <avr/io.h>

#include "random.h"

void random_init(void)
{
    srand(TCNT0);
}

/**
 * Random value in interval [a; b]
 */
uint8_t random_randint(uint8_t a, uint8_t b)
{
    return rand() % (b - a + 1) + a;
}