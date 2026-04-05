#pragma once

#include "color.h"

typedef struct yuime_style_border_s {
	yuime_color_t color;
	float radius;
	float size;
} yuime_style_border_t;

typedef struct yuime_style_s {
	yuime_style_border_t border;
	yuime_color_t color;
} yuime_style_t;