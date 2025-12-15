#include "linked_list.h"
#include <stdio.h>
#include <string.h>

list_t *new_linked_list()
{
    list_t *list = calloc(1, sizeof(list_t));
    return list;
}

node_t *new_node(void *value)
{
    node_t *node = calloc(1, sizeof(node_t));
    node->next = NULL;
    node->value = value;
    return node;
}

node_t *add_node(list_t *list, void *value)
{
    if (list->root == NULL) {
        list->root = new_node(value);
        return list->root;
    }

    node_t *last_node = list->root;
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }
    node_t *fresh_node = new_node(value);
    last_node->next = fresh_node;
    return fresh_node;
}

void free_node(node_t *node) {
    if (node == NULL) {
        return;
    }
    free(node->value);
    free(node);
}

bool remove_node(list_t *list, node_t *node, bool (*compare)(node_t *, node_t *))
{
    if (size(list) == 1) {
        puts("WARN: cannot delete root node");
        return false;
    }

    // compare root
    if (compare(list->root, node)) {
        node_t *prev_root = list->root;
        list->root = node;
        list -> root->next = prev_root->next;
        free(prev_root);
        return true;
    }

    node_t *p_node = list->root;

    bool found = compare(p_node->next, node);
    while (!found)
    {
        p_node = p_node->next;
        found = compare(p_node->next, node);
    }
    if (!found) {
        return false;
    }
    p_node->next = node->next;
    free(node);
    return true;
}


void print_nodes(list_t *list)
{
    if (list->root == NULL)
    {
        free(list);
        return;
    }

    node_t *last_node = list->root;

    while (last_node != NULL)
    {
        char *val = (char *)last_node->value;
        printf("Val %s\n", val);
        last_node = last_node->next;
    }
}

size_t size(list_t *list) {
   size_t size = 0;

    node_t *last_node = list->root;

    while (last_node != NULL) {
        last_node = last_node->next;
        size++;
    }
    return size;
}

node_t* get_node(list_t *list, size_t index) {
    if (list->root == NULL) {
        return NULL;
    }

    size_t l_size = size(list)-1; // make it index friendly
    if (index > l_size) {
        puts("WARN: index out of bounds");
        return NULL;
    }

    const node_t *node = list->root;
    size_t ctr =0;
    while (ctr <= l_size && node!= NULL) {
        if (ctr == index) {
            return node;
        }
        node = node->next;
        ctr++;
    }
    return NULL;
}

void* get(list_t *list, size_t index) {
    node_t *node = get_node(list, index);
    if (node == NULL) {
        return NULL;
    }
    return node->value;
}

void set(list_t *list, size_t index, void *value) {
    if (list->root == NULL) {
        return;
    }
    node_t *node = get_node(list, index);
    void *old_mem  = node->value;

    node->value = value;
    free(old_mem);
}

void free_list(list_t *list)
{

    if (list->root == NULL)
    {
        free(list);
        return;
    }

    node_t *last_node = list->root;
    node_t *prev_node = NULL;

    while (last_node->next != NULL)
    {
        prev_node = last_node;
        last_node = last_node->next;
    }
    if (prev_node == NULL) {
        return;
    }
    prev_node->next = NULL;
    free(last_node);
    free_list(list);
}

