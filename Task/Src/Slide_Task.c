
#include "Slide_Task.h"

#include "Outage_Task.h"

void Slide_Task_Init()
{
    HAL_GPIO_WritePin(MOTOR1_GPIO_1, MOTOR1_PIN_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR1_GPIO_2, MOTOR1_PIN_2, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(MOTOR2_GPIO_1, MOTOR2_PIN_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR2_GPIO_2, MOTOR2_PIN_2, GPIO_PIN_RESET);
}

void Slide_Task()
{
    if(if_work)
    {
        if(RC_CtrlData.rc.ch4 > 0)
        {
            HAL_GPIO_WritePin(MOTOR1_GPIO_1, MOTOR1_PIN_1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR1_GPIO_2, MOTOR1_PIN_2, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(MOTOR2_GPIO_1, MOTOR2_PIN_1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR2_GPIO_2, MOTOR2_PIN_2, GPIO_PIN_RESET);
        }
        else if(RC_CtrlData.rc.ch4 < 0)
        {
            HAL_GPIO_WritePin(MOTOR1_GPIO_2, MOTOR1_PIN_2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR1_GPIO_1, MOTOR1_PIN_1, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(MOTOR2_GPIO_1, MOTOR2_PIN_1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR2_GPIO_2, MOTOR2_PIN_2, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(MOTOR1_GPIO_2, MOTOR1_PIN_2, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR1_GPIO_1, MOTOR1_PIN_1, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(MOTOR2_GPIO_1, MOTOR2_PIN_1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR2_GPIO_2, MOTOR2_PIN_2, GPIO_PIN_RESET);
        }
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR1_GPIO_1, MOTOR1_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR1_GPIO_2, MOTOR1_PIN_2, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(MOTOR2_GPIO_1, MOTOR2_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR2_GPIO_2, MOTOR2_PIN_2, GPIO_PIN_RESET);
    }
}

