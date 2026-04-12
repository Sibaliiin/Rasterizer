#include	"types.h"
#include	"maths.h"
#include	"engine.h"

u32 fill_screen(u32 *pixels, u32 color)
{
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			pixels[y * SCREEN_WIDTH + x] = color;
		}
	}
}

u32 draw_pixel(u32 *pixels, vec2d p, u32 color)
{
	if (p.x >= SCREEN_WIDTH || p.y >= SCREEN_HEIGHT)
	{
		return 0;
	}

	pixels[p.y * SCREEN_WIDTH + p.x] = color;
}

void draw_triangle(u32 *pixels, vec2d A, vec2d B, vec2d C, u32 color)
{
	// define the bounding box for the triangle
	// only check pixels inside this box
	i32 x1 = bbox_x1(A, B, C);
	i32 y1 = bbox_y1(A, B, C);
	i32 x2 = bbox_x2(A, B, C);
	i32 y2 = bbox_y2(A, B, C);
	
	// clamp the bounding box
	if (x1 < 0)
	{
		x1 = 0;
	}
	
	if (y1 < 0)
	{
		y1 = 0;
	}

	if (x2 > SCREEN_WIDTH)
	{
		x2 = SCREEN_WIDTH;
	}

	if (y2 > SCREEN_HEIGHT)
	{
		y2 = SCREEN_HEIGHT;
	}

	vec2d ur = {A.y-B.y, B.x-A.x};
	vec2d vr = {B.y-C.y, C.x-B.x};
	vec2d wr = {C.y-A.y, A.x-C.x};

	vec2d P = {0, 0};

	vec2d PA = {0, 0};
	vec2d PB = {0, 0};
	vec2d PC = {0, 0};

	// drawing to the texture	
	for (int y = y1; y < y2; y++)			
	{
		for (int x = x1; x < x2; x++)	
		{	
			P.x = x;
			P.y = y;
		
			PA.x = P.x-A.x;
			PA.y = P.y-A.y;
			PB.x = P.x-B.x;
			PB.y = P.y-B.y;
			PC.x = P.x-C.x;
			PC.y = P.y-C.y;
			
			if (dot_product(PA, ur) >= 0 && dot_product(PB, vr) >= 0 && dot_product(PC, wr) >= 0)		
			{
				pixels[y * SCREEN_WIDTH + x] = color;
			}
			/*
			else
			{
				pixels[y * SCREEN_WIDTH + x] = color;
			}
			*/
		}
	}
}

u32 draw_rect(u32 *pixels, vec2d p, u8 d, u32 color)
{
	vec2d r1 = {p.x-d, p.y-d};
	vec2d r2 = {p.x+d, p.y+d};

	for (int y = r1.y; y < r2.y; y++)
	{
		for (int x = r1.x; x < r2.x; x++) 
		{
			if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
				continue;
			pixels[y*SCREEN_WIDTH+x] = color;
		}
	}
}
