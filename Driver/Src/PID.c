
#include "PID.h"

pid_t chassis_pid_velocity;

pid_t GM6020_pid_location;
pid_t GM6020_pid_velocity;

pid_t M2006_pid_location;
pid_t M2006_pid_velocity;
pid_t M2006_pid_torque;

int64_t Limit(int64_t limit,int64_t target)
{
    if(limit < target && target > 0)
    {
        return limit;
    }
    else if(-limit > target && target < 0)
    {
        return -limit;
    }
    return target;
}

void PID_Init(pid_t *pid,float kp,float ki,float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

int64_t PID_Calculate(pid_t *pid,int16_t target,int16_t now,uint16_t last,int16_t limit_i,int64_t limit_result,bool if_zero_crossing)
{
    int64_t result = 0;
    if(if_zero_crossing)
    {
        if(now - last > 0)
        {
            if(now - last > 4200)
            {
                pid->error_now += (8191 - now + last);
            }
            else
            {
                pid->error_now -= (now - last);
            }
        }
        else
        {
            if(now - last < -4200)
            {
                pid->error_now -= (last - 8191 + now);
            }
            else
            {
                pid->error_now += (last - now);
            }
        }
    }//位置环过零点pid
    else
    {
        pid->error_now =  target - now;
    }//速度环pid

    if(pid->error_now < 500)
    {
        pid->error_all += pid->error_now * 0.1;
    }//积分分离

    pid->error_all = Limit(limit_i,pid->error_all);
    if((target > 0 && pid->error_all < 0) || (target < 0 && pid->error_all > 0))
    {
        pid->error_all *= -0.8;
    }//减小正负交替的响应时间

    result = pid->kp * pid->error_now + pid->ki * pid->error_all;
    result = Limit(limit_result,result);
    pid->error_last = pid->error_now;
    return result;
}