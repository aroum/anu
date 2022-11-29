#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x4541
#define PRODUCT_ID 0x0003
#define DEVICE_VER 0x0001
#define MANUFACTURER aroum
#define PRODUCT Anu

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 8

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

// /* prevent stuck modifiers */
// #define PREVENT_STUCK_MODIFIERS

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLED_NUM 3 
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 180
#define RGBLIGHT_HUE_STEP 5
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 60
#define RGBLIGHT_EFFECT_STATIC_LIGHT
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 3
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYERS
#endif

/* {BTN1, BTN2, BTN3, STICK_BTN}  */
#define DIRECT_PINS                        \
    {                                      \
        {                                  \
            D4, D0, D1, F7 \
        }                                  \
    }


/* Joystick */
#define JOYSTICK_BUTTON_COUNT 4
#define JOYSTICK_AXES_COUNT 2


/* Joystick config */
#define ANALOG_JOYSTICK_X_AXIS_PIN F6
#define ANALOG_JOYSTICK_Y_AXIS_PIN F5
// #define ANALOG_JOYSTICK_CLICK_PIN F7

#define ANALOG_JOYSTICK_AXIS_MIN 0
#define ANALOG_JOYSTICK_AXIS_MAX 1023

#define ANALOG_JOYSTICK_READ_INTERVAL 10

#define POINTING_DEVICE_INVERT_X

/* Cursor speed */
#define ANALOG_JOYSTICK_SPEED_MAX 5
#define ANALOG_JOYSTICK_SPEED_REGULATOR 30

// #define TAP_CODE_DELAY 10
#define TAPPING_TERM 180
#define PERMISSIVE_HOLD

#define COMBO_COUNT 5
#endif