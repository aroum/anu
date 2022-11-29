#include "anu.h"
#include "pointing_device.h"

/* {BTN1, BTN2, BTN3, STICK_BTN}  */

enum combos{
  m12_ESC,
  m132_L2,
  RGB_L0,
  RGB_VM,
  RGB_HM
};

const uint16_t PROGMEM m12_combo[]   = {KC_BTN1, KC_BTN2, COMBO_END};
const uint16_t PROGMEM m132_combo[]  = {KC_BTN1, KC_BTN2, LT(1, KC_ESC), COMBO_END};
const uint16_t PROGMEM rgbL0_combo[] = {RGB_VAI, RGB_MOD, RGB_HUI, COMBO_END};
const uint16_t PROGMEM rgbVM_combo[] = {RGB_VAI, RGB_MOD, COMBO_END};
const uint16_t PROGMEM rgbHM_combo[] = {RGB_HUI, RGB_MOD, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [m12_ESC] = COMBO(m12_combo,   KC_ESC),
  [m132_L2] = COMBO(m132_combo,  TO(2)  ),
  [RGB_L0]  = COMBO(rgbL0_combo, TO(0)  ),
  [RGB_VM]  = COMBO(rgbVM_combo, RGB_VAD),
  [RGB_HM]  = COMBO(rgbHM_combo, RGB_HUD)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
         KC_BTN1, LT(1, KC_BTN3), KC_BTN2,KC_NO
        ),
    [1] = LAYOUT(
        KC_BTN1, KC_BTN3, KC_BTN2, KC_NO
        ),
    [2] = LAYOUT(
        RGB_VAI, RGB_MOD, RGB_HUI,KC_NO
        )
};

static bool scrolling_mode = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1:  // If we're on the 1 layer enable scrolling mode
            scrolling_mode = true;
            rgblight_setrgb (0x00,  0xFF, 0x00);
            // pointing_device_set_cpi(2000);
            break;
        case 2:
            rgblight_setrgb (0xFF,  0x00, 0x00);
            break;
        default:
            if (scrolling_mode) {  // check if we were scrolling before and set disable if so
                scrolling_mode = false;
                // pointing_device_set_cpi(8000);
                rgblight_setrgb (0x00,  0xFF, 0xFF);
            }
            break;
    }
    return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (scrolling_mode) {
        mouse_report.h = mouse_report.x/10;
        mouse_report.v = -mouse_report.y/10;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}