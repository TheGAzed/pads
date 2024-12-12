#include "stack_test.h"

#define STACK_MODE INFINITE_LIST_STACK
#define LIST_ARRAY_STACK_CHUNK (1 << 4)
#include <stack.h>

/// Tests if stack is initialized correctly when creating it.
TEST ILS_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if stack is initialized correctly when creating and then destroying it.
TEST ILS_02(void) {
    stack_s test = create_stack();
    destroy_stack(&test, NULL);

    ASSERT_EQm("[ILS-ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_EQm("[ILS-ERROR] Test stack head is not NULL.", NULL, test.head);

    PASS();
}

/// Tests if one pushed element is peeked correctly.
TEST ILS_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_STACK_CHUNK' - 1 pushed element is peeked correctly.
TEST ILS_04(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_STACK_CHUNK' pushed element is peeked correctly.
TEST ILS_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_STACK_CHUNK' + 1 pushed element is peeked correctly.
TEST ILS_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack peeked element not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if sequence of 'LIST_ARRAY_STACK_CHUNK' - 1 pushed numbers is popped correctly
TEST ILS_07(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK - 1; i >= 1; --i) {
        ASSERT_EQm("[ILS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if sequence of 'LIST_ARRAY_STACK_CHUNK' pushed numbers is popped correctly
TEST ILS_08(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK; i >= 1; --i) {
        ASSERT_EQm("[ILS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if sequence of 'LIST_ARRAY_STACK_CHUNK' - 1 pushed numbers is popped correctly
TEST ILS_09(void) {
    stack_s test = create_stack();

    for (int i = 1; i <= LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = LIST_ARRAY_STACK_CHUNK + 1; i >= 1; --i) {
        ASSERT_EQm("[ILS-ERROR] Test stack popped element not 'i'.", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST ILS_10(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    peep_stack(test);

    ASSERT_EQm("[ILS-ERROR] Expected stack size to not change after peek.", 1, test.size);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is empty when creating it.
TEST ILS_11(void) {
    stack_s test = create_stack();

    ASSERTm("[ILS-ERROR] Expected stack to be empty when creating it.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not empty when push_stacking element.
TEST ILS_12(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[ILS-ERROR] Expected stack to not be empty when push_stacking element.", is_empty_stack(test));

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if one pushed element is popped correctly.
TEST ILS_13(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_STACK_CHUNK' - 1 pushed element is popped correctly.
TEST ILS_14(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_STACK_CHUNK' pushed element is popped correctly.
TEST ILS_15(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_STACK_CHUNK' + 1 pushed element is popped correctly.
TEST ILS_16(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILS-ERROR] Test stack popped element not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if destroyed element
TEST ILS_17(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILS_18(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILS_19(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILS_20(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if 1 copied int element
TEST ILS_21(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'LIST_ARRAY_STACK_CHUNK' - 1 copied int element
TEST ILS_22(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'LIST_ARRAY_STACK_CHUNK' copied int element
TEST ILS_23(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 'LIST_ARRAY_STACK_CHUNK' + 1 copied int element
TEST ILS_24(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    destroy_stack(&copy, NULL);
    PASS();
}

/// Test if 1 copied string element
TEST ILS_25(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    stack_s copy = copy_stack(test, copy_element);

    STACK_DATA_TYPE elemen_test = pop_stack(&test);
    STACK_DATA_TYPE element_copy = pop_stack(&copy);
    ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if 'LIST_ARRAY_STACK_CHUNK' - 1 copied string element
TEST ILS_26(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if 'LIST_ARRAY_STACK_CHUNK' copied string element
TEST ILS_27(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if 'LIST_ARRAY_STACK_CHUNK' + 1 copied string element
TEST ILS_28(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    stack_s copy = copy_stack(test, copy_element);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE elemen_test = pop_stack(&test);
        STACK_DATA_TYPE element_copy = pop_stack(&copy);
        ASSERT_STRN_EQm("[ILS-TEST] Test stack string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_stack(&test, destroy_element);
    destroy_stack(&copy, destroy_element);
    PASS();
}

/// Test if stack is not empty
TEST ILS_29(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[ILS-TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST ILS_30(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[ILS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 1 push_stack/pop_stack
TEST ILS_31(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    ASSERTm("[ILS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'LIST_ARRAY_STACK_CHUNK' - 1 push_stack/pop_stack
TEST ILS_32(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ILS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty after 'LIST_ARRAY_STACK_CHUNK' push_stack/pop_stack
TEST ILS_33(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ILS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty 'LIST_ARRAY_STACK_CHUNK' + 1 push_stack/pop_stack
TEST ILS_34(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ILS-TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if head is NULL after 1 push and pop.
TEST ILS_35(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[ILS-ERROR] Expected stack's 'head' parameter to be NULL.", NULL, test.head);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if head is NULL after 'LIST_ARRAY_STACK_CHUNK - 1' push and pop.
TEST ILS_36(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        pop_stack(&test);
    }

    ASSERT_EQm("[ILS-ERROR] Expected stack's 'head' parameter to be NULL.", NULL, test.head);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if head is NULL after 'LIST_ARRAY_STACK_CHUNK' push and pop.
TEST ILS_37(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERT_EQm("[ILS-ERROR] Expected stack's 'head' parameter to be NULL.", NULL, test.head);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if head is NULL after 'LIST_ARRAY_STACK_CHUNK + 1' push and pop.
TEST ILS_38(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        pop_stack(&test);
    }

    ASSERT_EQm("[ILS-ERROR] Expected stack's 'head' parameter to be NULL.", NULL, test.head);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all one int values get incremented by 'increment'
TEST ILS_39(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'LIST_ARRAY_STACK_CHUNK - 1' int values get incremented by 'increment'
TEST ILS_40(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = LIST_ARRAY_STACK_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'LIST_ARRAY_STACK_CHUNK' int values get incremented by 'increment'
TEST ILS_41(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = LIST_ARRAY_STACK_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all 'LIST_ARRAY_STACK_CHUNK + 1' int values get incremented by 'increment'
TEST ILS_42(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = LIST_ARRAY_STACK_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);

    PASS();
}

/// Test if all one string values have changed to new string value
TEST ILS_43(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_element(&element);

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'LIST_ARRAY_STACK_CHUNK' - 1 string values have changed to new string value
TEST ILS_44(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'LIST_ARRAY_STACK_CHUNK' string values have changed to new string value
TEST ILS_45(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

/// Test if all 'LIST_ARRAY_STACK_CHUNK' + 1 string values have changed to new string value
TEST ILS_46(void) {
    stack_s test = create_stack();

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);

    PASS();
}

SUITE (infinite_list_stack_test) {
    RUN_TEST(ILS_01); RUN_TEST(ILS_02); RUN_TEST(ILS_03); RUN_TEST(ILS_04);
    RUN_TEST(ILS_05); RUN_TEST(ILS_06); RUN_TEST(ILS_07); RUN_TEST(ILS_08);
    RUN_TEST(ILS_09); RUN_TEST(ILS_10); RUN_TEST(ILS_11); RUN_TEST(ILS_12);
    RUN_TEST(ILS_13); RUN_TEST(ILS_14); RUN_TEST(ILS_15); RUN_TEST(ILS_16);
    RUN_TEST(ILS_17); RUN_TEST(ILS_18); RUN_TEST(ILS_19); RUN_TEST(ILS_20);
    RUN_TEST(ILS_21); RUN_TEST(ILS_22); RUN_TEST(ILS_23); RUN_TEST(ILS_24);
    RUN_TEST(ILS_25); RUN_TEST(ILS_26); RUN_TEST(ILS_27); RUN_TEST(ILS_28);
    RUN_TEST(ILS_29); RUN_TEST(ILS_30); RUN_TEST(ILS_31); RUN_TEST(ILS_32);
    RUN_TEST(ILS_33); RUN_TEST(ILS_34); RUN_TEST(ILS_35); RUN_TEST(ILS_36);
    RUN_TEST(ILS_37); RUN_TEST(ILS_38); RUN_TEST(ILS_39); RUN_TEST(ILS_40);
    RUN_TEST(ILS_41); RUN_TEST(ILS_42); RUN_TEST(ILS_43); RUN_TEST(ILS_44);
    RUN_TEST(ILS_45); RUN_TEST(ILS_46);
}
