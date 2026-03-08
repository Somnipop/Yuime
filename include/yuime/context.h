#pragma once

#include "alloc.h"
#include "element.h"

typedef struct yuime_context_s {
	yuime_mem_functions memory;
	yuime_element_array elements;
} yuime_context;

/**
 * @brief Sets default values for the given context.
 * @param ctx Context to initialize.
 * @param mem_functions memory functions related to memory allocation and deallocation.
 */
YUIME_API void yuime_context_init(yuime_context* ctx, yuime_mem_functions mem_functions);

/**
 * @brief Adds an element to ctx->elements
 * @param ctx Context to add element to.
 * @param element Memory address of the element to add.
 * @returns NULL if failed.
 */
YUIME_API yuime_element* yuime_context_element_add(yuime_context* ctx, yuime_element element);