#include "sysmodel.h"
#include "common.h"
#include <string.h>
#include <arpa/inet.h> // For ntohl on Unix-like systems
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

system_model_t *new_system_model(char *systemName, char *vndName, char *cpuType, int nCpuCores, float clockSpeed, float memory, float disk, char *os)
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
    strncpy(new_model->systemVendor, vndName, MAX_NAME_LENGTH);
    strncpy(new_model->cpuType, cpuType, MAX_CPU_OS_LENGTH);
    strncpy(new_model->os, os, MAX_CPU_OS_LENGTH);

    puts("DEBUG:: all attributes copied");
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
    header->fileSize = sizeof(system_inventory_header_t);
    header->version = 1;

    *header_out = header;
    return STATUS_OK;
}

int write_file_header(int fd, system_inventory_header_t *header)
{
    header->count = htons(0);
    header->magic = htonl(MAGIC);
    header->fileSize = htonl(sizeof(system_inventory_header_t));
    header->version = htons(1);
    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(system_inventory_header_t));
    close(fd);
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

    header->count = ntohs(header->count);
    header->magic = ntohl(header->magic);
    header->fileSize = ntohl(header->fileSize);
    header->version = ntohs(header->version);

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

    if (!(header->magic == MAGIC && header->fileSize == db_stat.st_size && header->version == 1))
    {
        puts("WARN:: validation failed");
        return STATUS_ERROR;
    }

    puts("INFO:: file validated");
    return STATUS_OK;
}