#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "requisition.h"

typedef struct Node {
    Requisition *requisition;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int size;
} Structure;

Structure* create_structure(void);

int add(Structure *structure, Requisition *requisition);

Requisition* removal(Structure *structure);

int get_size(Structure *structure);

void free_structure(Structure *structure);

#endif