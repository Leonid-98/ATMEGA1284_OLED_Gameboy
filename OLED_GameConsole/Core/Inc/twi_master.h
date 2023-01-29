/*
 * twi_master.h
 *
 * Created: 09-Jun-19 11:20:04 AM
 *  Author: TEP SOVICHEA
 *  Refactored: Leonid Tsigrinski
 */

#ifndef TWI_MASTER_H_
#define TWI_MASTER_H_

#include <avr/io.h>
#include <util/twi.h>
#include <stdbool.h>

#include "main.h"

#define TW_SCL_PIN          PORTC0
#define TW_SDA_PIN          PORTC1
#define TW_BAUDRATE         400000
#define TW_SLA_W(ADDR)      ((ADDR << 1) | TW_WRITE)

void tw_init();
void tw_start(void);
void tw_stop(void);
void tw_write(uint8_t data);

#endif /* TWI_MASTER_H_ */