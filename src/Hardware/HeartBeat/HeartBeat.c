#include "HeartBeat.h"

static void Blink(void *context)
{
  HeartBeat_t *self = context;
  static bool state;
  DigitalOutput_Write(&self->led.interface, state = !state);
}

void HeartBeat_Init(HeartBeat_t *self, TimerGroup_t *timerGroup, IOPort_t port, IOPin_t pin, TimerTicks_t period)
{
  self->timerGroup = timerGroup;
  DigitalOutput_Init(&self->led, port, pin);
  TimerGroup_StartPeriodic(timerGroup, &self->timer, period, Blink, self);
}