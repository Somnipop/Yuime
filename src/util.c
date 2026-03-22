#include "yuime/util.h"

#include "yuime/base/element/element.h"

typedef uint16_t _yuime_element_children_node_index_t;
typedef struct _yuime_children_node_s {
	yuime_element_pointer_array_t *children;
	yuime_element_pointer_array_index_t index;
} _yuime_children_node;

typedef struct _yuime_children_tree_s {
	yuime_element_pointer_array_index_t capacity;
	yuime_element_pointer_array_index_t count;
	_yuime_children_node *nodes;
} _yuime_children_tree;

uint8_t _yuime_children_tree_init(const yuime_memory_functions_t *mem_funcs, _yuime_children_tree *array, yuime_element_pointer_array_index_t initial_capacity) {
	array->count = 0;
	if (initial_capacity == 0)
		array->nodes = ((void *)0);
	else if (!mem_funcs->alloc(&array->nodes, initial_capacity * sizeof(_yuime_children_node)))
		return 0;
	array->capacity = initial_capacity;
	return 1;
}

uint8_t _yuime_children_tree_push(const yuime_memory_functions_t *mem_funcs, _yuime_children_tree *array, const _yuime_children_node *value) {
	if (array->count == array->capacity) {
		if (array->nodes == ((void *)0)) {
			if (!mem_funcs->alloc(&array->nodes, (array->capacity + 1) * sizeof(_yuime_children_node)))
				return 0;
		}
		else if (!mem_funcs->realloc(&array->nodes, array->capacity * sizeof(_yuime_children_node), (array->capacity + 1) * sizeof(_yuime_children_node))) {
			return 0;
		}
		array->capacity++;
	}
	array->nodes[array->count++] = *value;
	return 1;
}

void _yuime_children_tree_free(const yuime_memory_functions_t *mem_funcs, _yuime_children_tree *array) {
	if (array->nodes == ((void *)0))
		return;
	mem_funcs->free(array->nodes, array->capacity * sizeof(_yuime_children_node));
	array->nodes = ((void *)0);
	array->count = array->capacity = 0;
}

_yuime_children_node *_yuime_children_tree_get(const _yuime_children_tree *array, yuime_element_pointer_array_index_t index) {
	if (array->nodes == ((void *)0) || index >= array->count)
		return ((void *)0);
	return array->nodes + index;
}

void _yuime_children_tree_pop(_yuime_children_tree *array, yuime_element_pointer_array_index_t index) {
	for (yuime_element_pointer_array_index_t i = index; i < array->count; ++i) {
		array->nodes[i] = array->nodes[i + 1];
	}
	array->count--;
}

uint8_t _yuime_children_tree_reserve(yuime_memory_functions_t *mem_funcs, _yuime_children_tree *array, yuime_element_pointer_array_index_t to_reserve) {
	if (!mem_funcs->realloc(&array->nodes, array->capacity * sizeof(_yuime_children_node), (array->capacity + to_reserve) * sizeof(_yuime_children_node)))
		return 0;
	array->capacity += to_reserve;
	return 1;
}

void _yuime_children_tree_fit_capacity_to_size(yuime_memory_functions_t *mem_funcs, _yuime_children_tree *array) {
	if (array->capacity == array->count)
		return;
	if (array->count == 0) {
		_yuime_children_tree_free(mem_funcs, array);
		return;
	}
	mem_funcs->realloc(&array->nodes, array->capacity * sizeof(_yuime_children_node), array->count * sizeof(_yuime_children_node));
	array->capacity = array->count;
}


void yuime_element_children_iterate(const yuime_memory_functions_t *mem_funcs, yuime_element_pointer_array_t *children, yuime_element_children_iterate_callback_t callback, void *data) {
	if (children == NULL || callback == NULL) {
		return;
	}

	_yuime_children_tree tree;
	_yuime_children_tree_init(mem_funcs, &tree, 8);

	_yuime_children_node first_node;
	first_node.children = children;
	first_node.index = 0;

	_yuime_children_tree_push(mem_funcs, &tree, &first_node);

	yuime_element_pointer_array_index_t i = 0;
	while (tree.count > 0) {
		tree.nodes[tree.count-1].index = i;

		if (i < children->count) {
			callback(mem_funcs, children, i, data);
	
			if (children->data[i]->children.count > 0) {
				_yuime_children_node node;
				node.children = &children->data[i]->children;
				node.index = 0;
	
				if (!_yuime_children_tree_push(mem_funcs, &tree, &node)) {
					_yuime_children_tree_free(mem_funcs, &tree);
					return;
				}
	
				children = tree.nodes[tree.count-1].children;
				i = 0;
				continue;
			}
		}

		while (i >= children->count) {
			_yuime_children_tree_pop(&tree, tree.count-1);
			if (tree.count == 0) {
				break;
			}

			children = tree.nodes[tree.count-1].children;
			i = tree.nodes[tree.count-1].index;
		}

		i++;
	}
	/*
	while #temp ~= 0 do
		i = i + 1
		temp[#temp].index = i

		callback(children, i)

		if children[i].children then
			temp[#temp+1] = {children=children[i].children, index=0}
			children = temp[#temp].children
			i = 0
		end

		while i >= #children do
			temp[#temp] = nil
			if temp[#temp] == nil then -- weird looking code
				break
			end

			children = temp[#temp].children
			i = temp[#temp].index
		end
	end
	*/
	_yuime_children_tree_free(mem_funcs, &tree);
}