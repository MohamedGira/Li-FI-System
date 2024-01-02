#include "inc/tm4c123gh6pm.h"
#include "ultrasonic_driver.h"
#include <stdbool.h>
#include <stdint.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "bluetooth_driver.h"
#include "../delay_utils.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define PORTF_BUTTON0 GPIO_PIN_0
#define PORTF_LED_RED GPIO_PIN_1
#define PORTF_LED_BLUE GPIO_PIN_2
#define PORTF_LED_GREEN GPIO_PIN_3
#define PORTB_ULTRASONIC_TRIGGER GPIO_PIN_7
#define PORTB_ULTRASONIC_ECHO GPIO_PIN_6
#include "bluetooth_driver.h"
/* This function captures consecutive rising and falling edges of a periodic signal */
/* from Timer Block 0 Timer A and returns the time difference (the period of the signal). */

/*
Interfacing:
we will use portB for the ultrasonic,
we will connect GPIO_PIN_7 as a trigger,
and GPIO_PIN_6 as an echo
*/
void ultrasonic_init()
{
    // initialize Port b for ultrasonic sensor use

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        ;
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, PORTB_ULTRASONIC_TRIGGER);
    GPIOPinWrite(GPIO_PORTB_BASE, PORTB_ULTRASONIC_TRIGGER, 0x0);

    GPIO_PORTB_DIR_R &= ~PORTB_ULTRASONIC_ECHO;
    GPIO_PORTB_DEN_R |= PORTB_ULTRASONIC_ECHO;
    GPIO_PORTB_AFSEL_R |= PORTB_ULTRASONIC_ECHO;
    GPIO_PORTB_PCTL_R &= ~0x0F000000;
    GPIO_PORTB_PCTL_R |= 0x07000000;
}

uint32_t Measure_distance(void)
{
    int lastEdge, thisEdge;
    /* Given 10us trigger pulse */

    GPIO_PORTB_DATA_R &= ~(PORTB_ULTRASONIC_TRIGGER); /* make trigger  pin low */
    delay_microSecond(10);
    GPIO_PORTB_DATA_R |= (PORTB_ULTRASONIC_TRIGGER); /* make trigger  pin high */
    delay_microSecond(10);
    GPIO_PORTB_DATA_R &= ~(PORTB_ULTRASONIC_TRIGGER); /* make trigger  pin low */

    TIMER0_ICR_R = 4; /* clear timer0A capture flag */
    while ((TIMER0_RIS_R & 4) == 0)
        ; /* wait till captured */

    lastEdge = TIMER0_TAR_R; /* save the timestamp */

    /* detect falling edge */
    TIMER0_ICR_R = 4; /* clear timer0A capture flag */
    while ((TIMER0_RIS_R & 4) == 0)
        ;                                /* wait till captured */
    thisEdge = TIMER0_TAR_R;             /* save the timestamp */
    return (thisEdge - lastEdge) / 1000; /* return the time difference */
}

/* Timer0A initialization function */
/* Initialize Timer0A in input-edge time mode with up-count mode */
void Timer0ACapture_init(void)
{

    SYSCTL_RCGCTIMER_R |= 0x01; /* enable clock to Timer Block 0 */

    TIMER0_CTL_R &= ~1;   /* disable timer0A during setup */
    TIMER0_CFG_R = 4;     /* 16-bit timer mode */
    TIMER0_TAMR_R = 0x17; /* up-count, edge-time, capture mode */
    TIMER0_CTL_R |= 0x0C; /* capture the rising edge */
    TIMER0_CTL_R |= 0x01; /* enable timer0A */
}

void ultrasonic_start()
{
    ultrasonic_init();
    Timer0ACapture_init();
}
