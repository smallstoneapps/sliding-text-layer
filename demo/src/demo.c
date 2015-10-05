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

demo/demo.c

*/


#include <pebble.h>
#include "../../lib/sliding-text-layer.h"


static void init(void);
static void deinit(void);
static void window_load(Window* window);
static void window_unload(Window* window);
static void click_config_provider(void* context);
static void up_click_handler(ClickRecognizerRef recognizer, void* context);
static void down_click_handler(ClickRecognizerRef recognizer, void* context);


static Window* s_window;
static SlidingTextLayer* s_sliding_text_layer;
static char* s_texts[] = {
  "Interstellar",
  "Boyhood",
  "Gone Girl",
  "Guardians of the Galaxy",
  "The Grand Budapest Hotel",
  "X-Men: Days of Future Past",
  "The Raid 2",
  "How to Train Your Dragon 2",
  "Edge of Tomorrow",
  "The Fault in Our Stars"
};
static uint8_t s_text_count = 10;
static uint8_t s_text_position = 0;


int main(void) {
  init();
  app_event_loop();
  deinit();
}


static void init(void) {
  s_window = window_create();
  #ifdef PBL_SDK_2
  window_set_fullscreen(s_window, true);
  #endif
  window_set_background_color(s_window, COLOR_FALLBACK(GColorJazzberryJam, GColorBlack));
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
  window_stack_push(s_window, false);
  window_set_click_config_provider(s_window, click_config_provider);
}

static void deinit(void) {
  window_destroy(s_window);
}

static void window_load(Window* window) {
  GSize window_size = layer_get_bounds(window_get_root_layer(window)).size;

  s_sliding_text_layer = sliding_text_layer_create(GRect(0, window_size.h / 2 - 12, window_size.w, 24));
  sliding_text_layer_set_font(s_sliding_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  sliding_text_layer_set_text_color(s_sliding_text_layer, GColorWhite);
  sliding_text_layer_set_text(s_sliding_text_layer, s_texts[0]);
  sliding_text_layer_set_vertical_adjustment(s_sliding_text_layer, -6);
  sliding_text_layer_set_duration(s_sliding_text_layer, 500);
  sliding_text_layer_add_to_window(s_sliding_text_layer, s_window);
}

static void window_unload(Window* window) {
  sliding_text_layer_destroy(s_sliding_text_layer);
}

static void click_config_provider(void* context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void up_click_handler(ClickRecognizerRef recognizer, void* context) {
  if (sliding_text_layer_is_animating(s_sliding_text_layer)) {
    return;
  }

  if (s_text_position <= 0) {
    sliding_text_layer_animate_bounce_up(s_sliding_text_layer);
    return;
  }

  s_text_position -= 1;
  sliding_text_layer_set_next_text(s_sliding_text_layer, s_texts[s_text_position]);
  sliding_text_layer_animate_up(s_sliding_text_layer);
}

static void down_click_handler(ClickRecognizerRef recognizer, void* context) {
  if (sliding_text_layer_is_animating(s_sliding_text_layer)) {
    return;
  }

  if (s_text_position >= s_text_count - 1) {
    sliding_text_layer_animate_bounce_down(s_sliding_text_layer);
    return;
  }

  s_text_position += 1;
  sliding_text_layer_set_next_text(s_sliding_text_layer, s_texts[s_text_position]);
  sliding_text_layer_animate_down(s_sliding_text_layer);
}
