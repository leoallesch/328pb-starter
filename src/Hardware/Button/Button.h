#ifndef BUTTON_H
#define BUTTON_H

#include "DigitalInput.h"
#include "Event.h"
#include "Timer.h"


typedef struct
{
  TimerGroup_t *timerGroup;
  DigitalInput_t input;
  Event_t onChange;
  Timer_t timer;
  bool prevState;
} Button_t;

void Button_Init(Button_t *self, TimerGroup_t *timerGroup, IOPort_t port, IOPin_t pin);

I_Event_t *Button_OnChange(Button_t *button);

#endif