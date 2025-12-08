#include <stdio.h>
#include <stdlib.h>
#include <parse.h>
#include "sysmodel.h"
#include "common.h"
#include "file.h"

int main(int argc, char *argv[])
{
    printf("Welcome to System Inventory\n");
    app_args_t *app_args = parse_app_args(argc, argv);
    system_inventory_header_t *header = NULL;

    int fd = 0;
    if (app_args->newFile)
    {

        if ((fd = create_db_file(SYSTEM_DB_FILE)) == STATUS_ERROR)
        {
            return STATUS_ERROR;
        }

        if (new_system_header(&header) == STATUS_OK && write_file_header(fd, header) == STATUS_OK)
        {
            puts("INFO::file written");
        }
    }
    else
    {
        if ((fd = open_db_file(app_args->filePath)) == STATUS_ERROR)
        {
            puts("failed to open file ");
            return STATUS_ERROR;
        }

        if (read_file_header(fd, &header) == STATUS_ERROR)
        {
            puts("failed to read header");
            return STATUS_ERROR;
        }

        printf("File Magic: %u, Version: %d, size: %u, Count: %d \n", header->magic, header->version, header->fileSize, header->count);
    }

    free(header);
    free(app_args);
    return EXIT_SUCCESS;
}