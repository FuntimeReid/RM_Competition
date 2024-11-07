
#include "Outage_Task.h"

#include "LED.h"

uint16_t outage_tim;
bool if_start;
bool if_work;

void Outage_Task_Init(void)
{
    outage_tim = 0;
    if_start = false;
}

void Outage_Task(void)
{
    outage_tim++;
    if(outage_tim <= 150 && if_start)
    {
        if_work = true;
    }
    else
    {
        if_work = false;
    }//遥控器断开150ms或遥控器第一次打开前都不工作
}
