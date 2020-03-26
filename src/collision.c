
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>


//custom lib
#include "structs.h"

extern void drawSpeechBubble(GameState *game, Character *character);


// collision detection out of bounds
// returns true if there is an object in the way
void collision(GameState *game, GameObj *obj, int arrSize) {

	WindowSize *win = &game->windowSize;

	Player *player= &game->player;
	float playerY = (float)player->y;
	float playerX = (float)player->x;
	float playerA = (float)player->area;

	//loop all objects to see if there is collision
	for(int i = 0; i < arrSize; i++){

		
		float objY = (float)obj[i].y;
		float objX = (float)obj[i].x;
		float objA = (float)obj[i].area;
		

		//if obj and player are on the same y axis
		if(playerY + playerA > objY && playerY < (objY + objA)){
		
			//rubbing againts right edge
			if(playerX < (objX + objA) && (playerX + playerA) > (objX + objA)){
				
				//correct playerX
				game->player.x = (int)(objX + objA);
				playerX = objX + objA;
			}
			

			//rubbing againts left edge
			else if(playerX + playerA > objX && playerX < objX){
				
				//correct playerX
				game->player.x = (int)(objX - playerA);
				playerX = objX - objA;
			}
			
		}
		

		
		//if obj and player are on the same x axis
		if ( (playerX + (playerA/2)) > objX && playerX + (playerA/2) < (objX + objA)) {

			//if bumping head
			if(playerY < (objY + objA) && player->y > objY){
				
				//correct y
				game->player.y = (int)(objY + objA);
				playerY = objY + objA;

			}
			
			//if bumping feet
			else if(playerY + playerA > objY && playerY < objY){

				//correct y
				game->player.y = (int)(objY - playerA);
				playerY = objY - playerA;

			}

		}

	}
	
}

//character collision: will delete this method later
void characterCollision(GameState *game, Character *obj, int arrSize) {

	WindowSize *win = &game->windowSize;

	Player *player= &game->player;
	float playerY = (float)player->y;
	float playerX = (float)player->x;
	float playerA = (float)player->area;

	//loop all objects to see if there is collision
	for(int i = 0; i < arrSize; i++){

		
		float objY = (float)obj[i].y;
		float objX = (float)obj[i].x;
		float objA = (float)obj[i].area;
		

		//if obj and player are on the same y axis
		if(playerY + playerA > objY && playerY < (objY + objA)){
		
			//rubbing againts right edge
			if(playerX < (objX + objA) && (playerX + playerA) > (objX + objA)){
				
				drawSpeechBubble(game, &obj[i]);

				//correct playerX
				game->player.x = (int)(objX + objA);
				playerX = objX + objA;
			}
			

			//rubbing againts left edge
			else if(playerX + playerA > objX && playerX < objX){
				

				//correct playerX
				game->player.x = (int)(objX - playerA);
				playerX = objX - objA;
			}
			
		}
		

		
		//if obj and player are on the same x axis
		if ( (playerX + (playerA/2)) > objX && playerX + (playerA/2) < (objX + objA)) {

			//if bumping head
			if(playerY < (objY + objA) && player->y > objY){

				

				//correct y
				game->player.y = (int)(objY + objA);
				playerY = objY + objA;

			}
			
			//if bumping feet
			else if(playerY + playerA > objY && playerY < objY){
				

				//correct y
				game->player.y = (int)(objY - playerA);
				playerY = objY - playerA;

			}

		}

	}
	
}

void enemyCollision(GameState *game, Enemy *obj, int arrSize) {

	WindowSize *win = &game->windowSize;
	int pushEnemies = 200;

	Player *player= &game->player;
	float playerY = (float)player->y;
	float playerX = (float)player->x;
	float playerA = (float)player->area;
	float enemyPush = 50;
				
	//loop all objects to see if there is collision
	for(int i = 0; i < arrSize; i++){

		
		float objY = (float)obj[i].y;
		float objX = (float)obj[i].x;
		float objA = (float)obj[i].area;
		
		//only do enemy collision if enemy is alive
		if(obj->health > 0){

			//if obj and player are on the same y axis
			if(playerY + playerA > objY && playerY < (objY + objA)){

				
				//rubbing againts right edge
				if(playerX < (objX + objA) && (playerX + playerA) > (objX + objA)){
					
					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->x = obj->x - pushEnemies;
						obj->health = obj->health - game->player.attack;

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
				

				//rubbing againts left edge
				else if(playerX + playerA > objX && playerX < objX){
					
					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->x = obj->x + pushEnemies;
						obj->health = obj->health - game->player.attack;
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

				
			}
			

			
			//if obj and player are on the same x axis
			if ( (playerX + (playerA/2)) > objX && playerX + (playerA/2) < (objX + objA)) {

				//if bumping head
				if(playerY < (objY + objA) && player->y > objY){

					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->y = obj->y - pushEnemies;
						obj->health = obj->health - game->player.attack;
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
				
				//if bumping feet
				else if(playerY + playerA > objY && playerY < objY){

					//if attackting, push enemy and remove health
					if(game->player.isAttack){
						obj->y = obj->y + pushEnemies;
						obj->health = obj->health - game->player.attack;
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
		
			}

		}
			
	}

}

//code from  https://www.youtube.com/watch?v=yUiZcWHOfW4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=12

// animate
void animate(GameState *game, char direction) {

	Player *player = &game->player;
	int frameFreq = 8;

	if(direction == 'R'){

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
void enemyMovement(GameState *game, Enemy *enemy, int arrSize){
	
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

	if(direction == 'D'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			game->player.currentText = game->player.ad;
			game->player.isAttack = true;

	}

	if(direction == 'U'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			game->player.currentText = game->player.au;
			game->player.isAttack = true;

	}

	if(direction == 'L'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			game->player.currentText = game->player.al;
			game->player.isAttack = true;

	}

	
	if(direction == 'R'){

		if(pressed == false){
			//adjust player axis according to img size diff between stading still frame and attack frame 
			game->player.x = game->player.x - 44;
			game->player.y = game->player.y - 44;
		}
		

			game->player.area = 202;
			game->player.currentText = game->player.ar;
			game->player.isAttack = true;

	}

	

	

}

void deAttackAnimation(GameState *game, char direction){
	
	if(direction == 'D'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		game->player.currentText = game->player.wd[0];

	}

	if(direction == 'U'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		game->player.currentText = game->player.wu[0];

	}

	if(direction == 'L'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		game->player.currentText = game->player.wl[0];

	}

	if(direction == 'R'){
		game->player.x = game->player.x + 44;
		game->player.y = game->player.y + 44;
		

		game->player.area = 115;
		game->player.isAttack = false;
		game->player.currentText = game->player.wr[0];

	}

}

void animateEnemies(GameState *game){

	
	int numbOfSkel = 1;
	int frameFreq = 60;

	//iterate all skeletons
	for(int i = 0; i < numbOfSkel; i++){
		if(game->skeleton[i].isDamaged){

			//display damaged frame
			game->skeleton[i].currentText = game->enemyTextures.damaged;

			//progress damaged timer
			if(game->time % frameFreq == 0){
				game->skeleton[i].damageTime -= 1;
			} 

			// if damaged time hits 0, enemy isnt damaged anymore
			if(game->skeleton[i].damageTime == 0){
				game->skeleton[i].isDamaged = false;
				game->skeleton[i].currentText = game->enemyTextures.skeleton;
			}
		}

	}

}
