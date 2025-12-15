#pragma once
#include <stdlib.h>
#include <stdbool.h>
typedef struct Node node_t;

typedef struct LinkedList
{
    node_t *root;
} list_t;

typedef struct Node
{
    void *value;
    node_t *next;
} node_t;

list_t *new_linked_list();
node_t *new_node(void *value);

node_t *add_node(list_t *list, void *value);
bool remove_node(list_t *list, node_t *node, bool (*fptr)(node_t *, node_t *));

void* get(list_t *list, size_t index);
void set(list_t *list, size_t index, void *value);

void print_nodes(list_t *list);
size_t size(list_t *list);
void free_list(list_t *list);

