#include "double_list_test.h"

#include <functions.h>

#define DOUBLE_LIST_MODE INFINITE_ALLOCATED_DOUBLE_LIST_MODE
#define MAXIMUM_INFINITE_DOUBLE_LIST (1 << 4)
#define DOUBLE_LIST_DATA_TYPE DATA_TYPE
#include <list/double_list/double_list.h>

TEST IADL_CREATE_01(void) {
    double_list_s test = create_double_list();

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_DESTROY_01(void) {
    double_list_s test = create_double_list();

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_05(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_06(void) {
    double_list_s test = create_double_list();

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_07(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_08(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_09(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_DESTROY_10(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST IADL_CLEAR_01(void) {
    double_list_s test = create_double_list();

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_CLEAR_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_CLEAR_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_CLEAR_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_CLEAR_05(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_CLEAR_06(void) {
    double_list_s test = create_double_list();

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_CLEAR_07(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_CLEAR_08(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_CLEAR_09(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_CLEAR_10(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_COPY_01(void) {
    double_list_s test = create_double_list();
    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, copy.size);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST IADL_COPY_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 1.", 1, copy.size);

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", get_double_list(test, 0).sub_one, get_double_list(copy, 0).sub_one);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST IADL_COPY_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST - 1'.", MAXIMUM_INFINITE_DOUBLE_LIST - 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", get_double_list(test, i).sub_one, get_double_list(copy, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST IADL_COPY_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST'.", MAXIMUM_INFINITE_DOUBLE_LIST, copy.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", get_double_list(test, i).sub_one, get_double_list(copy, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST IADL_COPY_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST + 1'.", MAXIMUM_INFINITE_DOUBLE_LIST + 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", get_double_list(test, i).sub_one, get_double_list(copy, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST IADL_COPY_06(void) {
    double_list_s test = create_double_list();
    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, copy.size);

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST IADL_COPY_07(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 1.", 1, copy.size);

    DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, 0);
    DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, 0);
    ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST IADL_COPY_08(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST - 1'.", MAXIMUM_INFINITE_DOUBLE_LIST - 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, i);
        DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, i);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST IADL_COPY_09(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST'.", MAXIMUM_INFINITE_DOUBLE_LIST, copy.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, i);
        DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, i);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST IADL_COPY_10(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, copy.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST + 1'.", MAXIMUM_INFINITE_DOUBLE_LIST + 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, i);
        DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, i);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST IADL_IS_EMPTY_01(void) {
    double_list_s test = create_double_list();

    ASSERTm("[IADL-ERROR] Expected list to be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_EMPTY_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_EMPTY_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_EMPTY_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_EMPTY_05(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_FULL_01(void) {
    double_list_s test = create_double_list();

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_FULL_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_FULL_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_FULL_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_IS_FULL_05(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_NEXT_01(void) {
    double_list_s test = create_double_list();
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 0, });

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", 0 + increment, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_NEXT_02(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_NEXT_03(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_NEXT_04(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_NEXT_05(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
    ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_FOREACH_NEXT_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_FOREACH_NEXT_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_FOREACH_NEXT_08(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_FOREACH_PREV_01(void) {
    double_list_s test = create_double_list();
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 0, });

    int increment = 5;
    foreach_prev_double_list(&test, operation_int, &increment);

    ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", 0 + increment, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_PREV_02(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_prev_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_PREV_03(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_prev_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_PREV_04(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_prev_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_FOREACH_PREV_05(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_prev_double_list(&test, operation_string, new_string);

    DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
    ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_FOREACH_PREV_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_prev_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_FOREACH_PREV_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_prev_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_FOREACH_PREV_08(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_prev_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[IADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_MAP_01(void) {
    double_list_s test = create_double_list();

    map_double_list(&test, sort_int, compare_int_generic);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_MAP_02(void) {
    double_list_s test = create_double_list();

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_MAP_03(void) {
    double_list_s test = create_double_list();

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_MAP_04(void) {
    double_list_s test = create_double_list();

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_MAP_05(void) {
    double_list_s test = create_double_list();

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_MAP_06(void) {
    double_list_s test = create_double_list();

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_INFINITE_DOUBLE_LIST - 1 - 1) - (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_MAP_07(void) {
    double_list_s test = create_double_list();

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_INFINITE_DOUBLE_LIST - 1) - (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_MAP_08(void) {
    double_list_s test = create_double_list();

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_INFINITE_DOUBLE_LIST + 1 - 1) - (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_INSERT_AT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_INSERT_AT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL_ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST - 1'.", MAXIMUM_INFINITE_DOUBLE_LIST - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_INSERT_AT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL_ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST'.", MAXIMUM_INFINITE_DOUBLE_LIST, test.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_INSERT_AT_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL_ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST + 1'.", MAXIMUM_INFINITE_DOUBLE_LIST + 1, test.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_INSERT_AT_05(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_EQm("[IADL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_INSERT_AT_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[IADL_ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST - 1'.", MAXIMUM_INFINITE_DOUBLE_LIST - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_INSERT_AT_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[IADL_ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST'.", MAXIMUM_INFINITE_DOUBLE_LIST, test.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_INSERT_AT_08(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[IADL_ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST + 1'.", MAXIMUM_INFINITE_DOUBLE_LIST + 1, test.size);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_GET_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_GET_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_GET_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_GET_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_GET_05(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_GET_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_GET_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_GET_08(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_STRN_EQm("[IADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST IADL_REMOVE_FIRST_01(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, element);

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_FIRST_02(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_FIRST_03(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_FIRST_04(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_FIRST_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_FIRST_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_FIRST_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_LAST_01(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, element);

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_last_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_LAST_02(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_last_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_LAST_03(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_last_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_LAST_04(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_last_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_LAST_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_last_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_LAST_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_last_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_LAST_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_last_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_AT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_AT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_AT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_AT_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_AT_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, test.size - 1);
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, element.sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_AT_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, remove_at_double_list(&test, test.size - 1).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REMOVE_AT_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, remove_at_double_list(&test, test.size - 1).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REVERSE_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_double_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REVERSE_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, test.size - 1 - i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REVERSE_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, test.size - 1 - i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REVERSE_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, test.size - 1 - i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REVERSE_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REVERSE_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_REVERSE_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_NEXT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_double_list(&test, 1);

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_NEXT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", i,  get_double_list(test, 0).sub_one);
        shift_next_double_list(&test, 1);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_NEXT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", i,  get_double_list(test, 0).sub_one);
        shift_next_double_list(&test, 1);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_NEXT_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", i,  get_double_list(test, 0).sub_one);
        shift_next_double_list(&test, 1);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_PREV_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_prev_double_list(&test, 1);

    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_PREV_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        shift_prev_double_list(&test, 1);
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", MAXIMUM_INFINITE_DOUBLE_LIST - 1 - 1 - i,  get_double_list(test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_PREV_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        shift_prev_double_list(&test, 1);
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", MAXIMUM_INFINITE_DOUBLE_LIST - 1 - i,  get_double_list(test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SHIFT_PREV_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        shift_prev_double_list(&test, 1);
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", MAXIMUM_INFINITE_DOUBLE_LIST - i,  get_double_list(test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST IADL_SPLICE_01(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, one.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, one.head);

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_02(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 1.", 1, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);
    ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", 42, get_double_list(one, 0).sub_one);

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_03(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST - 1.'", MAXIMUM_INFINITE_DOUBLE_LIST - 1, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_04(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST.'", MAXIMUM_INFINITE_DOUBLE_LIST, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_05(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST + 1.'", MAXIMUM_INFINITE_DOUBLE_LIST + 1, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_06(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, one.size);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST - 1.'", MAXIMUM_INFINITE_DOUBLE_LIST - 1, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_07(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, one.size);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST.'", MAXIMUM_INFINITE_DOUBLE_LIST, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_08(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, one.size);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST + 1.'", MAXIMUM_INFINITE_DOUBLE_LIST + 1, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_09(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST - 1.'", MAXIMUM_INFINITE_DOUBLE_LIST - 1, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_10(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST.'", MAXIMUM_INFINITE_DOUBLE_LIST, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_11(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 'MAXIMUM_INFINITE_DOUBLE_LIST + 1.'", MAXIMUM_INFINITE_DOUBLE_LIST + 1, one.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to not be NULL.", NULL, one.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST IADL_SPLICE_12(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();
    double_list_s three = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST - 1) / 3; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST - 1) / 3; i < (2 *(MAXIMUM_INFINITE_DOUBLE_LIST - 1)) / 3; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_INFINITE_DOUBLE_LIST - 1)) / 3; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&three, three.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_double_list(&one, &three, start);
    splice_double_list(&one, &two, start);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, three.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);
    destroy_double_list(&three, destroy_int);

    PASS();
}

TEST IADL_SPLICE_13(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();
    double_list_s three = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST) / 3; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST) / 3; i < (2 *(MAXIMUM_INFINITE_DOUBLE_LIST)) / 3; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_INFINITE_DOUBLE_LIST)) / 3; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&three, three.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_double_list(&one, &three, start);
    splice_double_list(&one, &two, start);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, three.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);
    destroy_double_list(&three, destroy_int);

    PASS();
}

TEST IADL_SPLICE_14(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();
    double_list_s three = create_double_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST + 1) / 3; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_INFINITE_DOUBLE_LIST + 1) / 3; i < (2 *(MAXIMUM_INFINITE_DOUBLE_LIST + 1)) / 3; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_INFINITE_DOUBLE_LIST + 1)) / 3; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        insert_at_double_list(&three, three.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_double_list(&one, &three, start);
    splice_double_list(&one, &two, start);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, two.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, three.head);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; i++) {
        ASSERT_EQm("[IADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);
    destroy_double_list(&three, destroy_int);

    PASS();
}

TEST IADL_SPLIT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    double_list_s split = split_double_list(&test, 0, 1);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL.", NULL, test.head);

    ASSERT_EQm("[IADL-ERROR] Expected size to be 1.", 1, split.size);
    ASSERT_NEQm("[IADL-ERROR] Expected head to be NULL.", NULL, split.head);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST IADL_SPLIT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, 0, (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1);

    for (size_t i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i).sub_one);
    }

    for (size_t i = (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i - ((MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST IADL_SPLIT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, 0, MAXIMUM_INFINITE_DOUBLE_LIST >> 1);

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST >> 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i).sub_one);
    }

    for (size_t i = (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i - (MAXIMUM_INFINITE_DOUBLE_LIST >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST IADL_SPLIT_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, 0, (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1);

    for (size_t i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i).sub_one);
    }

    for (size_t i = (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i - ((MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST IADL_SPLIT_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1, test.size - ((MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1));

    for (size_t i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    for (size_t i = (MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i - ((MAXIMUM_INFINITE_DOUBLE_LIST - 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST IADL_SPLIT_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, MAXIMUM_INFINITE_DOUBLE_LIST >> 1, test.size - (MAXIMUM_INFINITE_DOUBLE_LIST >> 1));

    for (size_t i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    for (size_t i = (MAXIMUM_INFINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i - (MAXIMUM_INFINITE_DOUBLE_LIST >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST IADL_SPLIT_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1, test.size - ((MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1));

    for (size_t i = 0; i < (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    for (size_t i = (MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i - ((MAXIMUM_INFINITE_DOUBLE_LIST + 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

SUITE (infinite_allocated_double_list_test) {
    // create
    RUN_TEST(IADL_CREATE_01);
    // destroy
    RUN_TEST(IADL_DESTROY_01); RUN_TEST(IADL_DESTROY_02); RUN_TEST(IADL_DESTROY_03); RUN_TEST(IADL_DESTROY_04);
    RUN_TEST(IADL_DESTROY_05); RUN_TEST(IADL_DESTROY_06); RUN_TEST(IADL_DESTROY_07); RUN_TEST(IADL_DESTROY_08);
    RUN_TEST(IADL_DESTROY_09); RUN_TEST(IADL_DESTROY_10);
    // clear
    RUN_TEST(IADL_CLEAR_01); RUN_TEST(IADL_CLEAR_02); RUN_TEST(IADL_CLEAR_03); RUN_TEST(IADL_CLEAR_04);
    RUN_TEST(IADL_CLEAR_05); RUN_TEST(IADL_CLEAR_06); RUN_TEST(IADL_CLEAR_07); RUN_TEST(IADL_CLEAR_08);
    RUN_TEST(IADL_CLEAR_09); RUN_TEST(IADL_CLEAR_10);
    // copy
    RUN_TEST(IADL_COPY_01); RUN_TEST(IADL_COPY_02); RUN_TEST(IADL_COPY_03); RUN_TEST(IADL_COPY_04);
    RUN_TEST(IADL_COPY_05); RUN_TEST(IADL_COPY_06); RUN_TEST(IADL_COPY_07); RUN_TEST(IADL_COPY_08);
    RUN_TEST(IADL_COPY_09); RUN_TEST(IADL_COPY_10);
    // is empty
    RUN_TEST(IADL_IS_EMPTY_01); RUN_TEST(IADL_IS_EMPTY_02); RUN_TEST(IADL_IS_EMPTY_03); RUN_TEST(IADL_IS_EMPTY_04);
    RUN_TEST(IADL_IS_EMPTY_05);
    // is full
    RUN_TEST(IADL_IS_FULL_01); RUN_TEST(IADL_IS_FULL_02); RUN_TEST(IADL_IS_FULL_03); RUN_TEST(IADL_IS_FULL_04);
    RUN_TEST(IADL_IS_FULL_05);
    // foreach next
    RUN_TEST(IADL_FOREACH_NEXT_01); RUN_TEST(IADL_FOREACH_NEXT_02); RUN_TEST(IADL_FOREACH_NEXT_03); RUN_TEST(IADL_FOREACH_NEXT_04);
    RUN_TEST(IADL_FOREACH_NEXT_05); RUN_TEST(IADL_FOREACH_NEXT_06); RUN_TEST(IADL_FOREACH_NEXT_07); RUN_TEST(IADL_FOREACH_NEXT_08);
    // foreach prev
    RUN_TEST(IADL_FOREACH_PREV_01); RUN_TEST(IADL_FOREACH_PREV_02); RUN_TEST(IADL_FOREACH_PREV_03); RUN_TEST(IADL_FOREACH_PREV_04);
    RUN_TEST(IADL_FOREACH_PREV_05); RUN_TEST(IADL_FOREACH_PREV_06); RUN_TEST(IADL_FOREACH_PREV_07); RUN_TEST(IADL_FOREACH_PREV_08);
    // map
    RUN_TEST(IADL_MAP_01); RUN_TEST(IADL_MAP_02); RUN_TEST(IADL_MAP_03); RUN_TEST(IADL_MAP_04);
    RUN_TEST(IADL_MAP_05); RUN_TEST(IADL_MAP_06); RUN_TEST(IADL_MAP_07); RUN_TEST(IADL_MAP_08);
    // insert at
    RUN_TEST(IADL_INSERT_AT_01); RUN_TEST(IADL_INSERT_AT_02); RUN_TEST(IADL_INSERT_AT_03); RUN_TEST(IADL_INSERT_AT_04);
    RUN_TEST(IADL_INSERT_AT_05); RUN_TEST(IADL_INSERT_AT_06); RUN_TEST(IADL_INSERT_AT_07); RUN_TEST(IADL_INSERT_AT_08);
    // get
    RUN_TEST(IADL_GET_01); RUN_TEST(IADL_GET_02); RUN_TEST(IADL_GET_03); RUN_TEST(IADL_GET_04);
    RUN_TEST(IADL_GET_05); RUN_TEST(IADL_GET_06); RUN_TEST(IADL_GET_07); RUN_TEST(IADL_GET_08);
    // remove first
    RUN_TEST(IADL_REMOVE_FIRST_01); RUN_TEST(IADL_REMOVE_FIRST_02); RUN_TEST(IADL_REMOVE_FIRST_03); RUN_TEST(IADL_REMOVE_FIRST_04);
    RUN_TEST(IADL_REMOVE_FIRST_05); RUN_TEST(IADL_REMOVE_FIRST_06); RUN_TEST(IADL_REMOVE_FIRST_07);
    // remove last
    RUN_TEST(IADL_REMOVE_LAST_01); RUN_TEST(IADL_REMOVE_LAST_02); RUN_TEST(IADL_REMOVE_LAST_03); RUN_TEST(IADL_REMOVE_LAST_04);
    RUN_TEST(IADL_REMOVE_LAST_05); RUN_TEST(IADL_REMOVE_LAST_06); RUN_TEST(IADL_REMOVE_LAST_07);
    // remove at
    RUN_TEST(IADL_REMOVE_AT_01); RUN_TEST(IADL_REMOVE_AT_02); RUN_TEST(IADL_REMOVE_AT_03); RUN_TEST(IADL_REMOVE_AT_04);
    RUN_TEST(IADL_REMOVE_AT_05); RUN_TEST(IADL_REMOVE_AT_06); RUN_TEST(IADL_REMOVE_AT_07);
    // reverse
    RUN_TEST(IADL_REVERSE_01); RUN_TEST(IADL_REVERSE_02); RUN_TEST(IADL_REVERSE_03); RUN_TEST(IADL_REVERSE_04);
    RUN_TEST(IADL_REVERSE_05); RUN_TEST(IADL_REVERSE_06); RUN_TEST(IADL_REVERSE_07);
    // shift next
    RUN_TEST(IADL_SHIFT_NEXT_01); RUN_TEST(IADL_SHIFT_NEXT_02); RUN_TEST(IADL_SHIFT_NEXT_03); RUN_TEST(IADL_SHIFT_NEXT_04);
    // shift prev
    RUN_TEST(IADL_SHIFT_PREV_01); RUN_TEST(IADL_SHIFT_PREV_02); RUN_TEST(IADL_SHIFT_PREV_03); RUN_TEST(IADL_SHIFT_PREV_04);
    // splice
    RUN_TEST(IADL_SPLICE_01); RUN_TEST(IADL_SPLICE_02); RUN_TEST(IADL_SPLICE_03); RUN_TEST(IADL_SPLICE_04);
    RUN_TEST(IADL_SPLICE_05); RUN_TEST(IADL_SPLICE_06); RUN_TEST(IADL_SPLICE_07); RUN_TEST(IADL_SPLICE_08);
    RUN_TEST(IADL_SPLICE_09); RUN_TEST(IADL_SPLICE_10); RUN_TEST(IADL_SPLICE_11); RUN_TEST(IADL_SPLICE_12);
    RUN_TEST(IADL_SPLICE_13); RUN_TEST(IADL_SPLICE_14);
    // split
    RUN_TEST(IADL_SPLIT_01); RUN_TEST(IADL_SPLIT_02); RUN_TEST(IADL_SPLIT_03); RUN_TEST(IADL_SPLIT_04);
    RUN_TEST(IADL_SPLIT_05); RUN_TEST(IADL_SPLIT_06); RUN_TEST(IADL_SPLIT_07);
}
