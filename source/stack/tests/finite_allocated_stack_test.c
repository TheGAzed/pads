#include "stack_test.h"

#include <functions.h>

#define STACK_DATA_TYPE DATA_TYPE
#define STACK_MODE FINITE_ALLOCATED_STACK_MODE
#include <stack/stack.h>

#define MAXIMUM_STACK_SIZE  (1 << 4)

TEST FAS_CREATE_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_DESTROY_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_DESTROY_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_DESTROY_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_DESTROY_04(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_DESTROY_05(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_DESTROY_06(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_DESTROY_07(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_DESTROY_08(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAS_IS_FULL_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    ASSERT_FALSEm("[FAS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_IS_FULL_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[FAS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_IS_FULL_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (size_t i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[FAS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_IS_FULL_04(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (size_t i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERTm("[FAS-ERROR] Expected stack to be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_PEEP_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[FAS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_PEEP_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_PEEP_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_PUSH_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_PUSH_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = MAXIMUM_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_PUSH_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = MAXIMUM_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_POP_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_POP_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = MAXIMUM_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_POP_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = MAXIMUM_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_COPY_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FAS_COPY_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[FAS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FAS_COPY_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[FAS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FAS_COPY_04(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        ASSERT_EQm("[FAS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FAS_COPY_05(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FAS_COPY_06(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[FAS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FAS_COPY_07(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[FAS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FAS_COPY_08(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FAS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        ASSERT_STRN_EQm("[FAS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FAS_IS_EMPTY_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    ASSERTm("[FAS-ERROR] Expected stack to be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_IS_EMPTY_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FAS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_IS_EMPTY_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FAS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_CLEAR_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_CLEAR_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_CLEAR_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_CLEAR_04(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_CLEAR_05(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FAS_CLEAR_06(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FAS_CLEAR_07(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FAS_CLEAR_08(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FAS_FOREACH_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[FAS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FAS_FOREACH_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = MAXIMUM_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FAS_FOREACH_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = MAXIMUM_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FAS_FOREACH_04(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[FAS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FAS_FOREACH_05(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FAS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FAS_FOREACH_06(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FAS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FAS_FOREVERY_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    forevery_stack(&test, sort_int, compare_int);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_FOREVERY_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    forevery_stack(&test, sort_int, compare_int);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_FOREVERY_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = (MAXIMUM_STACK_SIZE - 1) >> 1; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_STACK_SIZE - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    forevery_stack(&test, sort_int, compare_int);

    for (int i = MAXIMUM_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_FOREVERY_04(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = (MAXIMUM_STACK_SIZE) >> 1; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_STACK_SIZE) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    forevery_stack(&test, sort_int, compare_int);

    for (int i = MAXIMUM_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_FOREVERY_05(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = (MAXIMUM_STACK_SIZE - 1) >> 1; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_STACK_SIZE - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    forevery_stack(&test, sort_int, compare_reverse_int);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[FAS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FAS_FOREVERY_06(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = (MAXIMUM_STACK_SIZE) >> 1; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_STACK_SIZE) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    forevery_stack(&test, sort_int, compare_reverse_int);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        ASSERT_EQm("[FAS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

SUITE (finite_allocated_stack_test) {
    // create
    RUN_TEST(FAS_CREATE_01);
    // destroy
    RUN_TEST(FAS_DESTROY_01); RUN_TEST(FAS_DESTROY_02); RUN_TEST(FAS_DESTROY_03); RUN_TEST(FAS_DESTROY_04); RUN_TEST(FAS_DESTROY_05);
    RUN_TEST(FAS_DESTROY_06); RUN_TEST(FAS_DESTROY_07); RUN_TEST(FAS_DESTROY_08);
    // is full
    RUN_TEST(FAS_IS_FULL_01); RUN_TEST(FAS_IS_FULL_02); RUN_TEST(FAS_IS_FULL_03); RUN_TEST(FAS_IS_FULL_04);
    // peep
    RUN_TEST(FAS_PEEP_01); RUN_TEST(FAS_PEEP_02); RUN_TEST(FAS_PEEP_03);
    // push
    RUN_TEST(FAS_PUSH_01); RUN_TEST(FAS_PUSH_02); RUN_TEST(FAS_PUSH_03);
    // pop
    RUN_TEST(FAS_POP_01); RUN_TEST(FAS_POP_02); RUN_TEST(FAS_POP_03);
    // copy
    RUN_TEST(FAS_COPY_01); RUN_TEST(FAS_COPY_02); RUN_TEST(FAS_COPY_03); RUN_TEST(FAS_COPY_04); RUN_TEST(FAS_COPY_05);
    RUN_TEST(FAS_COPY_06); RUN_TEST(FAS_COPY_07); RUN_TEST(FAS_COPY_08);
    // is empty
    RUN_TEST(FAS_IS_EMPTY_01); RUN_TEST(FAS_IS_EMPTY_02); RUN_TEST(FAS_IS_EMPTY_03);
    // clear
    RUN_TEST(FAS_CLEAR_01); RUN_TEST(FAS_CLEAR_02); RUN_TEST(FAS_CLEAR_03); RUN_TEST(FAS_CLEAR_04); RUN_TEST(FAS_CLEAR_05);
    RUN_TEST(FAS_CLEAR_06); RUN_TEST(FAS_CLEAR_07); RUN_TEST(FAS_CLEAR_08);
    // foreach
    RUN_TEST(FAS_FOREACH_01); RUN_TEST(FAS_FOREACH_02); RUN_TEST(FAS_FOREACH_03); RUN_TEST(FAS_FOREACH_04); RUN_TEST(FAS_FOREACH_05);
    RUN_TEST(FAS_FOREACH_06);
    // foevery
    RUN_TEST(FAS_FOREVERY_01); RUN_TEST(FAS_FOREVERY_02); RUN_TEST(FAS_FOREVERY_03); RUN_TEST(FAS_FOREVERY_04); RUN_TEST(FAS_FOREVERY_05);
    RUN_TEST(FAS_FOREVERY_06);
}
