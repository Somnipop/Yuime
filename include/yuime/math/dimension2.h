#pragma once

#include "vector2.h"

typedef struct yuime_dim2_s {
	yuime_vector2_t scale; ///< Relative (percentage).
	yuime_vector2_t offset; ///< Absolute (pixel).
} yuime_dim2_t;

inline float yuime_dim2_calculate_size(float parent_size, float scale, float offset) {
	return (parent_size * scale) + offset;
}

inline float yuime_dim2_calculate_position(float parent_position, float parent_size, float size, float scale, float offset, float pivot) {
	return parent_position + (parent_size * scale) + offset - (size * pivot);
}