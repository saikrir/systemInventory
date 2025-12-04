#include "munit.h"
#include "common.h"
#include "sysmodel.h"
#include <stdio.h>

void test_random_number()
{
    int lower_bound = 9000;
    int upper_bound = 10000;
    int rand = get_random_number(lower_bound, upper_bound);
    printf("Random value %d \n", rand);
    munit_assert_int(rand, >, lower_bound);
    munit_assert_int(rand, <, upper_bound);
}

void test_create_new_model()
{
    system_model_t *model = new_system_model("MacBook Air", "Apple", "ARM-M3", 8, 4.05, 24.0, 256.0, "MacOS 15");
    printf("%s, %s %f Ghz, %f GB \n", model->systemVendor, model->systemName, model->clockSpeedGHZ, model->memoryCapacityGB);
    munit_assert_false(model == NULL);
    free(model);
}

int main(int argc, char const *argv[])
{
    // test_random_number();
    test_create_new_model();
    return 0;
}
