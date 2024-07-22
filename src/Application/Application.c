#include "Application.h"
#include "UART.h"

void Application_Init(Application_t *self, TimerGroup_t *timerGroup)
{
  self->timerGroup = timerGroup;

  Button_Init(&self->button, timerGroup, &PIND, PD0);
  HeartBeat_Init(&self->heartbeat, timerGroup, &PORTB, PB5, 1000);
  LED_Init(&self->led, &PORTD, PD1, Button_OnChange(&self->button));
}