#pragma once

#include <stdint.h>

typedef struct yuime_color_s {
	uint8_t r, g, b, a;
} yuime_color_t;

#define YUIME_COLOR(_r, _g, _b, _a) (yuime_color_t){.r = (uint8_t)_r, .g = (uint8_t)_g, .b = (uint8_t)_b, .a = (uint8_t)_a}