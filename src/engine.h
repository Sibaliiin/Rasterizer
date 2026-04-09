#ifndef	ENGINE_H
#define	ENGINE_H

#include	<stdbool.h>

#include	<SDL2/SDL.h>

#include	"types.h"

#define WINDOW_TITLE    "Window"

// constants
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800


// engine structure
typedef struct
{
        SDL_Window      *window;
        SDL_Renderer    *renderer;
	SDL_Texture	*texture;
} Engine;

// function declaration
void game_cleanup       	(Engine *engine, int exit_status);
bool sdl_initialize		(Engine *engine);

#endif
