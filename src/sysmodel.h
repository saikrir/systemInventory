#ifndef SYSMODEL_H
#define SYSMODEL_H
#include <stdint.h>

#define MAGIC 0x5341494b
#define SYS_INV_TXN_SUCCESS 0
#define SYS_INV_TXN_FAILURE -1
#define MAX_NAME_LENGTH 64
#define MAX_CPU_OS_LENGTH 32
#define SYSTEM_ID_MIN 7000
#define SYSTEM_ID_MAX 8000
#define SYSTEM_DB_FILE system.db "

struct SystemInventoryHeader
{
    uint32_t magic;
    uint16_t version;
    uint16_t count;
    uint32_t fileSize;
};

struct SystemModel
{
    int systemID;
    char systemName[MAX_NAME_LENGTH];
    char systemType[MAX_CPU_OS_LENGTH];
    char systemVendor[MAX_NAME_LENGTH];
    char cpuType[MAX_CPU_OS_LENGTH];
    int nCpuCores;
    float clockSpeedGHZ;
    float memoryCapacityGB;
    float diskCapacityGB;
    char os[MAX_CPU_OS_LENGTH];
};

typedef struct SystemModel system_model_t;
typedef struct SystemInventoryHeader system_inventory_header_t;

system_model_t *new_system_model(char *systemName, char *systemType, char *vndName, char *cpuType, int nCpuCores, float clockSpeed, float memory, float disk, char *os);

int new_system_header(system_inventory_header_t **);

int write_file_header(int fd, system_inventory_header_t *);

int read_file_header(int fd, system_inventory_header_t **out_header);

int validate_header(int fd, system_inventory_header_t *header);

void print_system_model(system_model_t *sysinv);

int read_system_model(system_model_t **system_model);

int write_record(int fd, system_inventory_header_t *header, system_model_t *sysinv);

int read_inv_records(int fd, system_inventory_header_t *header, system_model_t **sysinv);

#endif
