#include "customer.h"
#include "list.h"

typedef struct Structure_ Structure;

Structure* create_structure();
int add_customer(Structure *structure, int criteria, Customer *customer);
List* retrieve_customer(Structure *structure, int criteria, int complement, char *search);
void free_structure(Structure *structure);