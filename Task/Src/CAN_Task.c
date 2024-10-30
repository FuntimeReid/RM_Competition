
#include "CAN_Task.h"
#include "ChassisCtrl.h"
#include "main.h"
#include "can.h"

uint8_t can_send_data[8];

void CAN_Task()
{
    switch (CAN_rx_header.StdId)
    {
        case 0x203:
        {
            Get_Motor_Measure(&motor_chassis[0],CAN_rx_data);
            break;
        }
        case 0x202:
        {
            Get_Motor_Measure(&motor_chassis[2],CAN_rx_data);
            break;
        }
    }
    CAN_SendMessage(&hcan1,0x200,0,0,1000,0);
}

void CAN_SendMessage(CAN_HandleTypeDef *hcan,uint32_t StdId,int16_t message1,int16_t message2,int16_t message3,int16_t message4)
{
    uint32_t send_mail_box;
    CAN_TxHeaderTypeDef txHeader;

    txHeader.StdId = StdId;
    txHeader.IDE = CAN_ID_STD;
    txHeader.DLC = 0x08;
    txHeader.ExtId = 0x00;
    txHeader.RTR = CAN_RTR_DATA;

    can_send_data[0] = message1 >> 8;
    can_send_data[1] = message1;
    can_send_data[2] = message2 >> 8;
    can_send_data[3] = message2;
    can_send_data[4] = message3 >> 8;
    can_send_data[5] = message3;
    can_send_data[6] = message4 >> 8;
    can_send_data[7] = message4;

    HAL_CAN_AddTxMessage(hcan, &txHeader, can_send_data, &send_mail_box);
}