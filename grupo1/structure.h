#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "requisition.h"

/* nó da estrutura - cada nó armazena uma requisição e aponta p/
   o próximo nó
*/ 

typedef struct Node {
    Requisition *requisition; // requisição armazenada
    struct Node *next; // ponteiro para o próximo nó
} Node;

/* estrutura que representa a fila de requisições
   'front' aponta p/ o primeiro e 'rear' p/ o último da fila
*/

typedef struct {
    Node *front;
    Node *rear;
    int size; // quantidade de elementos na fila
} Structure;

// cria e inicia uma nova estrutura
Structure* create_structure(void);

// adiciona uma requisição ao final dessa estrutura
int add(Structure *structure, Requisition *requisition);

// remove e retorna a primeira requisição dessa estrutura
Requisition* removal(Structure *structure);

// retorna a quantidade de elementos dessa estrutura
int get_size(Structure *structure);

// libera a memória utilizada pela estrutura
void free_structure(Structure *structure);

#endif