#pragma once

// NOTE: Call this in your HandleInput() *BEFORE* you call the RDUI's handler
void OIMaintain(int keycode, int bDown);
char OIReadAscii();

#ifdef ONLYINPUT_IMPLEMENTATION
#include "onlyinput.c"
#endif
