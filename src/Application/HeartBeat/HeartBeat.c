#include "HeartBeat.h"
#include <avr/io.h>

static void Blink(void *context)
{
  HeartBeat_t *self = context;
  static bool state;
  DigitalOutput_Write(&self->led.interface, state = !state);
}

void HeartBeat_Init(HeartBeat_t *self, TimerGroup_t *timerGroup)
{
  self->timerGroup = timerGroup;
  DigitalOutput_Init(&self->led, &PORTB, PB5);
  TimerGroup_StartPeriodic(timerGroup, &self->timer, 1000, Blink, self);
}