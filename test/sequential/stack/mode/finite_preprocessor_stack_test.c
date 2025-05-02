#include "stack_test.h"

#include <functions.h>

#define STACK_DATA_TYPE DATA_TYPE
#define STACK_MODE FINITE_PREPROCESSOR_STACK_MODE
#define PREPROCESSOR_STACK_SIZE  (1 << 4)
#include <sequential/stack/stack.h>

TEST FPS_CREATE_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_DESTROY_01(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_DESTROY_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_DESTROY_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_DESTROY_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_DESTROY_05(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_DESTROY_06(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_DESTROY_07(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_DESTROY_08(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST FPS_IS_FULL_01(void) {
    stack_s test = create_stack();

    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_IS_FULL_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_IS_FULL_03(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_IS_FULL_04(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERTm("[FPS-ERROR] Expected stack to be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_PEEP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[FPS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_PEEP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_PEEP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_PUSH_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_PUSH_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = PREPROCESSOR_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_PUSH_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_POP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_POP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = PREPROCESSOR_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_POP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_COPY_01(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FPS_COPY_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[FPS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FPS_COPY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[FPS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FPS_COPY_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        ASSERT_EQm("[FPS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST FPS_COPY_05(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FPS_COPY_06(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[FPS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FPS_COPY_07(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[FPS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FPS_COPY_08(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[FPS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        ASSERT_STRN_EQm("[FPS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST FPS_IS_EMPTY_01(void) {
    stack_s test = create_stack();

    ASSERTm("[FPS-ERROR] Expected stack to be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_IS_EMPTY_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_IS_EMPTY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_CLEAR_01(void) {
    stack_s test = create_stack();

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_CLEAR_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_CLEAR_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_CLEAR_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_CLEAR_05(void) {
    stack_s test = create_stack();

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FPS_CLEAR_06(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FPS_CLEAR_07(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FPS_CLEAR_08(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST FPS_FOREACH_01(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[FPS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FPS_FOREACH_02(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = PREPROCESSOR_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FPS_FOREACH_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FPS_FOREACH_04(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[FPS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FPS_FOREACH_05(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FPS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FPS_FOREACH_06(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FPS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FPS_MAP_01(void) {
    stack_s test = create_stack();

    map_stack(&test, sort_int, compare_int);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_MAP_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    map_stack(&test, sort_int, compare_int);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_MAP_03(void) {
    stack_s test = create_stack();

    for (int i = (PREPROCESSOR_STACK_SIZE - 1) >> 1; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_STACK_SIZE - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int);

    for (int i = PREPROCESSOR_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_MAP_04(void) {
    stack_s test = create_stack();

    for (int i = (PREPROCESSOR_STACK_SIZE) >> 1; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_STACK_SIZE) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int);

    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_MAP_05(void) {
    stack_s test = create_stack();

    for (int i = (PREPROCESSOR_STACK_SIZE - 1) >> 1; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_STACK_SIZE - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FPS_MAP_06(void) {
    stack_s test = create_stack();

    for (int i = (PREPROCESSOR_STACK_SIZE) >> 1; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_STACK_SIZE) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

SUITE (finite_preprocessor_stack_test) {
    // create
    RUN_TEST(FPS_CREATE_01);
    // destroy
    RUN_TEST(FPS_DESTROY_01); RUN_TEST(FPS_DESTROY_02); RUN_TEST(FPS_DESTROY_03); RUN_TEST(FPS_DESTROY_04); RUN_TEST(FPS_DESTROY_05);
    RUN_TEST(FPS_DESTROY_06); RUN_TEST(FPS_DESTROY_07); RUN_TEST(FPS_DESTROY_08);
    // is full
    RUN_TEST(FPS_IS_FULL_01); RUN_TEST(FPS_IS_FULL_02); RUN_TEST(FPS_IS_FULL_03); RUN_TEST(FPS_IS_FULL_04);
    // peep
    RUN_TEST(FPS_PEEP_01); RUN_TEST(FPS_PEEP_02); RUN_TEST(FPS_PEEP_03);
    // push
    RUN_TEST(FPS_PUSH_01); RUN_TEST(FPS_PUSH_02); RUN_TEST(FPS_PUSH_03);
    // pop
    RUN_TEST(FPS_POP_01); RUN_TEST(FPS_POP_02); RUN_TEST(FPS_POP_03);
    // copy
    RUN_TEST(FPS_COPY_01); RUN_TEST(FPS_COPY_02); RUN_TEST(FPS_COPY_03); RUN_TEST(FPS_COPY_04); RUN_TEST(FPS_COPY_05);
    RUN_TEST(FPS_COPY_06); RUN_TEST(FPS_COPY_07); RUN_TEST(FPS_COPY_08);
    // is empty
    RUN_TEST(FPS_IS_EMPTY_01); RUN_TEST(FPS_IS_EMPTY_02); RUN_TEST(FPS_IS_EMPTY_03);
    // clear
    RUN_TEST(FPS_CLEAR_01); RUN_TEST(FPS_CLEAR_02); RUN_TEST(FPS_CLEAR_03); RUN_TEST(FPS_CLEAR_04); RUN_TEST(FPS_CLEAR_05);
    RUN_TEST(FPS_CLEAR_06); RUN_TEST(FPS_CLEAR_07); RUN_TEST(FPS_CLEAR_08);
    // foreach
    RUN_TEST(FPS_FOREACH_01); RUN_TEST(FPS_FOREACH_02); RUN_TEST(FPS_FOREACH_03); RUN_TEST(FPS_FOREACH_04); RUN_TEST(FPS_FOREACH_05);
    RUN_TEST(FPS_FOREACH_06);
    // map
    RUN_TEST(FPS_MAP_01); RUN_TEST(FPS_MAP_02); RUN_TEST(FPS_MAP_03); RUN_TEST(FPS_MAP_04); RUN_TEST(FPS_MAP_05);
    RUN_TEST(FPS_MAP_06);
}
