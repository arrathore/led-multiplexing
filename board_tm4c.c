// HAL implementation for the TM4C development board

#include "hardware.h"
#include "TM4C123.h"

// map logical pins for Port E
typedef struct {
  GPIOA_Type *port;
  uint32_t mask;
} pinmap_t;

static const pinmap_t pinmap[PIN_COUNT] = {
  // Port D
  [PIN_PD0] = { GPIOD, (1U << 0) },
  [PIN_PD1] = { GPIOD, (1U << 1) },
  [PIN_PD2] = { GPIOD, (1U << 2) },
  [PIN_PD3] = { GPIOD, (1U << 3) },
  [PIN_PD6] = { GPIOD, (1U << 6) },

  // Port E
  [PIN_PE0] = { GPIOE, (1U << 0) },
  [PIN_PE1] = { GPIOE, (1U << 1) },
  [PIN_PE2] = { GPIOE, (1U << 2) },
  [PIN_PE3] = { GPIOE, (1U << 3) },
  [PIN_PE4] = { GPIOE, (1U << 4) },
  [PIN_PE5] = { GPIOE, (1U << 5) },
};

void HW_Init(void) {
  // enable clock to Ports E and D and wait until they're on
  SYSCTL->RCGCGPIO |= (1U << 4) | (1U << 3);
  while ((SYSCTL->PRGPIO & ((1U << 3) | (1U << 4))) != ((1U << 3) | (1U << 4)));

  // initialize pins from table
  for (int i = 0; i < PIN_COUNT; i++) HW_PinInit((pin_t)i);
}

void HW_PinInit(pin_t pin) {
  GPIOA_Type* port = pinmap[pin].port;
  uint32_t mask = pinmap[pin].mask;
  port->DIR |= mask; // set as output
  port->DEN |= mask; // digital enable
}

void HW_PinSet(pin_t pin) {
  pinmap[pin].port->DATA |= pinmap[pin].mask;
}

void HW_PinClear(pin_t pin) {
  pinmap[pin].port->DATA &= ~pinmap[pin].mask;
}

void HW_PinToggle(pin_t pin) {
  pinmap[pin].port->DATA ^= pinmap[pin].mask;
}
