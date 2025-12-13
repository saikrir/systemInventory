#include "sysmodel.h"
#include "common.h"
#include <string.h>
#include <arpa/inet.h> // For ntohl on Unix-like systems
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

system_model_t *new_system_model(char *systemName, char *systemType, char *vndName, char *cpuType, int nCpuCores, float clockSpeed, float memory, float disk, char *os)
{
    system_model_t *new_model = calloc(1, sizeof(system_model_t));

    if (new_model == NULL)
    {
        puts("ERROR::Malloc failed");
        return NULL;
    }

    new_model->systemID = get_random_number(SYSTEM_ID_MIN, SYSTEM_ID_MAX);
    new_model->clockSpeedGHZ = clockSpeed;
    new_model->memoryCapacityGB = memory;
    new_model->diskCapacityGB = disk;
    new_model->nCpuCores = nCpuCores;

    strncpy(new_model->systemName, systemName, MAX_NAME_LENGTH);
    strncpy(new_model->systemType, systemType, MAX_CPU_OS_LENGTH);
    strncpy(new_model->systemVendor, vndName, MAX_NAME_LENGTH);
    strncpy(new_model->cpuType, cpuType, MAX_CPU_OS_LENGTH);
    strncpy(new_model->os, os, MAX_CPU_OS_LENGTH);

    puts("DEBUG:: all attributes copied ");
    return new_model;
}

int new_system_header(system_inventory_header_t **header_out)
{
    system_inventory_header_t *header = calloc(1, sizeof(system_inventory_header_t));

    if (header == NULL)
    {
        puts("ERROR: failed to allocate memory for System Inventory Header");
        return STATUS_ERROR;
    }

    header->count = 0;
    header->magic = MAGIC;
    header->fileSize = sizeof(system_inventory_header_t) + (sizeof(system_model_t) * header->count);
    header->version = 1;

    *header_out = header;
    return STATUS_OK;
}

int write_file_header(int fd, system_inventory_header_t *header)
{
    // header->count = htons(header-> count);
    // header->magic = htonl(MAGIC);
    // header->fileSize = htonl(sizeof(system_inventory_header_t)  + sizeof(system_model_t) * header->count);
    // header->version = htons(1);
    header->fileSize = sizeof(system_inventory_header_t) + (sizeof(system_model_t) * header->count);
    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(system_inventory_header_t));
    return STATUS_OK;
}

int write_system_model(int fd, system_model_t *record)
{
    write(fd, record, sizeof(system_model_t));
    return STATUS_OK;
}

int read_file_header(int fd, system_inventory_header_t **out_header)
{
    if (fd < 0)
    {
        puts("ERROR:: invalid file descriptor, cannot read");
        return STATUS_ERROR;
    }

    system_inventory_header_t *header = calloc(1, sizeof(system_inventory_header_t));
    if (header == NULL)
    {
        puts("ERROR:: failed to allocate memory for read file");
        return STATUS_ERROR;
    }

    read(fd, header, sizeof(system_inventory_header_t));

    // header->count = ntohs(header->count);
    // header->magic = ntohl(header->magic);
    // header->fileSize = ntohl(header->fileSize);
    // header->version = ntohs(header->version);

    *out_header = header;
    return validate_header(fd, header);
}

int validate_header(int fd, system_inventory_header_t *header)
{

    struct stat db_stat = {0};

    if (fd < 0)
    {
        puts("ERROR:: failed to validate header, invalid file header");
        return STATUS_ERROR;
    }

    if (fstat(fd, &db_stat) != 0)
    {
        puts("ERROR:: failed to fstat");
        perror("fstat");
        return STATUS_ERROR;
    }

    if (!(header->magic == MAGIC && header->version == 1 && db_stat.st_size == header->fileSize))
    {
        puts("WARN:: validation failed");
        return STATUS_ERROR;
    }

    puts("INFO:: file validated");
    return STATUS_OK;
}

void print_system_model(system_model_t *sysinv)
{
    printf("System Inventory ID:[%d]: \n", sysinv->systemID);
    printf("System Name : %s \n", sysinv->systemName);
    printf("System Type : %s \n", sysinv->systemType);
    printf("Vendor Name : %s \n", sysinv->systemVendor);
    printf("CPU Type : %s \n", sysinv->cpuType);
    printf("Number of CPU cores : %d \n", sysinv->nCpuCores);
    printf("CPU Freq : %f \n", sysinv->clockSpeedGHZ);
    printf("Memory Capacity : %f GB \n", sysinv->memoryCapacityGB);
    printf("Disk Capacity : %f GB \n", sysinv->diskCapacityGB);
    printf("OS Name : %s \n", sysinv->os);
}

int accept_system_model(system_model_t **system_model)
{

    char *sysName = calloc(MAX_NAME_LENGTH, sizeof(char));
    char *systemType = calloc(MAX_CPU_OS_LENGTH, sizeof(char));
    char *vendorName = calloc(MAX_NAME_LENGTH, sizeof(char));
    char *cpuType = calloc(MAX_CPU_OS_LENGTH, sizeof(char));
    char *osName = calloc(MAX_CPU_OS_LENGTH, sizeof(char));

    int nCpuCores = 0;
    float clockSpeed = 0;
    float memoryCapacity = 0;
    float diskCapacity = 0;

    accept_string("Please enter SystemName (e.g MyPC-1): ", &sysName, MAX_NAME_LENGTH);
    accept_string("Please enter SystemType (e.g Desktop, Tablet, Phone): ", &systemType, MAX_CPU_OS_LENGTH);
    accept_string("Please enter VendorName (e.g Apple, Samsung): ", &vendorName, MAX_NAME_LENGTH);
    accept_string("Please enter CpuType + Model (e.g AMD Ryzen 7, Intel i7): ", &cpuType, MAX_CPU_OS_LENGTH);
    accept_string("Please enter OSName (e.g iOS, Android): ", &osName, MAX_CPU_OS_LENGTH);
    accept_int("Please enter Number of CPUs: ", &nCpuCores);
    accept_float("Please CPU Clock speed in Ghz: ", &clockSpeed);
    accept_float("Please RAM Capacity in GB: ", &memoryCapacity);
    accept_float("Please Disk Capacity in GB: ", &diskCapacity);

    *system_model = new_system_model(sysName, systemType, vendorName, cpuType, nCpuCores, clockSpeed, memoryCapacity, diskCapacity, osName);

    return STATUS_OK;
}

int write_record(int fd, system_inventory_header_t *header, system_model_t sysinv, system_model_t *systems)
{
    if (fd < 0)
    {
        puts("ERROR:: failed to write system model, invalid file header");
        return STATUS_ERROR;
    }

    systems[header->count - 1] = sysinv;

    write_file_header(fd, header);
    for (int i = 0; i < header->count; i++)
    {
        write_system_model(fd, &systems[i]);
    }

    return STATUS_OK;
}

int read_inv_records(int fd, system_inventory_header_t *header, system_model_t **sysinv)
{
    if (fd < 0)
    {
        puts("ERROR:: failed to write system model, invalid file header");
        return STATUS_ERROR;
    }

    system_model_t *models = calloc(header->count, sizeof(system_model_t));

    read(fd, models, sizeof(system_model_t) * header->count);

    *sysinv = models;
    return STATUS_OK;
}
