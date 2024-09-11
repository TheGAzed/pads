#include <greatest.h>

#ifndef TEST_STACK_MODE

#error No stack mode was defined before testing ('TEST_STACK_MODE' is not defined).

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#define STACK_DATA_TYPE int
#define PREPROCESSOR_STACK_SIZE 10
#include "stack.h"

#if   STACK_MODE == INFINITE_LIST_STACK

SUITE (is_full_stack_test) {
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Tests if stack of size 10 is full without pushing anything.
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    ASSERT_FALSEm("[ERROR] Stack cannot be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if stack of size 10 is full if 1 element is pushed.
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 10);
    ASSERT_FALSEm("[ERROR] Stack cannot be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if stack of size 10 is full if 10 elements are pushed.
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    for(size_t i = 0; i < 10; i++) {
        push_stack(&test, 10);
    }
    ASSERTm("[ERROR] Stack must be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if stack of size 10 is full if (10 - 1) elements are pushed.
TEST test_02_04(void) {
    stack_s test = create_stack(10);
    for(size_t i = 0; i < (10 - 1); i++) {
        push_stack(&test, 10);
    }
    ASSERT_FALSEm("[ERROR] Stack cannot be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (is_full_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
    RUN_TEST(test_02_04);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

SUITE (is_full_stack_test) {
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

/// @brief Tests if stack of size 'PREDEFINED_STACK_SIZE' is full without pushing anything.
TEST test_04_01(void) {
    stack_s test = create_stack();
    ASSERT_FALSEm("[ERROR] Stack cannot be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if stack of size 'PREDEFINED_STACK_SIZE' is full if 1 element is pushed.
TEST test_04_02(void) {
    stack_s test = create_stack();
    push_stack(&test, 10);
    ASSERT_FALSEm("[ERROR] Stack cannot be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if stack of size 'PREDEFINED_STACK_SIZE' is full if 'PREDEFINED_STACK_SIZE' elements are pushed.
TEST test_04_03(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < 10; i++) {
        push_stack(&test, 10);
    }
    ASSERTm("[ERROR] Stack must be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if stack of size 'PREDEFINED_STACK_SIZE' is full if ('PREDEFINED_STACK_SIZE' - 1) elements are pushed.
TEST test_04_04(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < (10 - 1); i++) {
        push_stack(&test, 10);
    }
    ASSERT_FALSEm("[ERROR] Stack cannot be full", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (is_full_stack_test) {
    RUN_TEST(test_04_01);
    RUN_TEST(test_04_02);
    RUN_TEST(test_04_03);
    RUN_TEST(test_04_04);
}

#endif
