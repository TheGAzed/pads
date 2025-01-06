#ifndef LIST_TEST_H
#define LIST_TEST_H

#include <greatest.h>
#include <stdbool.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define LIST_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"
void destroy_element(LIST_DATA_TYPE * element);
LIST_DATA_TYPE copy_element(const LIST_DATA_TYPE element);

bool operation_int(LIST_DATA_TYPE * element, void * args);
bool operation_string(LIST_DATA_TYPE * element, void * args);

SUITE_EXTERN(infinite_allocated_list_test);
SUITE_EXTERN(finite_allocated_list_test);
SUITE_EXTERN(infinite_realloc_list_test);
SUITE_EXTERN(finite_preprocessor_list_test);

#endif // LIST_TEST_H
