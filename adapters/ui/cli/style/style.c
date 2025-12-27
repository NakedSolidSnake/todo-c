#include <style.h>
#include <stdint.h>
#include <stdio.h>

#define STYLE_COLOR_RESET   "\033[0m"
#define STYLE_COLOR_RED     "\033[0;31m"
#define STYLE_COLOR_GREEN   "\033[0;32m"
#define STYLE_COLOR_CYAN    "\033[0;36m"
#define STYLE_COLOR_WHITE   "\033[0;37m"

typedef struct 
{
    style_t style;
    char *code;
} style_pair_t;

static style_pair_t pairs [] = 
{
    {.style = style_error,   .code = STYLE_COLOR_RED},
    {.style = style_success, .code = STYLE_COLOR_GREEN},
    {.style = style_fancy,   .code = STYLE_COLOR_CYAN},
    {.style = style_default, .code = STYLE_COLOR_WHITE},
};

static uint8_t style_amount = sizeof (pairs) / sizeof (pairs [0]);

static char *style_set_style (style_t style)
{
    char *code = STYLE_COLOR_WHITE;

    for (uint8_t i = 0; i < style_amount; i ++)
    {
        if (style == pairs [i].style)
        {
            code = pairs [i].code;
            break;
        }
    }

    return code;
}

void style_set (style_t style)
{
    printf ("%s", style_set_style (style));
}

void style_reset (void)
{
    printf ("%s", STYLE_COLOR_RESET);
}