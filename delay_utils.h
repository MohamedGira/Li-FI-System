#ifndef DELAY_UTILS_H
#define DELAY_UTILS_H
#include <stdint.h>

#include "inc/tm4c123gh6pm.h"

void delay_microSecond(uint64_t time);
void delay_ms(uint64_t milliseconds);
#endif DELAY_UTILS_H
