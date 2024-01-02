#include "control.h"
#include "delay_utils.h"
#include "drivers/hallswitch_driver.h"
int started = 1;
int sending = 0;

#define STOP_SIGNAL_DURATION 100
#define FIRE_SIGNAL_DURATION 200
#define INTRUDER_SIGNAL_DURATION 300
#define GOODNIGHT_SIGNAL_DURATION 400
#define GOODMORNING_SIGNAL_DURATION 500
#define DOOR_OPENED_SIGNAL_DURATION 600
#define DOOR_CLOSED_SIGNAL_DURATION 700


void send_ir_in_millis(int n)
{
    /*sends a high signal to PB2 for n millis*/
    /*disable for 30 ms to prevent interference*/
    GPIOPinWrite(GPIO_PORTB_BASE, IR_PIN, 0x0);
    delay_ms(30);
    GPIOPinWrite(GPIO_PORTB_BASE, IR_PIN, IR_PIN);
    delay_ms(n);
    GPIOPinWrite(GPIO_PORTB_BASE, IR_PIN, 0x0);
}

void BluetoothIntHandler(void)
{
    // handles incoming requests from the mobile app via bluetooth
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART_MODULE_BASE, true);
    UARTIntClear(UART_MODULE_BASE, ui32Status);

    while (UARTCharsAvail(UART_MODULE_BASE))
    {
        char receivedChar = UARTCharGetNonBlocking(UART_MODULE_BASE);
        if (receivedChar == 'r')
        {
            delay_ms(5000);
            send_stop();
        }
        else if (receivedChar == '1')
        {
            system_start();
        }
        else if (receivedChar == '0')
        {
            system_stop();
        }
    }
}

void control_inturrput_Handler()
{

    if (GPIOPinRead(GPIO_PORTB_BASE, START_PIN) == 0x0 && !started)
    {
        system_start();
        Bluetooth_Write_String("system started");
    }
    else if (GPIOPinRead(GPIO_PORTB_BASE, STOP_PIN) == 0x0 && started)
    {
        system_stop();
        Bluetooth_Write_String("system stopped");
    };
    GPIOIntClear(GPIO_PORTB_BASE, START_PIN | STOP_PIN);
}

void control_init_interrupts()
{
    // Enable interrupt for Port B (Control port)
    GPIOIntDisable(GPIO_PORTB_BASE, START_PIN | STOP_PIN);
    GPIOIntRegister(GPIO_PORTB_BASE, control_inturrput_Handler);
    GPIOIntTypeSet(GPIO_PORTB_BASE, START_PIN | STOP_PIN, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTB_BASE, START_PIN | STOP_PIN);
    bluetooth_init_inturrpts(BluetoothIntHandler);
}
void mute_inturrpt_handler()
{
    delay_ms(5000);
    send_stop();
    clear_port_f_inturrpt();
}

void control_init()
{
    // initialize portb buttons as output
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        ;
    GPIOPinWrite(GPIO_PORTB_BASE, HALL_INPUT_PIN, 0x0);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, START_PIN | STOP_PIN);
    GPIOPadConfigSet(GPIO_PORTB_BASE, HALL_INPUT_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    // initialize ir led pin
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, IR_PIN);
    control_init_interrupts();
    PORTF_INIT();
    PORTF_initInterrupts(mute_inturrpt_handler);
}

void send_stop()
{
    sending = 1;

    Bluetooth_Write('s');
    send_ir_in_millis(STOP_SIGNAL_DURATION);
    sending = 0;
}
void send_fire()
{
    sending = 1;
    Bluetooth_Write('f');
    send_ir_in_millis(FIRE_SIGNAL_DURATION);
    sending = 0;
}
void send_intruder()
{
    sending = 1;
    Bluetooth_Write('i');
    send_ir_in_millis(INTRUDER_SIGNAL_DURATION);
    sending = 0;
}
void send_goodnight()
{
    sending = 1;
    Bluetooth_Write('n');
    send_ir_in_millis(GOODNIGHT_SIGNAL_DURATION);
    sending = 0;
}
void send_goodmorning()
{
    sending = 1;
    Bluetooth_Write('m');
    send_ir_in_millis(GOODMORNING_SIGNAL_DURATION);
    sending = 0;
}
void send_door_opened()
{
    sending = 1;
    Bluetooth_Write('o');
    send_ir_in_millis(DOOR_OPENED_SIGNAL_DURATION);
    sending = 0;
}
void send_door_closed()
{
    sending = 1;
    Bluetooth_Write('c');
    send_ir_in_millis(DOOR_CLOSED_SIGNAL_DURATION);
    sending = 0;
}
