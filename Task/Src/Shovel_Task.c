
#include "Shovel_Task.h"
#include "tim.h"

uint32_t shovel_tim;

void Shovel_Task_Init()
{
    sConfigOC1.OCMode = TIM_OCMODE_PWM1;
    sConfigOC1.Pulse = 0;
    sConfigOC1.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC1.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC1.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC1.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC1.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    shovel_tim = 0;
}

void Shovel_Task()
{
    switch (RC_CtrlData.rc.s1)
    {
        case 1:
        {
            Shovel_Ctrl(400);
            break;
        }
        case 2:
        {
            Shovel_Ctrl(200);
            break;
        }
        case 3:
        {
            sConfigOC1.Pulse = 0;
            HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC1, TIM_CHANNEL_1);
            shovel_tim = 0;
            break;
        }
    }
}

void Shovel_Ctrl(int16_t pulse)
{
    if(shovel_tim > 500)
    {
        sConfigOC1.Pulse = pulse;
        HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC1, TIM_CHANNEL_1);
    }
    else
    {
        shovel_tim++;
    }
}
