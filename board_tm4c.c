// HAL implementation for the TM4C development board

#include "hardware.h"
#include "TM4C123.h"
#include <stdint.h>

// map logical pins for GPIO
typedef struct {
  GPIOA_Type* port;
  uint32_t mask;
} pinmap_t;

static const pinmap_t output_pinmap[OUT_PIN_COUNT] = {
  // Port D
  [PIN_PD0] = { GPIOD, (1U << 0) },
  [PIN_PD1] = { GPIOD, (1U << 1) },
  [PIN_PD2] = { GPIOD, (1U << 2) },
  [PIN_PD3] = { GPIOD, (1U << 3) },

  // Port E
  [PIN_PE0] = { GPIOE, (1U << 0) },
  [PIN_PE1] = { GPIOE, (1U << 1) },
  [PIN_PE2] = { GPIOE, (1U << 2) },
  [PIN_PE3] = { GPIOE, (1U << 3) },
  [PIN_PE4] = { GPIOE, (1U << 4) },
  [PIN_PE5] = { GPIOE, (1U << 5) },
};

static const pinmap_t input_pinmap[IN_PIN_COUNT] = {
  // Port D
  [PIN_PD6] = { GPIOD, (1U << 6) },
};

void HW_Init(void) {
  // enable clock to Ports E and D and wait until they're on
  SYSCTL->RCGCGPIO |= (1U << 4) | (1U << 3);
  while ((SYSCTL->PRGPIO & ((1U << 3) | (1U << 4))) != ((1U << 3) | (1U << 4)));

  // initialize pins from table
  for (int i = 0; i < OUT_PIN_COUNT; i++) HW_OutPinInit((out_pin_t)i);
  for (int i = 0; i < IN_PIN_COUNT; i++) HW_InPinInit((in_pin_t)i);
}

void HW_InPinInit(in_pin_t pin) {
  GPIOA_Type* port = input_pinmap[pin].port;
  uint32_t mask = input_pinmap[pin].mask;
  port->DIR &= ~mask; // set as input
  port->DEN |= mask; // digital enable
  port->PUR |= mask; // pull-up resistor
}

uint32_t HW_PinRead(in_pin_t pin) {
  GPIOA_Type* port = input_pinmap[pin].port;
  uint32_t mask = input_pinmap[pin].mask;
  return (port->DATA & mask) ? 1U : 0U;
}

void HW_OutPinInit(out_pin_t pin) {
  GPIOA_Type* port = output_pinmap[pin].port;
  uint32_t mask = output_pinmap[pin].mask;
  port->DIR |= mask; // set as output
  port->DEN |= mask; // digital enable
}

void HW_PinSet(out_pin_t pin) {
  output_pinmap[pin].port->DATA |= output_pinmap[pin].mask;
}

void HW_PinClear(out_pin_t pin) {
  output_pinmap[pin].port->DATA &= ~output_pinmap[pin].mask;
}

void HW_PinToggle(out_pin_t pin) {
  output_pinmap[pin].port->DATA ^= output_pinmap[pin].mask;
}
