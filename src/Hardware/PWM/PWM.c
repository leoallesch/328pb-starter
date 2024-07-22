#include "PWM.h"

static void Timer0_Init()
{
  TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
  OCR0A = 0;

  TCCR0B |= (1 << CS00);
}

static void SetDutyCycle(I_PWM_t *interface, PWM_DutyCycle_t duty)
{
  (void)interface;
  OCR0A = (duty / 100) * 255;
}

static void SetFrequency(I_PWM_t *interface, PWM_Freq_t frequency)
{
  (void)interface;
  (void)frequency;
}

static const I_PWM_Api_t api = {SetDutyCycle, SetFrequency};

void PWM_Init(PWM_t *self, IOPort_t port, IOPin_t pin)
{
  self->port = port;
  self->pin = pin;
  self->interface.api = &api;

  *(port - 1) |= (1 << pin);

  Timer0_Init();
}