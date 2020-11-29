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
static struct ModifierKeys CurrentModifiers = {.shift = 0, .ctrl = 0, .alt = 0, .win = 0};

void OIHandleKey(int keycode, int bDown) {
  CurrentKeycode = 0;
  CurrentBDown = bDown;

  switch(keycode) {
#ifdef WINDOWS_FASHION_KEYS
    case 0x10: CurrentModifiers.shift = bDown; break;
    case 0x11: CurrentModifiers.ctrl = bDown; break;
    case 0x12: CurrentModifiers.alt = bDown; break;
    case 0x5B: CurrentModifiers.win = bDown; break;
    case 0x5C: CurrentModifiers.win = bDown; break;
#else
    case 65505: CurrentModifiers.shift = bDown; break;
    case 65507: CurrentModifiers.ctrl = bDown; break;
    case 65513: CurrentModifiers.alt = bDown; break;
    case 65516: CurrentModifiers.win = bDown; break;
#endif
    default: CurrentKeycode = keycode;
  }
}

char OIReadAscii() {
  char result = 0;
  
  if(CurrentBDown) {
#ifdef WINDOWS_FASHION_KEYS
    if(CurrentKeycode >= 96 && CurrentKeycode < 127) {
#else
    if(CurrentKeycode >= 32 && CurrentKeycode < 127) {
#endif
      result = CurrentKeycode;
      if(CurrentKeycode > 47 && CurrentKeycode < 58 && CurrentModifiers.shift) {
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
      
      if(CurrentKeycode > 96 && CurrentKeycode < 123 && CurrentModifiers.shift) result -= 32;
    } else {
      switch(CurrentKeycode) {
#ifdef WINDOWS_FASHION_KEYS
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
        case 9: result = 9; break; // Tab
#else
        case 65289: result = 9; break; // Tab
#endif
      }
    }

    if(CurrentModifiers.shift) {
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

struct ModifierKeys OIReadModifiers() {
  return CurrentModifiers;
}
