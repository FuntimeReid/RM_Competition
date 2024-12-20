
#ifndef CAN_TASK_H
#define CAN_TASK_H

#include "stm32f4xx_hal.h"

extern CAN_RxHeaderTypeDef CAN_rx_header;
extern uint8_t CAN_rx_data[8];

void CAN_Task();

void CAN_SendMessage(CAN_HandleTypeDef *hcan,uint32_t StdId,int16_t message1,int16_t message2,int16_t message3,int16_t message4);

#endif //CAN_TASK_H

