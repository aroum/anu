#include "anu.h"
#include "joystick.h"
#include "analog.h"
#include "pointing_device.h"

#define X_PIN F6
#define Y_PIN F5
#define LOW_AXIS_VALUE 1
#define REST_AXIS_VALUE 512
#define HIGH_AXIS_VALUE 1023
#define MAX_COORDINATE_VALUE 127
#define COORDINATE_THRESHOLD_VALUE 8


/* {
       UP,
LEFT, CENTR, RIGHT,
       DOWN,
BTN1, BTN2, BTN3
}  */

enum combos
{
  m12_ESC,
  m132_L2,
  RGB_L0,
  RGB_VM,
  RGB_HM
};

const uint16_t PROGMEM m12_combo[] = {KC_BTN1, KC_BTN2, COMBO_END};
const uint16_t PROGMEM m132_combo[] = {KC_BTN1, KC_BTN2, LT(1, KC_ESC), COMBO_END};
const uint16_t PROGMEM rgbL0_combo[] = {RGB_VAI, RGB_MOD, RGB_HUI, COMBO_END};
const uint16_t PROGMEM rgbVM_combo[] = {RGB_VAI, RGB_MOD, COMBO_END};
const uint16_t PROGMEM rgbHM_combo[] = {RGB_HUI, RGB_MOD, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [m12_ESC] = COMBO(m12_combo, KC_BTN3),
    [m132_L2] = COMBO(m132_combo, TO(2)),
    [RGB_L0] = COMBO(rgbL0_combo, TO(0)),
    [RGB_VM] = COMBO(rgbVM_combo, RGB_VAD),
    [RGB_HM] = COMBO(rgbHM_combo, RGB_HUD)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
                KC_NO,
         KC_NO, KC_NO, KC_NO, 
                KC_NO, 
     KC_BTN1, LT(1,KC_ESC), KC_BTN2
     ),
    [1] = LAYOUT(
                KC_WH_U,
       KC_WH_L, KC_NO,   KC_WH_R,
                KC_WH_D, 
       KC_BTN1, KC_BTN3, KC_BTN2
     ),
        [2] = LAYOUT(
                 KC_NO, 
          KC_NO, KC_NO, KC_NO, 
                 KC_NO, 
        RGB_VAI, RGB_MOD, RGB_HUI
    ),
};

joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL};

uint8_t pointerThreshold = 10;
uint16_t keycodeThresholdStart = 500;
uint16_t delay = 20;
uint16_t lastTimestamp = 0;
typedef axisToKeycodeComponent myStruct Struct;


int8_t axisCoordinate(uint8_t pin)
{
  int8_t direction;
  int16_t range;
  int16_t distance;
  int16_t position = analogReadPin(pin);

  if (position == REST_AXIS_VALUE)
  {
    return 0;
  }
  else if (position < REST_AXIS_VALUE)
  {
    distance = REST_AXIS_VALUE - position;
    range = REST_AXIS_VALUE - LOW_AXIS_VALUE;
    direction = 1;
  }
  else
  {
    distance = position - REST_AXIS_VALUE;
    range = HIGH_AXIS_VALUE - REST_AXIS_VALUE;
    direction = -1;
  }

  float percent = (float)distance / range;
  int16_t coordinate = (int16_t)(percent * MAX_COORDINATE_VALUE);
  if (coordinate < 0)
  {
    return 0;
  }
  else if (coordinate > MAX_COORDINATE_VALUE)
  {
    return MAX_COORDINATE_VALUE * direction;
  }
  else
  {
    return coordinate * direction;
  }
}

int8_t axisToMouseComponent(uint8_t pin)
{
  int coordinate = axisCoordinate(pin);
  if (coordinate == 0)
  {
    return 0;
  }
  else
  {
    int precisionRegulator = 1000;
    return abs(coordinate) * (float)coordinate / precisionRegulator;
  }
}

Struct  axisToKeycodeComponent(uint8_t layer, uint8_t x_pin, uint8_t y_pin, uint16_t* keycodeThreshold, uint16_t* keycode)
{
  const keypos_t keypos[] = {
      [0] = (keypos_t){.row = 0, .col = 4}, // UP
      [1] = (keypos_t){.row = 0, .col = 0}, // DOWN
      [2] = (keypos_t){.row = 0, .col = 1}, // LEFT
      [3] = (keypos_t){.row = 0, .col = 3}  // RIGHT
  };
  int8_t x = axisCoordinate(X_PIN);
  int8_t y = axisCoordinate(Y_PIN);

  if (abs(x) > abs(y))
  {
    *keycodeThreshold = keycodeThresholdStart / abs(x);
    if (x > COORDINATE_THRESHOLD_VALUE)
    {
      *keycode = keymap_key_to_keycode(layer, keypos[3]);
    }
    else if ((x * -1) > COORDINATE_THRESHOLD_VALUE)
    {
      *keycode = keymap_key_to_keycode(layer, keypos[2]);
    }
  }
  else
  {
    *keycodeThreshold = keycodeThresholdStart / abs(y);
    if (y > COORDINATE_THRESHOLD_VALUE)
    {
      *keycode = keymap_key_to_keycode(layer, keypos[1]);
    }
    else if ((y * -1) > COORDINATE_THRESHOLD_VALUE)
    {
      *keycode = keymap_key_to_keycode(layer, keypos[0]);
    }
  }
  *keycode = KC_NO;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id)
  {
  }
  return MACRO_NONE;
}

void matrix_init_user(void) {}

void matrix_scan_user(void)
{
  uint8_t layer = biton32(layer_state);
  if (layer >= 1)
  {
    if (timer_elapsed(lastTimestamp) > delay)
    {
      lastTimestamp = timer_read();

      uint16_t keycode;
      uint16_t keycodeThreshold;
      axisToKeycodeComponent(layer, X_PIN, Y_PIN, &keycodeThreshold, &keycode);
      delay = keycodeThreshold;
      tap_code(keycode);
      uprintf("%s\n", tap_code);
    }
  }
}

void pointing_device_task(void)
{
  report_mouse_t report = pointing_device_get_report();
  uint8_t layer = biton32(layer_state);
  if (layer == 0)
  {
    if (timer_elapsed(lastTimestamp) > pointerThreshold)
    {
      lastTimestamp = timer_read();
      report.x = axisToMouseComponent(X_PIN);
      report.y = -axisToMouseComponent(Y_PIN);
    }
  }
  pointing_device_set_report(report);
  pointing_device_send();
}

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_RED});
const rgblight_segment_t PROGMEM my_layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GREEN});

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1,
    my_layer2 // Overrides other layers
);

void keyboard_post_init_user(void)
{
  // Enable the LED layers
  rgblight_layers = my_rgb_layers;
};

layer_state_t layer_state_set_user(layer_state_t state)
{
  // Both layers will light up if both kb layers are active
  rgblight_set_layer_state(1, layer_state_cmp(state, 1));
  rgblight_set_layer_state(2, layer_state_cmp(state, 2));
  return state;
};
bool led_update_user(led_t led_state)
{
  rgblight_set_layer_state(0, led_state.caps_lock);
  return true;
}
