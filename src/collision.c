
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>


//custom lib
#include "structs.h"

extern void drawSpeechBubble(GameState *game, MapAsset *character);


// collision detection out of bounds
// returns true if there is an object in the way
void collision(GameState *game, MapAsset *obj, int arrSize) {

	WindowSize *win = &game->windowSize;

	Player *player= &game->player;
	float playerY = (float)player->y;
	float playerX = (float)player->x;
	float playerA = (float)player->area;

	int pushEnemies = 200;
	float enemyPush = 50;

	//loop all objects to see if there is collision
	for(int i = 0; i < arrSize; i++){

		
		float objY = (float)obj[i].y;
		float objX = (float)obj[i].x;
		float objA = (float)obj[i].area;
		

		//if obj and player are on the same y axis
		if(playerY + playerA > objY && playerY < (objY + objA)){
		
			//rubbing againts right edge
			if(playerX < (objX + objA) && (playerX + playerA) > (objX + objA)){
				
				//if is character
				if(obj->assetType == 1){
					drawSpeechBubble(game, &obj[i]);

					//correct playerX
					game->player.x = (int)(objX + objA);
					playerX = objX + objA;
				}
			

				//if is enemy
				else if(obj->assetType == 2 && obj->health > 0){

					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->x = obj->x - pushEnemies;
						obj->health = obj->health - obj->attack;

						obj->isDamaged = true;
						obj->damageTime = 1;
					} 

					else {
						//correct playerX
						game->player.x = (int)(objX + objA + enemyPush);
						playerX = objX + objA + enemyPush;
						game->player.health = game->player.health - obj[i].attack; 		//remove health from player
					}
					
				}

				else if(obj->assetType == 0) {
					//correct playerX
					game->player.x = (int)(objX + objA);
					playerX = objX + objA;
				}
			}
			

			//rubbing againts left edge
			else if(playerX + playerA > objX && playerX < objX){
				
				if(obj->assetType == 1){
					drawSpeechBubble(game, &obj[i]);

					//correct playerX
					game->player.x = (int)(objX - playerA);
					playerX = objX - objA;
				}


				else if(obj->assetType == 2 && obj->health > 0){

					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->x = obj->x + pushEnemies;
						obj->health = obj->health - obj->attack;
						obj->isDamaged = true;
						obj->damageTime = 1;
					}

					else{
						//correct playerX
						game->player.x = (int)(objX - playerA - enemyPush);
						playerX = objX - objA - enemyPush;
						game->player.health = game->player.health - obj[i].attack;		//remove health from player
				
					}
				}

				else if(obj->assetType == 0) {
					//correct playerX
					game->player.x = (int)(objX - playerA);
					playerX = objX - objA;
				}
			}
			
		}
		

		
		//if obj and player are on the same x axis
		if ( (playerX + (playerA/2)) > objX && playerX + (playerA/2) < (objX + objA)) {

			//if bumping head
			if(playerY < (objY + objA) && player->y > objY){

				if(obj->assetType == 1){
					drawSpeechBubble(game, &obj[i]);

					//correct y
					game->player.y = (int)(objY + objA);
					playerY = objY + objA;
				}
				


				else if(obj->assetType == 2 && obj->health > 0){

					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->y = obj->y - pushEnemies;
						obj->health = obj->health - obj->attack;
						obj->isDamaged = true;
						obj->damageTime = 1;
					}

					else {
						//correct y
						game->player.y = (int)(objY + objA + enemyPush);
						playerY = objY + objA + enemyPush;
						game->player.health = game->player.health - obj[i].attack;
					}
				}

				else if(obj->assetType == 0){
					//correct y
					game->player.y = (int)(objY + objA);
					playerY = objY + objA;
				}

			}
			
			//if bumping feet
			else if(playerY + playerA > objY && playerY < objY){

				if(obj->assetType == 1){
					drawSpeechBubble(game, &obj[i]);

					//correct y
					game->player.y = (int)(objY - playerA);
					playerY = objY - playerA;
				}

				

				else if(obj->assetType == 2 && obj->health > 0){
					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->y = obj->y + pushEnemies;
						obj->health = obj->health - obj->attack;
						obj->isDamaged = true;
						obj->damageTime = 1;
					}

					else {
						//correct y
						game->player.y = (int)(objY - playerA);
						playerY = objY - playerA - enemyPush;
						game->player.health = game->player.health - obj[i].attack;
					}
				}

				else if(obj->assetType == 0) {
					//correct y
					game->player.y = (int)(objY - playerA);
					playerY = objY - playerA;
				}

			}

		}

	}
	
}


//code from  https://www.youtube.com/watch?v=yUiZcWHOfW4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=12

// animate
void animate(GameState *game, char direction) {

	Textures *textures = &game->textures;
	int frameFreq = 8;

	if(direction == 'R'){

		if(game->time % frameFreq == 0){
		
			if(textures->playerCText == textures->wr[0]){
				
				textures->playerCText = textures->wr[1];
			}

			else {
				textures->playerCText = textures->wr[0];
			}
		}
		
	}

	if(direction == 'L'){

		if(game->time % frameFreq == 0){
		
			if(textures->playerCText == textures->wl[0]){
				
				textures->playerCText = textures->wl[1];
			}

			else {
				textures->playerCText = textures->wl[0];
			}
		}
		
	}

	if(direction == 'U'){

		if(game->time % frameFreq == 0){
		
			if(textures->playerCText == textures->wu[0]){
				
				textures->playerCText = textures->wu[1];
			}

			else {
				textures->playerCText = textures->wu[0];
			}
		}
		
	}

	if(direction == 'D'){

		if(game->time % frameFreq == 0){
		
			if(textures->playerCText == textures->wd[0]){
				
				textures->playerCText = textures->wd[1];
			}

			else {
				textures->playerCText = textures->wd[0];
			}
		}
		
	}

}

//see if player is in range of enemy in the y axis
bool withInY(float playerY, float enemyY, float approach){
	 	//withing y axis when player is above					//withing y axis when player is below
	if( (playerY <= enemyY && enemyY - approach <= playerY) || (playerY >= enemyY && enemyY + approach >= playerY) ){
			return true;
	}
	return false;
}

//see if player is in range of enemy in the x axis
bool withInX(float playerX, float enemyX, float approach){
	 	//withing x axis when player is to the right					//withing x axis when player is left of enemy
	if( (enemyX <= playerX && enemyX + approach >= playerX) || (playerX <= enemyX && enemyX - approach <= playerX) ){
			return true;
	}
	return false;
}

//enemy moves towards player after certain distance
void enemyMovement(GameState *game, MapAsset *enemy, int arrSize){
	
	Player *player= &game->player;

	//import player position
	float playerY = (float)player->y;
	float playerX = (float)player->x;

	for(int i = 0; i < arrSize; i++){	

		//set enemy vars
		float enemyY = (float)enemy[i].y;
		float enemyX = (float)enemy[i].x;
		float approach = (float)enemy[i].approach;
		float speed = (float)enemy[i].speed;

		//player is to the right of enemy
		if(enemyX < playerX && withInX(playerX, enemyX, approach) && withInY(playerY, enemyY, approach)){
			enemyX += speed;
			enemy[i].x += speed;
		}

		//player is to the left of enemy 
		if(playerX < enemyX && withInX(playerX, enemyX, approach) && withInY(playerY, enemyY, approach)){
			enemyX -= speed;
			enemy[i].x -= speed;
		}

		//player is above the enemy
		if(playerY < enemyY && withInX(playerX, enemyX, approach) && withInY(playerY, enemyY, approach)){
			enemyY -= speed;
			enemy[i].y -= speed;
		}

		//player is below the enemy 
		if(playerY > enemyY && withInX(playerX, enemyX, approach) && withInY(playerY, enemyY, approach)){
			enemyY += speed;
			enemy[i].y += speed;
		}

	}

}

void attackAnimation(GameState *game, bool pressed, char direction){

	Textures *textures = &game->textures;


	if(direction == 'D'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			textures->playerCText = textures->ad;
			game->player.isAttack = true;

	}

	if(direction == 'U'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			textures->playerCText = textures->au;
			game->player.isAttack = true;

	}

	if(direction == 'L'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			textures->playerCText = textures->al;
			game->player.isAttack = true;

	}

	
	if(direction == 'R'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			textures->playerCText = textures->ar;
			game->player.isAttack = true;

	}

	

	

}

void deAttackAnimation(GameState *game, char direction){
	
	Textures *textures = &game->textures;

	if(direction == 'D'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		textures->playerCText = textures->wd[0];

	}

	if(direction == 'U'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		textures->playerCText = textures->wu[0];

	}

	if(direction == 'L'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		textures->playerCText = textures->wl[0];

	}

	if(direction == 'R'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		textures->playerCText = textures->wr[0];

	}

}

void animateEnemies(GameState *game, MapAsset *enemy, int enemyNumb){

	

	int frameFreq = 60;

	//iterate all skeletons
	for(int i = 0; i < enemyNumb; i++){
		if(enemy[i].isDamaged){

			//display damaged frame
			enemy[i].currentText = 1; // indicy of texture array

			//progress damaged timer
			if(game->time % frameFreq == 0){
				enemy[i].damageTime -= 1;
			} 

			// if damaged time hits 0, enemy isnt damaged anymore
			if(enemy[i].damageTime == 0){
				enemy[i].isDamaged = false;
				enemy[i].currentText = 0;
			}
		}

	}

}
