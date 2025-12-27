#include <common.h>
#include <ctype.h>
#include <string.h>

bool common_is_a_number (const char *const string)
{
    bool status = true;

    if (string != NULL)
    {
        size_t length = strlen (string);

        for (size_t i = 0; i < length; i ++)
        {
            /*
                if some char is not a number the loop will stop and fail
            */
            if (isdigit (string [i]) == 0)
            {
                status = false;
                break;
            }
        }
    }

    return status;
}

void common_string_to_lower (char *string)
{
    for (int i = 0; i < strlen (string); i ++)
    {
        string [i] = tolower (string [i]);
    }
}
