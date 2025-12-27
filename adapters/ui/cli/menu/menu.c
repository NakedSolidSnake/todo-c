#include <menu.h>
#include <stdio.h>

char *menu_logo (void)
{
    static char *logo = 
    {
        " _____         _         _     _     _ \n"
        "|_   _|       | |       | |   (_)   | |\n"
        "  | | ___   __| | ___   | |    _ ___| |\n"
        "  | |/ _ \\ / _` |/ _ \\  | |   | / __| __|\n"
        "  | | (_) | (_| | (_) | | |___| \\__ \\ |_\n"
        "  \\_/\\___/ \\__,_|\\___/  \\_____/_|___/\\__|\n\n"
    };

    return logo;
}

char *menu_show (translate_t *translate)
{
    static char options [1024] = {0};
    static bool initialized = false;

    if (initialized == false)
    {
        snprintf (options, 1023, "%s%s%s%s%s%s%s", translate_get_text_by (translate, type_menu_add),
                                                   translate_get_text_by (translate, type_menu_remove),
                                                   translate_get_text_by (translate, type_menu_update),
                                                   translate_get_text_by (translate, type_menu_display),
                                                   translate_get_text_by (translate, type_menu_complete),
                                                   translate_get_text_by (translate, type_menu_save),
                                                   translate_get_text_by (translate, type_menu_exit));

        initialized = true;
    }

    return options;   
}