#ifndef LED_H
#define LED_H

#include "DigitalOutput.h"
#include "I_Event.h"
#include "EventSubscription.h"

typedef struct
{
  DigitalOutput_t led;
  EventSubscription_t subscription;
} LED_t;

void LED_Init(LED_t *self, IOPort_t port, IOPin_t pin, I_Event_t *triggerEvent);

#endif