#include "yuime/base/element/element.h"

#include <string.h>

void yuime_element_init(yuime_element_t *element, yuime_element_event_callback_t event_callback, yuime_element_object self, uint8_t flags) {
	memset(element, 0, sizeof(yuime_element_t));

	element->event_callback = event_callback;
	element->self = self;
	element->flags = flags;
}