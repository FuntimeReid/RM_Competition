
#ifndef OUTAGE_TASK_H
#define OUTAGE_TASK_H

#include "stm32f4xx_hal.h"

extern uint16_t outage_tim;

void Outage_Task_Init(void);

void Outage_Task(void);

#endif //OUTAGE_TASK_H
