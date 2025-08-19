// Use multiplexing to draw images on a 4x4 array of LEDs

#define DELAY_VALUE 80000 // one millisecond
#define ANI_LENGTH 2

#include "TM4C123.h"
#include "hardware.h"
#include "display.h"
#include "animations.c"
#include <stdint.h>

static void delay(uint32_t millis) {
  for (uint32_t i = 0; i < millis; i++) {
    // wait until COUNTFLAG is set
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
  }
}

int main(void) {
  display_initialize();
  // display a short animation
  while (1) {
    for (int i = 0; i < ANIMATION_SLIDE_LENGTH; i++) {
      // draw each frame for 25 ms (40 hz)
      for (uint32_t j = 0; j < 25u / get_refresh_speed(); j++) {
	draw(animation_slide[i]);
	while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0); // display_initialize also initializes SysTick
      }
    }
    // play the animation every 500 ms
    delay(500);
  }
}
