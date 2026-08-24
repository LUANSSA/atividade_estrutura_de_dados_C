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

    // Copia do nome, limitando a 40 caracteres
    strncpy(requisition->name, name, 40);
    requisition->name[40] = '\0';

    //Armazenando o codigo 
    requisition->registration = registration;

    strncpy(requisition->procedure, procedure, 10);
    requisition->procedure[10] = '\0';

    //Retorno a requisição criada 
    return requisition;
}

const char* get_name(Requisition *requisition){
    
    //verificando se requisition exite 
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

    // Verifica se o requisition existe antes de ver os dados
    if (requisition == NULL) {
        return NULL;
    }

    return requisition->procedure;
}