#pragma once

#include <stdint.h>

#include "../API.h"

#include "../alloc.h"

struct yuime_context_s;

typedef void(*yuime_render_commands_function_t)(struct yuime_context_s *ctx);

typedef uint8_t yuime_render_command_type_t;
enum yuime_render_command_type_e {
	YUIME_RENDER_COMMAND_TYPE_RECTANGLE = 0,
	YUIME_RENDER_COMMAND_TYPE_TEXT,
	YUIME_RENDER_COMMAND_TYPE_BORDER,
	YUIME_RENDER_COMMAND_TYPE_SCISSOR_START,
	YUIME_RENDER_COMMAND_TYPE_SCISSOR_END,
	YUIME_RENDER_COMMAND_TYPE_IMAGE
};

typedef struct yuime_render_command_s {
	yuime_render_command_type_t type;
	void* data;
} yuime_render_command_t;


typedef uint32_t yuime_render_command_array_size_t;
typedef struct yuime_render_command_array_s {
	yuime_render_command_array_size_t capacity;
	yuime_render_command_array_size_t count;
	yuime_render_command_t *commands;
} yuime_render_command_array_t;


/**
 * @brief 
 * @param mem_funcs 
 * @param array 
 * @param initial_capacity 
 * @returns 0 if failed to allocate initial capacity.
 */
YUIME_API uint8_t yuime_render_command_array_init(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array, yuime_render_command_array_size_t initial_capacity);

/**
 * @brief 
 * @param mem_funcs 
 * @param array 
 * @param initial_capacity 
 * @returns 0 if failed to allocate/reallocate.
 */
YUIME_API uint8_t yuime_render_command_array_push(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array, const yuime_render_command_t *value);

YUIME_API void yuime_render_command_array_free(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array);

/**
 * @brief 
 * @param mem_funcs 
 * @param array 
 * @param initial_capacity 
 * @returns NULL if data is NULL or index is higher than or equal to array->count.
 */
YUIME_API yuime_render_command_t *yuime_render_command_array_get(const yuime_render_command_array_t *array, yuime_render_command_array_size_t index);

YUIME_API void yuime_render_command_array_pop(yuime_render_command_array_t *array, yuime_render_command_array_size_t index);

/**
 * @brief 
 * @param mem_funcs 
 * @param array 
 * @param to_reserve 
 * @returns 0 if failed to reallocate.
 */
YUIME_API uint8_t yuime_render_command_array_reserve(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array, yuime_render_command_array_size_t to_reserve);
YUIME_API void yuime_render_command_array_fit_capacity_to_size(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array);