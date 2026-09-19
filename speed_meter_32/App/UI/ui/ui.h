#pragma once
#include "Com_api.h"
#include "general.h"
#include "setting.h"
#include "gpx.h"
#include "Com_translate.h"



/**
 ** @brief 初始化UI
 */
void ui_init(void);

/**
 ** @brief 更新电池电量
 */
void ui_update_battery(bool charg, int percent);
