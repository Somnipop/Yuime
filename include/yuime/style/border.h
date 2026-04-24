#pragma once

#include "color.h"

typedef struct yuime_style_border_s {
	yuime_color_t color;
	float size;
} yuime_style_border_t;

typedef struct yuime_style_border_radius_s {
	float top_left;
	float top_right;
	float bottom_left;
	float bottom_right;
} yuime_style_border_radius_t;