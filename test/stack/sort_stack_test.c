#include <greatest.h>

#ifndef TEST_STACK_MODE

#error No stack mode was defined before testing ('TEST_STACK_MODE' is not defined).

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#define STACK_DATA_TYPE int
#define LIST_ARRAY_STACK_CHUNK  10
#define REALLOC_STACK_CHUNK     10
#define PREPROCESSOR_STACK_SIZE 10
#include "stack.h"

#if   STACK_MODE == INFINITE_LIST_STACK

/// @brief
TEST test_01_01(void) {
    stack_s test = create_stack();

    sort_stack(&test, NULL);

    destroy_stack(&test, NULL);

    PASS();
}

/// @brief
TEST test_01_02(void) {
    stack_s test = create_stack();

    push_stack(&test, 2);
    push_stack(&test, 0);
    push_stack(&test, 1);
    push_stack(&test, 4);
    push_stack(&test, 3);
    push_stack(&test, 7);
    push_stack(&test, 5);
    push_stack(&test, 6);
    push_stack(&test, 8);

    sort_stack(&test, NULL);
    for (int i = LIST_ARRAY_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected i to be equal to stack pop.", i, pop_stack(&test));
    }
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief
TEST test_01_03(void) {
    stack_s test = create_stack();

    push_stack(&test, 2);
    push_stack(&test, 0);
    push_stack(&test, 1);
    push_stack(&test, 4);
    push_stack(&test, 3);
    push_stack(&test, 7);
    push_stack(&test, 5);
    push_stack(&test, 6);
    push_stack(&test, 9);
    push_stack(&test, 8);

    sort_stack(&test, NULL);
    for (int i = LIST_ARRAY_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected i to be equal to stack pop.", i, pop_stack(&test));
    }
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief
TEST test_01_04(void) {
    stack_s test = create_stack();

    push_stack(&test, 10);
    push_stack(&test, 2);
    push_stack(&test, 0);
    push_stack(&test, 1);
    push_stack(&test, 4);
    push_stack(&test, 3);
    push_stack(&test, 7);
    push_stack(&test, 5);
    push_stack(&test, 6);
    push_stack(&test, 9);
    push_stack(&test, 8);

    sort_stack(&test, NULL);
    for (int i = LIST_ARRAY_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected i to be equal to stack pop.", i, pop_stack(&test));
    }
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (sort_stack_test) {
    RUN_TEST(test_01_01);
    RUN_TEST(test_01_02);
    RUN_TEST(test_01_03);
    RUN_TEST(test_01_04);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

SUITE (sort_stack_test) {
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

SUITE (sort_stack_test) {
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

SUITE (sort_stack_test) {
}

#endif
