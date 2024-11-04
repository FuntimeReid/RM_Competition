
#include "PID.h"

#include "Outage_Task.h"

pid_t chassis_pid_gyroscope;
pid_t chassis_pid_velocity;

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
    else if(-limit > target && target < 0)
    {
        return -limit;
    }
    return target;
}

void PID_Ini(pid_t *pid,float kp,float ki,float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

int16_t PID_Calc(pid_t *pid,int32_t target,int32_t now,int32_t last,int16_t limit_i,int16_t limit_result,bool if_zero_crossing,bool if_gyroscope)
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
    else if(if_gyroscope)
    {
        if(now - last > 0)
        {
            if(now - last > 180)
            {
                pid->error_now += (360 - now + last);
            }
            else
            {
                pid->error_now -= (now - last);
            }
        }
        else
        {
            if(now - last < -180)
            {
                pid->error_now += (360 - last + now);
            }
            else
            {
                pid->error_now -= (now - last);
            }
        }
    }//陀螺仪位置环过零点pid
    else
    {
        pid->error_now =  target - now;
    }//速度环pid

    if(pid->error_now < 500)
    {
        if(outage_tim <= 100)
        {
            pid->error_all += pid->error_now * 0.1;
        }
        else
        {
            pid->error_all = 0;
        }
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