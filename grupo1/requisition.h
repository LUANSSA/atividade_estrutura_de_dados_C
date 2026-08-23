#ifndef REQUISITION_H
#define REQUISITION_H

typedef struct {
    char name[41];
    int registration;
    char procedure[11];
} Requisition;

Requisition* create_requisition(
    const char *name,
    int registration,
    const char *procedure
);

const char* get_name(Requisition *requisition);
int get_registration(Requisition *requisition);
const char* get_procedure(Requisition *requisition);

#endif