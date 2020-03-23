#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

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

}