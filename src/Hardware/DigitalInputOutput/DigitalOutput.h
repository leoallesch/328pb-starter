#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

#include "I_DigitalOutput.h"
#include "Typedefs_IO.h"

typedef struct
{
  I_DigitalOutput_t interface;

  IOPort_t port;
  IOPin_t pin;
} DigitalOutput_t;

void DigitalOutput_Init(DigitalOutput_t *self, IOPort_t port, IOPin_t pin);

#endif