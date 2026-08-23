#define REQ_FUNC "requisition.c -> create_requisition function"
#define GN_FUN "requisition.c -> get_name function"
#define RG_FUN "requisition.c -> get_registration function"
#define GP_FUN "requisition.c -> get_procedure function"
#define GT_ERR "Getter returns a different value than expected."
#define REQ_FUNC_M "Create requisition fail"
#define NULL_NAME "Requisition creation failed because it created requisition with null name"
#define NULL_PROC "Requisition creation failed because it created requisition with null procedure"
#define NULL_REQ "Insert NULL requisition"
#define TRUNC_STR "Create requisition fail in truncate strings"
#define STR_FUNC "structure.c -> create_structure function"
#define CS_FAIL "Create structure fail"
#define AS_FUN "structure.c -> add function"
#define AS_FUN_F "Insert requisition fail"
#define AS_NUM_F "Incorrect number of elements added"
#define AS_NULL_STR "Insert in NULL structure"
#define RS_FUN "structure.c -> removal function"
#define U_REQ "Unexpected requisition removed"
#define NUM_ERR "Incorrect number of remaining elements"
#define RS_FAIL "Fail in removal requisition"
#define RS_NULL_STR "Removal in NULL structure"
#define TR_NULL "Lack of handling for NULL argument"

#define LONG_NAME "This is a very long name that shouldn't be allowed when creating the request, or at least the name should have been truncated."
#define LONG_PROC "This is a very long procedure name that should not be allowed when creating the request, or at least the name should have been truncated."

#include "requisition.h"
#include "structure.h"
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Part of the code with a structure for error handling and requisition presentation.
 */
typedef struct Error_ {
    char origin[51];
    char description[81];
} Error;

Error *list_errors;
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

void show(Requisition *requisition) {
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Address: %p\nName        : %40s\nRegistration: %40d\nProcedure   : %40s\n\n", requisition, get_name(requisition), get_registration(requisition), get_procedure(requisition));
}

/*
 * Application test 
 */
int main() {
    int statusfail;
    // Structure for storing identified errors.
    list_errors = malloc(999 * sizeof(Error));
    printf("*** Starting test...\n");
    printf("---------------------------------------\n");
    // Testing the functions required for the program.
    Requisition* r;
    signal_trap();
    if (setjmp(context) == 0) {
        r = create_requisition(NULL, 99, "T123456"); //test NULL name
        if(r) {
            strncpy(list_errors[count_errors].origin, REQ_FUNC, 50);
            strncpy(list_errors[count_errors++].description, NULL_NAME, 80); 
            fprintf(stderr, "[ERROR] Failed to create requisition with null name\n");
            free(r);
        }
    } else {
        strncpy(list_errors[count_errors].origin, REQ_FUNC, 50); 
        strncpy(list_errors[count_errors++].description, NULL_NAME, 80); 
        fprintf(stderr, "[ERROR] Error while trying to create request and throwing exception due to invalid parameter.\n");
    }
    signal_no_trap();
    signal_trap();
    if (setjmp(context) == 0) {
        r = create_requisition("Name test", 99, NULL); //test NULL procedure
        if(r) {
            strncpy(list_errors[count_errors].origin, REQ_FUNC, 50);
            strncpy(list_errors[count_errors++].description, NULL_PROC, 80); 
            fprintf(stderr, "[ERROR] Error while trying to create request and throwing exception due to invalid parameter.\n");
            free(r);
        }
    } else {
        strncpy(list_errors[count_errors].origin, REQ_FUNC, 50);
        strncpy(list_errors[count_errors++].description, NULL_PROC, 80); 
        fprintf(stderr, "[ERROR] Failed to create requisition with null procedure\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        r = create_requisition(LONG_NAME, 99, LONG_PROC); //test name and procedure long
        if(r) {
            if((strlen(get_name(r)) != 40) || strlen(get_procedure(r)) != 10) {                
                strncpy(list_errors[count_errors].origin, REQ_FUNC, 50);
                strncpy(list_errors[count_errors++].description, TRUNC_STR, 80); 
                fprintf(stderr, "[ERROR] Fail in truncate strings, size name = %lu, size procedure = %lu\n", (unsigned long)strlen(get_name(r)), (unsigned long)strlen(get_procedure(r)));
            }
            free(r); // It may produce an untreatable error.
        }
    } else {
        strncpy(list_errors[count_errors].origin, REQ_FUNC, 50);
        strncpy(list_errors[count_errors++].description, TRUNC_STR, 80);
        fprintf(stderr, "[ERROR] Fail in truncate strings, size name = %lu, size procedure = %lu\n", (unsigned long)strlen(get_name(r)), (unsigned long)strlen(get_procedure(r)));
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_name(NULL) != NULL) {
            strncpy(list_errors[count_errors].origin, GN_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80);
            fprintf(stderr, "[ERROR] Lack of treatment for NULL and no exceptiion\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GN_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80);
        fprintf(stderr, "[ERROR] Lack of treatment for NULL\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_registration(NULL) != -1) {
            strncpy(list_errors[count_errors].origin, RG_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80);
            fprintf(stderr, "[ERROR] Lack of treatment for NULL and no exception\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, RG_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80);
        fprintf(stderr, "[ERROR] Lack of treatment for NULL\n");
    }
    signal_no_trap();
    signal_trap();
    if(setjmp(context) == 0) {
        if(get_procedure(NULL) != NULL) {
            strncpy(list_errors[count_errors].origin, GP_FUN, 50);
            strncpy(list_errors[count_errors++].description, TR_NULL, 80);
            fprintf(stderr, "[ERROR] Lack of treatment for NULL and no exception\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, GP_FUN, 50);
        strncpy(list_errors[count_errors++].description, TR_NULL, 80);
        fprintf(stderr, "[ERROR] Lack of treatment for NULL\n");
    }
    signal_no_trap();
    r = create_requisition("Name", 1000, "Procedure");
    if(r) {
        if(strcmp("Name", get_name(r)) != 0) {
            strncpy(list_errors[count_errors].origin, GN_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80);
            fprintf(stderr, "[ERROR] Fail to retrieve name %s, was expected %s\n", get_name(r), "Name");
        }
        if(strcmp("Procedure", get_procedure(r)) != 0) {
            strncpy(list_errors[count_errors].origin, GP_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80);
            fprintf(stderr, "[ERROR] Fail to retrieve procedure %s, was expected %s\n", get_procedure(r), "Procedure");
        }
        if(1000 != get_registration(r)) {
            strncpy(list_errors[count_errors].origin, RG_FUN, 50);
            strncpy(list_errors[count_errors++].description, GT_ERR, 80);
            fprintf(stderr, "[ERROR] Fail to retrieve registration %d, was expected %d\n", get_registration(r), 1000);
        }
        free(r);
    }
    r = NULL;
    Structure* s = create_structure();
    if(!s) {
        strncpy(list_errors[count_errors].origin, STR_FUNC, 50);
        strncpy(list_errors[count_errors++].description, CS_FAIL, 80);
        fprintf(stderr, "Critical error! The structure could not be created.\n");
        show_test_report(count_errors);
        free(list_errors);
        exit(1);
    }
    statusfail = add(s, NULL);
    if(!statusfail) {
        strncpy(list_errors[count_errors].origin, AS_FUN, 50);
        strncpy(list_errors[count_errors++].description, NULL_REQ, 80);
        fprintf(stderr, "[ERROR] Failed to deny the insertion of a NULL requisition.\n");
    }
    free(s);
    r = create_requisition("Name", 1000, "Procedure");
    signal_trap();
    if(setjmp(context) == 0) {
        statusfail = add(NULL, r);
        if(!statusfail) {
            strncpy(list_errors[count_errors].origin, AS_FUN, 50);
            strncpy(list_errors[count_errors++].description, AS_NULL_STR, 80);  
            fprintf(stderr, "[ERROR] It did not deny the insertion of a null structure.\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, AS_FUN, 50);
        strncpy(list_errors[count_errors++].description, AS_NULL_STR, 80);  
        fprintf(stderr, "[ERROR] It failed because the structure NULL argument was not validated.\n");
    }
    free(r);
    // Mass data for requisitions
    char names[][40] = {"Joao", "Jose", "Maria", "Silvia", "Sonia", "Pedro", "Lucas", "Bernardete", "Lucia", "Olivia"}; 
    char procedures[][10] = {"123.1", "345.6", "678.9", "098.1", "758.5", "23.4", "5.98", "4,32", "3.3", "1.4"};
    // Test begin
    printf("*** Creating main structure ...\n");
    Structure *structure = create_structure();
    if(!structure) {
        strncpy(list_errors[count_errors].origin, STR_FUNC, 50);
        strncpy(list_errors[count_errors++].description, CS_FAIL, 80);
        fprintf(stderr, "Critical error! The structure could not be created.\n");
        show_test_report(count_errors);
        free(list_errors);
        exit(1);
    }
    int i;
    printf("*** Populating structure ...\n");
    Requisition *requisition;
    for(i = 0; i < 10; i++) {
        requisition = create_requisition(names[i], i, procedures[i]);
        if(requisition) {
            statusfail = add(structure, requisition);
            if(statusfail) {
                strncpy(list_errors[count_errors].origin, AS_FUN, 50);
                strncpy(list_errors[count_errors++].description, AS_FUN_F, 80);  
                fprintf(stderr, "[ERROR] Fail to insert %40s\n", get_name(requisition));
            } else {
                printf("Insert %40s, total: %04d\n", get_name(requisition), get_size(structure));
                if(get_size(structure) != (i + 1)) {
                    strncpy(list_errors[count_errors].origin, AS_FUN, 50);
                    strncpy(list_errors[count_errors++].description, AS_NUM_F, 80);
                    fprintf(stderr, "[ERROR] Add counter fail\n");
                }
            }
        } else {
            strncpy(list_errors[count_errors].origin, REQ_FUNC, 50);
            strncpy(list_errors[count_errors++].description, REQ_FUNC_M, 80); 
            fprintf(stderr, "[ERROR] Create requisition fail\n");
        }
    }
    printf("*** End of insertion and beginning of removal.\n");
    for(i = 0; i < 10; i++) {
        Requisition *requisition = removal(structure);
        if(requisition) {
            printf("Removed       %40s, total: %04d\n", get_name(requisition), get_size(structure));
            show(requisition);
            if(strcmp(names[i], get_name(requisition)) != 0) {
                strncpy(list_errors[count_errors].origin, RS_FUN, 50);
                strncpy(list_errors[count_errors++].description, U_REQ, 80);
                fprintf(stderr, "[ERROR] Incorret requisition - expected %s and removed %s\n", names[i], get_name(requisition));
            }
            if(get_size(structure) != (9 - i)) {
                strncpy(list_errors[count_errors].origin, RS_FUN, 50);
                strncpy(list_errors[count_errors++].description, NUM_ERR, 80);
                fprintf(stderr, "[ERROR] Number of remaining elements expected %d, but was %d\n", 9 - i, get_size(structure));
            }
            free(requisition);
        } else {
            strncpy(list_errors[count_errors].origin, RS_FUN, 50);
            strncpy(list_errors[count_errors++].description, RS_FAIL, 80);  
            fprintf(stderr, "[ERROR] Fail to removal requisition\n");
        }
    }
    signal_trap();
    if(setjmp(context) == 0) {
        requisition = removal(NULL);
        if(requisition) {
            strncpy(list_errors[count_errors].origin, RS_FUN, 50);
            strncpy(list_errors[count_errors++].description, RS_NULL_STR, 80);  
            fprintf(stderr, "[ERROR] Fail to removal requisition in NULL structure\n");
        }
    } else {
        strncpy(list_errors[count_errors].origin, RS_FUN, 50);
        strncpy(list_errors[count_errors++].description, RS_NULL_STR, 80);  
        fprintf(stderr, "[ERROR] Fail to removal requisition in NULL structure\n");
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
