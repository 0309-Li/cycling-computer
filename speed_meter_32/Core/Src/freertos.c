/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "lvgl.h"
#include "lv_port_indev.h"
#include "lv_port_lcd_stm32.h"
#include "demos/lv_demos.h"
#include "ui.h"
#include "fatfs.h"
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
/* Definitions for main_task */
osThreadId_t main_taskHandle;
const osThreadAttr_t main_task_attributes = {
  .name = "main_task",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for key_task */
osThreadId_t key_taskHandle;
const osThreadAttr_t key_task_attributes = {
  .name = "key_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for pwr_off */
osThreadId_t pwr_offHandle;
const osThreadAttr_t pwr_off_attributes = {
  .name = "pwr_off",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for gps_task */
osThreadId_t gps_taskHandle;
const osThreadAttr_t gps_task_attributes = {
  .name = "gps_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void main_task_func(void *argument);
extern void key_task_func(void *argument);
extern void power_task_func(void *argument);
extern void gps_task_func(void *argument);

extern void MX_USB_DEVICE_Init(void);
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
  /* creation of main_task */
  main_taskHandle = osThreadNew(main_task_func, NULL, &main_task_attributes);

  /* creation of key_task */
  key_taskHandle = osThreadNew(key_task_func, NULL, &key_task_attributes);

  /* creation of pwr_off */
  pwr_offHandle = osThreadNew(power_task_func, NULL, &pwr_off_attributes);

  /* creation of gps_task */
  gps_taskHandle = osThreadNew(gps_task_func, NULL, &gps_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_main_task_func */
/**
 * @brief  Function implementing the main_task thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_main_task_func */
void main_task_func(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN main_task_func */
  // 初始化LVGL
  lv_init();

  // 设置时钟回调
  lv_tick_set_cb(xTaskGetTickCount);
  lv_delay_set_cb(vTaskDelay);



  // 初始化显示设备
  lv_port_disp_init();

  // 初始化触摸屏
  lv_port_indev_init();

  // 创建UI 使用DEMO
  // lv_demo_benchmark();
  // lv_demo_widgets();
  //! 挂载SD卡
  f_mount(&SDFatFS, SDPath, 1);
  ui_init();

  /* Infinite loop */
  for (;;)
  {
    uint32_t tick = lv_timer_handler();
    osDelay(pdMS_TO_TICKS(tick));
  }
  /* USER CODE END main_task_func */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

