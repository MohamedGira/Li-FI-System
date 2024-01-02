#ifndef LDR_DRIVER_H
#define LDR_DRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

#define LDR_PORT_BASE GPIO_PORTE_BASE
#define LDR_PIN GPIO_PIN_2
#define LDR_SEQUENCER 2
/*sets PE2, along with adc0 ans sequencer0 for LDR sensor*/
void Ldr_Init();

uint32_t Ldr_value();

#endif // LDR_DRIVER_H
