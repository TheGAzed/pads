#include <suits.h>

#define HASH_SET_SIZE (1 << 4)
#define HASH_SET_DATA_TYPE DATA_TYPE
#include <set/hash_set.h>

TEST CREATE_01(void) {
    hash_set_s test = create_hash_set(hash_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST DESTROY_01(void) {
    hash_set_s test = create_hash_set(hash_int);

    destroy_hash_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.hash);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_02(void) {
    hash_set_s test = create_hash_set(hash_int);

    insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    destroy_hash_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.hash);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_03(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    destroy_hash_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.hash);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_04(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    destroy_hash_set(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.hash);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_05(void) {
    hash_set_s test = create_hash_set(hash_string);

    destroy_hash_set(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.hash);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_06(void) {
    hash_set_s test = create_hash_set(hash_string);

    insert_hash_set(&test, copy_string((HASH_SET_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_hash_set(&test, destroy_string);

    ASSERT_EQm("[ERROR] Expected compare to be NULL.", NULL, test.hash);
    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST COPY_01(void) {
    hash_set_s test = create_hash_set(hash_int);
    hash_set_s copy = copy_hash_set(test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.hash, copy.hash);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_hash_set(&test, destroy_int);
    destroy_hash_set(&copy, destroy_int);

    PASS();
}

TEST COPY_02(void) {
    hash_set_s test = create_hash_set(hash_int);

    insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    hash_set_s copy = copy_hash_set(test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.hash, copy.hash);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_hash_set(&test, destroy_int);
    destroy_hash_set(&copy, destroy_int);

    PASS();
}

TEST COPY_03(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s copy = copy_hash_set(test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.hash, copy.hash);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_hash_set(&test, destroy_int);
    destroy_hash_set(&copy, destroy_int);

    PASS();
}

TEST COPY_04(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s copy = copy_hash_set(test, copy_int);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.hash, copy.hash);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_hash_set(&test, destroy_int);
    destroy_hash_set(&copy, destroy_int);

    PASS();
}

TEST COPY_05(void) {
    hash_set_s test = create_hash_set(hash_string);
    hash_set_s copy = copy_hash_set(test, copy_string);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.hash, copy.hash);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_hash_set(&test, destroy_string);
    destroy_hash_set(&copy, destroy_string);

    PASS();
}

TEST COPY_06(void) {
    hash_set_s test = create_hash_set(hash_string);

    insert_hash_set(&test, copy_string((HASH_SET_DATA_TYPE) { .sub_two = TEST_STRING, }));

    hash_set_s copy = copy_hash_set(test, copy_string);

    ASSERT_EQm("[ERROR] Expected compare to be equal.", test.hash, copy.hash);
    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_hash_set(&test, destroy_string);
    destroy_hash_set(&copy, destroy_string);

    PASS();
}

TEST IS_EMPTY_01(void) {
    hash_set_s test = create_hash_set(hash_int);

    ASSERTm("[ERROR] Expected set to be empty.", is_empty_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_02(void) {
    hash_set_s test = create_hash_set(hash_int);

    insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_03(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_04(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_01(void) {
    hash_set_s test = create_hash_set(hash_int);

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_02(void) {
    hash_set_s test = create_hash_set(hash_int);

    insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_03(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_FULL_04(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected set to be full.", is_full_hash_set(test));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INSERT_01(void) {
    hash_set_s test = create_hash_set(hash_int);

    insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    const HASH_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INSERT_02(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INSERT_03(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST REMOVE_01(void) {
    hash_set_s test = create_hash_set(hash_int);

    insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    const HASH_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERT_EQm("[ERROR] Expected removed element to be valid.", 42, remove_hash_set(&test, element).sub_one);

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST REMOVE_02(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERT_EQm("[ERROR] Expected removed element to be valid.", i, remove_hash_set(&test, element).sub_one);
    }

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST REMOVE_03(void) {
    hash_set_s test = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&test, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERT_EQm("[ERROR] Expected removed element to be valid.", i, remove_hash_set(&test, element).sub_one);
    }

    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST UNION_01(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    hash_set_s test = union_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST UNION_02(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    hash_set_s test = union_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 1, test.size);

    const HASH_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST UNION_03(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = union_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", HASH_SET_SIZE - 1, test.size);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST UNION_04(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = union_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", HASH_SET_SIZE, test.size);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST UNION_05(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE - 1) >> 1; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = union_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", HASH_SET_SIZE - 1, test.size);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST UNION_06(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE) >> 1; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = union_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", HASH_SET_SIZE, test.size);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_01(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_02(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 1, test.size);

    const HASH_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_03(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", HASH_SET_SIZE - 1, test.size);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_04(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", HASH_SET_SIZE, test.size);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_05(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE - 1) >> 1; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_06(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE) >> 1; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_07(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < 2 * ((HASH_SET_SIZE - 1) / 3); ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = ((HASH_SET_SIZE - 1) / 3); i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    for (int i = ((HASH_SET_SIZE - 1) / 3); i < 2 * ((HASH_SET_SIZE - 1) / 3); ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST INTERSECT_08(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < 2 * ((HASH_SET_SIZE) / 3); ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = ((HASH_SET_SIZE) / 3); i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = intersect_hash_set(one, two, copy_int);

    for (int i = ((HASH_SET_SIZE) / 3); i < 2 * ((HASH_SET_SIZE) / 3); ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_01(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    hash_set_s test = subtract_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_02(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    hash_set_s test = subtract_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_03(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = subtract_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_04(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = subtract_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_05(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = subtract_hash_set(one, two, copy_int);

    for (int i = (HASH_SET_SIZE - 1) >> 1; i < HASH_SET_SIZE - 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to NOT contain element.", !contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST SUBTRACT_06(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = subtract_hash_set(one, two, copy_int);

    for (int i = (HASH_SET_SIZE) >> 1; i < HASH_SET_SIZE; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to contain element.", contains_hash_set(test, element));
    }

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected set to NOT contain element.", !contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_01(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_02(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_03(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_04(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_05(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE - 1) >> 1; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected elements to be contained.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_06(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE) >> 1; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        const HASH_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[ERROR] Expected elements to be contained.", contains_hash_set(test, element));
    }

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_07(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE - 1) >> 1; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    const HASH_SET_DATA_TYPE element = { .sub_one = 42, };

    if (!contains_hash_set(one, element)) {
        insert_hash_set(&one, element);
    }

    if (!contains_hash_set(two, element)) {
        insert_hash_set(&two, element);
    }

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    ASSERT_FALSEm("[ERROR] Expected elements to be contained.", contains_hash_set(test, element));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST EXCLUDE_08(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE) >> 1; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    const HASH_SET_DATA_TYPE element = { .sub_one = 42, };

    if (!contains_hash_set(one, element)) {
        insert_hash_set(&one, element);
    }

    if (!contains_hash_set(two, element)) {
        insert_hash_set(&two, element);
    }

    hash_set_s test = exclude_hash_set(one, two, copy_int);

    ASSERT_FALSEm("[ERROR] Expected elements to be contained.", contains_hash_set(test, element));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);
    destroy_hash_set(&test, destroy_int);

    PASS();
}

TEST IS_SUBSET_01(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_02(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_03(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_04(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_05(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1 - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 2, });

    ASSERT_FALSEm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_06(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 1, });

    ASSERT_FALSEm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_07(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1 - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 2, });

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_SUBSET_08(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 1, });

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_01(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_02(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_03(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_04(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_05(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1 - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 2, });

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_06(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 1, });

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_07(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1 - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 2, });

    ASSERTm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_PROPER_SUBSET_08(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = HASH_SET_SIZE - 1, });

    ASSERTm("[ERROR] Expected sets to be properly equal.", is_proper_subset_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_01(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_02(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_03(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_04(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_05(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE - 1) >> 1; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_06(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE) >> 1; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_07(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE - 1) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE - 1) >> 1; i < HASH_SET_SIZE - 1; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

TEST IS_DISJOINT_08(void) {
    hash_set_s one = create_hash_set(hash_int);
    hash_set_s two = create_hash_set(hash_int);

    for (int i = 0; i < (HASH_SET_SIZE) >> 1; ++i) {
        insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (HASH_SET_SIZE) >> 1; i < HASH_SET_SIZE; ++i) {
        insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = i, });
    }

    insert_hash_set(&one, (HASH_SET_DATA_TYPE) { .sub_one = 42, });
    insert_hash_set(&two, (HASH_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_hash_set(one, two));

    destroy_hash_set(&one, destroy_int);
    destroy_hash_set(&two, destroy_int);

    PASS();
}

SUITE (hash_set_test) {
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
