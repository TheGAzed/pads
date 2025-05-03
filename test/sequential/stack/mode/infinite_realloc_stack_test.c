#include "stack_test.h"

#include <functions.h>

#define STACK_DATA_TYPE DATA_TYPE
#define STACK_MODE INFINITE_REALLOC_STACK_MODE
#define REALLOC_STACK_CHUNK  (1 << 3)
#include <sequential/stack/stack.h>

TEST IRS_CREATE_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_DESTROY_01(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_05(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_06(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_07(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_08(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_09(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_DESTROY_10(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRS_IS_FULL_01(void) {
    stack_s test = create_stack();

    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_IS_FULL_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_IS_FULL_03(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_IS_FULL_04(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_IS_FULL_05(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be full", is_full_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PEEP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[IRS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PEEP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PEEP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PEEP_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PEEP_05(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Expected to peep 42", 42, peep_stack(test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PUSH_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PUSH_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PUSH_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_PUSH_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_POP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_POP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_POP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_POP_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_COPY_01(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_EQm("[IRS-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST IRS_COPY_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[IRS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST IRS_COPY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST IRS_COPY_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        ASSERT_EQm("[IRS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST IRS_COPY_05(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(test, copy_int);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRS-ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST IRS_COPY_06(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_EQm("[IRS-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST IRS_COPY_07(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[IRS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST IRS_COPY_08(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        ASSERT_STRN_EQm("[IRS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST IRS_COPY_09(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        ASSERT_STRN_EQm("[IRS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST IRS_COPY_10(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(test, copy_string);

    ASSERT_EQm("[IRS-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRS-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        ASSERT_STRN_EQm("[IRS-ERROR] Expected elements to be equal", peep_stack(test).sub_two, peep_stack(copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST IRS_IS_EMPTY_01(void) {
    stack_s test = create_stack();

    ASSERTm("[IRS-ERROR] Expected stack to be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_IS_EMPTY_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_IS_EMPTY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_IS_EMPTY_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be empty", is_empty_stack(test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_CLEAR_01(void) {
    stack_s test = create_stack();

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_CLEAR_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_CLEAR_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_CLEAR_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_CLEAR_05(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    clear_stack(&test, destroy_int);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_CLEAR_06(void) {
    stack_s test = create_stack();

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST IRS_CLEAR_07(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST IRS_CLEAR_08(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST IRS_CLEAR_09(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST IRS_CLEAR_10(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_stack(&test, destroy_string);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_string);
    PASS();
}

TEST IRS_FOREACH_01(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST IRS_FOREACH_02(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = REALLOC_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST IRS_FOREACH_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = REALLOC_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST IRS_FOREACH_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = REALLOC_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST IRS_FOREACH_05(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST IRS_FOREACH_06(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST IRS_FOREACH_07(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST IRS_FOREACH_08(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST IRS_MAP_01(void) {
    stack_s test = create_stack();

    map_stack(&test, sort_int, compare_int_generic);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_MAP_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    map_stack(&test, sort_int, compare_int_generic);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_MAP_03(void) {
    stack_s test = create_stack();

    for (int i = (REALLOC_STACK_CHUNK - 1) >> 1; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_STACK_CHUNK - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = REALLOC_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_MAP_04(void) {
    stack_s test = create_stack();

    for (int i = (REALLOC_STACK_CHUNK) >> 1; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_STACK_CHUNK) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = REALLOC_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_MAP_05(void) {
    stack_s test = create_stack();

    for (int i = (REALLOC_STACK_CHUNK + 1) >> 1; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_STACK_CHUNK + 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = REALLOC_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_MAP_06(void) {
    stack_s test = create_stack();

    for (int i = (REALLOC_STACK_CHUNK - 1) >> 1; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_STACK_CHUNK - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_MAP_07(void) {
    stack_s test = create_stack();

    for (int i = (REALLOC_STACK_CHUNK) >> 1; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_STACK_CHUNK) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        ASSERT_EQm("[IRS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IRS_MAP_08(void) {
    stack_s test = create_stack();

    for (int i = (REALLOC_STACK_CHUNK + 1) >> 1; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_STACK_CHUNK + 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRS-ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

SUITE (infinite_realloc_stack_test) {
    // create
    RUN_TEST(IRS_CREATE_01);
    // destroy
    RUN_TEST(IRS_DESTROY_01); RUN_TEST(IRS_DESTROY_02); RUN_TEST(IRS_DESTROY_03); RUN_TEST(IRS_DESTROY_04); RUN_TEST(IRS_DESTROY_05);
    RUN_TEST(IRS_DESTROY_06); RUN_TEST(IRS_DESTROY_07); RUN_TEST(IRS_DESTROY_08); RUN_TEST(IRS_DESTROY_09); RUN_TEST(IRS_DESTROY_10);
    // is full
    RUN_TEST(IRS_IS_FULL_01); RUN_TEST(IRS_IS_FULL_02); RUN_TEST(IRS_IS_FULL_03); RUN_TEST(IRS_IS_FULL_04); RUN_TEST(IRS_IS_FULL_05);
    // peep
    RUN_TEST(IRS_PEEP_01); RUN_TEST(IRS_PEEP_02); RUN_TEST(IRS_PEEP_03); RUN_TEST(IRS_PEEP_04); RUN_TEST(IRS_PEEP_05);
    // push
    RUN_TEST(IRS_PUSH_01); RUN_TEST(IRS_PUSH_02); RUN_TEST(IRS_PUSH_03); RUN_TEST(IRS_PUSH_04);
    // pop
    RUN_TEST(IRS_POP_01); RUN_TEST(IRS_POP_02); RUN_TEST(IRS_POP_03); RUN_TEST(IRS_POP_04);
    // copy
    RUN_TEST(IRS_COPY_01); RUN_TEST(IRS_COPY_02); RUN_TEST(IRS_COPY_03); RUN_TEST(IRS_COPY_04); RUN_TEST(IRS_COPY_05);
    RUN_TEST(IRS_COPY_06); RUN_TEST(IRS_COPY_07); RUN_TEST(IRS_COPY_08); RUN_TEST(IRS_COPY_09); RUN_TEST(IRS_COPY_10);
    // is empty
    RUN_TEST(IRS_IS_EMPTY_01); RUN_TEST(IRS_IS_EMPTY_02); RUN_TEST(IRS_IS_EMPTY_03); RUN_TEST(IRS_IS_EMPTY_04);
    // clear
    RUN_TEST(IRS_CLEAR_01); RUN_TEST(IRS_CLEAR_02); RUN_TEST(IRS_CLEAR_03); RUN_TEST(IRS_CLEAR_04); RUN_TEST(IRS_CLEAR_05);
    RUN_TEST(IRS_CLEAR_06); RUN_TEST(IRS_CLEAR_07); RUN_TEST(IRS_CLEAR_08); RUN_TEST(IRS_CLEAR_09); RUN_TEST(IRS_CLEAR_10);
    // foreach
    RUN_TEST(IRS_FOREACH_01); RUN_TEST(IRS_FOREACH_02); RUN_TEST(IRS_FOREACH_03); RUN_TEST(IRS_FOREACH_04); RUN_TEST(IRS_FOREACH_05);
    RUN_TEST(IRS_FOREACH_06); RUN_TEST(IRS_FOREACH_07); RUN_TEST(IRS_FOREACH_08);
    // map
    RUN_TEST(IRS_MAP_01); RUN_TEST(IRS_MAP_02); RUN_TEST(IRS_MAP_03); RUN_TEST(IRS_MAP_04); RUN_TEST(IRS_MAP_05);
    RUN_TEST(IRS_MAP_06); RUN_TEST(IRS_MAP_07); RUN_TEST(IRS_MAP_08);
}
