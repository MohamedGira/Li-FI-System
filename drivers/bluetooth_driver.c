#include "inc/tm4c123gh6pm.h"
#include "bluetooth_driver.h"

void HC05_init(void)
{
    // Enable clock to UART5 and port E using the standard registers from tm4c123gh6pm.h
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;

    // UART5 initialization
    UART5_CTL_R = 0;
    UART5_IBRD_R = 104;  // Set integer part of the baud rate divisor (9600 baud rate)
    UART5_FBRD_R = 11;   // Set fractional part of the baud rate divisor (9600 baud rate)
    UART5_CC_R = 0;      // Use system clock
    UART5_LCRH_R = 0x60; // 8-bit data, 1 stop bit, FIFO enable
    UART5_CTL_R = 0x301; // Enable UART5 module, Rx and Tx

    // Configure PE4 and PE5 for UART functionality

    GPIO_PORTE_DEN_R |= 0x30;   // Enable digital I/O on PE4 and PE5
    GPIO_PORTE_AFSEL_R |= 0x30; // Enable alternate function on PE4 and PE5
    GPIO_PORTE_AMSEL_R |= 0;
    GPIO_PORTE_PCTL_R |= 0x00110000; // Configure PE4 and PE5 for UART5
}

void bluetooth_init_inturrpts(void (*handler)())
{
    // Enable UART interrupt for receive
    UARTIntRegister(UART_MODULE_BASE, handler);
    UARTIntEnable(UART_MODULE_BASE, UART_INT_RX);
    IntEnable(INT_UART5);
}

char Bluetooth_Read(void)
{
    char data;
    while (UART5_FR_R & UART_FR_RXFE)
        ;              // Wait until Rx buffer is not full
    data = UART5_DR_R; // Read data from the UART5 data register
    return (unsigned char)data;
}

void Bluetooth_Write(unsigned char data)
{
    while ((UART5_FR_R & (1 << 5)) != 0)
        ;              /* wait until Tx buffer not full */
    UART5_DR_R = data; /* before giving it another byte */
}

void Bluetooth_Write_String(char *str)
{
    while (*str)
    {
        Bluetooth_Write(*(str++));
    }
}

void Bluetooth_test()
{
    HC05_init();
    Bluetooth_Write_String("hello world");
}
