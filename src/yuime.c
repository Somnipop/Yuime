#include "yuime/yuime.h"

#include "yuime/util.h"

static void _yuime_set_element_children_visibility(const yuime_memory_functions *mem_funcs, yuime_element_pointer_array *children, yuime_element_pointer_array_index_t i, void *data) {
	if (children->data[i]->flags & YUIME_ELEMENT_FLAG_VISIBLE) {
		children->data[i]->flags = (children->data[i]->flags & ~YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE) | (children->data[i]->parent->flags & YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE);
	}
}

void yuime_set_visibility(const yuime_memory_functions *mem_funcs, yuime_element *element, uint8_t visible) {
	// Do not call this function if the result will be the same.
	if ((element->flags & YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE) == visible ||
	  (!(element->flags & YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE) && !visible)) {
		return;
	}

	// Set visible state
	if (visible) {
		element->flags |= YUIME_ELEMENT_FLAG_VISIBLE;
		
		if (0) { // commented out code
			yuime_element *parent = element->parent;
			while (parent != NULL) {
				if ((parent->flags & YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE) ^ YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE) {
					element->flags &= ~YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE;
					return;
				}

				parent = parent->parent;
			}

			element->flags |= YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE;
		} else {
			// Inherit parent visibility flag
			if (element->parent == NULL) {
				element->flags |= YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE;
			} else {
				element->flags = (element->flags & ~YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE) | (element->parent->flags & YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE);
			}
		}
	} else {
		element->flags &= ~(YUIME_ELEMENT_FLAG_VISIBLE|YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE);
	}

	// Update children
	yuime_element_children_iterate(mem_funcs, &element->children, _yuime_set_element_children_visibility, NULL);
}


void yuime_update(yuime_context *ctx) {
	/*
	Sudado.cursorBlinkTimer = Sudado.cursorBlinkTimer + engine.getDeltaTime()
	if Sudado.cursorBlinkTimer >= Sudado.cursorBlinkInterval then
		Sudado.shouldDrawCursor = not Sudado.shouldDrawCursor
		Sudado.cursorBlinkTimer = 0.0
	end

	for _, e in ipairs(Sudado.elements) do
		if e and e.update then e:update() end
	end
	*/
	for (yuime_element_array_index_t i = 0; i < ctx->elements.count; ++i) {
		if (ctx->elements.data[i].flags | YUIME_ELEMENT_FLAG_VISIBLE)
		ctx->render.element(ctx, &ctx->elements.data[i], ctx->render.data);
	}
}

void yuime_draw(yuime_context *ctx) {
	for (yuime_element_array_index_t i = 0; i < ctx->elements.count; ++i) {
		if (ctx->elements.data[i].flags & YUIME_ELEMENT_FLAG_PARENT_RELATED_VISIBLE) {
			ctx->render.element(ctx, &ctx->elements.data[i], ctx->render.data);
		}
	}
}