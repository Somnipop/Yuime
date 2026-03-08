// Should only be used to get the expanded version of the macros and then replace the macro with the code it made.

#pragma once

#include <stdint.h>

#include "alloc.h"

#define YUIME_DEFINE_ARRAY_HEADER(type, name, function_name_prefix, array_size_t, declspec_prefix) \
typedef struct name##_s { \
	array_size_t capacity; \
	array_size_t count; \
	type* data; \
} name; \
/* Returns 0 if failed to allocate initial capacity. */ \
declspec_prefix uint8_t function_name_prefix##init(yuime_mem_functions* mem_funcs, name *array, array_size_t initial_capacity); \
/* Returns 0 if failed to allocate/reallocate. */ \
declspec_prefix uint8_t function_name_prefix##push(yuime_mem_functions* mem_funcs, name *array, const type *value); \
declspec_prefix void function_name_prefix##free(yuime_mem_functions* mem_funcs, name *array); \
/* Returns NULL if data is NULL or index is higher than or equal to array->count. */ \
declspec_prefix type* function_name_prefix##get(const name *array, array_size_t index); \
declspec_prefix void function_name_prefix##pop(name *array, array_size_t index); \
/* Returns 0 if failed to reallocate. */ \
declspec_prefix uint8_t function_name_prefix##reserve(yuime_mem_functions* mem_funcs, name *array, array_size_t to_reserve); \
declspec_prefix void function_name_prefix##fit_capacity_to_size(yuime_mem_functions* mem_funcs, name *array);

YUIME_DEFINE_ARRAY_HEADER(int, integers, integers_, size_t, YUIME_API)


#define YUIME_DEFINE_ARRAY_IMPLEMENTATION(type, name, function_name_prefix, array_size_t) \
uint8_t function_name_prefix##init(yuime_mem_functions* mem_funcs, name *array, array_size_t initial_capacity) { \
	array->count = 0; \
	if (initial_capacity == 0) array->data = NULL; \
	else if (!mem_funcs->alloc(&array->data, initial_capacity * sizeof(type))) return 0; \
	array->capacity = initial_capacity; \
	return 1; \
} \
uint8_t function_name_prefix##push(yuime_mem_functions* mem_funcs, name *array, const type *value) { \
	if (array->count == array->capacity) { \
		if (array->data == NULL) \
			if (!mem_funcs->alloc(&array->data, (array->capacity+1) * sizeof(type))) return 0; \
		else \
			if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(type), (array->capacity+1) * sizeof(type))) return 0; \
		array->capacity++; \
	} \
	array->data[array->count++] = *value; \
	return 1; \
} \
void function_name_prefix##free(yuime_mem_functions* mem_funcs, name *array) { \
	if (array->data == NULL) return; \
	free(array->data, array->capacity*sizeof(type)); \
	array->data = NULL; \
	array->count = array->capacity = 0; \
} \
type* function_name_prefix##get(const name *array, array_size_t index) { \
	if (array->data == NULL || index >= array->count) return NULL; \
	return array->data+index; \
} \
void function_name_prefix##pop(name *array, array_size_t index) { \
	for (array_size_t i = index; i < array->count; ++i) { \
		array->data[i] = array->data[i+1]; \
	} \
	array->count--; \
} \
uint8_t function_name_prefix##reserve(yuime_mem_functions* mem_funcs, name *array, array_size_t to_reserve) { \
	if (!mem_funcs->realloc(&array->data, array->capacity * sizeof(type), (array->capacity+to_reserve) * sizeof(type))) return 0; \
	array->capacity += to_reserve; \
	return 1; \
} \
void function_name_prefix##fit_capacity_to_size(yuime_mem_functions* mem_funcs, name *array) { \
	if (array->capacity == array->count) return; \
	if (array->count == 0) { \
		function_name_prefix##free(mem_funcs, array); \
		return; \
	} \
	array->data = mem_funcs->realloc(&array->data, array->capacity * sizeof(type), array->count * sizeof(type)); \
	array->capacity = array->count; \
}
