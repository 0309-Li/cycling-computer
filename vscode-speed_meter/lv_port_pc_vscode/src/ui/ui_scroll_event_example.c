#include "ui.h"

static void scroll_event_cb(lv_event_t *e);

//? 滚动标志位，用于判断是否是代码执行滚动
bool is_code_scroll_flag = false;

//? 滚动对象子对象颜色数组
uint32_t scroll_color[] = {BLUE, RED, GREEN, BLUE, RED};

//? 中间子对象索引
uint8_t center_index = 2;

/**
 ** @brief 初始化UI
 */
void ui_init(void)
{
    //! 轮播图案例
    //! 屏幕对象
    lv_obj_t *screen = lv_screen_active();
    //! 滚动事件案例
    //! 滚动对象
    lv_obj_t *obj_a = lv_obj_create(screen);
    //! 滚动对象设置
    //? 设置滚动对象大小
    lv_obj_set_size(obj_a, 400, 400);
    //? 去除边框，圆角和内边距
    lv_obj_set_style_radius(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(obj_a, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(obj_a, 0, LV_PART_MAIN);

    //? 隐藏滚动条
    lv_obj_set_scrollbar_mode(obj_a, LV_SCROLLBAR_MODE_OFF);

    //? 设置滚动对象布局为Flex布局
    lv_obj_set_layout(obj_a, LV_LAYOUT_FLEX);

    //? 创建滚动对象子对象
    for (int i = 0; i < 3; i++)
    {
        lv_obj_t *child = lv_obj_create(obj_a);
        lv_obj_set_size(child, 400, 400);
        lv_obj_set_style_bg_color(child, lv_color_hex(scroll_color[center_index + i - 1]), LV_PART_MAIN);
        lv_obj_set_style_border_width(child, 0, LV_PART_MAIN);
        lv_obj_set_style_pad_all(child, 0, LV_PART_MAIN);
        lv_obj_set_style_radius(child, 0, LV_PART_MAIN);
    }
    //? 滚动到中间子对象
    lv_obj_scroll_to_x(obj_a, 300, LV_ANIM_OFF);

    //? 声明滚动事件
    lv_obj_add_event_cb(obj_a, scroll_event_cb, LV_EVENT_SCROLL_END, NULL);
}

/**
 ** @brief 滚动事件回调函数
 * @param e 事件对象
 */
static void scroll_event_cb(lv_event_t *e)
{
    //? 滚动事件回调函数
    //? 检查滚动标志位
    if (is_code_scroll_flag)
    {
        is_code_scroll_flag = false;
        return;
    }
    //? 打印滚动事件
    //? 获取滚动对象
    lv_log("scroll_event_cb...\n");
    lv_obj_t *obj = lv_event_get_target(e);
    int32_t scroll_x = lv_obj_get_scroll_x(obj);
    //? 检查滚动方向 --- 用户手指向左，元素向右滚动
    if (scroll_x > 300)
    {
        center_index++;
        if (center_index == 4)
        {
            center_index = 1;
        }
    }
    //? 检查滚动方向 --- 用户手指向右，元素向左滚动
    else if (scroll_x < 300)
    {
        center_index--;
        if (center_index == 0)
        {
            center_index = 3;
        }
    }
    //? 更新滚动对象子对象颜色
    //? 遍历滚动对象子对象
    for (int i = 0; i < 3; i++)
    {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        lv_obj_set_style_bg_color(child, lv_color_hex(scroll_color[center_index + i - 1]), LV_PART_MAIN);
    }
    if (scroll_x > 300)
    {
        is_code_scroll_flag = true;
        //? 颜色改变之后进行回滚一个元素，防止颜色刷新露陷
        lv_obj_scroll_to_x(obj, scroll_x - 300, LV_ANIM_OFF);
    }
    else if (scroll_x < 300)
    {
        is_code_scroll_flag = true;
        //? 颜色改变之后进行回滚一个元素，防止颜色刷新露陷
        lv_obj_scroll_to_x(obj, scroll_x + 300, LV_ANIM_OFF);
    }
}
