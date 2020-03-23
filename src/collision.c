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

//code from  https://www.youtube.com/watch?v=yUiZcWHOfW4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=12

// animate
void animate(GameState *game, char direction) {

	Player *player = &game->player;
	int frameFreq = 6;

	if(direction == 'R'){

		//every 30 frames
		if(game->time % frameFreq == 0){
		
			if(player->currentText == player->wr[0]){
				
				player->currentText = player->wr[1];
			}

			else {
				player->currentText = player->wr[0];
			}
		}
		
	}

	if(direction == 'L'){

		//every 30 frames
		if(game->time % frameFreq == 0){
		
			if(player->currentText == player->wl[0]){
				
				player->currentText = player->wl[1];
			}

			else {
				player->currentText = player->wl[0];
			}
		}
		
	}

	if(direction == 'U'){

		//every 30 frames
		if(game->time % frameFreq == 0){
		
			if(player->currentText == player->wu[0]){
				
				player->currentText = player->wu[1];
			}

			else {
				player->currentText = player->wu[0];
			}
		}
		
	}

	if(direction == 'D'){

		//every 30 frames
		if(game->time % frameFreq == 0){
		
			if(player->currentText == player->wd[0]){
				
				player->currentText = player->wd[1];
			}

			else {
				player->currentText = player->wd[0];
			}
		}
		
	}

}