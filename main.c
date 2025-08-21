// Use multiplexing to draw images on a 4x4 array of LEDs

#define DELAY_VALUE 80000 // one millisecond at 80 MHz

#include "TM4C123.h"
#include "hardware.h"
#include "display.h"
#include "animations.c"
#include <stdint.h>

volatile uint8_t ani_num;

static void delay(uint32_t millis) {
  for (uint32_t i = 0; i < millis; i++) {
    // wait until COUNTFLAG is set
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
  }
}

void switch_animation(void) {
  ani_num++;
  if (ani_num > 3) ani_num = 0;
}

static const uint8_t test_img[4][4] = {
  {0, 1, 1, 2},
  {0, 1, 1, 2},
  {0, 1, 1, 2},
  {0, 1, 1, 2},
};

int main(void) {
  display_initialize(); // also calls HW_Init()

  // set interrupt for animation switching
  HW_PinAttachInterrupt(PIN_PD6, EDGE_FALLING, switch_animation);
  
  // display a short animation
  while (1) {

    if (ani_num == 0) {
      for (int i = 0; i < ANIMATION_ORBIT_LENGTH; i++) {
	// draw each frame for 25 ms (40 hz)
	for (uint32_t j = 0; j < 25u / get_refresh_speed(); j++) {
	  draw(animation_orbit[i]);
	  while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0); // display_initialize also initializes SysTick
	}
      }
    } else if (ani_num == 1) {
      for (int i = 0; i < ANIMATION_SLIDE_LENGTH; i++) {
	// draw each frame for 25 ms (40 hz)
	for (uint32_t j = 0; j < 25u / get_refresh_speed(); j++) {
	  draw(animation_slide[i]);
	  while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0); // display_initialize also initializes SysTick
	}
      }
    } else if (ani_num == 2) {
      for (int i = 0; i < ANIMATION_PULSE_LENGTH; i++) {
	// draw each frame for 25 ms (40 hz)
	for (uint32_t j = 0; j < 25u / get_refresh_speed(); j++) {
	  draw(animation_pulse[i]);
	  while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0); // display_initialize also initializes SysTick
	}
      }
    } else {
      draw(test_img);
    }
  }
}
