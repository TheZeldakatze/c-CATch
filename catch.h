/*
 * catch.h
 *
 *  Created on: 25.01.2020
 *      Author: victor
 */

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "chargebar.h"
#include "cat_bmp.h"
#include "grass_bmp.h"
#include "cloud1_bmp.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FLOOR_HEIGHT 50

#define CHARGEBAR_POS_X 10
#define CHARGEBAR_POS_Y 10

#define MAXIMUM_JUMP_FORCE 9

#define BIRD_COUNT 5
#define CLOUD_COUNT 14
#define BIRD_TYPE_NONE 0
#define BIRD_TYPE_PIDGIN 1
#define BIRD_TYPE_DEAD_PIDGIN 2

#define STATE_MAIN_MENU 1
#define STATE_GAME 2
#define STATE_GAME_OVER 3
#define GAME_TIME 60

#define TICK_SPEED 20
#define TICKS_PER_SECOND 1000 / TICK_SPEED

#undef PLASTIC_TEXTURES

struct Cloud {
	int x, y, type;
};

// cat and bird structures
struct Cat {
	int x;
	float y;
	float downwardForce;
	bool jumping;
};

struct Bird {
	float x, y;
	unsigned char type;
};

// function predefines
extern void gameRoutine();
extern bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern int getRandomInt(int limit);

// BitmapFontRenderer.c
extern void Font_Init();
extern void Font_DrawString(SDL_Surface* surface, int x, int y, char* string);

// pidginImage.c
extern SDL_Surface* image_pidgin_dead;
extern void Pidgin_Init();
extern void draw_Pidgin(SDL_Surface* surface, int x, int y);
extern void Pidgin_IncrementFrame();
