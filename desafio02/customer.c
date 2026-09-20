#include "customer.h"

#include <stdlib.h>
#include <string.h>

#define CUSTOMER_STRING_SIZE 41

struct Customer_ {
    char name[CUSTOMER_STRING_SIZE];
    char district[CUSTOMER_STRING_SIZE];
    int n_people;
    int children;
    double income;
};

Customer* create_customer(char* name, char* district, int n_people, int children, double income)
{
    Customer* customer;

    if (name == NULL || district == NULL) {
        return NULL;
    }
    customer = malloc(sizeof(Customer));
    
    if (customer == NULL) {
        return NULL;
    }

    strncpy(customer->name, name, CUSTOMER_STRING_SIZE - 1);
    customer->name[CUSTOMER_STRING_SIZE - 1] = '\0';

    strncpy(customer->district, district, CUSTOMER_STRING_SIZE - 1);
    customer->district[CUSTOMER_STRING_SIZE - 1] = '\0';

    customer->n_people = n_people;
    customer->children = children;
    customer->income = income;

    return customer;
}

char* get_name(Customer* customer)
{
    if (customer == NULL) {
        return NULL;
    }

    return customer->name;
}

char* get_district(Customer* customer)
{
    if (customer == NULL) {
        return NULL;
    }

    return customer->district;
}

int get_n_people(Customer* customer)
{
    if (customer == NULL) {
        return -1;
    }

    return customer->n_people;
}

int get_children(Customer* customer)
{
    if (customer == NULL) {
        return -1;
    }

    return customer->children;
}

double get_income(Customer* customer)
{
    if (customer == NULL) {
        return -1.0;
    }

    return customer->income;
}