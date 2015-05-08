/*

SlidingTextLayer v1.0

----------------------

The MIT License (MIT)

Copyright © 2015 Matthew Tole

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

--------------------

lib/sliding-text-layer.h

*/


#pragma once


#include <pebble.h>


#define STL_DEBUG false


typedef Layer SlidingTextLayer;


SlidingTextLayer* sliding_text_layer_create(GRect rect);
void sliding_text_layer_destroy(SlidingTextLayer* layer);
void sliding_text_layer_animate_up(SlidingTextLayer* layer);
void sliding_text_layer_animate_down(SlidingTextLayer* layer);
void sliding_text_layer_set_text(SlidingTextLayer* layer, char* text);
void sliding_text_layer_set_next_text(SlidingTextLayer* layer, char* text);
void sliding_text_layer_set_duration(SlidingTextLayer* layer, uint16_t duration);
void sliding_text_layer_set_animation_curve(SlidingTextLayer* layer, AnimationCurve curve);
void sliding_text_layer_set_font(SlidingTextLayer* layer, GFont* font);
void sliding_text_layer_set_text_color(SlidingTextLayer* layer, GColor color);
void sliding_text_layer_set_text_alignment(SlidingTextLayer* layer, GTextAlignment alignment);
void sliding_text_layer_set_vertical_adjustment(SlidingTextLayer* layer, int8_t adjust);


#define sliding_text_layer_add_to_window(layer, window) layer_add_child(window_get_root_layer(window), (Layer*)layer);
