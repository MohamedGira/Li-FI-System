#include "PORTF_driver.h"

void toggleLEDs()
{
    // Read the current pin states
    uint8_t pinStates = GPIOPinRead(GPIO_PORTF_BASE, PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN);

    // Invert the pin states for toggling
    pinStates ^= PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN;

    // Update the LEDs with the inverted pin states
    GPIOPinWrite(GPIO_PORTF_BASE, PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN, pinStates);
}

void CloseLEDs()
{
    GPIOPinWrite(GPIO_PORTF_BASE, PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN, 0x0);
}
void OpenLEDs()
{
    GPIOPinWrite(GPIO_PORTF_BASE, PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN, PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN);
}
void GPIOF_Handler1()
{
    GPIOIntClear(GPIO_PORTF_BASE, PORTF_BUTTON0 | PORTF_BUTTON1);
    toggleLEDs();
}
void clear_port_f_inturrpt()
{
    GPIOIntClear(GPIO_PORTF_BASE, PORTF_BUTTON0 | PORTF_BUTTON1);
}
void PORTF_initInterrupts(void (*handler)())
{
    // Enable interrupt for Port F
    GPIOIntRegister(GPIO_PORTF_BASE, handler);
    GPIOIntTypeSet(GPIO_PORTF_BASE, PORTF_BUTTON0 | PORTF_BUTTON1, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE, PORTF_BUTTON0 | PORTF_BUTTON1);
    // Enable Port F interrupts in NVIC
    IntEnable(INT_GPIOF);
}

void PORTF_INIT()
{
    // initialize portf leds as output
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN);
    GPIOPinWrite(GPIO_PORTF_BASE, PORTF_LED_RED | PORTF_LED_BLUE | PORTF_LED_GREEN, 0x00);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, PORTF_BUTTON0 | PORTF_BUTTON1);
    GPIOPadConfigSet(GPIO_PORTF_BASE, PORTF_BUTTON0 | PORTF_BUTTON1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

void setup_port_f_sutff_with_sws_send_mute()
{
    PORTF_INIT();
    PORTF_initInterrupts(GPIOF_Handler1);
}
