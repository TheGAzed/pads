#include <greatest.h>
#include <string.h>

#ifndef TEST_STACK_MODE

#error No stack mode was defined before testing ('TEST_STACK_MODE' is not defined).

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#define STRING_VALUE "thegazed"
typedef union test_type {
    int    integer;
    char * character_ptr;
} test_type_u;

#define STACK_DATA_TYPE         test_type_u
#define LIST_ARRAY_STACK_CHUNK  10
#define REALLOC_STACK_CHUNK     10
#define PREPROCESSOR_STACK_SIZE 10
#include "stack.h"

STACK_DATA_TYPE create_string_copy(void) {
    STACK_DATA_TYPE string = { 0 };
    string.character_ptr = malloc((sizeof(STRING_VALUE) * sizeof(char)));
    assert(string.character_ptr && "[ERROR] Memory allocation failed.");
    strncpy(string.character_ptr, STRING_VALUE, sizeof(STRING_VALUE) - 1);
    return string;
}

void destroy_string_copy(STACK_DATA_TYPE * string) {
    free(string->character_ptr);
    string->character_ptr = NULL;
}

STACK_DATA_TYPE copy_string_copy(const STACK_DATA_TYPE source) {
    STACK_DATA_TYPE copy = { 0 };
    copy.character_ptr = malloc(strnlen(source.character_ptr, sizeof(STRING_VALUE) - 1));
    assert(copy.character_ptr && "[ERROR] Memory allocation failed.");
    strncpy(copy.character_ptr, STRING_VALUE, sizeof(STRING_VALUE) - 1);
    return copy;
}

#if   STACK_MODE == INFINITE_LIST_STACK

/// @brief Tests if created test size is equal to copy size
TEST test_01_01(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test head is equal to copy head
TEST test_01_02(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack head of test and copy are different.", test.head, copy.head);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_01_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (test_type_u) { .integer = 42 });
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test head is not equal to copy head after pushing one value
TEST test_01_04(void) {
    stack_s test = create_stack();
    push_stack(&test, (test_type_u) { .integer = 42 });
    stack_s copy = copy_stack(test, NULL);

    ASSERT_NEQm("[ERROR] Stack head of test and copy are different.", test.head, copy.head);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'LIST_ARRAY_STACK_CHUNK' values
TEST test_01_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (test_type_u) { .integer = 42 });
    }

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 values
TEST test_01_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = 42 });
    }

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'LIST_ARRAY_STACK_CHUNK' values
TEST test_01_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 values
TEST test_01_08(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'LIST_ARRAY_STACK_CHUNK' - 1 invalid values
/// and one valid value
TEST test_01_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = -1 });
    }
    push_stack(&test, (test_type_u) { .integer = 42 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", peep_stack(test).integer, peep_stack(copy).integer);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'LIST_ARRAY_STACK_CHUNK' invalid values
/// and one valid value
TEST test_01_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }
    push_stack(&test, (test_type_u) { .integer = 42 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", peep_stack(test).integer, peep_stack(copy).integer);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size
TEST test_01_11(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test head is equal to copy head
TEST test_01_12(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack head of test and copy are different.", test.head, copy.head);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_01_13(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_copy());
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test head is not equal to copy head after pushing one value
TEST test_01_14(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_copy());
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_NEQm("[ERROR] Stack head of test and copy are different.", test.head, copy.head);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'LIST_ARRAY_STACK_CHUNK' values
TEST test_01_15(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 values
TEST test_01_16(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'LIST_ARRAY_STACK_CHUNK' values
TEST test_01_17(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE t = pop_stack(&test);
        STACK_DATA_TYPE c = pop_stack(&copy);
        ASSERTm(
            "[ERROR] Stack pop of test and copy are different.",
            strncmp(t.character_ptr, c.character_ptr, sizeof(STRING_VALUE) - 1) == 0
        );
        destroy_string_copy(&t);
        destroy_string_copy(&c);
    }

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 values
TEST test_01_18(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE t = pop_stack(&test);
        STACK_DATA_TYPE c = pop_stack(&copy);
        ASSERTm(
            "[ERROR] Stack pop of test and copy are different.",
            strncmp(t.character_ptr, c.character_ptr, sizeof(STRING_VALUE) - 1) == 0
        );
        destroy_string_copy(&t);
        destroy_string_copy(&c);
    }

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'LIST_ARRAY_STACK_CHUNK' - 1 values
TEST test_01_19(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, create_string_copy());
    }
    push_stack(&test, create_string_copy());

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERTm(
        "[ERROR] Stack pop of test and copy are different.",
        strncmp(peep_stack(test).character_ptr, peep_stack(copy).character_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 values
TEST test_01_20(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERTm(
        "[ERROR] Stack pop of test and copy are different.",
        strncmp(peep_stack(test).character_ptr, peep_stack(copy).character_ptr, sizeof(STRING_VALUE) - 1) == 0
    );
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

SUITE (copy_stack_test) {
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
    RUN_TEST(test_01_11);
    RUN_TEST(test_01_12);
    RUN_TEST(test_01_13);
    RUN_TEST(test_01_14);
    RUN_TEST(test_01_15);
    RUN_TEST(test_01_16);
    RUN_TEST(test_01_17);
    RUN_TEST(test_01_18);
    RUN_TEST(test_01_19);
    RUN_TEST(test_01_20);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Tests if created test size is equal to copy size
TEST test_02_01(void) {
    stack_s test = create_stack(10);
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test max is equal to copy max
TEST test_02_02(void) {
    stack_s test = create_stack(10);
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.max, copy.max);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_02_03(void) {
    stack_s test = create_stack(10);
    push_stack(&test, (test_type_u) { .integer = 42 });
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test elements pointer is not equal to copy elements pointer after pushing one value
TEST test_02_04(void) {
    stack_s test = create_stack(10);
    stack_s copy = copy_stack(test, NULL);

    ASSERT_NEQm("[ERROR] Stack head of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 10 values
TEST test_02_05(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, (test_type_u) { .integer = 42 });
    }

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'LIST_ARRAY_STACK_CHUNK' values
TEST test_02_06(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < test.max; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 10 values
TEST test_02_07(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < test.max; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 9 invalid values and one valid value
TEST test_02_08(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = -1 });
    }
    push_stack(&test, (test_type_u) { .integer = 42 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", peep_stack(test).integer, peep_stack(copy).integer);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size
TEST test_02_09(void) {
    stack_s test = create_stack(10);
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test max is equal to copy max
TEST test_02_10(void) {
    stack_s test = create_stack(10);
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.max, copy.max);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test elements pointer is not equal to copy elements pointer
TEST test_02_11(void) {
    stack_s test = create_stack(10);
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_NEQm("[ERROR] Stack head of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_02_12(void) {
    stack_s test = create_stack(10);
    push_stack(&test, create_string_copy());
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 9 values
TEST test_02_13(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 10 values
TEST test_02_14(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 10 values
TEST test_02_15(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    for (size_t i = 0; i < test.max; ++i) {
        STACK_DATA_TYPE t = pop_stack(&test);
        STACK_DATA_TYPE c = pop_stack(&copy);
        ASSERTm(
            "[ERROR] Stack pop of test and copy are different.",
            strncmp(t.character_ptr, c.character_ptr, sizeof(STRING_VALUE) - 1) == 0
        );
        destroy_string_copy(&t);
        destroy_string_copy(&c);
    }

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 10 values
TEST test_02_16(void) {
    stack_s test = create_stack(10);
    for (size_t i = 0; i < test.max; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERTm(
        "[ERROR] Stack pop of test and copy are different.",
        strncmp(peep_stack(test).character_ptr, peep_stack(copy).character_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

SUITE (copy_stack_test) {
    RUN_TEST(test_02_01);
    RUN_TEST(test_02_02);
    RUN_TEST(test_02_03);
    RUN_TEST(test_02_04);
    RUN_TEST(test_02_05);
    RUN_TEST(test_02_06);
    RUN_TEST(test_02_07);
    RUN_TEST(test_02_08);
    RUN_TEST(test_02_09);
    RUN_TEST(test_02_10);
    RUN_TEST(test_02_11);
    RUN_TEST(test_02_12);
    RUN_TEST(test_02_13);
    RUN_TEST(test_02_14);
    RUN_TEST(test_02_15);
    RUN_TEST(test_02_16);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

/// @brief Tests if created test size is equal to copy size
TEST test_03_01(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test elements is equal to copy elements
TEST test_03_02(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack elements of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_03_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (test_type_u) { .integer = 42 });
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test elements is not equal to copy elements after pushing one value
TEST test_03_04(void) {
    stack_s test = create_stack();
    push_stack(&test, (test_type_u) { .integer = 42 });
    stack_s copy = copy_stack(test, NULL);

    ASSERT_NEQm("[ERROR] Stack elements of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'REALLOC_STACK_CHUNK' values
TEST test_03_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (test_type_u) { .integer = 42 });
    }

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'REALLOC_STACK_CHUNK' + 1 values
TEST test_03_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = 42 });
    }

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'REALLOC_STACK_CHUNK' values
TEST test_03_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'REALLOC_STACK_CHUNK' + 1 values
TEST test_03_08(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'REALLOC_STACK_CHUNK' - 1 invalid values
/// and one valid value
TEST test_03_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = -1 });
    }
    push_stack(&test, (test_type_u) { .integer = 42 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", peep_stack(test).integer, peep_stack(copy).integer);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'REALLOC_STACK_CHUNK' invalid values
/// and one valid value
TEST test_03_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }
    push_stack(&test, (test_type_u) { .integer = 42 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", peep_stack(test).integer, peep_stack(copy).integer);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size
TEST test_03_11(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test elements is equal to copy elements
TEST test_03_12(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack elements of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_03_13(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_copy());
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test elements is not equal to copy elements after pushing one value
TEST test_03_14(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_copy());
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_NEQm("[ERROR] Stack elements of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'REALLOC_STACK_CHUNK' values
TEST test_03_15(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'REALLOC_STACK_CHUNK' + 1 values
TEST test_03_16(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'REALLOC_STACK_CHUNK' values
TEST test_03_17(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE t = pop_stack(&test);
        STACK_DATA_TYPE c = pop_stack(&copy);
        ASSERTm(
            "[ERROR] Stack pop of test and copy are different.",
            strncmp(t.character_ptr, c.character_ptr, sizeof(STRING_VALUE) - 1) == 0
        );
        destroy_string_copy(&t);
        destroy_string_copy(&c);
    }

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'REALLOC_STACK_CHUNK' + 1 values
TEST test_03_18(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE t = pop_stack(&test);
        STACK_DATA_TYPE c = pop_stack(&copy);
        ASSERTm(
            "[ERROR] Stack pop of test and copy are different.",
            strncmp(t.character_ptr, c.character_ptr, sizeof(STRING_VALUE) - 1) == 0
        );
        destroy_string_copy(&t);
        destroy_string_copy(&c);
    }

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'LIST_ARRAY_STACK_CHUNK' - 1 values
TEST test_03_19(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, create_string_copy());
    }
    push_stack(&test, create_string_copy());

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERTm(
        "[ERROR] Stack pop of test and copy are different.",
        strncmp(peep_stack(test).character_ptr, peep_stack(copy).character_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'LIST_ARRAY_STACK_CHUNK' + 1 values
TEST test_03_20(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERTm(
        "[ERROR] Stack pop of test and copy are different.",
        strncmp(peep_stack(test).character_ptr, peep_stack(copy).character_ptr, sizeof(STRING_VALUE) - 1) == 0
    );
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

SUITE (copy_stack_test) {
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
    RUN_TEST(test_03_11);
    RUN_TEST(test_03_12);
    RUN_TEST(test_03_13);
    RUN_TEST(test_03_14);
    RUN_TEST(test_03_15);
    RUN_TEST(test_03_16);
    RUN_TEST(test_03_17);
    RUN_TEST(test_03_18);
    RUN_TEST(test_03_19);
    RUN_TEST(test_03_20);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

/// @brief Tests if created test size is equal to copy size
TEST test_04_01(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_04_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (test_type_u) { .integer = 42 });
    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test elements pointer is not equal to copy elements pointer after pushing one value
TEST test_04_03(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, NULL);

    ASSERT_NEQm("[ERROR] Stack head of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 10 values
TEST test_04_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (test_type_u) { .integer = 42 });
    }

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 9 values
TEST test_04_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 10 values
TEST test_04_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (test_type_u) { .integer = (int)i });
    }

    stack_s copy = copy_stack(test, NULL);

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", pop_stack(&test).integer, pop_stack(&copy).integer);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 9 invalid values and one valid value
TEST test_04_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (test_type_u) { .integer = -1 });
    }
    push_stack(&test, (test_type_u) { .integer = 42 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ERROR] Stack pop of test and copy are different.", peep_stack(test).integer, peep_stack(copy).integer);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);

    PASS();
}

/// @brief Tests if created test size is equal to copy size
TEST test_04_08(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test elements pointer is not equal to copy elements pointer
TEST test_04_09(void) {
    stack_s test = create_stack();
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_NEQm("[ERROR] Stack head of test and copy are different.", test.elements, copy.elements);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing one value
TEST test_04_10(void) {
    stack_s test = create_stack();
    push_stack(&test, create_string_copy());
    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'PREPROCESSOR_STACK_SIZE' - 1 values
TEST test_04_11(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test size is equal to copy size after pushing 'PREPROCESSOR_STACK_SIZE' values
TEST test_04_12(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERT_EQm("[ERROR] Stack size of test and copy are different.", test.size, copy.size);
    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test pops are equal to copy pops after pushing 'PREPROCESSOR_STACK_SIZE' values
TEST test_04_13(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        STACK_DATA_TYPE t = pop_stack(&test);
        STACK_DATA_TYPE c = pop_stack(&copy);
        ASSERTm(
            "[ERROR] Stack pop of test and copy are different.",
            strncmp(t.character_ptr, c.character_ptr, sizeof(STRING_VALUE) - 1) == 0
        );
        destroy_string_copy(&t);
        destroy_string_copy(&c);
    }

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

/// @brief Tests if created test peep is equal to copy peep after pushing 'PREPROCESSOR_STACK_SIZE' values
TEST test_04_14(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, create_string_copy());
    }

    stack_s copy = copy_stack(test, copy_string_copy);

    ASSERTm(
        "[ERROR] Stack pop of test and copy are different.",
        strncmp(peep_stack(test).character_ptr, peep_stack(copy).character_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_stack(&test, destroy_string_copy);
    destroy_stack(&copy, destroy_string_copy);

    PASS();
}

SUITE (copy_stack_test) {
    RUN_TEST(test_04_01);
    RUN_TEST(test_04_02);
    RUN_TEST(test_04_03);
    RUN_TEST(test_04_04);
    RUN_TEST(test_04_05);
    RUN_TEST(test_04_06);
    RUN_TEST(test_04_07);
    RUN_TEST(test_04_08);
    RUN_TEST(test_04_09);
    RUN_TEST(test_04_10);
    RUN_TEST(test_04_11);
    RUN_TEST(test_04_12);
    RUN_TEST(test_04_13);
    RUN_TEST(test_04_14);
}

#endif
