
#include "CAN_Task.h"
#include "ChassisCtrl.h"
#include "main.h"

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
}