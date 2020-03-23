
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>


//custom lib
#include "structs.h"


// collision detection out of bounds
// returns true if there is an object in the way
void collision(GameState *game) {

	WindowSize *win = &game->windowSize;


	Player *player= &game->player;
	float playerY = (float)player->y;
	float playerX = (float)player->x;
	float playerA = (float)player->area;

	Tree *tree = &game->gameObj.tree;
	float treeY = (float)tree->y;
	float treeX = (float)tree->x;
	float treeA = (float)tree->area;
	

	//if tree and player are on the same y axis
	if(playerY + playerA > treeY && playerY < (treeY + treeA)){

		
		//rubbing againts right edge
		if(playerX < (treeX + treeA) && (playerX + playerA) > (treeX + treeA)){
			
			//correct playerX
			game->player.x = (int)(treeX + treeA);
			playerX = treeX + treeA;
		}
		

		//rubbing againts left edge
		else if(playerX + playerA > treeX && playerX < treeX){
			
			//correct playerX
			game->player.x = (int)(treeX - playerA);
			playerX = treeX - treeA;
		}

		
	}
	

	
	//if tree and player are on the same x axis
	if ( (playerX + (playerA/2)) > treeX && playerX + (playerA/2) < (treeX + treeA)) {

		//if bumping head
		if(playerY < (treeY + treeA) && player->y > treeY){
			
			//correct y
			game->player.y = (int)(treeY + treeA);
			playerY = treeY + treeA;

		}
		
		//if bumping feet
		else if(playerY + playerA > treeY && playerY < treeY){

			//correct y
			game->player.y = (int)(treeY - playerA);
			playerY = treeY - playerA;

		}
	}
	

			
	

	
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