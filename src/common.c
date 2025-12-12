#include "common.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void trimSpace(char **str)
{
    char *the_string = calloc(strlen(*str), sizeof(char));
    strncpy(the_string, *str, strlen(*str));

    int n_spaces = 0;


    for (int i = 0; i < strlen(the_string); i++)
    {
        if (!isspace(the_string[i])) {
            break;
        }
        n_spaces++;
    }

    the_string+= n_spaces;

    int l_spaces = 0;

    for (size_t i = strlen(the_string) - 1; i > 0; i--)
    {
        if (isspace(the_string[i]))
            l_spaces++;
    }

    the_string[strlen(the_string) - l_spaces] = '\0';

    char *temp = calloc(strlen(the_string), sizeof(char));
    strcpy(temp, the_string);
    free(the_string);

    *str = temp;
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
