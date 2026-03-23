#include "yuime/node.h"

#include <string.h>

#include "yuime/alloc.h"
#include "yuime/context.h"

inline yuime_node_t *_yuime_get_node_last_sibling(yuime_node_t *node) {
	while (node->next != NULL)
		node = node->next;
	return node;
}

inline yuime_node_t *_yuime_allocate_node(yuime_mem_alloc_t mem_alloc, yuime_node_t *node) {
	if (!mem_alloc(&node, sizeof(yuime_node_t)))
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