#include "DigitalOutput.h"

static void Write(I_DigitalOutput_t *interface, bool val)
{
  DigitalOutput_t *self = (DigitalOutput_t *)interface;
  if (val)
  {
    *self->port |= (1 << self->pin);
  }
  else
  {
    *self->port &= ~(1 << self->pin);
  }
}

static const I_DigitalOutput_Api_t api = {Write};

void DigitalOutput_Init(DigitalOutput_t *self, volatile uint8_t *port, uint8_t pin)
{
  self->port = port;
  self->pin = pin;
  self->interface.api = &api;

  *(port - 1) |= (1 << pin);
}