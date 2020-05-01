#include<stdio.h>
#include "structs.h"

void loadTrees(GameState *game){

	Assets *assets = &game->assets;

	//tree variables

	// 2 trees

	//large tress
	assets->tree[0].x = 150;  //tree x position
	assets->tree[0].y = 150;  //tree y position
	assets->tree[0].area = 250;     //tree area
	assets->tree[0].assetType = 0;

	assets->tree[1].x = 400;  //tree x position
	assets->tree[1].y = 150;  //tree y position
	assets->tree[1].area = 250;     //tree area
	assets->tree[1].assetType = 0;


	// 10 trees 
	
	//border trees right 2 - 21
	for(int i = 2; i < 12; i++){
		assets->tree[i].x = 1200;  //tree x position
		assets->tree[i].y = -1200 + ((i - 1) * 200);  //tree y position
		assets->tree[i].area = 200;     //tree area
		assets->tree[i].assetType = 0;
	
	}

	//10 trees
	
	//border trees left 22 - 42 
	for(int i = 12; i < 21; i++){
		assets->tree[i].x = -1000 ;  //tree x position
		assets->tree[i].y = -1000 + ((i - 11) * 200);  //tree y position
		assets->tree[i].area = 200;     //tree area
		assets->tree[i].assetType = 0;

		
	}


	//12 trees

	//border trees top
	for(int i = 21; i < 32; i++){

		assets->tree[i].x = -1000 + ((i - 20) * 200);  //tree x position
		assets->tree[i].y = -800;  //tree y position
		assets->tree[i].area = 200;     //tree area
		assets->tree[i].assetType = 0;
		
	}

	//12 trees

	//border trees top
	for(int i = 32; i < 43; i++){

		assets->tree[i].x = -1000 + ((i - 31) * 200);  //tree x position
		assets->tree[i].y = 900;  //tree y position
		assets->tree[i].area = 200;     //tree area
		assets->tree[i].assetType = 0;
	
		
	}
	




}