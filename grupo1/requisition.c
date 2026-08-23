#include <stdlib.h>
#include <string.h>

#include "requisition.h"

Requisition* create_requisition(const char *name, int registration, const char *procedure){

    // Verifica NULL
    if (name == NULL || procedure == NULL) {
        return NULL;
    }

    Requisition *requisition = malloc(sizeof(Requisition));

    // Verifica NULL
    if (requisition == NULL) {
        return NULL;
    }

    strncpy(requisition->name, name, 40);
    requisition->name[40] = '\0';

    requisition->registration = registration;

    strncpy(requisition->procedure, procedure, 10);
    requisition->procedure[10] = '\0';

    return requisition;
}

const char* get_name(Requisition *requisition){
    
    if (requisition == NULL) {
        return NULL;
    }

    return requisition->name;
}

int get_registration(Requisition *requisition){

    if (requisition == NULL) {
        return -1;
    }

    return requisition->registration;
}

const char* get_procedure(Requisition *requisition){

    if (requisition == NULL) {
        return NULL;
    }

    return requisition->procedure;
}