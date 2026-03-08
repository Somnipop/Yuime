#pragma once

#include <stdint.h>

#include "API.h"

struct yuime_context_s;
struct yuime_element_s;
typedef void(*yuime_event_callback_t)(struct yuime_context_s* ctx, struct yuime_element_s* element, void* data);

/**
 * @brief Passes data to all elements via element->event_callback().
 * 
 * @param ctx 
 * @param data Data to be passed.
 * @return YUIME_API 
 */
YUIME_API void yuime_context_send_event(struct yuime_context_s* ctx, void* data);