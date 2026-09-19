#include "Com_translate.h"

/**
 ** @brief 初始化翻译
 */
void Com_translate_init(void)
{
    //? 初始化翻译
    /* Arrays are defined `const` to place them in program space instead of RAM. */
    static const char *const languages[] = {"en", "ch", NULL};
    static const char *const tags[] = {"Language", "gpx", "general", "setting", "Dark Mode", "running", "stop", "pause", NULL};
    static const char *const translations[] = {
        "Language",
        "语言",
        "gpx",
        "路书",
        "general",
        "通用",
        "setting",
        "设置",
        "Dark Mode",
        "深色模式",
        "running",
        "运行",
        "stop",
        "停止",
        "pause",
        "暂停",
    };

    lv_translation_add_static(languages, tags, translations);

    //? 设置默认语言为中文
    lv_translation_set_language("ch");
}
