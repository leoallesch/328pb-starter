#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include "I_DigitalOutput.h"
#include <stdint.h>

typedef struct
{
  I_DigitalOutput_t interface;
  volatile uint8_t *port;
  uint8_t pin;
} DigitalOutput_t;

void DigitalOutput_Init(DigitalOutput_t *self, volatile uint8_t *port, uint8_t pin);

#endif