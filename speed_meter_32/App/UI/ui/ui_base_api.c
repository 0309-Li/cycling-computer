#include "ui.h"

/**
 ** @brief 事件回调函数
 * @param e 事件对象
 */
void obj_c_event_cb(lv_event_t *e)
{
    lv_log("obj_c_event_cb...");
    void *user_data = lv_event_get_user_data(e);
    void *cur_obj = lv_event_get_current_target(e);
    lv_obj_set_style_bg_color(cur_obj, lv_color_hex(0x000000), LV_PART_MAIN);
}

/**
 ** @brief 滚动事件回调函数
 * @param e 事件对象
 */
static void scroll_event_cb(lv_event_t * e)
{
    lv_log("scroll_event_cb...\n");
    lv_obj_t *obj = lv_event_get_target(e);
    lv_coord_t scroll_x = lv_obj_get_scroll_x(obj);
    lv_log("scroll_x = %d\n", scroll_x);
}

/**
 ** @brief 初始化UI
 */
void ui_init(void)
{
    //! 屏幕对象
    lv_obj_t *screen = lv_screen_active();

    // //? 创建一个对象A
    // lv_obj_t *obj_a = lv_obj_create(screen);
    // //? 设置对象的大小
    // lv_obj_set_size(obj_a, 300, 300);
    // //? 设置对象的背景颜色
    // lv_obj_set_style_bg_color(obj_a, lv_color_hex(0x00ff00), LV_PART_MAIN);
    // //? 设置对象的圆角大小
    // lv_obj_set_style_radius(obj_a, 0, LV_PART_MAIN);
    // //? 设置对象的边框宽度
    // lv_obj_set_style_border_width(obj_a, 0, LV_PART_MAIN);
    // //? 去除内边距宽度
    // lv_obj_set_style_pad_all(obj_a, 0, LV_PART_MAIN);
    // //? 设置对象的位置
    // // lv_obj_set_pos(obj_a, 20, 150);
    // //? 屏幕居中放置
    // lv_obj_align(obj_a, LV_ALIGN_CENTER, 0, 0);

    // //? 创建一个滑动条
    // lv_obj_t *slider = lv_slider_create(screen);
    // //? 设置滑动条的大小
    // lv_obj_set_size(slider, 200, 20);
    // //? 设置滑动条的范围
    // lv_slider_set_range(slider, 0, 10);
    // //? 设置滑动条的初始值
    // lv_slider_set_value(slider, 5, LV_ANIM_OFF);
    // //? 设置滑动条的位置
    // lv_obj_set_pos(slider, 20, 50);

    //! 盒模型案例
    // //? 以A对象为盒模型
    // //? 创建一个对象B
    // lv_obj_t *obj_b = lv_obj_create(obj_a);
    // //? 设置对象的大小
    // lv_obj_set_size(obj_b, 100, 100);
    // //? 设置对象的背景颜色
    // lv_obj_set_style_bg_color(obj_b, lv_color_hex(0xff0000), LV_PART_MAIN);
    // //? 去除圆角
    // lv_obj_set_style_radius(obj_b, 0, LV_PART_MAIN);
    // //? 去除边框宽度
    // lv_obj_set_style_border_width(obj_b, 0, LV_PART_MAIN);
    // lv_obj_set_style_transform_width(obj_b, sw_width, LV_PART_MAIN);

    // //! 样式表案例
    // static lv_style_t style_example;
    // lv_style_init(&style_example);

    // lv_style_set_bg_color(&style_example, lv_color_hex(0xff0000));
    // lv_style_set_radius(&style_example, 0);
    // lv_style_set_border_width(&style_example, 0);
    // lv_style_set_size(&style_example, 100, 100);
    // //? 设置透明度
    // lv_style_set_opa(&style_example, LV_OPA_50);

    // //? 创建一个对象C
    // lv_obj_t *obj_c = lv_obj_create(screen);
    // //? 将样式表应用到对象C
    // lv_obj_add_style(obj_c, &style_example, LV_PART_MAIN);
    // //? 设置对象C的位置
    // lv_obj_set_pos(obj_c, 20, 20);

    // //? 创建一个对象D
    // lv_obj_t *obj_d = lv_obj_create(screen);
    // //? 将样式表应用到对象D
    // lv_obj_add_style(obj_d, &style_example, LV_PART_MAIN);
    // //? 设置对象D的位置
    // lv_obj_set_pos(obj_d, 40, 40);

    // //? 创建一个对象E
    // lv_obj_t *obj_e = lv_obj_create(screen);
    // //? 将样式表应用到对象E
    // lv_obj_add_style(obj_e, &style_example, LV_PART_MAIN);
    // //? 设置对象E的位置
    // lv_obj_set_pos(obj_e, 60, 60);

    // //? 给对象c绑定事件
    // lv_obj_add_event_cb(obj_c, obj_c_event_cb, LV_EVENT_CLICKED, (void *)123);

    // //! flex布局案例
    // lv_obj_t *obj_f = lv_obj_create(screen);
    // lv_obj_set_size(obj_f, 300, 300);
    // lv_obj_set_style_bg_color(obj_f, lv_color_hex(0x00ff00), LV_PART_MAIN);
    // lv_obj_set_style_radius(obj_f, 0, LV_PART_MAIN);
    // lv_obj_set_style_border_width(obj_f, 0, LV_PART_MAIN);
    // lv_obj_set_style_pad_all(obj_f, 0, LV_PART_MAIN);

    // //? 设置为flex布局
    // lv_obj_set_layout(obj_f, LV_LAYOUT_FLEX);
    // //? 设置flex布局的流方向为行/列
    // lv_obj_set_flex_flow(obj_f, LV_FLEX_FLOW_ROW_WRAP);
    // //? 设置flex布局的对齐方式
    // lv_obj_set_flex_align(obj_f, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // for (int i = 0; i < 10; i++)
    // {
    //     lv_obj_t *obj_f_item = lv_obj_create(obj_f);
    //     lv_obj_set_size(obj_f_item, i * 5 + 10, i * 5 + 10);
    // }
    // // for (int i = 0; i < 2; i++)
    // // {
    // //     lv_obj_t *obj_f_item = lv_obj_create(obj_f);
    // //     lv_obj_set_size(obj_f_item, 100, 100);
    // //     //? 设置flex布局的子项的flex属性
    // //     lv_obj_set_flex_grow(obj_f_item, 10);
    // // }

    // //! grid布局案例
    // lv_obj_t *obj_g = lv_obj_create(screen);
    // lv_obj_set_size(obj_g, 400, 400);
    // lv_obj_set_style_bg_color(obj_g, lv_color_hex(0x00ff00), LV_PART_MAIN);
    // lv_obj_set_style_radius(obj_g, 0, LV_PART_MAIN);
    // lv_obj_set_style_border_width(obj_g, 0, LV_PART_MAIN);
    // lv_obj_set_style_pad_all(obj_g, 0, LV_PART_MAIN);
    // lv_obj_set_layout(obj_g, LV_LAYOUT_FLEX);
    // static const int32_t col_dsc[] = {100, 100, 100, LV_GRID_TEMPLATE_LAST};
    // static const int32_t row_dsc[] = {100, 100, 100, LV_GRID_TEMPLATE_LAST};
    // //? 设置grid布局的列描述符
    // lv_obj_set_grid_dsc_array(obj_g, col_dsc, row_dsc);
    // for (int i = 0; i < 9; i++)
    // {
    //     uint8_t col = i % 3;
    //     uint8_t row = i / 3;
    //     lv_obj_t *btn = lv_btn_create(obj_g);
    //     lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);
    //     lv_obj_t *label = lv_label_create(btn);
    //     lv_label_set_text_fmt(label, "C:%d  R:%d", col, row);
    //     lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    //     if (i == 6)
    //         lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row - 1, 2);
    //     else if (i == 8)
    //         lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, col - 1, 2, LV_GRID_ALIGN_STRETCH, row, 1);
    // }

    //! 滚动事件案例
    lv_obj_t *obj_s = lv_obj_create(screen);
    lv_obj_set_size(obj_s, 400, 400);
    lv_obj_set_style_bg_color(obj_s, lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_obj_set_style_radius(obj_s, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj_s, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj_s, 0, LV_PART_MAIN);

    lv_obj_t *obj_s_child = lv_obj_create(obj_s);
    lv_obj_set_size(obj_s_child, 200, 200);
    lv_obj_set_pos(obj_s_child, 300, 0);
    lv_obj_set_style_bg_color(obj_s_child, lv_color_hex(0xff0000), LV_PART_MAIN);

    lv_obj_t *child_one = lv_obj_create(obj_s_child);
    lv_obj_set_size(child_one, 100, 100);
    lv_obj_set_pos(child_one, 100, 0);
    lv_obj_set_style_bg_color(child_one, lv_color_hex(0x0000ff), LV_PART_MAIN);

    //? 禁用滚动链接
    lv_obj_set_flag(obj_s_child, LV_OBJ_FLAG_SCROLL_CHAIN_HOR, false);

    //? 声明滚动事件
    lv_obj_add_event_cb(obj_s, scroll_event_cb, LV_EVENT_SCROLL, NULL);
}
