
#include "Door_Task.h"

#include "cmsis_os2.h"
#include "tim.h"

uint8_t corotation;
uint8_t door_tim;

void Door_Task_Init()
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    door_tim = 0;
}

void Door_Task()
{
    if(RC_CtrlData.rc.s1 = 1)
    {
        if(door_tim > 500)
        {
            __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, 1000 * corotation);
        }
        else
        {
            door_tim++;
        }
    }
    else
    {
        door_tim = 0;
    }
}

