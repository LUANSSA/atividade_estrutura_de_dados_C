#include "node.h"

#include <stdlib.h>

struct Node_ {
    Customer* data;
    Node* next;
};

Node* create_node(Customer* data)
{
    Node* node;

    if (data == NULL) {
        return NULL;
    }

    node = malloc(sizeof(Node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

Customer* get_data(Node* n)
{
    if (n == NULL) {
        return NULL;
    }

    return n->data;
}

Node* get_next(Node* n)
{
    if (n == NULL) {
        return NULL;
    }

    return n->next;
}

int set_next(Node* n, Node* next)
{
    if (n == NULL) {
        return 1;
    }

    n->next = next;

    return 0;
}