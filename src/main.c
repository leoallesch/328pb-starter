#include "Application.h"
#include "TimeSource.h"

static TimerGroup_t timerGroup;
static Application_t application;

int main(void)
{
  TimerGroup_Init(&timerGroup, TimeSource_Init());
  Application_Init(&application, &timerGroup);

  while (1)
  {
    TimerGroup_Run(&timerGroup);
  }

  return 0;
}