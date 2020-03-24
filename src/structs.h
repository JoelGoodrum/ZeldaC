//code from https://www.youtube.com/watch?v=NTKjjqIzvd4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=10

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

//player obj
typedef struct 
{
	int x , y;  // player position
	int area;	// player area	
	int health; // player health

	//animation frames

	//walking right
	//w for walking, r,l,u,d for direction
	SDL_Texture *wr[2]; // wr[0] will be standing still, wr[1] will be moving
	SDL_Texture *wl[2];
	SDL_Texture *wu[2];
	SDL_Texture *wd[2];
	
	SDL_Texture *currentText; //current texture of character

} Player;

//enemy textures
typedef struct 
{
	SDL_Texture *skeleton;
} EnemyTextures;

//enemies obj
typedef struct 
{
	int x , y;
	int area;
	int health;
	int attack; //attack is how much health they take from player	
} Enemy;


//map textures
typedef struct 
{
	SDL_Texture *tree;
} MapTextures;


//in game objects
typedef struct 
{
	int x , y; //position
	int area;
} GameObj;


//window obj
typedef struct 
{
	int x , y;
} WindowSize;


//heads up display obj
typedef struct 
{
	//rendererd string
	SDL_Texture *label;

	//fonts
	TTF_Font *font;
} HUD;

	
//game state struct
typedef struct 
{
	// ## GAME ## //

	WindowSize windowSize;  		// game window size
	HUD hud;  						// head ups display data
	SDL_Renderer *rend;     		// renderer
	bool running; 					// check if game is running
	int time; 						// keep track of time to organize frames
	int scrollX, scrollY;   		// mv camera
	Player player;  
	int numbOfSkel;        		// player obj
	Enemy skeleton[1];					// enemy obj
	EnemyTextures enemyTextures; 	// enemy texture


	// ## MAP ## //

	int numbOfTrees; 			// needs to be set to two in load game function
	GameObj tree[2]; 			// tree objects, two are currently set
	MapTextures mapTextures; 	//map textures



	


} GameState;

void collision(GameState *game, GameObj *obj, int arrSize);
void animate(GameState *game, char direction);
void loadPlayerTextures(GameState *game);
void loadSkeletonTextures(GameState *game);
void loadFonts(GameState *game);
void drawMap(GameState *game);
void drawPlayer(GameState *game);
void drawEnemies(GameState *game);
void drawHUD(GameState *game);