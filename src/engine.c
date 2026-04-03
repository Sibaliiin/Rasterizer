#include	<stdio.h>
#include	<stdlib.h>
#include	<SDL2/SDL.h>
#include	<stdbool.h>

#include	"engine.h"

// function definitions	
void game_cleanup(Engine *engine, int exit_status)
{
	SDL_DestroyRenderer(engine->renderer);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
	exit(exit_status);
}

bool sdl_initialize(Engine *engine) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		fprintf(stderr, "Error initializing SDL: %s\n",
		SDL_GetError());

		return true;	
	}

	engine->window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!engine->window)
	{
		fprintf(stderr, "Error creating window: %s\n",
		SDL_GetError());

		return true;
	}

	engine->renderer = SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);
	if (!engine->renderer)
	{
		fprintf(stderr, "Error creating renderer: %s\n",
		SDL_GetError());

		return true;
	}

	engine->texture = SDL_CreateTexture(
			engine->renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
			);
	if (!engine->texture)
	{
		fprintf(stderr, "Error creating texture/frame buffer: %s\n",
		SDL_GetError());

		return true;
	}

	return false;
}
