/** fmt_transport.h
 * Common interface for the firment transport layers (spi, uart, etc.)
 
 * Dependency graph:
 * firment-base -> fmt_transport.h <-implements- firment-transport_xxx
 *
 * These are function pointers so:
 * 1. Several communication transports (spi, uart, can...) may implement this interface.
 * 2. Unit tests can cover fmt_comms.c using spys at the transport layer.
 * 3. Unit tests can compile all transports and switch which one is active.
 */
#ifndef FMT_TRANSPORT_H
#define FMT_TRANSPORT_H

#include <stdint.h>
#include <stdbool.h>

typedef volatile struct _transportErrCount
{
  uint16_t dataLost;
  uint16_t unhandledArmEvent;
  uint16_t armRxError;
  uint8_t modeFault;
} transportErrCount_t;

typedef void (*rxCallback_t)(const uint8_t * const rxData);
typedef bool (*txCallback_t)(uint8_t * const txBuffer);

// Define callback types.
typedef bool (*fmt_linkTransport_t)(txCallback_t pullTxPacket, rxCallback_t pushRxPacket);
typedef void (*fmt_startTxChain_t)(void);
typedef const transportErrCount_t *(*fmt_getTransportErrCount_t)(void);

// Declare function pointers.  Transport implementation will define these.
extern fmt_startTxChain_t fmt_startTxChain;
extern fmt_linkTransport_t fmt_linkTransport;
extern fmt_getTransportErrCount_t fmt_getTransportErrCount;

bool fmt_initTransport(void);

#endif // FMT_TRANSPORT_H
