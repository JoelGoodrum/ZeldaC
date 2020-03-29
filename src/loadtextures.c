#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
//custom lib
#include "structs.h"

extern void doRender(GameState *game);

void loadTexture(GameState *game, SDL_Texture** tmpTexture, char *path){


    //load image and create texture//
    SDL_Surface *tmpSurface;

	tmpSurface = IMG_Load(path);
	if(tmpSurface == NULL) {
		printf("cannot find: %s\n", path);
		SDL_Quit();
		exit(1);
	}
	
	*tmpTexture = SDL_CreateTextureFromSurface(game->rend, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

//make texture out of images
void loadPlayerTextures(GameState *game ){

	Textures *textures = &game->textures;

	loadTexture(game, &game->textures.wr[0], "../res/wr0.png");
	loadTexture(game, &game->textures.wl[0], "../res/wl0.png");
	loadTexture(game, &game->textures.wu[0], "../res/wu0.png");
	loadTexture(game, &game->textures.wd[0], "../res/wd0.png");

	loadTexture(game, &game->textures.wr[1], "../res/wr1.png");
	loadTexture(game, &game->textures.wl[1], "../res/wl1.png");
	loadTexture(game, &game->textures.wu[1], "../res/wu1.png");
	loadTexture(game, &game->textures.wd[1], "../res/wd1.png");

	loadTexture(game, &game->textures.ad, "../res/linkAttack/ad.png");
	loadTexture(game, &game->textures.au, "../res/linkAttack/au.png");
	loadTexture(game, &game->textures.al, "../res/linkAttack/al.png");
	loadTexture(game, &game->textures.ar, "../res/linkAttack/ar.png");

}

//load enemy textures
void loadSkeletonTextures(GameState *game){

	loadTexture(game, &game->textures.skeleton[0], "../res/skeleton/wd0.png");
	loadTexture(game, &game->textures.skeleton[1], "../res/skeleton/dd.png");

}

//load map textures
void loadMapTextures(GameState *game){

	loadTexture(game, &game->textures.tree, "../res/tree.png");


}

void loadCharacterTextures(GameState *game){

	loadTexture(game, &game->textures.characters[0], "../res/lostGuy.png");

}

//code from https://www.youtube.com/watch?v=8Z796HGwYLE&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=13
void loadFonts(GameState *game){
	game->hud.font = TTF_OpenFont("../res/Peepo.ttf", 28);
	game->gameOverFont = TTF_OpenFont("../res/Peepo.ttf", 68);
	if(!game->hud.font){
		printf("font not found!\n");
		SDL_Quit();
		exit(1);
	}
}

//code from https://www.youtube.com/watch?v=JbtiCeKl1uo&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=14



//draw map
void drawMap(GameState *game){

	int scrollX = game->scrollX;
	int scrollY = game->scrollY;
	Assets *assets = &game->assets;
	
	//background color
	SDL_SetRenderDrawColor(game->rend, 50, 140, 50, 255);

	//draw trees
	for(int i = 0; i < NUMB_OF_TREES; i++){
		SDL_Rect treeRect = {scrollX + assets->tree[i].x, scrollY + assets->tree[i].y, assets->tree[i].area, assets->tree[i].area};
		SDL_RenderCopy(game->rend, game->textures.tree, NULL, &treeRect);
	}
	
}

//draw player
void drawPlayer(GameState *game){

	int scrollX = game->scrollX;
	int scrollY = game->scrollY;

	//draw player at current postion
	SDL_Rect playerRect = {scrollX + game->player.x, scrollY + game->player.y, game->player.area, game->player.area};
	SDL_RenderCopy(game->rend, game->textures.playerCText, NULL, &playerRect);
}

void drawCharacters(GameState *game){

	int scrollX = game->scrollX;
	int scrollY = game->scrollY;
	Textures *textures = &game->textures;

	//draw all characters
	for(int i = 0; i < NUMB_OF_CHARACTERS; i++){

		MapAsset *character = &game->assets.characters[i];
		SDL_Rect charcaterRect = {scrollX + character[i].x, scrollY + character[i].y, character[i].area, character[i].area};
		SDL_RenderCopy(game->rend, textures->characters[character[i].currentText], NULL, &charcaterRect);

	}

}

void drawSkeletons(GameState *game){

	int scrollX = game->scrollX;
	int scrollY = game->scrollY;
	MapAsset *skeleton = game->assets.skeleton;

	//draw skeleton at current postion
	for(int i = 0; i < NUMB_OF_SKELS; i++){

		//draw skeleton if alive
		if(skeleton[i].health > 0){

			SDL_Rect skelRect = {scrollX + skeleton[i].x, scrollY + skeleton[i].y, 100, 100};
			SDL_RenderCopy(game->rend, game->textures.skeleton[skeleton[i].currentText], NULL, &skelRect);
		}

				
	}

}

//draw hud
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

void drawGameOver(GameState *game){

	//draw black background
	SDL_SetRenderDrawColor(game->rend, 10, 10, 10, 255);

	//clear screen
	SDL_RenderClear(game->rend);
	


	//draw is dead
	SDL_Color white = { 240, 240, 240, 255};

	SDL_Surface *tmp = TTF_RenderText_Blended(game->gameOverFont, "GAME OVER", white);
	game->hud.label = SDL_CreateTextureFromSurface(game->rend, tmp);
	
	SDL_Rect textRect = { (game->windowSize.x - tmp->w) / 2,  (game->windowSize.y - tmp->h) / 2, tmp->w, tmp->h};
	SDL_RenderCopy(game->rend, game->hud.label, NULL, &textRect);

	//terminate hud
	SDL_FreeSurface(tmp);
	
	SDL_RenderPresent(game->rend); //when done drawing, present drawing


}

void drawSpeechBubble(GameState *game, MapAsset *character){

	//make bubble rectangle
	int padding = 30;
	int bubbleH = 230;

	//draw speech bubble
	SDL_SetRenderDrawColor(game->rend, 0, 0, 150, 255);
	SDL_Rect bubbleRect = {padding , game->windowSize.y - (bubbleH +  padding), game->windowSize.x - (padding*2), bubbleH};
	SDL_RenderFillRect(game->rend, &bubbleRect);

	//draw speech
	SDL_Color white = { 240, 240, 240, 255};
	SDL_Surface *tmp = TTF_RenderText_Blended(game->hud.font, character->speech, white);
	game->hud.label = SDL_CreateTextureFromSurface(game->rend, tmp);
	
	SDL_Rect textRect = { padding * 2, game->windowSize.y - bubbleH + padding, tmp->w, tmp->h};
	SDL_RenderCopy(game->rend, game->hud.label, NULL, &textRect);

	//terminate hud
	SDL_FreeSurface(tmp);

	SDL_RenderPresent(game->rend);
	SDL_Delay(3000);
	doRender(game);
	
}