
#ifndef DOOR_TASK_H
#define DOOR_TASK_H

#include "stm32f4xx_hal.h"

void Door_Task_Init();

void Door_Task();

extern uint8_t corotation;
extern uint8_t door_tim;

#endif //DOOR_TASK_H
