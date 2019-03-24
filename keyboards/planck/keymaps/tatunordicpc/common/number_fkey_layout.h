
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ......................................................... Number Keypad Layer
#ifdef SHIFT_SYMBOLS
  // .-----------------------------------------------------------------------------------.
  // |      |   F  |   E  |   D  |      |      |      |   /  |   7  |   8  |   9  |   *  |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |   C  |   B  |   A  |      |      |      |   .  |   4  |   5  |   6  |   -  |
  // |-----------------------------------------------------------------------------------|
  // |      |   #  |   G  |   \  |      |      |      |   ,  |   1  |   2  |   3  |   +  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |   0  |   =  |      |      |      |
  // |      |      |      |  f() |      |      |      |   =  |   0  |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_NUMBER] = {
    {_______, KC_F,    MT_E,    KC_D,    _______, ___x___, ___x___, NO_SLSH, KC_7,    KC_8,    KC_9,    S(KC_NUHS)},
    {OS_CTL,  GT_C,    AT_B,    ST_A,    _______, ___x___, ___x___, TD_DOT,  KC_4,    KC_5,    KC_6,    NO_MINS},
    {_______, KC_HASH, SM_G,    KC_BSLS, _______, ___x___, ___x___, TD_COMM, KC_1,    KC_2,    KC_3,    NO_PLUS},
#ifdef THUMB_0
    {___x___, ___x___, ___x___, ___fn__, ___x___, ___x___, ___x___, KC_0,    LT_EQL,  ___x___, ___x___, ___x___},
#else
    {___x___, ___x___, ___x___, ___fn__, ___x___, ___x___, ___x___, NO_EQL,  LT_0,    ___x___, ___x___, ___x___},
#endif
  },
#else
  // .-----------------------------------------------------------------------------------.
  // |      |   F  |   E  |   D  |      |      |      |   /  |   7  |   8  |   9  |   *  |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |   C  |   B  |   A  |      |      |      |   .  |   4  |   5  |   6  |   -  |
  // |-----------------------------------------------------------------------------------|
  // |      |   #  |   X  |   G  |      |      |      |   ,  |   1  |   2  |   3  |   +  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |   0  |   =  |      |      |      |
  // |      |      |      |  f() |      |      |      |   =  |   0  |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_NUMBER] = {
    {_______, KC_F,    MT_E,    KC_D,    _______, _______, _______, NO_SLSH, KC_7,    KC_8,    KC_9,    S(KC_NUHS)},
    {OS_CTL,  GT_C,    AT_B,    LT_A,    _______, _______, _______, KC_DOT,  KC_4,    KC_5,    KC_6,    NO_MINS},
    {_______, KC_HASH, MT_X,    S(KC_G), _______, _______, _______, TD_COMM, KC_1,    KC_2,    KC_3,    NO_PLUS},
#ifdef THUMB_0
    {___x___, ___x___, ___x___, ___fn__, ___x___, ___x___, ___x___, KC_0,    LT_EQL,  ___x___, ___x___, ___x___},
#else
    {___x___, ___x___, ___x___, ___fn__, ___x___, ___x___, ___x___, NO_EQL,  LT_0,    ___x___, ___x___, ___x___},
#endif
  },

  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |   {  |   &  |   ?  |   :  |   }  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |   (  |   $  |   %  |   ^  |   )  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |   [  |   <  |   ~  |   >  |   ]  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |   \  |   |  |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_NUMSYM] = {
    {_______, _______, _______, ___x___, _______, _______, _______, TD_LCBR, NO_AMPR, NO_QUES, NO_COLN, NO_RCBR},
    {___x___, ___x___, ___x___, ___fn__, _______, _______, _______, TD_LPRN, NO_DLR,  KC_PERC, NO_CIRC, NO_RPRN},
    {_______, _______, _______, ___x___, _______, _______, _______, TD_LBRC, NO_LESS, NO_TILD, NO_GRTR, NO_RBRC},
    {___x___, ___x___, ___x___, ___fn__, ___x___, ___x___, ___x___, NO_BSLS, NO_PIPE, ___x___, ___x___, ___x___},
  },
#endif

// ............ .................................................. Function Keys

  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      |  F7  |  F8  |  F9  |  F12 |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |  GUI |  Alt | Shift|      |      |      |      |  F4  |  F5  |  F6  |  F11 |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |      |  F1  |  F2  |  F3  |  F10 |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |  f() |      |   +  |      |      |      |      |
  // |      |      |      |      |  f() |      |      |   +  |      |      |      |      | see _PLOVER
  // '-----------------------------------------------------------------------------------'

  [_FNCKEY] = {
    {_______, _______, _______, _______, _______, ___x___, ___x___, _______, KC_F7,   KC_F8,   KC_F9,   KC_F12 },
    {OS_CTL,  OS_GUI,  OS_ALT,  OS_SFT,  _______, ___x___, ___x___, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11 },
    {_______, _______, _______, _______, _______, ___x___, ___x___, _______, KC_F1,   KC_F2,   KC_F3,   KC_F10 },
    {_______, _______, _______, _______, ___fn__, ___fn__, _______, KC_PLUS, _______, _______, _______, _______},
  },

