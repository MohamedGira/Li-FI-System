#include "delay_utils.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"

void delay_microSecond(uint64_t microsecs)
{
  SysCtlDelay(5 * microsecs);
}
void delay_ms(uint64_t milliseconds)
{
  SysCtlDelay(5333 * milliseconds);
}