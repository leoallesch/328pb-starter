#include "Application.h"

void Application_Init(Application_t *self, TimerGroup_t *timerGroup)
{
  self->timerGroup = timerGroup;

  HeartBeat_Init(&self->heartbeat, timerGroup);
}