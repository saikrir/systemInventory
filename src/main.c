#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "sysmodel.h"
#include "common.h"
#include "file.h"

int main(const int argc, char *argv[])
{
    printf("Welcome to System Inventory\n");
    app_args_t *app_args = parse_app_args(argc, argv);
    system_inventory_header_t *header = NULL;
    system_model_t *systems = NULL;

    int fd = 0;
    if (app_args->newFile)
    {

        if ((fd = create_db_file(SYSTEM_DB_FILE)) == STATUS_ERROR)
        {
            free(header);
            free(app_args);
            return STATUS_ERROR;
        }

        if (new_system_header(&header) == STATUS_OK && write_file_header(fd, header) == STATUS_OK)
        {
            puts("INFO::file written");
        }
    }
    else if (app_args->list)
    {
        strcpy(app_args->filePath, SYSTEM_DB_FILE);
        if ((fd = open_db_file(app_args->filePath)) == STATUS_ERROR)
        {
            free(header);
            free(app_args);
            puts("failed to open file ");
            return STATUS_ERROR;
        }

        if (read_file_header(fd, &header) == STATUS_ERROR)
        {
            free(header);
            free(app_args);
            puts("failed to read header");
            return STATUS_ERROR;
        }

        if (header->count == 0)
        {
            printf("No Records \n");
            return STATUS_OK;
        }

        if (read_inv_records(fd, header, &systems) == STATUS_OK)
        {
            print_system_model(&systems[0]);
        }

        printf("File Magic: %u, Version: %d, size: %u, Count: %d \n", header->magic, header->version, header->fileSize, header->count);
    }

    else if (app_args->add)
    {
        if ((fd = open_db_file(SYSTEM_DB_FILE)) == STATUS_ERROR)
        {
            free(header);
            free(app_args);
            puts("failed to open file ");
            return STATUS_ERROR;
        }

        if (read_file_header(fd, &header) == STATUS_ERROR)
        {
            free(header);
            free(app_args);
            puts("failed to read header");
            return STATUS_ERROR;
        }

        system_model_t *system = NULL;
        if (accept_system_model(&system) != STATUS_OK)
        {
            free(header);
            free(system);
            puts("failed to read system model");
            return STATUS_ERROR;
        }
        header->count++;
        write_record(fd, header, system); /* code */
        free(system);
    }

    free(systems);
    free(header);
    free(app_args);
    close_db_file(fd);
    return EXIT_SUCCESS;
}
