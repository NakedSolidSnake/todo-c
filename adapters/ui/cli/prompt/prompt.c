#include <prompt.h>
#include <stdio.h>
#include <string.h>
#include <common.h>

void prompt_show (void)
{
    prompt_display_style ("(todo) > ", style_fancy, 0);
}

void prompt_read (char *const buffer, const size_t size)
{
    memset (buffer, 0, size);

    fgets (buffer, size - 1, stdin);

    buffer [strlen (buffer) - 1] = '\0';
}
void prompt_read_command (char *const buffer, const size_t size)
{
    prompt_read (buffer, size);

    common_string_to_lower (buffer);
}

void prompt_display_style (const char *const message, style_t style, uint8_t new_lines)
{
    style_set (style);
    printf ("%s", message);
    style_reset ();

    for (uint8_t i = 0; i < new_lines; i++)
    {
        printf ("\n");
    }
}
