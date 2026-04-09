#ifndef GRAPHICS_H
#define GRAPHICS_H

u32	fill_screen		(u32 *pixels, u32 color);

u32	draw_pixel		(u32* pixels, vec2d p, u32 color);
u32	draw_triangle		(u32 *pixels, vec2d A, vec2d B, vec2d C, u32 color);
u32	draw_rect		(u32 *pixels, vec2d p, u8 d, u32 color);

#endif
