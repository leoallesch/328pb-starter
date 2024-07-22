#include "UART1.h"
#include "Event.h"
#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>

static I_UART_t self;
static Event_t sendCompleteEvent;
static Event_t receiveEvent;

static void UART_Begin(uint32_t baud)
{
  int ubrr = ((F_CPU / 16 / baud) - 1);

  UBRR1L = (unsigned char)ubrr;
  UBRR1H = (unsigned)(ubrr >> 8);

  UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
  UCSR1B |= (1 << RXCIE1);
  UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10);

  sei();
}

static void Send(I_UART_t *self, uint8_t byte)
{
  (void)self;
  while (!(UCSR1A & (1 << UDRE1)))
    ;
  UDR1 = byte;

  Event_Publish(&sendCompleteEvent, NULL);
}

static I_Event_t *OnSendComplete(I_UART_t *self)
{
  (void)self;
  return &sendCompleteEvent.interface;
}

static I_Event_t *OnReceive(I_UART_t *self)
{
  (void)self;
  return &receiveEvent.interface;
}

static const I_UART_Api_t api = {Send, OnSendComplete, OnReceive};

I_UART_t *UART1_Init(uint32_t baud)
{
  self.api = &api;

  Event_Init(&sendCompleteEvent);
  Event_Init(&receiveEvent);

  UART_Begin(baud);

  return &self;
}

ISR(USART1_RX_vect)
{
  UART_OnReceiveArgs_t args = {(uint8_t)UDR1};
  Event_Publish(&receiveEvent, &args);
}