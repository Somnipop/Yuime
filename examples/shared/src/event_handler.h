#pragma once

#include <stdint.h>

#include <SDL3/SDL.h>

#include <yuime/yuime.h>

typedef uint8_t event_type_t;
enum event_type_e {
	EVENT_WINDOW_RESIZE = 0,
	EVENT_MOUSE_PRESS,
	EVENT_MOUSE_WHEEL,
	EVENT_MOUSE_ENTER,
	EVENT_MOUSE_LEAVE,
	EVENT_COUNT
};

typedef struct event_window_s {
	float width;
	float height;
} event_window_t;

typedef struct event_mouse_s {
	yuime_vector2_t position;
	union {
		SDL_MouseButtonFlags button;
		float wheel;
	};
} event_mouse_t;

uint8_t element_event_callback(yuime_context_t* ctx, yuime_element_t* element, uint32_t event_type, void* data);