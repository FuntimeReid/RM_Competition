
#include "Pitch_Task.h"

#include "DBUS_Task.h"
#include "GM6020Ctrl.h"
#include "Outage_Task.h"
#include "PID.h"
#include "math.h"

void Pitch_Task_Init()
{
    GM6020_pid_location.error_now = 0;;
}

void Pitch_Task()
{
    if(RC_CtrlData.rc.ch1 > -900)
    {
        GM6020_pid_location.error_now -= RC_CtrlData.rc.ch1 * 0.1;
        if(GM6020_measure.ecd + GM6020_pid_location.error_now  > 1150 && GM6020_measure.ecd < 7000)
        {
            GM6020_pid_location.error_now = -(GM6020_measure.ecd - 1150);
        }
        else if(GM6020_measure.ecd + GM6020_pid_location.error_now < 100)
        {
            GM6020_pid_location.error_now = fmin(100 - GM6020_measure.ecd,8191-GM6020_measure.ecd+100);
        }
    }
}
