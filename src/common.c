#include "common.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void trimSpace(char **str)
{
    char *temp = *str;

    if (str == NULL || strlen(temp) == 0)
    {
        return;
    }

    size_t len = strlen(temp);
    int lPad = 0, rPad = 0;

    for (; lPad < len - 1; lPad++)
    {
        if (!isspace(temp[lPad]))
        {
            break;
        }
    }

    for (size_t endIndex = len - 1; endIndex > 0; endIndex--, rPad++)
    {
        if (!isspace(temp[endIndex]))
        {
            break;
        }
    }

    if (lPad == 0 && rPad == 0)
    {
        return;
    }

    int newLength = (len - (lPad + rPad));

    char *newstr = calloc(newLength + 1, sizeof(char));

    strncpy(newstr, temp + lPad, newLength);

    newstr[newLength] = '\0';
    *str = newstr;
}

int get_random_number(int lower_bound, int upper_bound)
{
    srand((unsigned)time(NULL));
    return rand() % (upper_bound + 1 - lower_bound) + lower_bound;
}

int accept_string(const char *prompt, char **out, size_t size)
{
    char *new_value = calloc(size, sizeof(char));
    if (new_value == NULL)
    {
        puts("ERROR: could not allocate memory for accepting user input");
        free(new_value);
        return STATUS_ERROR;
    }

    int inputLength = 0;
    do
    {
        printf("%s", prompt);
        fgets(new_value, size, stdin);
        inputLength = strlen(new_value) - 1; // accounting for \n char
        if (!inputLength)
        {
            puts("invalid input, please try again");
        }

    } while (!inputLength || isspace(new_value[0]) == true);
    new_value[inputLength] = '\0';
    strncpy(*out, new_value, size);
    free(new_value);
    return STATUS_OK;
}

int accept_float(const char *prompt, float *out)
{
    printf("%s", prompt);
    scanf("%f", out);
    return STATUS_OK;
}

int accept_int(const char *prompt, int *out)
{
    printf("%s", prompt);
    scanf("%d", out);
    return STATUS_OK;
}
