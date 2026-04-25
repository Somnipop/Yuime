// Refactoring code from Clay UI since it matches the concept I am trying to do here.
// https://github.com/nicbarker/clay/blob/main/renderers/SDL3/clay_renderer_SDL3.c

#include "sdl.h"

#include <SDL3/SDL.h>

#include <yuime/style/color.h>

#include <yuime/render/render.h>
#include <yuime/render/command.h>

#include <yuime/render/rectangle.h>

// yuime_children_iterate_return_signal_t sdl_render_node(yuime_context_t *ctx, yuime_node_t *node, void* data) {
// 	if (node->rect == NULL /*|| !node->is_visible*/) {
// 		return YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_CHILDREN;
// 	}

// 	// if (node->draw != NULL) {
// 	// 	node->draw(ctx, node, data);
// 	// }

// 	SDL_FRect rect = (SDL_FRect){
// 		node->rect->x,
// 		node->rect->y,
// 		node->rect->w,
// 		node->rect->h
// 	};

// 	// draw border
// 	if (node->widget.widget != NULL && node->widget.type == YUIME_WIDGET_TYPE_PANEL) {
// 		yuime_widget_panel_t *panel = (yuime_widget_panel_t*)node->widget.widget;
// 		SDL_SetRenderDrawColor(renderer, panel->style->border.color.r, panel->style->border.color.g, panel->style->border.color.b, panel->style->border.color.a);
// 	}
// 	SDL_RenderFillRect(renderer, &rect);

// 	// draw rect
// 	// rect = (SDL_FRect){
// 	// 	node->rect.x+node->style->border.size,
// 	// 	node->rect.y+node->style->border.size,
// 	// 	node->rect.w-node->style->border.size*2,
// 	// 	node->rect.h-node->style->border.size*2
// 	// };

// 	// SDL_SetRenderDrawColor(renderer, node->style->color.r, node->style->color.g, node->style->color.b, node->style->color.a);
// 	// SDL_RenderFillRect(renderer, &rect);
// 	return YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_PASS;
// }

#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
// #include <SDL3_ttf/SDL_ttf.h>
// #include <SDL3_image/SDL_image.h>

// typedef struct sdl_renderer_data_s {
//     SDL_Renderer *renderer;
//     TTF_TextEngine *textEngine;
//     TTF_Font **fonts;
// } sdl_renderer_data_t;

/* Global for convenience. Even in 4K this is enough for smooth curves (low radius or rect size coupled with
 * no AA or low resolution might make it appear as jagged curves) */
#define NUM_CIRCLE_SEGMENTS 16

//all rendering is performed by a single SDL call, avoiding multiple RenderRect + plumbing choice for circles.
void SDL_Clay_RenderFillRoundedRect(yuime_context_t *ctx, const SDL_FRect rect, const float radius, const yuime_color_t _color) {
    const SDL_FColor color = { _color.r/255.0f, _color.g/255.0f, _color.b/255.0f, _color.a/255.0f };

    int indexCount = 0, vertexCount = 0;

    const float minRadius = SDL_min(rect.w, rect.h) / 2.0f;
    const float clampedRadius = SDL_min(radius, minRadius);

    const int numCircleSegments = SDL_max(NUM_CIRCLE_SEGMENTS, (int)(clampedRadius * 0.5f));

    // int totalVertices = 4 + (4 * (numCircleSegments * 2)) + 2*4;
    // int totalIndices = 6 + (4 * (numCircleSegments * 3)) + 6*4;

	// totalVertices if numCircleSegments = NUM_CIRCLE_SEGMENTS: 4 + (4 * (numCircleSegments * 2)) + 2*4 = 140
    SDL_Vertex vertices[140];
	// totalIndices if numCircleSegments = NUM_CIRCLE_SEGMENTS: 6 + (4 * (numCircleSegments * 3)) + 6*4 = 222
    int indices[222];

    //define center rectangle
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y + clampedRadius}, color, {0, 0} }; //0 center TL
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y + clampedRadius}, color, {1, 0} }; //1 center TR
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y + rect.h - clampedRadius}, color, {1, 1} }; //2 center BR
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y + rect.h - clampedRadius}, color, {0, 1} }; //3 center BL

    indices[indexCount++] = 0;
    indices[indexCount++] = 1;
    indices[indexCount++] = 3;
    indices[indexCount++] = 1;
    indices[indexCount++] = 2;
    indices[indexCount++] = 3;

    //define rounded corners as triangle fans
    const float step = (SDL_PI_F/2) / numCircleSegments;
    for (int i = 0; i < numCircleSegments; i++) {
        const float angle1 = (float)i * step;
        const float angle2 = ((float)i + 1.0f) * step;

        for (int j = 0; j < 4; j++) {  // Iterate over four corners
            float cx, cy, signX, signY;

            switch (j) {
                case 0: cx = rect.x + clampedRadius; cy = rect.y + clampedRadius; signX = -1; signY = -1; break; // Top-left
                case 1: cx = rect.x + rect.w - clampedRadius; cy = rect.y + clampedRadius; signX = 1; signY = -1; break; // Top-right
                case 2: cx = rect.x + rect.w - clampedRadius; cy = rect.y + rect.h - clampedRadius; signX = 1; signY = 1; break; // Bottom-right
                case 3: cx = rect.x + clampedRadius; cy = rect.y + rect.h - clampedRadius; signX = -1; signY = 1; break; // Bottom-left
                default: return;
            }

            vertices[vertexCount++] = (SDL_Vertex){ {cx + SDL_cosf(angle1) * clampedRadius * signX, cy + SDL_sinf(angle1) * clampedRadius * signY}, color, {0, 0} };
            vertices[vertexCount++] = (SDL_Vertex){ {cx + SDL_cosf(angle2) * clampedRadius * signX, cy + SDL_sinf(angle2) * clampedRadius * signY}, color, {0, 0} };

            indices[indexCount++] = j;  // Connect to corresponding central rectangle vertex
            indices[indexCount++] = vertexCount - 2;
            indices[indexCount++] = vertexCount - 1;
        }
    }

    //Define edge rectangles
    // Top edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y}, color, {0, 0} }; //TL
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y}, color, {1, 0} }; //TR

    indices[indexCount++] = 0;
    indices[indexCount++] = vertexCount - 2; //TL
    indices[indexCount++] = vertexCount - 1; //TR
    indices[indexCount++] = 1;
    indices[indexCount++] = 0;
    indices[indexCount++] = vertexCount - 1; //TR
    // Right edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w, rect.y + clampedRadius}, color, {1, 0} }; //RT
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w, rect.y + rect.h - clampedRadius}, color, {1, 1} }; //RB

    indices[indexCount++] = 1;
    indices[indexCount++] = vertexCount - 2; //RT
    indices[indexCount++] = vertexCount - 1; //RB
    indices[indexCount++] = 2;
    indices[indexCount++] = 1;
    indices[indexCount++] = vertexCount - 1; //RB
    // Bottom edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + rect.w - clampedRadius, rect.y + rect.h}, color, {1, 1} }; //BR
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x + clampedRadius, rect.y + rect.h}, color, {0, 1} }; //BL

    indices[indexCount++] = 2;
    indices[indexCount++] = vertexCount - 2; //BR
    indices[indexCount++] = vertexCount - 1; //BL
    indices[indexCount++] = 3;
    indices[indexCount++] = 2;
    indices[indexCount++] = vertexCount - 1; //BL
    // Left edge
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x, rect.y + rect.h - clampedRadius}, color, {0, 1} }; //LB
    vertices[vertexCount++] = (SDL_Vertex){ {rect.x, rect.y + clampedRadius}, color, {0, 0} }; //LT

    indices[indexCount++] = 3;
    indices[indexCount++] = vertexCount - 2; //LB
    indices[indexCount++] = vertexCount - 1; //LT
    indices[indexCount++] = 0;
    indices[indexCount++] = 3;
    indices[indexCount++] = vertexCount - 1; //LT

    // Render everything
    SDL_RenderGeometry((SDL_Renderer*)ctx->render.data, NULL, vertices, vertexCount, indices, indexCount);
}

void SDL_Clay_RenderArc(yuime_context_t *ctx, const SDL_FPoint center, const float radius, const float startAngle, const float endAngle, const float thickness, const yuime_color_t color) {
    SDL_Renderer *renderer = (SDL_Renderer*)ctx->render.data;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const float radStart = startAngle * (SDL_PI_F / 180.0f);
    const float radEnd = endAngle * (SDL_PI_F / 180.0f);

    const int numCircleSegments = SDL_max(NUM_CIRCLE_SEGMENTS, (int)(radius * 1.5f)); //increase circle segments for larger circles, 1.5 is arbitrary.

    const float angleStep = (radEnd - radStart) / (float)numCircleSegments;
    const float thicknessStep = 0.4f; //arbitrary value to avoid overlapping lines. Changing THICKNESS_STEP or numCircleSegments might cause artifacts.

    for (float t = thicknessStep; t < thickness - thicknessStep; t += thicknessStep) {
        SDL_FPoint points[NUM_CIRCLE_SEGMENTS + 1];
        const float clampedRadius = SDL_max(radius - t, 1.0f);

        for (int i = 0; i <= numCircleSegments; i++) {
            const float angle = radStart + i * angleStep;
            points[i] = (SDL_FPoint){
                    SDL_roundf(center.x + SDL_cosf(angle) * clampedRadius),
                    SDL_roundf(center.y + SDL_sinf(angle) * clampedRadius) };
        }
        SDL_RenderLines(renderer, points, numCircleSegments + 1);
    }
}

SDL_Rect currentClippingRectangle;

void sdl_render_commands(yuime_context_t *ctx) {
	SDL_Renderer *renderer = (SDL_Renderer*)ctx->render.data;

    for (yuime_render_command_array_size_t i = 0; i < ctx->render.render_commands.count; i++) {
        yuime_render_command_t *rcmd = yuime_render_command_array_get(&ctx->render.render_commands, i);

        switch (rcmd->type) {
		case YUIME_RENDER_COMMAND_TYPE_RECTANGLE: {
			yuime_command_rect_t *config = (yuime_command_rect_t*)rcmd->data;
			SDL_FRect rect = {
				config->rect->x,
				config->rect->y,
				config->rect->w,
				config->rect->h
			};

			SDL_SetRenderDrawColor(renderer, config->background_color->r, config->background_color->g, config->background_color->b, config->background_color->a);

			if (config->border_radius->top_left_radius > 0) {
				SDL_Clay_RenderFillRoundedRect(ctx, rect, config->border_radius->top_left_radius, *config->background_color);
			} else {
				SDL_RenderFillRect(renderer, &rect);
			}
		} break;
		// TODO: Text
		// case YUIME_RENDER_COMMAND_TYPE_TEXT: {
		//     Clay_TextRenderData *config = &rcmd->renderData.text;
		//     TTF_Font *font = fonts[config->fontId];
		//     TTF_SetFontSize(font, config->fontSize);
		//     TTF_Text *text = TTF_CreateText(textEngine, font, config->stringContents.chars, config->stringContents.length);
		//     TTF_SetTextColor(text, config->textColor.r, config->textColor.g, config->textColor.b, config->textColor.a);
		//     TTF_DrawRendererText(text, rect.x, rect.y);
		//     TTF_DestroyText(text);
		// } break;
		case YUIME_RENDER_COMMAND_TYPE_BORDER: {
			yuime_command_border_t *config = (yuime_command_border_t*)rcmd->data;
			SDL_FRect rect = {
				config->rect->x,
				config->rect->y,
				config->rect->w,
				config->rect->h
			};

			const float minRadius = SDL_min(rect.w, rect.h) / 2.0f;
			const yuime_style_border_corners_t clampedRadii = {
				.top_left_radius = SDL_min(config->corners->top_left_radius, minRadius),
				.top_right_radius = SDL_min(config->corners->top_right_radius, minRadius),
				.bottom_left_radius = SDL_min(config->corners->bottom_left_radius, minRadius),
				.bottom_right_radius = SDL_min(config->corners->bottom_right_radius, minRadius),
				.color = config->corners->color
			};

			// Edges
			if (config->left->size > 0) {
				const float starting_y = rect.y + clampedRadii.top_left_radius;
				const float length = rect.h - clampedRadii.top_left_radius - clampedRadii.bottom_left_radius;
				SDL_FRect line = { rect.x - 1, starting_y, config->left->size, length };
				SDL_SetRenderDrawColor(renderer, config->left->color.r, config->left->color.g, config->left->color.b, config->left->color.a);
				SDL_RenderFillRect(renderer, &line);
			}

			if (config->right->size > 0) {
				const float starting_x = rect.x + rect.w - (float)config->right->size + 1;
				const float starting_y = rect.y + clampedRadii.top_right_radius;
				const float length = rect.h - clampedRadii.top_right_radius - clampedRadii.bottom_right_radius;
				SDL_FRect line = { starting_x, starting_y, config->right->size, length };
				SDL_SetRenderDrawColor(renderer, config->right->color.r, config->right->color.g, config->right->color.b, config->right->color.a);
				SDL_RenderFillRect(renderer, &line);
			}

			if (config->top->size > 0) {
				const float starting_x = rect.x + clampedRadii.top_left_radius;
				const float length = rect.w - clampedRadii.top_left_radius - clampedRadii.top_right_radius;
				SDL_FRect line = { starting_x, rect.y - 1, length, config->top->size };
				SDL_SetRenderDrawColor(renderer, config->top->color.r, config->top->color.g, config->top->color.b, config->top->color.a);
				SDL_RenderFillRect(renderer, &line);
			}

			if (config->bottom->size > 0) {
				const float starting_x = rect.x + clampedRadii.bottom_left_radius;
				const float starting_y = rect.y + rect.h - (float)config->bottom->size + 1;
				const float length = rect.w - clampedRadii.bottom_left_radius - clampedRadii.bottom_right_radius;
				SDL_FRect line = { starting_x, starting_y, length, config->bottom->size };
				SDL_SetRenderDrawColor(renderer, config->bottom->color.r, config->bottom->color.g, config->bottom->color.b, config->bottom->color.a);
				SDL_RenderFillRect(renderer, &line);
			}

			// Corners
			if (config->corners->top_left_radius > 0) {
				const float centerX = rect.x + clampedRadii.top_left_radius -1;
				const float centerY = rect.y + clampedRadii.top_left_radius - 1;
				SDL_Clay_RenderArc(ctx, (SDL_FPoint){centerX, centerY}, clampedRadii.top_left_radius,
					180.0f, 270.0f, config->top->size, config->corners->color);
			}
			if (config->corners->top_right_radius > 0) {
				const float centerX = rect.x + rect.w - clampedRadii.top_right_radius;
				const float centerY = rect.y + clampedRadii.top_right_radius - 1;
				SDL_Clay_RenderArc(ctx, (SDL_FPoint){centerX, centerY}, clampedRadii.top_right_radius,
					270.0f, 360.0f, config->top->size, config->corners->color);
			}
			if (config->corners->bottom_left_radius > 0) {
				const float centerX = rect.x + clampedRadii.bottom_left_radius -1;
				const float centerY = rect.y + rect.h - clampedRadii.bottom_left_radius;
				SDL_Clay_RenderArc(ctx, (SDL_FPoint){centerX, centerY}, clampedRadii.bottom_left_radius,
					90.0f, 180.0f, config->bottom->size, config->corners->color);
			}
			if (config->corners->bottom_right_radius > 0) {
				const float centerX = rect.x + rect.w - clampedRadii.bottom_right_radius;
				const float centerY = rect.y + rect.h - clampedRadii.bottom_right_radius;
				SDL_Clay_RenderArc(ctx, (SDL_FPoint){centerX, centerY}, clampedRadii.bottom_right_radius,
					0.0f, 90.0f, config->bottom->size, config->corners->color);
			}

		} break;
		// TODO:
		// case YUIME_RENDER_COMMAND_TYPE_SCISSOR_START: {
		//     Clay_BoundingBox boundingBox = rcmd->boundingBox;
		//     currentClippingRectangle = (SDL_Rect) {
		//             .x = boundingBox.x,
		//             .y = boundingBox.y,
		//             .w = boundingBox.width,
		//             .h = boundingBox.height,
		//     };
		//     SDL_SetRenderClipRect(renderer, &currentClippingRectangle);
		//     break;
		// }
		// TODO:
		// case YUIME_RENDER_COMMAND_TYPE_SCISSOR_END: {
		//     SDL_SetRenderClipRect(renderer, NULL);
		//     break;
		// }
		// TODO:
		// case YUIME_RENDER_COMMAND_TYPE_IMAGE: {
		//     SDL_Texture *texture = (SDL_Texture *)rcmd->renderData.image.imageData;
		//     const SDL_FRect dest = { rect.x, rect.y, rect.w, rect.h };
		//     SDL_RenderTexture(renderer, texture, NULL, &dest);
		//     break;
		// }
		default:
			SDL_Log("Unknown render command type: %d", rcmd->type);
        }
    }
}