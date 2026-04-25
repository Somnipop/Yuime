#include "yuime/render/command.h"

uint8_t yuime_render_command_array_init(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array, yuime_render_command_array_size_t initial_capacity) {
    array->count = 0;
    if (initial_capacity == 0)
        array->commands = ((void *)0);
    else if (!mem_funcs->alloc(YUIME_ALLOC_CONTEXT_RENDER_COMMAND, (void*)&array->commands, initial_capacity * sizeof(yuime_render_command_t)))
        return 0;
    array->capacity = initial_capacity;
    return 1;
}

uint8_t yuime_render_command_array_push(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array, const yuime_render_command_t *value) {
    if (array->count == array->capacity) {
        if (array->commands == ((void *)0)) {
            if (!mem_funcs->alloc(YUIME_ALLOC_CONTEXT_RENDER_COMMAND, (void*)&array->commands, (array->capacity + 1) * sizeof(yuime_render_command_t)))
                return 0;
        } else if (!mem_funcs->realloc(YUIME_ALLOC_CONTEXT_RENDER_COMMAND, (void*)&array->commands, array->capacity * sizeof(yuime_render_command_t), (array->capacity + 1) * sizeof(yuime_render_command_t)))
            return 0;
        array->capacity++;
    }
    array->commands[array->count++] = *value;
    return 1;
}

void yuime_render_command_array_free(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array) {
    if (array->commands == ((void *)0))
        return;
    mem_funcs->free(YUIME_ALLOC_CONTEXT_RENDER_COMMAND, (void*)array->commands, array->capacity * sizeof(yuime_render_command_t));
    array->commands = ((void *)0);
    array->count = array->capacity = 0;
}

yuime_render_command_t *yuime_render_command_array_get(const yuime_render_command_array_t *array, yuime_render_command_array_size_t index) {
    if (array->commands == ((void *)0) || index >= array->count)
        return ((void *)0);
    return array->commands + index;
}

void yuime_render_command_array_pop(yuime_render_command_array_t *array, yuime_render_command_array_size_t index) {
    for (yuime_render_command_array_size_t i = index; i + 1 < array->count; ++i) {
        array->commands[i] = array->commands[i + 1];
    }
    array->count--;
}

uint8_t yuime_render_command_array_reserve(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array, yuime_render_command_array_size_t to_reserve) {
    if (!mem_funcs->realloc(YUIME_ALLOC_CONTEXT_RENDER_COMMAND, (void*)&array->commands, array->capacity * sizeof(yuime_render_command_t), (array->capacity + to_reserve) * sizeof(yuime_render_command_t)))
        return 0;
    array->capacity += to_reserve;
    return 1;
}

void yuime_render_command_array_fit_capacity_to_size(const yuime_mem_functions_t *mem_funcs, yuime_render_command_array_t *array) {
    if (array->capacity == array->count)
        return;
    if (array->count == 0) {
        yuime_render_command_array_free(mem_funcs, array);
        return;
    }
    mem_funcs->realloc(YUIME_ALLOC_CONTEXT_RENDER_COMMAND, (void*)&array->commands, array->capacity * sizeof(yuime_render_command_t), array->count * sizeof(yuime_render_command_t));
    array->capacity = array->count;
}