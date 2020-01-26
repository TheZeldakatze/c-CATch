/*
 * catch.h
 *
 *  Created on: 25.01.2020
 *      Author: victor
 */
#include <SDL/SDL.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "chargebar.h"
#include "cat_bmp.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FLOOR_HEIGHT 50

#define CHARGEBAR_POS_X 10
#define CHARGEBAR_POS_Y 10

#define MAXIMUM_JUMP_FORCE 5

#define BIRD_COUNT 3
#define BIRD_TYPE_NONE 0
#define BIRD_TYPE_BIRD 1

#define STATE_MAIN_MENU 1
#define STATE_GAME 2
#define STATE_GAME_OVER 3

// cat and bird structures
struct Cat {
	int x;
	float y;
	float downwardForce;
	bool jumping;
};

struct Bird {
	int x, y;
	unsigned char type;
};

// function predefines
extern void gameRoutine();

// BitmapFontRenderer.c
extern void Font_Init();
extern void Font_DrawString(SDL_Surface* surface, int x, int y, char* string);
