#include "gpx.h"

/**
 ** @brief 初始化速度和距离地图
 ** @param parent 父对象
 */
void speed_mile_map_init(lv_obj_t *parent);

/**
 ** @brief 更新地图
 */
void speed_mile_map_update(lv_obj_t *map_area);

/**
 ** @brief 地图事件回调
 ** @param e 事件对象
 */
void speed_mile_map_event_cb(lv_event_t *e);

/**
 ** @brief 删除地图缓存
 ** @param map_area 地图对象区域
 */
void del_map_cache(lv_obj_t *map_area);

/**
 ** @brief 地图缩放等级回调
 ** @param e 事件对象
 */
void speed_mile_map_zoom_level_cb(lv_event_t *e);

/**
 ** @brief 回到原点回调
 ** @param e 事件对象
 */
void map_back_cb(lv_event_t *e);

extern speed_meter_sub_t *speed_meter_sub;

Map_info_t *map_info;

//! 滚动回调标志位 --- 是否是代码触发
bool is_scroll_code = false;

/**
 ** @brief 设置gpx页面内容
 ** @param parent 父对象
 */
void Tab_pages_gpx_set_content(lv_obj_t *parent)
{
    //? 清除默认样式
    Com_clear_default(parent);
    //? 设置flex布局
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);
    //! 地图内容区域
    lv_obj_t *map_area = lv_obj_create(parent);
    //? 清除默认样式
    Com_clear_default(map_area);
    lv_obj_set_size(map_area, lv_pct(100), lv_pct(85));
    //? 设置背景颜色
    lv_obj_set_style_bg_color(map_area, lv_color_hex(0x000000), LV_PART_MAIN);
    //! 初始化地图
    speed_mile_map_init(map_area);
    //! 速度和距离内容区域
    lv_obj_t *speed_mile_area = lv_obj_create(parent);
    //? 清除默认样式
    Com_clear_default(speed_mile_area);
    lv_obj_set_size(speed_mile_area, lv_pct(100), lv_pct(15));
    //? 设置背景颜色
    lv_obj_set_style_bg_color(speed_mile_area, lv_color_hex(SPEED_METER_THEME_COLOR), LV_PART_MAIN);
    //? 设置flex布局
    lv_obj_set_layout(speed_mile_area, LV_LAYOUT_FLEX);
    //? 设置flex对齐方式
    lv_obj_set_flex_align(speed_mile_area, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    //! 创建速度和距离的label标签
    lv_obj_t *speed_label = lv_label_create(speed_mile_area);
    lv_obj_t *mile_label = lv_label_create(speed_mile_area);
    //? 绑定主题
    lv_label_bind_text(speed_label, &speed_meter_sub->speed_sub, "%0.1f km/h");
    lv_label_bind_text(mile_label, &speed_meter_sub->mile_sub, "%0.2f km");
}

/**
 ** @brief 初始化速度和距离地图
 ** @param parent 父对象
 */
void speed_mile_map_init(lv_obj_t *parent)
{
    //! 创建网格包裹器
    lv_obj_t *map_grid = lv_obj_create(parent);
    //? 清除默认样式
    Com_clear_default(map_grid);
    //? 设置地图包裹器大小
    lv_obj_set_size(map_grid, lv_pct(100), lv_pct(100));
    //? 隐藏滚动条
    lv_obj_set_scrollbar_mode(map_grid, LV_SCROLLBAR_MODE_OFF);
    //? 去除滚动动量
    lv_obj_remove_flag(map_grid, LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_ELASTIC);
    //! 初始化地图结构体指针
    map_info = lv_malloc_zeroed(sizeof(Map_info_t));
    //? 初始化地图主题
    lv_subject_init_int(&map_info->zoom_level, 14);
    //? 初始化旧的缩放等级
    map_info->old_zoom_level = lv_subject_get_int(&map_info->zoom_level);
    //? 设置grid布局
    lv_obj_set_layout(map_grid, LV_LAYOUT_GRID);
    //? 设置general包裹对象网格列/行数
    static const int32_t col_dsc[] = {256, 256, 256, LV_GRID_TEMPLATE_LAST};
    static const int32_t row_dsc[] = {256, 256, 256, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(map_grid, col_dsc, row_dsc);

    //? 转换经纬度为像素坐标
    latlng_to_pixel_float(lv_subject_get_float(&speed_meter_sub->longitude),
                          lv_subject_get_float(&speed_meter_sub->latitude),
                          lv_subject_get_int(&map_info->zoom_level),
                          &map_info->pixel_x, &map_info->pixel_y);

    //! 更新地图
    speed_mile_map_update(map_grid);

    //! 注册地图事件回调
    lv_obj_add_event_cb(map_grid, speed_mile_map_event_cb, LV_EVENT_SCROLL, NULL);

    //! 缩放等级控制 --- 4-14
    lv_obj_t *slider = lv_slider_create(parent);
    //? 设置滑动条大小
    lv_obj_set_size(slider, 10, lv_pct(80));
    //? 设置滑动条对齐方式
    lv_obj_align(slider, LV_ALIGN_RIGHT_MID, -10, 0);
    //? 设置滑动条范围
    lv_slider_set_range(slider, 4, 14);
    //? 绑定主题
    lv_slider_bind_value(slider, &map_info->zoom_level);
    lv_obj_add_event_cb(slider, speed_mile_map_zoom_level_cb, LV_EVENT_VALUE_CHANGED, map_grid);

    //! 回到原点
    lv_obj_t *back_btn = lv_obj_create(parent);
    //? 清除默认样式
    Com_clear_default(back_btn);
    //? 设置按钮大小
    lv_obj_set_size(back_btn, 20, 20);
    //? 设置背景颜色
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(SPEED_METER_THEME_COLOR), LV_PART_MAIN);
    //? 设置圆角
    lv_obj_set_style_radius(back_btn, lv_pct(50), LV_PART_MAIN);
    //? 设置按钮对齐方式
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
    //? 创建label标签
    lv_obj_t *back_label = lv_label_create(back_btn);
    //? 水滴图案
    lv_label_set_text(back_label, LV_SYMBOL_TINT);
    //? 设置文本颜色
    lv_obj_set_style_text_color(back_label, lv_color_hex(0xffffff), LV_PART_MAIN);
    //? 设置对齐方式
    lv_obj_align(back_label, LV_ALIGN_CENTER, 0, 0);
    //? 绑定单击事件
    lv_obj_add_event_cb(back_btn, map_back_cb, LV_EVENT_CLICKED, map_grid);
}

/**
 ** @brief 更新地图
 */
void speed_mile_map_update(lv_obj_t *map_grid)
{
    //! 删除地图缓存
    del_map_cache(map_grid);
    //? 转换为瓦片坐标
    pixel_to_tile_float(map_info->pixel_x, map_info->pixel_y, &map_info->tile_x, &map_info->tile_y);
    lv_log("tile_x: %d, tile_y: %d", map_info->tile_x, map_info->tile_y);
    //? 更新地图
    for (int i = 0; i < 9; i++)
    {
        //? 创建地图图片对象
        lv_obj_t *map_img = lv_image_create(map_grid);
        char map_data[128] = {0};
        sprintf(map_data, "D:/%d/%d/%d/tile.bmp", lv_subject_get_int(&map_info->zoom_level), map_info->tile_x + (i % 3 - 1), map_info->tile_y + (i / 3 - 1));
        lv_image_set_src(map_img, map_data);
        lv_obj_set_grid_cell(map_img, LV_GRID_ALIGN_STRETCH, i % 3, 1, LV_GRID_ALIGN_STRETCH, i / 3, 1);
    }
    //! 将具体定位地点移动到地图中心
    //? 获取容器宽度和高度 --- 先更新组件
    lv_obj_update_layout(map_grid);
    int32_t map_area_width = lv_obj_get_width(map_grid);
    int32_t map_area_height = lv_obj_get_height(map_grid);
    map_info->scroll_x = 256 + ((uint32_t)map_info->pixel_x % 256 - map_area_width / 2);
    map_info->scroll_y = 256 + ((uint32_t)map_info->pixel_y % 256 - map_area_height / 2);
    //? 居中位移生效
    is_scroll_code = true;
    lv_obj_scroll_to_x(map_grid, map_info->scroll_x, LV_ANIM_OFF);
    lv_obj_scroll_to_y(map_grid, map_info->scroll_y, LV_ANIM_OFF);
}

/**
 ** @brief 地图事件回调
 ** @param e 事件对象
 */
void speed_mile_map_event_cb(lv_event_t *e)
{
    //? 检查是否是代码触发
    if (is_scroll_code)
    {
        is_scroll_code = false;
        return;
    }
    //? 获取地图对象
    lv_obj_t *map_grid = lv_event_get_target(e);
    //! 获取新的偏移量
    int32_t new_scroll_x = lv_obj_get_scroll_x(map_grid);
    int32_t new_scroll_y = lv_obj_get_scroll_y(map_grid);
    //? 更新地图结构体
    int32_t old_scroll_x = map_info->scroll_x;
    int32_t old_scroll_y = map_info->scroll_y;

    //? 计算偏移量差值
    int32_t scroll_x_diff = new_scroll_x - old_scroll_x;
    int32_t scroll_y_diff = new_scroll_y - old_scroll_y;

    //? 更新像素坐标
    map_info->pixel_x += scroll_x_diff;
    map_info->pixel_y += scroll_y_diff;
    //? 更新地图
    speed_mile_map_update(map_grid);
}

/**
 ** @brief 删除地图缓存
 ** @param map_area 地图对象区域
 */
void del_map_cache(lv_obj_t *map_grid)
{
    uint32_t child_cnt = lv_obj_get_child_count(map_grid);
    for (int i = 0; i < child_cnt; i++)
    {
        lv_obj_del(lv_obj_get_child(map_grid, 0));
    }
}

/**
 ** @brief 地图缩放等级回调
 ** @param e 事件对象
 */
void speed_mile_map_zoom_level_cb(lv_event_t *e)
{
    //? 获取地图对象
    lv_obj_t *slider = lv_event_get_target(e);
    lv_obj_t *map_grid = lv_event_get_user_data(e);
    //? 更新地图结构体
    int32_t new_zoom_level = lv_slider_get_value(slider);
    //! 新旧缩放比与旧像素点坐标计算新像素点坐标
    pixel_zoom_convert_float(map_info->pixel_x, map_info->pixel_y,
                             map_info->old_zoom_level, new_zoom_level,
                             &map_info->pixel_x, &map_info->pixel_y);
    //? 更新地图缩放参数
    map_info->old_zoom_level = new_zoom_level;
    //? 更新地图
    speed_mile_map_update(map_grid);
}

/**
 ** @brief 回到原点回调
 ** @param e 事件对象
 */
void map_back_cb(lv_event_t *e)
{
    //? 重置缩放等级
    lv_subject_set_int(&map_info->zoom_level, 14);
    //? 更新旧缩放等级
    map_info->old_zoom_level = lv_subject_get_int(&map_info->zoom_level);
    //? 获取地图对象
    lv_obj_t *map_grid = lv_event_get_user_data(e);
    //? 根据经纬度计算原点像素坐标
    latlng_to_pixel_float(lv_subject_get_float(&speed_meter_sub->longitude),
                          lv_subject_get_float(&speed_meter_sub->latitude),
                          lv_subject_get_int(&map_info->zoom_level),
                          &map_info->pixel_x, &map_info->pixel_y);
    //? 更新地图
    speed_mile_map_update(map_grid);
}
