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
  if (ani_num > 2) ani_num = 0;
}

static const uint8_t test_img[4][4] = {
  {0, 1, 1, 2},
  {0, 1, 1, 2},
  {0, 1, 1, 2},
  {0, 1, 1, 2},
};

static inline const uint8_t* get_frame(const animation_t *ani, uint8_t frame_idx) {
  return ani->frames + frame_idx * ani->frame_width * ani->frame_height;
}

int main(void) {
  display_initialize(); // also calls HW_Init()

  // set interrupt for animation switching
  HW_PinAttachInterrupt(PIN_PD6, EDGE_FALLING, switch_animation);
  
  // display the selected animation
  while (1) {
    animation_t ani = *animations[ani_num];
    for (int i = 0; i < ani.length; i++) {
      // get the current frame
      const uint8_t *frame_ptr = get_frame(&ani, i);
      // draw each frame for the specified length
      for (uint32_t j = 0; j < ani.speed / get_refresh_speed(); j++) {
	draw((const uint8_t (*)[ani.frame_width])frame_ptr);
      }
    }    
  }
}
