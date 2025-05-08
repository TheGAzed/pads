#include "circular_list_test.h"

#include <functions.h>

#define CIRCULAR_LIST_DATA_TYPE DATA_TYPE
#define CIRCULAR_LIST_MODE FINITE_ALLOCATED_CIRCULAR_LIST
#define MAXIMUM_FINITE_CIRCULAR_LIST (1 << 4)
#include <list/circular_list/circular_list.h>

TEST FACL_CREATE_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_DESTROY_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_DESTROY_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_DESTROY_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_DESTROY_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_DESTROY_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_DESTROY_06(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_DESTROY_07(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_DESTROY_08(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    PASS();
}

TEST FACL_CLEAR_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    clear_circular_list(&test, destroy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_CLEAR_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    clear_circular_list(&test, destroy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_CLEAR_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_circular_list(&test, destroy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_CLEAR_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_circular_list(&test, destroy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_CLEAR_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    clear_circular_list(&test, destroy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_CLEAR_06(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_circular_list(&test, destroy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_CLEAR_07(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_circular_list(&test, destroy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_CLEAR_08(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_circular_list(&test, destroy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_COPY_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, test.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.empty_size);

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST FACL_COPY_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 1.", 1, copy.size);

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", get_circular_list(test, 0).sub_one, get_circular_list(copy, 0).sub_one);

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST FACL_COPY_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST - 1'.", MAXIMUM_FINITE_CIRCULAR_LIST - 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", get_circular_list(test, i).sub_one, get_circular_list(copy, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST FACL_COPY_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST'.", MAXIMUM_FINITE_CIRCULAR_LIST, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", get_circular_list(test, i).sub_one, get_circular_list(copy, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST FACL_COPY_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to be NULL.", NULL, copy.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, copy.size);

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST FACL_COPY_06(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 1.", 1, copy.size);

    CIRCULAR_LIST_DATA_TYPE test_element = get_circular_list(test, 0);
    CIRCULAR_LIST_DATA_TYPE copy_element = get_circular_list(copy, 0);
    ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST FACL_COPY_07(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST - 1'.", MAXIMUM_FINITE_CIRCULAR_LIST - 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        CIRCULAR_LIST_DATA_TYPE test_element = get_circular_list(test, i);
        CIRCULAR_LIST_DATA_TYPE copy_element = get_circular_list(copy, i);
        ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST FACL_COPY_08(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected head to not be NULL.", NULL, copy.next);
    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST'.", MAXIMUM_FINITE_CIRCULAR_LIST, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        CIRCULAR_LIST_DATA_TYPE test_element = get_circular_list(test, i);
        CIRCULAR_LIST_DATA_TYPE copy_element = get_circular_list(copy, i);
        ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST FACL_IS_EMPTY_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    ASSERTm("[FACL-ERROR] Expected list to be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_IS_EMPTY_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FACL-ERROR] Expected list to not be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_IS_EMPTY_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FACL-ERROR] Expected list to not be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_IS_EMPTY_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FACL-ERROR] Expected list to not be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_IS_FULL_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    ASSERT_FALSEm("[FACL-ERROR] Expected list to not be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_IS_FULL_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FACL-ERROR] Expected list to not be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_IS_FULL_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FACL-ERROR] Expected list to not be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_IS_FULL_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERTm("[FACL-ERROR] Expected list to be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_FOREACH_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 0, });

    int increment = 5;
    foreach_circular_list(&test, operation_int, &increment);

    ASSERT_EQm("[FACL-ERROR] Expected incremented element by 'increment'.", 0 + increment, remove_at_circular_list(&test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_FOREACH_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_circular_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
        ASSERT_EQm("[FACL-ERROR] Expected incremented element by 'increment'.", i + increment, element.sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_FOREACH_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_circular_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_circular_list(&test, 0).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_FOREACH_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_circular_list(&test, operation_string, new_string);

    CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
    ASSERT_STRN_EQm("[FACL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_FOREACH_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_circular_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
        ASSERT_STRN_EQm("[FACL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_FOREACH_06(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_circular_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
        ASSERT_STRN_EQm("[FACL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_MAP_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    map_circular_list(&test, sort_int, compare_int_generic);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_MAP_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_circular_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_MAP_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_circular_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_MAP_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    map_circular_list(&test, sort_int, compare_reverse_int_generic);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_MAP_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_circular_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_FINITE_CIRCULAR_LIST - 1 - 1) - (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_MAP_06(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_circular_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_FINITE_CIRCULAR_LIST - 1) - (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_INSERT_AT_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FACL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42, get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_INSERT_AT_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FACL_ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST - 1'.", MAXIMUM_FINITE_CIRCULAR_LIST - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_INSERT_AT_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FACL_ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST'.", MAXIMUM_FINITE_CIRCULAR_LIST, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_INSERT_AT_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_EQm("[FACL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_INSERT_AT_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FACL_ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST - 1'.", MAXIMUM_FINITE_CIRCULAR_LIST - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_INSERT_AT_06(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FACL_ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST'.", MAXIMUM_FINITE_CIRCULAR_LIST, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_GET_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42, get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_GET_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_GET_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_GET_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_GET_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_GET_06(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_STRN_EQm("[FACL-ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FACL_REMOVE_FIRST_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    CIRCULAR_LIST_DATA_TYPE element = (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_circular_list(&test, test.size, element);

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42, remove_first_circular_list(&test, element, compare_int).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REMOVE_FIRST_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    CIRCULAR_LIST_DATA_TYPE element = (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42, remove_first_circular_list(&test, element, compare_int).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REMOVE_FIRST_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    CIRCULAR_LIST_DATA_TYPE element = (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42, remove_first_circular_list(&test, element, compare_int).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REMOVE_AT_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42, remove_at_circular_list(&test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REMOVE_AT_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, 0).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REMOVE_AT_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, 0).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REMOVE_AT_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, test.size - 1).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REMOVE_AT_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, test.size - 1).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REVERSE_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_circular_list(&test);

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42,  get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REVERSE_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i,  get_circular_list(test, test.size - 1 - i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REVERSE_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i,  get_circular_list(test, test.size - 1 - i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REVERSE_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_REVERSE_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_SHIFT_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_circular_list(&test, 1);

    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42,  get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_SHIFT_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", i,  get_circular_list(test, 0).sub_one);
        shift_circular_list(&test, 1);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_SHIFT_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", i,  get_circular_list(test, 0).sub_one);
        shift_circular_list(&test, 1);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FACL_SPLICE_01(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    splice_circular_list(&one, &two, 0, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, one.next);

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_02(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_circular_list(&one, &two, 0, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 1.", 1, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);
    ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", 42, get_circular_list(one, 0).sub_one);

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_03(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST - 1.'", MAXIMUM_FINITE_CIRCULAR_LIST - 1, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        CIRCULAR_LIST_DATA_TYPE element = get_circular_list(one, i);
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, element.sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_04(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST.'", MAXIMUM_FINITE_CIRCULAR_LIST, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_05(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, one.size, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST - 1.'", MAXIMUM_FINITE_CIRCULAR_LIST - 1, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_06(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, one.size, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST.'", MAXIMUM_FINITE_CIRCULAR_LIST, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_07(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST - 1.'", MAXIMUM_FINITE_CIRCULAR_LIST - 1, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_08(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 'MAXIMUM_FINITE_CIRCULAR_LIST.'", MAXIMUM_FINITE_CIRCULAR_LIST, one.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST FACL_SPLICE_09(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s three = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST - 1) / 3; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST - 1) / 3; i < (2 *(MAXIMUM_FINITE_CIRCULAR_LIST - 1)) / 3; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_FINITE_CIRCULAR_LIST - 1)) / 3; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        insert_at_circular_list(&three, three.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_circular_list(&one, &three, start, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    splice_circular_list(&one, &two, start, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to not be NULL.", NULL, one.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);
    destroy_circular_list(&three, destroy_int);

    PASS();
}

TEST FACL_SPLICE_10(void) {
    circular_list_s one = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s two = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);
    circular_list_s three = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST) / 3; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_CIRCULAR_LIST) / 3; i < (2 *(MAXIMUM_FINITE_CIRCULAR_LIST)) / 3; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_FINITE_CIRCULAR_LIST)) / 3; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        insert_at_circular_list(&three, three.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_circular_list(&one, &three, start, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    splice_circular_list(&one, &two, start, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, one.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, two.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, three.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, three.next);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; i++) {
        ASSERT_EQm("[FACL-ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);
    destroy_circular_list(&three, destroy_int);

    PASS();
}

TEST FACL_SPLIT_01(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    circular_list_s split = split_circular_list(&test, 0, 1, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, split.max);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, test.next);

    ASSERT_EQm("[FACL-ERROR] Expected size to be 1.", 1, split.size);
    ASSERT_NEQm("[FACL-ERROR] Expected elements to be NULL.", NULL, split.elements);
    ASSERT_NEQm("[FACL-ERROR] Expected next to be NULL.", NULL, split.next);

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST FACL_SPLIT_02(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, 0, (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, split.max);

    for (size_t i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i).sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i - ((MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST FACL_SPLIT_03(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, 0, MAXIMUM_FINITE_CIRCULAR_LIST >> 1, MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, split.max);

    for (size_t i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST >> 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i).sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i - (MAXIMUM_FINITE_CIRCULAR_LIST >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST FACL_SPLIT_04(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1, test.size - ((MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1), MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, split.max);

    for (size_t i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST - 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i - ((MAXIMUM_FINITE_CIRCULAR_LIST - 1) >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST FACL_SPLIT_05(void) {
    circular_list_s test = create_circular_list(MAXIMUM_FINITE_CIRCULAR_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, MAXIMUM_FINITE_CIRCULAR_LIST >> 1, test.size - (MAXIMUM_FINITE_CIRCULAR_LIST >> 1), MAXIMUM_FINITE_CIRCULAR_LIST);
    ASSERT_EQm("[FACL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_CIRCULAR_LIST, split.max);

    for (size_t i = 0; i < (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_CIRCULAR_LIST) >> 1; i < MAXIMUM_FINITE_CIRCULAR_LIST; ++i) {
        ASSERT_EQm("[FACL-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i - (MAXIMUM_FINITE_CIRCULAR_LIST >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

SUITE (finite_allocated_circular_list_test) {
        // create
    RUN_TEST(FACL_CREATE_01);
    // destroy
    RUN_TEST(FACL_DESTROY_01); RUN_TEST(FACL_DESTROY_02); RUN_TEST(FACL_DESTROY_03); RUN_TEST(FACL_DESTROY_04);
    RUN_TEST(FACL_DESTROY_05); RUN_TEST(FACL_DESTROY_06); RUN_TEST(FACL_DESTROY_07); RUN_TEST(FACL_DESTROY_08);
    // clear
    RUN_TEST(FACL_CLEAR_01); RUN_TEST(FACL_CLEAR_02); RUN_TEST(FACL_CLEAR_03); RUN_TEST(FACL_CLEAR_04);
    RUN_TEST(FACL_CLEAR_05); RUN_TEST(FACL_CLEAR_06); RUN_TEST(FACL_CLEAR_07); RUN_TEST(FACL_CLEAR_08);
    // copy
    RUN_TEST(FACL_COPY_01); RUN_TEST(FACL_COPY_02); RUN_TEST(FACL_COPY_03); RUN_TEST(FACL_COPY_04);
    RUN_TEST(FACL_COPY_05); RUN_TEST(FACL_COPY_06); RUN_TEST(FACL_COPY_07); RUN_TEST(FACL_COPY_08);
    // is empty
    RUN_TEST(FACL_IS_EMPTY_01); RUN_TEST(FACL_IS_EMPTY_02); RUN_TEST(FACL_IS_EMPTY_03); RUN_TEST(FACL_IS_EMPTY_04);
    // is full
    RUN_TEST(FACL_IS_FULL_01); RUN_TEST(FACL_IS_FULL_02); RUN_TEST(FACL_IS_FULL_03); RUN_TEST(FACL_IS_FULL_04);
    // foreach
    RUN_TEST(FACL_FOREACH_01); RUN_TEST(FACL_FOREACH_02); RUN_TEST(FACL_FOREACH_03); RUN_TEST(FACL_FOREACH_04);
    RUN_TEST(FACL_FOREACH_05); RUN_TEST(FACL_FOREACH_06);
    // map
    RUN_TEST(FACL_MAP_01); RUN_TEST(FACL_MAP_02); RUN_TEST(FACL_MAP_03); RUN_TEST(FACL_MAP_04);
    RUN_TEST(FACL_MAP_05); RUN_TEST(FACL_MAP_06);
    // insert at
    RUN_TEST(FACL_INSERT_AT_01); RUN_TEST(FACL_INSERT_AT_02); RUN_TEST(FACL_INSERT_AT_03); RUN_TEST(FACL_INSERT_AT_04);
    RUN_TEST(FACL_INSERT_AT_05); RUN_TEST(FACL_INSERT_AT_06);
    // get
    RUN_TEST(FACL_GET_01); RUN_TEST(FACL_GET_02); RUN_TEST(FACL_GET_03); RUN_TEST(FACL_GET_04);
    RUN_TEST(FACL_GET_05); RUN_TEST(FACL_GET_06);
    // remove first
    RUN_TEST(FACL_REMOVE_FIRST_01); RUN_TEST(FACL_REMOVE_FIRST_02); RUN_TEST(FACL_REMOVE_FIRST_03);
    // remove at
    RUN_TEST(FACL_REMOVE_AT_01); RUN_TEST(FACL_REMOVE_AT_02); RUN_TEST(FACL_REMOVE_AT_03); RUN_TEST(FACL_REMOVE_AT_04);
    RUN_TEST(FACL_REMOVE_AT_05);
    // reverse
    RUN_TEST(FACL_REVERSE_01); RUN_TEST(FACL_REVERSE_02); RUN_TEST(FACL_REVERSE_03); RUN_TEST(FACL_REVERSE_04);
    RUN_TEST(FACL_REVERSE_05);
    // shift
    RUN_TEST(FACL_SHIFT_01); RUN_TEST(FACL_SHIFT_02); RUN_TEST(FACL_SHIFT_03);
    // splice
    RUN_TEST(FACL_SPLICE_01); RUN_TEST(FACL_SPLICE_02); RUN_TEST(FACL_SPLICE_03); RUN_TEST(FACL_SPLICE_04);
    RUN_TEST(FACL_SPLICE_05); RUN_TEST(FACL_SPLICE_06); RUN_TEST(FACL_SPLICE_07); RUN_TEST(FACL_SPLICE_08);
    RUN_TEST(FACL_SPLICE_09); RUN_TEST(FACL_SPLICE_10);
    // split
    RUN_TEST(FACL_SPLIT_01); RUN_TEST(FACL_SPLIT_02); RUN_TEST(FACL_SPLIT_03); RUN_TEST(FACL_SPLIT_04);
    RUN_TEST(FACL_SPLIT_05);
}
