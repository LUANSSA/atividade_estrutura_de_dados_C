#include "customer.h"

typedef struct Node_ Node;

Node* create_node(Customer* data);
Customer* get_data(Node* n);
Node* get_next(Node* n);
int set_next(Node* n, Node* next);