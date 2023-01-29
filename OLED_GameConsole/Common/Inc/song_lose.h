/*
 * song_lose.h
 *
 * Created: 27.01.2023 23:19:45
 *  Author: msi
 */ 


#ifndef SONG_LOSE_H_
#define SONG_LOSE_H_

#include "notes.h"

#define MELODY_SIZE 	24

const int16_t melody[MELODY_SIZE] = {
	// game over sound
	NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, 
	NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
	NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2
};

const int16_t tempo = 35;

#endif /* SONG_LOSE_H_ */