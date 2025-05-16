#include "double_list_test.h"

#include <functions.h>

#define DOUBLE_LIST_MODE FINITE_ALLOCATED_DOUBLE_LIST
#define MAXIMUM_FINITE_DOUBLE_LIST (1 << 4)
#define DOUBLE_LIST_DATA_TYPE DATA_TYPE
#include <list/double_list/double_list.h>

TEST FADL_CREATE_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_DESTROY_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_DESTROY_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_DESTROY_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_EQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_DESTROY_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_EQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_DESTROY_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_EQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_DESTROY_06(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_EQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_DESTROY_07(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_EQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_DESTROY_08(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_EQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_EQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FADL_CLEAR_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    clear_double_list(&test, destroy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_CLEAR_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    clear_double_list(&test, destroy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_CLEAR_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_double_list(&test, destroy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_CLEAR_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_double_list(&test, destroy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_CLEAR_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    clear_double_list(&test, destroy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_CLEAR_06(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_double_list(&test, destroy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_CLEAR_07(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_double_list(&test, destroy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_CLEAR_08(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_double_list(&test, destroy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_COPY_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FADL_COPY_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, copy.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, copy.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 1.", 1, copy.size);

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", get_double_list(test, 0).sub_one, get_double_list(copy, 0).sub_one);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FADL_COPY_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, copy.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, copy.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST - 1'.", MAXIMUM_FINITE_DOUBLE_LIST - 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", get_double_list(test, i).sub_one, get_double_list(copy, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FADL_COPY_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_NEQm("[FADL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, copy.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, copy.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST'.", MAXIMUM_FINITE_DOUBLE_LIST, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", get_double_list(test, i).sub_one, get_double_list(copy, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FADL_COPY_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, copy.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, copy.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, copy.size);

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FADL_COPY_06(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, copy.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, copy.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 1.", 1, copy.size);

    DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, 0);
    DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, 0);
    ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FADL_COPY_07(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, copy.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, copy.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST - 1'.", MAXIMUM_FINITE_DOUBLE_LIST - 1, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, i);
        DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, i);
        ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FADL_COPY_08(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_NEQm("[FADL-ERROR] Expected head to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, copy.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, copy.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST'.", MAXIMUM_FINITE_DOUBLE_LIST, copy.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, i);
        DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, i);
        ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FADL_IS_EMPTY_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    ASSERTm("[FADL-ERROR] Expected list to be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_IS_EMPTY_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FADL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_IS_EMPTY_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FADL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_IS_EMPTY_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FADL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_IS_FULL_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    ASSERT_FALSEm("[FADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_IS_FULL_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_IS_FULL_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FADL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_IS_FULL_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERTm("[FADL-ERROR] Expected list to be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_FOREACH_NEXT_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 0, });

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    ASSERT_EQm("[FADL-ERROR] Expected incremented element by 'increment'.", 0 + increment, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_FOREACH_NEXT_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_EQm("[FADL-ERROR] Expected incremented element by 'increment'.", i + increment, element.sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_FOREACH_NEXT_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_FOREACH_NEXT_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
    ASSERT_STRN_EQm("[FADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_FOREACH_NEXT_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[FADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_FOREACH_NEXT_06(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[FADL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_MAP_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    map_double_list(&test, sort_int, compare_int_generic);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_MAP_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_MAP_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_MAP_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_MAP_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_FINITE_DOUBLE_LIST - 1 - 1) - (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_MAP_06(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (MAXIMUM_FINITE_DOUBLE_LIST - 1) - (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_INSERT_AT_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FADL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42, get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_INSERT_AT_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FADL_ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST - 1'.", MAXIMUM_FINITE_DOUBLE_LIST - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_INSERT_AT_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FADL_ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST'.", MAXIMUM_FINITE_DOUBLE_LIST, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_INSERT_AT_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_EQm("[FADL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_INSERT_AT_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FADL_ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST - 1'.", MAXIMUM_FINITE_DOUBLE_LIST - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_INSERT_AT_06(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FADL_ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST'.", MAXIMUM_FINITE_DOUBLE_LIST, test.size);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_GET_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42, get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_GET_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_GET_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_GET_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_GET_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_GET_06(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_STRN_EQm("[FADL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FADL_REMOVE_FIRST_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, element);

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REMOVE_FIRST_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REMOVE_FIRST_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REMOVE_AT_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REMOVE_AT_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REMOVE_AT_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REMOVE_AT_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, test.size - 1);
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", i, element.sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REMOVE_AT_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", i, remove_at_double_list(&test, test.size - 1).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REVERSE_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_double_list(&test);

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REVERSE_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, test.size - 1 - i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REVERSE_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, test.size - 1 - i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REVERSE_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_REVERSE_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_SHIFT_NEXT_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_double_list(&test, 1);

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_SHIFT_NEXT_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", i,  get_double_list(test, 0).sub_one);
        shift_next_double_list(&test, 1);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_SHIFT_NEXT_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", i,  get_double_list(test, 0).sub_one);
        shift_next_double_list(&test, 1);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_SHIFT_PREV_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_prev_double_list(&test, 1);

    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_SHIFT_PREV_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        shift_prev_double_list(&test, 1);
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", MAXIMUM_FINITE_DOUBLE_LIST - 1 - 1 - i,  get_double_list(test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_SHIFT_PREV_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        shift_prev_double_list(&test, 1);
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", MAXIMUM_FINITE_DOUBLE_LIST - 1 - i,  get_double_list(test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FADL_SPLICE_01(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    splice_double_list(&one, &two, 0, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_02(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_double_list(&one, &two, 0, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 1.", 1, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);
    ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", 42, get_double_list(one, 0).sub_one);

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_03(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST - 1.'", MAXIMUM_FINITE_DOUBLE_LIST - 1, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        DOUBLE_LIST_DATA_TYPE element = get_double_list(one, i);
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, element.sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_04(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST.'", MAXIMUM_FINITE_DOUBLE_LIST, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_05(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, one.size, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST - 1.'", MAXIMUM_FINITE_DOUBLE_LIST - 1, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_06(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, one.size, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST.'", MAXIMUM_FINITE_DOUBLE_LIST, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_07(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST - 1.'", MAXIMUM_FINITE_DOUBLE_LIST - 1, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_08(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 'MAXIMUM_FINITE_DOUBLE_LIST.'", MAXIMUM_FINITE_DOUBLE_LIST, one.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FADL_SPLICE_09(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s three = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST - 1) / 3; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST - 1) / 3; i < (2 *(MAXIMUM_FINITE_DOUBLE_LIST - 1)) / 3; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_FINITE_DOUBLE_LIST - 1)) / 3; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        insert_at_double_list(&three, three.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_double_list(&one, &three, start, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    splice_double_list(&one, &two, start, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to not be NULL.", NULL, one.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to not be NULL.", NULL, one.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to not be NULL.", NULL, one.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);
    destroy_double_list(&three, destroy_int);

    PASS();
}

TEST FADL_SPLICE_10(void) {
    double_list_s one = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s two = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);
    double_list_s three = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST) / 3; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (MAXIMUM_FINITE_DOUBLE_LIST) / 3; i < (2 *(MAXIMUM_FINITE_DOUBLE_LIST)) / 3; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(MAXIMUM_FINITE_DOUBLE_LIST)) / 3; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        insert_at_double_list(&three, three.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_double_list(&one, &three, start, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    splice_double_list(&one, &two, start, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, one.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, two.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, two.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, two.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, two.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, three.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, three.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, three.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, three.node[DOUBLE_LIST_PREV]);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; i++) {
        ASSERT_EQm("[FADL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);
    destroy_double_list(&three, destroy_int);

    PASS();
}

TEST FADL_SPLIT_01(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    double_list_s split = split_double_list(&test, 0, 1, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, split.max);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, test.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, test.node[DOUBLE_LIST_PREV]);

    ASSERT_EQm("[FADL-ERROR] Expected size to be 1.", 1, split.size);
    ASSERT_NEQm("[FADL-ERROR] Expected elements to be NULL.", NULL, split.elements);
    ASSERT_NEQm("[FADL-ERROR] Expected next to be NULL.", NULL, split.node[DOUBLE_LIST_NEXT]);
    ASSERT_NEQm("[FADL-ERROR] Expected prev to be NULL.", NULL, split.node[DOUBLE_LIST_PREV]);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FADL_SPLIT_02(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, 0, (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, split.max);

    for (size_t i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = get_double_list(split, i);
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, element.sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i - ((MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FADL_SPLIT_03(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, 0, MAXIMUM_FINITE_DOUBLE_LIST >> 1, MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, split.max);

    for (size_t i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST >> 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i).sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i - (MAXIMUM_FINITE_DOUBLE_LIST >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FADL_SPLIT_04(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1, test.size - ((MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1), MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, split.max);

    for (size_t i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i - ((MAXIMUM_FINITE_DOUBLE_LIST - 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FADL_SPLIT_05(void) {
    double_list_s test = create_double_list(MAXIMUM_FINITE_DOUBLE_LIST);

    for (int i = 0; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, MAXIMUM_FINITE_DOUBLE_LIST >> 1, test.size - (MAXIMUM_FINITE_DOUBLE_LIST >> 1), MAXIMUM_FINITE_DOUBLE_LIST);
    ASSERT_EQm("[FADL-ERROR] Expected maximums to be the same.", MAXIMUM_FINITE_DOUBLE_LIST, split.max);

    for (size_t i = 0; i < (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    for (size_t i = (MAXIMUM_FINITE_DOUBLE_LIST) >> 1; i < MAXIMUM_FINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[FADL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i - (MAXIMUM_FINITE_DOUBLE_LIST >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

SUITE (finite_allocated_double_list_test) {
    // create
    RUN_TEST(FADL_CREATE_01);
    // destroy
    RUN_TEST(FADL_DESTROY_01); RUN_TEST(FADL_DESTROY_02); RUN_TEST(FADL_DESTROY_03); RUN_TEST(FADL_DESTROY_04);
    RUN_TEST(FADL_DESTROY_05); RUN_TEST(FADL_DESTROY_06); RUN_TEST(FADL_DESTROY_07); RUN_TEST(FADL_DESTROY_08);
    // clear
    RUN_TEST(FADL_CLEAR_01); RUN_TEST(FADL_CLEAR_02); RUN_TEST(FADL_CLEAR_03); RUN_TEST(FADL_CLEAR_04);
    RUN_TEST(FADL_CLEAR_05); RUN_TEST(FADL_CLEAR_06); RUN_TEST(FADL_CLEAR_07); RUN_TEST(FADL_CLEAR_08);
    // copy
    RUN_TEST(FADL_COPY_01); RUN_TEST(FADL_COPY_02); RUN_TEST(FADL_COPY_03); RUN_TEST(FADL_COPY_04);
    RUN_TEST(FADL_COPY_05); RUN_TEST(FADL_COPY_06); RUN_TEST(FADL_COPY_07); RUN_TEST(FADL_COPY_08);
    // is empty
    RUN_TEST(FADL_IS_EMPTY_01); RUN_TEST(FADL_IS_EMPTY_02); RUN_TEST(FADL_IS_EMPTY_03); RUN_TEST(FADL_IS_EMPTY_04);
    // is full
    RUN_TEST(FADL_IS_FULL_01); RUN_TEST(FADL_IS_FULL_02); RUN_TEST(FADL_IS_FULL_03); RUN_TEST(FADL_IS_FULL_04);
    // foreach
    RUN_TEST(FADL_FOREACH_NEXT_01); RUN_TEST(FADL_FOREACH_NEXT_02); RUN_TEST(FADL_FOREACH_NEXT_03); RUN_TEST(FADL_FOREACH_NEXT_04);
    RUN_TEST(FADL_FOREACH_NEXT_05); RUN_TEST(FADL_FOREACH_NEXT_06);
    // map
    RUN_TEST(FADL_MAP_01); RUN_TEST(FADL_MAP_02); RUN_TEST(FADL_MAP_03); RUN_TEST(FADL_MAP_04);
    RUN_TEST(FADL_MAP_05); RUN_TEST(FADL_MAP_06);
    // insert at
    RUN_TEST(FADL_INSERT_AT_01); RUN_TEST(FADL_INSERT_AT_02); RUN_TEST(FADL_INSERT_AT_03); RUN_TEST(FADL_INSERT_AT_04);
    RUN_TEST(FADL_INSERT_AT_05); RUN_TEST(FADL_INSERT_AT_06);
    // get
    RUN_TEST(FADL_GET_01); RUN_TEST(FADL_GET_02); RUN_TEST(FADL_GET_03); RUN_TEST(FADL_GET_04);
    RUN_TEST(FADL_GET_05); RUN_TEST(FADL_GET_06);
    // remove first
    RUN_TEST(FADL_REMOVE_FIRST_01); RUN_TEST(FADL_REMOVE_FIRST_02); RUN_TEST(FADL_REMOVE_FIRST_03);
    // remove at
    RUN_TEST(FADL_REMOVE_AT_01); RUN_TEST(FADL_REMOVE_AT_02); RUN_TEST(FADL_REMOVE_AT_03); RUN_TEST(FADL_REMOVE_AT_04);
    RUN_TEST(FADL_REMOVE_AT_05);
    // reverse
    RUN_TEST(FADL_REVERSE_01); RUN_TEST(FADL_REVERSE_02); RUN_TEST(FADL_REVERSE_03); RUN_TEST(FADL_REVERSE_04);
    RUN_TEST(FADL_REVERSE_05);
    // shift
    RUN_TEST(FADL_SHIFT_NEXT_01); RUN_TEST(FADL_SHIFT_NEXT_02); RUN_TEST(FADL_SHIFT_NEXT_03);
    // shift
    RUN_TEST(FADL_SHIFT_PREV_01); RUN_TEST(FADL_SHIFT_PREV_02); RUN_TEST(FADL_SHIFT_PREV_03);
    // splice
    RUN_TEST(FADL_SPLICE_01); RUN_TEST(FADL_SPLICE_02); RUN_TEST(FADL_SPLICE_03); RUN_TEST(FADL_SPLICE_04);
    RUN_TEST(FADL_SPLICE_05); RUN_TEST(FADL_SPLICE_06); RUN_TEST(FADL_SPLICE_07); RUN_TEST(FADL_SPLICE_08);
    RUN_TEST(FADL_SPLICE_09); RUN_TEST(FADL_SPLICE_10);
    // split
    RUN_TEST(FADL_SPLIT_01); RUN_TEST(FADL_SPLIT_02); RUN_TEST(FADL_SPLIT_03); RUN_TEST(FADL_SPLIT_04);
    RUN_TEST(FADL_SPLIT_05);
}
