#include	"maths.h"
#include	"types.h"

i32 dot_product(vec2d a, vec2d b)
{
	return (a.x * b.x) + (a.y * b.y);
}

u32 max_u32(u32 a, u32 b)
{
	if(a >= b) {
		return a;
	}
	else
	{
		return b;
	}
}

u32 min_u32(u32 a, u32 b)
{
	if(a <= b) {
		return a;
	}
	else
	{
		return b;
	}
}

u32 bbox_x1(vec2d A, vec2d B, vec2d C)
{
	return min_u32(A.x, min_u32(B.x, C.x));
}

u32 bbox_y1(vec2d A, vec2d B, vec2d C)
{
	return min_u32(A.y, min_u32(B.y, C.y));
}

u32 bbox_x2(vec2d A, vec2d B, vec2d C)
{
	return max_u32(A.x, max_u32(B.x, C.x));
}

u32 bbox_y2(vec2d A, vec2d B, vec2d C)
{
	return max_u32(A.y, max_u32(B.y, C.y));
}
