#include "stack_test.h"

#include <functions.h>

#define STACK_DATA_TYPE DATA_TYPE
#define STACK_MODE INFINITE_LIST_STACK_MODE
#define LIST_ARRAY_STACK_CHUNK (1 << 4)
#include <sequential/stack/stack.h>

TEST ILS_CREATE_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_DESTROY_01(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_05(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_06(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_07(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_08(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_09(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_DESTROY_10(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

TEST ILS_IS_FULL_01(void) {
    stack_s test = create_stack();

    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_IS_FULL_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_IS_FULL_03(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_IS_FULL_04(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_IS_FULL_05(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PEEP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[ILS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PEEP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PEEP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PEEP_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PEEP_05(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PUSH_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PUSH_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PUSH_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_PUSH_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_POP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_POP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_POP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_POP_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_COPY_01(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_EQm("[ILS-ERROR] Expected heads to be equal", test.head, copy.head);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST ILS_COPY_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    ASSERT_EQm("[ILS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST ILS_COPY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST ILS_COPY_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        ASSERT_EQm("[ILS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST ILS_COPY_05(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST ILS_COPY_06(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_EQm("[ILS-ERROR] Expected heads to be equal", test.head, copy.head);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST ILS_COPY_07(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    ASSERT_STRN_EQm("[ILS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST ILS_COPY_08(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        ASSERT_STRN_EQm("[ILS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST ILS_COPY_09(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        ASSERT_STRN_EQm("[ILS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST ILS_COPY_10(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[ILS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ILS-ERROR] Expected heads to not be equal", test.head, copy.head);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        ASSERT_STRN_EQm("[ILS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST ILS_IS_EMPTY_01(void) {
    stack_s test = create_stack();

    ASSERTm("[ILS-ERROR] Expected stack to be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_IS_EMPTY_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_IS_EMPTY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_IS_EMPTY_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_CLEAR_01(void) {
    stack_s test = create_stack();

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_CLEAR_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_CLEAR_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_CLEAR_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_CLEAR_05(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_CLEAR_06(void) {
    stack_s test = create_stack();

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST ILS_CLEAR_07(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST ILS_CLEAR_08(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST ILS_CLEAR_09(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST ILS_CLEAR_10(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST ILS_FOREACH_01(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST ILS_FOREACH_02(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = LIST_ARRAY_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST ILS_FOREACH_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = LIST_ARRAY_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST ILS_FOREACH_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = LIST_ARRAY_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST ILS_FOREACH_05(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST ILS_FOREACH_06(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST ILS_FOREACH_07(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST ILS_FOREACH_08(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST ILS_MAP_01(void) {
    stack_s test = create_stack();

    map_stack(&test, sort_int, compare_int_generic);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_MAP_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    map_stack(&test, sort_int, compare_int_generic);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_MAP_03(void) {
    stack_s test = create_stack();

    for (int i = (LIST_ARRAY_STACK_CHUNK - 1) >> 1; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_STACK_CHUNK - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = LIST_ARRAY_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_MAP_04(void) {
    stack_s test = create_stack();

    for (int i = (LIST_ARRAY_STACK_CHUNK) >> 1; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_STACK_CHUNK) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = LIST_ARRAY_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_MAP_05(void) {
    stack_s test = create_stack();

    for (int i = (LIST_ARRAY_STACK_CHUNK + 1) >> 1; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_STACK_CHUNK + 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = LIST_ARRAY_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_MAP_06(void) {
    stack_s test = create_stack();

    for (int i = (LIST_ARRAY_STACK_CHUNK - 1) >> 1; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_STACK_CHUNK - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_MAP_07(void) {
    stack_s test = create_stack();

    for (int i = (LIST_ARRAY_STACK_CHUNK) >> 1; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_STACK_CHUNK) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST ILS_MAP_08(void) {
    stack_s test = create_stack();

    for (int i = (LIST_ARRAY_STACK_CHUNK + 1) >> 1; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_STACK_CHUNK + 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

SUITE (infinite_list_stack_test) {
    // create
    RUN_TEST(ILS_CREATE_01);
    // destroy
    RUN_TEST(ILS_DESTROY_01); RUN_TEST(ILS_DESTROY_02); RUN_TEST(ILS_DESTROY_03); RUN_TEST(ILS_DESTROY_04); RUN_TEST(ILS_DESTROY_05);
    RUN_TEST(ILS_DESTROY_06); RUN_TEST(ILS_DESTROY_07); RUN_TEST(ILS_DESTROY_08); RUN_TEST(ILS_DESTROY_09); RUN_TEST(ILS_DESTROY_10);
    // is full
    RUN_TEST(ILS_IS_FULL_01); RUN_TEST(ILS_IS_FULL_02); RUN_TEST(ILS_IS_FULL_03); RUN_TEST(ILS_IS_FULL_04); RUN_TEST(ILS_IS_FULL_05);
    // peep
    RUN_TEST(ILS_PEEP_01); RUN_TEST(ILS_PEEP_02); RUN_TEST(ILS_PEEP_03); RUN_TEST(ILS_PEEP_04); RUN_TEST(ILS_PEEP_05);
    // push
    RUN_TEST(ILS_PUSH_01); RUN_TEST(ILS_PUSH_02); RUN_TEST(ILS_PUSH_03); RUN_TEST(ILS_PUSH_04);
    // pop
    RUN_TEST(ILS_POP_01); RUN_TEST(ILS_POP_02); RUN_TEST(ILS_POP_03); RUN_TEST(ILS_POP_04);
    // copy
    RUN_TEST(ILS_COPY_01); RUN_TEST(ILS_COPY_02); RUN_TEST(ILS_COPY_03); RUN_TEST(ILS_COPY_04); RUN_TEST(ILS_COPY_05);
    RUN_TEST(ILS_COPY_06); RUN_TEST(ILS_COPY_07); RUN_TEST(ILS_COPY_08); RUN_TEST(ILS_COPY_09); RUN_TEST(ILS_COPY_10);
    // is empty
    RUN_TEST(ILS_IS_EMPTY_01); RUN_TEST(ILS_IS_EMPTY_02); RUN_TEST(ILS_IS_EMPTY_03); RUN_TEST(ILS_IS_EMPTY_04);
    // clear
    RUN_TEST(ILS_CLEAR_01); RUN_TEST(ILS_CLEAR_02); RUN_TEST(ILS_CLEAR_03); RUN_TEST(ILS_CLEAR_04); RUN_TEST(ILS_CLEAR_05);
    RUN_TEST(ILS_CLEAR_06); RUN_TEST(ILS_CLEAR_07); RUN_TEST(ILS_CLEAR_08); RUN_TEST(ILS_CLEAR_09); RUN_TEST(ILS_CLEAR_10);
    // foreach
    RUN_TEST(ILS_FOREACH_01); RUN_TEST(ILS_FOREACH_02); RUN_TEST(ILS_FOREACH_03); RUN_TEST(ILS_FOREACH_04); RUN_TEST(ILS_FOREACH_05);
    RUN_TEST(ILS_FOREACH_06); RUN_TEST(ILS_FOREACH_07); RUN_TEST(ILS_FOREACH_08);
    // map
    RUN_TEST(ILS_MAP_01); RUN_TEST(ILS_MAP_02); RUN_TEST(ILS_MAP_03); RUN_TEST(ILS_MAP_04); RUN_TEST(ILS_MAP_05);
    RUN_TEST(ILS_MAP_06); RUN_TEST(ILS_MAP_07); RUN_TEST(ILS_MAP_08);
}
