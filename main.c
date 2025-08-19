// Use multiplexing to draw images on a 4x4 array of LEDs

#define DELAY_VALUE 80000 // one millisecond

#include "TM4C123.h"
#include "hardware.h"
#include "display.h"
#include <stdint.h>

static const uint8_t img[4][4] = {
  {0, 1, 1, 0},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 1, 0},
};

int main(void) {
  display_initialize();

  // display a static image
  while (1) {
    draw(img);
  }
}
