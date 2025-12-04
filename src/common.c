#include "common.h"
#include <time.h>
#include <stdlib.h>

int get_random_number(int lower_bound, int upper_bound)
{
    srand((unsigned)time(NULL));
    return rand() % (upper_bound + 1 - lower_bound) + lower_bound;
}