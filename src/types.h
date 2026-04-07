#ifndef	TYPES_H
#define	TYPES_H

#include <stdint.h>

// unsigned integers
#define u8	uint8_t
#define u16	uint16_t
#define	u32	uint32_t
#define	u64	uint64_t

// signed integers
#define i8	int8_t
#define	i16	int16_t
#define i32	int32_t
#define	i64	int64_t

// vector			3 dimensional, floating point coordinates
typedef struct
{
	float x;
	float y;
	float z;
} vec3f;

// vector			2 dimensional, unsigned integers 
typedef struct
{
	u32 x;
	u32 y;
} vec2d;

// triangle structure		three points, floating point numbers
typedef struct
{
	vec3f A;
	vec3f B;
	vec3f C;
} Tri;

#endif
