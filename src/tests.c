#include "common.h"
#include "sysmodel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_random_number()
{
    int lower_bound = 9000;
    int upper_bound = 10000;
    int rand = get_random_number(lower_bound, upper_bound);
    printf("Random value %d \n", rand);
}

void test_create_new_model()
{
    system_model_t *model = new_system_model("MacBook Air", "Laptop", "Apple", "ARM-M3", 8, 4.05, 24.0, 256.0, "MacOS 15");
    printf("%s, %s %f Ghz, %f GB \n", model->systemVendor, model->systemName, model->clockSpeedGHZ, model->memoryCapacityGB);
    free(model);
}

int main_(int argc, char const *argv[])
{
    // system_model_t *model = NULL;

    // if (read_system_model(&model) == STATUS_ERROR)
    // {
    //     puts("failed");
    //     return EXIT_FAILURE;
    // }

    // puts(model->systemName);
    // print_system_model(model);


    char *name = "Sai  ";


    trimSpace(&name);

    printf("Name [%d] -> [%s]\n", strlen(name), name);

    return 0;
}
