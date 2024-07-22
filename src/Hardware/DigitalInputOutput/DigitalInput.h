#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include "I_DigitalInput.h"
#include "Typedefs_IO.h"

typedef struct
{
  I_DigitalInput_t interface;
  IOPort_t port;
  IOPin_t pin;
} DigitalInput_t;

void DigitalInput_Init(DigitalInput_t *self, IOPort_t port, IOPin_t pin);

#endif