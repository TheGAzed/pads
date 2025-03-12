#ifndef STRAIGHT_LIST_TEST_H
#define STRAIGHT_LIST_TEST_H

#include <greatest.h>
#include <stdbool.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define STRAIGHT_LIST_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"
void destroy_element(STRAIGHT_LIST_DATA_TYPE * element);
STRAIGHT_LIST_DATA_TYPE copy_element(const STRAIGHT_LIST_DATA_TYPE element);

int compare_int(const STRAIGHT_LIST_DATA_TYPE a, const STRAIGHT_LIST_DATA_TYPE b);
int compare_string(const STRAIGHT_LIST_DATA_TYPE a, const STRAIGHT_LIST_DATA_TYPE b);

void sort_int(STRAIGHT_LIST_DATA_TYPE * elements, const size_t size, void * args);
void sort_string(STRAIGHT_LIST_DATA_TYPE * elements, const size_t size, void * args);

bool operation_int(STRAIGHT_LIST_DATA_TYPE * element, void * args);
bool operation_string(STRAIGHT_LIST_DATA_TYPE * element, void * args);

SUITE_EXTERN(infinite_allocated_straight_list_test);
SUITE_EXTERN(finite_allocated_straight_list_test);
SUITE_EXTERN(infinite_realloc_straight_list_test);
SUITE_EXTERN(finite_preprocessor_straight_list_test);

#endif //STRAIGHT_LIST_TEST_H
