#include "Application.h"
#include "TimeSource.h"
#include "PWM.h"

static TimerGroup_t timerGroup;
static Application_t application;
static PWM_t pwm;

int main(void)
{
  TimerGroup_Init(&timerGroup, TimeSource_Init());
  Application_Init(&application, &timerGroup);
  PWM_Init(&pwm, &PORTD, PB6);
  PWM_SetDutyCycle(&pwm.interface, 50);

  while (1)
  {
    TimerGroup_Run(&timerGroup);
  }

  return 0;
}