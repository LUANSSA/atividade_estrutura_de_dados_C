#define LONG_NAME "This is a very long name that shouldn't be allowed when creating the request, or at least the name should have been truncated."
#define LONG_DIST "This is a very long procedure name that should not be allowed when creating the request, or at least the name should have been truncated."

#define CUS_FUNC "customer.c -> create_customer function"
#define CR_CUS_ERR "Create customer fail"
#define NULL_NAME "Customer creation failed because it created customer with null name"
#define NULL_DIST "Customer creation failed because it created customer with null district"
#define GN_FUN "customer.c -> get_name function"
#define GD_FUN "customer.c -> get_district function"
#define GP_FUN "customer.c -> get_n_people function"
#define GC_FUN "customer.c -> get_children function"
#define GI_FUN "customer.c -> get_income function"
#define GT_ERR "Getter returns a different value than expected."
#define NOD_FUNC "node.c -> create_node function"
#define CR_NOD_ERR "Create invalid node with NULL customer"
#define GT_DATA "node.c -> get_data function"
#define GT_NEXT "node.c -> get_next function"
#define ST_NEXT "node.c -> set_next function"
#define ST_NEXT_ERR "Fail in set next of the node"
#define LIS_FUNC "list.c -> create_list function"
#define GT_LIS_B "list.c -> get_begin function"
#define GT_LIS_QT "list.c -> get_quantity function"
#define ADD_LIS "list.c -> add_list function"
#define ADD_LIS_ERR "Fail to add customer in list"
#define STR_FUNC "structure.c -> create_structure function"
#define CR_STR_ERR "Create structure fail"
#define STR_CUS_ADD "structure.c -> add_customer function"
#define ADD_CUS_ERR "add customer fail"
#define STR_RT_CUS "structure.c -> retrieve_customer function"
#define RT_CUS_ERR "retrieve customer incorrect"
#define FREE_STR "structure.c -> free_structure function"
#define RT_CUS_IN_ERR "Customer outside the expected income range"
#define RT_CUS_NR_ERR "The number of customers recovered is different from what was expected"
#define TR_NULL "Lack of handling for NULL argument"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include "customer.h"
#include "structure.h"
#include "list.h"
#include "node.h"

/*
 * Part of the code with a structure for error handling and requisition presentation.
 */

typedef struct Error_ {
    char origin[51];
    char description[81];
} Error;

Error *list_errors = NULL;
int count_errors = 0;

void show_error(Error e) {
    fprintf(stderr, "%-50s - %-80s\n", e.origin, e.description);
}

void show_test_report(int quantity) {
    int i;
    fprintf(stderr, "---------------------( Error Report )--------------------------------------\n");
    fprintf(stderr, "--> Total Errors: %d\n", quantity);
    fprintf(stderr, "List Errors:\n");
    fprintf(stderr, "---------------------------------------------------------------------------\n");
    fprintf(stderr, "  %-50s + %-80s\n", "Origin", "Description");
    for(i = 0; i < quantity; i++) {
        fprintf(stderr, " .%-50s   %-80s\n", list_errors[i].origin, list_errors[i].description);
    }
    fprintf(stderr, "---------------------------------------------------------------------------\n");
}

/*
 * Handling functions that may send interrupts or cause memory crashes.
 */
static jmp_buf context;
void trap_segfault(int sig) {
    longjmp(context, 1);
}
void signal_trap() {
    signal(SIGSEGV, trap_segfault);
}
void signal_no_trap() {
    signal(SIGSEGV, SIG_DFL);
}
void show(Customer *customer) {
    printf("Name      : %40s\nDistrict  : %40s\nQ People  : %40d\nChildren  : %40s\nIncome    : %40.2f\n\n", get_name(customer), get_district(customer), get_n_people(customer), get_children(customer) == 0 ? "No": "Yes", get_income(customer));
}

/*
 * Application test 
 */
int main() {
    printf("*** Starting test ...\n");
    list_errors = (Error *) malloc(999 * sizeof(Error));
/*
 * Validating the expected functions according to the headers.
 */
    //Customer
    Customer *c;
    signal_trap();
    if(setjmp(context) == 0) {
        c = create_customer(NULL, "district", 5, 1, 10.0);
        if(c) {  
            strncpy(list_errors[count_errors].origin, CUS_FUNC, 50);
            strncpy(list_errors[count_errors++].description, NULL_NAME, 80); 
            fprintf(stderr, "[ERROR] Failed to create requisition with null name\n");
            free(c);
        } 
    } else {
        strncpy(list_errors[count_errors].origin, CUS_FUNC, 50);
        strncpy(list_errors[count_errors++].description, NULL_NAME, 80); 
        fprintf(stderr, "[ERROR] Failed to create requisition with null name with exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        c = create_customer("Name", NULL, 5, 1, 10.0);
        if(c) {     
            strncpy(list_errors[count_errors].origin, CUS_FUNC, 50);
            strncpy(list_errors[count_errors++].description, NULL_DIST, 80); 
            fprintf(stderr, "[ERROR] Failed to create requisition with null district\n");
            free(c);
        }
    } else {
        strncpy(list_errors[count_errors].origin, CUS_FUNC, 50);
        strncpy(list_errors[count_errors++].description, NULL_DIST, 80); 
        fprintf(stderr, "[ERROR] Failed to create requisition with null district with exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_name(NULL) != NULL) {
            strncpy(list_errors[count_errors].origin, GN_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
            fprintf(stderr, "[ERROR] Failed to execute get_name with a NULL requisition.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GN_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
        fprintf(stderr, "[ERROR] Failed to execute get_name with a NULL requisition with exception.\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_district(NULL) != NULL) {
            strncpy(list_errors[count_errors].origin, GD_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
            fprintf(stderr, "[ERROR] Failed to execute get_district with a NULL requisition.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GN_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
        fprintf(stderr, "[ERROR] Failed to execute get_district with a NULL requisition with exception.\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_children(NULL) != -1) {
            strncpy(list_errors[count_errors].origin, GD_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
            fprintf(stderr, "[ERROR] Failed to execute get_children with a NULL requisition.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GN_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
        fprintf(stderr, "[ERROR] Failed to execute get_children with a NULL requisition with exception.\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_n_people(NULL) != -1) {
            strncpy(list_errors[count_errors].origin, GD_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
            fprintf(stderr, "[ERROR] Failed to execute get_n_people with a NULL requisition.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GN_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
        fprintf(stderr, "[ERROR] Failed to execute get_n_people with a NULL requisition with exception.\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_income(NULL) != -1.0) {
            strncpy(list_errors[count_errors].origin, GD_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
            fprintf(stderr, "[ERROR] Failed to execute get_income with a NULL requisition.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GN_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
        fprintf(stderr, "[ERROR] Failed to execute get_income with a NULL requisition with exception.\n");
    }
    signal_no_trap();
    c = create_customer("Name", "District", 5, 1, 10.0);
    if(c) {   
        if(strcmp(get_name(c), "Name") != 0) {
            strncpy(list_errors[count_errors].origin, GN_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Fail to retrieve name %s, was expected %s\n", get_name(c), "Name");
        }  
        if(strcmp(get_district(c), "District") != 0) {
            strncpy(list_errors[count_errors].origin, GD_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Fail to retrieve district %s, was expected %s\n", get_district(c), "District");
        } 
        if(get_n_people(c) != 5) {
            strncpy(list_errors[count_errors].origin, GP_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Fail to retrieve number of people %d, was expected %d\n", get_n_people(c), 5);
        }
        if(get_children(c) != 1) {
            strncpy(list_errors[count_errors].origin, GC_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Fail to retrieve children %d, was expected %d\n", get_children(c), 1);
        }
        if(get_income(c) != 10.0) {
            strncpy(list_errors[count_errors].origin, GI_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Fail to retrieve income %f, was expected %f\n", get_income(c), 10.0);
        }
        free(c);
    }
    //Node
    Node *n = create_node(NULL);
    if(n) {     
        strncpy(list_errors[count_errors].origin, NOD_FUNC, 50);
        strncpy(list_errors[count_errors++].description, CR_NOD_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to create node with null customer\n");
        free(n);
    }
    c = create_customer("Name", "district", 4, 1, 1.0);
    n = create_node(c);
    if(n) {
        if(get_data(n) != c) {
            strncpy(list_errors[count_errors].origin, GT_DATA, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve data of the node\n");
        } 
        if(get_next(n) != NULL) {
            strncpy(list_errors[count_errors].origin, GT_NEXT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve next of the node\n");
        }
        Node *n1 = create_node(c);
        if(set_next(n, n1) != EXIT_SUCCESS) {
            strncpy(list_errors[count_errors].origin, ST_NEXT, 50);
            strncpy(list_errors[count_errors++].description, ST_NEXT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed in set next of the node\n");
        }
        if(get_next(n) != n1) {
            strncpy(list_errors[count_errors].origin, GT_NEXT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve next of the node\n");
        }
        free(n);
        free(n1);
        free(c);
    }
    n = NULL;
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_data(n) != NULL) {
            strncpy(list_errors[count_errors].origin, GT_DATA, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] It failed because the NULL argument was not validated.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GT_DATA, 50);
        strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
        fprintf(stderr, "[ERROR] It failed because the NULL argument was not validated with exception.\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_next(n) != NULL) {
            strncpy(list_errors[count_errors].origin, GT_NEXT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] It failed because the NULL argument was not validated.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GT_NEXT, 50);
        strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
        fprintf(stderr, "[ERROR] It failed because the NULL argument was not validated with exception.\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(set_next(n, n) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, ST_NEXT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] It failed because the NULL argument was not validated.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, ST_NEXT, 50);
        strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
        fprintf(stderr, "[ERROR] It failed because the NULL argument was not validated with exception.\n");
    }
    signal_no_trap();
    //List
    List* l = create_list();
    if(l) {
        if(get_quantity(l) != 0) {
            strncpy(list_errors[count_errors].origin, GT_LIS_QT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve quantity customers of the list\n");
        }
        c = create_customer("Name", "District", 2, 0, 1.0);
        if(add_list(l, c) != EXIT_SUCCESS) {
            strncpy(list_errors[count_errors].origin, ADD_LIS, 50);
            strncpy(list_errors[count_errors++].description, ADD_LIS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed in insert valid customer\n");
        }
        if(get_quantity(l) != 1) {
            strncpy(list_errors[count_errors].origin, GT_LIS_QT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve quantity customers of the list\n");
        }
        if(get_begin(l) == NULL) {
            strncpy(list_errors[count_errors].origin, GT_LIS_B, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve begin list, return NULL\n");
        }
        signal_trap();
        if(setjmp(context) == 0) {
            if(add_list(l, NULL) != EXIT_FAILURE) {
                strncpy(list_errors[count_errors].origin, ADD_LIS, 50);
                strncpy(list_errors[count_errors++].description, ADD_LIS_ERR, 80); 
                fprintf(stderr, "[ERROR] Failed to insert invalid customer\n");
            }
        } else {
            strncpy(list_errors[count_errors].origin, ADD_LIS, 50);
            strncpy(list_errors[count_errors++].description, ADD_LIS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert invalid customer with exception\n");
        }
        if(get_quantity(l) != 1) {
            strncpy(list_errors[count_errors].origin, GT_LIS_QT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve quantity customers of the list\n");
        }
        signal_trap();
        if(setjmp(context) == 0) {
            if(add_list(NULL, c) != EXIT_FAILURE) {
                strncpy(list_errors[count_errors].origin, ADD_LIS, 50);
                strncpy(list_errors[count_errors++].description, ADD_LIS_ERR, 80); 
                fprintf(stderr, "[ERROR] Failed to insert customer in NULL list\n");
            } 
        } else {
            strncpy(list_errors[count_errors].origin, ADD_LIS, 50);
            strncpy(list_errors[count_errors++].description, ADD_LIS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert customer in NULL list with exception\n");
        }
        signal_no_trap();
        signal_trap();
        if(setjmp(context) == 0) {
            if(get_quantity(NULL) != -1) {
                strncpy(list_errors[count_errors].origin, GT_LIS_QT, 50);
                strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
                fprintf(stderr, "[ERROR] Failed to get quantity int NULL list\n");
            }
        } else {
            strncpy(list_errors[count_errors].origin, GT_LIS_QT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to get quantity int NULL list with exception\n");
        }
        signal_no_trap();
        if(get_quantity(l) != 1) {
            strncpy(list_errors[count_errors].origin, GT_LIS_QT, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve quantity customers of the list\n");  
        }
        n = get_begin(l);
        if(n) {
            if(get_quantity(l) != 1) n = get_next(n);
            Customer *cr = get_data(n);
            if(strcmp(get_name(cr), "Name")) {
                strncpy(list_errors[count_errors].origin, GT_LIS_B, 50);
                strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
                fprintf(stderr, "[ERROR] Failed to retrieve begin node of the list\n");
            }
        } else {
            strncpy(list_errors[count_errors].origin, GT_LIS_B, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve begin node of the list\n");
        }
        free_list(l);
    }
    //Structure
    Structure* str = create_structure();
    c = create_customer("Name", "district", 4, 1, 1.0);
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(str, 1, NULL) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 1 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 1 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(str, 2, NULL) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 2 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 2 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(str, 3, NULL) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 3 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 3 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(str, 4, NULL) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 4 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 4 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(str, 5, NULL) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 5 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert NULL customer in structure with 5 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(NULL, 1, c) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 1 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 1 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(NULL, 2, c) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 2 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 2 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(NULL, 3, c) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 3 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 3 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(NULL, 4, c) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 4 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 4 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(add_customer(NULL, 5, c) != EXIT_FAILURE) {
            strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
            strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 5 criteria\n");
        }    
    } else {
        strncpy(list_errors[count_errors].origin, STR_CUS_ADD, 50);
        strncpy(list_errors[count_errors++].description, ADD_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to insert customer in NULL structure with 5 criteria, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(retrieve_customer(NULL, 1, 0, " ") != NULL) {
            strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
            strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve customers in NULL structure\n");
        } 
    } else {
        strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
        strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to retrieve customers in NULL structure, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(retrieve_customer(NULL, 2 , 0, " ") != NULL) {
            strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
            strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve customers in NULL structure\n");
        } 
    } else {
        strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
        strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to retrieve customers in NULL structure, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(retrieve_customer(str, 1, 0, NULL) != NULL) {
            strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
            strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve customers using NULL in search\n");
        } 
    } else {
        strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
        strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to retrieve customers using NULL in search, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(retrieve_customer(str, 2, 0, NULL) != NULL) {
            strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
            strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
            fprintf(stderr, "[ERROR] Failed to retrieve customers using NULL in search\n");
        } 
    } else {
        strncpy(list_errors[count_errors].origin, STR_RT_CUS, 50);
        strncpy(list_errors[count_errors++].description, RT_CUS_ERR, 80); 
        fprintf(stderr, "[ERROR] Failed to retrieve customers using NULL in search, throw exception\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        free_structure(NULL);
    } else {
        strncpy(list_errors[count_errors].origin, FREE_STR, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80); 
        fprintf(stderr, "[ERROR] Failed to free NULL structure, throw exception\n");
    }
/*
 * Mass of customers to be included in the structure
 */   
    Customer *customer[10];
    customer[0] = create_customer("Alberto", "Centro", 3, 1, 4500.00);
    if(!customer[0]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[1] = create_customer("Bernardo", "Ingleses", 1, 0, 1800.00);
    if(!customer[1]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[2] = create_customer("Amarilis", "Trindade", 2, 0, 2980.00);
    if(!customer[2]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[3] = create_customer("Rodolfo", "Centro", 5, 1, 6500.00);
    if(!customer[3]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[4] = create_customer("Maria", "Trindade", 2, 1, 15800.00);
    if(!customer[4]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[5] = create_customer("Marta", "Trindade", 1, 0, 8000.00);
    if(!customer[5]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[6] = create_customer("Vanessa", "Centro", 3, 1, 8300.00);
    if(!customer[6]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[7] = create_customer("Gilberto", "Ingleses", 2, 0, 4000.00);
    if(!customer[7]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[8] = create_customer("Simone", "Centro", 1, 0, 5000.00);
    if(!customer[8]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
    customer[9] = create_customer("Antonio", "Trindade", 4, 1, 3500.00);
    if(!customer[9]) {
        strcpy(list_errors[count_errors].origin, CUS_FUNC);
        strcpy(list_errors[count_errors].description, CR_CUS_ERR);
        fprintf(stderr, "[ERROR] Create customer fail\n");
    }
/*-------------------------------------------------------------------------------------------------
Criação da structure vazia
-------------------------------------------------------------------------------------------------*/
    Structure *structure = create_structure(); 
    if(!structure) {
        strcpy(list_errors[count_errors].origin, STR_FUNC);
        strcpy(list_errors[count_errors].description, CR_STR_ERR);
        fprintf(stderr, "[ERROR] Create structure fail\n");
    }
    int i, statusfail;
/*-------------------------------------------------------------------------------------------------
Populate hashtables:
1 - Insertion into the structure that uses the name as the key
2 - Insertion into the structure that uses the district as the key
3 - Insertion into the structure that uses the number of people in the residence as the key
4 - Insertion into the structure that uses the presence of children under 5 years old as the key
5 - Insertion into the structure that uses gross family income as the key
-------------------------------------------------------------------------------------------------*/
    for(i = 0; i < 10; i++) {
        statusfail = add_customer(structure, 1, customer[i]);
        if(statusfail) {
            strcpy(list_errors[count_errors].origin, STR_CUS_ADD);
            strcpy(list_errors[count_errors].description, ADD_CUS_ERR);
            fprintf(stderr, "[ERROR] Add customer %s with criteria 1 fail\n", get_name(customer[i]));
        }
        statusfail = add_customer(structure, 2, customer[i]);
        if(statusfail) {
            strcpy(list_errors[count_errors].origin, STR_CUS_ADD);
            strcpy(list_errors[count_errors].description, ADD_CUS_ERR);
            fprintf(stderr, "[ERROR] Add customer %s with criteria 2 fail\n", get_name(customer[i]));
        }
        statusfail = add_customer(structure, 3, customer[i]);
        if(statusfail) {
            strcpy(list_errors[count_errors].origin, STR_CUS_ADD);
            strcpy(list_errors[count_errors].description, ADD_CUS_ERR);
            fprintf(stderr, "[ERROR] Add customer %s with criteria 3 fail\n", get_name(customer[i]));
        }
        statusfail = add_customer(structure, 4, customer[i]);
        if(statusfail) {
            strcpy(list_errors[count_errors].origin, STR_CUS_ADD);
            strcpy(list_errors[count_errors].description, ADD_CUS_ERR);
            fprintf(stderr, "[ERROR] Add customer %s with criteria 4 fail\n", get_name(customer[i]));
        }
        statusfail = add_customer(structure, 5, customer[i]);
        if(statusfail) {
            strcpy(list_errors[count_errors].origin, STR_CUS_ADD);
            strcpy(list_errors[count_errors].description, ADD_CUS_ERR);
            fprintf(stderr, "[ERROR] Add customer %s with criteria 5 fail\n", get_name(customer[i]));
        }
    }
    printf("Included in the structure ...\n");
    int counter = 0;
/*
 * Retrieving customers using name as a search key.
 */
    List *list = retrieve_customer(structure, 1, 0, "Vanessa");
    if(get_quantity(list) > 0) {
        printf("Customers with name Vanessa [1]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(strcmp(get_name(c), "Vanessa") != 0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] Retrieve custemer %s, but was expected Vanessa\n", get_name(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 1) {
            fprintf(stderr, "[ERROR] 1 was expected, but the number of recovered customers named Vanessa was different!\n");
        }
    } else {
        fprintf(stderr, "[ERROR] Expected 1, but no recovered customer named Vanessa!\n");
    }
    printf("-------------------------------------------\n\n");
    list = retrieve_customer(structure, 1, 0, "Arthur");
    if(get_quantity(list) > 0) {
        fprintf(stderr, "[ERROR] It wasn't expected, but there are customers named Arthur:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_ERR);
            fprintf(stderr, "[ERROR] %s was recovered, but no one was expected\n", get_name(c));
            cursor = get_next(cursor);
            counter++;
        }
    } else {
        printf("No customers named Arthur were retrieved, as expected!\n");
    }
    counter = 0;
    printf("-------------------------------------------\n\n");
    list = retrieve_customer(structure, 1, 0, "Maria");
    if(get_quantity(list) > 0) {
        printf("Customers with name Maria [1]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(strcmp(get_name(c), "Maria") != 0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] Retrieve custemer %s, but was expected Maria\n", get_name(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 1) {
            fprintf(stderr, "[ERROR] 1 was expected, but the number of recovered customers named Maria was different!\n");
        }
    } else {
        fprintf(stderr, "[ERROR] Expected 1, but no recovered customer named Vanessa!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
/*
 * Recovering customers using district as a search term
 */
    list = retrieve_customer(structure, 2, 0, "Centro");
    if(get_quantity(list) > 0) {
        printf("Customers from the Centro district [4]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(strcmp(get_district(c), "Centro") != 0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] Retrieve district of custemer %s, but was expected Centro\n", get_district(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 4) {
            fprintf(stderr, "[ERROR] The number of recovered customers from the Centro district is different from 4!\n");
        }
    } else {
        fprintf(stderr, "[ERROR] No customers recovered from the Centro district, 4 was expected.!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 2, 0, "Ingleses");
    if(get_quantity(list) > 0) {
        printf("Customers from the Ingleses district [2]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(strcmp(get_district(c), "Ingleses") != 0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] Retrieve district of custemer %s, but was expected Ingleses\n", get_district(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 2) {
            fprintf(stderr, "[ERROR] The number of recovered customers from the Ingleses district is different from 2!\n");
        }
    } else {
        fprintf(stderr, "[ERROR] No customers recovered from the Ingleses district, 2 was expected.!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 2, 0, "Trindade");
    if(get_quantity(list) > 0) {
        printf("Customers from the Trindade district [4]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(strcmp(get_district(c), "Trindade") != 0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] Retrieve district of custemer %s, but was expected Trindade\n", get_district(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 4) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_ERR);
            fprintf(stderr, "[ERROR] The number of recovered customers from the Trindade district is different from 4!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_ERR);
        fprintf(stderr, "[ERROR] No customers recovered from the Trindade district, 4 was expected.!\n");
    }
    printf("-------------------------------------------\n\n");
/*
 * Recovering customers using the number of people as a search term.
 */
    counter = 0;
    list = retrieve_customer(structure, 3, 1, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with 1 person in the household [3]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_n_people(c) != 1) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] The customer has %d people in the household and 1 was expected\n", get_n_people(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 3) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_ERR);
            fprintf(stderr, "[ERROR] Number of recovered customers with 1 person in the residence and different from 3!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_ERR);
        fprintf(stderr, "[ERROR] No recovered customers with 1 person in the residence, 3 were expected!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 3, 2, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with 2 people in the household [3]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_n_people(c) != 2) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] The customer has %d people in the household and 2 was expected\n", get_n_people(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 3) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_ERR);
            fprintf(stderr, "[ERROR] Number of recovered customers with 2 people in the residence and different from 3!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_ERR);
        fprintf(stderr, "[ERROR] No recovered customers with 2 people in the residence, 3 were expected!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 3, 3, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with 3 people in the household [2]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_n_people(c) != 3) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] The customer has %d people in the household and 3 was expected\n", get_n_people(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 2) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_ERR);
            fprintf(stderr, "ERROR] Number of recovered customers with 3 people in the household and different from 2!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_ERR);
        fprintf(stderr, "ERROR] No recovered customers with 3 people in the household, 2 were expected!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 3, 4, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with 4 people in the household [1]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_n_people(c) != 4) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] The customer has %d people in the household and 4 was expected\n", get_n_people(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 1) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_ERR);
            fprintf(stderr, "[ERROR] Number of recovered customers with 4 people in the household and different from 1!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_ERR);
        fprintf(stderr, "[ERROR] No recovered customers with 4 people in the household, 1 was expected!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 3, 5, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with 5 or more people in the household [1]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_n_people(c) != 5) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] The customer has %d people in the household and 5 was expected\n", get_n_people(c));
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 1) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_ERR);
            fprintf(stderr, "[ERROR] Number of recovered customers with 5 or more people in the household and different from 1.!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_ERR);
        fprintf(stderr, "[ERROR] No recovered customers with 5 or more people in the household, 1 was expected!\n");
    }
    printf("-------------------------------------------\n\n");
/*
 * Recovering customers using the existence of children under 5 years old as a search keyword.
 */
    counter = 0;
    list = retrieve_customer(structure, 4, 0, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers who do not have children under 5 years old in the household [5]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_children(c) != 0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] Customer have children under 5 years old, and it was expected that they wouldn't have...\n");
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 5) {
            fprintf(stderr, "[ERROR] Number of recovered customers without minors in the household and different from 5.!\n");
        }
    } else {
        fprintf(stderr, "[ERROR] No recovered customers, no minors in the household, 5 were expected.!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 4, 1, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers who have children under 5 years old in the household [5]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_children(c) != 1) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_ERR);
                fprintf(stderr, "[ERROR] Customer don't have children under 5 years old, and it was expected that they would have\n");
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 5) {
            fprintf(stderr, "[ERROR] Number of recovered customers with minors in the household and different from 5!\n");
        }
    } else {
        fprintf(stderr, "[ERRO] No recovered customers with minors in the household, 5 were expected.!\n");
    }
    printf("-------------------------------------------\n\n");
/*
 * Recovering customers using gross income range as a search key.
 */
    counter = 0;
    list = retrieve_customer(structure, 5, 1, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with an income of up to 2000 [1]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_income(c) >= 2000.0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_IN_ERR);
                fprintf(stderr, "[ERROR] Customer outside the expected income range\n");
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 1) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_NR_ERR);
            fprintf(stderr, "[ERROR] Number of recovered customers with income up to 2000 and different from 1!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_NR_ERR);
        fprintf(stderr, "[ERROR] No recovered customers with income up to 2000, 1 was expected!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 5, 2, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with an income of up to 3000 [1]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_income(c) < 2000.0 && get_income(c) > 3000.0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_IN_ERR);
                fprintf(stderr, "[ERROR] Customer outside the expected income range\n");
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 1) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_NR_ERR);
            fprintf(stderr, "[ERROR] Number of recovered customers with income up to 3000 is different from 1!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_NR_ERR);
        fprintf(stderr, "[ERROR] No recovered customers with income up to 3000, 1 was expected.!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 5, 3, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with an income of up to 5000 [4]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_income(c) <= 3000.0 && get_income(c) > 5000.0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_IN_ERR);
                fprintf(stderr, "[ERROR] Customer outside the expected income range\n");
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 4) {
            fprintf(stderr, "[ERROR] Number of recovered customers with income up to 5000 and different from 4!\n");
        }
    } else {
        fprintf(stderr, "[ERROR] No recovered customers with income up to 5000, 4 were expected!\n");
    }
    printf("-------------------------------------------\n\n");
    counter = 0;
    list = retrieve_customer(structure, 5, 4, NULL);
    if(get_quantity(list) > 0) {
        printf("Customers with an income greater than 5000 [4]:\n");
        Node *cursor = get_begin(list);
        while(cursor != NULL) {
            c = get_data(cursor);
            show(c);
            if(get_income(c) <= 5000.0) {
                strcpy(list_errors[count_errors].origin, STR_RT_CUS);
                strcpy(list_errors[count_errors].description, RT_CUS_IN_ERR);
                fprintf(stderr, "[ERROR] Customer outside the expected income range\n");
            }
            cursor = get_next(cursor);
            counter++;
        }
        if(counter != 4) {
            strcpy(list_errors[count_errors].origin, STR_RT_CUS);
            strcpy(list_errors[count_errors].description, RT_CUS_NR_ERR);
            fprintf(stderr, "[ERROR] Number of recovered customers with income greater than 5000 and different from 4!\n");
        }
    } else {
        strcpy(list_errors[count_errors].origin, STR_RT_CUS);
        strcpy(list_errors[count_errors].description, RT_CUS_NR_ERR);
        fprintf(stderr, "[ERROR] No recovered customers with income above 5000, and 4 were expected!\n");
    }
    free_structure(structure);
    if(count_errors > 0) {
        printf("*** %d errors found ...\n", count_errors);
        show_test_report(count_errors);
    } else {
        printf("*** No errors identified in the test.\n");
    }
    free(list_errors);
    return EXIT_SUCCESS;
}