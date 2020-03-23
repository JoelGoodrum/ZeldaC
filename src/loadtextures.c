#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
//custom lib
#include "structs.h"


//make texture out of images
void loadPlayerTextures(GameState *game ){


    //load image and create texture//
    SDL_Surface *playerSurface;

    //#######################################//
    char *path = "../res/wr0.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wr[0] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#######################################//
    path = "../res/wl0.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wl[0] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#######################################//
    path = "../res/wd0.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wd[0] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#######################################//
    path = "../res/wu0.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wu[0] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#####################################//
	//#####################################//
	//#####################################//

	//#######################################//
    path = "../res/wr1.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wr[1] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#######################################//
    path = "../res/wl1.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wl[1] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#######################################//
    path = "../res/wd1.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wd[1] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#######################################//
    path = "../res/wu1.png";

	playerSurface = IMG_Load(path);
	if(playerSurface == NULL) {
		printf("cannot find %s: \n", path);
		SDL_Quit();
		exit(1);
	}
	
	game->player.wu[1] = SDL_CreateTextureFromSurface(game->rend, playerSurface);
	SDL_FreeSurface(playerSurface);

	//#### font texture ##########//
	game->hud.label = NULL;

}

//code from https://www.youtube.com/watch?v=8Z796HGwYLE&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=13
void loadFonts(GameState *game){
	game->hud.font = TTF_OpenFont("../res/Peepo.ttf", 28);
	if(!game->hud.font){
		printf("font not found!\n");
		SDL_Quit();
		exit(1);
	}
}

//https://www.youtube.com/watch?v=JbtiCeKl1uo&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=14
void drawHUD(GameState *game){

	//make health string
	char healthStr[50] = "";
	sprintf(healthStr, "health: %d", game->player.health);

	//draw health
	SDL_Color red = { 180, 0, 0, 255};
	SDL_Surface *tmp = TTF_RenderText_Blended(game->hud.font, healthStr, red);
	game->hud.label = SDL_CreateTextureFromSurface(game->rend, tmp);
	
	SDL_Rect textRect = { 20, 15, tmp->w, tmp->h};
	SDL_RenderCopy(game->rend, game->hud.label, NULL, &textRect);


	//terminate hud
	SDL_FreeSurface(tmp);
	
}