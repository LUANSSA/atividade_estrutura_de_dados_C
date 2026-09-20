#include "node.h"

typedef struct List_ List;

List* create_list();
int get_quantity(List* list);
Node* get_begin(List* list);
int add_list(List* list, Customer* customer);
void free_list(List* list);