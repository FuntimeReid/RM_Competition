
#ifndef GM6020CTRL_H
#define GM6020CTRL_H

#include "stm32f4xx_hal.h"

typedef struct
{
    uint16_t ecd;
    int16_t speed_rpm;
    int16_t given_current;
    uint16_t temperature;
    uint16_t last_ecd;
}GM6020_measure_t;

typedef struct
{
    int16_t target_velocity;
    int32_t current;
}GM6020_state_t;

#define Get_GM6020_Measure(ptr, data) \
{ \
(ptr)->last_ecd =  (ptr)->ecd;\
(ptr)->ecd =  (uint16_t)((data)[0] << 8 | (data)[1]);\
(ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); \
(ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
(ptr)->temperature = (data)[6]; \
}

extern GM6020_measure_t GM6020_measure;
extern GM6020_state_t GM6020_state;

#endif //GM6020CTRL_H
