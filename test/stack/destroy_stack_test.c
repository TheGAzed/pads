#ifndef TEST_STACK_MODE

#error 'TEST_STACK_MODE' not defined.

#else

#define STACK_MODE TEST_STACK_MODE

#endif

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

#include <greatest.h>

#define STACK_MODE INFINITE_LIST_STACK
#define STACK_DATA_TYPE type_dst_u
#define REALLOC_STACK_CHUNK     (1 << 3)
#define LIST_ARRAY_STACK_CHUNK  (1 << 3)
#define PREPROCESSOR_STACK_SIZE (1 << 3)
#include "stack.h"

void destroy_element_cst(STACK_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (STACK_DATA_TYPE) { 0 };
}

#if   STACK_MODE == INFINITE_LIST_STACK

/// Tests if stack's head parameter is NULL.
TEST ILS_01(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    destroy_stack(&test_stack);
    ASSERT_EQm("[ILS-TEST] Stack's head parameter is not NULL.", NULL, test_stack.head);

    PASS();
}

/// Tests if stack's head parameter is NULL.
TEST ILS_02(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    destroy_stack(&test_stack);
    ASSERT_EQm("[ILS-TEST] Stack's head parameter is not NULL.", NULL, test_stack.head);

    PASS();
}

/// Tests if stack's head parameter is NULL.
TEST ILS_03(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    destroy_stack(&test_stack);
    ASSERT_EQm("[ILS-TEST] Stack's head parameter is not NULL.", NULL, test_stack.head);

    PASS();
}

/// Tests if stack's head parameter is NULL.
TEST ILS_04(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    destroy_stack(&test_stack);
    ASSERT_EQm("[ILS-TEST] Stack's head parameter is not NULL.", NULL, test_stack.head);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(ILS_01);
    RUN_TEST(ILS_02);
    RUN_TEST(ILS_03);
    RUN_TEST(ILS_04);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK
#elif STACK_MODE == INFINITE_REALLOC_STACK
#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK
#endif
