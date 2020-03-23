//code from https://www.youtube.com/watch?v=NTKjjqIzvd4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=10


#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

//custom lib
#include "structs.h"

extern bool collision(GameState *game, char directrion);
extern void animate(GameState *game, char directrion);
extern void loadPlayerTextures(GameState *game);
extern void loadFonts(GameState *game);
extern void drawHUD(GameState *game);

//load function
void loadGame(GameState *game) {

	//set player area
	game->player.area = 100;

	//start game time
	game->time = 0;

	//signal that game is on
	game->running = true;

	//load texture
	loadPlayerTextures(game);

	//load fonts
	loadFonts(game);

	//first frame
	game->player.currentText = game->player.wd[0];
	
	//set player variables
	game->player.x = 220;
	game->player.y = 140;
	game->player.health = 100;

}

//render game condition on screen
void doRender(GameState *game) {	

	//clear the screen
	SDL_RenderClear(game->rend);

	//background color
	SDL_SetRenderDrawColor(game->rend, 50, 140, 50, 255);


	//draw player postion
	SDL_Rect playerRect = {game->player.x, game->player.y, 100, 100};
	SDL_RenderCopy(game->rend, game->player.currentText, NULL, &playerRect);
	

	//draw HUD
	drawHUD(game);

	//when done drawing, present drawing
	SDL_RenderPresent(game->rend);

}

//process inputs and outputs to game
int processEvents(SDL_Window *window, GameState *game){

	SDL_Event event;
	int notDone = true;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	while(SDL_PollEvent(&event)){

		switch(event.type){
			
			case SDL_QUIT:
				SDL_DestroyWindow(window);
				window = NULL;
				notDone = false;
				break;


			//set standing still frame
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
					case SDLK_RIGHT:
						game->player.currentText = game->player.wr[0]; 
						break;
					case SDLK_LEFT:
						game->player.currentText = game->player.wl[0];
						break;
					case SDLK_UP:
						game->player.currentText = game->player.wu[0];
						break;
					case SDLK_DOWN:
						game->player.currentText = game->player.wd[0];
						break;
				}
				break;

		}
	}


	int playerSpeed = 7; //how fast player moves

	if(state[SDL_SCANCODE_LEFT] && !collision(game , 'L')){
		animate(game, 'L');
		game->player.x -= playerSpeed;
	}

	else if(state[SDL_SCANCODE_RIGHT] && !collision(game , 'R')){
		animate(game, 'R');
		game->player.x += playerSpeed;
	}

	else if(state[SDL_SCANCODE_UP] && !collision(game , 'U')){
		animate(game, 'U');
		game->player.y -= playerSpeed;
		
	}

	else if(state[SDL_SCANCODE_DOWN] && !collision(game , 'D')){
		animate(game, 'D');
		game->player.y += playerSpeed;
	}
	
	game->time++;
	game->time = game->time % 60;
	return notDone;
}

//close everything and quit
int terminateGame(GameState *game, SDL_Window *window){
	
	printf("terminating game...\n");
	SDL_DestroyTexture(game->player.wr[0]);
	
	SDL_DestroyTexture(game->player.wu[0]);
	SDL_DestroyTexture(game->player.wl[0]);
	SDL_DestroyTexture(game->player.wd[0]);

	SDL_DestroyTexture(game->player.wr[1]);
	SDL_DestroyTexture(game->player.wu[1]);
	SDL_DestroyTexture(game->player.wl[1]);
	SDL_DestroyTexture(game->player.wd[1]);
	
	SDL_DestroyTexture(game->player.currentText);
	
	//destroy font
	if(game->hud.label != NULL){
		SDL_DestroyTexture(game->hud.label);
		TTF_CloseFont(game->hud.font);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(game->rend);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

//boot game
int main(int argc, const char *argv[]){

	//contains all game objects
	GameState game;

	//set window size
	game.windowSize.x = 740;
	game.windowSize.y = 580;

	SDL_Window *window; 		//decalre window
	SDL_Event event;    		//decalre event
	
	SDL_Init(SDL_INIT_VIDEO);	 //start sdl2
	TTF_Init(); 				 //initialize fonts

	//start window
	window = SDL_CreateWindow("game",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  game.windowSize.x,
							  game.windowSize.y,
							  0);

	game.rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
	//loads textures and player variables
	loadGame(&game);

	printf("game is running\n");

	while(game.running == true){

		//run input and continue or quit the game
		game.running = processEvents(window, &game);

		//render the game
		doRender(&game);

	}

	return terminateGame(&game, window);

}