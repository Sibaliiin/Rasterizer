// build using: 
// gcc $(sdl2-config --cflags) src/main.c src/engine.c src/maths.c src/rasterizer.c -o bin/p $(sdl2-config --libs) -lm

// default headers
#include	<stdio.h>
#include	<stdint.h>
#include	<stdbool.h>

// SDL2
#include	<SDL2/SDL.h>

// headers
#include	"engine.h"
#include	"types.h"
#include	"maths.h"
#include	"rasterizer.h"

int main(int argc, char* argv[])
{
	Engine engine = {NULL, NULL};
	Camera cam = {0.0, 0.0, 1.0};

	// pixels
	u32 *pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32));
	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);

	// defining colors
	u32	white	= SDL_MapRGBA(format, 255,	255,	255,	255);
	u32	black	= SDL_MapRGBA(format, 0,	0,	0,	255);
	u32	red	= SDL_MapRGBA(format, 255,	0,	0,	255);
	u32	green	= SDL_MapRGBA(format, 0,	255,	0,	255);
	u32	blue	= SDL_MapRGBA(format, 0,	0,	255,	255);
	u32	magenta	= SDL_MapRGBA(format, 255,	0,	255,	255);
	u32	yellow	= SDL_MapRGBA(format, 255,	255,	0,	255);
	u32	cyan	= SDL_MapRGBA(format, 0,	255,	255,	255);

	// custom color
	i8 cr = 0;
	i8 cg = 0;
	i8 cb = 0;
	i8 ca = 255;
	u32	color	= SDL_MapRGBA(format, cr,	cg,	cb,	ca);

	// vector mathematics
	vec2d A = {100, 100};
	vec2d B = {400, 100};
	vec2d C = {100, 400};
	vec2d D = {400, 400};
	vec2d E = {150, 50};
	vec2d F = {450, 50};
	vec2d G = {450, 350};
	
	// initialize engine
	if (sdl_initialize(&engine))
	{
		game_cleanup(&engine, EXIT_FAILURE);
	}

	// main while loop
	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					game_cleanup(&engine, EXIT_SUCCESS);
					break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						game_cleanup(&engine, EXIT_SUCCESS);
						break;
					default:
						break;
				}
			default:
				break;
			}
		}
		
		// draw an EPIC cube
		draw_triangle(pixels, A, B, C, blue);
		draw_triangle(pixels, B, D, C, green);
		draw_triangle(pixels, A, E, B, red);
		draw_triangle(pixels, E, F, B, yellow);
		draw_triangle(pixels, B, F, D, cyan);
		draw_triangle(pixels, F, G, D, magenta);

		SDL_UpdateTexture(engine.texture, NULL, pixels, SCREEN_WIDTH * sizeof(u32));
		SDL_RenderClear(engine.renderer);
		SDL_RenderCopy(engine.renderer, engine.texture, NULL, NULL);
		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);
	}

	free(pixels);
	SDL_FreeFormat(format);
	
	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}
