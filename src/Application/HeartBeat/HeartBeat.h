#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "Timer.h"

typedef struct
{
  TimerGroup_t *timerGroup;
  Timer_t timer;
} HeartBeat_t;

void HeartBeat_Init(HeartBeat_t *self, TimerGroup_t *timerGroup);

#endif