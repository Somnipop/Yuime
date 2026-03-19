#include "yuime/base/event.h"

#include "yuime/base/context.h"

void yuime_context_send_event(struct yuime_context_s* ctx, void* data) {
	for (size_t i = 0; i < ctx->elements.count; i++) {
		if (ctx->elements.data[i].event_callback != NULL)
			ctx->elements.data[i].event_callback(ctx, ctx->elements.data+i, data);
	}
}

// TODO: instead of having default events, split their code into functions and use them in the examples
// void yuime_event_on_window_resize_default(yuime_context* ctx, yuime_element* element, void* data);
// void yuime_event_on_resize_default(yuime_context* ctx, yuime_element* element, void* data);
// void yuime_event_on_move_default(yuime_context* ctx, yuime_element* element, void* data);