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

/*
// projection function
vec2d	project_point	(vec3f P,	// point in 3d space
			proj_matrix,	// projection matrix
			vec2d p);	// pixel on the screen
*/

vec3f	scale_point	(vec3f P, float d);
vec3f	move_point	(vec3f P, vec3f v);
vec3f	invert_vector	(vec3f v);

vec3f	screen		(vec3f P);
vec3f	project		(vec3f P);
vec3f	rotate_xz	(vec3f P, double angle);

int main(int argc, char* argv[])
{
	Engine engine = {NULL, NULL};

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
	cube_v[0] = (vec3f){0.5, 0.5, 4.0};
	cube_v[1] = (vec3f){-0.5, 0.5, 4.0};
	cube_v[2] = (vec3f){0.5, -0.5, 4.0};
	cube_v[3] = (vec3f){-0.5, -0.5, 4.0};
	cube_v[4] = (vec3f){0.5, 0.5, 5.0};
	cube_v[5] = (vec3f){-0.5, 0.5, 5.0};
	cube_v[6] = (vec3f){0.5, -0.5, 5.0};
	cube_v[7] = (vec3f){-0.5, -0.5, 5.0};
	vec3f cube_center = {0.0, 0.0, 4.5};

	float rad = 3.14159/180.0;
	float height = 90*rad;
	double angle = 10*rad;

	// test point
	vec2d P = {100, 100};


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

		// projected cube
		vec3f cube_v_rxz[8];
		vec3f cube_v_p[8];
		vec3f cube_v_s[8];
		vec2d cube_v_pixel[8];


		// project the points onto the screen
		for (int i=0; i<8; i++)
		{	
			cube_v_rxz[i] = rotate_xz(cube_v[i], angle);
			
			
			if (cube_v_rxz[i].z <= NEAR_PLANE)
				continue;
			

			cube_v_p[i] = project(cube_v_rxz[i]);
			cube_v_s[i] = screen(cube_v_p[i]);
			cube_v_pixel[i] = (vec2d){cube_v_s[i].x, cube_v_s[i].y};
		}

		angle += 0.5*rad;

		if (angle >= 2*3.141592)
		{
			angle -= 2*3.141592;
		}


		
		// draw a projected test triangle
		draw_triangle(pixels, cube_v_pixel[1], cube_v_pixel[0], cube_v_pixel[3], blue);
		draw_triangle(pixels, cube_v_pixel[3], cube_v_pixel[0], cube_v_pixel[2], green);	
		draw_triangle(pixels, cube_v_pixel[2], cube_v_pixel[7], cube_v_pixel[3], red);
		draw_triangle(pixels, cube_v_pixel[2], cube_v_pixel[6], cube_v_pixel[7], yellow);
		

		// draw a rectangle
		for (int i=0; i<8; i++)
		{
			draw_rect(pixels, cube_v_pixel[i], 5, blue);
		}

		
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

vec3f screen(vec3f P)
{
	P.x = (P.x + 1)/2*SCREEN_WIDTH;
	P.y = (1 - (P.y + 1)/2)*SCREEN_HEIGHT;

	return P;
}

vec3f project (vec3f P)
{
	P.x = P.x / P.z;
	P.y = P.y / P.z;

	return P;
}

vec3f rotate_xz (vec3f P, double angle)
{	
	double c = cos(angle);
	double s = sin(angle);

	double x = (P.x*c) - (P.z*s);
	double z = (P.x*s) + (P.z*c);

	P.x = x;
	P.z = z;

	return P;
}

vec3f move_point(vec3f P, vec3f v)
{
	P.x += v.x;
	P.y += v.y;
	P.z += v.z;

	return P;
}

vec3f invert_vector(vec3f v)
{
	vec3f v_i = {0.0, 0.0, 0.0};

	v_i.x = -v.x;
	v_i.y = -v.y;
	v_i.z = -v.z;

	return v_i;
}
