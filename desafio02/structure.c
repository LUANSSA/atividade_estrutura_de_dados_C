#include "structure.h"

#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101

struct Structure_ {
    List* name_table[HASH_SIZE];
    List* district_table[HASH_SIZE];
    List* people_table[HASH_SIZE];
    List* children_table[HASH_SIZE];
    List* income_table[HASH_SIZE];
};

static unsigned int hash_string(const char* text)
{
    unsigned int hash = 5381;
    int character;

    while ((character = *text++) != '\0') {
        hash = ((hash << 5) + hash) + (unsigned int) character;
    }

    return hash % HASH_SIZE;
}

static int people_key(int n_people)
{
    if (n_people >= 5) {
        return 5;
    }

    return n_people;
}

static int income_band(double income)
{
    if (income <= 1999.99) {
        return 1;
    }

    if (income <= 3000.00) {
        return 2;
    }

    if (income <= 5000.00) {
        return 3;
    }

    return 4;
}


Structure* create_structure()
{
    Structure* structure;
    int i;

    structure = malloc(sizeof(Structure));

    if (structure == NULL) {
        return NULL;
    }

    for (i = 0; i < HASH_SIZE; i++) {
        structure->name_table[i] = create_list();
        structure->district_table[i] = create_list();
        structure->people_table[i] = create_list();
        structure->children_table[i] = create_list();
        structure->income_table[i] = create_list();

        if (structure->name_table[i] == NULL ||
            structure->district_table[i] == NULL ||
            structure->people_table[i] == NULL ||
            structure->children_table[i] == NULL ||
            structure->income_table[i] == NULL) {

            free_structure(structure);
            return NULL;
        }
    }

    return structure;
}

int add_customer(Structure *structure, int criteria, Customer *customer)
{
    unsigned int index;

    if (structure == NULL || customer == NULL) {
        return 1;
    }

    switch (criteria) {

        case 1:
            index = hash_string(get_name(customer));

            return add_list(
                structure->name_table[index],
                customer
            );

        case 2:
            index = hash_string(get_district(customer));

            return add_list(
                structure->district_table[index],
                customer
            );

        case 3:
            index = (unsigned int) people_key(get_n_people(customer));

            return add_list(
                structure->people_table[index],
                customer
            );

        case 4:
            index = (unsigned int) get_children(customer);

            if (index > 1) {
                return 1;
            }

            return add_list(
                structure->children_table[index],
                customer
            );

        case 5:
            index = (unsigned int) income_band(get_income(customer));

            return add_list(
                structure->income_table[index],
                customer
            );

        default:
            return 1;
    }
}


static List* copy_matching_list(List* source, char* search, int type, int complement)
{
    List* result;
    Node* current;
    Customer* customer;
    int match;

    result = create_list();

    if (result == NULL) {
        return NULL;
    }

    current = get_begin(source);

    while (current != NULL) {
        customer = get_data(current);
        match = 0;

        if (type == 1) {
            if (strcmp(get_name(customer), search) == 0) {
                match = 1;
            }
        }

        else if (type == 2) {
            if (strcmp(get_district(customer), search) == 0) {
                match = 1;
            }
        }

        else if (type == 3) {
            if (people_key(get_n_people(customer)) == complement) {
                match = 1;
            }
        }

        else if (type == 4) {
            if (get_children(customer) == complement) {
                match = 1;
            }
        }

        else if (type == 5) {
            if (income_band(get_income(customer)) == complement) {
                match = 1;
            }
        }

        if (match) {
            if (add_list(result, customer) != 0) {
                free_list(result);
                return NULL;
            }
        }

        current = get_next(current);
    }

    return result;
}

List* retrieve_customer(
    Structure *structure,
    int criteria,
    int complement,
    char *search
)
{
    unsigned int index;
    List* source;

    if (structure == NULL) {
        return NULL;
    }

    switch (criteria) {

        case 1:
            if (search == NULL) {
                return NULL;
            }

            index = hash_string(search);

            source = structure->name_table[index];

            return copy_matching_list(
                source,
                search,
                1,
                0
            );

        case 2:
            if (search == NULL) {
                return NULL;
            }

            index = hash_string(search);

            source = structure->district_table[index];

            return copy_matching_list(
                source,
                search,
                2,
                0
            );

        case 3:
            if (complement < 1 || complement > 5) {
                return NULL;
            }

            source = structure->people_table[complement];

            return copy_matching_list(
                source,
                NULL,
                3,
                complement
            );

        case 4:
            if (complement < 0 || complement > 1) {
                return NULL;
            }

            source = structure->children_table[complement];

            return copy_matching_list(
                source,
                NULL,
                4,
                complement
            );

        case 5:
            if (complement < 1 || complement > 4) {
                return NULL;
            }

            source = structure->income_table[complement];

            return copy_matching_list(
                source,
                NULL,
                5,
                complement
            );

        default:
            return NULL;
    }
}


void free_structure(Structure *structure)
{
    int i;
    Node* current;
    Node* next;
    Customer* customer;

    if (structure == NULL) {
        return;
    }

    /*
     * Primeiro libera os Customer.
     * A tabela de nomes é usada como referência
     * para liberar cada cliente uma única vez.
     */
    for (i = 0; i < HASH_SIZE; i++) {
        current = get_begin(structure->name_table[i]);

        while (current != NULL) {
            customer = get_data(current);

            if (customer != NULL) {
                free(customer);
            }

            current = get_next(current);
        }
    }

    /*
     * Agora liberamos os Nodes e as Lists.
     * free_list() não libera Customer.
     */
    for (i = 0; i < HASH_SIZE; i++) {
        free_list(structure->name_table[i]);
        free_list(structure->district_table[i]);
        free_list(structure->people_table[i]);
        free_list(structure->children_table[i]);
        free_list(structure->income_table[i]);
    }

    free(structure);
}