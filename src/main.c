#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "sysmodel.h"
#include "common.h"
#include "file.h"


system_model_t* accept_user_input() {

    system_model_t *sys_inv = calloc(1 ,sizeof(system_model_t));

    printf("Please enter system name: ");
    fgets(sys_inv->systemName, MAX_NAME_LENGTH, stdin);
    sys_inv->systemName[strlen(sys_inv->systemName) - 1] = '\0';


    printf("Please enter vendor: ");
    fgets(sys_inv->systemVendor, MAX_NAME_LENGTH, stdin);
    sys_inv->systemVendor[strlen(sys_inv->systemVendor) - 1] = '\0';


    printf("Please enter cpuType: ");
    fgets(sys_inv->cpuType, MAX_CPU_OS_LENGTH, stdin);
    sys_inv->cpuType[strlen(sys_inv->cpuType) - 1] = '\0';


    printf("Please enter number of cpu cores: ");
    int x =scanf("%d", &sys_inv->nCpuCores);
    printf("CPU Core Result: %d ", x);


    printf("Please enter system clockSpeed in Ghz: ");
    scanf("%f", &sys_inv->clockSpeedGHZ);


    printf("Please enter memory capacity in GB: ");
    scanf("%f", &sys_inv->memoryCapacityGB);


    printf("Please enter disk capacity in GB: ");
    scanf("%f", &sys_inv->diskCapacityGB);

    printf("Please enter OS Name: ");
    fgets(sys_inv->os, MAX_CPU_OS_LENGTH, stdin);
    sys_inv->os[strlen(sys_inv->os) - 1] = '\0';

    return sys_inv;
}

void print_system_model(system_model_t *sysinv) {
    printf("System Inventory : \n");
    printf("System Name %s \n", sysinv->systemName);
    printf("Vendor Name %s \n", sysinv->systemVendor);
    printf("CPU Type %s \n", sysinv->cpuType);
    printf("Number of CPU cores %d \n", sysinv->nCpuCores);
    printf("CPU Freq %f \n", sysinv->clockSpeedGHZ);
    printf("Memory Capacity %f GB \n", sysinv->memoryCapacityGB);
    printf("Disk Capacity %f GB \n", sysinv->diskCapacityGB);
    printf("OS Name %s \n", sysinv->os);
}

int main(const int argc, char *argv[])
{
    printf("Welcome to System Inventory\n");
    app_args_t *app_args = parse_app_args(argc, argv);
    system_inventory_header_t *header = nullptr;

    system_model_t *val = accept_user_input();

    print_system_model(val);

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
    else
    {
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

        printf("File Magic: %u, Version: %d, size: %u, Count: %d \n", header->magic, header->version, header->fileSize, header->count);
    }

    free(header);
    free(app_args);
    return EXIT_SUCCESS;
}