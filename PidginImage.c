/*
 * PidginImage.c
 *
 *  Created on: 26.01.2020
 *      Author: victor
 */
#include "pidgin_image.h"
#include "catch.h"

static int animation_index = 0, delay, ax = 1;
static SDL_Rect sdl_rect_output, sdl_rect_source;
static SDL_Surface* image_pidgin;

void Pidgin_Init() {
	SDL_RWops* rwops = SDL_RWFromConstMem(pidgin_bmp, sizeof(pidgin_bmp) / sizeof(char));
	image_pidgin = SDL_LoadBMP_RW(rwops,1);
	SDL_SetColorKey(image_pidgin, SDL_SRCCOLORKEY, SDL_MapRGB(image_pidgin->format, 255, 0, 255));
	//SDL_FreeRW(rwops);

	sdl_rect_source.x = 0;
	sdl_rect_source.w = PIDGIN_WIDTH;
	sdl_rect_source.h = PIDGIN_HEIGHT;
}

void draw_Pidgin(SDL_Surface* surface, int x, int y) {
	sdl_rect_output.x = x;
	sdl_rect_output.y = y;
	SDL_BlitSurface(image_pidgin, &sdl_rect_source, surface, &sdl_rect_output);
}

void Pidgin_IncrementFrame() {
	delay++;
	//printf("%d\n", delay);
	if(delay >= 50) {
		delay = 0;
		animation_index+=ax;
		sdl_rect_source.y = animation_index * PIDGIN_HEIGHT;
		if(animation_index > 1) ax = -1;
		if(animation_index < 1) ax = 1;
	}
}
