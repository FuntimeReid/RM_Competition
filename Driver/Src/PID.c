
#include "PID.h"

#include "Outage_Task.h"

pid_t chassis_pid_gyroscope;
pid_t chassis_pid_velocity[2];

pid_t GM6020_pid_location;
pid_t GM6020_pid_velocity;

pid_t M2006_pid_location[2];
pid_t M2006_pid_velocity[2];
pid_t M2006_pid_torque[2];

int32_t Limit(int32_t limit,int32_t target)
{
    if(limit < target && target > 0)
    {
        return limit;
    }
    if(-limit > target && target < 0)
    {
        return -limit;
    }
    return target;
}

void PID_Ini(pid_t *pid,float kp,float ki,float kd,int16_t limit_i,int16_t limit_result)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->limit_i = limit_i;
    pid->limit_result = limit_result;
}

int16_t PID_Calc(pid_t *pid,int32_t target,int16_t now)
{
    int32_t result = 0;

    pid->error_now =  target - now;

    if(pid->error_now < 500)
    {
        if(if_work)
        {
            pid->error_all += pid->error_now * 0.1;
        }
        else
        {
            pid->error_all = 0;
        }
    }//积分分离

    pid->error_all = Limit(pid->limit_i,pid->error_all);
    if((target > 0 && pid->error_all < 0) || (target < 0 && pid->error_all > 0))
    {
        pid->error_all *= -0.8;
    }//减小正负交替的响应时间

    result = pid->kp * pid->error_now + pid->ki * pid->error_all + pid->kd * (pid->error_now - pid->error_last);
    result = Limit(pid->limit_result,result);
    pid->error_last = pid->error_now;
    return result;
}

int32_t Loc_Error_Now_Calc(pid_t pid,int32_t now,int32_t last)
{
    int32_t temp = 0;

    if(now - last > 0)
    {
        if(now - last > 4200)
        {
            temp = (8191 - now + last) + pid.error_now;
            return temp;
        }
        else
        {
            temp = (last - now) + pid.error_now;
            return temp;
        }
    }
    else
    {
        if(now - last < -4200)
        {
            temp = -(last - 8191 + now) + pid.error_now;
            return temp;
        }
        else
        {
            temp = (last - now) + pid.error_now;
            return temp;
        }
    }
}