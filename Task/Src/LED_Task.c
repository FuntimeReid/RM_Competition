
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
    if(!if_work)
    {
        LED_WHITE();
    }//关控亮白灯
    else if(shift_coefficient.if_fast)
    {
        LED_RED();
    }//快速模式亮红灯
    else
    {
        LED_GREEN();
    }//慢速亮绿灯
}