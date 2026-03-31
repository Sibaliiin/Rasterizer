#ifndef MATHS_H
#define MATHS_H

#include	"types.h"

i32	dot_product	(vec2d a, vec2d b);
u32	max_u32		(u32 a, u32 b);
u32	min_u32		(u32 a, u32 b);

u32	bbox_x1		(vec2d A, vec2d B, vec2d C);
u32	bbox_y1		(vec2d A, vec2d B, vec2d C);

u32	bbox_x2		(vec2d A, vec2d B, vec2d C);
u32	bbox_y2		(vec2d A, vec2d B, vec2d C);

#endif
