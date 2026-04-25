#pragma once

#include "color.h"

typedef struct yuime_style_border_s {
	yuime_color_t color;
	float size;
} yuime_style_border_t;

typedef struct yuime_style_border_corners_s {
	float top_left_radius;
	float top_right_radius;
	float bottom_left_radius;
	float bottom_right_radius;

	yuime_color_t color;
} yuime_style_border_corners_t;