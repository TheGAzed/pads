#include "stack_test.h"

#define STACK_MODE INFINITE_REALLOC_STACK
#define REALLOC_STACK_CHUNK  (1 << 3)
#include <stack/stack.h>

/// Tests if stack is initialized correctly when creating it.
TEST IRS_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack elements is not NULL.", NULL, test.elements);

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if stack is initialized correctly when creating and then destroying it.
TEST IRS_02(void) {
    stack_s test = create_stack();
    destroy_stack(&test, NULL);

    ASSERT_EQm("[IRS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[IRS-ERROR] Test stack elements is not NULL.", NULL, test.elements);

    PASS();
}

/// Tests if one pushed element is peeked correctly.
TEST IRS_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_STACK_CHUNK' - 1 pushed element is peeked correctly.
TEST IRS_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_STACK_CHUNK' pushed element is peeked correctly.
TEST IRS_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_STACK_CHUNK' + 1 pushed element is peeked correctly.
TEST IRS_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if sequence of 'REALLOC_STACK_CHUNK' - 1 pushed numbers is popped correctly
TEST IRS_07(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK - 1; i >= 1; --i) {
        ASSERT_EQm("[IRS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if sequence of 'REALLOC_STACK_CHUNK' pushed numbers is popped correctly
TEST IRS_08(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK; i >= 1; --i) {
        ASSERT_EQm("[IRS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if sequence of 'REALLOC_STACK_CHUNK' - 1 pushed numbers is popped correctly
TEST IRS_09(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = REALLOC_STACK_CHUNK + 1; i >= 1; --i) {
        ASSERT_EQm("[IRS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST IRS_10(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    peep_stack(test);

    ASSERT_EQm("[IRS-ERROR] Expected stack size to not change after peek.", 1, test.size);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is empty when creating it.
TEST IRS_11(void) {
    stack_s test = create_stack();

    ASSERTm("[IRS-ERROR] Expected stack to be empty when creating it.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not empty when push_stacking element.
TEST IRS_12(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[IRS-ERROR] Expected stack to not be empty when push_stacking element.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if one pushed element is popped correctly.
TEST IRS_13(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_STACK_CHUNK' - 1 pushed element is popped correctly.
TEST IRS_14(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_STACK_CHUNK' pushed element is popped correctly.
TEST IRS_15(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_STACK_CHUNK' + 1 pushed element is popped correctly.
TEST IRS_16(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if destroyed element
TEST IRS_17(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRS_18(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRS_19(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRS_20(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if 1 copied int element
TEST IRS_21(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[IRS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'REALLOC_STACK_CHUNK' - 1 copied int element
TEST IRS_22(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'REALLOC_STACK_CHUNK' copied int element
TEST IRS_23(void) {
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

/// Test if 'REALLOC_STACK_CHUNK' + 1 copied int element
TEST IRS_24(void) {
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

/// Test if 1 copied string element
TEST IRS_25(void) {
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

/// Test if 'REALLOC_STACK_CHUNK' - 1 copied string element
TEST IRS_26(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
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

/// Test if 'REALLOC_STACK_CHUNK' copied string element
TEST IRS_27(void) {
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

/// Test if 'REALLOC_STACK_CHUNK' + 1 copied string element
TEST IRS_28(void) {
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
TEST IRS_29(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[IRS-TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST IRS_30(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[IRS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 1 push_stack/pop_stack
TEST IRS_31(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    ASSERTm("[IRS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'REALLOC_STACK_CHUNK' - 1 push_stack/pop_stack
TEST IRS_32(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[IRS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'REALLOC_STACK_CHUNK' push_stack/pop_stack
TEST IRS_33(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[IRS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty 'REALLOC_STACK_CHUNK' + 1 push_stack/pop_stack
TEST IRS_34(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[IRS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 1 push and pop.
TEST IRS_35(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[IRS-ERROR] Expected stack's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 'REALLOC_STACK_CHUNK - 1' push and pop.
TEST IRS_36(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        pop_stack(&test);
    }

    ASSERT_EQm("[IRS-ERROR] Expected stack's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 'REALLOC_STACK_CHUNK' push and pop.
TEST IRS_37(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERT_EQm("[IRS-ERROR] Expected stack's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 'REALLOC_STACK_CHUNK + 1' push and pop.
TEST IRS_38(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        pop_stack(&test);
    }

    ASSERT_EQm("[IRS-ERROR] Expected stack's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all one int values get incremented by 'increment'
TEST IRS_39(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'REALLOC_STACK_CHUNK - 1' int values get incremented by 'increment'
TEST IRS_40(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = REALLOC_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'REALLOC_STACK_CHUNK' int values get incremented by 'increment'
TEST IRS_41(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = REALLOC_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'REALLOC_STACK_CHUNK + 1' int values get incremented by 'increment'
TEST IRS_42(void) {
    stack_s test = create_stack();
    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = REALLOC_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[IRS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all one string values have changed to new string value
TEST IRS_43(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_element(&element);

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'REALLOC_STACK_CHUNK' - 1 string values have changed to new string value
TEST IRS_44(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_STACK_CHUNK - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'REALLOC_STACK_CHUNK' string values have changed to new string value
TEST IRS_45(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'REALLOC_STACK_CHUNK' + 1 string values have changed to new string value
TEST IRS_46(void) {
    stack_s test = create_stack();

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[IRS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

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
    RUN_TEST(IRS_37); RUN_TEST(IRS_38); RUN_TEST(IRS_39); RUN_TEST(IRS_40);
    RUN_TEST(IRS_41); RUN_TEST(IRS_42); RUN_TEST(IRS_43); RUN_TEST(IRS_44);
    RUN_TEST(IRS_45); RUN_TEST(IRS_46);
}
