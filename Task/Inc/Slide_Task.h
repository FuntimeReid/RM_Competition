
#ifndef SLIDE_TASK_H
#define SLIDE_TASK_H

#include "stm32f4xx_hal.h"
#include "tim.h"

void Slide_Task_Init();

void Slide_Task();

void Slide_OC1Pulse_Setting(int16_t pulse);

#endif //SLIDE_TASK_H
