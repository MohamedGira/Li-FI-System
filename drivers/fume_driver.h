#ifndef FUME_DRIVER_H
#define FUME_DRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

#define FUME_PORT_BASE GPIO_PORTE_BASE
#define FUME_PIN GPIO_PIN_3
#define FUME_SEQUENCER 1
/*sets PE3, along with adc0 ans sequencer1 for fume sensor*/
void Fume_Init();

uint32_t Fume_value();

#endif // FUME_DRIVER_H
