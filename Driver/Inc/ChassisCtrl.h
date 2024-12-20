
#ifndef CHASSISCTRL_H
#define CHASSISCTRL_H

#include "stm32f4xx_hal.h"

#define Get_Motor_Measure(ptr, data) \
{ \
(ptr)->last_ecd = (ptr)->ecd; \
(ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]); \
(ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); \
(ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
(ptr)->temperate = (data)[6]; \
}

typedef struct
{
    uint16_t ecd;
    int16_t speed_rpm;
    int16_t given_current;
    uint8_t temperate;
    int16_t last_ecd;
}motor_measure_t;

typedef struct
{
    int16_t target_velocity;
    int16_t current;
}chassis_target_state_t;

extern motor_measure_t motor_chassis[2];
extern chassis_target_state_t chassis_target_state[2];

#endif //CHASSISCTRL_H
