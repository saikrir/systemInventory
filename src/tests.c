#include "common.h"
#include "sysmodel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

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

bool compare_nodes(node_t *node1, node_t *node2) {

    if (node1==NULL && node2==NULL) return false;

    char *v1 = (char *) node1->value;
    char *v2 = (char *) node2->value;

    if (v1!= NULL && v2 != NULL && strcmp(v1, v2) == 0) {
        return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{

    list_t *list = new_linked_list();
    node_t *n0 = add_node(list, "Sai");
    node_t *n1 = add_node(list, "Krishna");
    node_t *n2 = add_node(list, "Rao");
    node_t *n3 = add_node(list, "Katterishetty");

   set(list,0, "Sunny");
    print_nodes(list);


   free_list(list);

    return 0;
}
