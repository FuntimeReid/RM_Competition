/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "DBUS_Task.h"
#include "CAN_Task.h"
#include "PID_Task.h"
#include "Chassis_Task.h"
#include "Shift_Task.h"
#include "GM6020Ctrl.h"
#include "ChassisCtrl.h"
#include "M2006.h"
#include "Outage_Task.h"
#include "Door_Task.h"
#include "LED_Task.h"
#include "Pitch_Task.h"
#include "Shovel_Task.h"
#include "imu_task.h"
#include "Lift_Task.h"
#include "Slide_Task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DBUSTasK */
osThreadId_t DBUSTasKHandle;
const osThreadAttr_t DBUSTasK_attributes = {
  .name = "DBUSTasK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for CANTask */
osThreadId_t CANTaskHandle;
const osThreadAttr_t CANTask_attributes = {
  .name = "CANTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for PIDTask */
osThreadId_t PIDTaskHandle;
const osThreadAttr_t PIDTask_attributes = {
  .name = "PIDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DoorTask */
osThreadId_t DoorTaskHandle;
const osThreadAttr_t DoorTask_attributes = {
  .name = "DoorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ShiftTask */
osThreadId_t ShiftTaskHandle;
const osThreadAttr_t ShiftTask_attributes = {
  .name = "ShiftTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ChassisTask */
osThreadId_t ChassisTaskHandle;
const osThreadAttr_t ChassisTask_attributes = {
  .name = "ChassisTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for PitchTask */
osThreadId_t PitchTaskHandle;
const osThreadAttr_t PitchTask_attributes = {
  .name = "PitchTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for OutageTask */
osThreadId_t OutageTaskHandle;
const osThreadAttr_t OutageTask_attributes = {
  .name = "OutageTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LEDTask */
osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes = {
  .name = "LEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ShovelTask */
osThreadId_t ShovelTaskHandle;
const osThreadAttr_t ShovelTask_attributes = {
  .name = "ShovelTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for IMUTask */
osThreadId_t IMUTaskHandle;
const osThreadAttr_t IMUTask_attributes = {
  .name = "IMUTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for SlideTask */
osThreadId_t SlideTaskHandle;
const osThreadAttr_t SlideTask_attributes = {
  .name = "SlideTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LiftTask */
osThreadId_t LiftTaskHandle;
const osThreadAttr_t LiftTask_attributes = {
  .name = "LiftTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DBUS_Sem */
osSemaphoreId_t DBUS_SemHandle;
const osSemaphoreAttr_t DBUS_Sem_attributes = {
  .name = "DBUS_Sem"
};
/* Definitions for CAN_Sem */
osSemaphoreId_t CAN_SemHandle;
const osSemaphoreAttr_t CAN_Sem_attributes = {
  .name = "CAN_Sem"
};
/* Definitions for Shift_Sem */
osSemaphoreId_t Shift_SemHandle;
const osSemaphoreAttr_t Shift_Sem_attributes = {
  .name = "Shift_Sem"
};
/* Definitions for Outage_Sem */
osSemaphoreId_t Outage_SemHandle;
const osSemaphoreAttr_t Outage_Sem_attributes = {
  .name = "Outage_Sem"
};
/* Definitions for Chassis_Sem */
osSemaphoreId_t Chassis_SemHandle;
const osSemaphoreAttr_t Chassis_Sem_attributes = {
  .name = "Chassis_Sem"
};
/* Definitions for Pitch_Sem */
osSemaphoreId_t Pitch_SemHandle;
const osSemaphoreAttr_t Pitch_Sem_attributes = {
  .name = "Pitch_Sem"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartDBUSTask(void *argument);
void StartCANTask(void *argument);
void StartPIDTask(void *argument);
void StartDoorTask(void *argument);
void StartShiftTask(void *argument);
void StartChassisTask(void *argument);
void StartPitchTask(void *argument);
void StartOutageTask(void *argument);
void StartLEDTask(void *argument);
void StartShovelTask(void *argument);
void StartIMUTask(void *argument);
void StartSlideTask(void *argument);
void StartLiftTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of DBUS_Sem */
  DBUS_SemHandle = osSemaphoreNew(1, 1, &DBUS_Sem_attributes);

  /* creation of CAN_Sem */
  CAN_SemHandle = osSemaphoreNew(1, 1, &CAN_Sem_attributes);

  /* creation of Shift_Sem */
  Shift_SemHandle = osSemaphoreNew(1, 1, &Shift_Sem_attributes);

  /* creation of Outage_Sem */
  Outage_SemHandle = osSemaphoreNew(1, 1, &Outage_Sem_attributes);

  /* creation of Chassis_Sem */
  Chassis_SemHandle = osSemaphoreNew(1, 1, &Chassis_Sem_attributes);

  /* creation of Pitch_Sem */
  Pitch_SemHandle = osSemaphoreNew(1, 1, &Pitch_Sem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of DBUSTasK */
  DBUSTasKHandle = osThreadNew(StartDBUSTask, NULL, &DBUSTasK_attributes);

  /* creation of CANTask */
  CANTaskHandle = osThreadNew(StartCANTask, NULL, &CANTask_attributes);

  /* creation of PIDTask */
  PIDTaskHandle = osThreadNew(StartPIDTask, NULL, &PIDTask_attributes);

  /* creation of DoorTask */
  DoorTaskHandle = osThreadNew(StartDoorTask, NULL, &DoorTask_attributes);

  /* creation of ShiftTask */
  ShiftTaskHandle = osThreadNew(StartShiftTask, NULL, &ShiftTask_attributes);

  /* creation of ChassisTask */
  ChassisTaskHandle = osThreadNew(StartChassisTask, NULL, &ChassisTask_attributes);

  /* creation of PitchTask */
  PitchTaskHandle = osThreadNew(StartPitchTask, NULL, &PitchTask_attributes);

  /* creation of OutageTask */
  OutageTaskHandle = osThreadNew(StartOutageTask, NULL, &OutageTask_attributes);

  /* creation of LEDTask */
  LEDTaskHandle = osThreadNew(StartLEDTask, NULL, &LEDTask_attributes);

  /* creation of ShovelTask */
  ShovelTaskHandle = osThreadNew(StartShovelTask, NULL, &ShovelTask_attributes);

  /* creation of IMUTask */
  IMUTaskHandle = osThreadNew(StartIMUTask, NULL, &IMUTask_attributes);

  /* creation of SlideTask */
  SlideTaskHandle = osThreadNew(StartSlideTask, NULL, &SlideTask_attributes);

  /* creation of LiftTask */
  LiftTaskHandle = osThreadNew(StartLiftTask, NULL, &LiftTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartDBUSTask */
/**
* @brief Function implementing the DBUSTasK thread.
* @param argument: Not used
* @retval None
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  RemoteDataProcess(sbus_rx_buffer);
  osSemaphoreRelease(DBUS_SemHandle);
  if_start = true;
}
/* USER CODE END Header_StartDBUSTask */
void StartDBUSTask(void *argument)
{
  /* USER CODE BEGIN StartDBUSTask */
  osStatus_t DBUS_rx_return = osOK;
  DBUS_Init();
  /* Infinite loop */
  for(;;)
  {
    DBUS_rx_return = osSemaphoreAcquire(DBUS_SemHandle, osWaitForever);
    if(DBUS_rx_return == osOK)
    {
      DBUS_Task();
      osSemaphoreRelease(Pitch_SemHandle);
      osSemaphoreRelease(Chassis_SemHandle);
    }
    osDelay(1);
  }
  /* USER CODE END StartDBUSTask */
}

/* USER CODE BEGIN Header_StartCANTask */
/**
* @brief Function implementing the CANTask thread.
* @param argument: Not used
* @retval None
*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN_rx_header, CAN_rx_data);
  switch (CAN_rx_header.StdId)
  {
    case 0x201:
    {
      Get_M2006_Measure(&M2006_measure[0],CAN_rx_data);
      break;
    }
    case 0x202:
    {
      Get_M2006_Measure(&M2006_measure[1],CAN_rx_data);
      break;
    }
    case 0x203:
    {
      Get_Motor_Measure(&motor_chassis[0],CAN_rx_data);
      break;
    }
    case 0x204:
    {
      Get_Motor_Measure(&motor_chassis[1],CAN_rx_data);
      break;
    }
    case 0x207:
    {
      Get_GM6020_Measure(&GM6020_measure,CAN_rx_data);
      break;
    }
  }
}
/* USER CODE END Header_StartCANTask */
void StartCANTask(void *argument)
{
  /* USER CODE BEGIN StartCANTask */
  /* Infinite loop */
  for(;;)
  {
    CAN_Task();
    osDelay(1);
  }
  /* USER CODE END StartCANTask */
}

/* USER CODE BEGIN Header_StartPIDTask */
/**
* @brief Function implementing the PIDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPIDTask */
void StartPIDTask(void *argument)
{
  /* USER CODE BEGIN StartPIDTask */
  PID_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    PID_Task();
    osDelay(1);
  }
  /* USER CODE END StartPIDTask */
}

/* USER CODE BEGIN Header_StartDoorTask */
/**
* @brief Function implementing the DoorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDoorTask */
void StartDoorTask(void *argument)
{
  /* USER CODE BEGIN StartDoorTask */
  Door_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    Door_Task();
    osDelay(1);
  }
  /* USER CODE END StartDoorTask */
}

/* USER CODE BEGIN Header_StartShiftTask */
/**
* @brief Function implementing the ShiftTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartShiftTask */
void StartShiftTask(void *argument)
{
  /* USER CODE BEGIN StartShiftTask */
  Shift_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    Shift_Task();
    osDelay(1);
  }
  /* USER CODE END StartShiftTask */
}

/* USER CODE BEGIN Header_StartChassisTask */
/**
* @brief Function implementing the ChassisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartChassisTask */
void StartChassisTask(void *argument)
{
  /* USER CODE BEGIN StartChassisTask */
  osStatus_t chassis_return = osOK;
  /* Infinite loop */
  for(;;)
  {
    chassis_return = osSemaphoreAcquire(Chassis_SemHandle, osWaitForever);
    if(chassis_return == osOK)
    {
      Chassis_Task();
    }
    osDelay(1);
  }
  /* USER CODE END StartChassisTask */
}

/* USER CODE BEGIN Header_StartPitchTask */
/**
* @brief Function implementing the PitchTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPitchTask */
void StartPitchTask(void *argument)
{
  /* USER CODE BEGIN StartPitchTask */
  osStatus_t pitch_return = osOK;
  Pitch_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    pitch_return = osSemaphoreAcquire(Pitch_SemHandle, osWaitForever);
    if(pitch_return == osOK)
    {
      Pitch_Task();
    }
    osDelay(1);
  }
  /* USER CODE END StartPitchTask */
}

/* USER CODE BEGIN Header_StartOutageTask */
/**
* @brief Function implementing the OutageTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOutageTask */
void StartOutageTask(void *argument)
{
  /* USER CODE BEGIN StartOutageTask */
  Outage_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    Outage_Task();
    osDelay(1);
  }
  /* USER CODE END StartOutageTask */
}

/* USER CODE BEGIN Header_StartLEDTask */
/**
* @brief Function implementing the LEDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLEDTask */
void StartLEDTask(void *argument)
{
  /* USER CODE BEGIN StartLEDTask */
  LED_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    LED_Task();
    osDelay(1);
  }
  /* USER CODE END StartLEDTask */
}

/* USER CODE BEGIN Header_StartShovelTask */
/**
* @brief Function implementing the ShovelTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartShovelTask */
void StartShovelTask(void *argument)
{
  /* USER CODE BEGIN StartShovelTask */
  Shovel_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    Shovel_Task();
    osDelay(1);
  }
  /* USER CODE END StartShovelTask */
}

/* USER CODE BEGIN Header_StartIMUTask */
/**
* @brief Function implementing the IMUTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartIMUTask */
void StartIMUTask(void *argument)
{
  /* USER CODE BEGIN StartIMUTask */

  IMU_Init();
  /* Infinite loop */
  for(;;)
  {
    IMU_Task();
    osDelay(1);
  }
  /* USER CODE END StartIMUTask */
}

/* USER CODE BEGIN Header_StartSlideTask */
/**
* @brief Function implementing the SlideTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSlideTask */
void StartSlideTask(void *argument)
{
  /* USER CODE BEGIN StartSlideTask */
  Slide_Task_Init();
  /* Infinite loop */
  for(;;)
  {
    Slide_Task();
    osDelay(1);
  }
  /* USER CODE END StartSlideTask */
}

/* USER CODE BEGIN Header_StartLiftTask */
/**
* @brief Function implementing the LiftTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLiftTask */
void StartLiftTask(void *argument)
{
  /* USER CODE BEGIN StartLiftTask */
  /* Infinite loop */
  for(;;)
  {
    Lift_Task();
    osDelay(1);
  }
  /* USER CODE END StartLiftTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

