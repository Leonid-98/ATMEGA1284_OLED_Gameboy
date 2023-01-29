/*
 * buzzer.h
 *
 * Created: 28.01.2023 13:31:05
 *  Author: msi
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_DDR     DDRD
#define BUZZER_PORT    PORTD
#define BUZZER_PIN     PORTD5

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

void buzzer_init(void);
void buzzer_play_music(void);


#endif /* BUZZER_H_ */