
#include<stdio.h>
#include<SDL.h>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
SDL_Window* gwindow = NULL;
SDL_Surface* gWindowSurface = NULL;
SDL_Surface* gGameOver = NULL;


bool init() {
	bool succes = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unnable to initialize SDL, SDL_ERROR: %s\n", SDL_GetError());
		succes = false;
	}
	else {
		gwindow = SDL_CreateWindow("HangMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (gwindow == NULL) {
			printf("Unnable to create window, SDL ERROR: %s\n", SDL_GetError());
			succes = false;
		}
		else {
			gWindowSurface = SDL_GetWindowSurface(gwindow);
		}

	}
	return succes;
}

bool loadMedia() {
	bool succes = true;

	gGameOver = SDL_LoadBMP("picturesForTest/Gamover.bmp");
	if (gGameOver == NULL) {
		printf("Unnable to load file! SDL Error is: %s\n", SDL_GetError());
		succes = false;
	}
	return succes;
}

void close() {

	SDL_FreeSurface(gGameOver);
	gGameOver = NULL;

	SDL_DestroyWindow(gwindow);

	gwindow = NULL;
	SDL_Quit();
}

int main(int argc, char* argv[]) {

	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (!loadMedia()) {
			printf("Failed to load image!\n");
		}
		else {
			SDL_BlitSurface(gGameOver, NULL, gWindowSurface, NULL);
			SDL_UpdateWindowSurface(gwindow);

			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	close();

	return 0;



}