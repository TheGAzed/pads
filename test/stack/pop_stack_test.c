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

/// @brief Test if poped value is correct after pushing it
TEST test_01_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing one invalid and one valid
TEST test_01_02(void) {
    stack_s test = create_stack();
    push_stack(&test, -1);
    push_stack(&test, 42);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 'LIST_ARRAY_STACK_CHUNK' - 1 invalid ones and one valid
TEST test_01_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 'LIST_ARRAY_STACK_CHUNK' - 1 invalid ones and one valid,
/// one more invalid and poping twice
TEST test_01_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct 'LIST_ARRAY_STACK_CHUNK' invalid ones and one valid
TEST test_01_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing and poping once
TEST test_01_06(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero (0).", 0, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing two and poping once
TEST test_01_07(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be one (1).", 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing 'LIST_ARRAY_STACK_CHUNK' and poping once
TEST test_01_08(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'LIST_ARRAY_STACK_CHUNK' - 1.", LIST_ARRAY_STACK_CHUNK - 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 and poping once
TEST test_01_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'LIST_ARRAY_STACK_CHUNK'.", LIST_ARRAY_STACK_CHUNK, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 and poping two times
TEST test_01_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'LIST_ARRAY_STACK_CHUNK' - 1.", LIST_ARRAY_STACK_CHUNK - 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

SUITE (pop_stack_test) {
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

/// @brief Test if poped value is correct after pushing it
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing one invalid and one valid
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    push_stack(&test, -1);
    push_stack(&test, 42);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 9 invalid ones and one valid
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < 9; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 8 invalid ones and one valid, one more invalid and poping
/// twice
TEST test_02_04(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < 8; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after push and pop
TEST test_02_05(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero (0).", 0, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after two pushes and pop
TEST test_02_06(void) {
    stack_s test = create_stack(10);
    push_stack(&test, 42);
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be one (1).", 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after 10 pushes and pop
TEST test_02_07(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be nine (9).", 9, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after 10 pushes and two pops
TEST test_02_08(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be eight (8).", 8, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

SUITE (pop_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
    RUN_TEST(test_02_04);
    RUN_TEST(test_02_05);
    RUN_TEST(test_02_06);
    RUN_TEST(test_02_07);
    RUN_TEST(test_02_08);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

/// @brief Test if poped value is correct after pushing it
TEST test_03_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing one invalid and one valid
TEST test_03_02(void) {
    stack_s test = create_stack();
    push_stack(&test, -1);
    push_stack(&test, 42);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 'REALLOC_STACK_CHUNK' - 1 invalid ones and one valid
TEST test_03_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 'REALLOC_STACK_CHUNK' - 1 invalid ones and one valid,
/// one more invalid and poping twice
TEST test_03_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing it and 'REALLOC_STACK_CHUNK' invalid ones
TEST test_03_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERTm("[ERROR] Expected poped value 42.", 42 == pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing and poping once
TEST test_03_06(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero (0).", 0, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing two and poping once
TEST test_03_07(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be one (1).", 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing 'REALLOC_STACK_CHUNK' and poping once
TEST test_03_08(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'REALLOC_STACK_CHUNK' - 1.", REALLOC_STACK_CHUNK - 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing 'REALLOC_STACK_CHUNK' + 1 and poping once
TEST test_03_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'REALLOC_STACK_CHUNK'.", REALLOC_STACK_CHUNK, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after pushing 'REALLOC_STACK_CHUNK' + 1 and poping two times
TEST test_03_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'REALLOC_STACK_CHUNK' - 1.", REALLOC_STACK_CHUNK - 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

SUITE (pop_stack_test) {
    RUN_TEST(test_03_01);
    RUN_TEST(test_03_02);
    RUN_TEST(test_03_03);
    RUN_TEST(test_03_04);
    RUN_TEST(test_03_05);
    RUN_TEST(test_03_06);
    RUN_TEST(test_03_07);
    RUN_TEST(test_03_08);
    RUN_TEST(test_03_09);
    RUN_TEST(test_03_10);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

/// @brief Test if poped value is correct after pushing it
TEST test_04_01(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing one invalid and one valid
TEST test_04_02(void) {
    stack_s test = create_stack();
    push_stack(&test, -1);
    push_stack(&test, 42);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 9 invalid ones and one valid
TEST test_04_03(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if poped value is correct after pushing 8 invalid ones and one valid, one more invalid and poping
/// twice
TEST test_04_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 2; ++i) {
        push_stack(&test, -1);
    }
    push_stack(&test, 42);
    push_stack(&test, -1);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected poped value 42.", 42, pop_stack(&test));
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after push and pop
TEST test_04_05(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero (0).", 0, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after two pushes and pop
TEST test_04_06(void) {
    stack_s test = create_stack();
    push_stack(&test, 42);
    push_stack(&test, 42);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be one (1).", 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after 'PREPROCESSOR_STACK_SIZE' pushes and pop
TEST test_04_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'PREPROCESSOR_STACK_SIZE' - 1.", PREPROCESSOR_STACK_SIZE - 1, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

/// @brief Test if size is correct after 'PREPROCESSOR_STACK_SIZE' pushes and two pops
TEST test_04_08(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, 42);
    }
    pop_stack(&test);
    pop_stack(&test);

    ASSERT_EQm("[ERROR] Expected size to be 'PREPROCESSOR_STACK_SIZE' - 2.", PREPROCESSOR_STACK_SIZE - 2, test.size);
    destroy_stack(&test, NULL);
    PASS();
}

SUITE (pop_stack_test) {
    RUN_TEST(test_04_01);
    RUN_TEST(test_04_02);
    RUN_TEST(test_04_03);
    RUN_TEST(test_04_04);
    RUN_TEST(test_04_05);
    RUN_TEST(test_04_06);
    RUN_TEST(test_04_07);
    RUN_TEST(test_04_08);
}

#endif
