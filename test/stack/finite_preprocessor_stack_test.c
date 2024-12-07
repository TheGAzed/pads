#include "stack_test.h"

#define STACK_MODE FINITE_PRERPOCESSOR_STACK
#define PREPROCESSOR_STACK_SIZE  (1 << 4)
#include <stack.h>

/// Tests if stack is created properly.
TEST FPS_01(void) {
    stack_s test = create_stack();

    ASSERT_NEQm("[ILS-TEST] Stack's 'elements' parameter is NULL.", NULL, test.elements);
    ASSERT_EQm("[ILS-TEST] Stack's 'size' parameter is not zero.", 0, test.size);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if peeped top element is equal to 42
TEST FPS_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST FPS_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST FPS_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST FPS_05(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    peep_stack(test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 1.", 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST FPS_06(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    peep_stack(test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 2.", 2, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST FPS_07(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    peep_stack(test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 'PREPROCESSOR_STACK_SIZE'.", PREPROCESSOR_STACK_SIZE, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST FPS_08(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST FPS_09(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST FPS_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST FPS_11(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not zero.", 0, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST FPS_12(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not one.", 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST FPS_13(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    pop_stack(&test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 'PREPROCESSOR_STACK_SIZE' - 1.", PREPROCESSOR_STACK_SIZE - 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if destroyed element freed.
TEST FPS_14(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element freed.
TEST FPS_15(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST FPS_16(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if copied element
TEST FPS_17(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if copied element
TEST FPS_18(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 1 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if copied element
TEST FPS_19(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if copied element
TEST FPS_20(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    stack_s copy = copy_stack(test, copy_element);

    STACK_DATA_TYPE elemen_test = pop_stack(&test);
    STACK_DATA_TYPE element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if copied element
TEST FPS_21(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    stack_s copy = copy_stack(test, copy_element);

    STACK_DATA_TYPE elemen_test = pop_stack(&test);
    STACK_DATA_TYPE element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    elemen_test = pop_stack(&test);
    element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if copied element
TEST FPS_22(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if stack is not empty
TEST FPS_23(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    ASSERT_FALSEm("[FPS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST FPS_24(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    ASSERT_FALSEm("[FPS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST FPS_25(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[FPS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST FPS_26(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    ASSERTm("[FPS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST FPS_27(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    pop_stack(&test);
    ASSERTm("[FPS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST FPS_28(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[FPS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if stack is not full when adding one element
TEST FPS_29(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be full.", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not full when adding 'PREPROCESSOR_STACK_SIZE' - 1 elements
TEST FPS_30(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be full.", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not full when adding 'PREPROCESSOR_STACK_SIZE' - 1 elements
TEST FPS_31(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERTm("[FPS-ERROR] Expected stack to be full.", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

SUITE (finite_preprocessor_stack_test) {
    RUN_TEST(FPS_01); RUN_TEST(FPS_02); RUN_TEST(FPS_03); RUN_TEST(FPS_04);
    RUN_TEST(FPS_05); RUN_TEST(FPS_06); RUN_TEST(FPS_07); RUN_TEST(FPS_08);
    RUN_TEST(FPS_09); RUN_TEST(FPS_10); RUN_TEST(FPS_11); RUN_TEST(FPS_12);
    RUN_TEST(FPS_13); RUN_TEST(FPS_14); RUN_TEST(FPS_15); RUN_TEST(FPS_16);
    RUN_TEST(FPS_17); RUN_TEST(FPS_18); RUN_TEST(FPS_19); RUN_TEST(FPS_20);
    RUN_TEST(FPS_21); RUN_TEST(FPS_22); RUN_TEST(FPS_23); RUN_TEST(FPS_24);
    RUN_TEST(FPS_25); RUN_TEST(FPS_26); RUN_TEST(FPS_27); RUN_TEST(FPS_28);
    RUN_TEST(FPS_29); RUN_TEST(FPS_30); RUN_TEST(FPS_31);
}
