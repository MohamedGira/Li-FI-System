#ifndef SYSTEM_H
#define SYSTEM_H
/*
purpuose:
    starts everything.
    ldr init
    fume init
    timing init
    bluetooth init
    ultrasonic init
    hall switch init

system_init():
    initilize control (start/stop buttons)
    initializes fume,ldr,bluetooth, hallswitch, and ultrasonic
    initializes timer
*/
#include <stdint.h>
#include "control.h"
#include "drivers/fume_driver.h"
#include "drivers/ldr_driver.h"
#include "drivers/ultrasonic_driver.h"
#include "drivers/bluetooth_driver.h"
#include "drivers/hallswitch_driver.h"
#include "drivers/timing_driver.h"
#include "drivers/PORTF_driver.h"
extern int started;
extern int sending;
void timer_ISR(void);
void system_init();
void system_start();
void system_stop();
#endif // __SYSTEM_H