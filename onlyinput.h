#pragma once

struct ModifierKeys {
  int shift: 1;
  int ctrl: 1;
  int alt: 1;
  int win: 1;
	int caps_lock: 1;
	int caps_lock_down: 1;
};

// NOTE: Call this in your HandleKey() *BEFORE* you call the RDUI's handler
void OIHandleKey(int keycode, int bDown);
char OIReadAscii();
struct ModifierKeys OIReadModifiers();

#ifdef ONLYINPUT_IMPLEMENTATION
#include "onlyinput.c"
#endif
