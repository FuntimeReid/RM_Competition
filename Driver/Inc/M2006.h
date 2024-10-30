
#ifndef M2006_H
#define M2006_H

#include "stm32f4xx_hal.h"

#define Get_M2006_Measure(ptr, data) \
{ \
(ptr)->last_ecd = (ptr)->ecd; \
(ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]); \
(ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); \
(ptr)->torque = (uint16_t)((data)[4] << 8 | (data)[5]); \
}

typedef struct
{
    uint16_t last_ecd;
    int32_t speed_rpm;
    int32_t torque;
    uint16_t ecd;
}M2006_measure_t;

typedef struct
{
    int32_t target_torque;
    int32_t target_speed;
    int32_t current;
}M2006_state_t;

extern M2006_measure_t M2006_measure[2];
extern M2006_state_t M2006_state[2];

#endif //M2006_H
