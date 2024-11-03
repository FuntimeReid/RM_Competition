
#include "PID_Task.h"

#include "ChassisCtrl.h"
#include "GM6020Ctrl.h"
#include "M2006.h"
#include "PID.h"
#include "imu_task.h"

int64_t gyro_temp;

void PID_Task_Init()
{
    PID_Ini(&chassis_pid_velocity,5,0.06,0);
    PID_Ini(&chassis_pid_gyroscope,30,0,0);
    gyro_temp = 0;

    PID_Ini(&GM6020_pid_location,0.4,0,0);
    PID_Ini(&GM6020_pid_velocity,8,0,0);

    PID_Ini(&M2006_pid_location[0],0.25,0,0.4);
    PID_Ini(&M2006_pid_velocity[0],8,0,0);
    PID_Ini(&M2006_pid_torque[0],1.4,0.5,0);
    PID_Ini(&M2006_pid_location[1],0.25,0,0.4);
    PID_Ini(&M2006_pid_velocity[1],8,0,0);
    PID_Ini(&M2006_pid_torque[1],1.4,0.5,0);
}

void PID_Task()
{
    chassis_target_state[0].current = PID_Calc(&chassis_pid_velocity,chassis_target_state[0].target_velocity,motor_chassis[0].speed_rpm,0,10000,16384,false,false);
    chassis_target_state[1].current = PID_Calc(&chassis_pid_velocity,chassis_target_state[1].target_velocity,motor_chassis[1].speed_rpm,0,10000,16384,false,false);
    yaw_state.last_yaw = yaw_state.yaw;
    yaw_state.yaw = (int32_t)INS.Yaw;
    gyro_temp = PID_Calc(&chassis_pid_gyroscope,0,yaw_state.yaw,yaw_state.last_yaw,10000,16384,false,true);;
    chassis_target_state[0].target_velocity += gyro_temp;
    chassis_target_state[1].target_velocity -= gyro_temp;
    chassis_target_state[0].target_velocity = Limit(9000,chassis_target_state[0].target_velocity);
    chassis_target_state[1].target_velocity = Limit(9000,chassis_target_state[1].target_velocity);

    GM6020_state.target_velocity = PID_Calc(&GM6020_pid_location,0,GM6020_measure.ecd,GM6020_measure.last_ecd,50,160,true,false);
    GM6020_state.current = PID_Calc(&GM6020_pid_velocity,GM6020_state.target_velocity * 10,GM6020_measure.speed_rpm * 10,0,1500,30000,false,false);

    M2006_state[0].target_speed = PID_Calc(&M2006_pid_location[0],0,M2006_measure[0].ecd,M2006_measure[0].last_ecd,500,13000,true,false);
    M2006_state[0].target_torque = PID_Calc(&M2006_pid_velocity[0],M2006_state[0].target_speed,M2006_measure[0].speed_rpm,0,10000,10000,false,false);
    M2006_state[0].current = PID_Calc(&M2006_pid_torque[0],M2006_state[0].target_torque,M2006_measure[0].torque,0,3000,10000,false,false);
}
