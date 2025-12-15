#ifndef PARSE_H
#define PARSE_H
#include <stdbool.h>

#include "sysmodel.h"
#define FILE_PATH_MAX_LENGTH 96

typedef struct AppArgs
{
    bool newFile;
    bool list;
    bool add;
    bool delete;
    bool search;
    char filePath[FILE_PATH_MAX_LENGTH];
    char search_str[MAX_NAME_LENGTH];
} app_args_t;
app_args_t *parse_app_args(int, char **);

#endif