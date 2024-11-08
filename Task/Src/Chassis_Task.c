
#include "Chassis_Task.h"

#include "ChassisCtrl.h"
#include "DBUS_Task.h"
#include "imu_task.h"
#include "PID.h"
#include "Shift_Task.h"

void Chassis_Task()
{
    if(RC_CtrlData.rc.ch3 > -900)//遥控器有概率第一次烧代码连不通，因为归零导致数值是-1024，但正常不会低于-660，检测避免疯掉
    {
        chassis_target_state[0].target_velocity = RC_CtrlData.rc.ch3 * shift_coefficient.chassis;
        chassis_target_state[1].target_velocity = -RC_CtrlData.rc.ch3 * shift_coefficient.chassis;
    }//遥控器控制底盘前进后退
    if(RC_CtrlData.rc.ch2 > -900)
    {
        yaw_state.target_yaw -= RC_CtrlData.rc.ch2 * shift_coefficient.gyro;
    }//遥控器控制转向
}
