// Define functions to get info about and draw images on a display

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

// how many pixels wide is the display?
int get_width(void);
// how many pixels tall is the display?
int get_height(void);

// run any hardware initialization needed
void display_initialize();

/**
   draw an image encoded as an array of 1s and 0s
   expects an array of dimensions width x height
*/
void draw(const uint8_t img[get_height()][get_width()]);

#endif
