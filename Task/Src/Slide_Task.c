
#include "Slide_Task.h"

#include "Outage_Task.h"

void Slide_Task_Init()
{
    Tim1_sConfigOC1.OCMode = TIM_OCMODE_PWM1;
    Tim1_sConfigOC1.Pulse = 0;
    Tim1_sConfigOC1.OCPolarity = TIM_OCPOLARITY_HIGH;
    Tim1_sConfigOC1.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    Tim1_sConfigOC1.OCFastMode = TIM_OCFAST_DISABLE;
    Tim1_sConfigOC1.OCIdleState = TIM_OCIDLESTATE_RESET;
    Tim1_sConfigOC1.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
}

void Slide_Task()
{
    if(if_work)
    {
        if(RC_CtrlData.rc.ch4 > 0)
        {
            Slide_OC1Pulse_Setting(RC_CtrlData.rc.ch4 * 2);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
        }
        else if(RC_CtrlData.rc.ch4 < 0)
        {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
            Slide_OC1Pulse_Setting(0);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
            Slide_OC1Pulse_Setting(0);
        }
    }
    else
    {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
        Slide_OC1Pulse_Setting(0);
    }
}

void Slide_OC1Pulse_Setting(int16_t pulse)
{
    Tim1_sConfigOC1.Pulse = pulse;
    HAL_TIM_PWM_ConfigChannel(&htim1, &Tim1_sConfigOC1, TIM_CHANNEL_1);
}
