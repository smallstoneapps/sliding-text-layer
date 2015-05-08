#include <pebble.h>
#include "sliding-text-layer.h"

#define ANIMATION_DIRECTION_UP 0
#define ANIMATION_DIRECTION_DOWN 1

typedef struct SlidingTextLayerData {
  char* text_next;
  char* text_current;
  GColor color_text;
  GFont* font;
  bool is_animating;
  GTextOverflowMode overflow;
  GTextAlignment align;
  Animation* animation;
  AnimationImplementation implementation;
  uint16_t offset;
  uint8_t direction;
  AnimationCurve curve;
} SlidingTextLayerData;


static void animate(SlidingTextLayer* layer, uint8_t direction, uint16_t duration);
static void render(Layer* layer, GContext* ctx);
static void animation_started(Animation *anim, void *context);
static void animation_stopped(Animation *anim, bool stopped, void *context);
static void update(Animation* anim, AnimationProgress dist_normalized);
#define get_layer(layer) (Layer*)layer
#define get_data(layer) (SlidingTextLayerData*) layer_get_data(get_layer(layer))


SlidingTextLayer* sliding_text_layer_create(GRect rect) {
  SlidingTextLayer* layer = (SlidingTextLayer*)layer_create_with_data(rect, sizeof(SlidingTextLayerData));
  SlidingTextLayerData* data = get_data(layer);
  data->color_text = GColorBlack;
  data->align = GTextAlignmentCenter;
  data->overflow = GTextOverflowModeFill;
  data->offset = 0;
  data->is_animating = false;
  data->implementation.update = update;
  data->curve = AnimationCurveEaseInOut;
  layer_set_update_proc(get_layer(layer), render);
  return layer;
}

void sliding_text_layer_destroy(SlidingTextLayer* layer) {
  SlidingTextLayerData* data = get_data(layer);
  if (data->is_animating) {

  }
  layer_destroy(get_layer(layer));
}

void sliding_text_layer_animate_up(SlidingTextLayer* layer, uint16_t duration) {
  animate(layer, ANIMATION_DIRECTION_UP, duration);
}

void sliding_text_layer_animate_down(SlidingTextLayer* layer, uint16_t duration) {
  animate(layer, ANIMATION_DIRECTION_DOWN, duration);
}

void sliding_text_layer_set_text(SlidingTextLayer* layer, char* text) {
  if (! layer) {
    return;
  }
  SlidingTextLayerData* data = get_data(layer);
  if (! data) {
    return;
  }
  data->text_current = text;
  layer_mark_dirty(get_layer(layer));
}

void sliding_text_layer_set_next_text(SlidingTextLayer* layer, char* text) {
  if (! layer) {
    return;
  }
  SlidingTextLayerData* data = get_data(layer);
  if (! data) {
    return;
  }
  data->text_next = text;
}

void sliding_text_layer_set_font(SlidingTextLayer* layer, GFont* font) {
  if (! layer) {
    return;
  }
  SlidingTextLayerData* data = get_data(layer);
  if (! data) {
    return;
  }
  data->font = font;
  layer_mark_dirty(get_layer(layer));
}

void sliding_text_layer_set_text_color(SlidingTextLayer* layer, GColor color) {
  if (! layer) {
    return;
  }
  SlidingTextLayerData* data = get_data(layer);
  if (! data) {
    return;
  }
  data->color_text = color;
  layer_mark_dirty(get_layer(layer));
}


static void animate(SlidingTextLayer* layer, uint8_t direction, uint16_t duration) {
  if (! layer) {
    return;
  }
  SlidingTextLayerData* data = get_data(layer);
  if (! data) {
    return;
  }
  if (data->is_animating) {
    return;
  }

  data->direction = direction;
  data->offset = 0;
  data->animation = animation_create();
  animation_set_duration(data->animation, duration);
  animation_set_curve(data->animation, data->curve);
  animation_set_implementation(data->animation, &data->implementation);
  animation_set_handlers(data->animation, (AnimationHandlers) {
    .started = animation_started,
    .stopped = animation_stopped
  }, (void*)layer);
  animation_schedule(data->animation);
}

static void render(Layer* layer, GContext* ctx) {
  SlidingTextLayerData* data = get_data(layer);
  graphics_context_set_text_color(ctx, data->color_text);

  #if STL_DEBUG
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
  #endif

  int8_t y_offset = -6;

  if (data->is_animating) {
    graphics_draw_text(ctx,
      data->direction == ANIMATION_DIRECTION_UP ? data->text_next : data->text_current,
      data->font,
      GRect(0, y_offset - data->offset, 144, 24),
      data->overflow,
      data->align,
      NULL);
    graphics_draw_text(ctx,
      data->direction == ANIMATION_DIRECTION_UP ? data->text_current : data->text_next,
      data->font,
      GRect(0, 24 + y_offset - data->offset, 144, 24),
      data->overflow,
      data->align,
      NULL);
  }
  else {
    graphics_draw_text(ctx,
      data->text_current,
      data->font,
      GRect(0, y_offset, 144, 24),
      data->overflow,
      data->align,
      NULL);
  }
}

static void animation_started(Animation *anim, void *context) {
  SlidingTextLayerData* data = get_data((SlidingTextLayer*)context);
  data->is_animating = true;
}

static void animation_stopped(Animation *anim, bool stopped, void *context) {
  SlidingTextLayerData* data = get_data((SlidingTextLayer*)context);
  data->is_animating = false;
  data->text_current = data->text_next;
  data->text_next = false;
}

static void update(Animation* anim, AnimationProgress dist_normalized) {
  SlidingTextLayer* layer = (SlidingTextLayer*)animation_get_context(anim);
  SlidingTextLayerData* data = get_data(layer);

  float percent = (float)dist_normalized / (float)ANIMATION_NORMALIZED_MAX;
  data->offset = data->direction == ANIMATION_DIRECTION_UP ? (24 - (uint16_t)24.0f * percent) : (uint16_t)24.0f * percent;
  layer_mark_dirty(get_layer(layer));
}
