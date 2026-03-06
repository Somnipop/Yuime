#pragma once

#include <stdint.h>

typedef uint8_t yuime_event_flag_t;
typedef uint8_t yuime_mouse_button_t;
typedef uint8_t yuime_mouse_button_t;
typedef float yuime_wheel_direction_t;
typedef uint32_t yuime_key_t;

// Mouse
#define YUIME_EVENT_MOUSE_PRESS_FLAG ((yuime_event_flag_t)1)
typedef void(*on_mouse_press_callback_t)(yuime_mouse_button_t button);

#define YUIME_EVENT_MOUSE_RELEASE_FLAG ((yuime_event_flag_t)2)
typedef void(*on_mouse_release_callback_t)(yuime_mouse_button_t button);

#define YUIME_EVENT_MOUSE_WHEEL_MOVE_FLAG ((yuime_event_flag_t)4)
typedef void(*on_mouse_wheel_move_callback_t)(yuime_wheel_direction_t dir);

// Keyboard
#define YUIME_EVENT_KEY_PRESS_FLAG ((yuime_event_flag_t)8)
typedef void(*on_key_press_callback_t)(yuime_key_t key);

#define YUIME_EVENT_KEY_RELEASE_FLAG ((yuime_event_flag_t)16)
typedef void(*on_key_release_callback_t)(yuime_key_t key);