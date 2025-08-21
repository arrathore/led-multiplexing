// Use multiplexing to draw an image on a 4x4 array of LEDs
// Expects HW_Init() and SysTick_Init() already called 
#define DELAY_VALUE 80000 // one millisecond

#include "display.h"
#include "TM4C123.h"
#include "hardware.h"
#include <stdint.h>

uint32_t get_width(void) {
  return 4;
}

uint32_t get_height(void) {
  return 4;
}

uint32_t get_refresh_speed(void) {
  return 4;
}

void SysTick_Init(void) {
  SysTick->CTRL = 0; // disable SysTick
  SysTick->LOAD = 80 - 1; // reload val for 1us (80 cycles)
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // enable SysTick with system clock
}

// sets up needed pins through HAL and initialize SysTick for timing
void display_initialize() {
  SysTick_Init();
  HW_Init();
}

// expects SysTick_Init() already called
static void delay(uint32_t millis) {
  for (uint32_t i = 0; i < (millis * 1000); i++) {
    // wait until COUNTFLAG is set
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
  }
}

// expects SysTick_Init() already called
static void udelay(uint32_t micros) {
  for (uint32_t i = 0; i < micros; i++) {
    // wait until COUNTFLAG is set
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
  }
}

// draw the given image, expects 4x4 array of 1s and 0s
// expects display_initialize() already called
void draw(const uint8_t img[4][4]) {
  // for each row
  for (int i = 0; i < 4; i++) {
    // which pixels are at low-brightness
    uint8_t lows[] = {0, 0, 0, 0};
    
    // draw row i
    for (int j = 0; j < 4; j++) {
      // if the LED should be off, we turn on the pin (Port D)
      if (img[i][j] == 0) HW_PinSet((out_pin_t)j);
      else {
	HW_PinClear((out_pin_t)j);
	lows[j] = img[i][j];
      }
    }

    // turn on line (display row i)
    HW_PinSet((out_pin_t)(i + 4)); // scanline pins are at offset 4 (Port E)

    // if the pixel is low-brightness we turn it off early
    udelay(100);
    for (int j = 0; j < 4; j++) if (lows[j] == 1) HW_PinSet((out_pin_t)j);
    udelay(900);
    HW_PinClear((out_pin_t)(i + 4));
  }
}
