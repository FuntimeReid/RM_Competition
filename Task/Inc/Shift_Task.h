
#ifndef SHIFT_TASK_H
#define SHIFT_TASK_H

#include "stm32f4xx_hal.h"
#include "stdbool.h"

typedef struct
{
    bool if_fast;
    float chassis;
    float lift;
}shift_coefficient_t;

extern uint16_t shift_tim;
extern uint8_t s1_time;
extern uint8_t last_s1;
extern shift_coefficient_t shift_coefficient;
extern uint32_t shovel_tim;

void Shift_Task_Init();

void Shift_Task();



#endif //SHIFT_TASK_H
