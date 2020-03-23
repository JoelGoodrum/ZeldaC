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
	// position
	int x , y;

	//area
	int area;		

	//health
	int health;

	//animation frames

	//walking right
	//w for walking, r,l,u,d for direction
	SDL_Texture *wr[2]; // wr[0] will be standing still, wr[1] will be moving
	SDL_Texture *wl[2];
	SDL_Texture *wu[2];
	SDL_Texture *wd[2];
	
	//current texture of character
	SDL_Texture *currentText;
	
	

} Player;

//window obj
typedef struct 
{
	int x , y;
} WindowSize;

//heads up display obj
typedef struct {
	//rendererd string
	SDL_Texture *label;

	//fonts
	TTF_Font *font;
} HUD;

	

typedef struct 
{

	//game window size
	WindowSize windowSize;

	//check if game is running
	bool running;

	//player struct
	Player player;

	//renderer
	SDL_Renderer *rend;

	// keep track of time to organize frames
	int time;

	HUD hud;


} GameState;

bool collision(GameState *game, char direction);
void animate(GameState *game, char direction);
void loadPlayerTextures(GameState *game);
void loadFonts(GameState *game);
void drawHUD(GameState *game);