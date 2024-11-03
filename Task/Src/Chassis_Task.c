
#include "Chassis_Task.h"

#include "ChassisCtrl.h"
#include "DBUS_Task.h"
#include "imu_task.h"
#include "PID.h"
#include "Shift_Task.h"

void Chassis_Task()
{
    if(RC_CtrlData.rc.ch3 > -900)
    {
        chassis_target_state[0].target_velocity = RC_CtrlData.rc.ch3 * shift_coefficient.chassis;
        chassis_target_state[1].target_velocity = RC_CtrlData.rc.ch3 * shift_coefficient.chassis;
    }
    if(RC_CtrlData.rc.ch2 > -900)
    {
        chassis_pid_gyroscope.error_now += RC_CtrlData.rc.ch2 * shift_coefficient.gyro;
    }
}
