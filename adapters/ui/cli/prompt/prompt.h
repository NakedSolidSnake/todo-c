#ifndef PROMPT_H
#define PROMPT_H

#include <todo_types.h>
#include <stdbool.h>
#include <stddef.h>
#include <style.h>

void prompt_show (void);
void prompt_read (char *const buffer, const size_t size);
void prompt_read_command (char *const buffer, const size_t size);
void prompt_display_style (const char *const message, style_t style);

#endif /* PROMPT_H */
