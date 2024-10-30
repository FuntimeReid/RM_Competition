
#include "DBUS_Task.h"
#include "usart.h"

uint8_t sbus_rx_buffer[RC_FRAME_LENGTH];//DMA接收
CtrlData RC_CtrlData;//遥控器解算后数据
uint16_t outage_tim;

void DBUS_Init()
{
    HAL_UART_Receive_DMA(&huart3, sbus_rx_buffer, RC_FRAME_LENGTH);
    outage_tim = 0;
}

void DBUS_Task()
{
    outage_tim = 0;
}

void RemoteDataProcess(uint8_t *pData)
{
    if(pData == NULL)
    {
        return;
    }

    RC_CtrlData.rc.ch0 = (((int16_t)pData[0]) | ((int16_t)pData[1] << 8) & 0x07FF);
    RC_CtrlData.rc.ch1 = (((int16_t)pData[1]) >> 3 | ((int16_t)pData[2] << 5)) & 0x07FF;
    RC_CtrlData.rc.ch2 = (((int16_t)pData[2]) >> 6 | ((int16_t)pData[3] << 2 | ((int16_t)pData[4] << 10))) & 0x07FF;
    RC_CtrlData.rc.ch3 = (((int16_t)pData[4]) >> 1 | ((int16_t)pData[5] << 7)) & 0x07FF;
    RC_CtrlData.rc.ch0 -= 1024;
    RC_CtrlData.rc.ch1 -= 1024;
    RC_CtrlData.rc.ch2 -= 1024;
    RC_CtrlData.rc.ch3 -= 1024;

    RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
    RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);

    RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7]) << 8;
    RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9]) << 8;
    RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11]) << 8;

    RC_CtrlData.mouse.press_l = pData[12];
    RC_CtrlData.mouse.press_r = pData[13];

    RC_CtrlData.key.v = ((int16_t)pData[14]);

    RC_CtrlData.rc.ch4 = (((int16_t)pData[16]) | ((int16_t)pData[17]) << 8) & 0x07FF;
    RC_CtrlData.rc.ch4 -= 1024;
}
