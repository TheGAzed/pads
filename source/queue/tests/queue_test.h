#ifndef QUEUE_TEST_H
#define QUEUE_TEST_H

#include <greatest.h>
#include <stdbool.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#define QUEUE_DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"
void destroy_element(QUEUE_DATA_TYPE * element);
QUEUE_DATA_TYPE copy_element(const QUEUE_DATA_TYPE element);

bool operation_int(QUEUE_DATA_TYPE * element, void * args);
bool operation_string(QUEUE_DATA_TYPE * element, void * args);

SUITE_EXTERN(infinite_list_queue_test);
SUITE_EXTERN(finite_allocated_queue_test);
SUITE_EXTERN(infinite_realloc_queue_test);
SUITE_EXTERN(finite_preprocessor_queue_test);

#endif // QUEUE_TEST_H
