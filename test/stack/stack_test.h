#ifndef STACK_TEST_H
#define STACK_TEST_H

#include <greatest.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define STACK_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"
void destroy_element(STACK_DATA_TYPE * element);
STACK_DATA_TYPE copy_element(const STACK_DATA_TYPE element);

int compare_int_asc(const void * a, const void * b);
int compare_int_desc(const void * a, const void * b);

int compare_string_asc(const void * a, const void * b);
int compare_string_desc(const void * a, const void * b);

void operation_int(STACK_DATA_TYPE * element, void * args);
void operation_string(STACK_DATA_TYPE * element, void * args);

SUITE_EXTERN(infinite_list_stack_test);
SUITE_EXTERN(finite_allocated_stack_test);
SUITE_EXTERN(infinite_realloc_stack_test);
SUITE_EXTERN(finite_preprocessor_stack_test);

#endif //STACK_TEST_H
