#pragma once

#include <stdint.h>

#include "API.h"

#include "math/rect.h"
#include "math/vector2.h"
#include "math/geometry.h"
#include "math/dimension2.h"

#include "widget/widget.h"

/*
---@alias Sudado.IsPointCollidingDragRegion fun(self: any, point: SDL.FPoint): boolean
---@alias Sudado.GetResizeRegionFromPointCollision fun(self: any, point: SDL.Point): Sudado.ResizeRegion
*/

struct yuime_context_s;
struct yuime_node_s;

typedef void(*yuime_window_resize_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_vector2_t ratio, yuime_vector2_t delta);

typedef void(*yuime_resize_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node);
typedef void(*yuime_move_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node);

// previous_focused_node can be NULL.
typedef void(*yuime_focus_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, struct yuime_node_s *previous_focused_node);
// new_focused_node can be NULL.
typedef void(*yuime_unfocus_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, struct yuime_node_s *new_focused_node);

// previous_hovered_node can be NULL.
typedef void(*yuime_hover_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, struct yuime_node_s *previous_hovered_node);
// new_hovered_node can be NULL.
typedef void(*yuime_unhover_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, struct yuime_node_s *new_hovered_node);

typedef void(*yuime_mouse_button_press_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, uint8_t button, yuime_vector2_t mouse_position);
typedef void(*yuime_mouse_button_release_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, uint8_t button, yuime_vector2_t mouse_position);
typedef void(*yuime_mouse_wheel_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_vector2_t direction, yuime_vector2_t mouse_position);

typedef void(*yuime_mouse_move_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_vector2_t mouse_position, yuime_vector2_t mouse_delta);

typedef void(*yuime_key_press_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, uint32_t key);
typedef void(*yuime_key_release_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, uint32_t key);

typedef void(*yuime_char_press_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, uint16_t codepoint);

typedef void(*yuime_update_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node);
typedef void(*yuime_draw_callback_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, void* data);

// TODO: make dynamic arrays for: events, update and draw callbacks.
// TODO: draw callbacks should consider z index when being made.
// TODO: do not let nodes have unecessary code.
// TODO: remove unecessary members from context if any.

/*
---@class Sudado.Element
---@field type Sudado.ElementType
---@field zIndex number DO NOT FORGET TO USE `Sudado.sortElementsByZIndex` WHEN MODIFYING THIS VARIABLE!
---@field visible boolean
---@field _visible boolean Checks if element is visible related to parent.
---@field rect SDL.FRect
---@field draw Sudado.Draw
---@field layout Sudado.Layout?
---@field parent Sudado.Element?
---@field children Sudado.Children?
---@field verticalScrollBar Sudado.VerticalScrollBar?
---@field horizontalScrollBar Sudado.HorizontalScrollBar?
---@field offsetX number?
---@field offsetY number?
---@field minSize SDL.Point?
---@field maxSize SDL.Point?
---@field resizable boolean?
---@field getResizeRegionFromPointCollision Sudado.GetResizeRegionFromPointCollision?
---@field draggable boolean?
---@field isPointCollidingDragRegion Sudado.IsPointCollidingDragRegion?
---@field dragOffset SDL.Point?
---@field backgroundColor SDL.Color?
---@field bordersSizes SDL.Rect|SDL.Point?
---@field borderColor SDL.Color?
---@field updateScrollbars fun(self: Sudado.Element)?
---@field onWindowResize Sudado.OnWindowResize?
---@field onResize Sudado.OnResize? when screen resizes or parent resizes this is called
---@field onMove Sudado.OnMove? when parent moves this is called. This is more for Sudado.Window to move its children
---@field onFocus Sudado.OnFocus?
---@field onUnfocus Sudado.OnUnfocus?
---@field onHover Sudado.OnHover?
---@field onUnhover Sudado.OnUnhover?
---@field onKeyDown Sudado.OnKeyboardPress?
---@field onTextInput Sudado.OnCharPress?
---@field onMouseButtonDown Sudado.OnMousePress?
---@field onMouseMotion Sudado.OnMouseMove?
---@field onMouseButtonUp Sudado.OnMouseUp?
---@field onMouseWheel Sudado.OnMouseWheel?
---@field update Sudado.Update?
*/

typedef struct yuime_node_s {
	struct yuime_node_s *parent;
	struct yuime_node_s *first_child;
	struct yuime_node_s *next;

	yuime_widget_t widget;

	yuime_rect_t *rect;
	yuime_geometry_t *geometry;

	yuime_dim2_t *max_size;
	yuime_dim2_t *min_size;

	yuime_window_resize_callback_t on_window_resize;

	yuime_resize_callback_t on_resize;
	yuime_move_callback_t on_move;

	yuime_focus_callback_t on_focus;
	yuime_unfocus_callback_t on_unfocus;

	yuime_hover_callback_t on_hover;
	yuime_unhover_callback_t on_unhover;

	yuime_mouse_button_press_callback_t on_mouse_button_press;
	yuime_mouse_button_release_callback_t on_mouse_button_release;
	yuime_mouse_wheel_callback_t on_mouse_wheel;

	yuime_mouse_move_callback_t on_mouse_move;

	yuime_key_press_callback_t on_key_press;
	yuime_key_release_callback_t on_key_release;

	yuime_update_callback_t update;
	yuime_draw_callback_t draw;
} yuime_node_t;

struct yuime_context_s;
/**
 * @brief Creates a new node and inserts it in parent.
 * 
 * @param ctx
 * @param parent If NULL, node is created in root.
 * @returns NULL if failed to allocate memory.
 */
YUIME_API yuime_node_t *yuime_node_new(struct yuime_context_s *ctx, struct yuime_node_s *parent);

/**
 * @brief Frees a node together with its children and updates siblings pointers.
 * @param ctx Can not be NULL.
 * @param node Can not be NULL.
 */
YUIME_API void yuime_node_free(struct yuime_context_s *ctx, struct yuime_node_s *node);

typedef uint8_t yuime_children_iterate_return_signal_t;
enum yuime_children_iterate_return_signal_e {
	YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_PASS = 0, ///< Iterates children and next siblings.
	YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_CHILDREN = 1, ///< Does not iterate children. NOTE: In `yuime_node_iterate_children`, it does the same effect as `YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_SIBLING`.
	YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_SIBLING = 2, ///< Does not iterate next siblings.
	YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_BREAK = 3, ///< Does not iterate children nor next siblings. NOTE: In `yuime_node_iterate_children`, it does the same effect as `YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_SIBLING`.
};

/**
 * @see yuime_children_iterate_return_signal_e
 */
typedef yuime_children_iterate_return_signal_t(*yuime_children_iterate_function_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, void* data);

/**
 * @brief Calls iter_function for every node below.
 * 
 * @param ctx Context passed to iter_function. Can be NULL.
 * @param node Parent of the nodes that iter_function will be used.
 * @param iter_function The function to be called for them.
 * @param data Data passed to iter_function. Can be NULL.
 * 
 * @see yuime_node_iterate_children_parent_first
 */
YUIME_API void yuime_node_iterate_children(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_children_iterate_function_t iter_function, void *data);

/**
 * @brief Calls iter_function for every node below, calling iter_function with parent before children.
 * 
 * @param ctx Context passed to iter_function. Can be NULL.
 * @param node Parent of the nodes that iter_function will be used.
 * @param iter_function The function to be called for them.
 * @param data Data passed to iter_function. Can be NULL.
 * 
 * @see yuime_node_iterate_children
 */
YUIME_API void yuime_node_iterate_children_parent_first(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_children_iterate_function_t iter_function, void *data);