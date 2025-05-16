#include "double_list_test.h"

#include <functions.h>

#define DOUBLE_LIST_MODE FINITE_PREPROCESSOR_DOUBLE_LIST
#define PREPROCESSOR_DOUBLE_LIST_SIZE (1 << 4)
#define DOUBLE_LIST_DATA_TYPE DATA_TYPE
#include <list/double_list/double_list.h>

TEST FPDL_CREATE_01(void) {
    double_list_s test = create_double_list();

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_DESTROY_01(void) {
    double_list_s test = create_double_list();

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_DESTROY_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_DESTROY_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_DESTROY_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_DESTROY_05(void) {
    double_list_s test = create_double_list();

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_DESTROY_06(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_DESTROY_07(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_DESTROY_08(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPDL_CLEAR_01(void) {
    double_list_s test = create_double_list();

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_CLEAR_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_CLEAR_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_CLEAR_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    clear_double_list(&test, destroy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_CLEAR_05(void) {
    double_list_s test = create_double_list();

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_CLEAR_06(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_CLEAR_07(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_CLEAR_08(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_double_list(&test, destroy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_COPY_01(void) {
    double_list_s test = create_double_list();
    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FPDL_COPY_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 1.", 1, copy.size);

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", get_double_list(test, 0).sub_one, get_double_list(copy, 0).sub_one);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FPDL_COPY_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE - 1'.", PREPROCESSOR_DOUBLE_LIST_SIZE - 1, copy.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", get_double_list(test, i).sub_one, get_double_list(copy, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FPDL_COPY_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s copy = copy_double_list(test, copy_int);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE'.", PREPROCESSOR_DOUBLE_LIST_SIZE, copy.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", get_double_list(test, i).sub_one, get_double_list(copy, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&copy, destroy_int);

    PASS();
}

TEST FPDL_COPY_05(void) {
    double_list_s test = create_double_list();
    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, copy.size);

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FPDL_COPY_06(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 1.", 1, copy.size);

    DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, 0);
    DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, 0);
    ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FPDL_COPY_07(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE - 1'.", PREPROCESSOR_DOUBLE_LIST_SIZE - 1, copy.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, i);
        DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, i);
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FPDL_COPY_08(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    double_list_s copy = copy_double_list(test, copy_string);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE'.", PREPROCESSOR_DOUBLE_LIST_SIZE, copy.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        DOUBLE_LIST_DATA_TYPE test_element = get_double_list(test, i);
        DOUBLE_LIST_DATA_TYPE copy_element = get_double_list(copy, i);
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);
    destroy_double_list(&copy, destroy_string);

    PASS();
}

TEST FPDL_IS_EMPTY_01(void) {
    double_list_s test = create_double_list();

    ASSERTm("[FPDL-ERROR] Expected list to be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_IS_EMPTY_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FPDL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_IS_EMPTY_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPDL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_IS_EMPTY_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPDL-ERROR] Expected list to not be empty.", is_empty_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_IS_FULL_01(void) {
    double_list_s test = create_double_list();

    ASSERT_FALSEm("[FPDL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_IS_FULL_02(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[FPDL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_IS_FULL_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPDL-ERROR] Expected list to not be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_IS_FULL_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERTm("[FPDL-ERROR] Expected list to be full.", is_full_double_list(test));

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_FOREACH_NEXT_01(void) {
    double_list_s test = create_double_list();
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 0, });

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    ASSERT_EQm("[FPDL-ERROR] Expected incremented element by 'increment'.", 0 + increment, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_FOREACH_NEXT_02(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_EQm("[FPDL-ERROR] Expected incremented element by 'increment'.", i + increment, element.sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_FOREACH_NEXT_03(void) {
    double_list_s test = create_double_list();
    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_next_double_list(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_FOREACH_NEXT_04(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
    ASSERT_STRN_EQm("[FPDL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_FOREACH_NEXT_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_FOREACH_NEXT_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_next_double_list(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, 0);
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_MAP_01(void) {
    double_list_s test = create_double_list();

    map_double_list(&test, sort_int, compare_int_generic);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_MAP_02(void) {
    double_list_s test = create_double_list();

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_MAP_03(void) {
    double_list_s test = create_double_list();

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_MAP_04(void) {
    double_list_s test = create_double_list();

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_MAP_05(void) {
    double_list_s test = create_double_list();

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (PREPROCESSOR_DOUBLE_LIST_SIZE - 1 - 1) - (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_MAP_06(void) {
    double_list_s test = create_double_list();

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    map_double_list(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) - (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_INSERT_AT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPDL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42, get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_INSERT_AT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPDL_ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE - 1'.", PREPROCESSOR_DOUBLE_LIST_SIZE - 1, test.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_INSERT_AT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPDL_ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE'.", PREPROCESSOR_DOUBLE_LIST_SIZE, test.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_INSERT_AT_04(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_EQm("[FPDL_ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_INSERT_AT_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FPDL_ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE - 1'.", PREPROCESSOR_DOUBLE_LIST_SIZE - 1, test.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_INSERT_AT_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[FPDL_ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE'.", PREPROCESSOR_DOUBLE_LIST_SIZE, test.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_GET_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42, get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_GET_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_GET_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_GET_04(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_GET_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_GET_06(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, copy_string((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_STRN_EQm("[FPDL-ERROR] Expected elements to be equal.", TEST_STRING, get_double_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_double_list(&test, destroy_string);

    PASS();
}

TEST FPDL_REMOVE_FIRST_01(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, element);

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REMOVE_FIRST_02(void) {
    double_list_s test = create_double_list();

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REMOVE_FIRST_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    DOUBLE_LIST_DATA_TYPE element = (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42, remove_first_double_list(&test, element, compare_int).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REMOVE_AT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REMOVE_AT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REMOVE_AT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REMOVE_AT_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, test.size - 1);
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", i, element.sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REMOVE_AT_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", i, remove_at_double_list(&test, test.size - 1).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REVERSE_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_double_list(&test);

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REVERSE_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, test.size - 1 - i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REVERSE_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i,  get_double_list(test, test.size - 1 - i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REVERSE_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_REVERSE_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_double_list(&test);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_SHIFT_NEXT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_double_list(&test, 1);

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_SHIFT_NEXT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", i,  get_double_list(test, 0).sub_one);
        shift_next_double_list(&test, 1);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_SHIFT_NEXT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", i,  get_double_list(test, 0).sub_one);
        shift_next_double_list(&test, 1);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_SHIFT_PREV_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_prev_double_list(&test, 1);

    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42,  get_double_list(test, 0).sub_one);

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_SHIFT_PREV_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        shift_prev_double_list(&test, 1);
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", PREPROCESSOR_DOUBLE_LIST_SIZE - 1 - 1 - i,  get_double_list(test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_SHIFT_PREV_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        shift_prev_double_list(&test, 1);
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", PREPROCESSOR_DOUBLE_LIST_SIZE - 1 - i,  get_double_list(test, 0).sub_one);
    }

    destroy_double_list(&test, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_01(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, one.size);

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_02(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 1.", 1, one.size);
    ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", 42, get_double_list(one, 0).sub_one);

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_03(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE - 1.'", PREPROCESSOR_DOUBLE_LIST_SIZE - 1, one.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        DOUBLE_LIST_DATA_TYPE element = get_double_list(one, i);
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, element.sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_04(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE.'", PREPROCESSOR_DOUBLE_LIST_SIZE, one.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_05(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, one.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE - 1.'", PREPROCESSOR_DOUBLE_LIST_SIZE - 1, one.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_06(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, one.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE.'", PREPROCESSOR_DOUBLE_LIST_SIZE, one.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_07(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE - 1.'", PREPROCESSOR_DOUBLE_LIST_SIZE - 1, one.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_08(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_double_list(&one, &two, 0);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 'PREPROCESSOR_DOUBLE_LIST_SIZE.'", PREPROCESSOR_DOUBLE_LIST_SIZE, one.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_09(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();
    double_list_s three = create_double_list();

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) / 3; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) / 3; i < (2 *(PREPROCESSOR_DOUBLE_LIST_SIZE - 1)) / 3; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(PREPROCESSOR_DOUBLE_LIST_SIZE - 1)) / 3; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        insert_at_double_list(&three, three.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_double_list(&one, &three, start);

    splice_double_list(&one, &two, start);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, three.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);
    destroy_double_list(&three, destroy_int);

    PASS();
}

TEST FPDL_SPLICE_10(void) {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();
    double_list_s three = create_double_list();

    for (int i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE) / 3; i++) {
        insert_at_double_list(&one, one.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (PREPROCESSOR_DOUBLE_LIST_SIZE) / 3; i < (2 *(PREPROCESSOR_DOUBLE_LIST_SIZE)) / 3; i++) {
        insert_at_double_list(&two, two.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(PREPROCESSOR_DOUBLE_LIST_SIZE)) / 3; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        insert_at_double_list(&three, three.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_double_list(&one, &three, start);

    splice_double_list(&one, &two, start);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, three.size);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; i++) {
        ASSERT_EQm("[FPDL-ERROR] Expected elements to be equal.", (int)i, get_double_list(one, i).sub_one);
    }

    destroy_double_list(&one, destroy_int);
    destroy_double_list(&two, destroy_int);
    destroy_double_list(&three, destroy_int);

    PASS();
}

TEST FPDL_SPLIT_01(void) {
    double_list_s test = create_double_list();

    insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    double_list_s split = split_double_list(&test, 0, 1);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 0.", 0, test.size);

    ASSERT_EQm("[FPDL-ERROR] Expected size to be 1.", 1, split.size);

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FPDL_SPLIT_02(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, 0, (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1);

    for (size_t i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; ++i) {
        DOUBLE_LIST_DATA_TYPE element = get_double_list(split, i);
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, element.sub_one);
    }

    for (size_t i = (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i - ((PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FPDL_SPLIT_03(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, 0, PREPROCESSOR_DOUBLE_LIST_SIZE >> 1);

    for (size_t i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE >> 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i).sub_one);
    }

    for (size_t i = (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i - (PREPROCESSOR_DOUBLE_LIST_SIZE >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FPDL_SPLIT_04(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1, test.size - ((PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1));

    for (size_t i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    for (size_t i = (PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i - ((PREPROCESSOR_DOUBLE_LIST_SIZE - 1) >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

TEST FPDL_SPLIT_05(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        insert_at_double_list(&test, test.size, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i, });
    }

    double_list_s split = split_double_list(&test, PREPROCESSOR_DOUBLE_LIST_SIZE >> 1, test.size - (PREPROCESSOR_DOUBLE_LIST_SIZE >> 1));

    for (size_t i = 0; i < (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(test, i).sub_one);
    }

    for (size_t i = (PREPROCESSOR_DOUBLE_LIST_SIZE) >> 1; i < PREPROCESSOR_DOUBLE_LIST_SIZE; ++i) {
        ASSERT_EQm("[FPDL-ERROR] Expected element to be equal to i.", (int)i, get_double_list(split, i - (PREPROCESSOR_DOUBLE_LIST_SIZE >> 1)).sub_one);
    }

    destroy_double_list(&test, destroy_int);
    destroy_double_list(&split, destroy_int);

    PASS();
}

SUITE (finite_preprocessor_double_list_test) {
    // create
    RUN_TEST(FPDL_CREATE_01);
    // destroy
    RUN_TEST(FPDL_DESTROY_01); RUN_TEST(FPDL_DESTROY_02); RUN_TEST(FPDL_DESTROY_03); RUN_TEST(FPDL_DESTROY_04);
    RUN_TEST(FPDL_DESTROY_05); RUN_TEST(FPDL_DESTROY_06); RUN_TEST(FPDL_DESTROY_07); RUN_TEST(FPDL_DESTROY_08);
    // clear
    RUN_TEST(FPDL_CLEAR_01); RUN_TEST(FPDL_CLEAR_02); RUN_TEST(FPDL_CLEAR_03); RUN_TEST(FPDL_CLEAR_04);
    RUN_TEST(FPDL_CLEAR_05); RUN_TEST(FPDL_CLEAR_06); RUN_TEST(FPDL_CLEAR_07); RUN_TEST(FPDL_CLEAR_08);
    // copy
    RUN_TEST(FPDL_COPY_01); RUN_TEST(FPDL_COPY_02); RUN_TEST(FPDL_COPY_03); RUN_TEST(FPDL_COPY_04);
    RUN_TEST(FPDL_COPY_05); RUN_TEST(FPDL_COPY_06); RUN_TEST(FPDL_COPY_07); RUN_TEST(FPDL_COPY_08);
    // is empty
    RUN_TEST(FPDL_IS_EMPTY_01); RUN_TEST(FPDL_IS_EMPTY_02); RUN_TEST(FPDL_IS_EMPTY_03); RUN_TEST(FPDL_IS_EMPTY_04);
    // is full
    RUN_TEST(FPDL_IS_FULL_01); RUN_TEST(FPDL_IS_FULL_02); RUN_TEST(FPDL_IS_FULL_03); RUN_TEST(FPDL_IS_FULL_04);
    // foreach
    RUN_TEST(FPDL_FOREACH_NEXT_01); RUN_TEST(FPDL_FOREACH_NEXT_02); RUN_TEST(FPDL_FOREACH_NEXT_03); RUN_TEST(FPDL_FOREACH_NEXT_04);
    RUN_TEST(FPDL_FOREACH_NEXT_05); RUN_TEST(FPDL_FOREACH_NEXT_06);
    // map
    RUN_TEST(FPDL_MAP_01); RUN_TEST(FPDL_MAP_02); RUN_TEST(FPDL_MAP_03); RUN_TEST(FPDL_MAP_04);
    RUN_TEST(FPDL_MAP_05); RUN_TEST(FPDL_MAP_06);
    // insert at
    RUN_TEST(FPDL_INSERT_AT_01); RUN_TEST(FPDL_INSERT_AT_02); RUN_TEST(FPDL_INSERT_AT_03); RUN_TEST(FPDL_INSERT_AT_04);
    RUN_TEST(FPDL_INSERT_AT_05); RUN_TEST(FPDL_INSERT_AT_06);
    // get
    RUN_TEST(FPDL_GET_01); RUN_TEST(FPDL_GET_02); RUN_TEST(FPDL_GET_03); RUN_TEST(FPDL_GET_04);
    RUN_TEST(FPDL_GET_05); RUN_TEST(FPDL_GET_06);
    // remove first
    RUN_TEST(FPDL_REMOVE_FIRST_01); RUN_TEST(FPDL_REMOVE_FIRST_02); RUN_TEST(FPDL_REMOVE_FIRST_03);
    // remove at
    RUN_TEST(FPDL_REMOVE_AT_01); RUN_TEST(FPDL_REMOVE_AT_02); RUN_TEST(FPDL_REMOVE_AT_03); RUN_TEST(FPDL_REMOVE_AT_04);
    RUN_TEST(FPDL_REMOVE_AT_05);
    // reverse
    RUN_TEST(FPDL_REVERSE_01); RUN_TEST(FPDL_REVERSE_02); RUN_TEST(FPDL_REVERSE_03); RUN_TEST(FPDL_REVERSE_04);
    RUN_TEST(FPDL_REVERSE_05);
    // shift
    RUN_TEST(FPDL_SHIFT_NEXT_01); RUN_TEST(FPDL_SHIFT_NEXT_02); RUN_TEST(FPDL_SHIFT_NEXT_03);
    // shift
    RUN_TEST(FPDL_SHIFT_PREV_01); RUN_TEST(FPDL_SHIFT_PREV_02); RUN_TEST(FPDL_SHIFT_PREV_03);
    // splice
    RUN_TEST(FPDL_SPLICE_01); RUN_TEST(FPDL_SPLICE_02); RUN_TEST(FPDL_SPLICE_03); RUN_TEST(FPDL_SPLICE_04);
    RUN_TEST(FPDL_SPLICE_05); RUN_TEST(FPDL_SPLICE_06); RUN_TEST(FPDL_SPLICE_07); RUN_TEST(FPDL_SPLICE_08);
    RUN_TEST(FPDL_SPLICE_09); RUN_TEST(FPDL_SPLICE_10);
    // split
    RUN_TEST(FPDL_SPLIT_01); RUN_TEST(FPDL_SPLIT_02); RUN_TEST(FPDL_SPLIT_03); RUN_TEST(FPDL_SPLIT_04);
    RUN_TEST(FPDL_SPLIT_05);
}
