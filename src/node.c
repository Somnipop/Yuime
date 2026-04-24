#include "yuime/node.h"

#include <string.h>

#include "yuime/math/geometry.h"
#include "yuime/math/dimension2.h"

#include "yuime/alloc.h"
#include "yuime/context.h"

static inline yuime_node_t *_yuime_get_node_last_sibling(yuime_node_t *node) {
	while (node->next != NULL)
		node = node->next;
	return node;
}

static inline yuime_node_t *_yuime_allocate_node(yuime_mem_alloc_t mem_alloc, yuime_node_t *node) {
	if (!mem_alloc(YUIME_ALLOC_CONTEXT_NODE, &node, sizeof(yuime_node_t)))
		return NULL;

	memset(node, 0, sizeof(yuime_node_t));
	return node;
}

yuime_node_t *yuime_node_new(struct yuime_context_s *ctx, struct yuime_node_s *parent) {
	if (ctx == NULL)
		return NULL;

	yuime_node_t* previous_sibling = NULL;
	if (parent == NULL) {
		if (ctx->node_tree == NULL) {
			ctx->node_tree = _yuime_allocate_node(ctx->memory.alloc, ctx->node_tree);
			return ctx->node_tree;
		}

		previous_sibling = _yuime_get_node_last_sibling(ctx->node_tree);

	} else {
		if (parent->first_child == NULL) {
			parent->first_child = _yuime_allocate_node(ctx->memory.alloc, parent->first_child);
			parent->first_child->parent = parent;
			return parent->first_child;
		}

		previous_sibling = _yuime_get_node_last_sibling(parent->first_child);
	}

	previous_sibling->next = _yuime_allocate_node(ctx->memory.alloc, previous_sibling->next);
	previous_sibling->next->parent = parent;
	return previous_sibling->next;
}


static inline void _yuime_node_free_children(yuime_context_t *ctx, yuime_node_t *node) {
	if (node == NULL || node->first_child == NULL) {
		return;
	}

	yuime_node_t *child = node->first_child;
	yuime_node_t *next_to_process;

	while (child != NULL) {
		next_to_process = child->next;

		_yuime_node_free_children(ctx, child);
		// memset(child, 0, sizeof(yuime_node_t));
		if (child->widget != NULL);
			ctx->memory.free(YUIME_ALLOC_CONTEXT_WIDGET, child->widget, child->widget_size);
		ctx->memory.free(YUIME_ALLOC_CONTEXT_NODE, child, sizeof(yuime_node_t));

		child = next_to_process;
	}
}

/**
 * @returns previous sibling or the node itself, if there's no previous sibling.
 */
static inline yuime_node_t *_yuime_get_node_previous_sibling(yuime_node_t *first_sibling, yuime_node_t *node) {
	if (first_sibling == node || first_sibling == NULL) {
		return node;
	}

	yuime_node_t* previous_sibling = first_sibling;
	yuime_node_t* _previous_sibling;

	while (1) {
		_previous_sibling = previous_sibling->next;

		if (_previous_sibling == node || _previous_sibling == NULL)
			return previous_sibling;

		previous_sibling = _previous_sibling;
	}
}

void yuime_node_free(struct yuime_context_s *ctx, struct yuime_node_s *node) {
	if (ctx == NULL || node == NULL)
		return;

	_yuime_node_free_children(ctx, node);

	_yuime_get_node_previous_sibling(node->parent == NULL ? ctx->node_tree : node->parent->first_child, node)->next = node->next;

	if (node->parent != NULL && node->parent->first_child == node) {
		node->parent->first_child = node->next;

	} else if (node->parent == NULL && ctx->node_tree == node) {
		ctx->node_tree = node->next;
	}

	if (node->widget != NULL) {
		ctx->memory.free(YUIME_ALLOC_CONTEXT_WIDGET, node->widget, node->widget_size);
	}
	ctx->memory.free(YUIME_ALLOC_CONTEXT_NODE, node, sizeof(yuime_node_t));
}


void yuime_node_iterate_children(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_children_iterate_function_t iter_function, void *data) {
	if (node == NULL || node->first_child == NULL || iter_function == NULL) {
		return;
	}

	yuime_node_t *child = node->first_child;
	yuime_node_t *next_sibling;
	while (child != NULL) {
		next_sibling = child->next;

		if (child->first_child != NULL) {
			yuime_node_iterate_children(ctx, child, iter_function, data);
		}

		if (iter_function(ctx, child, data) != YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_PASS) {
			break;
		}

		child = next_sibling;
	}
}

void yuime_node_iterate_children_parent_first(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_children_iterate_function_t iter_function, void *data) {
	if (node == NULL || node->first_child == NULL || iter_function == NULL) {
		return;
	}

	yuime_children_iterate_return_signal_t iter_result;
	yuime_node_t *child = node->first_child;
	yuime_node_t *next_sibling;

	while (child != NULL) {
		next_sibling = child->next;

		iter_result = iter_function(ctx, child, data);
		if (iter_result == YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_CHILDREN) {
			child = next_sibling;

		} else if (iter_result == YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_SIBLING) {
			if (child->first_child != NULL) {
				yuime_node_iterate_children_parent_first(ctx, child, iter_function, data);
			}
			break;

		} else if (iter_result == YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_BREAK) {
			break;

		} else { // YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_PASS
			if (child->first_child != NULL) {
				yuime_node_iterate_children_parent_first(ctx, child, iter_function, data);
			}
			child = next_sibling;
		}
	}
}