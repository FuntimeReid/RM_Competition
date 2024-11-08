
#ifndef SLIDE_TASK_H
#define SLIDE_TASK_H

#include "stm32f4xx_hal.h"
#include "tim.h"

#define MOTOR1_GPIO_1 GPIOE
#define MOTOR1_GPIO_2 GPIOE
#define MOTOR2_GPIO_1 GPIOE
#define MOTOR2_GPIO_2 GPIOE

#define MOTOR1_PIN_1 GPIO_PIN_9
#define MOTOR1_PIN_2 GPIO_PIN_11
#define MOTOR2_PIN_1 GPIO_PIN_13
#define MOTOR2_PIN_2 GPIO_PIN_14

void Slide_Task_Init();

void Slide_Task();

#endif //SLIDE_TASK_H
