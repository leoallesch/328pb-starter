#include "Application.h"
#include "UART.h"

void Application_Init(Application_t *self, TimerGroup_t *timerGroup)
{
  self->timerGroup = timerGroup;
  HeartBeat_Init(&self->heartbeat, timerGroup);
}