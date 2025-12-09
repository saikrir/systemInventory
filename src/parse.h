#ifndef PARSE_H
#define PARSE_H
#include <stdbool.h>
#define FILE_PATH_MAX_LENGTH 96

typedef struct AppArgs
{
    bool newFile;
    char filePath[FILE_PATH_MAX_LENGTH];
} app_args_t;
app_args_t *parse_app_args(int, char **);

#endif