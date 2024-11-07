
#include "PID_Task.h"
#include "ChassisCtrl.h"
#include "GM6020Ctrl.h"
#include "M2006.h"
#include "PID.h"
#include "imu_task.h"

int32_t gyro_temp[2];

void PID_Task_Init()
{
    PID_Ini(&chassis_pid_velocity[0],5,0.06,0,10000,16384);
    PID_Ini(&chassis_pid_velocity[1],5,0.06,0,10000,16384);
    PID_Ini(&chassis_pid_gyroscope,40,0.5,2,50,16384);
    gyro_temp[0] = 0;
    gyro_temp[1] = 0;

    PID_Ini(&GM6020_pid_location,0.4,0,0,50,160);
    PID_Ini(&GM6020_pid_velocity,8,0,0,1500,30000);

    PID_Ini(&M2006_pid_location[0],0.25,0,0.4,500,13000);
    PID_Ini(&M2006_pid_velocity[0],8,0,0,10000,10000);
    PID_Ini(&M2006_pid_torque[0],1.4,0.5,0,3000,10000);
    PID_Ini(&M2006_pid_location[1],0.25,0,0.4,500,13000);
    PID_Ini(&M2006_pid_velocity[1],8,0,0,10000,10000);
    PID_Ini(&M2006_pid_torque[1],1.4,0.5,0,3000,10000);
}

void PID_Task()
{
    gyro_temp[0] = -PID_Calc(&chassis_pid_gyroscope,(int32_t)yaw_state.target_yaw,yaw_state.yaw);;
    gyro_temp[1] = gyro_temp[0];
    gyro_temp[0] += chassis_target_state[0].target_velocity;
    gyro_temp[1] += chassis_target_state[1].target_velocity;
    chassis_target_state[0].current = PID_Calc(&chassis_pid_velocity[0],gyro_temp[0],motor_chassis[0].speed_rpm);
    chassis_target_state[1].current = PID_Calc(&chassis_pid_velocity[1],gyro_temp[1],motor_chassis[1].speed_rpm);


    GM6020_state.target_velocity = PID_Calc(&GM6020_pid_location,Loc_Error_Now_Calc(GM6020_pid_location,GM6020_measure.ecd,GM6020_measure.last_ecd),0);
    GM6020_state.current = PID_Calc(&GM6020_pid_velocity,GM6020_state.target_velocity * 10,GM6020_measure.speed_rpm * 10);

    M2006_state[0].target_speed = PID_Calc(&M2006_pid_location[0],Loc_Error_Now_Calc(M2006_pid_location[0],M2006_measure[0].ecd,M2006_measure[0].last_ecd),0);
    M2006_state[0].target_torque = PID_Calc(&M2006_pid_velocity[0],M2006_state[0].target_speed,M2006_measure[0].speed_rpm);
    M2006_state[0].current = PID_Calc(&M2006_pid_torque[0],M2006_state[0].target_torque,M2006_measure[0].torque);

    M2006_state[1].target_speed = PID_Calc(&M2006_pid_location[1],Loc_Error_Now_Calc(M2006_pid_location[1],M2006_measure[1].ecd,M2006_measure[1].last_ecd),0);
    M2006_state[1].target_torque = PID_Calc(&M2006_pid_velocity[1],M2006_state[1].target_speed,M2006_measure[1].speed_rpm);
    M2006_state[1].current = PID_Calc(&M2006_pid_torque[1],M2006_state[1].target_torque,M2006_measure[1].torque);
}
