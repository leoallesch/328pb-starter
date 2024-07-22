#ifndef PWM_H
#define PWM_H

#include "I_PWM.h"
#include "Typedefs_IO.h"

typedef struct
{
  I_PWM_t interface;

  IOPort_t port;
  IOPin_t pin;
} PWM_t;

void PWM_Init(PWM_t *self, IOPort_t port, IOPin_t pin);

#endif