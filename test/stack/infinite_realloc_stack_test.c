#include "stack_test.h"

#define STACK_MODE INFINITE_REALLOC_STACK
#define REALLOC_STACK_CHUNK  (1 << 3)
#include <stack.h>

/// Tests if stack is created properly.
TEST IRS_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[IRS-TEST] Stack's 'head' parameter is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRS-TEST] Stack's 'size' parameter is not zero.", 0, test.size);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is destroyed properly.
TEST IRS_02(void) {
    stack_s test = create_stack();
    destroy_stack(&test, NULL);

    ASSERT_EQm("[IRS-TEST] Stack's 'head' parameter is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRS-TEST] Stack's 'size' parameter is not zero.", 0, test.size);

    PASS();
}

/// Test if peeped top element is equal to 42
TEST IRS_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST IRS_04(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST IRS_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST IRS_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST IRS_07(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    peep_stack(test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not 1.", 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST IRS_08(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    peep_stack(test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not 2.", 2, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST IRS_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    peep_stack(test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not 'REALLOC_STACK_CHUNK'.", REALLOC_STACK_CHUNK, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST IRS_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    peep_stack(test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not 'REALLOC_STACK_CHUNK' + 1.", REALLOC_STACK_CHUNK + 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST IRS_11(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST IRS_12(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST IRS_13(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST IRS_14(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[IRS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST IRS_15(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not zero.", 0, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST IRS_16(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not one.", 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST IRS_17(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    pop_stack(&test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not 'REALLOC_STACK_CHUNK' - 1.", REALLOC_STACK_CHUNK - 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST IRS_18(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    pop_stack(&test);

    ASSERT_EQm("[IRS-TEST] Stack's size is not 'REALLOC_STACK_CHUNK'.", REALLOC_STACK_CHUNK, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if destroyed element
TEST IRS_19(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRS_20(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRS_21(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRS_22(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if copied element
TEST IRS_23(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[IRS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if copied element
TEST IRS_24(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 1 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[IRS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    ASSERT_EQm("[IRS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if copied element
TEST IRS_25(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        ASSERT_EQm("[IRS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if copied element
TEST IRS_26(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if copied element
TEST IRS_27(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    stack_s copy = copy_stack(test, copy_element);

    STACK_DATA_TYPE elemen_test = pop_stack(&test);
    STACK_DATA_TYPE element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[IRS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if copied element
TEST IRS_28(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    stack_s copy = copy_stack(test, copy_element);

    STACK_DATA_TYPE elemen_test = pop_stack(&test);
    STACK_DATA_TYPE element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[IRS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    elemen_test = pop_stack(&test);
    element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[IRS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if copied element
TEST IRS_29(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[IRS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if copied element
TEST IRS_30(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[IRS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if stack is not empty
TEST IRS_31(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    ASSERT_FALSEm("[IRS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST IRS_32(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    ASSERT_FALSEm("[IRS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST IRS_33(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[IRS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST IRS_34(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[IRS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST IRS_35(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    ASSERTm("[IRS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST IRS_36(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    pop_stack(&test);
    ASSERTm("[IRS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST IRS_37(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[IRS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST IRS_38(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[IRS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if head is NULL after push and pop.
TEST IRS_39(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[IRS-ERROR] Expected stack's 'head' parameter to be NULL.", NULL, test.elements);

    destroy_stack(&test, NULL);
    PASS();
}

SUITE (infinite_realloc_stack_test) {
    RUN_TEST(IRS_01); RUN_TEST(IRS_02); RUN_TEST(IRS_03); RUN_TEST(IRS_04);
    RUN_TEST(IRS_05); RUN_TEST(IRS_06); RUN_TEST(IRS_07); RUN_TEST(IRS_08);
    RUN_TEST(IRS_09); RUN_TEST(IRS_10); RUN_TEST(IRS_11); RUN_TEST(IRS_12);
    RUN_TEST(IRS_13); RUN_TEST(IRS_14); RUN_TEST(IRS_15); RUN_TEST(IRS_16);
    RUN_TEST(IRS_17); RUN_TEST(IRS_18); RUN_TEST(IRS_19); RUN_TEST(IRS_20);
    RUN_TEST(IRS_21); RUN_TEST(IRS_22); RUN_TEST(IRS_23); RUN_TEST(IRS_24);
    RUN_TEST(IRS_25); RUN_TEST(IRS_26); RUN_TEST(IRS_27); RUN_TEST(IRS_28);
    RUN_TEST(IRS_29); RUN_TEST(IRS_30); RUN_TEST(IRS_31); RUN_TEST(IRS_32);
    RUN_TEST(IRS_33); RUN_TEST(IRS_34); RUN_TEST(IRS_35); RUN_TEST(IRS_36);
    RUN_TEST(IRS_37); RUN_TEST(IRS_38); RUN_TEST(IRS_39);
}
