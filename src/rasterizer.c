#include	"types.h"
#include	"maths.h"
#include	"engine.h"

u32 draw_triangle (u32 *pixels, vec2d A, vec2d B, vec2d C, u32 color)
{
	i32 x1 = bbox_x1(A, B, C);
	i32 y1 = bbox_y1(A, B, C);
	i32 x2 = bbox_x2(A, B, C);
	i32 y2 = bbox_y2(A, B, C);

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
			
			if ((dot_product(PA, ur) > 0) && (dot_product(PB, vr) > 0) && dot_product(PC, wr) > 0)		
			{
				pixels[y * SCREEN_WIDTH + x] = color;
			}		
		}
	}

	return *pixels;
}
