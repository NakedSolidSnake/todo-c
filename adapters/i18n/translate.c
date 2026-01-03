#include <translate.h>
#include <string.h>
#include <sat.h>

static text_t texts [] = 
{
    {.type = type_error_command,          .tag = "error.command",          .content = "Invalid command"},
    {.type = type_error_option,           .tag = "error.option",           .content = "Invalid option."},
    {.type = type_error_canceled,         .tag = "error.canceled",         .content = "Canceled"},
    {.type = type_error_task_add,         .tag = "error.task.add",         .content = "Couldn't add a new Task"},
    {.type = type_error_task_remove,      .tag = "error.task.remove",      .content = "Couldn't remove the Task"},
    {.type = type_error_task_update,      .tag = "error.task.update",      .content = "Couldn't update the Task"},
    {.type = type_error_task_complete,    .tag = "error.task.complete",    .content = "Couldn't complete the Task"},
    {.type = type_error_task_id,          .tag = "error.task.id",          .content = "Please. Type a valid ID number."},
    {.type = type_question_exit,          .tag = "question.exit",          .content = "Do you want to quit anyway? (yes/no): "},
    {.type = type_question_task_add,      .tag = "question.task.add",      .content = "You are about to add a new task. Are you sure? (yes/no): "},
    {.type = type_question_task_remove,   .tag = "question.task.remove",   .content = "Would you like to remove? (yes/no): "},
    {.type = type_question_task_update,   .tag = "question.task.update",   .content = "Would you like to update? (yes/no): "},
    {.type = type_question_task_complete, .tag = "question.task.complete", .content = "Would you like to complete? (yes/no): "},
    {.type = type_success_task_add,       .tag = "success.task.add",       .content = "New Task added successfully"},
    {.type = type_success_task_remove,    .tag = "success.task.remove",    .content = "Task removed successfully"},
    {.type = type_success_task_update,    .tag = "success.task.update",    .content = "Task updated successfully"},
    {.type = type_success_task_complete,  .tag = "success.task.complete",  .content = "Task completed successfully"},
    {.type = type_id_remove,              .tag = "id.remove",              .content = "Type the task id to delete or exit to cancel: "},
    {.type = type_id_update,              .tag = "id.update",              .content = "Type the task id to update or exit to cancel: "},
    {.type = type_id_complete,            .tag = "id.complete",            .content = "Type the task id to complete or exit to cancel: "},
    {.type = type_task_name,              .tag = "task.name",              .content = "Type the task name: "},
    {.type = type_task_description,       .tag = "task.description",       .content = "Type the task description: "},
    {.type = type_input_yes,              .tag = "input.yes",              .content = "yes"},
    {.type = type_input_no,               .tag = "input.no",               .content = "no"},
    {.type = type_input_exit,             .tag = "input.exit",             .content = "exit"},
    {.type = type_menu_add,               .tag = "menu.add",               .content = "Add      To add a new task"},
    {.type = type_menu_remove,            .tag = "menu.remove",            .content = "Remove   To remove a task"},
    {.type = type_menu_update,            .tag = "menu.update",            .content = "Update   To update a task"},
    {.type = type_menu_display,           .tag = "menu.display",           .content = "Display  To display tasks"},
    {.type = type_menu_complete,          .tag = "menu.complete",          .content = "Complete To complete a task"},
    {.type = type_menu_exit,              .tag = "menu.exit",              .content = "Exit     To quit application"},
};

static unsigned char text_amount = sizeof (texts) / sizeof (texts [0]);

static sat_json_mapper_t mapper [] = 
{
    { .token = "error.command", .data = texts [type_error_command].content, .type = sat_json_type_string, .size = 100},
    { .token = "error.option", .data = texts [type_error_option].content, .type = sat_json_type_string, .size = 100},
    { .token = "error.canceled", .data = texts [type_error_canceled].content, .type = sat_json_type_string, .size = 100},
    { .token = "error.task.add", .data = texts [type_error_task_add].content, .type = sat_json_type_string, .size = 100},
    { .token = "error.task.remove", .data = texts [type_error_task_remove].content, .type = sat_json_type_string, .size = 100},
    { .token = "error.task.update", .data = texts [type_error_task_update].content, .type = sat_json_type_string, .size = 100},
    { .token = "error.task.complete", .data = texts [type_error_task_complete].content, .type = sat_json_type_string, .size = 100},
    { .token = "error.task.id", .data = texts [type_error_task_id].content, .type = sat_json_type_string, .size = 100},
    { .token = "question.exit", .data = texts [type_question_exit].content, .type = sat_json_type_string, .size = 100},
    { .token = "question.task.add", .data = texts [type_question_task_add].content, .type = sat_json_type_string, .size = 100},
    { .token = "question.task.remove", .data = texts [type_question_task_remove].content, .type = sat_json_type_string, .size = 100},
    { .token = "question.task.update", .data = texts [type_question_task_update].content, .type = sat_json_type_string, .size = 100},
    { .token = "question.task.complete", .data = texts [type_question_task_complete].content, .type = sat_json_type_string, .size = 100},
    { .token = "success.task.add", .data = texts [type_success_task_add].content, .type = sat_json_type_string, .size = 100},
    { .token = "success.task.remove", .data = texts [type_success_task_remove].content, .type = sat_json_type_string, .size = 100},
    { .token = "success.task.update", .data = texts [type_success_task_update].content, .type = sat_json_type_string, .size = 100},
    { .token = "success.task.complete", .data = texts [type_success_task_complete].content, .type = sat_json_type_string, .size = 100},
    { .token = "id.remove", .data = texts [type_id_remove].content, .type = sat_json_type_string, .size = 100},
    { .token = "id.update", .data = texts [type_id_update].content, .type = sat_json_type_string, .size = 100},
    { .token = "id.complete", .data = texts [type_id_complete].content, .type = sat_json_type_string, .size = 100},
    { .token = "task.name", .data = texts [type_task_name].content, .type = sat_json_type_string, .size = 100},
    { .token = "task.description", .data = texts [type_task_description].content, .type = sat_json_type_string, .size = 100},
    { .token = "input.yes", .data = texts [type_input_yes].content, .type = sat_json_type_string, .size = 100},
    { .token = "input.no", .data = texts [type_input_no].content, .type = sat_json_type_string, .size = 100},
    { .token = "input.exit", .data = texts [type_input_exit].content, .type = sat_json_type_string, .size = 100},
    { .token = "menu.add", .data = &texts [type_menu_add].content [9], .type = sat_json_type_string, .size = 90},
    { .token = "menu.remove", .data = &texts [type_menu_remove].content [9], .type = sat_json_type_string, .size = 90},
    { .token = "menu.update", .data = &texts [type_menu_update].content [9], .type = sat_json_type_string, .size = 90},
    { .token = "menu.display", .data = &texts [type_menu_display].content [9], .type = sat_json_type_string, .size = 90},
    { .token = "menu.complete", .data = &texts [type_menu_complete].content [9], .type = sat_json_type_string, .size = 90},
    { .token = "menu.exit", .data = &texts [type_menu_exit].content [9], .type = sat_json_type_string, .size = 90},
};

bool translate_init (translate_t *const object, const char *const filename)
{
    bool status = false;

    if (object != NULL)
    {
        object->texts = texts;
        object->initialized = true;

        if (filename != NULL)
        {
            //load file
            sat_file_t file;
            if (sat_file_open (&file, filename, sat_file_mode_read) == true)
            {
                uint32_t size = sat_file_get_size (&file);
                char *buffer = calloc (1, size + 1);

                sat_file_read (&file, buffer, size);
                sat_file_close (&file);
                
                sat_json_t json;

                sat_json_deserialize (&json, buffer, mapper, text_amount);
            }
        }

        status = true;
    }

    return status;
}

char *translate_get_text_by (const translate_t *const object, type_t type)
{
    char *content = "Not Found";

    if (type >= type_error_command && type <= type_menu_exit)
    {
        content = object->texts [type].content;
    }

    return content;
}

