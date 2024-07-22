#include "UART.h"
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

  UBRR0L = (unsigned char)ubrr;
  UBRR0H = (unsigned)(ubrr >> 8);

  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  UCSR0B |= (1 << RXCIE0);
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

  sei();
}

static void Send(I_UART_t *self, uint8_t byte)
{
  (void)self;
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = byte;

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

I_UART_t *UART_Init(uint32_t baud)
{
  self.api = &api;

  Event_Init(&sendCompleteEvent);
  Event_Init(&receiveEvent);

  UART_Begin(baud);

  return &self;
}

ISR(USART0_RX_vect)
{
  UART_OnReceiveArgs_t args = {(uint8_t)UDR0};
  Event_Publish(&receiveEvent, &args);
}