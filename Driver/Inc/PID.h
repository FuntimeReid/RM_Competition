
#ifndef PID_H
#define PID_H

#include "stm32f4xx_hal.h"
#include "stdbool.h"

typedef struct
{
    float kp;
    float ki;
    float kd;
    int32_t error_now;
    int32_t error_last;
    int32_t error_all;

    int16_t limit_i;
    int16_t limit_result;
}pid_t;

extern pid_t chassis_pid_gyroscope;
extern pid_t chassis_pid_velocity[2];

extern pid_t GM6020_pid_location;
extern pid_t GM6020_pid_velocity;

extern pid_t M2006_pid_location[2];
extern pid_t M2006_pid_velocity[2];
extern pid_t M2006_pid_torque[2];

int32_t Limit(int32_t limit,int32_t target);

void PID_Ini(pid_t *pid,float kp,float ki,float kd,int16_t limit_i,int16_t limit_result);

int16_t PID_Calc(pid_t *pid,int32_t target,int16_t now);

int32_t Loc_Error_Now_Calc(pid_t pid,int32_t now,int32_t last);

#endif //PID_H
