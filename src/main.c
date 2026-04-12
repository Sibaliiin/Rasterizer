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
#include	"graphics.h"

#define NEAR_PLANE 0.1f

vec3f	sib_Screen		(vec3f P);
vec3f	sib_Project		(vec3f P);
vec3f	sib_RotateXZ	(vec3f P, double angle);

int main(int argc, char* argv[])
{
	Engine engine = {NULL, NULL};

	// defining cube vertices
	vec3f v[9];
	v[0] = (vec3f){0.5, 0.5, 2.0};		// first vertice
	v[1] = (vec3f){-0.5, 0.5, 2.0};
	v[2] = (vec3f){0.5, -0.5, 2.0};
	v[3] = (vec3f){-0.5, -0.5, 2.0};
	v[4] = (vec3f){0.5, 0.5, 3.0};
	v[5] = (vec3f){-0.5, 0.5, 3.0};
	v[6] = (vec3f){0.5, -0.5, 3.0};
	v[7] = (vec3f){-0.5, -0.5, 3.0};	// last vertice	
	v[8] = (vec3f){0.0, 0.0, 2.5};		// center of the cube
	
	// projected points, 
	vec3f vT[8];
	for (int i=0; i<8; i++)
	{
		vT[i] = v[i];
	}

	// pixel points of v
	vec2d vP[8];

	// pixels
	u32 *pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32));
	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);

	// defining colors
	u32	white	= SDL_MapRGBA(format, 255,	255,	255,	255);
	u32	black	= SDL_MapRGBA(format, 0,	0,	0,	255);
	u32 	gray	= SDL_MapRGBA(format, 127,	127,	127,	255);

	u32	red	= SDL_MapRGBA(format, 255,	0,	0,	255);
	u32	green	= SDL_MapRGBA(format, 0,	255,	0,	255);
	u32	blue	= SDL_MapRGBA(format, 0,	0,	255,	255);
	u32	magenta	= SDL_MapRGBA(format, 255,	0,	255,	255);
	u32	yellow	= SDL_MapRGBA(format, 255,	255,	0,	255);
	u32	cyan	= SDL_MapRGBA(format, 0,	255,	255,	255);

	// custom color
	u8 c_r = 0;
	u8 c_g = 0;
	u8 c_b = 0;
	u8 c_a = 255;
	u32	color_c	= SDL_MapRGBA(format, c_r,	c_g,	c_b,	c_a);
	
	// test cube (manual)
	vec2d A = {100, 100};
	vec2d B = {400, 100};
	vec2d C = {100, 400};
	vec2d D = {400, 400};
	vec2d E = {150, 50};
	vec2d F = {450, 50};
	vec2d G = {450, 350};
	
	// test cube (projected)
	vec3f cube_v[8];
	vec3f cube_center = {0.0, 0.0, 4.5};

	float rad = 3.14159/180.0;
	double angle = 10*rad;
	double bounce = 0*rad;

	// initialize engine
	if (sdl_initialize(&engine))
	{
		game_cleanup(&engine, EXIT_FAILURE);
	}

	// main while loop
	while (true)
	{
		// SDL event handling
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
		// Manipulating the framebuffer
		// ============================

		// fill the screen with a color
		fill_screen(pixels, black);	
	
		/*
		// draw a cube (flat)
		draw_triangle(pixels, A, B, C, blue);
		draw_triangle(pixels, B, D, C, green);
		draw_triangle(pixels, A, E, B, red);
		draw_triangle(pixels, E, F, B, yellow);
		draw_triangle(pixels, B, F, D, cyan);
		draw_triangle(pixels, F, G, D, magenta);
		*/

		// testing graphics
		for (int y=0; y<64; y++)
		{
			for (int x=0; x<64; x++)
			{
				if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
				{
					return 0;
				}

				pixels[y*SCREEN_WIDTH+x] = color_c;

				c_r += 4;
				color_c = SDL_MapRGBA(format, c_r, c_g, c_b, c_a);
			}

			c_g += 4;
			color_c = SDL_MapRGBA(format, c_r, c_g, c_b, c_a);
		}
		c_r = 0;
		c_g = 0;
		c_b = 0;
		color_c = SDL_MapRGBA(format, c_r, c_g, c_b, c_a);


		// rendering every point of v
		for (int i=0; i<8; i++)
		{
			// move every point back into the origin
			vT[i].x -= v[8].x;
			vT[i].y -= v[8].y;
			vT[i].z -= v[8].z;

			// rotate every point with angle "angle"
			vT[i] = sib_RotateXZ(vT[i], angle);

			// move every point back into their original place
			vT[i].x += v[8].x;
			vT[i].y += v[8].y;
			vT[i].z += v[8].z;

			// check if near plane
			if (vT[i].z > NEAR_PLANE)
			{
				// project and scale every point
				vT[i] = sib_Project(vT[i]);
				vT[i] = sib_Screen(vT[i]);
				vP[i].x = vT[i].x;
				vP[i].y = vT[i].y;

				//draw_rect(pixels, vP[i], 5, green);

				
			}

			vT[i] = v[i];

			// bounce the cube up and down
			vT[i].y += 0.8*sin(bounce);
		}

		angle += 2*rad;
		bounce += 4*rad;

		if (angle >= 2*3.141592)
		{
			angle -= 2*3.141592;
		}

		if (bounce >= 2*3.141592)
		{
			bounce -= 2*3.141592;
		}

		// draw rotated v cube triangles
		//
		// front face
		draw_triangle(pixels, vP[1], vP[0], vP[3], blue);		// 1, 0, 3
		draw_triangle(pixels, vP[0], vP[2], vP[3], green);

		// right face
		draw_triangle(pixels, vP[0], vP[4], vP[2], cyan);
		draw_triangle(pixels, vP[2], vP[4], vP[6], magenta);
		
		// backface
		draw_triangle(pixels, vP[6], vP[4], vP[5], blue);
		draw_triangle(pixels, vP[5], vP[7], vP[6], green);
	
		// left face
		draw_triangle(pixels, vP[7], vP[5], vP[1], cyan);		// 7, 5, 1
		draw_triangle(pixels, vP[1], vP[3], vP[7], magenta);

		// top face
		draw_triangle(pixels, vP[5], vP[0], vP[1], red);
		draw_triangle(pixels, vP[5], vP[4], vP[0], yellow);

		// bottom face
		draw_triangle(pixels, vP[3], vP[2], vP[7], red);
		draw_triangle(pixels, vP[2], vP[6], vP[7], yellow);
		
		// render everything
		SDL_UpdateTexture(engine.texture, NULL, pixels, SCREEN_WIDTH * sizeof(u32));
		SDL_RenderClear(engine.renderer);
		SDL_RenderCopy(engine.renderer, engine.texture, NULL, NULL);
		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);
	}

	// clean up everything
	free(pixels);
	SDL_FreeFormat(format);
	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}

vec3f sib_Screen(vec3f P)
{
	P.x = (P.x + 1)/2*SCREEN_WIDTH;
	P.y = (1 - (P.y + 1)/2)*SCREEN_HEIGHT;

	return P;
}

vec3f sib_Project (vec3f P)
{
	P.x = P.x / P.z;
	P.y = P.y / P.z;

	return P;
}

vec3f sib_RotateXZ (vec3f P, double angle)
{	
	double c = cos(angle);
	double s = sin(angle);

	double x = (P.x*c) - (P.z*s);
	double z = (P.x*s) + (P.z*c);

	P.x = x;
	P.z = z;

	return P;
}
