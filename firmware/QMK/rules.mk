# MCU name
MCU = atmega32u4

F_CPU = 16000000

ARCH = AVR8

F_USB = $(F_CPU)

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Boot Section Size in *bytes*
OPT_DEFS += -DBOOTLOADER_SIZE=4096

# Build Options
COMBO_ENABLE = no
BOOTMAGIC_ENABLE ?= no	# Virtual DIP switch configuration(+1000)
EXTRAKEY_ENABLE ?= no # Audio control and System control(+450)
CONSOLE_ENABLE ?= no	# Console for debug(+400)
COMMAND_ENABLE ?= no    # Commands for debug and configuration
SLEEP_LED_ENABLE ?= no  # Breathing sleep LED during USB suspend
NKRO_ENABLE ?= yes		# USB Nkey Rollover
BACKLIGHT_ENABLE ?= no  # Enable keyboard backlight functionality
AUDIO_ENABLE ?= no
RGB_MATRIX_ENABLE = no
RGB_MATRIX_DRIVER = WS2812
RGBLIGHT_ENABLE = yes
RGBLIGHT_LAYERS = yes
EXTRAKEY_ENABLE = yes
OLED_DRIVER_ENABLE = no
LTO_ENABLE = yes
MOUSEKEY_ENABLE = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = analog_joystick
ANALOG_JOYSTICK_X_AXIS_PIN = F6
ANALOG_JOYSTICK_Y_AXIS_PIN = F5
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

COMBO_ENABLE = yes 
