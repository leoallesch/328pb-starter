#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "Timer.h"
#include "DigitalOutput.h"

typedef struct
{
  TimerGroup_t *timerGroup;
  DigitalOutput_t led;
  Timer_t timer;
} HeartBeat_t;

void HeartBeat_Init(HeartBeat_t *self, TimerGroup_t *timerGroup);

#endif