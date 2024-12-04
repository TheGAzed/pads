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

/// Test if int sorted ascending correctly qsort
TEST FPS_29(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 8 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 5 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 2 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 3 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 7 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 6 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 9 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 4 });

    sort_stack(&test, qsort, compare_int_asc);

    for (int i = 9; i >= 0; i--) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if int sorted descending correctly qsort
TEST FPS_30(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 8 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 5 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 2 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 3 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 7 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 6 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 9 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 4 });

    sort_stack(&test, qsort, compare_int_desc);

    for (int i = 0; i < 10; i++) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if string sorted ascending correctly qsort
TEST FPS_31(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "i" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "a" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "f" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "c" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "d" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "h" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "b" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "g" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "j" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "e" });

    sort_stack(&test, qsort, compare_string_asc);

    for (int i = 9; i >= 0; i--) {
        char temp[] = "a";
        temp[0] += i;
        ASSERT_STRN_EQm("[FPS-ERROR] Expected sorted values to be equal", temp , pop_stack(&test).sub_two, sizeof(temp) - 1);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if string sorted descending correctly qsort
TEST FPS_32(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "i" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "a" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "f" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "c" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "d" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "h" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "b" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "g" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "j" });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_two = "e" });

    sort_stack(&test, qsort, compare_string_desc);

    for (int i = 0; i < 10; i++) {
        char temp[] = "a";
        temp[0] += i;
        ASSERT_STRN_EQm("[FPS-ERROR] Expected sorted values to be equal", temp , pop_stack(&test).sub_two, sizeof(temp) - 1);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all int values get incremented by 'increment'
TEST FPS_33(void) {
    stack_s test = create_stack();

    for (int i = 0; i < 10; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = 9; i >= 0; --i) {
        ASSERT_EQm("[FPS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all string values have changed to new string value
TEST FPS_34(void) {
    stack_s test = create_stack();

    for (int i = 0; i < 10; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < 10; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[FPS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Tests if stack is not full when adding one element
TEST FPS_35(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be full.", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not full when adding 'PREPROCESSOR_STACK_SIZE' - 1 elements
TEST FPS_36(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPS-ERROR] Expected stack to not be full.", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is not full when adding 'PREPROCESSOR_STACK_SIZE' - 1 elements
TEST FPS_37(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < PREPROCESSOR_STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERTm("[FPS-ERROR] Expected stack to be full.", is_full_stack(test));
    destroy_stack(&test, NULL);

    PASS();
}

/// Tests sorting 'PREPROCESSOR_STACK_SIZE' - 1 descending values into ascending
TEST FPS_38(void) {
    stack_s test = create_stack();
    for (int i = PREPROCESSOR_STACK_SIZE - 2; i >= 0; i--) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    sort_stack(&test, qsort, compare_int_asc);

    for (int i = PREPROCESSOR_STACK_SIZE - 2; i >= 0; i--) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests sorting 'PREPROCESSOR_STACK_SIZE' descending values into ascending
TEST FPS_39(void) {
    stack_s test = create_stack();
    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 0; i--) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    sort_stack(&test, qsort, compare_int_asc);

    for (int i = PREPROCESSOR_STACK_SIZE - 1; i >= 0; i--) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests sorting 'PREPROCESSOR_STACK_SIZE' - 1 ascending values into descending
TEST FPS_40(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; i++) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    sort_stack(&test, qsort, compare_int_desc);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE - 1; i++) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Tests sorting 'PREPROCESSOR_STACK_SIZE' ascending values into descending
TEST FPS_41(void) {
    stack_s test = create_stack();
    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; i++) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    sort_stack(&test, qsort, compare_int_desc);

    for (int i = 0; i < PREPROCESSOR_STACK_SIZE; i++) {
        ASSERT_EQm("[FPS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }

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
    RUN_TEST(FPS_29); RUN_TEST(FPS_30); RUN_TEST(FPS_31); RUN_TEST(FPS_32);
    RUN_TEST(FPS_33); RUN_TEST(FPS_34); RUN_TEST(FPS_35); RUN_TEST(FPS_36);
    RUN_TEST(FPS_37); RUN_TEST(FPS_38); RUN_TEST(FPS_39); RUN_TEST(FPS_40);
    RUN_TEST(FPS_41);
}
