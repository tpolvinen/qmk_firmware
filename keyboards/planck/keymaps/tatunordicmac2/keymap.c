// To flash planck firmware
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//
//   cd qmk_firmware
//   make planck/rev6:tatunordicmac2:clean (good practice before flashing)
//   Reset keyboard or press hw reset button on base (hole).
//   make planck/rev6:tatunordicmac2:dfu-util
//
//
// Notes
// ▔▔▔▔▔
//   ** E R G O   W I D E   S P L I T ** Layout
//   
//   For Macs with Swedish/Finnish keyboard layout
//
//   
//   Autocompletion tap dance key pairs (),[],{} are available from the
//   symbol layer _SYMBOL, as well as numerous (un)shift key values
//
//   The navigation pad provides a single hand right thumb activated cluster
//   with left hand modifiers
//
//   #define PRIVATE_STRING includes private_string.h, a user defined code
//   block for the PRIV tap dance e.g. SEND_STRING("secret message"),
//   see function private()
//
// Modifier clusters
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   The num and sym keys together access the navigation pad layer
//
//   ,-----------------------------------------------------------------------------------.
//   | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
//   `-----------------------------------------------------------------------------------'
//
// Hint
// ▔▔▔▔
//   For sculpted keycaps such as Cherry or OEM profile, reverse the six center keycaps 
//   on the bottom row for more ergonomic thumb orientation and actuation.
//
// Code
// ▔▔▔▔
//   tpolvinen: This source is shamelessly based on sdothum´s Ergo Wide Split Layout, 
//   which in turn "is shamelessly based on the "default" planck layout".
//
//   #ifdef/#endif block structures are not indented, as syntax highlighting
//   in vim is sufficient for identification
//
//   c++ commenting style is used throughout
//   tpolvinen: changes to the original layout have been marked after each line in layout descriptions.
//
// Change history
// ▔▔▔▔▔▔▔▔▔▔▔▔▔▔
//   See http://thedarnedestthing.com/planck%20constant
//   See http://thedarnedestthing.com/planck%20done

#include "config.h"
#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"
#include "keymap_swedish.h"

extern keymap_config_t keymap_config;

// appears to be 0..15 layer limit
enum planck_layers {
  _BASE = 0
 ,_SHIFT
 ,_LSHIFT
 ,_RSHIFT
 ,_NUMBER
 ,_NUMSYM
 ,_SYMBOL
 ,_SYMREG
 ,_MOUSE
 ,_FNCKEY
 ,_EDIT
 ,_ADJUST
};

enum planck_keycodes {
  BASE = SAFE_RANGE
 ,PLOVER
 ,PLOVEX
 ,PS_CIRC   // pseudo GUI_T(S(KC_6))            for modified key-codes, see process_record_user()
 ,PS_DLR    // pseudo SFT_T(S(KC_4))            for modified key-codes, see process_record_user()
 ,PS_PERC   // pseudo ALT_T(S(KC_5))            for modified key-codes, see process_record_user()
 ,PS_LPRN   // pseudo CTL_T(S(KC_9))            for modified key-codes, see process_record_user()
 ,PS_LEFT   // pseudo LT   (_MOUSE, S(KC_LEFT)) for modified key-codes, see process_record_user()
 ,PS_PIPE   // pseudo LT   (_MOUSE, S(KC_BSLS)) for modified key-codes, see process_record_user()
 ,PS_TAB    // pseudo LT   (_FNCKEY, S(KC_TAB)) for modified key-codes, see process_record_user()
#ifdef THUMB_0
 ,LT_EQL  = LT (_ADJUST, KC_EQL)
#else
 ,LT_0    = LT (_ADJUST, KC_0)
#endif
 ,LT_A    = LT (_NUMSYM, KC_A)
 ,LT_BSLS = LT (_ADJUST, KC_BSLS)
 ,LT_BSPC = LT (_EDIT,   KC_BSPC)
 ,LT_ESC  = LT (_NUMBER, KC_ESC)
 ,LT_LEFT = LT (_SYMBOL, KC_LEFT)           // see process_record_user() for extended handling
 ,LT_LFTX = LT (_SYMREG, KC_LEFT)
 ,LT_TAB  = LT (_FNCKEY, KC_TAB)
 ,OS_ALT  = OSM(MOD_LALT)
 ,OS_CALT = OSM(MOD_LALT | MOD_LCTL)
 ,OS_CGUI = OSM(MOD_LGUI | MOD_LCTL)
 ,OS_CSFT = OSM(MOD_LSFT | MOD_LCTL)
 ,OS_CTL  = OSM(MOD_LCTL)
 ,OS_GUI  = OSM(MOD_LGUI)
 ,OS_SALT = OSM(MOD_LALT | MOD_LSFT)
 ,OS_SFT  = OSM(MOD_LSFT)
 ,OS_SGUI = OSM(MOD_LGUI | MOD_LSFT)
};

// modifier keys
#define AT_B    ALT_T(KC_B)
#define AT_DOWN ALT_T(KC_DOWN)
#define CT_RGHT CTL_T(KC_RGHT)
#define GT_C    GUI_T(KC_C)
#define GT_UP   GUI_T(KC_UP)
#define MT_E    MT   (MOD_LCTL | MOD_LALT, KC_E)
#define MT_X    MT   (MOD_LALT | MOD_LSFT, KC_X)

#define S_DOWN  S    (KC_DOWN)
#define S_RGHT  S    (KC_RGHT)
#define S_UP    S    (KC_UP)

// tap dance keys
enum tap_dance {
  _CAPS = 0
 ,_COLN
 ,_COMM
 ,_DQOT
 ,_ENT
 ,_FBKT
 ,_GRV
 ,_GT
 ,_LBRC
 ,_LCBR
 ,_LPRN
 ,_LT
 ,_PRIV
 ,_RBRC
 ,_RCBR
 ,_RNGL
 ,_RPRN
 ,_SEND
 ,_SHEX
 ,_SPC
 ,_TILD
};

#define TD_CAPS TD(_CAPS)
#define TD_COLN TD(_COLN)
#define TD_COMM TD(_COMM)
#define TD_PERC TD(_PERC)
#define TD_DQOT TD(_DQOT)
#define TD_ENT  TD(_ENT)
#define TD_GRV  TD(_GRV)
#define TD_GT   TD(_GT)
#define TD_LBRC TD(_LBRC)
#define TD_LCBR TD(_LCBR)
#define TD_LPRN TD(_LPRN)
#define TD_LT   TD(_LT)
#define TD_PRIV TD(_PRIV)                   // compile time macro string, provided in private_string.h
#define TD_RBRC TD(_RBRC)
#define TD_RCBR TD(_RCBR)
#define TD_RNGL TD(_RNGL)
#define TD_RPRN TD(_RPRN)
#define TD_SEND TD(_SEND)                   // config.h defined macro string
#define TD_SPC  TD(_SPC)                    // see process_record_user() for extended handling of Spc
#define TD_TILD TD(_TILD)

// keycodes
#ifdef KC_NO
#undef KC_NO
#endif
#define COPY    LGUI(KC_C) // LCTL(KC_C) -> LGUI(KC_C)
#define CUT     LGUI(KC_X) // LCTL(KC_X) -> LGUI(KC_X)
#define EOT     LGUI(KC_D) // LCTL(KC_D) -> LGUI(KC_D)
#define NAK     LGUI(KC_U) // LCTL(KC_U) -> LGUI(KC_U)
#define PASTE   LGUI(KC_V) // LCTL(KC_V) -> LGUI(KC_V)
#define UNDO    LGUI(KC_Z) // LCTL(KC_Z) -> LGUI(KC_Z)
#define TMCOPY  LALT(LGUI(KC_C)) // LALT(LCTL(KC_C)) 
#define TMPASTE LALT(LGUI(KC_V)) // LALT(LCTL(KC_V)) -> LALT(LGUI(KC_V))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


// .............................................................. Colemak Mod-DH

#ifdef COLEMAK
  // http://www.keyboard-layout-editor.com/#/gists/f69e4a658b7ec911f4b7340d3081963a
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   ö  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | Caps |^Shift|   K  |   H  |   ,  |   .  |   ä  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_BASE] = LAYOUT_ortho_4x12(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    OS_CALT, OS_CGUI,  KC_J,   KC_L,    KC_U,    KC_Y,    NO_OSLH,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    OS_SALT, OS_SGUI,  KC_M,   KC_N,    KC_E,    KC_I,    KC_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    TD_CAPS, OS_CSFT,  KC_K,   KC_H,    KC_COMM, KC_DOT,  NO_AE,   // " and ' -> _LSHIFT and _RSHIFT layers
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC,  TD_ENT, LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  [_SHIFT] = LAYOUT_ortho_4x12(
    S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), OS_CALT, OS_CGUI, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), NO_OSLH,
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), OS_SALT, OS_SGUI, S(KC_M), S(KC_N), S(KC_E), S(KC_I), S(KC_O),
    S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), TD_CAPS, OS_CSFT, S(KC_K), S(KC_H), KC_COMM, KC_DOT,  S(NO_AE),
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  LT_TAB,  LT_BSPC,  TD_ENT, LT_LEFT, AT_DOWN, GT_UP,   CT_RGHT
  ),

  // http://www.keyboard-layout-editor.com/#/gists/5248fe0cb848118552a5113587a16b62
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   '  |   {  |   }  |   €  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   Ö  | S(KC_F) -> TD_LCBR  S(KC_P) -> TD_RCBR  S(KC_B) -> NO_DLR_MAC
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   "  |   <  |   >  |   ~  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  | S(KC_S) -> NO_LESS_MAC  S(KC_T) -> NO_GRTR_MAC  S(KC_G) -> NO_TILD
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   !  |   =  |   `  | Caps |^Shift|   K  |   H  |   ;  |   :  |   Ä  | ; and : added here  / and ? -> RSHIFT    S(KC_C) -> KC_EXLM  S(KC_D) -> NO_EQL S(KC_V) -> NO_GRV
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   -  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LSHIFT] = LAYOUT_ortho_4x12(
    S(KC_Q), NO_APOS, TD_LCBR,     TD_RCBR,     NO_DLR_MAC, OS_CALT, OS_CGUI, S(KC_J), S(KC_L), S(KC_U),    S(KC_Y),   S(NO_OSLH), 
    S(KC_A), TD_DQOT, NO_LESS_MAC, TD_RNGL, TD_TILD,    OS_SALT, OS_SGUI, S(KC_M), S(KC_N), S(KC_E),    S(KC_I),   S(KC_O),
    S(KC_Z), S(KC_X), KC_EXLM,     NO_EQL,      NO_GRV,     TD_CAPS, OS_CSFT, S(KC_K), S(KC_H), S(KC_COMM), S(KC_DOT), S(NO_AE), 
    OS_CTL,  OS_GUI,  OS_ALT,      LT_ESC,      KC_TRNS,    LT_TAB,  KC_DEL,  NO_MINS, PS_LEFT, S_DOWN,     S_UP,      S_RGHT  // KC_MINS -> NO_MINS
  ),

  //  http://www.keyboard-layout-editor.com/#/gists/10d6e05e9db760e1e2a0fd7d44ca0aa3
  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   ^  |   [  |   ]  |   '  |   Å  | S(KC_J) -> NO_CIRC  S(KC_L) -> TD_LBRC  S(KC_U) -> TD_RBRC
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   |  |   (  |   )  |   "  |   O  | S(KC_M) -> NO_PIPE_MAC  S(KC_N) -> TD_LPRN  S(KC_E) -> TD_RPRN
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | Caps |^Shift|   *  |   \  |   /  |   ?  |   å  | ? added here  ~ TD_TILD and ` TD_GRV -> _SYMBOL Layer    S(KC_K) -> NO_ASTR  S(KC_H) -> NO_BSLS_MAC
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt | Caps |   _  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right| KC_UNDS -> NO_UNDS
  // `-----------------------------------------------------------------------------------'

  [_RSHIFT] = LAYOUT_ortho_4x12(
    S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), OS_CALT, OS_CGUI, NO_CIRC,     TD_LBRC,     TD_RBRC, NO_APOS, S(NO_AA), 
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), OS_SALT, OS_SGUI, NO_PIPE_MAC, TD_LPRN,     TD_RPRN, TD_DQOT, S(KC_O), 
    S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), TD_CAPS, OS_CSFT, NO_ASTR,     NO_BSLS_MAC, NO_SLSH, NO_QUES, NO_AA, 
    OS_CTL,  OS_GUI,  OS_ALT,  KC_CAPS, NO_UNDS, PS_TAB,  LT_BSPC, KC_TRNS,     PS_LEFT,     S_DOWN,  S_UP,    S_RGHT 
  ),
#endif

// ......................................................... Number Keypad Layer

  // http://www.keyboard-layout-editor.com/#/gists/41a5841daff39461af667308282826eb
  // .-----------------------------------------------------------------------------------.
  // |      |   F  |   E  |   D  |      |      |      |   /  |   7  |   8  |   9  |   *  | KC_SLSH -> KC_PSLS KC_ASTR -> KC_PAST
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |   C  |   B  |   A  |      |      |      |   .  |   4  |   5  |   6  |   -  | KC_MINS -> KC_PMNS
  // |-----------------------------------------------------------------------------------|
  // |      |   #  |   X  |   G  |      |      |      |   ,  |   1  |   2  |   3  |   +  | TD_COMM -> KC_PCMM  KC_PLUS -> KC_PPLS
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |   0  |   =  |      |      |      | LT_EQL -> KC_PEQL (NO_EQL)
  // |      |      |      |  f() |      |      |      |   =  |   0  |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_NUMBER] = LAYOUT_ortho_4x12(
    KC_NO,   KC_F,    MT_E,    KC_D,    KC_NO,   KC_NO,   KC_NO,   KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PAST,
    OS_CTL,  GT_C,    AT_B,    LT_A,    KC_NO,   KC_NO,   KC_NO,   KC_DOT,  KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
    KC_NO,   KC_HASH, MT_X,    S(KC_G), KC_NO,   KC_NO,   KC_NO,   KC_COMM, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
#ifdef THUMB_0
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0,   KC_PEQL, KC_TRNS, KC_TRNS, KC_TRNS
#else
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LT_EQL,  LT_0,    KC_TRNS, KC_TRNS, KC_TRNS
#endif
  ),

  // http://www.keyboard-layout-editor.com/#/gists/3b5cb8fcda59380d56664d6daf4f92a7
  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |   {  |   &  |   ?  |   :  |   }  | KC_LCBR -> TD_LCBR  KC_AMPR -> NO_AMPR  KC_QUES -> NO_QUES KC_COLN -> TD_COLN 
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |   (  |   $  |   %  |   ^  |   )  | KC_DLR -> NO_DLR  ? -> NO_CIRC  KC_RPRN -> TD_RPRN
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |   [  |   <  |   ~  |   >  |   ]  | KC_LBRC -> TD_LBRC  KC_LT -> NO_LESS_MAC  KC_TILD -> NO_TILD  KC_GT -> NO_GRTR  KC_RBRC -> TD_RBRC
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |   |  |   \  |      |      |      | -> NO_PIPE_MAC  -> NO_BSLS_MAC
  // '-----------------------------------------------------------------------------------'

  [_NUMSYM] = LAYOUT_ortho_4x12(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TD_LCBR,     NO_AMPR,     NO_QUES, TD_COLN,     TD_RCBR,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_NO,   TD_LPRN,     NO_DLR,      KC_PERC, NO_CIRC,     TD_RPRN,
    KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO,   KC_NO,   KC_NO,   TD_LBRC,     NO_LESS_MAC, TD_TILD, TD_RNGL, TD_RBRC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NO_PIPE_MAC, NO_BSLS_MAC, KC_TRNS, KC_TRNS,     KC_TRNS
  ),

// ..................................................... Symbol Navigation Layer

  // http://www.keyboard-layout-editor.com/#/gists/002d5c4f0148d1f780c07b72f9546c97
  // .-----------------------------------------------------------------------------------.
  // |   {  |   .  |   *  |   &  |   }  |      |      |      | Home |  Up  |  End | PgUp | KC_DOT  KC_ASTR -> NO_ASTR  KC_AMPR -> NO_AMPR
  // |-----------------------------------------------------------------------------------|
  // |   (  |   ^  |   %  |   €  |   )  |      |      |   ~  | Left | Down | Right| PgDn | KC_RPRN -> TD_RPRN
  // |-----------------------------------------------------------------------------------|
  // |   [  |   #  |   @  |   !  |   ]  |      |      |      |      |   `  |   ´  |      | KC_LBRC -> TD_LBRC  KC_HASH  KC_AT -> NO_AT  KC_EXLM (? -> NO_ACUT)
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |   \  |   |  |      |      |      |  f() |      |      |      | LT_BSLS -> NO_BSLS_MAC   PS_PIPE -> NO_PIPE_MAC
  // '-----------------------------------------------------------------------------------'

  [_SYMBOL] = LAYOUT_ortho_4x12(
    TD_LCBR, KC_DOT,  NO_ASTR, NO_AMPR,     TD_RCBR,     KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP,
    PS_LPRN, PS_CIRC, KC_PERC, PS_DLR,      TD_RPRN,     KC_NO,   KC_NO,   TD_TILD, LT_LFTX, KC_DOWN, KC_RGHT, KC_PGDN,
    TD_LBRC, KC_HASH, NO_AT,   KC_EXLM,     TD_RBRC,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   TD_GRV,  NO_ACUT, KC_NO,
    KC_TRNS, KC_TRNS, KC_TRNS, NO_BSLS_MAC, NO_PIPE_MAC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // http://www.keyboard-layout-editor.com/#/gists/b381b4787a152dcf7ef2fa8e9c23c0c8
  // .-----------------------------------------------------------------------------------.
  // |      |   ?  |   +  |   ~  |      |      |      |      |      |      |      |      | KC_QUES -> NO_QUES KC_PLUS -> NO_PLUS KC_TILD -> TD_TILD
  // |-----------------------------------------------------------------------------------|
  // |      |   <  |   =  |   >  |      |      |      |      |  f() |      |      |      | KC_LT -> NO_LESS_MAC  KC_EQL -> KC_PEQL
  // |-----------------------------------------------------------------------------------|
  // |      |   3  |   2  |   1  |      |      |      |      |      |      |      |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |      |  f() |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_SYMREG] = LAYOUT_ortho_4x12(
    KC_TRNS, NO_QUES,     NO_PLUS, TD_TILD, KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, NO_LESS_MAC, KC_PEQL, TD_RNGL, KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_3,        KC_2,    KC_1,    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

// ............................................................... Mouse Actions
 
  // http://www.keyboard-layout-editor.com/#/gists/81bffa133162c8e74f50157ac4b7158a
  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      | Left |  Up  | Right|  Up  |
  // |-----------------------------------------------------------------------------------|
  // |      | Btn3 | Btn2 | Btn1 |      |      |      |      | Left | Down | Right| Down |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |      |      |      |      |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |  f() |      |      |      |  f() |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_MOUSE] = LAYOUT_ortho_4x12(
    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U,
    KC_NO, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,   KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO,   KC_NO,   KC_NO
  ),

// ............ .................................................. Function Keys

  // http://www.keyboard-layout-editor.com/#/gists/877e8fd3b5b2e907f23b9466459833a1
  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      |  F7  |  F8  |  F9  |  F12 |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |  GUI |  Alt | Shift|      |      |      |      |  F4  |  F5  |  F6  |  F11 |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |      |  F1  |  F2  |  F3  |  F10 |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |  f() |      |   +  |      |      |      |      |  KC_PLUS -> KC_PPLS
  // '-----------------------------------------------------------------------------------'

  [_FNCKEY] = LAYOUT_ortho_4x12(
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,   KC_NO, KC_NO,   KC_F7, KC_F8, KC_F9, KC_F12,
    OS_CTL, OS_GUI, OS_ALT, OS_SFT, KC_NO, KC_NO,   KC_NO, KC_NO,   KC_F4, KC_F5, KC_F6, KC_F11,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,   KC_NO, KC_NO,   KC_F1, KC_F2, KC_F3, KC_F10,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_TRNS, KC_NO, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_NO 
  ),

// .................................................................. Short Cuts

// http://www.keyboard-layout-editor.com/#/gists/9c46dc89637cc99d0531ce3702d22236
  // .-----------------------------------------------------------------------------------.
  // |      |      | Copy | Paste|      |      |      |      |      |      |      |      |
  // |--------------------------------------------------------------+------+------+------|
  // | Undo |  Cut | Copy | Paste|      |      |      |      | PRIV |  PUB |      |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |  Nak |  Eot |      |      |      |      |      |      |      |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |  f() |      |      |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_EDIT] = LAYOUT_ortho_4x12(
    KC_NO, KC_NO, TMCOPY, TMPASTE, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,
    UNDO,  CUT,   COPY,   PASTE,   KC_NO, KC_NO, KC_NO,   KC_NO, TD_PRIV, TD_SEND, KC_NO, KC_NO,
    KC_NO, KC_NO, NAK,    EOT,     KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO,  KC_NO,   KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO
  ),

// ................................................................ Adjust Layer

  // ,-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      |      |      |      |      |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |Aud on|      |      |      |      |      |      |      |      |      |      |      |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // | Reset|      |      |      |      |      |      |      |      |      |      |      |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |      |      |      |  f() |      |      |      |      |  f() |      |      |      |
  // `-----------------------------------------------------------------------------------'

// TODO: Add Power off, Sleep, Lock

  [_ADJUST] = LAYOUT_ortho_4x12(
    KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
    AU_ON, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
    RESET, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO
  )
};

#ifdef AUDIO_ENABLE
float song_startup  [][2] = SONG(STARTUP_SOUND);
float song_colemak  [][2] = SONG(COLEMAK_SOUND);
float song_qwerty   [][2] = SONG(QWERTY_SOUND);
float song_caps_on  [][2] = SONG(CAPS_LOCK_ON_SOUND);
float song_caps_off [][2] = SONG(CAPS_LOCK_OFF_SOUND);
float music_scale   [][2] = SONG(MUSIC_SCALE_SOUND);
float song_goodbye  [][2] = SONG(GOODBYE_SOUND);
#endif

// .......................................................... Keycode Primitives

// register simple key press
void tap_key(uint16_t keycode)
{
  register_code  (keycode);
  unregister_code(keycode);
}

void shift_key(uint16_t keycode)
{
  register_code  (KC_LSFT);
  tap_key        (keycode);
  unregister_code(KC_LSFT);
}

#define         SHIFT   1
#define         NOSHIFT 0

static uint16_t key_timer = 0;

// key press for com_layer() and lt_shift() macros
bool key_press(uint16_t keycode, uint8_t shift)
{
  if (keycode) {
    if (timer_elapsed(key_timer) < TAPPING_TERM) {
      if (shift) {
        shift_key(keycode);
      }
      else {
        tap_key(keycode);
      }
      return true;
    }
  }
  return false;
}

// ALT_T, CTL_T, GUI_T, SFT_T for shifted keycodes
void mt_shift(keyrecord_t *record, uint16_t modifier, uint16_t keycode)
{
  if (record->event.pressed) {
    register_code (modifier);
    key_timer = timer_read();
  }
  else {
    unregister_code (modifier);
    if (timer_elapsed(key_timer) < TAPPING_TERM) {
      shift_key(keycode);
    }
    key_timer = 0;
  }
}

// ................................................................... Mod Masks

// tap dance persistant mods, see process_record_user()
// keyboard_report->mods (?) appears to be cleared by tap dance
static uint8_t mods = 0;

void tap_mods(keyrecord_t *record, uint16_t keycode)
{
  if (record->event.pressed) {
    mods |= MOD_BIT(keycode);
  }
  else {
    mods &= ~(MOD_BIT(keycode));
  }
}

// (un)register modifiers
void modifier(void (*f)(uint8_t))
{
  if (mods & MOD_BIT(KC_LCTL)) {
    (*f)(KC_LCTL);
  }
  if (mods & MOD_BIT(KC_LGUI)) {
    (*f)(KC_LGUI);
  }
  if (mods & MOD_BIT(KC_LALT)) {
    (*f)(KC_LALT);
  }
}

// ......................................................... Triple Dance Insert

void tilde(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 2) {
    register_code(KC_ALGR);  // KC_LSFT -> KC_ALGR
    register_code(NO_QUOT);  // KC_GRV -> NO_QUOT
  }
  // tap: keycode
  else {
    register_code(KC_ALGR);  // shift_key(KC_GRV) -> register_code KC_ALGR & NO_QUOT
    register_code(NO_QUOT);
    // double tap: unix home directory
    if (state->count > 1) {
      unregister_code(KC_ALGR);  // tap_key(KC_SLSH) -> unregister_code(KC_ALGR)  &  shift_key(KC_7);
      shift_key(KC_7);
    }
  }
}

void tilde_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(NO_QUOT);
  unregister_code(KC_ALGR);
}

void rcurly(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 3) {
    register_code(KC_ALGR);
    shift_key(KC_9);
  }
  // tap: keycode
  else if (state->count > 2) {
      register_code(KC_ALGR);
      shift_key(KC_8);
      shift_key(KC_9);
      unregister_code(KC_ALGR);
      tap_key(KC_LEFT);
  } 
  else if (state->count > 1) {
      register_code(KC_ALGR);
      shift_key(KC_8);
      shift_key(KC_9);
  }
  else {
    register_code(KC_ALGR);
    shift_key(KC_9);
  }
}

void rcurly_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_ALGR);
}

void lcurly(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 3) {
    register_code(KC_ALGR);
    shift_key(KC_8);
  }
  // tap: keycode
  else if (state->count > 2) {
      register_code(KC_ALGR);
      shift_key(KC_8);
      shift_key(KC_9);
      unregister_code(KC_ALGR);
      tap_key(KC_LEFT);
  } 
  else if (state->count > 1) {
      register_code(KC_ALGR);
      shift_key(KC_8);
      shift_key(KC_9);
  }
  else {
    register_code(KC_ALGR);
    shift_key(KC_8);
  }
}

void lcurly_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_ALGR);
}

void rbrace(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 3) {
    register_code(KC_RALT);
    shift_key(KC_9);
  }
  // tap: keycode
  else if (state->count > 2) {
      register_code(KC_RALT);
      tap_key(KC_8);
      tap_key(KC_9);
      unregister_code(KC_RALT);
      tap_key(KC_LEFT);
  } 
  else if (state->count > 1) {
      register_code(KC_RALT);
      tap_key(KC_8);
      tap_key(KC_9);
  }
  else {
    register_code(KC_RALT);
    tap_key(KC_9);
  }
}

void rbrace_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_RALT);
}


void lbrace(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 3) {
    register_code(KC_RALT);
    shift_key(KC_8);
  }
  // tap: keycode
  else if (state->count > 2) {
      register_code(KC_RALT);
      tap_key(KC_8);
      tap_key(KC_9);
      unregister_code(KC_RALT);
      tap_key(KC_LEFT);
  } 
  else if (state->count > 1) {
      register_code(KC_RALT);
      tap_key(KC_8);
      tap_key(KC_9);
  }
  else {
    register_code(KC_RALT);
    tap_key(KC_8);
  }
}

void lbrace_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_RALT);
}

void rangle(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 3) {
    tap_key(KC_GRV);
  }
  // tap: keycode
  else if (state->count > 2) {
      tap_key(KC_GRV);
      shift_key(KC_GRV);
      tap_key(KC_LEFT);
  } 
  else if (state->count > 1) {
      tap_key(KC_GRV);
      shift_key(KC_GRV);
  }
  else {
    shift_key(KC_GRV);
  }
}

void rparen(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 3) {
    shift_key(KC_9);
  }
  // tap: keycode
  else if (state->count > 2) {
      shift_key(KC_8);
      shift_key(KC_9);
      tap_key(KC_LEFT);
  } 
  else if (state->count > 1) {
      shift_key(KC_8);
      shift_key(KC_9);
  }
  else {
    shift_key(KC_9);
  }
}

// .................................................... Triple Dance Shift/Layer

static uint8_t dt_shift = 0;

void double_shift(uint16_t keycode, uint8_t layer)
{
  tap_key (keycode);
  if (DT_SHIFT) {
    // set_oneshot_mods(MOD_LSFT);
    // layer_on(layer);
    layer_on(_SHIFT);
    set_oneshot_layer(_SHIFT, ONESHOT_START);
    dt_shift = 1;
  }
  else {
    layer_on(layer);
  }
}

// tap dance LT (LAYER, KEY) emulation with <KEY><DOWN> -> <KEY><SHIFT> and auto-repeat extensions!
void tap_shift(qk_tap_dance_state_t *state, uint16_t keycode, uint8_t layer)
{
  // double tap plus down
  if (state->count > 2) {
    // double enter shift
    if (keycode == KC_ENT) {
      tap_key     (keycode);
      double_shift(keycode, layer);
    }
    // repeating keycode
    else {
      register_code(keycode);
    }
  }
  // tap plus down (or double tap): keycode (one shot) shift
  else if (state->count > 1) {
    double_shift(keycode, layer);
  }
  // down: shift
  else if (state->pressed) {
    layer_on(layer);
  }
  // tap: keycode
  else {
    modifier(register_code);
    tap_key (keycode);
    modifier(unregister_code);
  }
}

void tap_reset(uint16_t keycode, uint8_t layer)
{
  unregister_code(keycode);
  if (DT_SHIFT && dt_shift) {
    clear_oneshot_layer_state(ONESHOT_PRESSED);
    dt_shift = 0;
  }
  else {
    layer_off(layer);
  }
}

// augment pseudo LT (_RSHIFT, KC_ENT) handling below for rapid <ENTER><SHIFT> sequences
void enter(qk_tap_dance_state_t *state, void *user_data)
{
  tap_shift(state, KC_ENT, _RSHIFT);
}

void enter_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_ENT, _RSHIFT);
}

// augment pseudo LT (_LSHIFT, KC_SPC) handling below for rapid <SPACE><SHIFT> sequences
void space(qk_tap_dance_state_t *state, void *user_data)
{
  tap_shift(state, KC_SPC, _LSHIFT);
}

void space_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_SPC, _LSHIFT);
}

// ............................................................. Tap Dance Pairs

// tap dance shift rules
#define S_NEVER  0
#define S_SINGLE 1
#define S_DOUBLE 2
#define S_ALWAYS S_SINGLE | S_DOUBLE

void symbol_pair(uint8_t shift, uint16_t left, uint16_t right)
{
  if (shift & S_DOUBLE) {
    shift_key(left);
    shift_key(right);
  }
  else {
    tap_key(left);
    tap_key(right);
  }
}

#define CLOSE 1

// tap dance symbol pairs
void tap_pair(qk_tap_dance_state_t *state, uint8_t shift, uint16_t left, uint16_t right, uint8_t modifier, uint8_t close)
{
  // triple tap: left right with cursor between symbol pair a la vim :-)
  if (state->count > 2) {
    symbol_pair(shift, left, right);
    tap_key(KC_LEFT);
  }
  // double tap: left right
  else if (state->count > 1) {
    symbol_pair(shift, left, right);
  }
  // down: modifier
  else if (state->pressed) {
    if (modifier) {
      register_code(modifier);
    }
  }
  // tap: left (close: right)
  else {
    if (shift & S_SINGLE) {
      shift_key(close ? right : left);
    }
    else {
      tap_key(close ? right : left);
    }
  }
  if (!modifier) {
    reset_tap_dance(state);
  }
}

void doublequote(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, NO_QUO2, NO_QUO2, 0, 0); // KC_QUOT -> NO_QUO2
}

void grave(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, NO_ACUT, NO_ACUT, 0, 0); // S_NEVER, KC_GRV -> S_ALWAYS, NO_ACUT
}

/*void lbrace(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_LBRC, KC_RBRC, 0, 0);
}*/

/*void lcurly(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_LBRC, KC_RBRC, 0, 0);
}*/

void lparen(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_8, KC_9, 0, 0);
}

/*void lparen_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LCTL);
}*/

/*void quote(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, NO_QUO2, NO_QUO2, 0, 0); // KC_QUOT -> NO_QUO2
}*/

/*void rangle(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, NO_LESS_MAC, NO_GRTR_MAC, 0, CLOSE); //S_ALWAYS, KC_COMM, KC_DOT, 0, CLOSE)
}*/

/*void rbrace(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_LBRC, KC_RBRC, 0, CLOSE);
}*/

/*void rcurly(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_LBRC, KC_RBRC, 0, CLOSE);
}*/

/*void rparen(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_9, KC_8, 0, 0);  // S_ALWAYS, KC_9, KC_0, KC_LCTL, CLOSE
}*/

/*void rparen_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LCTL);
}*/

// ............................................................ Tap Dance Insert

void colon(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_SPC);
    shift_key(KC_DOT);  // KC_SCLN -> KC_DOT
    shift_key(KC_DOT);  // KC_SCLN -> KC_DOT
    tap_key(KC_SPC);
  }
  else {
    shift_key(KC_DOT);  // KC_SCLN -> KC_DOT
  }
  reset_tap_dance(state);
}

void comma(qk_tap_dance_state_t *state, void *user_data)
{
  tap_key(KC_COMM);
  if (state->count > 1) {
    tap_key(KC_SPC);
  }
  reset_tap_dance(state);
}

void greater(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_SPC);
    tap_key(KC_MINS);
    shift_key(KC_DOT);
    tap_key(KC_SPC);
  }
  else {
    shift_key(KC_DOT);
  }
  reset_tap_dance(state);
}

void lesser(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_SPC);
    shift_key(KC_COMM);
    tap_key(KC_MINS);
    tap_key(KC_SPC);
  }
  else {
    shift_key(KC_COMM);
  }
  reset_tap_dance(state);
}

// compile time macro string, see functions/hardware planck script
void private(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
#ifdef PRIVATE_STRING
#include "private_string.h"
#endif
  }
  reset_tap_dance(state);
}

// config.h defined string
void send(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    SEND_STRING(PUBLIC_STRING);
  }
  reset_tap_dance(state);
}

// ............................................................ Tap Dance Toggle

void caps(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_CAPS);    
  }
  else {
    set_oneshot_mods(MOD_LSFT);
  }
  reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [_CAPS] = ACTION_TAP_DANCE_FN         (caps)
 ,[_COLN] = ACTION_TAP_DANCE_FN         (colon)
 ,[_COMM] = ACTION_TAP_DANCE_FN         (comma)
 ,[_DQOT] = ACTION_TAP_DANCE_FN         (doublequote)
 ,[_ENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enter, enter_reset)
 ,[_GT]   = ACTION_TAP_DANCE_FN         (greater)
 ,[_GRV]  = ACTION_TAP_DANCE_FN         (grave)  
 ,[_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbrace, lbrace_reset)
 ,[_LCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lcurly, rcurly_reset)
 ,[_LPRN] = ACTION_TAP_DANCE_FN         (lparen)
 ,[_LT]   = ACTION_TAP_DANCE_FN         (lesser)
 ,[_PRIV] = ACTION_TAP_DANCE_FN         (private)
 ,[_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbrace, rbrace_reset)
 ,[_RCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rcurly, rcurly_reset)
 ,[_RNGL] = ACTION_TAP_DANCE_FN         (rangle)
 ,[_RPRN] = ACTION_TAP_DANCE_FN         (rparen)
 ,[_SEND] = ACTION_TAP_DANCE_FN         (send)
 ,[_SPC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space, space_reset)
 ,[_TILD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tilde, tilde_reset)
};

// .............................................................. Dynamic Layers

#define        LEFT    1
#define        RIGHT   2
static uint8_t thumb = 0;

// LEFT (KC_SPC, S(KC_BSLS)), RIGHT (KC_LEFT, S(KC_LEFT)) opposite thumb combinations, see process_record_user()
// up,   up   -> _COLEMAK
// up,   down -> _SYMBOL
// down, up   -> _NUMBER
// down, down -> _MOUSE
#define THUMBS_DOWN _MOUSE

static uint8_t overlayer = THUMBS_DOWN;

// left right layer combinations
void com_layer(keyrecord_t *record, uint8_t side, uint16_t keycode, uint8_t shift, uint8_t layer, uint8_t default_layer)
{
  if (record->event.pressed) {
    // layer_on via tap_layer(), see process_record_user()
    key_timer = timer_read();
    thumb     = thumb | side;
  }
  else {
    layer_off(layer);
    // opposite com_layer() thumb may have switched effective layer!
    if (overlayer) {
      layer_off(overlayer);
      overlayer = THUMBS_DOWN;
    }
    if (!key_press(keycode, shift)) {
      // opposite thumb down? see left right combination layer table above
      if (thumb & (side == LEFT ? RIGHT : LEFT)) {
        layer_on(default_layer);
        overlayer = default_layer;
      }
    }
    clear_mods();
    thumb     = thumb & ~side;
    key_timer = 0;
  }
}

// LT for S(keycode)
void lt_shift(keyrecord_t *record, uint16_t keycode, uint8_t layer)
{
  if (record->event.pressed) {
    layer_on(layer);
    key_timer = timer_read();
  }
  else {
    layer_off(layer);
    // for shifted keycodes, hence, LT_SHIFT
    key_press(keycode, SHIFT);
    clear_mods();
    key_timer = 0;
  }
}

// set layer asap to overcome macro latency errors, notably tap dance and LT usage
// this routine inexplicably (?) sets layer_on() faster than can be done in com_layer()
void tap_layer(keyrecord_t *record, uint8_t layer)
{
  if (record->event.pressed) {
    layer_on(layer);
  }
  else {
    layer_off(layer);
  }
}

// ........................................................... User Keycode Trap

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case AT_DOWN:
      tap_mods(record, KC_LALT);
      break;
    case CT_RGHT:
      tap_mods(record, KC_LCTL);
      break;
    case GT_UP:
      tap_mods(record, KC_LGUI);
      break;
    case LT_ESC:
      tap_layer(record, _NUMBER);
      break;
    case LT_LEFT:
      tap_layer(record, _SYMBOL);
      // LT (_SYMBOL, KC_LEFT) left right combination layer
      com_layer(record, RIGHT, 0, 0, _SYMBOL, _LSHIFT);
      break;
    case OS_ALT:
      tap_mods(record, KC_LALT);
      break;
    case OS_CTL:
      tap_mods(record, KC_LCTL);
      break;
    case OS_GUI:
      tap_mods(record, KC_LGUI);
      break;
    case PS_CIRC:
      // GUI_T(S(KC_6))
      mt_shift(record, KC_LGUI, KC_RBRC); // Just for mac, was: mt_shift(record, KC_LGUI, KC_6);
      break;
    case PS_DLR:
      // SFT_T(S(KC_4))
      mt_shift(record, KC_LSFT, KC_4);
      break;
    case PS_LPRN:
      // CTL_T(S(KC_9))
      mt_shift(record, KC_LCTL, KC_8); // was: mt_shift(record, KC_LCTL, KC_9);
      break;
    case PS_PERC:
      // ALT_T(S(KC_5))
      mt_shift(record, KC_LALT, KC_5);
      break;
    case PS_LEFT:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_LEFT)) left right combination layer
      com_layer(record, RIGHT, KC_LEFT, SHIFT, _MOUSE, _LSHIFT);
      break;
    case PS_PIPE: // Not really needed since NO_PIPE_MAC is in layers. Or is it???
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_BSLS)) left right combination layer
      com_layer(record, LEFT, KC_BSLS, SHIFT, _MOUSE, _SYMBOL);
      break;
    case PS_TAB: // Not sure whether this is needed in my use case?
      // LT (_FNCKEY, S(KC_TAB)) emulation
      lt_shift(record, KC_TAB, _FNCKEY);
      break;
    case TD_ENT:
      tap_layer(record, _RSHIFT);
      // LT (_RSHIFT, KC_ENT) emulation, see tap dance enter
      break;
    case TD_SPC:
      tap_layer(record, _LSHIFT);
      // LT (_LSHIFT, KC_SPC) left right combination layer, see tap dance space
      com_layer(record, LEFT, 0, 0, _LSHIFT, _SYMBOL);
      break;
    // case PLOVER:
    //   plover(record);
    //   return false;
    // case PLOVEX:
    //   plovex(record);
    //   return false;
  }
  return true;
}

// ....................................................................... Audio

void matrix_init_user(void)
{
#ifdef AUDIO_ENABLE
  startup_user();
#endif
}

#ifdef AUDIO_ENABLE
  void startup_user(void)
  {
    wait_ms(20);                            // gets rid of tick
    PLAY_SONG(song_startup);
  }

  void shutdown_user(void)
  {
    PLAY_SONG(song_goodbye);
    wait_ms(150);
    stop_all_notes();
  }

  void music_on_user(void)
  {
    music_scale_user();
  }

  void music_scale_user(void)
  {
    PLAY_SONG(music_scale);
  }
#endif
