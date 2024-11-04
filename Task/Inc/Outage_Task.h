
#ifndef OUTAGE_TASK_H
#define OUTAGE_TASK_H

#include "stm32f4xx_hal.h"
#include "stdbool.h"

extern uint16_t outage_tim;
extern bool if_start;
extern bool if_work;

void Outage_Task_Init(void);

void Outage_Task(void);

#endif //OUTAGE_TASK_H
