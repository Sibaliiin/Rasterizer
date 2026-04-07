#include	"types.h"
#include	"maths.h"
#include	"engine.h"

u32 draw_triangle (u32 *pixels, vec2d A, vec2d B, vec2d C, u32 color)
{
	i32 x1 = bbox_x1(A, B, C);
	i32 y1 = bbox_y1(A, B, C);
	i32 x2 = bbox_x2(A, B, C);
	i32 y2 = bbox_y2(A, B, C);

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
		for (int x=x1; x<x2; x++)	
		{	
			P.x = x;
			P.y = y;
		
			PA.x = P.x-A.x;
			PA.y = P.y-A.y;
			PB.x = P.x-B.x;
			PB.y = P.y-B.y;
			PC.x = P.x-C.x;
			PC.y = P.y-C.y;
			
			if ((dot_product(PA, ur) > -1) && (dot_product(PB, vr) > -1) && dot_product(PC, wr) > -1)		
			{
				pixels[y * SCREEN_WIDTH + x] = color;
			}		
		}
	}

	return *pixels;
}
