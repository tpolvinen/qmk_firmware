#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define USB_MAX_POWER_CONSUMPTION 100

// required because lower/raise modifiers are redefined by colemak-dh
#define PREVENT_STUCK_MODIFIERS

// tap dance key press termination interval
#define TAPPING_TERM   250

// compile time macro string, see functions/hardware planck script (undefine otherwise)
// #define PRIVATE_STRING

// compile time macro string, must be in quotes
#define PUBLIC_STRING ":%s/arch=(.*)/arch=('any')\n"

// thumb key tap-shift() double tap: one shot shift (0) off (1) on
#define DT_SHIFT 1

// number layer 0 position KEYPAD_0, THUMB_0
#define THUMB_0

// Layout BEAKL*, COLEKA*, QWERTY (default)
#define COLEMAK

#endif
