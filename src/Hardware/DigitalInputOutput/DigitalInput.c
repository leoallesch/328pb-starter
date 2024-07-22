#include "DigitalInput.h"

static bool Read(I_DigitalInput_t *interface)
{
  DigitalInput_t *self = (DigitalInput_t *)interface;
  return *(self->port + self->pin);
}

static const I_DigitalInput_Api_t api = {Read};

void DigitalInput_Init(DigitalInput_t *self, IOPort_t port, IOPin_t pin)
{
  self->port = port;
  self->pin = pin;
  self->interface.api = &api;
}