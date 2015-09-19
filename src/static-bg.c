#include <pebble.h>

static Window *s_main_window;

static TextLayer *s_time_layer;
static GFont s_time_font;

static GBitmap *s_example_bitmap;
static BitmapLayer *s_bitmap_layer;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
}

static void main_window_load(Window *window) {

        // Create bitmap
    s_example_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NUM_1);
    s_bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
    //s_bitmap_layer = bitmap_layer_create(layer_get_bounds(window_layer));
    bitmap_layer_set_bitmap(s_bitmap_layer, s_example_bitmap);
#ifdef PBL_PLATFORM_APLITE
    bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpAssign);
#elif PBL_PLATFORM_BASALT
    bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
    #endif
    //layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer));
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));

    // Create time TextLayer
    s_time_layer = text_layer_create(GRect(0, 10, 144, 50));
    text_layer_set_background_color(s_time_layer, GColorBlack);
    text_layer_set_text_color(s_time_layer, GColorWhite);

    // Create GFont
    s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SAN_FRANCISCO_42));

    // Apply to time TextLayer
    text_layer_set_font(s_time_layer, s_time_font);
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));

    update_time();
}

static void main_window_unload(Window *window) {
    // Unload GFont
    fonts_unload_custom_font(s_time_font);

    //destroy GBitmap
    gbitmap_destroy(s_example_bitmap);

    // destroy bitmap layer
    bitmap_layer_destroy(s_bitmap_layer);

    // destroy the text layer
    text_layer_destroy(s_time_layer);

    // destroy location layer
    //text_layer_destroy(s_location_layer);
    //fonts_unload_custom_font(s_location_font);
}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
}

static void init() {
    s_main_window = window_create();
#ifdef PBL_SDK_2
    window_set_fullscreen(s_main_window, true);
#endif

    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });

    window_stack_push(s_main_window, true);
    //update_time();

    // Register with TickTimerService
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
    window_destroy(s_main_window);
}

int main(void) {
    init();
    app_event_loop();
    deinit();
}
