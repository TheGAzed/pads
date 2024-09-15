#include <greatest.h>

#ifndef TEST_STACK_MODE

#error No stack mode was defined before testing ('TEST_STACK_MODE' is not defined).

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#include "stack.h"

#if   STACK_MODE == INFINITE_LIST_STACK

/// @brief Tests if size of stack is zero when creating it.
TEST test_01_01(void) {
    stack_s test = create_stack();
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if head of stack is NULL when creating it.
TEST test_01_02(void) {
    stack_s test = create_stack();
    ASSERTm("[ERROR] Stack head must be NULL/have no allocated memory", test.head == NULL);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(test_01_01);
    RUN_TEST(test_01_02);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Tests if size of stack is zero when creating it.
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if maximum size is 10 when creating it and adding parameter 10.
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    ASSERTm("[ERROR] Stack maximum size must equal 10", test.max == 10);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if elements pointer of stack is not NULL when creating it, has allocated memory.
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    ASSERTm("[ERROR] Stack elements pointer is NULL", test.elements);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

/// @brief Tests if size of stack is zero when creating it.
TEST test_03_01(void) {
    stack_s test = create_stack();
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if elements array of stack is NULL when creating it.
TEST test_03_02(void) {
    stack_s test = create_stack();
    ASSERT_FALSEm("[ERROR] Stack elements must be NULL", test.elements);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(test_03_01);
    RUN_TEST(test_03_02);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

/// @brief Tests if size of stack is zero when creating it.
TEST test_04_01(void) {
    stack_s test = create_stack();
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if elements array has correct size when creating it.
TEST test_04_02(void) {
    stack_s test = create_stack();
    ASSERTm(
        "[ERROR] Stack array size is invalid",
        (sizeof(test.elements) / sizeof(STACK_DATA_TYPE)) == PREPROCESSOR_STACK_SIZE);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(test_04_01);
    RUN_TEST(test_04_02);
}

#endif
