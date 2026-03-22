#pragma once

#include "../../API.h"

#include "../alloc.h"

struct yuime_element_s;
typedef uint32_t yuime_element_pointer_array_index_t;

typedef struct yuime_element_pointer_array_s {
	yuime_element_pointer_array_index_t capacity;
	yuime_element_pointer_array_index_t count;
	struct yuime_element_s** data;
} yuime_element_pointer_array_t;

/**
 * @brief Initializes an element array.
 * 
 * @param mem_funcs 
 * @param array 
 * @param initial_capacity 
 * 
 * @returns 0 if failed to allocate initial capacity.
 */
YUIME_API uint8_t yuime_element_pointer_array_init(const yuime_memory_functions_t *mem_funcs, yuime_element_pointer_array_t *array, yuime_element_pointer_array_index_t initial_capacity);

YUIME_API void yuime_element_pointer_array_free(const yuime_memory_functions_t *mem_funcs, yuime_element_pointer_array_t *array);

/**
 * @brief Copies an element to the array.
 * 
 * @param mem_funcs 
 * @param array 
 * @param value 
 * 
 * @returns 0 if failed to allocate/reallocate.
 */
YUIME_API uint8_t yuime_element_pointer_array_push(const yuime_memory_functions_t *mem_funcs, yuime_element_pointer_array_t *array, struct yuime_element_s *value);

/**
 * @brief Gets an element from array at index.
 * 
 * @param array Array to get element from.
 * @param index Position of the element.
 * 
 * @returns NULL if data is NULL or index is higher than or equal to array->count.
 */
YUIME_API struct yuime_element_s *yuime_element_pointer_array_get(const yuime_element_pointer_array_t *array, yuime_element_pointer_array_index_t index);

/**
 * @brief Erases an element from array.
 * 
 * @param array Array to erase the element.
 * @param index Position of the element to be erased.
 */
YUIME_API void yuime_element_pointer_array_pop(yuime_element_pointer_array_t *array, yuime_element_pointer_array_index_t index);

/**
 * @brief 
 * 
 * @param mem_funcs 
 * @param array 
 * @param to_reserve 
 * @returns 0 if failed to reallocate.
 */
YUIME_API uint8_t yuime_element_pointer_array_reserve(const yuime_memory_functions_t *mem_funcs, yuime_element_pointer_array_t *array, yuime_element_pointer_array_index_t to_reserve);

/**
 * @brief 
 * 
 * @param mem_funcs 
 * @param array 
 * @returns 0 if failed to reallocate
 */
YUIME_API uint8_t yuime_element_pointer_array_fit_capacity_to_size(const yuime_memory_functions_t *mem_funcs, yuime_element_pointer_array_t *array);