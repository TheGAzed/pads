#include <greatest.h>
#include <string.h>

#ifndef TEST_STACK_MODE

#error No stack mode was defined before testing ('TEST_STACK_MODE' is not defined).

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#define STACK_DATA_TYPE char*
#define STACK_LIST_ARRAY_SIZE 10
#include "stack.h"

void destroy_string(char ** string) {
    free(*string);
}

#if   STACK_MODE == INFINITE_STACK

/// @brief Tests if size of stack is zeroed when pushing and destroying it.
TEST test_01_01(void) {
    stack_s test = create_stack();
    push_stack(&test, strdup("thegazed"));
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing and destroying it.
TEST test_01_02(void) {
    stack_s test = create_stack();
    push_stack(&test, strdup("thegazed"));
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack head must be NULL/have no allocated memory", test.head == NULL);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing 'STACK_LIST_ARRAY_SIZE' elements and destroying it.
TEST test_01_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < STACK_LIST_ARRAY_SIZE; ++i) {
        push_stack(&test, strdup("thegazed"));
    }
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack head must be NULL/have no allocated memory", test.head == NULL);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing 'STACK_LIST_ARRAY_SIZE + 1' elements and destroying it.
TEST test_01_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < STACK_LIST_ARRAY_SIZE + 1; ++i) {
        push_stack(&test, strdup("thegazed"));
    }
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack head must be NULL/have no allocated memory", test.head == NULL);

    PASS();
}

SUITE (destroy_stack_test) {
    RUN_TEST(test_01_01);
    RUN_TEST(test_01_02);
    RUN_TEST(test_01_03);
    RUN_TEST(test_01_04);
}

#elif STACK_MODE == FINITE_STACK

/// @brief Tests if size of stack is zeroed when pushing and destroying it.
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    push_stack(&test, strdup("thegazed"));
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);

    PASS();
}

/// @brief Tests if maximum size is zeroed when pushing and destroying it.
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    push_stack(&test, strdup("thegazed"));
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack maximum size must be zero", test.max == 0);

    PASS();
}

/// @brief Tests if elements pointer of stack is NULL when pushing and destroying it, has no allocated memory.
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    push_stack(&test, strdup("thegazed"));
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack elements pointer is not NULL", !test.elements);

    PASS();
}

SUITE (destroy_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
}

#elif STACK_MODE == PREDEFINED_STACK

/// @brief Tests if size of stack is zero when creating it.
TEST test_03_01(void) {
    stack_s test = create_stack();
    push_stack(&test, strdup("thegazed"));
    destroy_stack(&test, destroy_string);
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);

    PASS();
}

SUITE (destroy_stack_test) {
    RUN_TEST(test_03_01);
}

#endif