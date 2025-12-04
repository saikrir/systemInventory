#include "sysmodel.h"
#include "common.h"
#include <string.h>

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
