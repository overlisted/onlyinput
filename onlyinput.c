#include "onlyinput.h"

#if defined(WINDOWS) || defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
#define ON_WINDOWS
#elif defined(__wasm__)
#define ON_WEB
#elif defined(EGL_LEAN_AND_MEAN)
#define ON_JUST_EGL
#elif defined(__android__) || defined(ANDROID)
#define ON_ANDROID
#else // *MOST LIKELY* x11
#define ON_X11
#endif

#if defined(ON_WINDOWS) || defined(ON_WEB)
#define WINDOWS_FASHION_KEYS
#endif

static int CurrentBDown = 0;
static int CurrentKeycode = 0;

static int ShiftDown = 0;

void OIMaintain(int keycode, int bDown) {
  CurrentKeycode = keycode;
  CurrentBDown = bDown;

#ifdef WINDOWS_FASHION_KEYS
  if(keycode == 0x10) ShiftDown = bDown;
#endif
  
#ifdef ON_X11
  if(keycode == 65505) ShiftDown = bDown;
#endif
}

char OIReadAscii() {
  char result = 0;
  
  if(CurrentBDown) {
#ifdef WINDOWS_FASHION_KEYS
    if(CurrentKeycode >= 0x41 && CurrentKeycode < 0x5A) {
#else
    if(CurrentKeycode >= 32 && CurrentKeycode < 127) {
#endif
      result = CurrentKeycode;
      
      if(CurrentKeycode > 96 && CurrentKeycode < 12 && ShiftDown) result -= 32;
      return result;
    } else {
#ifdef WINDOWS_FASHION_KEYS
      switch(CurrentKeycode) {
        case 0xBA: result = ';'
        case 0xBB: result = '+'
        case 0xBC: result = ','
        case 0xBD: result = '-'
        case 0xBE: result = '.'
        case 0xBF: result = '/'
        case 0xC0: result = '`'
        case 0xDB: result = '['
        case 0xDC: result = '\\'
        case 0xDD: result = ']'
        case 0xDE: result = '\''
        case 0xDF: result = '{'
      }
#endif
    }
  }
                     
  return result;
}
