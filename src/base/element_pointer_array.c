#include "yuime/base/element_pointer_array.h"

#include "yuime/base/element.h"

uint8_t yuime_element_pointer_array_init(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *array, yuime_element_pointer_array_index_t initial_capacity) {
	array->count = 0;
	if (initial_capacity == 0) {
		array->data = NULL;

	} else if (!mem_funcs->alloc(&array->data, initial_capacity * sizeof(yuime_element*)))
		return 0;

	array->capacity = initial_capacity;
	return 1;
}

uint8_t yuime_element_pointer_array_push(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *array, yuime_element *value) {
	if (array->count == array->capacity) {
		if (array->data == NULL) {
			if (!mem_funcs->alloc(&array->data, (array->capacity+1) * sizeof(yuime_element*)))
				return 0;
		} else if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(yuime_element*), (array->capacity+1) * sizeof(yuime_element*)))
			return 0;
		array->capacity++;
	}

	array->data[array->count++] = value;
	return 1;
}

void yuime_element_pointer_array_free(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *array) {
	if (array->data == NULL)
		return;

	mem_funcs->free(array->data, array->capacity*sizeof(yuime_element*));

	array->data = NULL;
	array->count = array->capacity = 0;
}

yuime_element *yuime_element_pointer_array_get(const yuime_element_pointer_array *array, yuime_element_pointer_array_index_t index) {
	if (array->data == NULL || index >= array->count)
		return NULL;
	return *(array->data+index);
}

void yuime_element_pointer_array_pop(yuime_element_pointer_array *array, yuime_element_pointer_array_index_t index) {
	for (size_t i = index; i+1 < array->count; ++i) {
		array->data[i] = array->data[i+1];
	}
	array->count--;
}

uint8_t yuime_element_pointer_array_reserve(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *array, yuime_element_pointer_array_index_t to_reserve) {
	if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(yuime_element*), (array->capacity+to_reserve) * sizeof(yuime_element*)))
		return 0;

	array->capacity += to_reserve;
	return 1;
}

uint8_t yuime_element_pointer_array_fit_capacity_to_size(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *array) {
	if (array->capacity == array->count)
		return 1;

	if (array->count == 0) {
		yuime_element_pointer_array_free(mem_funcs, array);
		return 1;
	}

	if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(yuime_element*), array->count * sizeof(yuime_element*))) {
		return 0;
	}

	array->capacity = array->count;
	return 1;
}