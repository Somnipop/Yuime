#include "yuime/base/element.h"

#include <stdlib.h>
#include <string.h>

void yuime_element_init(yuime_element* element, yuime_event_callback_t event_callback, yuime_element_object self, uint8_t flags) {
	memset(element, 0, sizeof(yuime_element));

	element->event_callback = event_callback;
	element->self = self;
	element->flags = flags;
}


uint8_t yuime_element_array_init(yuime_mem_functions* mem_funcs, yuime_element_array *array, yuime_element_array_index_t initial_capacity) {
	array->count = 0;
	if (initial_capacity == 0) {
		array->data = NULL;

	} else if (!mem_funcs->alloc(&array->data, initial_capacity * sizeof(yuime_element)))
		return 0;

	array->capacity = initial_capacity;
	return 1;
}

uint8_t yuime_element_array_push(yuime_mem_functions* mem_funcs, yuime_element_array *array, const yuime_element *value) {
	if (array->count == array->capacity) {
		if (array->data == NULL) {
			if (!mem_funcs->alloc(&array->data, (array->capacity+1) * sizeof(yuime_element)))
				return 0;
		} else if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(yuime_element), (array->capacity+1) * sizeof(yuime_element)))
			return 0;
		array->capacity++;
	}

	array->data[array->count++] = *value;
	return 1;
}

void yuime_element_array_free(yuime_mem_functions* mem_funcs, yuime_element_array *array) {
	if (array->data == NULL)
		return;

	mem_funcs->free(array->data, array->capacity*sizeof(yuime_element));

	array->data = NULL;
	array->count = array->capacity = 0;
}

yuime_element* yuime_element_array_get(const yuime_element_array *array, yuime_element_array_index_t index) {
	if (array->data == NULL || index >= array->count)
		return NULL;
	return array->data+index;
}

void yuime_element_array_pop(yuime_element_array *array, yuime_element_array_index_t index) {
	for (size_t i = index; i < array->count; ++i) {
		array->data[i] = array->data[i+1];
	}
	array->count--;
}

uint8_t yuime_element_array_reserve(yuime_mem_functions* mem_funcs, yuime_element_array *array, yuime_element_array_index_t to_reserve) {
	if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(yuime_element), (array->capacity+to_reserve) * sizeof(yuime_element)))
		return 0;

	array->capacity += to_reserve;
	return 1;
}

uint8_t yuime_element_array_fit_capacity_to_size(yuime_mem_functions* mem_funcs, yuime_element_array *array) {
	if (array->capacity == array->count)
		return 1;

	if (array->count == 0) {
		yuime_element_array_free(mem_funcs, array);
		return 1;
	}

	if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(yuime_element), array->count * sizeof(yuime_element))) {
		return 0;
	}

	array->capacity = array->count;
	return 1;
}