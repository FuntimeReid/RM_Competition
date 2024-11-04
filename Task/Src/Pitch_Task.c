
#include "Pitch_Task.h"

#include "DBUS_Task.h"
#include "Outage_Task.h"
#include "PID.h"

void Pitch_Task_Init()
{
    GM6020_pid_location.error_now = 0;;
}

void Pitch_Task()
{
    if(RC_CtrlData.rc.ch1 > -900)
    {
        GM6020_pid_location.error_now -= RC_CtrlData.rc.ch1 * 0.1;
    }
}
