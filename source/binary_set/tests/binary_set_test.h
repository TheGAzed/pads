#ifndef BINARY_SET_TEST_H
#define BINARY_SET_TEST_H

#include <greatest.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define BINARY_SET_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"
void destroy_element(BINARY_SET_DATA_TYPE * element);
BINARY_SET_DATA_TYPE copy_element(const BINARY_SET_DATA_TYPE element);

void operation_int(BINARY_SET_DATA_TYPE * element, void * args);
void operation_string(BINARY_SET_DATA_TYPE * element, void * args);

SUITE_EXTERN(infinite_realloc_binary_set_test);
SUITE_EXTERN(finite_allocated_binary_set_test);
SUITE_EXTERN(finite_preprocessor_binary_set_test);


#endif //BINARY_SET_TEST_H
