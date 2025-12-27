#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include <stdbool.h>

#define TRANSLATE_CONTENT_SIZE      100
typedef enum 
{
    type_error_command,
    type_error_option,
    type_error_canceled,
    type_error_task_add,
    type_error_task_remove,
    type_error_task_update,
    type_error_task_complete,
    type_error_task_id,
    type_question_modification,
    type_question_task_add,
    type_question_task_remove,
    type_question_task_update,
    type_question_task_complete,
    type_success_task_add,
    type_success_task_remove,
    type_success_task_update,
    type_success_task_complete,
    type_id_remove,
    type_id_update,
    type_id_complete,
    type_task_name,
    type_task_description,
    type_input_yes,
    type_input_no,
    type_input_exit,
    type_menu_add,
    type_menu_remove,
    type_menu_update,
    type_menu_display,
    type_menu_complete,
    type_menu_save,
    type_menu_exit,

} type_t;

typedef struct 
{
    type_t type;
    const char *tag;
    char content [TRANSLATE_CONTENT_SIZE + 1];
} text_t;

typedef struct 
{
    text_t *texts;
    bool initialized;
} translate_t;

bool translate_init (translate_t *object, char *filename);
char *translate_get_text_by (translate_t *object, type_t type);

#endif/* TRANSLATE_H_ */

