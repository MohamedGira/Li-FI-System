#ifndef __ULTRASONIC_DRIVER
#define __ULTRASONIC_DRIVER
#include <stdint.h>
/*

we will use portB for the ultrasonic,
connect GPIO_PIN_7 PB7 as a trigger,
connect GPIO_PIN_6 PB6 as an echo

explaination:
Timer0ACapture_init:            timers can be used as timers, but they can also be used as event listener, in our case, we use timer0A as an edge detector.
                                this function intilizes timer0 to work as edge capturer

delay_microSecond:              we need accuracy on firing the trigger, so we use timer1A to make a function that waits for N micro seconds.

Measure_distance:               simply, we fire a signal with our trigger, then we start listening to it using this timer, when the echo recieves a signal (low to high), we take the timestamp,
                                when the signal is over (high to low) the timer is triggered again, we take the delta time to get the distance.

PORTB_ULTRASONIC_DRIVER_INIT:   timers are tied to specific ports, in our case, we can tie PB6 to timer 0 using this method

*/
uint32_t Measure_distance(void);
void Timer0ACapture_init(void);
void ultrasonic_init(); // echo orange PB 6 , trigger yellow PB7
void ultrasonic_start();
#endif