#pragma once
#include "lvgl.h"
#define SPEED_METER_THEME_COLOR 0x6ea5cc

typedef struct
{
    /* gps数量 */
    lv_subject_t gps;
    /* 运动状态 */
    lv_subject_t sport_status;
    /* 电池电量 */
    lv_subject_t battery_level;
    /* 速度 */
    lv_subject_t speed_sub;
    /* 公里数 */
    lv_subject_t mile_sub;
    /* 坡度 */
    lv_subject_t slope_sub;
    /* 经纬度 */
    lv_subject_t latitude;  // 纬度
    lv_subject_t longitude; // 经度
    /* 计时 */
    lv_subject_t min_sub; // 分钟
    lv_subject_t sec_sub; // 秒
} speed_meter_sub_t;

typedef struct
{
    /* 地图 */
    lv_subject_t zoom_level;
    /* 存旧的地图缩放等级 */
    uint8_t old_zoom_level;
    /* 像素坐标 */
    float pixel_x;
    float pixel_y;
    /* 瓦片坐标 */
    int tile_x;
    int tile_y;
    /* 偏移量 */
    int32_t scroll_x;
    int32_t scroll_y;
} Map_info_t;

/**
 ** @brief 清除默认值
 */
void Com_clear_default(lv_obj_t *obj);

/**
 ** @brief 设置主题
 */
void Com_set_theme(lv_color_t theme_color, bool is_dark);
