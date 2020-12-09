#define CNFGOGL

#include <stdio.h>

#define ONLYINPUT_IMPLEMENTATION
#define CNFG_IMPLEMENTATION
#include <../onlyinput.h>
#include <rawdraw/CNFG.h>

void HandleKey(int keycode, int bDown) {
  OIHandleKey(keycode, bDown);
}

void HandleButton(int x, int y, int button, int bDown) {

}

void HandleMotion(int x, int y, int mask) {

}

void HandleDestroy() {

}

int main() {
  CNFGSetup("Example", 800, 600);

  while(1) {
    CNFGClearFrame();
    CNFGHandleInput();

    printf("Pressed letter: %c\n", OIReadAscii());

    CNFGSwapBuffers();
  }
}
