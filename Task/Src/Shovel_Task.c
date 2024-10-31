
#include "Shovel_Task.h"
#include "tim.h"

void Shovel_Task_Init()
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
}

void Shovel_Task()
{
    switch (RC_CtrlData.rc.s2)
    {
        case 1:
        {
            Shovel_Ctrl(1000);
        }
        case 2:
        {
            Shovel_Ctrl(-1000);
            break;
        }
        default:
        {
            break;
        }
    }
}

void Shovel_Ctrl(int16_t compare)
{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, compare);
}
