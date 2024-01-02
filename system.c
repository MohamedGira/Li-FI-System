
#include "system.h"
int is_morning = 0;
extern int started;
void timer_ISR(void)
{
  if (!sending)
  {
    uint32_t distance = Measure_distance();
    uint32_t light_value = Ldr_value();
    uint32_t fume_value = Fume_value();
    char mesg[100];

    if (fume_value > 1500)
    {
      send_fire();
    }
    else if (distance < 15)
    {
      send_intruder();
    }
    else if (light_value < 1200 && !is_morning)
    { // sun is up
      send_goodmorning();
      is_morning = 1;
    }
    else if (light_value > 2000 && is_morning)
    { // sun is down
      send_goodnight();
      is_morning = 0;
    }
    else
    {
      sprintf(mesg, "ValsDistance is: %d\nFume Value is:%d\nLight Intensity is: %d", distance, fume_value, light_value); /*convert float type distance data into string */
      Bluetooth_Write_String(mesg);
    }
  }
  clear_timer2_inturrput();
}
void single_isr()
{
  // for testing purposes
  if (started)
  {
    uint32_t fume_value = Fume_value();
    char mesg[70];                             /* string format of distance value */
    sprintf(mesg, "\r\n,fume=%d", fume_value); /*convert float type distance data into string */
    Bluetooth_Write_String(mesg);
    clear_timer2_inturrput();
  }
}
void system_init()
{

  HC05_init();
  Ldr_Init();
  Fume_Init();
  ultrasonic_start();
  start_hallswitch();
  control_init();
  OpenLEDs();
  set_timer2_int_handler_and_enable(timer_ISR);
  started = 1;
  Bluetooth_Write_String("System Initialized!\n");

}

void system_start()
{

  started = 1;
  OpenLEDs();
  enable_hallswitch();
  enable_timer2_inturrput();
  Bluetooth_Write_String("System started!\n");
}
void system_stop()
{

  started = 0;
  send_stop();
  CloseLEDs();
  disable_hallswitch();
  send_stop();
  disable_timer2_inturrput();
  Bluetooth_Write_String("System stopped!\n");
  
}
