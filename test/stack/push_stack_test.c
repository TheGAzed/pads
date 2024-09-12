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

#if STACK_MODE == INFINITE_LIST_STACK

/// @brief Test if one push is correct
TEST test_01_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if one push has correct stack size
TEST test_01_02(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);

    ASSERTm("[ERROR] Stack size must be one (1).", 1 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'LIST_ARRAY_STACK_CHUNK' pushes have valid value at top
TEST test_01_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'LIST_ARRAY_STACK_CHUNK' + 1 pushes have valid value at top
TEST test_01_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'LIST_ARRAY_STACK_CHUNK' pushes have correct size (equal to 'LIST_ARRAY_STACK_CHUNK').
TEST test_01_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERTm("[ERROR] Stack size must be 'LIST_ARRAY_STACK_CHUNK'.", LIST_ARRAY_STACK_CHUNK == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'LIST_ARRAY_STACK_CHUNK' + 1 pushes have correct size (equal to 'LIST_ARRAY_STACK_CHUNK').
TEST test_01_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERTm("[ERROR] Stack size must be 'LIST_ARRAY_STACK_CHUNK' + 1.", (LIST_ARRAY_STACK_CHUNK + 1) == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if peeped element is valid after 'LIST_ARRAY_STACK_CHUNK' pushes and one pop
TEST test_01_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if peeped element is valid after 'LIST_ARRAY_STACK_CHUNK' pushes and 'LIST_ARRAY_STACK_CHUNK' pop
TEST test_01_08(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if stack is empty after pushing and poping 'LIST_ARRAY_STACK_CHUNK'
TEST test_01_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Stack size must be zero (0)", 0 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if stack head is NULL after pushing and poping 'LIST_ARRAY_STACK_CHUNK'
TEST test_01_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Stack head must be NULL", NULL == test.head);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (push_stack_test) {
    RUN_TEST(test_01_01);
    RUN_TEST(test_01_02);
    RUN_TEST(test_01_03);
    RUN_TEST(test_01_04);
    RUN_TEST(test_01_05);
    RUN_TEST(test_01_06);
    RUN_TEST(test_01_07);
    RUN_TEST(test_01_08);
    RUN_TEST(test_01_09);
    RUN_TEST(test_01_10);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Test if one push is correct
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if one push has correct stack size
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);
    ASSERTm("[ERROR] Stack size must be one (1).", 1 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 10 pushes have valid value at top
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < 9; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 10 pushes have correct size (equal to 10).
TEST test_02_04(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < 9; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Stack size must be 10", 10 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if peeped element is valid after 10 pushes and one pop
TEST test_02_05(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < 8; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if first added element is valid after 9 pushes and 9 pop
TEST test_02_06(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);
    for (size_t i = 0; i < 9; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < 9; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if stack size is zero after pushing and poping stack max values
TEST test_02_07(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < test.max; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Stack size must be zero (0)", 0 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (push_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
    RUN_TEST(test_02_04);
    RUN_TEST(test_02_05);
    RUN_TEST(test_02_06);
    RUN_TEST(test_02_07);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

/// @brief Test if one push is correct
TEST test_03_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if one push has correct stack size
TEST test_03_02(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    ASSERTm("[ERROR] Stack size must be one (1).", 1 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'REALLOC_STACK_CHUNK' pushes have valid value at top
TEST test_03_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'REALLOC_STACK_CHUNK' + 1 pushes have valid value at top
TEST test_03_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'LIST_ARRAY_STACK_CHUNK' pushes have correct size (equal to 'REALLOC_STACK_CHUNK').
TEST test_03_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Stack size must be 'REALLOC_STACK_CHUNK'.", REALLOC_STACK_CHUNK == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'REALLOC_STACK_CHUNK' + 1 pushes have correct size (equal to 'REALLOC_STACK_CHUNK').
TEST test_03_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Stack size must be 'REALLOC_STACK_CHUNK' + 1.", (REALLOC_STACK_CHUNK + 1) == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if peeped element is valid after 'REALLOC_STACK_CHUNK' pushes and one pop
TEST test_03_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if peeped element is valid after 'REALLOC_STACK_CHUNK' pushes and 'REALLOC_STACK_CHUNK' pop
TEST test_03_08(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if stack is empty after pushing and poping 'REALLOC_STACK_CHUNK'
TEST test_03_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Stack size must be zero (0)", 0 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (push_stack_test) {
    RUN_TEST(test_03_01);
    RUN_TEST(test_03_02);
    RUN_TEST(test_03_03);
    RUN_TEST(test_03_04);
    RUN_TEST(test_03_05);
    RUN_TEST(test_03_06);
    RUN_TEST(test_03_07);
    RUN_TEST(test_03_08);
    RUN_TEST(test_03_09);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK


/// @brief Test if one push is correct
TEST test_04_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if one push has correct stack size
TEST test_04_02(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    ASSERTm("[ERROR] Stack size must be one (1).", 1 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'PREPROCESSOR_STACK_SIZE' pushes have valid value at top
TEST test_04_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if 'PREPROCESSOR_STACK_SIZE' pushes have correct size (equal to 'PREPROCESSOR_STACK_SIZE').
TEST test_04_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    ASSERTm("[ERROR] Stack size must be 'PREPROCESSOR_STACK_SIZE'", PREPROCESSOR_STACK_SIZE == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if peeped element is valid after 'PREPROCESSOR_STACK_SIZE' pushes and one pop
TEST test_04_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 2; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if first added element is valid after 'PREPROCESSOR_STACK_SIZE' - 1 pushes
/// and 'PREPROCESSOR_STACK_SIZE' - 1 pop
TEST test_04_06(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Peeped stack element must equal 42", 42 == peep_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// @brief Test if stack size is zero after pushing and poping 'PREPROCESSOR_STACK_SIZE' values
TEST test_04_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, -1);
    }
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ERROR] Stack size must be zero (0)", 0 == test.size);
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (push_stack_test) {
    RUN_TEST(test_04_01);
    RUN_TEST(test_04_02);
    RUN_TEST(test_04_03);
    RUN_TEST(test_04_04);
    RUN_TEST(test_04_05);
    RUN_TEST(test_04_06);
    RUN_TEST(test_04_07);
}

#endif