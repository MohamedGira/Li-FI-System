#ifndef PORTF_DRIVER
#define PORTF_DRIVER
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "PORTF_driver.h"

#define PORTF_BUTTON0 GPIO_PIN_0
#define PORTF_LED_RED GPIO_PIN_1
#define PORTF_LED_BLUE GPIO_PIN_2
#define PORTF_LED_GREEN GPIO_PIN_3
#define PORTF_BUTTON1 GPIO_PIN_4
#define PORTB_HALL_INPUT GPIO_PIN_0

void toggleLEDs();
void CloseLEDs();
void OpenLEDs();
void GPIOF_Handler1();
void PORTF_initInterrupts(void (*handler)());
void PORTF_INIT();
void setup_port_f_sutff_with_toggle_led_inturrupt_when_sw0_or_sw1_pressed();
void clear_port_f_inturrpt();

#endif //__PORTF_DRIVER_H__