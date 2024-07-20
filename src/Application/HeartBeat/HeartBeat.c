#include "HeartBeat.h"

#include <avr/io.h>
#include <stddef.h>

static void Blink(void *context)
{
  (void)context;
  PORTB ^= (1 << PB5);
}

void HeartBeat_Init(HeartBeat_t *self, TimerGroup_t *timerGroup)
{
  self->timerGroup = timerGroup;
  DDRB = (1 << PB5);

  TimerGroup_StartPeriodic(timerGroup, &self->timer, 1000, Blink, NULL);
}