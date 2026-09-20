#include "list.h"

#include <stdlib.h>

struct List_ {
    Node* begin;
    int quantity;
};

List* create_list()
{
    List* list;

    list = malloc(sizeof(List));

    if (list == NULL) {
        return NULL;
    }

    list->begin = NULL;
    list->quantity = 0;

    return list;
}

int get_quantity(List* list)
{
    if (list == NULL) {
        return -1;
    }

    return list->quantity;
}

Node* get_begin(List* list)
{
    if (list == NULL) {
        return NULL;
    }

    return list->begin;
}

int add_list(List* list, Customer* customer)
{
    Node* new_node;
    Node* current;

    if (list == NULL || customer == NULL) {
        return 1;
    }

    new_node = create_node(customer);

    if (new_node == NULL) {
        return 1;
    }

    if (list->begin == NULL) {
        list->begin = new_node;
    } else {
        current = list->begin;

        while (get_next(current) != NULL) {
            current = get_next(current);
        }

        set_next(current, new_node);
    }

    list->quantity++;

    return 0;
}

void free_list(List* list)
{
    Node* current;
    Node* next;

    if (list == NULL) {
        return;
    }

    current = list->begin;

    while (current != NULL) {
        next = get_next(current);
        free(current);
        current = next;
    }

    free(list);
}