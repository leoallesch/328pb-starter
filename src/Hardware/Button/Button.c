#include "Button.h"
#include <stdbool.h>

void Poll(void *context)
{
  Button_t *self = context;
  bool state = DigitalInput_Read(&self->input.interface);

  if (self->prevState != state)
  {
    self->prevState = state;
    Event_Publish(&self->onChange, &state);
  }
}

I_Event_t *Button_OnChange(Button_t *button)
{
  return &button->onChange.interface;
}

void Button_Init(Button_t *self, TimerGroup_t *timerGroup, IOPort_t port, IOPin_t pin)
{
  self->timerGroup = timerGroup;
  self->prevState = false;

  DigitalInput_Init(&self->input, port, pin);

  Event_Init(&self->onChange);

  TimerGroup_StartPeriodic(timerGroup, &self->timer, 10, Poll, self);
}