#ifndef FORWARD_LIST_TEST_H
#define FORWARD_LIST_TEST_H

#include <greatest.h>
#include <stdbool.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define FORWARD_LIST_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"
void destroy_element(FORWARD_LIST_DATA_TYPE * element);
FORWARD_LIST_DATA_TYPE copy_element(const FORWARD_LIST_DATA_TYPE element);

int compare_int(const void * a, const void * b);
int compare_string(const void * a, const void * b);

void sort_int(FORWARD_LIST_DATA_TYPE * elements, const size_t size);
void sort_string(FORWARD_LIST_DATA_TYPE * elements, const size_t size);

bool operation_int(FORWARD_LIST_DATA_TYPE * element, void * args);
bool operation_string(FORWARD_LIST_DATA_TYPE * element, void * args);

SUITE_EXTERN(infinite_allocated_forward_list_test);
SUITE_EXTERN(finite_allocated_forward_list_test);
SUITE_EXTERN(infinite_realloc_forward_list_test);
SUITE_EXTERN(finite_preprocessor_forward_list_test);

#endif //FORWARD_LIST_TEST_H
