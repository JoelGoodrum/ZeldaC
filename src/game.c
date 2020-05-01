#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

//custom lib
#include "structs.h"



extern void collision(GameState *game, MapAsset *obj, int arrSize);

extern void animate(GameState *game, char directrion);
extern void enemyMovement(GameState *game, MapAsset *enemy, int arrSize);

extern void loadMapTextures(GameState *game);
extern void loadPlayerTextures(GameState *game);
extern void loadSkeletonTextures(GameState *game);
extern void loadCharacterTextures(GameState *game);
extern void loadFonts(GameState *game);

extern void drawMap(GameState *game);
extern void drawSkeletons(GameState *game);
extern void drawHUD(GameState *game);
extern void drawPlayer(GameState *game);
extern void drawGameOver(GameState *game);

extern void attackAnimation(GameState *game, bool pressed, char directrion);
extern void deAttackAnimation(GameState *game, char directrion);
extern void animateEnemies(GameState *game, MapAsset *enemy, int enemyNumb);
extern void drawCharacters(GameState *game);

extern void loadTrees(GameState *game);


//load function
void loadGame(GameState *game) {

	// ## load textures and fonts ## 
	loadPlayerTextures(game); 
	loadSkeletonTextures(game); 
	loadCharacterTextures(game);
	loadMapTextures(game);    
	loadFonts(game);		

	Player *player = &game->player;
	Assets *assets = &game->assets;

	//game variables
	game->spacePressed = false;
	game->time = 0; 		  // start game time
	game->running = true;     // signal that game is on
	game->scrollX = 0;		  // center camera on player
	game->scrollY = 0;		  // center camera on player
	game->textures.playerCText = game->textures.wd[0]; 			//set first frame
	game->hud.label = NULL;

	//player variables
	player->area = 115;  								     //set player area
	player->x = (game->windowSize.x / 2) - (player->area / 2); //start in the middle of x axis
	player->y = (game->windowSize.y / 2) - (player->area / 2); //start in the middle of y axis
	player->health = 100;
	player->attack = 30;
	player->isAttack = false;
	player->lastDirection = 'D';


	// ## map assets ## 


	//character variables
	assets->lostGuy.assetType = 1;  //is character flag
	assets->lostGuy.x = 210;
	assets->lostGuy.y = 350;
	assets->lostGuy.area = 100;
	assets->lostGuy.speech = "Hey?!?!  Can you please kill that skeleton up there?";
	assets->characters[0] = assets->lostGuy;  	//character[0] is lost guy

	loadTrees(game);

	//skeleton variables

	for(int i = 0; i < 3; i++){

		assets->skeleton[i].assetType = 2;		//is enemy flag
		assets->skeleton[i].x = 150 + (i * 150 * 3);
		assets->skeleton[i].y = -250;
		assets->skeleton[i].area = 100;
		assets->skeleton[i].attack = 10;
		assets->skeleton[i].approach = 500;
		assets->skeleton[i].speed = 3;
		assets->skeleton[i].health = 20;
		assets->skeleton[i].isDamaged = false;
		assets->skeleton[i].damageTime = 0;
		assets->skeleton[i].currentText = 0; 	

	}

	
}


//render game condition on screen
void doRender(GameState *game) {	
	
	SDL_RenderClear(game->rend); 	//clear the screen

	//draw functions
	drawMap(game);	
	
	drawPlayer(game);
	drawSkeletons(game);
	drawCharacters(game);
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

		
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_SPACE:
						attackAnimation(game, game->spacePressed, game->player.lastDirection);
						game->spacePressed = true;
						break;
						
				}
				break;

			//set standing still frame
			case SDL_KEYUP:
				switch(event.key.keysym.sym){

					case SDLK_RIGHT:
						if(!game->player.isAttack){
							game->textures.playerCText = game->textures.wr[0]; 
						}
						break;
						

					case SDLK_LEFT:
						if(!game->player.isAttack){
							game->textures.playerCText = game->textures.wl[0];
						}
						break;

					case SDLK_UP:
						if(!game->player.isAttack){
							game->textures.playerCText = game->textures.wu[0];
						}
						break;
					case SDLK_DOWN:
						if(!game->player.isAttack){
							game->textures.playerCText = game->textures.wd[0];
						}
						break;

					case SDLK_SPACE:
						deAttackAnimation(game, game->player.lastDirection);
						game->spacePressed = false;
						break;
				
				}
				break;

		}
	}


	int playerSpeed = 7; //how fast player moves

										//does not allow to mv and atk at the same time
	if(state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_SPACE]){
		animate(game, 'L');
		game->player.x -= playerSpeed;
		game->player.lastDirection = 'L';
	}

	else if(state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_SPACE]){
		animate(game, 'R');
		game->player.x += playerSpeed;
		game->player.lastDirection = 'R';
	}

	else if(state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_SPACE]){
		animate(game, 'U');
		game->player.y -= playerSpeed;
		game->player.lastDirection = 'U';
		
	}

	else if(state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_SPACE]){
		animate(game, 'D');
		game->player.y += playerSpeed;
		game->player.lastDirection = 'D';
	}
	
	game->time++;
	game->time = game->time % 60;

	game->scrollX = -game->player.x + (game->windowSize.x / 2) - (game->player.area / 2);
	game->scrollY = -game->player.y + (game->windowSize.y / 2) - (game->player.area / 2);

	return notDone;
}


//player is dead 
void ifGameOver(GameState *game){
	
	if(game->player.health < 1){
		SDL_Delay(500);
		drawGameOver(game);
		SDL_Delay(2000);
		SDL_RenderClear(game->rend);
		//start from begenning
		loadGame(game);
	}
	
}


//close everything and quit
int terminateGame(GameState *game, SDL_Window *window){
	
	printf("terminating game...\n");

	//destroy player textures standing still
	SDL_DestroyTexture(game->textures.wr[0]);
	SDL_DestroyTexture(game->textures.wu[0]);
	SDL_DestroyTexture(game->textures.wl[0]);
	SDL_DestroyTexture(game->textures.wd[0]);

	//destroy textures in movement
	SDL_DestroyTexture(game->textures.wr[1]);
	SDL_DestroyTexture(game->textures.wu[1]);
	SDL_DestroyTexture(game->textures.wl[1]);
	SDL_DestroyTexture(game->textures.wd[1]);

	//destroy attack textures
	
	SDL_DestroyTexture(game->textures.playerCText);
	SDL_DestroyTexture(game->textures.tree);			//destroy map textures
	SDL_DestroyTexture(game->textures.skeleton[0]);
	SDL_DestroyTexture(game->textures.skeleton[1]);
	
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

//code from https://www.youtube.com/watch?v=NTKjjqIzvd4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=10
//boot game
int main(int argc, const char *argv[]){

	GameState game;				//contains all game objects

	//set window size
	game.windowSize.x = 1180;
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
		
	loadGame(&game);											// loads textures and player variables

	printf("game is running\n");

	while(game.running == true){

		game.running = processEvents(window, &game);			// run input and continue or quit the game
		
		
		enemyMovement(&game, game.assets.skeleton, NUMB_OF_SKELS);	// mv enemy towards player
		
		collision(&game, game.assets.tree, NUMB_OF_TREES); 			// process tree collision
		collision(&game, game.assets.characters, NUMB_OF_CHARACTERS);
		collision(&game, game.assets.skeleton, NUMB_OF_SKELS);		// process enemy collision
		
		animateEnemies(&game, game.assets.skeleton, NUMB_OF_SKELS);
		
		doRender(&game);										// render the game
		ifGameOver(&game);										// check if player died

	}

	return terminateGame(&game, window);

}
