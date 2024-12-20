
#include "Shift_Task.h"
#include "DBUS_Task.h"
#include "LED.h"

shift_coefficient_t shift_coefficient;
uint16_t shift_tim;
uint8_t s1_time;
uint8_t last_s1;

void Shift_Task_Init()
{
    shift_coefficient.if_fast = true;
    shift_coefficient.chassis = 10;
    shift_coefficient.lift = 1.5;
    shift_coefficient.gyro = 0.004;
    shift_coefficient.pitch = 0.1;
    last_s1 = 3;
}//初始化为快速模式

void Shift_Task()
{
    if(shift_tim >= 500)
    {
        shift_tim = 0;
        s1_time = 0;
    }
    else
    {
        if(s1_time != 0)
        {
            shift_tim++;
        }
        if(last_s1 != RC_CtrlData.rc.s1)
        {
            last_s1 = RC_CtrlData.rc.s1;
            s1_time++;
        }
        if(s1_time >= 7)
        {
            if(shift_coefficient.if_fast)
            {
                shift_coefficient.if_fast = false;
                shift_coefficient.chassis = 0.5;
                shift_coefficient.lift = 0.5;
                shift_coefficient.gyro = 0.0003;
                shift_coefficient.pitch = 0.1;
            }//切换为慢速
            else
            {
                shift_coefficient.if_fast = true;
                shift_coefficient.chassis = 10;
                shift_coefficient.lift = 1.5;
                shift_coefficient.gyro = 0.004;
                shift_coefficient.pitch = 0.1;
            }//切换为快速
            s1_time = 0;
        }//要改灵敏度就在这里和init里改数值
    }
}