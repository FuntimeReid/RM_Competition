
#ifndef PID_H
#define PID_H

#include "stm32f4xx_hal.h"
#include "stdbool.h"

typedef struct
{
    float kp;
    float ki;
    float kd;
    double error_now;
    double error_last;
    double error_all;
}pid_t;

extern pid_t chassis_pid_gyroscope;
extern pid_t chassis_pid_velocity;

extern pid_t GM6020_pid_location;
extern pid_t GM6020_pid_velocity;

extern pid_t M2006_pid_location[2];
extern pid_t M2006_pid_velocity[2];
extern pid_t M2006_pid_torque[2];

int64_t Limit(int64_t limit,int64_t target);

void PID_Ini(pid_t *pid,float kp,float ki,float kd);

int64_t PID_Calc(pid_t *pid,int32_t target,int32_t now,int32_t last,int16_t limit_i,int64_t limit_result,bool if_zero_crossing,bool if_gyroscope);

#endif //PID_H
