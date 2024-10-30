
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

extern pid_t chassis_pid_velocity;

extern pid_t GM6020_pid_location;
extern pid_t GM6020_pid_velocity;
extern pid_t GM6020_pid_torque;

extern pid_t M2006_pid_location;
extern pid_t M2006_pid_velocity;
extern pid_t M2006_pid_torque;

int64_t Limit(int64_t limit,int64_t target);

void PID_Init(pid_t *pid,float kp,float ki,float kd);

int64_t PID_Calculate(pid_t *pid,int16_t target,int16_t now,int16_t last,int16_t limit_i,int64_t limit_result,bool if_zero_crossing);

#endif //PID_H
