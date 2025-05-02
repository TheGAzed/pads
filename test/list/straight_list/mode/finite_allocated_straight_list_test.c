#include "straight_list_test.h"

#include <functions.h>

#define STRAIGHT_LIST_DATA_TYPE DATA_TYPE
#define STRAIGHT_LIST_MODE FINITE_ALLOCATED_STRAIGHT_LIST
#define MAXIMUM_FINITE_STRAIGHT_LIST (1 << 4)
#include <list/straight_list/straight_list.h>

TEST FASL_CREATE_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_DESTROY_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    destroy_straight_list(&test, destroy_int);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_DESTROY_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_straight_list(&test, destroy_int);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_DESTROY_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_straight_list(&test, destroy_int);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_DESTROY_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_straight_list(&test, destroy_int);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_DESTROY_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    destroy_straight_list(&test, destroy_string);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_DESTROY_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_straight_list(&test, destroy_string);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_DESTROY_07(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_straight_list(&test, destroy_string);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_DESTROY_08(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_straight_list(&test, destroy_string);

    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FASL_CLEAR_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    clear_straight_list(&test, destroy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_CLEAR_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    clear_straight_list(&test, destroy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_CLEAR_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_straight_list(&test, destroy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_CLEAR_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_straight_list(&test, destroy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_CLEAR_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    clear_straight_list(&test, destroy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_CLEAR_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_straight_list(&test, destroy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_CLEAR_07(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_straight_list(&test, destroy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_CLEAR_08(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_straight_list(&test, destroy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_COPY_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s copy = copy_straight_list(test, copy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&copy, destroy_int);

    PASS();
}

TEST FASL_COPY_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    straight_list_s copy = copy_straight_list(test, copy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 1.", 1, copy.size);

    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", get_straight_list(test, 0).sub_one, get_straight_list(copy, 0).sub_one);

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&copy, destroy_int);

    PASS();
}

TEST FASL_COPY_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s copy = copy_straight_list(test, copy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST - 1'.", MAXIMUM_FINITE_STRAIGHT_LIST - 1, copy.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", get_straight_list(test, i).sub_one, get_straight_list(copy, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&copy, destroy_int);

    PASS();
}

TEST FASL_COPY_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s copy = copy_straight_list(test, copy_int);

    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST'.", MAXIMUM_FINITE_STRAIGHT_LIST, copy.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", get_straight_list(test, i).sub_one, get_straight_list(copy, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&copy, destroy_int);

    PASS();
}

TEST FASL_COPY_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s copy = copy_straight_list(test, copy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to be NULL.", NULL, copy.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, copy.size);

    destroy_straight_list(&test, destroy_string);
    destroy_straight_list(&copy, destroy_string);

    PASS();
}

TEST FASL_COPY_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    straight_list_s copy = copy_straight_list(test, copy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 1.", 1, copy.size);

    STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, 0);
    STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, 0);
    ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_straight_list(&test, destroy_string);
    destroy_straight_list(&copy, destroy_string);

    PASS();
}

TEST FASL_COPY_07(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    straight_list_s copy = copy_straight_list(test, copy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST - 1'.", MAXIMUM_FINITE_STRAIGHT_LIST - 1, copy.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_string);
    destroy_straight_list(&copy, destroy_string);

    PASS();
}

TEST FASL_COPY_08(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    straight_list_s copy = copy_straight_list(test, copy_string);

    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST'.", MAXIMUM_FINITE_STRAIGHT_LIST, copy.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_string);
    destroy_straight_list(&copy, destroy_string);

    PASS();
}

TEST FASL_IS_EMPTY_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    ASSERTm("[FASL-ERROR] Expected list to be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_IS_EMPTY_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FASL-ERROR] Expected list to not be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_IS_EMPTY_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FASL-ERROR] Expected list to not be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_IS_EMPTY_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FASL-ERROR] Expected list to not be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_IS_FULL_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    ASSERT_FALSEm("[FASL-ERROR] Expected list to not be full.", is_full_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_IS_FULL_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FASL-ERROR] Expected list to not be full.", is_full_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_IS_FULL_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FASL-ERROR] Expected list to not be full.", is_full_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_IS_FULL_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERTm("[FASL-ERROR] Expected list to be full.", is_full_straight_list(test));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_FOREACH_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, });

    int increment = 5;
    foreach_straight_list(&test, operation_int, &increment);

    ASSERT_EQm("[FASL-ERROR] Expected incremented element by 'increment'.", 0 + increment, remove_at_straight_list(&test, 0).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_FOREACH_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_straight_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
        ASSERT_EQm("[FASL-ERROR] Expected incremented element by 'increment'.", i + increment, element.sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_FOREACH_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_straight_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_straight_list(&test, 0).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_FOREACH_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_straight_list(&test, operation_string, new_string);

    STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
    ASSERT_STRN_EQm("[FASL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_FOREACH_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_straight_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
        ASSERT_STRN_EQm("[FASL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_FOREACH_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_straight_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
        ASSERT_STRN_EQm("[FASL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_MAP_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    map_straight_list(&test, sort_int, compare_int);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_MAP_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_MAP_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_MAP_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    map_straight_list(&test, sort_int, compare_reverse_int);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_MAP_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_reverse_int);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_FINITE_STRAIGHT_LIST - 1 - 1) - i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_MAP_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_reverse_int);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_FINITE_STRAIGHT_LIST - 1) - i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    ASSERT_FALSEm("[FASL-ERROR] Expected search to be false.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST - 1;
    for (size_t i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_07(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_08(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_09(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERT_FALSEm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_10(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERT_FALSEm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_11(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST - 1;
    for (size_t i = 1; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERT_FALSEm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_12(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST;
    for (size_t i = 1; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    ASSERT_FALSEm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_13(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_BINARY_SEARCH_14(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    const size_t count = MAXIMUM_FINITE_STRAIGHT_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_straight_list(&test, sort_int, compare_int);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[FASL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_INSERT_AT_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FASL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42, get_straight_list(test, 0).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_INSERT_AT_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FASL_ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST - 1'.", MAXIMUM_FINITE_STRAIGHT_LIST - 1, test.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_INSERT_AT_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FASL_ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST'.", MAXIMUM_FINITE_STRAIGHT_LIST, test.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_INSERT_AT_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_EQm("[FASL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", TEST_STRING, get_straight_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_INSERT_AT_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FASL_ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST - 1'.", MAXIMUM_FINITE_STRAIGHT_LIST - 1, test.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", TEST_STRING, get_straight_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_INSERT_AT_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FASL_ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST'.", MAXIMUM_FINITE_STRAIGHT_LIST, test.size);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", TEST_STRING, get_straight_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_GET_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42, get_straight_list(test, 0).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_GET_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_GET_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_GET_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", TEST_STRING, get_straight_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_GET_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", TEST_STRING, get_straight_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_GET_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, copy_string((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_STRN_EQm("[FASL-ERROR] Expected elements to be equal.", TEST_STRING, get_straight_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_string);

    PASS();
}

TEST FASL_REMOVE_FIRST_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    STRAIGHT_LIST_DATA_TYPE element = (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_straight_list(&test, test.size, element);

    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42, remove_first_straight_list(&test, element, compare_int).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REMOVE_FIRST_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    STRAIGHT_LIST_DATA_TYPE element = (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42, remove_first_straight_list(&test, element, compare_int).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REMOVE_FIRST_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    STRAIGHT_LIST_DATA_TYPE element = (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42, remove_first_straight_list(&test, element, compare_int).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REMOVE_AT_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42, remove_at_straight_list(&test, 0).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REMOVE_AT_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, remove_at_straight_list(&test, 0).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REMOVE_AT_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, remove_at_straight_list(&test, 0).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REMOVE_AT_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, remove_at_straight_list(&test, test.size - 1).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REMOVE_AT_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, remove_at_straight_list(&test, test.size - 1).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REVERSE_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    reverse_straight_list(&test);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REVERSE_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_straight_list(&test);

    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42,  get_straight_list(test, 0).sub_one);

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REVERSE_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_straight_list(&test);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i,  get_straight_list(test, test.size - 1 - i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REVERSE_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_straight_list(&test);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i,  get_straight_list(test, test.size - 1 - i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REVERSE_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_straight_list(&test);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i,  get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_REVERSE_06(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_straight_list(&test);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i,  get_straight_list(test, i).sub_one);
    }

    destroy_straight_list(&test, destroy_int);

    PASS();
}

TEST FASL_SPLICE_01(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    splice_straight_list(&one, &two, 0, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, one.next);

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_02(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_straight_list(&one, &two, 0, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 1.", 1, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);
    ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", 42, get_straight_list(one, 0).sub_one);

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_03(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&one, &two, 0, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST - 1.'", MAXIMUM_FINITE_STRAIGHT_LIST - 1, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_04(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&one, &two, 0, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST.'", MAXIMUM_FINITE_STRAIGHT_LIST, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_05(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i++) {
        insert_at_straight_list(&one, one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&one, &two, one.size, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST - 1.'", MAXIMUM_FINITE_STRAIGHT_LIST - 1, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_06(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i++) {
        insert_at_straight_list(&one, one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&one, &two, one.size, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST.'", MAXIMUM_FINITE_STRAIGHT_LIST, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_07(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&one, one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&one, &two, 0, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST - 1.'", MAXIMUM_FINITE_STRAIGHT_LIST - 1, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_08(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&one, one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&one, &two, 0, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 'MAXIMUM_FINITE_STRAIGHT_LIST.'", MAXIMUM_FINITE_STRAIGHT_LIST, one.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);

    PASS();
}

TEST FASL_SPLICE_09(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s three = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST - 1) / 3; i++) {
        insert_at_straight_list(&one, one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST - 1) / 3; i < (2 *(MAXIMUM_FINITE_STRAIGHT_LIST - 1)) / 3; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_FINITE_STRAIGHT_LIST - 1)) / 3; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        insert_at_straight_list(&three, three.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_straight_list(&one, &three, start, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    splice_straight_list(&one, &two, start, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);
    destroy_straight_list(&three, destroy_int);

    PASS();
}

TEST FASL_SPLICE_10(void) {
    straight_list_s one = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s two = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);
    straight_list_s three = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST) / 3; i++) {
        insert_at_straight_list(&one, one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST) / 3; i < (2 *(MAXIMUM_FINITE_STRAIGHT_LIST)) / 3; i++) {
        insert_at_straight_list(&two, two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_FINITE_STRAIGHT_LIST)) / 3; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        insert_at_straight_list(&three, three.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_straight_list(&one, &three, start, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    splice_straight_list(&one, &two, start, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, one.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, three.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, three.next);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; i++) {
        ASSERT_EQm("[FASL-ERROR] Expected elements to be equal.", i, get_straight_list(one, i).sub_one);
    }

    destroy_straight_list(&one, destroy_int);
    destroy_straight_list(&two, destroy_int);
    destroy_straight_list(&three, destroy_int);

    PASS();
}

TEST FASL_SPLIT_01(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    straight_list_s split = split_straight_list(&test, 0, 1, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, split.max);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, test.next);

    ASSERT_EQm("[FASL-ERROR] Expected size to be 1.", 1, split.size);
    ASSERT_NEQm("[FASL-ERROR] Expected elements to be NULL.", NULL, split.elements);
    ASSERT_NEQm("[FASL-ERROR] Expected next to be NULL.", NULL, split.next);

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&split, destroy_int);

    PASS();
}

TEST FASL_SPLIT_02(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s split = split_straight_list(&test, 0, (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, split.max);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(split, i).sub_one);
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(test, i - ((MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1)).sub_one);
    }

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&split, destroy_int);

    PASS();
}

TEST FASL_SPLIT_03(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s split = split_straight_list(&test, 0, MAXIMUM_FINITE_STRAIGHT_LIST >> 1, MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, split.max);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST >> 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(split, i).sub_one);
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(test, i - (MAXIMUM_FINITE_STRAIGHT_LIST >> 1)).sub_one);
    }

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&split, destroy_int);

    PASS();
}

TEST FASL_SPLIT_04(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s split = split_straight_list(&test, (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1, test.size - ((MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1), MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, split.max);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(test, i).sub_one);
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST - 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(split, i - ((MAXIMUM_FINITE_STRAIGHT_LIST - 1) >> 1)).sub_one);
    }

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&split, destroy_int);

    PASS();
}

TEST FASL_SPLIT_05(void) {
    straight_list_s test = create_straight_list(MAXIMUM_FINITE_STRAIGHT_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s split = split_straight_list(&test, MAXIMUM_FINITE_STRAIGHT_LIST >> 1, test.size - (MAXIMUM_FINITE_STRAIGHT_LIST >> 1), MAXIMUM_FINITE_STRAIGHT_LIST);
    ASSERT_EQm("[FASL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_STRAIGHT_LIST, split.max);

    for (int i = 0; i < (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(test, i).sub_one);
    }

    for (int i = (MAXIMUM_FINITE_STRAIGHT_LIST) >> 1; i < MAXIMUM_FINITE_STRAIGHT_LIST; ++i) {
        ASSERT_EQm("[FASL-ERROR] Expected element to be equal to i.", i, get_straight_list(split, i - (MAXIMUM_FINITE_STRAIGHT_LIST >> 1)).sub_one);
    }

    destroy_straight_list(&test, destroy_int);
    destroy_straight_list(&split, destroy_int);

    PASS();
}

SUITE (finite_allocated_straight_list_test) {
    // create
    RUN_TEST(FASL_CREATE_01);
    // destroy
    RUN_TEST(FASL_DESTROY_01); RUN_TEST(FASL_DESTROY_02); RUN_TEST(FASL_DESTROY_03); RUN_TEST(FASL_DESTROY_04);
    RUN_TEST(FASL_DESTROY_05); RUN_TEST(FASL_DESTROY_06); RUN_TEST(FASL_DESTROY_07); RUN_TEST(FASL_DESTROY_08);
    // clear
    RUN_TEST(FASL_CLEAR_01); RUN_TEST(FASL_CLEAR_02); RUN_TEST(FASL_CLEAR_03); RUN_TEST(FASL_CLEAR_04);
    RUN_TEST(FASL_CLEAR_05); RUN_TEST(FASL_CLEAR_06); RUN_TEST(FASL_CLEAR_07); RUN_TEST(FASL_CLEAR_08);
    // copy
    RUN_TEST(FASL_COPY_01); RUN_TEST(FASL_COPY_02); RUN_TEST(FASL_COPY_03); RUN_TEST(FASL_COPY_04);
    RUN_TEST(FASL_COPY_05); RUN_TEST(FASL_COPY_06); RUN_TEST(FASL_COPY_07); RUN_TEST(FASL_COPY_08);
    // is empty
    RUN_TEST(FASL_IS_EMPTY_01); RUN_TEST(FASL_IS_EMPTY_02); RUN_TEST(FASL_IS_EMPTY_03); RUN_TEST(FASL_IS_EMPTY_04);
    // is full
    RUN_TEST(FASL_IS_FULL_01); RUN_TEST(FASL_IS_FULL_02); RUN_TEST(FASL_IS_FULL_03); RUN_TEST(FASL_IS_FULL_04);
    // foreach
    RUN_TEST(FASL_FOREACH_01); RUN_TEST(FASL_FOREACH_02); RUN_TEST(FASL_FOREACH_03); RUN_TEST(FASL_FOREACH_04);
    RUN_TEST(FASL_FOREACH_05); RUN_TEST(FASL_FOREACH_06);
    // map
    RUN_TEST(FASL_MAP_01); RUN_TEST(FASL_MAP_02); RUN_TEST(FASL_MAP_03); RUN_TEST(FASL_MAP_04);
    RUN_TEST(FASL_MAP_05); RUN_TEST(FASL_MAP_06);
    // binary search
    RUN_TEST(FASL_BINARY_SEARCH_01); RUN_TEST(FASL_BINARY_SEARCH_02); RUN_TEST(FASL_BINARY_SEARCH_03); RUN_TEST(FASL_BINARY_SEARCH_04);
    RUN_TEST(FASL_BINARY_SEARCH_05); RUN_TEST(FASL_BINARY_SEARCH_06); RUN_TEST(FASL_BINARY_SEARCH_07); RUN_TEST(FASL_BINARY_SEARCH_08);
    RUN_TEST(FASL_BINARY_SEARCH_09); RUN_TEST(FASL_BINARY_SEARCH_10); RUN_TEST(FASL_BINARY_SEARCH_11); RUN_TEST(FASL_BINARY_SEARCH_12);
    RUN_TEST(FASL_BINARY_SEARCH_13); RUN_TEST(FASL_BINARY_SEARCH_14);
    // insert at
    RUN_TEST(FASL_INSERT_AT_01); RUN_TEST(FASL_INSERT_AT_02); RUN_TEST(FASL_INSERT_AT_03); RUN_TEST(FASL_INSERT_AT_04);
    RUN_TEST(FASL_INSERT_AT_05); RUN_TEST(FASL_INSERT_AT_06);
    // get
    RUN_TEST(FASL_GET_01); RUN_TEST(FASL_GET_02); RUN_TEST(FASL_GET_03); RUN_TEST(FASL_GET_04);
    RUN_TEST(FASL_GET_05); RUN_TEST(FASL_GET_06);
    // remove first
    RUN_TEST(FASL_REMOVE_FIRST_01); RUN_TEST(FASL_REMOVE_FIRST_02); RUN_TEST(FASL_REMOVE_FIRST_03);
    // remove at
    RUN_TEST(FASL_REMOVE_AT_01); RUN_TEST(FASL_REMOVE_AT_02); RUN_TEST(FASL_REMOVE_AT_03); RUN_TEST(FASL_REMOVE_AT_04);
    RUN_TEST(FASL_REMOVE_AT_05);
    // reverse
    RUN_TEST(FASL_REVERSE_01); RUN_TEST(FASL_REVERSE_02); RUN_TEST(FASL_REVERSE_03); RUN_TEST(FASL_REVERSE_04);
    RUN_TEST(FASL_REVERSE_05); RUN_TEST(FASL_REVERSE_06);
    // splice
    RUN_TEST(FASL_SPLICE_01); RUN_TEST(FASL_SPLICE_02); RUN_TEST(FASL_SPLICE_03); RUN_TEST(FASL_SPLICE_04);
    RUN_TEST(FASL_SPLICE_05); RUN_TEST(FASL_SPLICE_06); RUN_TEST(FASL_SPLICE_07); RUN_TEST(FASL_SPLICE_08);
    RUN_TEST(FASL_SPLICE_09); RUN_TEST(FASL_SPLICE_10);
    // split
    RUN_TEST(FASL_SPLIT_01); RUN_TEST(FASL_SPLIT_02); RUN_TEST(FASL_SPLIT_03); RUN_TEST(FASL_SPLIT_04);
    RUN_TEST(FASL_SPLIT_05);
}
