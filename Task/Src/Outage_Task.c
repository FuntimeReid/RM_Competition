
#include "Outage_Task.h"

#include "LED.h"

uint16_t outage_tim;

void Outage_Task_Init(void)
{
    outage_tim = 0;
}

void Outage_Task(void)
{
    outage_tim++;
}
