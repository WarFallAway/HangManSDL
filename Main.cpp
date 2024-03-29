
#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<string>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
SDL_Window* gwindow = NULL;
SDL_Surface* gWindowSurface = NULL;




enum keyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};
SDL_Surface* gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

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
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL Error: %s\n", SDL_GetError());
				succes = false;
			}
			else {

				gWindowSurface = SDL_GetWindowSurface(gwindow);
			}
		}

	}
	return succes;
}

SDL_Surface* loadSurface(std::string path) {

	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unnable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gWindowSurface->format, 0);
		if (optimizedSurface == NULL) {
			printf("Unnable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

bool loadMedia() {
	bool succes = true;

	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("picturesForTest/default.png");

	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load image!\n");
		succes = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("picturesForTest/up.png");

	if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Failed to load image!\n");
		succes = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("picturesForTest/down.png");

	if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Failed to load image!\n");
		succes = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("picturesForTest/left.png");

	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Failed to load image!\n");
		succes = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("picturesForTest/right.png");

	if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Failed to load image!\n");
		succes = false;
	}

	return succes;
}

void close() {

	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	SDL_DestroyWindow(gwindow);

	gwindow = NULL;
	SDL_Quit();
}

//Individual image loading


//the images that correspondent to a keypress


//Current displayed image


int main(int argc, char* argv[]) {

	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (!loadMedia()) {
			printf("Failed to load image!\n");
		}
		else {
			

			bool quit = false;
			SDL_Event e; 

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {

						case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
						break;

						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;

						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
							break;

						}
					}
				}
				SDL_Rect StretchRect;
				StretchRect.x = 0;
				StretchRect.y = 0;
				StretchRect.w = WINDOW_WIDTH;
				StretchRect.h = WINDOW_HEIGHT;
				SDL_BlitScaled(gCurrentSurface, NULL, gWindowSurface, &StretchRect);
				SDL_UpdateWindowSurface(gwindow);
			}

		}
	}
	
	close();

	return 0;



}