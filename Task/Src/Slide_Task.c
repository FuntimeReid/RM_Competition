
#include "Slide_Task.h"

#include "Outage_Task.h"

void Slide_Task_Init()
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
}

void Slide_Task()
{
    if(if_work)
    {
        if(RC_CtrlData.rc.ch4 > 0)
        {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
        }
        else if(RC_CtrlData.rc.ch4 < 0)
        {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
        }
    }
    else
    {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
    }
}

