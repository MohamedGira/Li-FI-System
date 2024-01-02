// PB2 IRLED
// start Button: PB3 (set global variable 'extern'? to 1, check it in ISRS)
// stop Button:  PB4
// note, default to high, so when button is pressed, it goes low
#ifndef CONTROL_H
#define CONTROL_H
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "delay_utils.h"
#include "drivers/hallswitch_driver.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "drivers/PORTF_driver.h"
#include "drivers/bluetooth_driver.h"
#define IR_PIN GPIO_PIN_2
#define START_PIN GPIO_PIN_3
#define STOP_PIN GPIO_PIN_4

// Declaration of the shared variables
extern int started;
extern int sending;

void control_inturrput_Handler();
void control_init_interrupts();
void control_init();

void send_ir_in_millis();
void send_stop();
void send_fire();
void send_intruder();
void send_goodnight();
void send_goodmorning();
void send_door_opened();
void send_door_closed();
void BluetoothIntHandler();

#endif // CONTROL_H