//code from https://www.youtube.com/watch?v=J8qH-JLe2Ys&list=PLT6WFYYZE6uLMcPGS3qfpYm7T_gViYMMt&index=8


#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct 
{
	int x;
	int y;		
} Player;

void doRender(SDL_Renderer *rend, Player *player) {
	SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);

	//clear the screen
	SDL_RenderClear(rend);

	//set drawing to white
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

	SDL_Rect rect = {player->x, player->y, 200, 200};
	SDL_RenderFillRect(rend, &rect);

	//when done drawing, present drawing
	SDL_RenderPresent(rend);

	//dont burn up the cpu
	SDL_Delay(100);
}

int processEvents(SDL_Window *window, Player *player){

	SDL_Event event;
	int notDone = true;

	while(SDL_PollEvent(&event)){
		switch(event.type){
			
			case SDL_QUIT:
				SDL_DestroyWindow(window);
				window = NULL;
				notDone = false;
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_RIGHT:
						player->x += 10;
						break;

					case SDLK_LEFT:
						player->x -= 10;
						break;
				}
				

		}
	}

	return notDone;
}


int main(int argc, const char *argv[]){

	bool on = true;
	SDL_Window *window; //decalre window
	SDL_Renderer *rend; //delcare renderer
	SDL_Event event;    //decalre event

	SDL_Init(SDL_INIT_VIDEO);	 //start sdl2

	Player player;
	player.x = 220;
	player.y = 140;

	window = SDL_CreateWindow("game",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  640,
							  480,
							  0);

	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	

	printf("game is on\n");
	while(on == true){
		
		on = processEvents(window, &player);
		doRender(rend, &player);

	}

	//close everything and quit
	printf("terminating game...\n");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	return 0;


}