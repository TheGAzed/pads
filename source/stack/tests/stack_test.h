#ifndef STACK_TEST_H
#define STACK_TEST_H

#include <greatest.h>
#include <stdbool.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define STACK_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"

void destroy_int(STACK_DATA_TYPE * element);
void destroy_string(STACK_DATA_TYPE * element);

STACK_DATA_TYPE copy_int(const STACK_DATA_TYPE element);
STACK_DATA_TYPE copy_string(const STACK_DATA_TYPE element);

bool operation_int(STACK_DATA_TYPE * element, void * args);
bool operation_string(STACK_DATA_TYPE * element, void * args);

int compare_int(void * a, void * b);
int compare_reverse_int(void * a, void * b);

void sort_int(STACK_DATA_TYPE * elements, const size_t size, void * args);

SUITE_EXTERN(infinite_list_stack_test);
SUITE_EXTERN(finite_allocated_stack_test);
SUITE_EXTERN(infinite_realloc_stack_test);
SUITE_EXTERN(finite_preprocessor_stack_test);

#endif //STACK_TEST_H
