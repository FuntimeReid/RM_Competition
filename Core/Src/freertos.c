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
/* Definitions for Pitch_Sem */
osSemaphoreId_t Pitch_SemHandle;
const osSemaphoreAttr_t Pitch_Sem_attributes = {
  .name = "Pitch_Sem"
};
/* Definitions for Chassis_Sem */
osSemaphoreId_t Chassis_SemHandle;
const osSemaphoreAttr_t Chassis_Sem_attributes = {
  .name = "Chassis_Sem"
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

  /* creation of Pitch_Sem */
  Pitch_SemHandle = osSemaphoreNew(1, 1, &Pitch_Sem_attributes);

  /* creation of Chassis_Sem */
  Chassis_SemHandle = osSemaphoreNew(1, 1, &Chassis_Sem_attributes);

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
  osSemaphoreRelease(DBUS_SemHandle);
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
      osSemaphoreRelease(Chassis_SemHandle);
      osSemaphoreRelease(Pitch_SemHandle);
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
  osSemaphoreRelease(CAN_SemHandle);
}
/* USER CODE END Header_StartCANTask */
void StartCANTask(void *argument)
{
  /* USER CODE BEGIN StartCANTask */
  osStatus CAN_rx_return = osOK;
  /* Infinite loop */
  for(;;)
  {
    CAN_rx_return = osSemaphoreAcquire(CAN_SemHandle, osWaitForever);
    if(CAN_rx_return == osOK)
    {
      CAN_RX_Task();
    }
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
  /* Infinite loop */
  for(;;)
  {
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
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartPitchTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

