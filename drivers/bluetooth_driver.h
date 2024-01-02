#ifndef __BLUETOOTH_DRIVER
#define __BLUETOOTH_DRIVER
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "../control.h"

#define UART_MODULE_BASE UART5_BASE

/*
connect TX PE4
connect RX PE5

NOTE: disconnect these pins when u try to connect the blutooth to ur phone.

*/

void HC05_init(void);                     // Initialize UART5 module for HC-05 RED TX PE4 . Brown RX PE5
char Bluetooth_Read(void);                // Read data from Rx5 pin of TM4C123
void Bluetooth_Write(unsigned char data); // Transmit a character to HC-05 over Tx5 pin
void Bluetooth_Write_String(char *str);   // Transmit a string to HC-05 over Tx5 pin
void Bluetooth_test(void);
void bluetooth_init_inturrpts(void (*handler)());

#endif
