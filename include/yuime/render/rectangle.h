#pragma once

#include "../math/rect.h"

#include "../style/color.h"
#include "../style/border.h"

typedef struct yuime_command_rect_s {
	yuime_color_t *background_color;
	yuime_style_border_radius_t *border_radius;
	yuime_rect_t *rect;
} yuime_command_rect_t;

typedef struct yuime_command_border_s {
	yuime_style_border_t *top;
	yuime_style_border_t *bottom;
	yuime_style_border_t *left;
	yuime_style_border_t *right;

	yuime_style_border_radius_t *radius;

	yuime_rect_t *rect;
} yuime_command_border_t;