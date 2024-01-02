#include "timing_driver.h"
#include "inc/tm4c123gh6pm.h"

void initTimer2()
{

  SYSCTL_RCGCTIMER_R |= (1 << 2);
  ;
  TIMER2_CTL_R = 0;
  TIMER2_CFG_R = 0x04;
  TIMER2_TAMR_R |= 0x02;

  TIMER2_TAILR_R = 64000 - 1;
  TIMER2_TAPR_R = 250 - 1;
  TIMER2_ICR_R |= 0x01;
  /*
      or use tivaware:

      SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
      TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
      TimerLoadSet(TIMER2_BASE, TIMER_A, 64000-1);
      TimerPrescaleSet(TIMER2_BASE,TIMER_A,250-1);
      TimerEnable(TIMER2_BASE, TIMER_A);
   */
}

void set_timer2_int_handler_and_enable(void (*inturrpt_handler)())
{
  /*
  handler must call clear_timer2_inturrput at the end
  */
  initTimer2();
  TimerIntRegister(TIMER2_BASE, TIMER_A, inturrpt_handler);
  TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
  TIMER2_CTL_R |= 0x01;
}

void clear_timer2_inturrput()
{
  TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}

void enable_timer2_inturrput()
{
  TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}
void disable_timer2_inturrput()
{
  TimerIntDisable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}