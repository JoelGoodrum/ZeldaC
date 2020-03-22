#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

typedef struct 
{
	// position
	int x , y;

	//area
	int area;		

	//images
	SDL_Texture *wr0; //standing right idle

} Player;

typedef struct 
{
	int x , y;
} WindowSize;


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


} GameState;

bool collision(GameState *game, char direction);