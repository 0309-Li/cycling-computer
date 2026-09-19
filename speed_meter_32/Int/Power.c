#include "Power.h"
#include "gpio.h"
#include "adc.h"
#include "Key.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "ui.h"
// extern ui_t *ui;
bool isCharging;
float voltage;

void power_async_cb(void *arg)
{
    ui_update_battery(isCharging, (uint8_t)(voltage * 100.0f / 4.2f));
}

void Power_Off(void *arg)
{
    vTaskDelay(2);
    HAL_GPIO_WritePin(POWER_EN_GPIO_Port, POWER_EN_Pin, GPIO_PIN_RESET);
}

void power_task_func(void *arg)
{
    Power_Init();
    printf("Power function start\n");

    for (;;)
    {
        isCharging = Power_IsCharging();
        voltage = Power_GetBatteryVoltage();
        // printf("isCharging: %d, voltage: %f\n", isCharging, voltage);
        //! 异步调用更新电池电量函数
        lv_async_call(power_async_cb, NULL);
        // ui_update_battery(isCharging, (uint8_t)(voltage * 100.0f / 4.2f));

        // lv_subject_set_pointer(&ui->data.battery, (void *)LV_SYMBOL_CHARGE);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Power_Init()
{
    HAL_ADC_Start(&hadc1);
    vTaskDelay(pdMS_TO_TICKS(1000));
    Key_RegisterCallback(KEY_POWER, Power_Off, NULL);
}

bool Power_IsCharging()
{
    return HAL_GPIO_ReadPin(CHG_DET_GPIO_Port, CHG_DET_Pin) == GPIO_PIN_RESET;
}

float Power_GetBatteryVoltage()
{
    uint32_t val = HAL_ADC_GetValue(&hadc1);
    return ((float)(val * 2)) / 4096.0f * 3.3f;
}
