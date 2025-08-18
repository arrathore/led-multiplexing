// HAL defining what we need out of the hardware

#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

// logical pins for Port E
typedef enum {
  PIN_PE0,
  PIN_PE1,
  PIN_PE2,
  PIN_PE3,
  PIN_PE4,
  PIN_PE5,
  PIN_COUNT
} pin_t;

// HAL functions 
void HW_Init(void);
void HW_PinInit(pin_t pin);
void HW_PinSet(pin_t pin);
void HW_PinClear(pin_t pin);
void HW_PinToggle(pin_t pin);

#endif
