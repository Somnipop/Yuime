#pragma once

#include <stdint.h>

#include "../API.h"
#include "event.h"
#include "rect.h"
#include "geometry.h"
#include "element_pointer_array.h"


typedef uint8_t yuime_element_flag_t;
typedef enum yuime_element_flag_e {
	YUIME_ELEMENT_FLAG_NONE = 0,
	YUIME_ELEMENT_FLAG_VISIBLE = 1, ///< SHOULD NOT BE MODIFIED MANUALLY! Use yuime_set_visibility() instead
	YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE = 2, ///< True if element parent and self is visible. False otherwise. SHOULD NOT BE MODIFIED MANUALLY!
} yuime_element_flag;

typedef struct yuime_element_object_s {
	uint32_t type; ///< Object type
	void *obj; ///< Object
} yuime_element_object;

struct yuime_element_s;
typedef void(*yuime_element_free_callback_t)(struct yuime_element_s* element);

typedef struct yuime_element_s {
	yuime_rect rect;

	yuime_event_callback_t event_callback; ///< Function to be called when yuime_context_send_event() is called.
	yuime_element_free_callback_t free;

	yuime_element_object self;
	struct yuime_element_s *parent;

	yuime_element_pointer_array children;
	
	yuime_element_flag_t flags;
} yuime_element;

/**
 * @brief Sets default values for the given element.
 * @param element Element to initialize.
 */
YUIME_API void yuime_element_init(yuime_element *element, yuime_event_callback_t event_callback, yuime_element_object self, uint8_t flags);