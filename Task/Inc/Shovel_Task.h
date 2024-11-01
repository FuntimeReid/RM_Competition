
#ifndef SHOVEL_TASK_H
#define SHOVEL_TASK_H

#include "stm32f4xx_hal.h"

void Shovel_Task_Init();

void Shovel_Task();

void Shovel_Ctrl(int16_t pulse);

void Shovel_Pulse_Setting(int16_t pulse);

#endif //SHOVEL_TASK_H
