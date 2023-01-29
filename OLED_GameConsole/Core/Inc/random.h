/*
 * random.h
 *
 * Created: 29.01.2023 16:45:22
 *  Author: Leonid Tsigrinski
 */ 


#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdint.h>

void random_init(void);
uint8_t random_randint(uint8_t a, uint8_t b);


#endif /* RANDOM_H_ */