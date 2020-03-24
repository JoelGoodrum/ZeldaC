//code from https://www.youtube.com/watch?v=NTKjjqIzvd4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=10


#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

//custom lib
#include "structs.h"

extern void collision(GameState *game, GameObj *obj, int arrSize);
extern void animate(GameState *game, char directrion);
extern void loadMapTextures(GameState *game);
extern void loadPlayerTextures(GameState *game);
extern void loadSkeletonTextures(GameState *game);
extern void loadFonts(GameState *game);
extern void drawMap(GameState *game);
extern void drawEnemies(GameState *game);
extern void drawHUD(GameState *game);
extern void drawPlayer(GameState *game);


//load function
void loadGame(GameState *game) {

	//player variables
	game->player.area = 100;  //set player area
	game->time = 0; 		  //start game time
	game->running = true;     //signal that game is on
	game->player.x = (game->windowSize.x / 2) - (game->player.area / 2); //start in the middle of x axis
	game->player.y = (game->windowSize.y / 2) - (game->player.area / 2); //start in the middle of y axis
	game->player.health = 100;

	// ## map variables ## 

	//tree variables
	game->numbOfTrees = 2;
	game->tree[0].x = 150;  //tree x position
	game->tree[0].y = 150;  //tree y position
	game->tree[0].area = 250;     //tree area

	game->tree[1].x = 400;  //tree x position
	game->tree[1].y = 150;  //tree y position
	game->tree[1].area = 250;     //tree area

	//skeleton variables
	game->numbOfSkel = 1;
	game->skeleton[0].x = 150;
	game->skeleton[0].y = -250;
	game->skeleton[0].area = 100;

	// ## load textures and fonts ## 
	loadPlayerTextures(game); 
	loadSkeletonTextures(game); 
	loadMapTextures(game);    
	loadFonts(game);		  

	//set first frame
	game->player.currentText = game->player.wd[0];

	//set scroll var
	game->scrollX = 0;

	
}

//render game condition on screen
void doRender(GameState *game) {	
	
	SDL_RenderClear(game->rend); 	//clear the screen

	//draw functions
	drawMap(game);
	drawEnemies(game);
	drawPlayer(game);
	drawHUD(game);

	SDL_RenderPresent(game->rend); //when done drawing, present drawing

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

	if(state[SDL_SCANCODE_LEFT]){
		animate(game, 'L');
		game->player.x -= playerSpeed;
	}

	else if(state[SDL_SCANCODE_RIGHT]){
		animate(game, 'R');
		game->player.x += playerSpeed;
	}

	else if(state[SDL_SCANCODE_UP]){
		animate(game, 'U');
		game->player.y -= playerSpeed;
		
	}

	else if(state[SDL_SCANCODE_DOWN]){
		animate(game, 'D');
		game->player.y += playerSpeed;
	}
	
	game->time++;
	game->time = game->time % 60;

	game->scrollX = -game->player.x + (game->windowSize.x / 2) - (game->player.area / 2);
	game->scrollY = -game->player.y + (game->windowSize.y / 2) - (game->player.area / 2);

	return notDone;
}

//close everything and quit
int terminateGame(GameState *game, SDL_Window *window){
	
	printf("terminating game...\n");

	//destroy player textures
	SDL_DestroyTexture(game->player.wr[0]);
	
	SDL_DestroyTexture(game->player.wu[0]);
	SDL_DestroyTexture(game->player.wl[0]);
	SDL_DestroyTexture(game->player.wd[0]);

	SDL_DestroyTexture(game->player.wr[1]);
	SDL_DestroyTexture(game->player.wu[1]);
	SDL_DestroyTexture(game->player.wl[1]);
	SDL_DestroyTexture(game->player.wd[1]);
	
	SDL_DestroyTexture(game->player.currentText);

	//destroy map textures
	SDL_DestroyTexture(game->mapTextures.tree);
	
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
	game.windowSize.x = 840;
	game.windowSize.y = 680;

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

		//process tree collision
		collision(&game, game.tree, game.numbOfTrees);

		//render the game
		doRender(&game);

	}

	return terminateGame(&game, window);

}