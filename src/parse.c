#include "parse.h"
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>

app_args_t *parse_app_args(int argc, char **argv)
{
    app_args_t *app_args = calloc(1, sizeof(app_args_t));

    if (app_args == NULL)
    {
        puts("ERROR: failed to alloc memory for app_args");
        return NULL;
    }

    int c;
    while ((c = getopt(argc, argv, "nf:al")) != -1)
    {
        switch (c)
        {
        case 'n':
            app_args->newFile = true;
            break;

        case 'a':
            app_args->add = true;
            break;
        case 'l':
            app_args->list = true;
            break;
        case 'f':
            strncpy(app_args->filePath, optarg, FILE_PATH_MAX_LENGTH);
            break;
        default:
            break;
        }
    }
    return app_args;
}