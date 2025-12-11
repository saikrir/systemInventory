#ifndef COMMON_H
#define COMMON_H
#define STATUS_OK 1
#define STATUS_ERROR -1
#include <stdio.h>

int get_random_number(int, int);
int accept_string(const char *prompt, char **out, size_t size);
int accept_float(const char *prompt, float *out);
int accept_int(const char *prompt, int *out);
void trimSpace(char **str);

#endif