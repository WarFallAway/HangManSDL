
#include<stdio.h>
#include<SDL.h>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


int main(int argc, char* argv[]) {

	SDL_Window* window = NULL;
	SDL_Surface* WindowSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unnable to initialize SDL, SDL_ERROR: %s\n", SDL_GetError());
	}
	else {
		window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Unnable to create window, SDL ERROR: %s\n", SDL_GetError());
		}
		else {
			WindowSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(WindowSurface, NULL, SDL_MapRGB(WindowSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);

			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }

		}


	}
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;



}