#include "setting.h"

// bool is_ch = false;

/**
 ** @brief 注册switch回调函数
 ** @param *e 结构体参数
 */
static void switch_cb(lv_event_t *e)
{
    lv_obj_t *sw = lv_event_get_target_obj(e);
    bool on = lv_obj_has_state(sw, LV_STATE_CHECKED);
    Com_set_theme(lv_color_hex(SPEED_METER_THEME_COLOR), on);
}

/**
 ** @brief 注册dropdown回调函数
 ** @param *e 结构体参数
 */
static void dropdown_cb(lv_event_t *e)
{
    lv_obj_t *dd = lv_event_get_target_obj(e);
    uint32_t ddx = lv_dropdown_get_selected(dd);
    char buf[32];
    lv_dropdown_get_selected_str(dd, buf, sizeof(buf));
    if(ddx == 0)
    {
        lv_translation_set_language("ch");
        // is_ch = true;
    }
    else
    {
        lv_translation_set_language("en");
        // is_ch = false;
    }
    LV_LOG_USER("dropdown: selected %u (\"%s\")", ddx, buf);
}

/**
 ** @brief 设置setting页面内容
 ** @param parent 父对象
 */
void Tab_pages_setting_set_content(lv_obj_t *parent)
{
    //? 清除默认样式
    Com_clear_default(parent);
    //? 创建setting页面
    lv_obj_t *setting = lv_obj_create(parent);
    //? 清除默认样式
    Com_clear_default(setting);
    lv_obj_set_style_pad_all(setting, 20, LV_PART_MAIN);
    lv_obj_set_size(setting, lv_pct(100), lv_pct(100));
    //? 设置grid布局
    lv_obj_set_layout(setting, LV_LAYOUT_GRID);
    //? 设置general包裹对象网格列/行数
    static const int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static const int32_t row_dsc[] = {50, 50, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(setting, col_dsc, row_dsc);

    //! language区域
    lv_obj_t *language = lv_obj_create(setting);
    //? 清除默认样式
    Com_clear_default(language);
    lv_obj_set_grid_cell(language, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 0, 1);
    //? 设置flex布局
    lv_obj_set_layout(language, LV_LAYOUT_FLEX);
    lv_obj_set_flex_align(language, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //? 创建language的label
    lv_obj_t *language_label = lv_label_create(language);
    lv_label_set_translation_tag(language_label, "Language");
    // 设置language的label的字体大小
    lv_obj_set_style_text_font(language_label, &noto_sans_sc_14, LV_PART_MAIN);
    //? 创建language的dropdown
    lv_obj_t *language_dropdown = lv_dropdown_create(language);
    lv_dropdown_set_options(language_dropdown, "中文\nEnglish");
    lv_obj_set_size(language_dropdown, lv_pct(60), lv_pct(100));
    //? 绑定回调事件
    lv_obj_add_event_cb(language_dropdown, dropdown_cb, LV_EVENT_VALUE_CHANGED, NULL);

    //! Dark mode区域
    lv_obj_t *dark_mode = lv_obj_create(setting);
    //? 清除默认样式
    Com_clear_default(dark_mode);
    lv_obj_set_grid_cell(dark_mode, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 1, 1);
    //? 设置flex布局
    lv_obj_set_layout(dark_mode, LV_LAYOUT_FLEX);
    lv_obj_set_flex_align(dark_mode, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //? 创建dark_mode的label
    lv_obj_t *dark_mode_label = lv_label_create(dark_mode);
    lv_label_set_translation_tag(dark_mode_label, "Dark Mode");
    // 设置dark_mode的label的字体大小
    lv_obj_set_style_text_font(dark_mode_label, &noto_sans_sc_14, LV_PART_MAIN);
    //? 创建dark_mode的switch
    lv_obj_t *dark_mode_switch = lv_switch_create(dark_mode);
    //? 绑定回调事件
    lv_obj_add_event_cb(dark_mode_switch, switch_cb, LV_EVENT_VALUE_CHANGED, NULL);
}
