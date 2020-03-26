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
extern void enemyCollision(GameState *game, Enemy *obj, int arrSize);
extern void characterCollision(GameState *game, Character *obj, int arrSize);
extern void animate(GameState *game, char directrion);
extern void enemyMovement(GameState *game, Enemy *enemy, int arrSize);

extern void loadMapTextures(GameState *game);
extern void loadPlayerTextures(GameState *game);
extern void loadSkeletonTextures(GameState *game);
extern void loadCharacterTextures(GameState *game);
extern void loadFonts(GameState *game);

extern void drawMap(GameState *game);
extern void drawEnemies(GameState *game);
extern void drawHUD(GameState *game);
extern void drawPlayer(GameState *game);
extern void drawGameOver(GameState *game);

extern void attackAnimation(GameState *game, bool pressed, char directrion);
extern void deAttackAnimation(GameState *game, char directrion);
extern void animateEnemies(GameState *game);
extern void drawCharacters(GameState *game);


//load function
void loadGame(GameState *game) {

	// ## load textures and fonts ## 
	loadPlayerTextures(game); 
	loadSkeletonTextures(game); 
	loadCharacterTextures(game);
	loadMapTextures(game);    
	loadFonts(game);		

	//game variables
	game->spacePressed = false;
	game->player.currentText = game->player.wd[0]; //set first frame
	game->scrollX = 0;							   //set scroll var

	//player variables
	game->player.area = 115;  //set player area
	game->time = 0; 		  //start game time
	game->running = true;     //signal that game is on
	game->player.x = (game->windowSize.x / 2) - (game->player.area / 2); //start in the middle of x axis
	game->player.y = (game->windowSize.y / 2) - (game->player.area / 2); //start in the middle of y axis
	game->player.health = 100;
	game->player.attack = 30;
	game->player.isAttack = false;
	game->player.lastDirection = 'D';

	//character variables
	//character[0] is lost guy
	game->lostGuy.x = 210;
	game->lostGuy.y = 350;
	game->lostGuy.area = 100;
	game->lostGuy.speech = "Hey?!?!  Can you please kill that skeleton up there?";
	game->characters[0] = game->lostGuy;
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
	game->skeleton[0].attack = 10;
	game->skeleton[0].approach = 500;
	game->skeleton[0].speed = 3;
	game->skeleton[0].health = 100;
	game->skeleton[0].isDamaged = false;
	game->skeleton[0].damageTime = 0;
	game->skeleton[0].currentText = game->enemyTextures.skeleton;
	
	
}

//render game condition on screen
void doRender(GameState *game) {	
	
	SDL_RenderClear(game->rend); 	//clear the screen

	//draw functions
	drawMap(game);	
	drawEnemies(game);
	
	drawPlayer(game);
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
							game->player.currentText = game->player.wr[0]; 
						}
						break;
						

					case SDLK_LEFT:
						if(!game->player.isAttack){
							game->player.currentText = game->player.wl[0];
						}
						break;

					case SDLK_UP:
						if(!game->player.isAttack){
							game->player.currentText = game->player.wu[0];
						}
						break;
					case SDLK_DOWN:
						if(!game->player.isAttack){
							game->player.currentText = game->player.wd[0];
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
	SDL_DestroyTexture(game->player.wr[0]);
	SDL_DestroyTexture(game->player.wu[0]);
	SDL_DestroyTexture(game->player.wl[0]);
	SDL_DestroyTexture(game->player.wd[0]);

	//destroy textures in movement
	SDL_DestroyTexture(game->player.wr[1]);
	SDL_DestroyTexture(game->player.wu[1]);
	SDL_DestroyTexture(game->player.wl[1]);
	SDL_DestroyTexture(game->player.wd[1]);

	//destroy attack textures
	
	SDL_DestroyTexture(game->player.currentText);
	SDL_DestroyTexture(game->mapTextures.tree);			//destroy map textures
	SDL_DestroyTexture(game->enemyTextures.skeleton);
	
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
		
	loadGame(&game);											//loads textures and player variables

	printf("game is running\n");

	while(game.running == true){

		game.running = processEvents(window, &game);			//run input and continue or quit the game
		enemyMovement(&game, game.skeleton, game.numbOfSkel);	//mv enemy towards player
		collision(&game, game.tree, game.numbOfTrees); 			//process tree collision
		characterCollision(&game, game.characters, 1);
		enemyCollision(&game, game.skeleton, game.numbOfSkel);	//process enemy collision
		animateEnemies(&game);
		doRender(&game);										//render the game
		ifGameOver(&game);										//check if player died

	}

	return terminateGame(&game, window);

}
