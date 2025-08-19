// Use multiplexing to draw images on a 4x4 array of LEDs

#define DELAY_VALUE 80000 // one millisecond
#define ANI_LENGTH 2

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

static const uint8_t ani[ANI_LENGTH][4][4] = {
  {
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0},
  },
  {
    {1, 0, 0, 1},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {1, 0, 0, 1},
  },  
};

int main(void) {
  display_initialize();
  // display a short 'animation'
  while (1) {
    for (int i = 0; i < ANI_LENGTH; i++) {
      for (uint32_t j = 0; j < 500u / get_refresh_speed(); j++) {
	draw(ani[i]);
	while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0); // display_initialize also initializes SysTick
      }
    }
  }
}
