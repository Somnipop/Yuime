#pragma once

typedef struct yuime_vector2_s {
	float x; ///< horizontal
	float y; ///< vertical
} yuime_vector2_t;

#define YUIME_VEC2(_x, _y) \
	(yuime_vector2_t){ \
		.x = (float)_x, \
		.y = (float)_y \
	}