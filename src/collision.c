#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>


//custom lib
#include "structs.h"

// collision detection out of bounds
bool collision(GameState *game, char direction) {

	Player *position = &game->player;
	WindowSize *win = &game->windowSize;
	int boundsPadding = game->player.area + 5; //space between character and object

	if(direction == 'L'){
		if(position->x  <= 0){
			return true;
		}
	}

	if(direction == 'R'){
		if(position->x + boundsPadding >= win->x){
			return true;
		}
	}

	if(direction == 'U'){
		if(position->y <= 0){
			return true;
		}
	}

	if(direction == 'D'){
		if(position->y + boundsPadding >= win->y){
			return true;
		}
	}
	

	return false;
}