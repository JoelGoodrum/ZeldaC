//code from https://www.youtube.com/watch?v=NTKjjqIzvd4&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=10


#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct 
{
	int x , y;		
} Player;

typedef struct 
{
	int x , y;
} Star;

typedef struct 
{
	//check if game is running
	bool running;

	//player struct
	Player player;

	//stars
	Star stars[5];

	//images
	SDL_Texture *star;	

	//renderer
	SDL_Renderer *rend;

} GameState;


//load function
void loadGame(GameState *game) {

	//set player variables
	game->player.x = 220;
	game->player.y = 140;

	//declare star surface
    SDL_Surface *starSurface;	

	//load image and create texture
	starSurface = IMG_Load("../res/star.png");
	if(starSurface == NULL) {
		printf("cannot find star.png!\n\n");
		SDL_Quit();
		exit(1);
	}

	game->star = SDL_CreateTextureFromSurface(game->rend, starSurface);
	SDL_FreeSurface(starSurface);

}





void doRender(GameState *game) {

	//background color
	SDL_SetRenderDrawColor(game->rend, 0, 0, 255, 255);

	//clear the screen
	SDL_RenderClear(game->rend);

	//set drawing to white
	SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);

	//draw player postion
	SDL_Rect rect = {game->player.x, game->player.y, 100, 100};
	SDL_RenderFillRect(game->rend, &rect);

	//draw star img
	SDL_Rect starRect = { 50, 50, 64, 64};
	SDL_RenderCopy(game->rend, game->star, NULL, &starRect);

	//when done drawing, present drawing
	SDL_RenderPresent(game->rend);

	//dont burn up the cpu
	//SDL_Delay(25);
}

int processEvents(SDL_Window *window, GameState *game){

	SDL_Event event;
	int notDone = true;

	while(SDL_PollEvent(&event)){
		switch(event.type){
			
			case SDL_QUIT:
				SDL_DestroyWindow(window);
				window = NULL;
				notDone = false;
				break;

		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_LEFT]){
		game->player.x -= 10;
	}
	if(state[SDL_SCANCODE_RIGHT]){
		game->player.x += 10;
	}
	if(state[SDL_SCANCODE_UP]){
		game->player.y -= 10;
	}
	if(state[SDL_SCANCODE_DOWN]){
		game->player.y += 10;
	}

	return notDone;
}


int main(int argc, const char *argv[]){

	//contains all game objects
	GameState game;

	//signal that game is on
	game.running = true;

	SDL_Window *window; 		//decalre window
	SDL_Event event;    		//decalre event
	

	SDL_Init(SDL_INIT_VIDEO);	 //start sdl2

	

	window = SDL_CreateWindow("game",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  640,
							  480,
							  0);

	game.rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	loadGame(&game);

	printf("game is on\n");


	while(game.running == true){
		
		game.running = processEvents(window, &game);
		doRender(&game);

	}

	//close everything and quit
	printf("terminating game...\n");
	SDL_DestroyTexture(game.star);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(game.rend);
	SDL_Quit();
	return 0;


}