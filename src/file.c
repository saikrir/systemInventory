#include "file.h"
#include <fcntl.h>
#include "common.h"
#include <unistd.h>
#include <stdio.h>

int open_db_file(char *file_name)
{
    int fd = open(file_name, O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return STATUS_ERROR;
    }
    return fd;
}

int create_db_file(char *file_name)
{
    int fd = open(file_name, O_RDWR | O_CREAT, 0644);
    if (fd < 0)
    {
        puts("ERROR:: failed to create new file");
        perror("open");
        return STATUS_ERROR;
    }
    return fd;
}

void close_db_file(int fd) {
    close(fd);
}