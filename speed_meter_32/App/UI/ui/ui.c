#include "ui.h"

/**
 ** @brief 初始化屏幕
 */
void __ui_speed_meter_screen_init(void);

/**
 ** @brief 初始化导航栏
 */
void __ui_speed_meter_navbar_init(void);

/**
 ** @brief 初始化所有主题
 */
void __ui_speed_meter_all_sub_init(void);

/**
 ** @brief 初始化tabview
 */
void __ui_speed_meter_tabview_init(void);

/**
 ** @brief 运动状态主题观察者回调
 ** 当 sport_status subject 的值发生变化时执行。
 */
static void sport_status_observer_cb(lv_observer_t *observer, lv_subject_t *subject);

//! 唯一屏幕对象
lv_obj_t *screen;

// extern bool is_ch;

//! 定义主题的结构体指针
speed_meter_sub_t *speed_meter_sub = NULL;

//! 运动状态
char *sport_status[] = {"stop", "running", "pause"};

/**
 ** @brief 初始化UI
 */
void ui_init(void)
{
    //? 初始化所有主题
    __ui_speed_meter_all_sub_init();
    //? 设置主题(theme----颜色大小)
    Com_set_theme(lv_color_hex(SPEED_METER_THEME_COLOR), false);
    //? 初始化翻译
    Com_translate_init();
    //? 初始化屏幕
    __ui_speed_meter_screen_init();
    //? 初始化导航栏
    __ui_speed_meter_navbar_init();
    //? 初始化tabview
    __ui_speed_meter_tabview_init();
}

/**
 ** @brief 初始化屏幕
 */
void __ui_speed_meter_screen_init(void)
{
    //? 获取当前屏幕对象
    screen = lv_screen_active();
    //? 清除默认样式
    Com_clear_default(screen);
    //? 设置布局为flex布局
    lv_obj_set_layout(screen, LV_LAYOUT_FLEX);
    //? 设置flex排列方向
    lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
}

/**
 ** @brief 初始化导航栏
 */
void __ui_speed_meter_navbar_init(void)
{
    //? 创建导航栏
    lv_obj_t *navbar = lv_obj_create(screen);
    lv_obj_set_size(navbar, lv_pct(100), lv_pct(10));
    //? 清除默认样式
    Com_clear_default(navbar);
    //? 设置左右内边距
    lv_obj_set_style_pad_column(navbar, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_row(navbar, 10, LV_PART_MAIN);

    //? 设置布局
    lv_obj_set_layout(navbar, LV_LAYOUT_FLEX);
    //? 设置布局对齐方式
    lv_obj_set_flex_align(navbar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    //? 设置导航栏背景颜色
    lv_obj_set_style_bg_color(navbar, lv_color_hex(SPEED_METER_THEME_COLOR), 0);

    //? 创建三个label
    lv_obj_t *gps_label = lv_label_create(navbar);
    lv_obj_t *sport_status_label = lv_label_create(navbar);
    lv_obj_t *battery_level_label = lv_label_create(navbar);

    //? 绑定主题
    lv_label_bind_text(gps_label, &speed_meter_sub->gps, LV_SYMBOL_GPS " %d");
    // lv_label_bind_text(sport_status_label, &speed_meter_sub->sport_status, "%s");
    lv_subject_add_observer_obj(
        &speed_meter_sub->sport_status,
        sport_status_observer_cb,
        sport_status_label,
        NULL);
    lv_label_bind_text(battery_level_label, &speed_meter_sub->battery_level, "%s");
}

/**
 ** @brief 初始化所有主题
 */
void __ui_speed_meter_all_sub_init(void)
{
    //! 分配内存大小
    speed_meter_sub = lv_malloc_zeroed(sizeof(speed_meter_sub_t));
    /* gps主题 */
    lv_subject_init_int(&speed_meter_sub->gps, 1);
    /* 运动状态主题 */
    lv_subject_init_pointer(&speed_meter_sub->sport_status, sport_status[0]);
    /* 电池电量主题 */
    lv_subject_init_pointer(&speed_meter_sub->battery_level, LV_SYMBOL_BATTERY_2);
    /* 速度主题 */
    lv_subject_init_float(&speed_meter_sub->speed_sub, 0.0f);
    /* 公里数主题 */
    lv_subject_init_float(&speed_meter_sub->mile_sub, 0.00f);
    /* 坡度主题 */
    lv_subject_init_float(&speed_meter_sub->slope_sub, 0.0);
    /* 经纬度主题 */
    lv_subject_init_float(&speed_meter_sub->longitude, 116.36634);
    lv_subject_init_float(&speed_meter_sub->latitude, 40.10217);

    /* 计时主题 */
    lv_subject_init_int(&speed_meter_sub->min_sub, 0);
    lv_subject_init_int(&speed_meter_sub->sec_sub, 0);
}

/**
 ** @brief 初始化tabview
 */
void __ui_speed_meter_tabview_init(void)
{
    //? 创建tabview
    lv_obj_t *tabview = lv_tabview_create(screen);
    lv_obj_set_size(tabview, lv_pct(100), lv_pct(90));
    lv_obj_t *gpx_tab = lv_tabview_add_tab(tabview, "gpx");
    lv_obj_t *general_tab = lv_tabview_add_tab(tabview, "general");
    lv_obj_t *setting_tab = lv_tabview_add_tab(tabview, "setting");
    //? 设置标签栏位置
    lv_tabview_set_tab_bar_position(tabview, LV_DIR_BOTTOM);
    //? 设置标签栏大小
    lv_tabview_set_tab_bar_size(tabview, lv_pct(12));

    // //? 设置tabview默认选中项
    // lv_tabview_set_active(tabview,1,LV_ANIM_OFF);

    //? 中文翻译
    lv_obj_t *tab_bars = lv_tabview_get_tab_bar(tabview);
    lv_label_set_translation_tag(lv_obj_get_child(lv_obj_get_child(tab_bars, 0), 0), "gpx");
    lv_label_set_translation_tag(lv_obj_get_child(lv_obj_get_child(tab_bars, 1), 0), "general");
    lv_label_set_translation_tag(lv_obj_get_child(lv_obj_get_child(tab_bars, 2), 0), "setting");

    //? 设置general页面内容
    Tab_pages_general_set_content(general_tab);

    //? 设置setting页面内容
    Tab_pages_setting_set_content(setting_tab);

    //? 设置gpx页面内容
    Tab_pages_gpx_set_content(gpx_tab);
}

/**
 ** @brief 运动状态主题观察者回调函数
 */
static void sport_status_observer_cb(
    lv_observer_t *observer,
    lv_subject_t *subject
)
{
    if(observer == NULL || subject == NULL) {
        return;
    }

    lv_obj_t *label = lv_observer_get_target_obj(observer);

    if(label == NULL) {
        return;
    }

    const char *status_key =
        (const char *)lv_subject_get_pointer(subject);

    if(status_key == NULL) {
        return;
    }

    lv_label_set_translation_tag(label, status_key);
}

/**
 ** @brief 更新电池电量
 */
void ui_update_battery(bool charg, int percent)
{
    char *battery_level_str[] = {LV_SYMBOL_BATTERY_EMPTY, LV_SYMBOL_BATTERY_1, LV_SYMBOL_BATTERY_2, LV_SYMBOL_BATTERY_3, LV_SYMBOL_BATTERY_FULL};
    if (charg)
    {
        lv_subject_set_pointer(&speed_meter_sub->battery_level, LV_SYMBOL_CHARGE);
    }
    else
    {
        lv_subject_set_pointer(&speed_meter_sub->battery_level, battery_level_str[percent / 20]);
    }
}
