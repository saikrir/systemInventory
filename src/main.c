#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "sysmodel.h"
#include "common.h"
#include "file.h"
#include "linked_list.h"

int main(const int argc, char *argv[])
{
    printf("Welcome to System Inventory\n");
    app_args_t *app_args = parse_app_args(argc, argv);
    system_inventory_header_t *header = NULL;
    list_t *sysList = NULL;

    int fd = 0;
    if (app_args->newFile)
    {

        if ((fd = create_db_file(SYSTEM_DB_FILE)) < 2)
        {
            free(header);
            free(app_args);
            return STATUS_ERROR;
        }

        if (new_system_header(&header) == STATUS_OK && write_file_header(fd, header) == STATUS_OK)
        {
            puts("INFO::file written");
        }
        sysList = new_linked_list();
    }
    else if (app_args->list)
    {
        fd = open_db_file(app_args->filePath);
        printf("Will open %s, fd[%d] \n", app_args->filePath, fd);
        if (fd < 0)
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

        printf("Found [%d] Records \n", header->count);
        printf("--------------------------------------------------------------------\n");

        if (header->count == 0)
        {
            return STATUS_OK;
        }

        sysList = new_linked_list();

        if (read_inv_records(fd, header, sysList) == STATUS_OK)
        {
            for (int i = 0; i < size(sysList); i++)
            {
                system_model_t *sys_node = get(sysList, i);
                if (sys_node != NULL) {
                    print_system_model(sys_node);
                    printf("--------------------------------------------------------------------\n");
                }

            }
        }
    }
    else if (app_args-> search)
    {
        fd = open_db_file(SYSTEM_DB_FILE);
        if (fd < 0)
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
            return STATUS_OK;
        }

        sysList = new_linked_list();

        if (read_inv_records(fd, header, sysList) == STATUS_OK)
        {
           list_t *search_results = find_system_model(sysList, app_args->search_str);
            if (search_results == NULL) {
                puts("failed to find system model");
            }

            int s_size = size(search_results);

            printf("Search Found [%d] Records \n", s_size );
            printf("--------------------------------------------------------------------\n");
            for (int i = 0; i < size(search_results); i++) {
                system_model_t *sys_node = get(search_results, i);
                print_system_model(sys_node);
                printf("--------------------------------------------------------------------\n");
            }
            free_list(search_results);
        }
    }

    else if (app_args->add)
    {
        if ((fd = open_db_file(SYSTEM_DB_FILE)) < 0)
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
        sysList = new_linked_list();
        if (read_inv_records(fd, header, sysList) == STATUS_ERROR)
        {
            free(header);
            free(app_args);
            puts("failed to records");
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
        add_node(sysList, system);
        write_record(fd, header, sysList);
    }

    if (sysList!= NULL) {
        puts("will free sysList");
        free_list(sysList);
    }
    free(header);
    free(app_args);
    close_db_file(fd);
    return EXIT_SUCCESS;
}
