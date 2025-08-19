// Use multiplexing to draw images on a 4x4 array of LEDs

#define DELAY_VALUE 80000 // one millisecond

#include "TM4C123.h"
#include "hardware.h"
#include <stdint.h>

void SysTick_Init(void) {
  SysTick->CTRL = 0; // disable SysTick
  SysTick->LOAD = 80000 - 1; // reload val for 1ms (80k cycles)
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // enable SysTick with system clock
}

void delay(uint32_t millis) {
  for (uint32_t i = 0; i < millis; i++) {
    // wait until COUNTFLAG is set
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
  }
}

static const uint8_t img[4][4] = {
  {0, 1, 1, 0},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 1, 0},
};

int main(void) {
  SysTick_Init();

  HW_Init();

  while (1) {
    // for each row
    for (int i = 0; i < 4; i++) {
      // draw row i
      for (int j = 0; j < 4; j++) {
	// if the LED should be off, we turn on the pin
	if (img[i][j] == 0) HW_PinSet((pin_t)j);
	else HW_PinClear((pin_t)j);
      }
      
      // turn on line (display row i)
      HW_PinSet((pin_t)(i + 5)); // scanline pins are at offset 5

      delay(1);
      HW_PinClear((pin_t)(i + 5));
      delay(1);
    }
  }
}
