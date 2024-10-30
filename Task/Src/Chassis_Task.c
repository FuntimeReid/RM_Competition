
#include "Chassis_Task.h"

#include "ChassisCtrl.h"
#include "DBUS_Task.h"
#include "Shift_Task.h"

void Chassis_Task()
{
    if(RC_CtrlData.rc.ch3 > -900)
    {
        chassis_target_state[0].target_velocity = RC_CtrlData.rc.ch3 * chassis_coefficient;
        chassis_target_state[1].target_velocity = RC_CtrlData.rc.ch3 * chassis_coefficient;
    }

}
