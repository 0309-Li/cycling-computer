#include "ui.h"

static void sub_observer_cb(lv_observer_t * observer, lv_subject_t * subject);

/**
 ** @brief 初始化UI
 */
void ui_init(void)
{
    //! 监视者案例
    lv_obj_t *screen = lv_screen_active();
    lv_obj_t *obj_a = lv_obj_create(screen);
    //? 设置对象大小
    lv_obj_set_size(obj_a, 400, 400);
    //? 去除边框，圆角和内边距
    lv_obj_set_style_radius(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(obj_a, 0, LV_PART_MAIN);

    //? 隐藏滚动条
    lv_obj_set_scrollbar_mode(obj_a, LV_SCROLLBAR_MODE_OFF);

    //! 初始化主题
    static lv_subject_t subject;
    lv_subject_init_int(&subject,3);
    lv_subject_add_observer(&subject,sub_observer_cb,NULL);

    //? 创建滑动条
    lv_obj_t *silder = lv_slider_create(obj_a);
    lv_slider_set_range(silder,0,10);
    lv_obj_set_size(silder, 100, 10);
    lv_obj_set_pos(silder, 50, 30);
    lv_slider_bind_value(silder,&subject);

    //? 创建文本标签
    lv_obj_t *label = lv_label_create(obj_a);
    lv_label_bind_text(label,&subject,"sub_value = %d");
}

/**
 ** @brief 监视者回调函数
 ** @param observer 监视者对象
 ** @param subject 监视主题对象
 */
static void sub_observer_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    lv_log("sub_observer_cb...\n");
    int32_t sub_value = lv_subject_get_int(subject);
    lv_log("sub_value = %d\n",sub_value);
}
