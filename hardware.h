// HAL defining what we need out of the hardware

#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

// logical pins
typedef enum {
  // Port D
  PIN_PD0,
  PIN_PD1,
  PIN_PD2,
  PIN_PD3,
  // PIN_PD4, [used in UART]
  // PIN_PD5,
  PIN_PD6,
  // PIN_PD7, [used in JTAG]

  // Port E
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
