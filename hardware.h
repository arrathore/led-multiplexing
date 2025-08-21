// HAL defining what we need out of the hardware

#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

// logical input pins
typedef enum {
  // Port D
  PIN_PD0,
  PIN_PD1,
  PIN_PD2,
  PIN_PD3,
  // PIN_PD4, [used in UART]
  // PIN_PD5,

  // PIN_PD7, [used in JTAG]

  // Port E
  PIN_PE0,
  PIN_PE1,
  PIN_PE2,
  PIN_PE3,
  PIN_PE4,
  PIN_PE5,
  
  OUT_PIN_COUNT
} out_pin_t;

// logical output pins
typedef enum {
  // Port D
  PIN_PD6,

  IN_PIN_COUNT
} in_pin_t;

// interrupt triggers
typedef enum {
  EDGE_FALLING,
  EDGE_RISING,
  EDGE_BOTH
} edge_t;

// HAL functions
// perform any needed initialization
void HW_Init(void);

// initialize an input pin
void HW_InPinInit(in_pin_t pin);

// initialize an output pin
void HW_OutPinInit(out_pin_t pin);

// read an input pin
uint32_t HW_PinRead(in_pin_t pin);

// attach an interrupt to an input pin
void HW_PinAttachInterrupt(in_pin_t pin, edge_t edge, void(*callback)(void));

// set an output pin
void HW_PinSet(out_pin_t pin);

// clear an output pin
void HW_PinClear(out_pin_t pin);

// toggle an output pin
void HW_PinToggle(out_pin_t pin);

#endif
