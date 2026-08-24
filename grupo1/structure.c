#include <stdlib.h>

#include "structure.h"

Structure* create_structure(void){

    Structure *structure = malloc(sizeof(Structure));

    if (structure == NULL) {
        return NULL;
    }

    structure->front = NULL;
    structure->rear = NULL;
    structure->size = 0;

    return structure;
}

// adiciona uma requisition ao final da fila
int add(Structure *structure, Requisition *requisition){

    if (structure == NULL || requisition == NULL) {
        return 1;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        return 1;
    }

    new_node->requisition = requisition;
    new_node->next = NULL;

    if (structure->rear == NULL) {
        structure->front = new_node;
        structure->rear = new_node;
    } else {
        structure->rear->next = new_node;
        structure->rear = new_node;
    }

    structure->size++;

    return 0;
}

// remove a primeira requisition da fila, segue a ordem 
Requisition* removal(Structure *structure){

    if (structure == NULL || structure->front == NULL) {
        return NULL;
    }

    Node *removed_node = structure->front;
    Requisition *requisition = removed_node->requisition;
    structure->front = removed_node->next;

    //Se a fila ficar vazia, o final tambem deve ser NULL
    if (structure->front == NULL) {
        structure->rear = NULL;
    }

    structure->size--;
    free(removed_node);
    return requisition;
}

//retorna a quantidade de requsition na fila 
int get_size(Structure *structure){

    if (structure == NULL) {
        return -1;
    }

    return structure->size;
}

void free_structure(Structure *structure){
    
    if (structure == NULL) {
        return;
    }

    Node *current = structure->front;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(structure);
}