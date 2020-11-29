#define CNFGOGL

#define ONLYINPUT_IMPLEMENTATION
#define CNFG_IMPLEMENTATION
#include <../onlyinput.h>
#include <rawdraw/CNFG.h>

void HandleKey(int keycode, int bDown) {
  OIMaintain(keycode, bDown);
}

void HandleButton(int x, int y, int button, int bDown) {

}

void HandleMotion(int x, int y, int mask) {

}

void HandleDestroy() {

}

int main() {
  return 0;
}
