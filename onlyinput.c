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
  if(keycode == 0x10) {
#else
  if(keycode == 65505) {
#endif
    ShiftDown = bDown;
    CurrentKeycode = 0;
  }
}

char OIReadAscii() {
  char result = 0;
  
  if(CurrentBDown) {
      result = CurrentKeycode;
#ifdef WINDOWS_FASHION_KEYS
    if(CurrentKeycode >= 0x30 && CurrentKeycode < 0x5A) {
#else
    if(CurrentKeycode >= 32 && CurrentKeycode < 127) {
#endif
      if(CurrentKeycode > 47 && CurrentKeycode < 58 && ShiftDown) {
        switch(result) {
          case '1': result = '!'; break;
          case '2': result = '@'; break;
          case '3': result = '#'; break;
          case '4': result = '$'; break;
          case '5': result = '%'; break;
          case '6': result = '^'; break;
          case '7': result = '&'; break;
          case '8': result = '*'; break;
          case '9': result = '('; break;
          case '0': result = ')'; break;
        }
      }
      
      if(CurrentKeycode > 96 && CurrentKeycode < 12 && ShiftDown) result -= 32;
    } else {
#ifdef WINDOWS_FASHION_KEYS
      switch(CurrentKeycode) {
        case 0xBA: result = ';'; break;
        case 0xBB: result = '='; break;
        case 0xBC: result = ','; break;
        case 0xBD: result = '-'; break;
        case 0xBF: result = '/'; break;
        case 0xC0: result = '`'; break;
        case 0xDB: result = '['; break;
        case 0xDC: result = '\\'; break;
        case 0xDD: result = ']'; break;
        case 0xDE: result = '\''; break;
      }
#endif
    }

    if(ShiftDown) {
      switch(result) {
        case ';': result = ':'; break;
        case '=': result = '+'; break;
        case ',': result = '<'; break;
        case '-': result = '_'; break;
        case '.': result = '>'; break;
        case '/': result = '?'; break;
        case '`': result = '~'; break;
        case '[': result = '{'; break;
        case '\\': result = '|'; break;
        case ']': result = '}'; break;
        case '\'': result = '"'; break;
      }
    }
  }
                     
  return result;
}
