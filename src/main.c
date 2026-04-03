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

	// custom color
	i8 cr = 0;
	i8 cg = 0;
	i8 cb = 0;
	i8 ca = 255;
	u32	color	= SDL_MapRGBA(format, cr,	cg,	cb,	ca);

	// TEST MALLOC
	size_t n = 4;
	i8 *numbers = malloc(n);
	numbers[0] = 7;
	printf("numbers memory allocation.\n");
	printf("numbers[0] = %d\n", numbers[0]);
	free(numbers);

	// vector mathematics
	vec2d A = {100, 100};
	vec2d B = {300, 50};
	vec2d C = {150, 300};

	i32 x1 = bbox_x1(A, B, C);
	i32 y1 = bbox_y1(A, B, C);
	i32 x2 = bbox_x2(A, B, C);
	i32 y2 = bbox_y2(A, B, C);
		
	printf("bounding box x1: %d\n", bbox_x1(A, B, C));
	printf("bounding box y1: %d\n", bbox_y1(A, B, C));
	printf("bounding box x2: %d\n", bbox_x2(A, B, C));
	printf("bounding box y2: %d\n", bbox_y2(A, B, C));

	vec2d u = {0, 0};
	vec2d ur = {0, 0};
	
	vec2d v = {0, 0};
	vec2d vr = {0, 0};
	
	vec2d w = {0, 0};
	vec2d wr = {0, 0};

	u.x = B.x - A.x;
	u.y = B.y - A.y;
	ur.x = -u.y;
	ur.y = u.x;
	
	v.x = C.x - B.x;
	v.y = C.y - B.y;
	vr.x = -v.y;
	vr.y = v.x;

	w.x = A.x - C.x;
	w.y = A.y - C.y;
	wr.x = -w.y;
	wr.y = w.x;

	vec2d P = {0, 0};

	vec2d PA = {0, 0};
	vec2d PB = {0, 0};
	vec2d PC = {0, 0};

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

		// drawing to the texture	
		for (int y = y1; y < y2; y++)			// screen_height
		{
			for (int x=x1; x<x2; x++)		// screen_width
			{	
				P.x = x;
				P.y = y;
			
				PA.x = P.x-A.x;
				PA.y = P.y-A.y;
	
				PB.x = P.x-B.x;
				PB.y = P.y-B.y;
			
				PC.x = P.x-C.x;
				PC.y = P.y-C.y;
				
			
				if ((dot_product(PA, ur) > 0) && (dot_product(PB, vr) > 0) && dot_product(PC, wr) > 0)		
				{
					pixels[y * SCREEN_WIDTH + x] = green;
				}
				else
				{
					pixels[y * SCREEN_WIDTH + x] = red;
				}
			}
		}


		pixels[A.y * SCREEN_WIDTH + A.x] = green;
		pixels[B.y * SCREEN_WIDTH + B.x] = green;	
		pixels[C.y * SCREEN_WIDTH + C.x] = green;

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
