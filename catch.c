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

unsigned int state, menu_state, score;
int ticks_to_next_second, time_left;
unsigned long last_fps_count_time;

int main(int argc, char *argv[]) {
	memset(keyPressed,0,sizeof(keyPressed));
	srand(435334);

	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("Could not initialize SDL! Error: %s", SDL_GetError());
		return -1;
	}

	// create a window
	if(argc>1 && strcmp(argv[1], "-fs") == 0)
		screen = SDL_SetVideoMode(640, 480, 8, SDL_DOUBLEBUF | SDL_FULLSCREEN);
	else
		screen = SDL_SetVideoMode(640, 480, 8, SDL_DOUBLEBUF);

	if(!screen) {
		printf("Could not create a SDL window! Error: %s", SDL_GetError());
		return -1;
	}

	// initialize the font renderer
	Font_Init();

	// initialize the pidgin animation
	Pidgin_Init();

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
	state = 1;
	while(run) {

		// get the time
		long deltaTime = SDL_GetTicks();

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

		// check if the fullscreen toogle button was hit
		if(keyPressed[SDLK_f]) {
			SDL_WM_ToggleFullScreen(screen);
		}

		// run the game routine
		gameRoutine();

		// draw the sky
		sdl_rect.x = 0;
		sdl_rect.y = 0;
		sdl_rect.w = SCREEN_WIDTH;
		sdl_rect.h = SCREEN_HEIGHT-FLOOR_HEIGHT;
		SDL_FillRect(screen,&sdl_rect,SDL_MapRGB(screen->format,0,0,200));

		// draw the floor
		sdl_rect.y = sdl_rect.h;
		sdl_rect.h = FLOOR_HEIGHT;
		SDL_FillRect(screen,&sdl_rect,SDL_MapRGB(screen->format,0,200,000));

		// draw the cat
		cat.x = SCREEN_WIDTH/2 - image_cat->w/2;
		sdl_rect.x = cat.x;
		sdl_rect.y = cat.y;
		SDL_BlitSurface(image_cat, 0, screen, &sdl_rect);


		if(state == STATE_MAIN_MENU) {
			// draw the main menu
			sdl_rect.x = SCREEN_WIDTH/2-73;
			sdl_rect.h = 18;
			sdl_rect.y = 175 + menu_state * 20;
			sdl_rect.w = 146;
			SDL_FillRect(screen,&sdl_rect,SDL_MapRGB(screen->format,204,133,0));
			Font_DrawString(screen, SCREEN_WIDTH/2-16, 180, "Play");
			Font_DrawString(screen, SCREEN_WIDTH/2-68, 200, "Toggle Fullscreen");
			Font_DrawString(screen, SCREEN_WIDTH/2-16, 220, "Quit");
		}
		else
		if(state == STATE_GAME) {

			// draw the birds
			Pidgin_IncrementFrame();
			for(int i = 0; i<BIRD_COUNT; i++) {
				if(bird[i].type == BIRD_TYPE_PIDGIN) {
					draw_Pidgin(screen, bird[i].x, bird[i].y);
				}
				else if(bird[i].type == BIRD_TYPE_DEAD_PIDGIN) {
					sdl_rect.x = bird[i].x;
					sdl_rect.y = bird[i].y;
					SDL_BlitSurface(image_pidgin_dead, 0, screen, &sdl_rect);
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

			// draw the score
			char score_s[50]; // TODO this could create a buffer overflow
			sprintf(score_s, "SCORE: %d", score);
			int length = strlen(score_s) + 1;
			Font_DrawString(screen, SCREEN_WIDTH - length * 8, 5, score_s);

			// draw the time
			sprintf(score_s, "TIME LEFT: %d", time_left);
			length = strlen(score_s) + 1;
			Font_DrawString(screen, SCREEN_WIDTH - length * 8, 15, score_s);
		}
		else if(state == STATE_GAME_OVER) {
			Font_DrawString(screen, SCREEN_WIDTH/2-36, 150, "GAME OVER");
			Font_DrawString(screen, SCREEN_WIDTH/2-96, 200, "Press Return to continue");

			// draw the score
			char score_s[50]; // TODO this could create a buffer overflow
			sprintf(score_s, "Score: %d", score);
			int length = strlen(score_s) + 1;
			Font_DrawString(screen, SCREEN_WIDTH /2  - length * 4, 180, score_s);
		}

		// draw the fps
		char fps_s[50]; // TODO this could create a buffer overflow
		sprintf(fps_s, "FPS: %i", 1000 / (SDL_GetTicks() - last_fps_count_time));
		last_fps_count_time = SDL_GetTicks();
		int length = strlen(fps_s) + 1;
		Font_DrawString(screen, SCREEN_WIDTH - length * 8, 24, fps_s);

		//Font_DrawString(screen, 0,5, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstufwxyz\n 01234567890: +");
		Font_DrawString(screen, SCREEN_HEIGHT-10, 5, "");

		// draw the screen
		SDL_Flip(screen);

		// get the delta time
		deltaTime = SDL_GetTicks()-deltaTime;

		// calculate the time until the next frame
		deltaTime = TICK_SPEED - deltaTime;

		// if it is higher than 0, sleep
		if(deltaTime > 0) {
				unsigned int time_from_sleep_return = SDL_GetTicks();

				while(deltaTime + time_from_sleep_return > SDL_GetTicks()) {

					// try to sleep for the left time
					unsigned int time = (deltaTime + time_from_sleep_return-SDL_GetTicks()) * 1000;
					if(time > 0)
						usleep(time);
				}
		}
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
		cat.downwardForce+=0.1;
		cat.y+=cat.downwardForce;

		// the cat has touched the floor
		if(cat.y>SCREEN_HEIGHT-FLOOR_HEIGHT-CAT_HEIGHT) {
			cat.y = SCREEN_HEIGHT-FLOOR_HEIGHT-CAT_HEIGHT;
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
				cat.downwardForce-=0.2;
		}
	}

	if(state == STATE_MAIN_MENU) {
		if(keyPressed[SDLK_UP] && menu_state > 0) {
			menu_state--;
			keyPressed[SDLK_UP] = false;
		}
		if(keyPressed[SDLK_DOWN] && menu_state < 2) {
			menu_state++;
			keyPressed[SDLK_DOWN] = false;
		}

		if(keyPressed[SDLK_RETURN]) {
			keyPressed[SDLK_RETURN] = false; // reset the key
			if(menu_state == 0) { // start button
				score = 0;
				time_left = GAME_TIME;
				ticks_to_next_second = TICKS_PER_SECOND;
				for(int i = 0; i<BIRD_COUNT; i++)
					bird[i].type = BIRD_TYPE_NONE;
				state = STATE_GAME;
			}
			else
			if(menu_state == 1) { // toggle fullscreen button
				SDL_WM_ToggleFullScreen(screen);
			}
			else
			if(menu_state == 2) { // quit button
				run = false;
			}
		}
	}
	else
	// move the birds in the game state
	if(state == STATE_GAME) {

		// count down
		ticks_to_next_second--;
		if(ticks_to_next_second < 0) {
			ticks_to_next_second = TICKS_PER_SECOND;
			time_left--;
			if(time_left<0)
				state = STATE_GAME_OVER;
		}

		for(int i = 0; i<BIRD_COUNT; i++) {

			// if the selected bird exists, move it
			if(bird[i].type == BIRD_TYPE_PIDGIN) {
				bird[i].x+= 1;

				// if the bird left the screen, reset it
				if(bird[i].x > SCREEN_WIDTH) {
					bird[i].type = BIRD_TYPE_NONE;
				}
				else {

					// check if the bird collided with the cat
					if(checkCollision(cat.x, cat.y, image_cat->w, image_cat->h, bird[i].x, bird[i].y, image_cat->w, image_cat->h)) {
						bird[i].type = BIRD_TYPE_DEAD_PIDGIN;
						score+=10;
					}
				}

			} else if(bird[i].type == BIRD_TYPE_DEAD_PIDGIN) {
				bird[i].y+= 2;

				if(bird[i].y > SCREEN_HEIGHT-FLOOR_HEIGHT) {
					bird[i].type = BIRD_TYPE_NONE;
				}

			} else {
				// there should be a 1 in 10 chance for a bird to spawn
				if(getRandomInt(20) == 1) {
					bird[i].x = -150 + getRandomInt(100);
					bird[i].y = 10 + getRandomInt(SCREEN_HEIGHT - FLOOR_HEIGHT - 40);
					bird[i].type = BIRD_TYPE_PIDGIN;
				}
			}
		}
	}

	// the game over state
	else
	if(state == STATE_GAME_OVER) {
		if(keyPressed[SDLK_RETURN]) {
			state = STATE_MAIN_MENU;
			keyPressed[SDLK_RETURN] = false;
		}
	}
}

bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
		if(y1 > y2 + h2) return false;
		if(y2 > y1 + h1) return false;
		if(x1 > x2 + w2) return false;
		if(x2 > x1 + w1) return false;

		return true;
}


int getRandomInt(int limit) {
	return rand() % (limit+1);
}
