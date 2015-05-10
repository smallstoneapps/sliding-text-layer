/*

SlidingTextLayer v1.1

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


/**
 * Create a new SlidingTextLayer on the heap.
 * @param rect The frame of the SlidingTextLayer.
 * @return Pointer to the newly created SlidingTextLayer.
 */
SlidingTextLayer* sliding_text_layer_create(GRect rect);

/**
 * Destroys a SlidingTextLayer and frees all memory associated with it.
 * @param layer Pointer to the SlidingTextLayer to be destroyed.
 */
void sliding_text_layer_destroy(SlidingTextLayer* layer);

/**
 * Animate to the next text in an upwards direction.
 * @param layer Pointer to the SlidingTextLayer.
 */
void sliding_text_layer_animate_up(SlidingTextLayer* layer);

/**
 * Animate to the next text in an downwards direction.
 * @param layer Pointer to the SlidingTextLayer.
 */
void sliding_text_layer_animate_down(SlidingTextLayer* layer);

/**
 * Animate a small bounce up to show there are no more items.
 * @param layer Pointer to the SlidingTextLayer.
 */
void sliding_text_layer_animate_bounce_up(SlidingTextLayer* layer);

/**
 * Animate a small bounce down to show there are no more items.
 * @param layer Pointer to the SlidingTextLayer.
 */
void sliding_text_layer_animate_bounce_down(SlidingTextLayer* layer);

/**
 * Set the currently displayed text.
 * @param layer Pointer to the SlidingTextLayer.
 * @param text Text to be used. The SlidingTextLayer will not copy this string.
 */
void sliding_text_layer_set_text(SlidingTextLayer* layer, char* text);

/**
 * Set the next text that will be used in the next animation.
 * @param layer Pointer to the SlidingTextLayer.
 * @param text Text to be used in next animation. The SlidingTextLayer will not copy this string.
 */
void sliding_text_layer_set_next_text(SlidingTextLayer* layer, char* text);

/**
 * Set the duration of the animation.
 * @param layer Pointer to the SlidingTextLayer.
 * @param duration Duration (in milliseconds) of the animations
 */
void sliding_text_layer_set_duration(SlidingTextLayer* layer, uint16_t duration);

/**
 * Set the curve function of the animation.
 * @param layer Pointer to the SlidingTextLayer.
 * @param curve AnimationCurve to use.
 */
void sliding_text_layer_set_animation_curve(SlidingTextLayer* layer, AnimationCurve curve);

/**
 * Set the font to use for the layer.
 * @param layer Pointer to the SlidingTextLayer.
 * @param font Font to use when rendering the text.
 */
void sliding_text_layer_set_font(SlidingTextLayer* layer, GFont* font);

/**
 * Set the color of the text.
 * @param layer Pointer to the SlidingTextLayer.
 * @param color Color to use when rendering the text.
 */
void sliding_text_layer_set_text_color(SlidingTextLayer* layer, GColor color);

/**
 * Set the alignment of the text.
 * @param layer Pointer to the SlidingTextLayer.
 * @param alignment Text alignment to use when rendering the text.
 */
void sliding_text_layer_set_text_alignment(SlidingTextLayer* layer, GTextAlignment alignment);

/**
 * Set the vertical adjusment of the layer. This can be used to help position
 * the text better in the layer.
 * @param layer Pointer to the SlidingTextLayer.
 * @param adjust Pixel offset to use when rendering the text.
 */
void sliding_text_layer_set_vertical_adjustment(SlidingTextLayer* layer, int8_t adjust);

/**
 * Get the current animation state of the SlidingTextLayer.
 * @param layer Pointer to the SlidingTextLayer.
 * @return True if the layer is currently animating.
 */
bool sliding_text_layer_is_animating(SlidingTextLayer* layer);

/**
 * Add the SlidingTextLayer to a window.
 * @param layer Pointer to the SlidingTextLayer.
 * @param winder Window to add the SlidingTextLayer to.
 */
#define sliding_text_layer_add_to_window(layer, window) layer_add_child(window_get_root_layer(window), (Layer*)layer);
