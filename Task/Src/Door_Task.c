
#include "Door_Task.h"

#include "cmsis_os2.h"
#include "tim.h"

uint8_t door_tim;

void Door_Task_Init()
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    door_tim = 0;
}

void Door_Task()
{
    switch (RC_CtrlData.rc.s1)
    {
        case 1:
        {
            Door_Ctrl(1000);
            break;
        }
        case 2:
        {
            Door_Ctrl(-1000);
            break;
        }
        case 3:
        {
            door_tim = 0;
            break;
        }
    }
}

void Door_Ctrl(int16_t compare)
{
    if(door_tim > 500)
    {
        __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, compare);
    }
    else
    {
        door_tim++;
    }
}

