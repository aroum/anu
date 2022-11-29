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
#define DEBOUNCING_DELAY 5

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

/* {UP, LEFT, CENTR, RIGHT, DOWN, BTN1, BTN2, BTN3}  */
#define DIRECT_PINS                        \
    {                                      \
        {                                  \
            B1, B3, F7, B2, B6, D4, D0, D1 \
        }                                  \
    }
#define UNUSED_PINS

/* Joystick */
#define JOYSTICK_BUTTON_COUNT 8
#define JOYSTICK_AXES_COUNT 2

#define COMBO_COUNT 5

// #define TAP_CODE_DELAY 10
#define TAPPING_TERM 180
#define PERMISSIVE_HOLD

#endif