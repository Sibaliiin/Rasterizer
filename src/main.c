// build using: 
// gcc $(sdl2-config --cflags) src/main.c src/engine.c src/maths.c src/rasterizer.c -o bin/p $(sdl2-config --libs) -lm

// default headers
#include	<stdio.h>
#include	<stdint.h>
#include	<stdbool.h>
#include	<math.h>

// SDL2
#include	<SDL2/SDL.h>

// headers
#include	"engine.h"
#include	"types.h"
#include	"maths.h"
#include	"rasterizer.h"

vec

int main(int argc, char* argv[])
{
	Engine engine = {NULL, NULL};

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

	// Projection Variables
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
	
	// Projection Matrix
	float *proj_matrix = malloc(6*sizeof(float));
	proj_matrix[0] = fAspectRatio * fFovRad;
	proj_matrix[1] = fFovRad;
	proj_matrix[2] = fFar / (fFar - fNear);
	proj_matrix[3] =  (-fFar * fNear) / (fFar - fNear);
	proj_matrix[4] = 1.0f;
	proj_matrix[5] = 0.0f;

	// test cube (manual)
	vec2d A = {100, 100};
	vec2d B = {400, 100};
	vec2d C = {100, 400};
	vec2d D = {400, 400};
	vec2d E = {150, 50};
	vec2d F = {450, 50};
	vec2d G = {450, 350};
	
	// test cube (projected)
	vec3f A0 = {1.0000, 1.0000, 1.0000};
	vec3f A1 = {1.0000, 1.0000, -1.0000};
	vec3f A2 = {1.0000, -1.0000, 1.0000};
	vec3f A3 = {1.0000, -1.0000, -1.0000};
	vec3f A4 = {-1.0000, 1.0000, 1.0000};
	vec3f A5 = {-1.0000, 1.0000, -1.0000};
	vec3f A6 = {-1.0000, -1.0000, 1.0000};
	vec3f A7 = {-1.0000, -1.0000, -1.0000};

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
		
		// draw a cube (flat)
		draw_triangle(pixels, A, B, C, blue);
		draw_triangle(pixels, B, D, C, green);
		draw_triangle(pixels, A, E, B, red);
		draw_triangle(pixels, E, F, B, yellow);
		draw_triangle(pixels, B, F, D, cyan);
		draw_triangle(pixels, F, G, D, magenta);

		// draw a cube (projected)

		// render
		SDL_UpdateTexture(engine.texture, NULL, pixels, SCREEN_WIDTH * sizeof(u32));
		SDL_RenderClear(engine.renderer);
		SDL_RenderCopy(engine.renderer, engine.texture, NULL, NULL);
		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);
	}

	// clean up everything
	free(pixels);
	free(proj_matrix);
	SDL_FreeFormat(format);
	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}
