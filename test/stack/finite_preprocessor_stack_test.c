#include "stack_test.h"

#define STACK_MODE FINITE_PRERPOCESSOR_STACK
#define PREPROCESSOR_STACK_SIZE  (1 << 4)
#include <stack.h>

/// Tests if stack is initialized correctly when creating it.
TEST FPS_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if stack is initialized correctly when creating and then destroying it.
TEST FPS_02(void) {
    stack_s test = create_stack();
    destroy_stack(&test, NULL);

    ASSERT_EQm("[FPS-ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

/// Tests if one pushed element is peeked correctly.
TEST FPS_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_STACK_SIZE' - 1 pushed element is peeked correctly.
TEST FPS_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_STACK_SIZE' pushed element is peeked correctly.
TEST FPS_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if sequence of 'PREPROCESSOR_STACK_SIZE' - 1 pushed numbers is popped correctly
TEST FPS_06(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 1; --i) {
        ASSERT_EQm("[FPS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if sequence of 'PREPROCESSOR_STACK_SIZE' pushed numbers is popped correctly
TEST FPS_07(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = PREPROCESSOR_STACK_SIZE; i >= 1; --i) {
        ASSERT_EQm("[FPS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST FPS_08(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    peep_stack(test);

    ASSERT_EQm("[FPS-ERROR] Expected stack size to not change after peek.", 1, test.size);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is empty when creating it.
TEST FPS_09(void) {
    stack_s test = create_stack();

    ASSERTm("[FPS-ERROR] Expected stack to be empty when creating it.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not empty when push_stacking element.
TEST FPS_10(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be empty when push_stacking element.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if one pushed element is popped correctly.
TEST FPS_11(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_STACK_SIZE' - 1 pushed element is popped correctly.
TEST FPS_12(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_STACK_SIZE' pushed element is popped correctly.
TEST FPS_13(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if destroyed element
TEST FPS_14(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST FPS_15(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

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

/// Test if 1 copied int element
TEST FPS_17(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[FPS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'PREPROCESSOR_STACK_SIZE' - 1 copied int element
TEST FPS_18(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[FPS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'PREPROCESSOR_STACK_SIZE' copied int element
TEST FPS_19(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        ASSERT_EQm("[FPS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 1 copied string element
TEST FPS_20(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    stack_s copy = copy_stack(test, copy_element);

    STACK_DATA_TYPE elemen_test = pop_stack(&test);
    STACK_DATA_TYPE element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[FPS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if 'PREPROCESSOR_STACK_SIZE' - 1 copied string element
TEST FPS_21(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[FPS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if 'PREPROCESSOR_STACK_SIZE' copied string element
TEST FPS_22(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[FPS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if stack is not empty
TEST FPS_23(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[FPS-TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 1 push_stack/pop_stack
TEST FPS_24(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    ASSERTm("[FPS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'PREPROCESSOR_STACK_SIZE' - 1 push_stack/pop_stack
TEST FPS_25(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[FPS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'PREPROCESSOR_STACK_SIZE' push_stack/pop_stack
TEST FPS_26(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[FPS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all one int values get incremented by 'increment'
TEST FPS_27(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[FPS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'PREPROCESSOR_STACK_SIZE - 1' int values get incremented by 'increment'
TEST FPS_28(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = PREPROCESSOR_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'PREPROCESSOR_STACK_SIZE' int values get incremented by 'increment'
TEST FPS_29(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all one string values have changed to new string value
TEST FPS_30(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[FPS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_element(&element);

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'PREPROCESSOR_STACK_SIZE' - 1 string values have changed to new string value
TEST FPS_31(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FPS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'PREPROCESSOR_STACK_SIZE' string values have changed to new string value
TEST FPS_32(void) {
    stack_s test = create_stack();

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FPS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

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
    RUN_TEST(FPS_29); RUN_TEST(FPS_30); RUN_TEST(FPS_31); RUN_TEST(FPS_32);
}
