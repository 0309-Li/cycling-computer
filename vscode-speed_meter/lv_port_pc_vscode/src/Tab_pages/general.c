#include "general.h"

//! 定义主题的结构体指针
extern speed_meter_sub_t *speed_meter_sub;

/**
 ** @brief 设置general页面边框
 ** @param target 目标对象
 */
void __Tab_pages_set_border(lv_obj_t *target)
{
    //? 设置边框大小
    lv_obj_set_style_border_width(target, 5, LV_PART_MAIN);

    //? 设置边框颜色
    lv_obj_set_style_border_color(target, lv_color_hex(SPEED_METER_THEME_COLOR), LV_PART_MAIN);

    //? 设置边框圆角
    lv_obj_set_style_radius(target, 10, LV_PART_MAIN);
}

/**
 ** @brief 设置general页面内容
 ** @param parent 父对象
 */
void Tab_pages_general_set_content(lv_obj_t *parent)
{
    //? 清除默认样式
    Com_clear_default(parent);
    //? 创建general包裹对象
    lv_obj_t *general = lv_obj_create(parent);
    //? 去除圆角
    lv_obj_set_style_radius(general, 0, LV_PART_MAIN);
    //? 去除边框
    lv_obj_set_style_border_width(general, 0, LV_PART_MAIN);
    lv_obj_set_size(general, lv_pct(100), lv_pct(100));
    //? 设置general包裹对象布局
    lv_obj_set_layout(general, LV_LAYOUT_GRID);
    //? 设置general包裹对象网格列/行数
    static const int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static const int32_t row_dsc[] = {LV_GRID_FR(2), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(general, col_dsc, row_dsc);

    //! 速度区域
    lv_obj_t *speed_obj = lv_obj_create(general);
    lv_obj_set_grid_cell(speed_obj, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 0, 1);
    //? 设置速度区域边框
    __Tab_pages_set_border(speed_obj);
    //? 创建速度label
    lv_obj_t *speed_label = lv_label_create(speed_obj);
    //? 绑定主题
    lv_label_bind_text(speed_label, &speed_meter_sub->speed_sub, "%.1f km/h");
    //? 设置速度label字体大小
    lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_26, LV_PART_MAIN);
    //? 设置对齐位置
    lv_obj_set_style_align(speed_label, LV_ALIGN_CENTER, LV_PART_MAIN);

    //! 公里数区域
    lv_obj_t *mile_obj = lv_obj_create(general);
    lv_obj_set_grid_cell(mile_obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    //? 设置公里数区域边框
    __Tab_pages_set_border(mile_obj);
    //? 创建公里数label
    lv_obj_t *mile_label = lv_label_create(mile_obj);
    //? 绑定主题
    lv_label_bind_text(mile_label, &speed_meter_sub->mile_sub, "%.2f km");
    //? 设置公里数label字体大小
    lv_obj_set_style_text_font(mile_label, &lv_font_montserrat_14, LV_PART_MAIN);
    //? 设置对齐位置
    lv_obj_set_style_align(mile_label, LV_ALIGN_CENTER, LV_PART_MAIN);

    //! 坡度区域
    lv_obj_t *slope_obj = lv_obj_create(general);
    lv_obj_set_grid_cell(slope_obj, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    //? 设置坡度区域边框
    __Tab_pages_set_border(slope_obj);
    //? 创建坡度label
    lv_obj_t *slope_label = lv_label_create(slope_obj);
    //? 绑定主题
    lv_label_bind_text(slope_label, &speed_meter_sub->slope_sub, "%.1f %%");
    //? 设置坡度label字体大小
    lv_obj_set_style_text_font(slope_label, &lv_font_montserrat_14, LV_PART_MAIN);
    //? 设置对齐位置
    lv_obj_set_style_align(slope_label, LV_ALIGN_CENTER, LV_PART_MAIN);

    //! 经纬度区域
    lv_obj_t *latitude_obj = lv_obj_create(general);
    //? 清楚默认样式
    Com_clear_default(latitude_obj);
    //? 设置flex布局
    lv_obj_set_layout(latitude_obj, LV_LAYOUT_FLEX);
    //? 设置flex方向
    lv_obj_set_style_flex_flow(latitude_obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN);
    lv_obj_set_grid_cell(latitude_obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
    //? 设置flex对齐方式
    lv_obj_set_flex_align(latitude_obj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //? 设置纬度区域边框
    __Tab_pages_set_border(latitude_obj);
    //? 创建纬度label
    lv_obj_t *latitude_label = lv_label_create(latitude_obj);
    //? 创建经度label
    lv_obj_t *longitude_label = lv_label_create(latitude_obj);
    //? 绑定主题
    lv_label_bind_text(latitude_label, &speed_meter_sub->latitude, "%.5f");
    lv_label_bind_text(longitude_label, &speed_meter_sub->longitude, "%.5f");
    //? 设置纬度label字体大小
    lv_obj_set_style_text_font(latitude_label, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_font(longitude_label, &lv_font_montserrat_14, LV_PART_MAIN);
    //? 设置对齐位置
    lv_obj_set_style_align(latitude_label, LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_align(longitude_label, LV_ALIGN_CENTER, LV_PART_MAIN);

    //! 计时区域
    lv_obj_t *time_obj = lv_obj_create(general);
    lv_obj_set_grid_cell(time_obj, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
    //? 设置计时区域边框
    __Tab_pages_set_border(time_obj);
    //? 创建计时label
    lv_obj_t *min_label = lv_label_create(time_obj);
    lv_obj_t *sec_label = lv_label_create(time_obj);
    //? 绑定主题
    lv_label_bind_text(min_label, &speed_meter_sub->min_sub, "%02d");
    lv_label_bind_text(sec_label, &speed_meter_sub->sec_sub, ":%02d");
    //? 设置计时label字体大小
    lv_obj_set_style_text_font(min_label, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_font(sec_label, &lv_font_montserrat_14, LV_PART_MAIN);
    //? 设置计时label位置
    lv_obj_set_pos(min_label, -10, 0);
    lv_obj_set_pos(sec_label, 10, 0);
    //? 设置对齐位置
    lv_obj_set_style_align(min_label, LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_align(sec_label, LV_ALIGN_CENTER, LV_PART_MAIN);
}
