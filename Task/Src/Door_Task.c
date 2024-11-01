
#include "Door_Task.h"

#include "cmsis_os2.h"
#include "tim.h"

uint32_t door_tim;

void Door_Task_Init()
{
    Tim8_sConfigOC2.OCMode = TIM_OCMODE_PWM1;
    Tim8_sConfigOC2.Pulse = 0;
    Tim8_sConfigOC2.OCPolarity = TIM_OCPOLARITY_HIGH;
    Tim8_sConfigOC2.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    Tim8_sConfigOC2.OCFastMode = TIM_OCFAST_DISABLE;
    Tim8_sConfigOC2.OCIdleState = TIM_OCIDLESTATE_RESET;
    Tim8_sConfigOC2.OCNIdleState = TIM_OCNIDLESTATE_RESET;
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
            Door_Pulse_Setting(0);
            door_tim = 0;
            break;
        }
    }
}

void Door_Ctrl(int16_t pulse)
{
    if(door_tim > 500)
    {
      Door_Pulse_Setting(pulse);
    }
    else
    {
        door_tim++;
    }
}

void Door_Pulse_Setting(int16_t pulse)
{
    Tim8_sConfigOC2.Pulse = pulse;
    HAL_TIM_PWM_ConfigChannel(&htim8, &Tim8_sConfigOC2, TIM_CHANNEL_2);
}