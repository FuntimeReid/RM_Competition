//
// Created by 73932 on 2024/10/30.
//

#ifndef LED_H
#define LED_H

#include "stm32f4xx_hal.h"

#define LED_R_GPIO_Port GPIOH
#define LED_G_GPIO_Port GPIOH
#define LED_B_GPIO_Port GPIOH
#define LED_R_Pin GPIO_PIN_12
#define LED_G_Pin GPIO_PIN_11
#define LED_B_Pin GPIO_PIN_10

void LED_WHITE(void);
void LED_RED(void);
void LED_GREEN(void);
void LED_BLUE(void);
void LED_OFF(void);

#endif //LED_H

