#include "LED.h"
#include <avr/io.h>

static void Update(void *context, const void *args)
{
  LED_t *self = context;
  const bool *state = args;
  DigitalOutput_Write(&self->led.interface, *state);
}

void LED_Init(LED_t *self, IOPort_t port, IOPin_t pin, I_Event_t *triggerEvent)
{
  DigitalOutput_Init(&self->led, port, pin);

  EventSubscription_Init(&self->subscription, self, Update);
  Event_Subscribe(triggerEvent, &self->subscription);
}