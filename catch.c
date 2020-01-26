/*
 * catch.c
 *
 *  Created on: 25.01.2020
 *      Author: victor
 */
#include "catch.h"

SDL_Surface* screen;
bool run;
SDL_Rect sdl_rect, sdl_rect2;

// key handler stuff
bool keyPressed[SDLK_LAST];

// the images
SDL_Surface* image_chargebar, *image_chargebar_dark, *image_cat, *image_bird;

struct Cat cat;
struct Bird bird[BIRD_COUNT];

int state;

int main(int argc, char* argv[]) {
	memset(keyPressed,0,sizeof(keyPressed));

	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("Could not initialize SDL! Error: %s", SDL_GetError());
		return -1;
	}

	// create a window
	screen = SDL_SetVideoMode(640, 480, 8, SDL_DOUBLEBUF | SDL_FULLSCREEN);
	if(!screen) {
		printf("Could not create a SDL window! Error: %s", SDL_GetError());
		return -1;
	}

	// initialize the font renderer
	Font_Init();

	// load the images
	SDL_RWops* rwops = SDL_RWFromConstMem(chargebar_bmp, sizeof(chargebar_bmp) / sizeof(char));
	image_chargebar = SDL_LoadBMP_RW(rwops,1);
	rwops = SDL_RWFromConstMem(chargebar_dark_bmp, sizeof(chargebar_dark_bmp) / sizeof(char));
	image_chargebar_dark = SDL_LoadBMP_RW(rwops,1);
	rwops = SDL_RWFromConstMem(cat_bmp, sizeof(cat_bmp) / sizeof(char));
	image_cat = SDL_LoadBMP_RW(rwops,1);
	SDL_SetColorKey(image_cat, SDL_SRCCOLORKEY, SDL_MapRGB(image_cat->format, 255, 0, 255));

	// set the correct physics flags for the cat
	cat.jumping = true;

	// start the event loop
	run = true;
	while(run) {
		// process all sdl events
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					run = false;
					break;

				case SDL_KEYDOWN:
					keyPressed[event.key.keysym.sym] = true;
					break;

				case SDL_KEYUP:
					keyPressed[event.key.keysym.sym] = false;
					break;
			}
		}

		// quit if the esc key was pressed
		if(keyPressed[SDLK_ESCAPE]) run = false;

		// run the game routine
		gameRoutine();

		// draw the sky
		sdl_rect.x = 0;
		sdl_rect.y = 0;
		sdl_rect.w = screen->w;
		sdl_rect.h = screen->h-FLOOR_HEIGHT;
		SDL_FillRect(screen,&sdl_rect,SDL_MapRGB(screen->format,0,0,200));

		// draw the floor
		sdl_rect.y = sdl_rect.h;
		sdl_rect.h = FLOOR_HEIGHT;
		SDL_FillRect(screen,&sdl_rect,SDL_MapRGB(screen->format,0,200,000));

		// draw the cat
		cat.x = screen->w/2 + image_cat->w/2;
		sdl_rect.x = cat.x;
		sdl_rect.y = cat.y;
		SDL_BlitSurface(image_cat, 0, screen, &sdl_rect);

		// draw the birds
		for(int i = 0; i<BIRD_COUNT; i++) {
			if(bird[i].type != BIRD_TYPE_NONE) {
				sdl_rect.x = bird[i].x;
				sdl_rect.y = bird[i].y;
				SDL_BlitSurface(image_bird, 0, screen, &sdl_rect);
			}
		}

		// draw the chargebar
		int chargeBarSplitPosition;

		if(!cat.jumping && cat.downwardForce == 0) {
			chargeBarSplitPosition = CHARGEBAR_WIDTH;
		}
		else
		if(cat.downwardForce == 0)
			chargeBarSplitPosition = 0;
		else
		if(cat.downwardForce < 0)
			chargeBarSplitPosition = CHARGEBAR_WIDTH / -(MAXIMUM_JUMP_FORCE / cat.downwardForce);
		else
			chargeBarSplitPosition = CHARGEBAR_WIDTH / (MAXIMUM_JUMP_FORCE / cat.downwardForce);

		sdl_rect.x = 0;
		sdl_rect.y = 0;
		sdl_rect.w = chargeBarSplitPosition;
		sdl_rect.h = 1;
		sdl_rect2.x = CHARGEBAR_POS_X;
		sdl_rect2.y = CHARGEBAR_POS_Y;

		// draw it 16 times
		for(int i = 0; i<15;i++) {
			SDL_BlitSurface(image_chargebar, &sdl_rect, screen, &sdl_rect2);
			sdl_rect2.y++;
		}

		// draw the grayed out part of the bar
		sdl_rect.x = chargeBarSplitPosition;
		sdl_rect.y = 0;
		sdl_rect.w = CHARGEBAR_WIDTH-chargeBarSplitPosition;
		sdl_rect2.x = CHARGEBAR_POS_X+chargeBarSplitPosition;
		sdl_rect2.y = CHARGEBAR_POS_Y;

		// draw it 16 times
		for(int i = 0; i<15;i++) {
			SDL_BlitSurface(image_chargebar_dark, &sdl_rect, screen, &sdl_rect2);
			sdl_rect2.y++;
		}

		Font_DrawString(screen, 0,5, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstufwxyz\n 01234567890: +");

		// draw the screen
		SDL_Flip(screen);

		// wait 50 milliseconds
		usleep(50);
	}

	// dispose the surfaces
	SDL_FreeSurface(screen);
	SDL_FreeSurface(image_chargebar);
	SDL_FreeSurface(image_chargebar_dark);
	//SDL_FreeSurface(screen);
	SDL_Quit();

	// close the program
	return 0;
}

void gameRoutine() {
	bool charge = keyPressed[SDLK_SPACE] && (state == STATE_GAME);

	// do the physics calculation
	if(cat.jumping) {
		cat.downwardForce+=0.03;
		cat.y+=cat.downwardForce;

		// the cat has touched the floor
		if(cat.y>screen->h-FLOOR_HEIGHT-CAT_HEIGHT) {
			cat.y = screen->h-FLOOR_HEIGHT-CAT_HEIGHT;
			cat.jumping = false;
			cat.downwardForce = 0;
		}
	} else {

		//the player accumulated some energy and let go of the space bar
		if(!charge && cat.downwardForce<0) {
			cat.jumping = true;
		}
		else if(charge) {
			if(cat.downwardForce > -MAXIMUM_JUMP_FORCE)
				cat.downwardForce-=0.02;
		}
	}

	//
}