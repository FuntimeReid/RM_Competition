
#ifndef DOOR_TASK_H
#define DOOR_TASK_H

#include "stm32f4xx_hal.h"

void Door_Task_Init();

void Door_Task();

void Door_Ctrl(int16_t pulse);

void Door_Pulse_Setting(int16_t pulse);

extern uint32_t door_tim;

#endif //DOOR_TASK_H
