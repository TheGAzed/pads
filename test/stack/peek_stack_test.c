#include <greatest.h>

#ifndef TEST_STACK_MODE

#error No stack mode was defined before testing ('TEST_STACK_MODE' is not defined).

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#define STACK_DATA_TYPE         int
#define LIST_ARRAY_STACK_CHUNK  10
#define REALLOC_STACK_CHUNK     10
#define PREPROCESSOR_STACK_SIZE 10
#include "stack.h"

#if   STACK_MODE == INFINITE_LIST_STACK

/// @brief Tests if peeked first element is correct.
TEST test_01_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked second added value is correct.
TEST test_01_02(void) {
    stack_s test = create_stack();
    push_stack(&test, -1);
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked first value is correct after pushing and poping invalid value.
TEST test_01_03(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked value is correct when reaching 'LIST_ARRAY_STACK_CHUNK' size.
TEST test_01_04(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; i++) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42); // adding last element to 'LIST_ARRAY_STACK_CHUNK' array
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked value is correct when exceeding 'LIST_ARRAY_STACK_CHUNK' size by one.
TEST test_01_05(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; i++) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42); // exceeding 'LIST_ARRAY_STACK_CHUNK' size
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked element is correct when exceeding 'LIST_ARRAY_STACK_CHUNK' size by one
/// and then poping back to 'LIST_ARRAY_STACK_CHUNK' size.
TEST test_01_06(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; i++) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42); // adding last element to 'LIST_ARRAY_STACK_CHUNK' array
    push_stack(&test, -1); // exceeding 'LIST_ARRAY_STACK_CHUNK' size
    pop_stack(&test);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked element is correct when pushing correct value first, then pushing 'LIST_ARRAY_STACK_CHUNK'
/// number of invalid values and lastly poping 'LIST_ARRAY_STACK_CHUNK' number of invalid values.
TEST test_01_07(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; i++) {
        push_stack(&test, -1);
    }
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; i++) {
        pop_stack(&test);
    }
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (peek_stack_test) {
    RUN_TEST(test_01_01);
    RUN_TEST(test_01_02);
    RUN_TEST(test_01_03);
    RUN_TEST(test_01_04);
    RUN_TEST(test_01_05);
    RUN_TEST(test_01_06);
    RUN_TEST(test_01_07);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Tests if peeked first element is correct.
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked second added value is correct.
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    push_stack(&test, -1);
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked first value is correct after pushing and poping invalid value.
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (peek_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

/// @brief Tests if peeked first element is correct.
TEST test_03_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked second added value is correct.
TEST test_03_02(void) {
    stack_s test = create_stack();
    push_stack(&test, -1);
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked first value is correct after pushing and poping invalid value.
TEST test_03_03(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked value is correct when reaching 'REALLOC_STACK_CHUNK' size.
TEST test_03_04(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; i++) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42); // adding last element to 'LIST_ARRAY_STACK_CHUNK' array
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked value is correct when exceeding 'REALLOC_STACK_CHUNK' size by one.
TEST test_03_05(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; i++) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42); // exceeding 'LIST_ARRAY_STACK_CHUNK' size
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked element is correct when exceeding 'REALLOC_STACK_CHUNK' size by one
/// and then poping back to 'LIST_ARRAY_STACK_CHUNK' size.
TEST test_03_06(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; i++) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42); // adding last element to 'LIST_ARRAY_STACK_CHUNK' array
    push_stack(&test, -1); // exceeding 'LIST_ARRAY_STACK_CHUNK' size
    pop_stack(&test);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked element is correct when pushing correct value first, then pushing 'LIST_ARRAY_STACK_CHUNK'
/// number of invalid values and lastly poping 'REALLOC_STACK_CHUNK' number of invalid values.
TEST test_03_07(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; i++) {
        push_stack(&test, -1);
    }
    for(size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; i++) {
        pop_stack(&test);
    }
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (peek_stack_test) {
    RUN_TEST(test_03_01);
    RUN_TEST(test_03_02);
    RUN_TEST(test_03_03);
    RUN_TEST(test_03_04);
    RUN_TEST(test_03_05);
    RUN_TEST(test_03_06);
    RUN_TEST(test_03_07);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

/// @brief Tests if peeked first element is correct.
TEST test_04_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked second added value is correct.
TEST test_04_02(void) {
    stack_s test = create_stack();
    push_stack(&test, -1);
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked first value is correct after pushing and poping invalid value.
TEST test_04_03(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if peeked value is correct after filling stack to 'PREPROCESSOR_STACK_SIZE' with invalid values.
TEST test_04_04(void) {
    stack_s test = create_stack();
    for(size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; i++) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Tests if first added peeked value is correct after filling stack to 'PREPROCESSOR_STACK_SIZE' with
/// invalid values and then popping all but first.
TEST test_04_05(void) {
    stack_s test = create_stack();

    push_stack(&test, 42);
    for(size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; i++) {
        push_stack(&test, -1);
    }
    for(size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; i++) {
        pop_stack(&test);
    }
    ASSERTm("[ERROR] Peeked stack element must equal 42", 42 == peek_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (peek_stack_test) {
    RUN_TEST(test_04_01);
    RUN_TEST(test_04_02);
    RUN_TEST(test_04_03);
    RUN_TEST(test_04_04);
    RUN_TEST(test_04_05);
}

#endif
