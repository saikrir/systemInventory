#ifndef FILE_H
#define FILE_H

int open_db_file(char *file_name);
int create_db_file(char *file_name);
void close_db_file(int fd);

#endif