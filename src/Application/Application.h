#ifndef APPLICATION_H
#define APPLICATION_H

#include "Timer.h"
#include "Heartbeat.h"
#include "Button.h"
#include "LED.h"

typedef struct
{
  TimerGroup_t *timerGroup;
  HeartBeat_t heartbeat;
  Button_t button;
  LED_t led;
} Application_t;

void Application_Init(Application_t *self, TimerGroup_t *timerGroup);

#endif