#pragma once

#include <pebble.h>

#define STL_DEBUG false

typedef Layer SlidingTextLayer;

SlidingTextLayer* sliding_text_layer_create(GRect rect);
void sliding_text_layer_destroy(SlidingTextLayer* layer);
void sliding_text_layer_animate_up(SlidingTextLayer* layer, uint16_t duration);
void sliding_text_layer_animate_down(SlidingTextLayer* layer, uint16_t duration);
void sliding_text_layer_set_text(SlidingTextLayer* layer, char* text);
void sliding_text_layer_set_next_text(SlidingTextLayer* layer, char* text);
void sliding_text_layer_set_font(SlidingTextLayer* layer, GFont* font);
void sliding_text_layer_set_text_color(SlidingTextLayer* layer, GColor color);

#define sliding_text_layer_add_to_window(layer, window) layer_add_child(window_get_root_layer(window), (Layer*)layer);
