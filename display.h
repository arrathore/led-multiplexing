// Define functions to get info about and draw images on a display

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

// how many pixels wide is the display?
uint32_t get_width(void);
// how many pixels tall is the display?
uint32_t get_height(void);
// about how long does it take to draw one frame?
uint32_t get_refresh_speed(void);

// run any hardware initialization needed
void display_initialize(void);

/**
   draw an image encoded as an array of 1s and 0s
   expects an array of dimensions width x height
*/
void draw(const uint8_t img[get_height()][get_width()]);

#endif
