#ifndef TIMING_DRIVER_H
#define TIMING_DRIVER_H
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

/*
use along with analog inputs (fume,light) to fire corresponding actions
*/
void initTimer2();
void Timer2InturrptHandler();
void set_timer2_int_handler_and_enable(void (*handler)());
void clear_timer2_inturrput();
#endif // TIMING_DRIVER_H