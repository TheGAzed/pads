#include "stack_test.h"

#define STACK_MODE INFINITE_LIST_STACK
#define LIST_ARRAY_STACK_CHUNK  (1 << 3)
#include <stack.h>

/// Tests if stack is created properly.
TEST ILS_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[ILS-TEST] Stack's 'head' parameter is not NULL.", NULL, test.head);
    ASSERT_EQm("[ILS-TEST] Stack's 'size' parameter is not zero.", 0, test.size);

    destroy_stack(&test, NULL);

    PASS();
}

/// Tests if stack is destroyed properly.
TEST ILS_02(void) {
    stack_s test = create_stack();
    destroy_stack(&test, NULL);

    ASSERT_EQm("[ILS-TEST] Stack's 'head' parameter is not NULL.", NULL, test.head);
    ASSERT_EQm("[ILS-TEST] Stack's 'size' parameter is not zero.", 0, test.size);

    PASS();
}

/// Test if peeped top element is equal to 42
TEST ILS_03(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST ILS_04(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST ILS_05(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peeped top element is equal to 42
TEST ILS_06(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's top element is not 42.", 42, peep_stack(test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST ILS_07(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    peep_stack(test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 1.", 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST ILS_08(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    peep_stack(test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 2.", 2, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST ILS_09(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    peep_stack(test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 'LIST_ARRAY_STACK_CHUNK'.", LIST_ARRAY_STACK_CHUNK, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if peep remains size
TEST ILS_10(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    peep_stack(test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 'LIST_ARRAY_STACK_CHUNK' + 1.", LIST_ARRAY_STACK_CHUNK + 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST ILS_11(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST ILS_12(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST ILS_13(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if popped top element is equal to 42
TEST ILS_14(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1 });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    ASSERT_EQm("[ILS-TEST] Stack's popped element is not 42.", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST ILS_15(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not zero.", 0, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST ILS_16(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not one.", 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST ILS_17(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    pop_stack(&test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 'LIST_ARRAY_STACK_CHUNK' - 1.", LIST_ARRAY_STACK_CHUNK - 1, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if pop decreases size
TEST ILS_18(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    pop_stack(&test);

    ASSERT_EQm("[ILS-TEST] Stack's size is not 'LIST_ARRAY_STACK_CHUNK'.", LIST_ARRAY_STACK_CHUNK, test.size);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if destroyed element
TEST ILS_19(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILS_20(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILS_21(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILS_22(void) {
    stack_s test = create_stack();
    for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if copied element
TEST ILS_23(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    stack_s copy = copy_stack(test, NULL);

    ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if copied element
TEST ILS_24(void) {
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
TEST ILS_25(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if copied element
TEST ILS_26(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    stack_s copy = copy_stack(test, NULL);
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILS-TEST] Test stack is not equal to copy.", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if copied element
TEST ILS_27(void) {
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
TEST ILS_28(void) {
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
TEST ILS_29(void) {
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
    PASS();
}

/// Test if copied element
TEST ILS_30(void) {
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
    PASS();
}

/// Test if stack is not empty
TEST ILS_31(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    ASSERT_FALSEm("[ILS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST ILS_32(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    ASSERT_FALSEm("[ILS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST ILS_33(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[ILS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is not empty
TEST ILS_34(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[ILS_TEST] Stack is empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST ILS_35(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    ASSERTm("[ILS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST ILS_36(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);
    pop_stack(&test);
    ASSERTm("[ILS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST ILS_37(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ILS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if stack is empty
TEST ILS_38(void) {
    stack_s test = create_stack();
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < LIST_ARRAY_STACK_CHUNK + 1; ++i) {
        pop_stack(&test);
    }

    ASSERTm("[ILS_TEST] Stack is not empty.", is_empty_stack(test));

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if int sorted ascending correctly qsort
TEST ILS_39(void) {
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
        ASSERT_EQm("[ILS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if int sorted descending correctly qsort
TEST ILS_40(void) {
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
        ASSERT_EQm("[ILS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if int sorted ascending correctly bubble sort
TEST ILS_41(void) {
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

    sort_stack(&test, NULL, compare_int_asc);

    for (int i = 9; i >= 0; i--) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if int sorted descending correctly bubble sort
TEST ILS_42(void) {
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

    sort_stack(&test, NULL, compare_int_desc);

    for (int i = 0; i < 10; i++) {
        ASSERT_EQm("[ILS-ERROR] Expected sorted values to be equal", i, pop_stack(&test).sub_one);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if string sorted ascending correctly qsort
TEST ILS_43(void) {
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
        ASSERT_STRN_EQm("[ILS-ERROR] Expected sorted values to be equal", temp , pop_stack(&test).sub_two, sizeof(temp) - 1);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if string sorted descending correctly qsort
TEST ILS_44(void) {
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
        ASSERT_STRN_EQm("[ILS-ERROR] Expected sorted values to be equal", temp , pop_stack(&test).sub_two, sizeof(temp) - 1);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if string sorted ascending correctly bubble sort
TEST ILS_45(void) {
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

    sort_stack(&test, NULL, compare_string_asc);
    for (int i = 9; i >= 0; i--) {
        char temp[] = "a";
        temp[0] += i;
        ASSERT_STRN_EQm("[ILS-ERROR] Expected sorted values to be equal", temp , pop_stack(&test).sub_two, sizeof(temp) - 1);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if string sorted descending correctly bubble sort
TEST ILS_46(void) {
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

    sort_stack(&test, NULL, compare_string_desc);

    for (int i = 0; i < 10; i++) {
        char temp[] = "a";
        temp[0] += i;
        ASSERT_STRN_EQm("[ILS-ERROR] Expected sorted values to be equal", temp , pop_stack(&test).sub_two, sizeof(temp) - 1);
    }
    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all int values get incremented by 'increment'
TEST ILS_47(void) {
    stack_s test = create_stack();

    for (int i = 0; i < 10; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = 9; i >= 0; --i) {
        ASSERT_EQm("[ILS-ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, NULL);
    PASS();
}

/// Test if all string values have changed to new string value
TEST ILS_48(void) {
    stack_s test = create_stack();

    for (int i = 0; i < 10; ++i) {
        push_stack(&test, copy_element((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < 10; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ILS-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_stack(&test, destroy_element);
    PASS();
}

/// Test if head is NULL after push and pop.
TEST ILS_49(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });
    pop_stack(&test);

    ASSERT_EQm("[ILS-ERROR] Expected stack's 'head' parameter to be NULL.", NULL, test.head);

    destroy_stack(&test, NULL);
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
    RUN_TEST(ILS_45); RUN_TEST(ILS_46); RUN_TEST(ILS_47); RUN_TEST(ILS_48);
    RUN_TEST(ILS_49);
}