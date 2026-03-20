#pragma once

#include "API.h"
#include "base/element_pointer_array.h"

typedef void(*yuime_element_children_iterate_callback_t)(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *children, yuime_element_pointer_array_index_t index, void *data);

YUIME_API void yuime_element_children_iterate(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *children, yuime_element_children_iterate_callback_t callback, void *data);