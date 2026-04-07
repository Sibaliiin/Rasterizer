#ifndef	TYPES_H
#define	TYPES_H

#include <stdint.h>

// definitions
//
// integers
#define u8	uint8_t
#define u16	uint16_t
#define	u32	uint32_t
#define	u64	uint64_t

#define i8	int8_t
#define	i16	int16_t
#define i32	int32_t
#define	i64	int64_t

// structures

// mathematical 3d point OR vector
// depending on use case
typedef struct
{
	float x;
	float y;
	float z;
} vec3f;

// mathematical 2d point or vector
// u16 = 0 to 65535
typedef struct
{
	u32 x;
	u32 y;
} vec2d;

// triangle structure
// uses vec3f, here they are _points_ in 3d space
typedef struct
{
	vec3f A;
	vec3f B;
	vec3f C;
} Tri;

#endif
