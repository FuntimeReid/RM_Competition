
#include "LED_Task.h"
#include "cmsis_os2.h"
#include "LED.h"
#include "Outage_Task.h"
#include "Shift_Task.h"

void LED_Task_Init(void)
{
    LED_RED();
}

void LED_Task()
{
    if(outage_tim > 100)
    {
        LED_WHITE();
    }
    else if(shift_coefficient.if_fast)
    {
        LED_RED();
    }
    else
    {
        LED_GREEN();
    }
}