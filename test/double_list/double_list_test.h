#ifndef DOUBLE_LIST_TEST_H
#define DOUBLE_LIST_TEST_H

#include <greatest.h>
#include <stdbool.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define DOUBLE_LIST_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"
void destroy_element(DOUBLE_LIST_DATA_TYPE * element);
DOUBLE_LIST_DATA_TYPE copy_element(const DOUBLE_LIST_DATA_TYPE element);

bool operation_int(DOUBLE_LIST_DATA_TYPE * element, void * args);
bool operation_string(DOUBLE_LIST_DATA_TYPE * element, void * args);

SUITE_EXTERN(infinite_allocated_double_list_test);
SUITE_EXTERN(finite_allocated_double_list_test);
SUITE_EXTERN(infinite_realloc_double_list_test);
SUITE_EXTERN(finite_preprocessor_double_list_test);

#endif // DOUBLE_LIST_TEST_H
