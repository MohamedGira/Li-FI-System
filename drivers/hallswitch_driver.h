#ifndef HALLSWITCH_DRIVER
#define HALLSWITCH_DRIVER
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h" //remove if unused
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "../control.h"
#include "../delay_utils.h"

#define HALL_INPUT_PIN GPIO_PIN_1
#define HALL_INPUT_PORT_BASE GPIO_PORTE_BASE
#define HALL_INPUT_PREHIPHERAL SYSCTL_PERIPH_GPIOE
/*
Interfacing, hall switch digital output is connected to PE1
function: send door opened notification
*/

void hallswitch_inturrpt_handler();
void hallswitch_init();
void hallswitch_inturrpt_init();
void start_hallswitch();
void disable_hallswitch();
void enable_hallswitch();
#endif // __HALLSWITCH_DRIVER