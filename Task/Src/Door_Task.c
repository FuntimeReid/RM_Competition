
#include "Door_Task.h"

#include "cmsis_os2.h"
#include "tim.h"

uint32_t door_tim;

void Door_Task_Init()
{
    sConfigOC2.OCMode = TIM_OCMODE_PWM1;
    sConfigOC2.Pulse = 0;
    sConfigOC2.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC2.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC2.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC2.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC2.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    door_tim = 0;
}

void Door_Task()
{
    switch (RC_CtrlData.rc.s2)
    {
        case 1:
        {
            Door_Ctrl(400);
            break;
        }
        case 2:
        {
            Door_Ctrl(200);
            break;
        }
        case 3:
        {
            sConfigOC2.Pulse = 0;
            HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC2, TIM_CHANNEL_2);
            door_tim = 0;
            break;
        }
    }
}

void Door_Ctrl(int16_t pulse)
{
    if(door_tim > 500)
    {
        sConfigOC2.Pulse = pulse;
        HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC2, TIM_CHANNEL_2);
    }
    else
    {
        door_tim++;
    }
}

