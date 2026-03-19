#pragma once

#include <stdint.h>

#include "../API.h"
#include "event.h"
#include "rect.h"
#include "alloc.h"
#include "geometry.h"

typedef uint8_t yuime_element_flag_t;
typedef enum yuime_element_flag_e {
	YUIME_ELEMENT_FLAG_NONE = 0,
	YUIME_ELEMENT_FLAG_VISIBLE = 1,
	YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE = 2, ///< True if element parent and self is visible. False otherwise.
} yuime_element_flag;

typedef struct yuime_element_object_s {
	uint32_t type; ///< Object type
	void* obj; ///< Object
} yuime_element_object;

typedef struct yuime_element_s {
	yuime_rect rect;

	yuime_event_callback_t event_callback; ///< Function to be called when yuime_context_send_event() is called.

	yuime_element_object self;
	yuime_element_object parent;

	yuime_element_flag_t flags;
} yuime_element;


/**
 * @brief Sets default values for the given element.
 * @param element Element to initialize.
 */
YUIME_API void yuime_element_init(yuime_element* element, yuime_event_callback_t event_callback, yuime_element_object self, uint8_t flags);


typedef uint32_t yuime_element_array_index_t;

typedef struct yuime_element_array_s {
	yuime_element_array_index_t capacity;
	yuime_element_array_index_t count;
	yuime_element* data;
} yuime_element_array;

/**
 * @brief Initializes an element array.
 * 
 * @param mem_funcs 
 * @param array 
 * @param initial_capacity 
 * 
 * @returns 0 if failed to allocate initial capacity.
 */
YUIME_API uint8_t yuime_element_array_init(yuime_mem_functions* mem_funcs, yuime_element_array *array, yuime_element_array_index_t initial_capacity);
YUIME_API void yuime_element_array_free(yuime_mem_functions* mem_funcs, yuime_element_array *array);

/**
 * @brief Copies an element to the array.
 * 
 * @param mem_funcs 
 * @param array 
 * @param value 
 * 
 * @returns 0 if failed to allocate/reallocate.
 */
YUIME_API uint8_t yuime_element_array_push(yuime_mem_functions* mem_funcs, yuime_element_array *array, const yuime_element *value);

/**
 * @brief Gets an element from array at index.
 * 
 * @param array Array to get element from.
 * @param index Position of the element.
 * 
 * @returns NULL if data is NULL or index is higher than or equal to array->count.
 */
YUIME_API yuime_element* yuime_element_array_get(const yuime_element_array *array, yuime_element_array_index_t index);
/**
 * @brief Erases an element from array.
 * 
 * @param array Array to erase the element.
 * @param index Position of the element to be erased.
 */
YUIME_API void yuime_element_array_pop(yuime_element_array *array, yuime_element_array_index_t index);

/**
 * @brief 
 * 
 * @param mem_funcs 
 * @param array 
 * @param to_reserve 
 * @returns 0 if failed to reallocate.
 */
YUIME_API uint8_t yuime_element_array_reserve(yuime_mem_functions* mem_funcs, yuime_element_array *array, yuime_element_array_index_t to_reserve);
/**
 * @brief 
 * 
 * @param mem_funcs 
 * @param array 
 * @returns 0 if failed to reallocate
 */
YUIME_API uint8_t yuime_element_array_fit_capacity_to_size(yuime_mem_functions* mem_funcs, yuime_element_array *array);