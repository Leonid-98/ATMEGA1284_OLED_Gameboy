/*
 * twi_master.c
 *
 * Created: 09-Jun-19 11:20:17 AM
 *  Author: TEP SOVICHEA
 */

#include "twi_master.h"

void tw_init()
{
	DDRC |= (1 << TW_SDA_PIN) | (1 << TW_SCL_PIN);
#ifdef TW_PULLUP_EN
	PORTC |= (1 << TW_SDA_PIN) | (1 << TW_SCL_PIN);
#else
	PORTC &= ~((1 << TW_SDA_PIN) | (1 << TW_SCL_PIN));
#endif
	DDRC &= ~((1 << TW_SDA_PIN) | (1 << TW_SCL_PIN));
	TWBR = ((F_CPU / TW_BAUDRATE) - 16) / 2;
	TWSR = (0 << TWPS1) | (1 << TWPS0);
}

void tw_start(void)
{
	/* Send START condition */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	/* Wait for TWINT flag to set */
	while (!(TWCR & (1 << TWINT)));
}

void tw_stop(void)
{
	/* Send STOP condition */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void tw_write(uint8_t data)
{
	/* Transmit 1 byte*/
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT flag to set */
	while (!(TWCR & (1 << TWINT)));
	
	}
	
}
