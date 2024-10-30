
#ifndef DBUS_TASK_H
#define DBUS_TASK_H

#include "stm32f4xx_hal.h"

typedef struct
{
    struct
    {
        int16_t ch0;
        int16_t ch1;
        int16_t ch2;
        int16_t ch3;
        int16_t s1;
        int16_t s2;
    }rc;

    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;
        uint8_t press_l;
        uint8_t press_r;
    }mouse;

    struct
    {
        int16_t v;
    }key;

    uint16_t resc;
}CtrlData;

void RemoteDataProcess(uint8_t *pData);

void CH_Return_Zero();

void DBUS_Init();

void DBUS_Task();

#endif //DBUS_TASK_H