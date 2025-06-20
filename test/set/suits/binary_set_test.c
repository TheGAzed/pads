#include <suits.h>

#define BINARY_SET_SIZE (1 << 4)
#define BINARY_SET_DATA_TYPE DATA_TYPE
#include <set/binary_set.h>

TEST CREATE_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST DESTROY_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_05(void) {
    binary_set_s test = create_binary_set(compare_string);

    destroy_binary_set(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_06(void) {
    binary_set_s test = create_binary_set(compare_string);

    insert_binary_set(&test, copy_string((BINARY_SET_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_binary_set(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST COPY_01(void) {
    binary_set_s test = create_binary_set(compare_int);
    binary_set_s copy = copy_binary_set(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST COPY_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s copy = copy_binary_set(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST COPY_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s copy = copy_binary_set(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST COPY_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s copy = copy_binary_set(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST COPY_05(void) {
    binary_set_s test = create_binary_set(compare_string);
    binary_set_s copy = copy_binary_set(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_string);
    destroy_binary_set(&copy, destroy_string);

    PASS();
}

TEST COPY_06(void) {
    binary_set_s test = create_binary_set(compare_string);

    insert_binary_set(&test, copy_string((BINARY_SET_DATA_TYPE) { .sub_two = TEST_STRING, }));

    binary_set_s copy = copy_binary_set(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_string);
    destroy_binary_set(&copy, destroy_string);

    PASS();
}

TEST IS_EMPTY_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    ASSERTm("[ERROR] Expected set to be empty.", is_empty_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected set to be full.", is_full_binary_set(&test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST FOREACH_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST FOREACH_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    const BINARY_SET_DATA_TYPE element = (BINARY_SET_DATA_TYPE) { .sub_one = 42 + increment, };
    ASSERTm("[ERROR] Expected value to be incremented.", contains_binary_set(&test, element));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST FOREACH_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = (BINARY_SET_DATA_TYPE) { .sub_one = i + increment, };
        ASSERTm("[ERROR] Expected value to be incremented.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST FOREACH_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = (BINARY_SET_DATA_TYPE) { .sub_one = i + increment, };
        ASSERTm("[ERROR] Expected value to be incremented.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    struct compare cmp = { .function = compare_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    struct compare cmp = { .function = compare_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    ASSERT_EQm("[ERROR] Expected sorted elements to be equal.", 42, test.elements[0].sub_one);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    for (size_t i = 0; i < test.size; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted elements to be equal.", (int)(i), test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    for (size_t i = 0; i < test.size; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted elements to be equal.", (int)(i), test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    struct compare cmp = { .function = compare_reverse_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_06(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    struct compare cmp = { .function = compare_reverse_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    ASSERT_EQm("[ERROR] Expected sorted elements to be equal.", 42, test.elements[0].sub_one);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_07(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_reverse_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    for (int i = 0; i < (int)(test.size); ++i) {
        const int expected = (int)(test.size) - 1 - i;
        ASSERT_EQm("[ERROR] Expected sorted elements to be equal.", expected, test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST MAP_08(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    struct compare cmp = { .function = compare_reverse_int_generic, };
    map_binary_set(&test, sort_int, &cmp);

    for (int i = 0; i < (int)(test.size); ++i) {
        const int expected = (int)(test.size) - 1 - i;
        ASSERT_EQm("[ERROR] Expected sorted elements to be equal.", expected, test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INSERT_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INSERT_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INSERT_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST REMOVE_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERT_EQm("[ERROR] Expected removed element to be valid.", 42, remove_binary_set(&test, element).sub_one);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST REMOVE_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERT_EQm("[ERROR] Expected removed element to be valid.", i, remove_binary_set(&test, element).sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST REMOVE_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERT_EQm("[ERROR] Expected removed element to be valid.", i, remove_binary_set(&test, element).sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST UNION_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    binary_set_s test = union_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST UNION_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s test = union_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 1, test.size);

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST UNION_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BINARY_SET_SIZE - 1, test.size);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST UNION_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BINARY_SET_SIZE, test.size);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST UNION_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE - 1) >> 1; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BINARY_SET_SIZE - 1, test.size);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST UNION_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE) >> 1; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BINARY_SET_SIZE, test.size);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 1, test.size);

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BINARY_SET_SIZE - 1, test.size);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BINARY_SET_SIZE, test.size);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE - 1) >> 1; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE) >> 1; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < 2 * ((BINARY_SET_SIZE - 1) / 3); ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = ((BINARY_SET_SIZE - 1) / 3); i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    for (int i = ((BINARY_SET_SIZE - 1) / 3); i < 2 * ((BINARY_SET_SIZE - 1) / 3); ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < 2 * ((BINARY_SET_SIZE) / 3); ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = ((BINARY_SET_SIZE) / 3); i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(&one, &two, copy_int);

    for (int i = ((BINARY_SET_SIZE) / 3); i < 2 * ((BINARY_SET_SIZE) / 3); ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    binary_set_s test = subtract_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s test = subtract_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(&one, &two, copy_int);

    for (int i = (BINARY_SET_SIZE - 1) >> 1; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to NOT contain element.", !contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(&one, &two, copy_int);

    for (int i = (BINARY_SET_SIZE) >> 1; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_binary_set(&test, element));
    }

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to NOT contain element.", !contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE - 1) >> 1; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected elements to be contained.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE) >> 1; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected elements to be contained.", contains_binary_set(&test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE - 1) >> 1; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };

    if (!contains_binary_set(&one, element)) {
        insert_binary_set(&one, element);
    }

    if (!contains_binary_set(&two, element)) {
        insert_binary_set(&two, element);
    }

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    ASSERT_FALSEm("[ERROR] Expected elements to be contained.", contains_binary_set(&test, element));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE) >> 1; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };

    if (!contains_binary_set(&one, element)) {
        insert_binary_set(&one, element);
    }

    if (!contains_binary_set(&two, element)) {
        insert_binary_set(&two, element);
    }

    binary_set_s test = exclude_binary_set(&one, &two, copy_int);

    ASSERT_FALSEm("[ERROR] Expected elements to be contained.", contains_binary_set(&test, element));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IS_SUBSET_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 2, });

    ASSERT_FALSEm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 1, });

    ASSERT_FALSEm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 2, });

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 1, });

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 2, });

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 1, });

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 2, });

    ASSERTm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = BINARY_SET_SIZE - 1, });

    ASSERTm("[ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE - 1) >> 1; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE) >> 1; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE - 1) >> 1; i < BINARY_SET_SIZE - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (BINARY_SET_SIZE) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (BINARY_SET_SIZE) >> 1; i < BINARY_SET_SIZE; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(&one, &two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

SUITE (binary_set_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01); RUN_TEST(DESTROY_02); RUN_TEST(DESTROY_03); RUN_TEST(DESTROY_04);
    RUN_TEST(DESTROY_05); RUN_TEST(DESTROY_06);
    // copy
    RUN_TEST(COPY_01); RUN_TEST(COPY_02); RUN_TEST(COPY_03); RUN_TEST(COPY_04);
    RUN_TEST(COPY_05); RUN_TEST(COPY_06);
    // is empty
    RUN_TEST(IS_EMPTY_01); RUN_TEST(IS_EMPTY_02); RUN_TEST(IS_EMPTY_03); RUN_TEST(IS_EMPTY_04);
    // is full
    RUN_TEST(IS_FULL_01); RUN_TEST(IS_FULL_02); RUN_TEST(IS_FULL_03); RUN_TEST(IS_FULL_04);
    // foreach
    RUN_TEST(FOREACH_01); RUN_TEST(FOREACH_02); RUN_TEST(FOREACH_03); RUN_TEST(FOREACH_04);
    // map
    RUN_TEST(MAP_01); RUN_TEST(MAP_02); RUN_TEST(MAP_03); RUN_TEST(MAP_04);
    RUN_TEST(MAP_05); RUN_TEST(MAP_06); RUN_TEST(MAP_07); RUN_TEST(MAP_08);
    // insert
    RUN_TEST(INSERT_01); RUN_TEST(INSERT_02); RUN_TEST(INSERT_03);
    // remove
    RUN_TEST(REMOVE_01); RUN_TEST(REMOVE_02); RUN_TEST(REMOVE_03);
    // union
    RUN_TEST(UNION_01); RUN_TEST(UNION_02); RUN_TEST(UNION_03); RUN_TEST(UNION_04);
    RUN_TEST(UNION_05); RUN_TEST(UNION_06);
    // intersect
    RUN_TEST(INTERSECT_01); RUN_TEST(INTERSECT_02); RUN_TEST(INTERSECT_03); RUN_TEST(INTERSECT_04);
    RUN_TEST(INTERSECT_05); RUN_TEST(INTERSECT_06); RUN_TEST(INTERSECT_07); RUN_TEST(INTERSECT_08);
    // subtract
    RUN_TEST(SUBTRACT_01); RUN_TEST(SUBTRACT_02); RUN_TEST(SUBTRACT_03); RUN_TEST(SUBTRACT_04);
    RUN_TEST(SUBTRACT_05); RUN_TEST(SUBTRACT_06);
    // exclude
    RUN_TEST(EXCLUDE_01); RUN_TEST(EXCLUDE_02); RUN_TEST(EXCLUDE_03); RUN_TEST(EXCLUDE_04);
    RUN_TEST(EXCLUDE_05); RUN_TEST(EXCLUDE_06); RUN_TEST(EXCLUDE_07); RUN_TEST(EXCLUDE_08);
    // is subset
    RUN_TEST(IS_SUBSET_01); RUN_TEST(IS_SUBSET_02); RUN_TEST(IS_SUBSET_03); RUN_TEST(IS_SUBSET_04);
    RUN_TEST(IS_SUBSET_05); RUN_TEST(IS_SUBSET_06); RUN_TEST(IS_SUBSET_07); RUN_TEST(IS_SUBSET_08);
    // is proper subset
    RUN_TEST(IS_PROPER_SUBSET_01); RUN_TEST(IS_PROPER_SUBSET_02); RUN_TEST(IS_PROPER_SUBSET_03); RUN_TEST(IS_PROPER_SUBSET_04);
    RUN_TEST(IS_PROPER_SUBSET_05); RUN_TEST(IS_PROPER_SUBSET_06); RUN_TEST(IS_PROPER_SUBSET_07); RUN_TEST(IS_PROPER_SUBSET_08);
    // is disjoint
    RUN_TEST(IS_DISJOINT_01); RUN_TEST(IS_DISJOINT_02); RUN_TEST(IS_DISJOINT_03); RUN_TEST(IS_DISJOINT_04);
    RUN_TEST(IS_DISJOINT_05); RUN_TEST(IS_DISJOINT_06); RUN_TEST(IS_DISJOINT_07); RUN_TEST(IS_DISJOINT_08);
}
