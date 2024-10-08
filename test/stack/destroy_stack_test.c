#include <greatest.h>
#include <string.h>

#ifndef TEST_STACK_MODE

#error No stack mode was defined before testing ('TEST_STACK_MODE' is not defined).

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#define STACK_DATA_TYPE        char*
#define LIST_ARRAY_STACK_CHUNK 10
#define REALLOC_STACK_CHUNK    10
#include "stack.h"

#define STRING_VALUE "thegazed"
STACK_DATA_TYPE create_string_d(void) {
    STACK_DATA_TYPE string = calloc((sizeof(STRING_VALUE)), sizeof(char));
    assert(string && "[ERROR] Memory allocation failed.");
    strncpy(string, STRING_VALUE, sizeof(STRING_VALUE) - 1);
    return string;
}

void destroy_string_d(STACK_DATA_TYPE * string) {
    free(*string);
}

#if   STACK_MODE == INFINITE_LIST_STACK

/// @brief Tests if size of stack is zeroed when pushing and destroying it.
TEST test_01_01(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);

    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing and destroying it.
TEST test_01_02(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack head must be NULL/have no allocated memory", test.head, NULL);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing 'LIST_ARRAY_STACK_CHUNK' elements and destroying it.
TEST test_01_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, create_string_d());
    }
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack head must be NULL/have no allocated memory", test.head, NULL);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing 'LIST_ARRAY_STACK_CHUNK + 1' elements and destroying it.
TEST test_01_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_d());
    }
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack head must be NULL/have no allocated memory", test.head, NULL);

    PASS();
}

SUITE (destroy_stack_test) {
    RUN_TEST(test_01_01);
    RUN_TEST(test_01_02);
    RUN_TEST(test_01_03);
    RUN_TEST(test_01_04);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Tests if size of stack is zeroed when pushing and destroying it.
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack size must be zero", 0, test.size);

    PASS();
}

/// @brief Tests if maximum size is zeroed when pushing and destroying it.
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack size must be zero", 0, test.max);

    PASS();
}

/// @brief Tests if elements pointer of stack is NULL when pushing and destroying it, has no allocated memory.
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack elements pointer is not NULL", NULL, test.elements);

    PASS();
}

SUITE (destroy_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

/// @brief Tests if size of stack is zeroed when pushing and destroying it.
TEST test_03_01(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);
    ASSERTm("[ERROR] Stack size must be zero", test.size == 0);

    ASSERT_EQm("[ERROR] Stack size must be zero", 0, test.size);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing and destroying it.
TEST test_03_02(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack head must be NULL/have no allocated memory", NULL, test.elements);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing 'REALLOC_STACK_CHUNK' elements and destroying it.
TEST test_03_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, create_string_d());
    }
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack head must be NULL/have no allocated memory", NULL, test.elements);

    PASS();
}

/// @brief Tests if head of stack is NULLed when pushing 'REALLOC_STACK_CHUNK + 1' elements and destroying it.
TEST test_03_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_d());
    }
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack head must be NULL/have no allocated memory", NULL, test.elements);

    PASS();
}

SUITE (destroy_stack_test) {
    RUN_TEST(test_03_01);
    RUN_TEST(test_03_02);
    RUN_TEST(test_03_03);
    RUN_TEST(test_03_04);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

/// @brief Tests if size of stack is zero when creating it.
TEST test_04_01(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_d());
    destroy_stack(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Stack size must be zero", 0, test.size);

    PASS();
}

SUITE (destroy_stack_test) {
    RUN_TEST(test_04_01);
}

#endif
