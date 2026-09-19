#include "Com_api.h"

/**
 ** @brief 清除默认值
 */
void Com_clear_default(lv_obj_t *obj)
{
    //! 清除默认值，包括圆角、边框、内边距(外围和行 / 列)等
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN);
}

/**
 ** @brief 设置主题
 */
void Com_set_theme(lv_color_t theme_color, bool is_dark)
{
    lv_display_t *display = lv_display_get_default();
    lv_theme_t *th = lv_theme_default_init(display,
                                           theme_color,
                                           theme_color,
                                           is_dark,
                                           &noto_sans_sc_14);
    lv_display_set_theme(display, th);
}
