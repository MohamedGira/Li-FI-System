#include "hallswitch_driver.h"
void hallswitch_inturrpt_handler()
{
    delay_ms(200); // for signal to stableize
    if (GPIOPinRead(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN))
    {
        send_door_opened();
    }
    else
    {
        send_door_closed();
    }

    GPIOIntClear(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN);
}

void hallswitch_init()
{
    // initialize portf leds as output
    SysCtlPeripheralEnable(HALL_INPUT_PREHIPHERAL);
    while (!SysCtlPeripheralReady(HALL_INPUT_PREHIPHERAL))
        ;
    GPIOPinWrite(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN, 0x0);
    GPIOPinTypeGPIOInput(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN);
    GPIOPadConfigSet(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
void hallswitch_inturrpt_init()
{
    // Enable interrupt for Port E
    GPIOIntDisable(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN);
    GPIOIntRegister(HALL_INPUT_PORT_BASE, hallswitch_inturrpt_handler);
    GPIOIntTypeSet(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN, GPIO_RISING_EDGE);
}
void start_hallswitch()
{
    hallswitch_init();
    hallswitch_inturrpt_init();
    enable_hallswitch();
}
void disable_hallswitch()
{
    GPIOIntDisable(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN);
}
void enable_hallswitch()
{
    GPIOIntEnable(HALL_INPUT_PORT_BASE, HALL_INPUT_PIN);
}