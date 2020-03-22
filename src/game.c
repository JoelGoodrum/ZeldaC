//code from https://www.youtube.com/watch?v=NTKjjqIzvd4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=10


#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

//custom lib
#include "structs.h"
extern bool collision(GameState *game, char directrion);

//load function
void loadGame(GameState *game) {


    //player surface
    SDL_Surface *playerSurface = NULL;

	//load image and create texture
	playerSurface = IMG_Load("../res/wr0.png");
	if(playerSurface == NULL) {
		printf("cannot find img!\n\n");
		SDL_Quit();
		exit(1);
	}
	

	game->player.wr0 = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//set player variables
	game->player.x = 220;
	game->player.y = 140;


}





void doRender(GameState *game) {

	//background color
	SDL_SetRenderDrawColor(game->rend, 50, 140, 50, 255);

	//clear the screen
	SDL_RenderClear(game->rend);


	//draw player postion
	SDL_Rect playerRect = {game->player.x, game->player.y, 100, 100};
	SDL_RenderCopy(game->rend, game->player.wr0, NULL, &playerRect);
	

	//when done drawing, present drawing
	SDL_RenderPresent(game->rend);

}

int processEvents(SDL_Window *window, GameState *game){

	SDL_Event event;
	int notDone = true;

	while(SDL_PollEvent(&event)){
		switch(event.type){
			
			case SDL_QUIT:
				SDL_DestroyWindow(window);
				window = NULL;
				notDone = false;
				break;

		}
	}


	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if(state[SDL_SCANCODE_LEFT] & !collision(game , 'L')){
		game->player.x -= 10;
	}

	if(state[SDL_SCANCODE_RIGHT] & !collision(game , 'R')){
		game->player.x += 10;
	}

	if(state[SDL_SCANCODE_UP] & !collision(game , 'U')){
		game->player.y -= 10;
	}

	if(state[SDL_SCANCODE_DOWN] & !collision(game , 'D')){
		game->player.y += 10;
	}

	return notDone;
}



int main(int argc, const char *argv[]){

	//contains all game objects
	GameState game;

	//set window size
	game.windowSize.x = 640;
	game.windowSize.y = 480;

	//set player area
	game.player.area = 100;


	//signal that game is on
	game.running = true;

	SDL_Window *window; 		//decalre window
	SDL_Event event;    		//decalre event
	SDL_Renderer *rend;
	

	SDL_Init(SDL_INIT_VIDEO);	 //start sdl2

	

	window = SDL_CreateWindow("game",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  game.windowSize.x,
							  game.windowSize.y,
							  0);

	game.rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		



	loadGame(&game);



	printf("game is on\n");


	while(game.running == true){
		
		//run input and continue or quit the game
		game.running = processEvents(window, &game);
		
		//render the game
		doRender(&game);
		

	}

	//close everything and quit
	printf("terminating game...\n");
	SDL_DestroyTexture(game.player.wr0);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(game.rend);
	SDL_Quit();
	return 0;


}