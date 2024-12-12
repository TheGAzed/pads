#include "stack_test.h"

#define STACK_MODE FINITE_ALLOCATED_STACK
#define MAXIMUM_STACK_SIZE  (1 << 4)
#include <stack.h>

/// Tests if stack is initialized correctly when creating it.
TEST FAS_01(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack max is not MAXIMUM_STACK_SIZE.", MAXIMUM_STACK_SIZE, test.max);
    ASSERT_NEQm("[FAS-ERROR] Test stack elements is not NULL.", NULL, test.elements);

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if stack is initialized correctly when creating and then destroying it.
TEST FAS_02(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    destroy_stack(&test, NULL);

    ASSERT_EQm("[FAS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[FAS-ERROR] Test stack max is not zero.", 0, test.max);
    ASSERT_EQm("[FAS-ERROR] Test stack elements is not NULL.", NULL, test.elements);

    PASS();
}

/// Tests if one pushed element is peeked correctly.
TEST FAS_03(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_STACK_SIZE' - 1 pushed element is peeked correctly.
TEST FAS_04(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (size_t i = 0; i < MAXIMUM_STACK_SIZE - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_STACK_SIZE' pushed element is peeked correctly.
TEST FAS_05(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (size_t i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if sequence of 'MAXIMUM_STACK_SIZE' - 1 pushed numbers is popped correctly
TEST FAS_06(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 1; i <= MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = MAXIMUM_STACK_SIZE - 1; i >= 1; --i) {
        ASSERT_EQm("[FAS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if sequence of 'MAXIMUM_STACK_SIZE' pushed numbers is popped correctly
TEST FAS_07(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 1; i <= MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = MAXIMUM_STACK_SIZE; i >= 1; --i) {
        ASSERT_EQm("[FAS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST FAS_08(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    peep_stack(test);

    ASSERT_EQm("[FAS-ERROR] Expected stack size to not change after peek.", 1, test.size);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is empty when creating it.
TEST FAS_09(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    ASSERTm("[FAS-ERROR] Expected stack to be empty when creating it.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not empty when push_stacking element.
TEST FAS_10(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[FAS-ERROR] Expected stack to not be empty when push_stacking element.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if one pushed element is popped correctly.
TEST FAS_11(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_STACK_SIZE' - 1 pushed element is popped correctly.
TEST FAS_12(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (size_t i = 0; i < MAXIMUM_STACK_SIZE - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_STACK_SIZE' pushed element is popped correctly.
TEST FAS_13(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (size_t i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if destroyed element
TEST FAS_14(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST FAS_15(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (size_t i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST FAS_16(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (size_t i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if 1 copied int element
TEST FAS_17(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[FAS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'MAXIMUM_STACK_SIZE' - 1 copied int element
TEST FAS_18(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[FAS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'MAXIMUM_STACK_SIZE' copied int element
TEST FAS_19(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        ASSERT_EQm("[FAS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 1 copied string element
TEST FAS_20(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    stack_s copy = copy_stack(test, copy_element);

    STACK_DATA_TYPE elemen_test = pop_stack(&test);
    STACK_DATA_TYPE element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[FAS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if 'MAXIMUM_STACK_SIZE' - 1 copied string element
TEST FAS_21(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[FAS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if 'MAXIMUM_STACK_SIZE' copied string element
TEST FAS_22(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[FAS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if stack is not empty
TEST FAS_23(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[FAS-TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 1 push_stack/pop_stack
TEST FAS_24(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    ASSERTm("[FAS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'MAXIMUM_STACK_SIZE' - 1 push_stack/pop_stack
TEST FAS_25(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[FAS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'MAXIMUM_STACK_SIZE' push_stack/pop_stack
TEST FAS_26(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[FAS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all one int values get incremented by 'increment'
TEST FAS_27(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[FAS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'MAXIMUM_STACK_SIZE - 1' int values get incremented by 'increment'
TEST FAS_28(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = MAXIMUM_STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'MAXIMUM_STACK_SIZE' int values get incremented by 'increment'
TEST FAS_29(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);
    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = MAXIMUM_STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FAS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all one string values have changed to new string value
TEST FAS_30(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[FAS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_element(&element);

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'MAXIMUM_STACK_SIZE' - 1 string values have changed to new string value
TEST FAS_31(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_STACK_SIZE - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FAS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'MAXIMUM_STACK_SIZE' string values have changed to new string value
TEST FAS_32(void) {
    stack_s test = create_stack(MAXIMUM_STACK_SIZE);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_STACK_SIZE; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FAS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

SUITE (finite_allocated_stack_test) {
    RUN_TEST(FAS_01); RUN_TEST(FAS_02); RUN_TEST(FAS_03); RUN_TEST(FAS_04);
    RUN_TEST(FAS_05); RUN_TEST(FAS_06); RUN_TEST(FAS_07); RUN_TEST(FAS_08);
    RUN_TEST(FAS_09); RUN_TEST(FAS_10); RUN_TEST(FAS_11); RUN_TEST(FAS_12);
    RUN_TEST(FAS_13); RUN_TEST(FAS_14); RUN_TEST(FAS_15); RUN_TEST(FAS_16);
    RUN_TEST(FAS_17); RUN_TEST(FAS_18); RUN_TEST(FAS_19); RUN_TEST(FAS_20);
    RUN_TEST(FAS_21); RUN_TEST(FAS_22); RUN_TEST(FAS_23); RUN_TEST(FAS_24);
    RUN_TEST(FAS_25); RUN_TEST(FAS_26); RUN_TEST(FAS_27); RUN_TEST(FAS_28);
    RUN_TEST(FAS_29); RUN_TEST(FAS_30); RUN_TEST(FAS_31); RUN_TEST(FAS_32);
}
