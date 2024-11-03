
#include "../Inc/Lift_Task.h"

#include "DBUS_Task.h"
#include "M2006.h"
#include "PID.h"
#include "Shift_Task.h"

void Lift_Task()
{
    M2006_pid_location[0].error_now += RC_CtrlData.rc.ch0 * shift_coefficient.lift;
    M2006_pid_location[1].error_now += RC_CtrlData.rc.ch0 * shift_coefficient.lift;
}
