#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

#define NUMB_OF_TREES 43
#define NUMB_OF_SKELS 3
#define NUMB_OF_CHARACTERS 1


//player obj
typedef struct 
{
	int x , y;     // player position
	int area;	   // player area	
	int health;    // player health
	int attack;		//player attack
	bool isAttack; // true if spacebar is pressed
	char lastDirection; 

} Player;


//map textures
typedef struct 
{
	// ## player textures ## //
	//w for walking, r,l,u,d for direction
	SDL_Texture *wr[2]; // wr[0] will be standing still, wr[1] will be moving
	SDL_Texture *wl[2];
	SDL_Texture *wu[2];
	SDL_Texture *wd[2];

	//attack textures
	SDL_Texture *ad;
	SDL_Texture *au;
	SDL_Texture *al;
	SDL_Texture *ar;	
	SDL_Texture *playerCText; //current texture of character

	// Map Textures
	SDL_Texture *tree;

	//skeleton textures
	SDL_Texture *skeleton[2];

	//character textures
	SDL_Texture *characters[1]; //characters[0] is lost guy

} Textures;


//map object
typedef struct 
{
	int x , y;
	int area;
	int assetType; // 1: character, 2: enemy

	// enemy variables 
	int currentText; //indecie to which texture to use
	int health;
	int attack; //attack is how much health they take from player	
	int approach; //when player is at a certain distance, approach
	int speed;
	bool isDamaged; //when set true, skeleton frame changes
	int damageTime; //how long damaged animation is on

	// character variables
	char *speech;
	

} MapAsset;

//in game objects
typedef struct 
{

	//characters
	MapAsset lostGuy;
	MapAsset characters[NUMB_OF_CHARACTERS];

	MapAsset tree[NUMB_OF_TREES]; 		
	MapAsset skeleton[NUMB_OF_SKELS];				
	
} Assets;


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
	SDL_Renderer *rend;     		// renderer
	HUD hud;  	
	Player player;  				// player obj
	Textures textures; 				// map textures
	bool running; 					// check if game is running
	int time; 						// keep track of time to organize frames
	int scrollX, scrollY;   		// mv camera


	TTF_Font *gameOverFont;
	bool spacePressed;				// if space bar is pressed, set to ture
	Assets assets;					// load all in game assets

} GameState;


void collision(GameState *game, MapAsset *obj, int arrSize);
void animate(GameState *game, char direction);
void enemyMovement(GameState *game, MapAsset *enemy, int arrSize);

void loadPlayerTextures(GameState *game);
void loadSkeletonTextures(GameState *game);
void loadCharacterTextures(GameState *game);
void loadFonts(GameState *game);

void drawMap(GameState *game);
void drawPlayer(GameState *game);
void drawSkeletons(GameState *game);
void drawCharacters(GameState *game);
void drawHUD(GameState *game);
void drawGameOver(GameState *game);
void drawSpeechBubble(GameState *game, MapAsset *character);

void attackAnimation(GameState *game, bool pressed, char direction);
void deAttackAnimation(GameState *game, char direction);
void animateEnemies(GameState *game, MapAsset *enemy, int enemyNumb);

void loadTrees(GameState *game);