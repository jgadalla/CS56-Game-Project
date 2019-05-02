/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Button.hpp"
#include "Unit.hpp"
#include "Queue.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 792;
const int SCREEN_HEIGHT = 469;

//road intersection locations
 const int XMID = SCREEN_WIDTH/2;
 const int YMID = SCREEN_HEIGHT/2;
 const int XMAX = SCREEN_WIDTH;
 const int YMAX = SCREEN_HEIGHT;

 //direction locations clockwise 
 int north = 0;
 int east = 1;
 int west = 2;
 int south = 3;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

//Scene textures
LTexture startTexture;
LTexture gameTexture;
LTexture carTexture;

int check_click_in_rect(int x, int y, SDL_Rect *rect)
{
	/* Check X coordinate is within rectangle range */
	if (x >= rect->x && x < (rect->x + rect->w))
	{
		/* Check Y coordinate is within rectangle range */
		if (y >= rect->y && y < (rect->y + rect->h))
		{
			/* X and Y is inside the rectangle */
			return 1;
		}
	}

	/* X or Y is outside the rectangle */
	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{

		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Sixth Street Scramble", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface into textures

	if (!startTexture.loadFromFile("Images/Start-Screen.png", gRenderer))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!gameTexture.loadFromFile("Images/roadtile.png", gRenderer))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	if (!carTexture.loadFromFile("Images/red.png", gRenderer))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	gameTexture.free();
	startTexture.free();

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char *args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;
			bool start_screen = true;

			long int frame = 0;

			Button *start_button = new Button(286, 132);
			Queue southList;
			Queue northList;
			Queue eastList;
			Queue westList;
			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				if (frame%240 == 0){
					Unit* southCar = new Unit(&carTexture, (float)SCREEN_WIDTH/2 - 30, -50);
					southList.Enqueue(southCar);
				}
	
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_KEYDOWN)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);
						SDL_Rect currRect = start_button->getRect();
						if (e.type == SDL_MOUSEBUTTONUP && check_click_in_rect(x, y, &currRect))
						{
							start_screen = false;
						}

						const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

						if (currentKeyStates[SDLK_ESCAPE])
						{
							quit = true;
						}
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				if (start_screen)
				{
					// SDL_BlitSurface( gStartSurface, NULL, gScreenSurface, NULL );
					startTexture.render(0, 0, startTexture.getTexRect(0, 0), 0.0, NULL, SDL_FLIP_NONE, gRenderer);
					start_button->render(gRenderer);
				}
				if(!start_screen)
				{
					// SDL_BlitSurface( gGameSurface, NULL, gScreenSurface, NULL );
					gameTexture.render(0, 0, gameTexture.getTexRect(0, 0), 0.0, NULL, SDL_FLIP_NONE, gRenderer);
					southList.Render(gRenderer);
					southList.Move();
				}
				//Update the surface
				//SDL_UpdateWindowSurface( gWindow );
				SDL_RenderPresent(gRenderer);

				++frame;
			}
			delete start_button;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}