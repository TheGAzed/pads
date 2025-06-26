#include <suits.h>

#define CIRCULAR_LIST_DATA_TYPE DATA_TYPE
#define CIRCULAR_LIST_SIZE (1 << 4)
#include <list/circular_list.h>

TEST CREATE_01(void) {
    circular_list_s test = create_circular_list();

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST DESTROY_01(void) {
    circular_list_s test = create_circular_list();

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_02(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_03(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_04(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    destroy_circular_list(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_05(void) {
    circular_list_s test = create_circular_list();

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_06(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_07(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_08(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_circular_list(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST COPY_01(void) {
    circular_list_s test = create_circular_list();
    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST COPY_02(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, copy.size);

    ASSERT_EQm("[ERROR] Expected elements to be equal.", get_circular_list(test, 0).sub_one, get_circular_list(copy, 0).sub_one);

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST COPY_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE - 1'.", CIRCULAR_LIST_SIZE - 1, copy.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", get_circular_list(test, i).sub_one, get_circular_list(copy, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST COPY_04(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s copy = copy_circular_list(test, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE'.", CIRCULAR_LIST_SIZE, copy.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", get_circular_list(test, i).sub_one, get_circular_list(copy, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&copy, destroy_int);

    PASS();
}

TEST COPY_05(void) {
    circular_list_s test = create_circular_list();
    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_NEQm("[ERROR] Expected head to be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head to be NULL.", NULL, copy.next);
    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, copy.size);

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST COPY_06(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, copy.size);

    CIRCULAR_LIST_DATA_TYPE test_element = get_circular_list(test, 0);
    CIRCULAR_LIST_DATA_TYPE copy_element = get_circular_list(copy, 0);
    ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST COPY_07(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE - 1'.", CIRCULAR_LIST_SIZE - 1, copy.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        CIRCULAR_LIST_DATA_TYPE test_element = get_circular_list(test, i);
        CIRCULAR_LIST_DATA_TYPE copy_element = get_circular_list(copy, i);
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST COPY_08(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    circular_list_s copy = copy_circular_list(test, copy_string);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE'.", CIRCULAR_LIST_SIZE, copy.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        CIRCULAR_LIST_DATA_TYPE test_element = get_circular_list(test, i);
        CIRCULAR_LIST_DATA_TYPE copy_element = get_circular_list(copy, i);
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", test_element.sub_two , copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);
    destroy_circular_list(&copy, destroy_string);

    PASS();
}

TEST IS_EMPTY_01(void) {
    circular_list_s test = create_circular_list();

    ASSERTm("[ERROR] Expected list to be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_02(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected list to not be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_03(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ERROR] Expected list to not be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_04(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ERROR] Expected list to not be empty.", is_empty_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST IS_FULL_01(void) {
    circular_list_s test = create_circular_list();

    ASSERT_FALSEm("[ERROR] Expected list to not be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST IS_FULL_02(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected list to not be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST IS_FULL_03(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ERROR] Expected list to not be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST IS_FULL_04(void) {
    circular_list_s test = create_circular_list();

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERTm("[ERROR] Expected list to be full.", is_full_circular_list(test));

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FOREACH_01(void) {
    circular_list_s test = create_circular_list();
    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 0, });

    int increment = 5;
    foreach_circular_list(test, operation_int, &increment);

    ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", 0 + increment, remove_at_circular_list(&test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FOREACH_02(void) {
    circular_list_s test = create_circular_list();
    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_circular_list(test, operation_int, &increment);

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, element.sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FOREACH_03(void) {
    circular_list_s test = create_circular_list();
    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_circular_list(test, operation_int, &increment);

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, remove_at_circular_list(&test, 0).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST FOREACH_04(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_circular_list(test, operation_string, new_string);

    CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
    ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FOREACH_05(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_circular_list(test, operation_string, new_string);

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST FOREACH_06(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_circular_list(test, operation_string, new_string);

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        CIRCULAR_LIST_DATA_TYPE element = remove_at_circular_list(&test, 0);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST MAP_01(void) {
    circular_list_s test = create_circular_list();

    struct compare cmp = { .function = compare_int_generic, };
    map_circular_list(test, sort_int, &cmp);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST MAP_02(void) {
    circular_list_s test = create_circular_list();

    for (int i = (CIRCULAR_LIST_SIZE - 1) >> 1; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (CIRCULAR_LIST_SIZE - 1) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_int_generic, };
    map_circular_list(test, sort_int, &cmp);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST MAP_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = (CIRCULAR_LIST_SIZE) >> 1; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (CIRCULAR_LIST_SIZE) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_int_generic, };
    map_circular_list(test, sort_int, &cmp);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST MAP_04(void) {
    circular_list_s test = create_circular_list();

    struct compare cmp = { .function = compare_reverse_int_generic, };
    map_circular_list(test, sort_int, &cmp);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST MAP_05(void) {
    circular_list_s test = create_circular_list();

    for (int i = (CIRCULAR_LIST_SIZE - 1) >> 1; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (CIRCULAR_LIST_SIZE - 1) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_reverse_int_generic, };
    map_circular_list(test, sort_int, &cmp);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (CIRCULAR_LIST_SIZE - 1 - 1) - (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST MAP_06(void) {
    circular_list_s test = create_circular_list();

    for (int i = (CIRCULAR_LIST_SIZE) >> 1; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (CIRCULAR_LIST_SIZE) >> 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_reverse_int_generic, };
    map_circular_list(test, sort_int, &cmp);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[IALS-ERROR] Expected element to be equal to i.", (CIRCULAR_LIST_SIZE - 1) - (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST INSERT_AT_01(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42, get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST INSERT_AT_02(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE - 1'.", CIRCULAR_LIST_SIZE - 1, test.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST INSERT_AT_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE'.", CIRCULAR_LIST_SIZE, test.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST INSERT_AT_04(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST INSERT_AT_05(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE - 1'.", CIRCULAR_LIST_SIZE - 1, test.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST INSERT_AT_06(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE'.", CIRCULAR_LIST_SIZE, test.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST GET_01(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42, get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST GET_02(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST GET_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST GET_04(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, 0).sub_two, sizeof(TEST_STRING) - 1);

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST GET_05(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST GET_06(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, copy_string((CIRCULAR_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", TEST_STRING, get_circular_list(test, i).sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_circular_list(&test, destroy_string);

    PASS();
}

TEST REMOVE_FIRST_01(void) {
    circular_list_s test = create_circular_list();

    CIRCULAR_LIST_DATA_TYPE element = (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_circular_list(&test, test.size, element);

    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42, remove_first_circular_list(&test, element, compare_int).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REMOVE_FIRST_02(void) {
    circular_list_s test = create_circular_list();

    CIRCULAR_LIST_DATA_TYPE element = (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42, remove_first_circular_list(&test, element, compare_int).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REMOVE_FIRST_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    CIRCULAR_LIST_DATA_TYPE element = (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, };
    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42, remove_first_circular_list(&test, element, compare_int).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REMOVE_AT_01(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42, remove_at_circular_list(&test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REMOVE_AT_02(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, 0).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REMOVE_AT_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, 0).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REMOVE_AT_04(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, test.size - 1).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REMOVE_AT_05(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", i, remove_at_circular_list(&test, test.size - 1).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REVERSE_01(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_circular_list(&test);

    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42,  get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REVERSE_02(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i,  get_circular_list(test, test.size - 1 - i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REVERSE_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i,  get_circular_list(test, test.size - 1 - i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REVERSE_04(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i,  get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST REVERSE_05(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_circular_list(&test);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(test, i).sub_one);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST SHIFT_01(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, 0, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_circular_list(&test, 1);

    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42,  get_circular_list(test, 0).sub_one);

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST SHIFT_02(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", i,  get_circular_list(test, 0).sub_one);
        shift_circular_list(&test, 1);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST SHIFT_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", i,  get_circular_list(test, 0).sub_one);
        shift_circular_list(&test, 1);
    }

    destroy_circular_list(&test, destroy_int);

    PASS();
}

TEST SPLICE_01(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    splice_circular_list(&one, &two, 0);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, one.size);

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_02(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_circular_list(&one, &two, 0);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, one.size);
    ASSERT_EQm("[ERROR] Expected elements to be equal.", 42, get_circular_list(one, 0).sub_one);

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_03(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE - 1.'", CIRCULAR_LIST_SIZE - 1, one.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_04(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE.'", CIRCULAR_LIST_SIZE, one.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_05(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    for (int i = 0; i < (CIRCULAR_LIST_SIZE - 1) >> 1; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (CIRCULAR_LIST_SIZE - 1) >> 1; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, one.size);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE - 1.'", CIRCULAR_LIST_SIZE - 1, one.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_06(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    for (int i = 0; i < (CIRCULAR_LIST_SIZE) >> 1; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (CIRCULAR_LIST_SIZE) >> 1; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, one.size);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE.'", CIRCULAR_LIST_SIZE, one.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_07(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    for (int i = 0; i < (CIRCULAR_LIST_SIZE - 1) >> 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (CIRCULAR_LIST_SIZE - 1) >> 1; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE - 1.'", CIRCULAR_LIST_SIZE - 1, one.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_08(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();

    for (int i = 0; i < (CIRCULAR_LIST_SIZE) >> 1; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (CIRCULAR_LIST_SIZE) >> 1; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_circular_list(&one, &two, 0);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 'CIRCULAR_LIST_SIZE.'", CIRCULAR_LIST_SIZE, one.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);

    PASS();
}

TEST SPLICE_09(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();
    circular_list_s three = create_circular_list();

    for (int i = 0; i < (CIRCULAR_LIST_SIZE - 1) / 3; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (CIRCULAR_LIST_SIZE - 1) / 3; i < (2 *(CIRCULAR_LIST_SIZE - 1)) / 3; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(CIRCULAR_LIST_SIZE - 1)) / 3; i < CIRCULAR_LIST_SIZE - 1; i++) {
        insert_at_circular_list(&three, three.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_circular_list(&one, &three, start);

    splice_circular_list(&one, &two, start);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, three.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE - 1; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);
    destroy_circular_list(&three, destroy_int);

    PASS();
}

TEST SPLICE_10(void) {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();
    circular_list_s three = create_circular_list();

    for (int i = 0; i < (CIRCULAR_LIST_SIZE) / 3; i++) {
        insert_at_circular_list(&one, one.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (CIRCULAR_LIST_SIZE) / 3; i < (2 *(CIRCULAR_LIST_SIZE)) / 3; i++) {
        insert_at_circular_list(&two, two.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (2 *(CIRCULAR_LIST_SIZE)) / 3; i < CIRCULAR_LIST_SIZE; i++) {
        insert_at_circular_list(&three, three.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t start = one.size;
    splice_circular_list(&one, &three, start);

    splice_circular_list(&one, &two, start);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, two.size);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, three.size);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE; i++) {
        ASSERT_EQm("[ERROR] Expected elements to be equal.", (int)i, get_circular_list(one, i).sub_one);
    }

    destroy_circular_list(&one, destroy_int);
    destroy_circular_list(&two, destroy_int);
    destroy_circular_list(&three, destroy_int);

    PASS();
}

TEST SPLIT_01(void) {
    circular_list_s test = create_circular_list();

    insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = 42, });

    circular_list_s split = split_circular_list(&test, 0, 1);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, split.size);

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST SPLIT_02(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, 0, (CIRCULAR_LIST_SIZE - 1) >> 1);

    for (size_t i = 0; i < (CIRCULAR_LIST_SIZE - 1) >> 1; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i).sub_one);
    }

    for (size_t i = (CIRCULAR_LIST_SIZE - 1) >> 1; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i - ((CIRCULAR_LIST_SIZE - 1) >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST SPLIT_03(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, 0, CIRCULAR_LIST_SIZE >> 1);

    for (size_t i = 0; i < CIRCULAR_LIST_SIZE >> 1; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i).sub_one);
    }

    for (size_t i = (CIRCULAR_LIST_SIZE) >> 1; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i - (CIRCULAR_LIST_SIZE >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST SPLIT_04(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, (CIRCULAR_LIST_SIZE - 1) >> 1, test.size - ((CIRCULAR_LIST_SIZE - 1) >> 1));

    for (size_t i = 0; i < (CIRCULAR_LIST_SIZE - 1) >> 1; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    for (size_t i = (CIRCULAR_LIST_SIZE - 1) >> 1; i < CIRCULAR_LIST_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i - ((CIRCULAR_LIST_SIZE - 1) >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

TEST SPLIT_05(void) {
    circular_list_s test = create_circular_list();

    for (int i = 0; i < CIRCULAR_LIST_SIZE; ++i) {
        insert_at_circular_list(&test, test.size, (CIRCULAR_LIST_DATA_TYPE) { .sub_one = i, });
    }

    circular_list_s split = split_circular_list(&test, CIRCULAR_LIST_SIZE >> 1, test.size - (CIRCULAR_LIST_SIZE >> 1));

    for (size_t i = 0; i < (CIRCULAR_LIST_SIZE) >> 1; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(test, i).sub_one);
    }

    for (size_t i = (CIRCULAR_LIST_SIZE) >> 1; i < CIRCULAR_LIST_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected element to be equal to i.", (int)i, get_circular_list(split, i - (CIRCULAR_LIST_SIZE >> 1)).sub_one);
    }

    destroy_circular_list(&test, destroy_int);
    destroy_circular_list(&split, destroy_int);

    PASS();
}

SUITE (circular_list_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01); RUN_TEST(DESTROY_02); RUN_TEST(DESTROY_03); RUN_TEST(DESTROY_04);
    RUN_TEST(DESTROY_05); RUN_TEST(DESTROY_06); RUN_TEST(DESTROY_07); RUN_TEST(DESTROY_08);
    // copy
    RUN_TEST(COPY_01); RUN_TEST(COPY_02); RUN_TEST(COPY_03); RUN_TEST(COPY_04);
    RUN_TEST(COPY_05); RUN_TEST(COPY_06); RUN_TEST(COPY_07); RUN_TEST(COPY_08);
    // is empty
    RUN_TEST(IS_EMPTY_01); RUN_TEST(IS_EMPTY_02); RUN_TEST(IS_EMPTY_03); RUN_TEST(IS_EMPTY_04);
    // is full
    RUN_TEST(IS_FULL_01); RUN_TEST(IS_FULL_02); RUN_TEST(IS_FULL_03); RUN_TEST(IS_FULL_04);
    // foreach
    RUN_TEST(FOREACH_01); RUN_TEST(FOREACH_02); RUN_TEST(FOREACH_03); RUN_TEST(FOREACH_04);
    RUN_TEST(FOREACH_05); RUN_TEST(FOREACH_06);
    // map
    RUN_TEST(MAP_01); RUN_TEST(MAP_02); RUN_TEST(MAP_03); RUN_TEST(MAP_04);
    RUN_TEST(MAP_05); RUN_TEST(MAP_06);
    // insert at
    RUN_TEST(INSERT_AT_01); RUN_TEST(INSERT_AT_02); RUN_TEST(INSERT_AT_03); RUN_TEST(INSERT_AT_04);
    RUN_TEST(INSERT_AT_05); RUN_TEST(INSERT_AT_06);
    // get
    RUN_TEST(GET_01); RUN_TEST(GET_02); RUN_TEST(GET_03); RUN_TEST(GET_04);
    RUN_TEST(GET_05); RUN_TEST(GET_06);
    // remove first
    RUN_TEST(REMOVE_FIRST_01); RUN_TEST(REMOVE_FIRST_02); RUN_TEST(REMOVE_FIRST_03);
    // remove at
    RUN_TEST(REMOVE_AT_01); RUN_TEST(REMOVE_AT_02); RUN_TEST(REMOVE_AT_03); RUN_TEST(REMOVE_AT_04);
    RUN_TEST(REMOVE_AT_05);
    // reverse
    RUN_TEST(REVERSE_01); RUN_TEST(REVERSE_02); RUN_TEST(REVERSE_03); RUN_TEST(REVERSE_04);
    RUN_TEST(REVERSE_05);
    // shift
    RUN_TEST(SHIFT_01); RUN_TEST(SHIFT_02); RUN_TEST(SHIFT_03);
    // splice
    RUN_TEST(SPLICE_01); RUN_TEST(SPLICE_02); RUN_TEST(SPLICE_03); RUN_TEST(SPLICE_04);
    RUN_TEST(SPLICE_05); RUN_TEST(SPLICE_06); RUN_TEST(SPLICE_07); RUN_TEST(SPLICE_08);
    RUN_TEST(SPLICE_09); RUN_TEST(SPLICE_10);
    // split
    RUN_TEST(SPLIT_01); RUN_TEST(SPLIT_02); RUN_TEST(SPLIT_03); RUN_TEST(SPLIT_04);
    RUN_TEST(SPLIT_05);
}
