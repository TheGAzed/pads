#include <suits.h>

#define BITWISE_SET_SIZE (1 << 4)
#include <set/bitwise_set.h>

TEST CREATE_01(void) {
    bitwise_set_s test = create_bitwise_set();

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    destroy_bitwise_set(&test);

    PASS();
}

TEST DESTROY_01(void) {
    bitwise_set_s test = create_bitwise_set();

    destroy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_02(void) {
    bitwise_set_s test = create_bitwise_set();

    insert_bitwise_set(&test, 0);

    destroy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_03(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&test, i);
    }

    destroy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST DESTROY_04(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&test, i);
    }

    destroy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST COPY_01(void) {
    bitwise_set_s test = create_bitwise_set();
    bitwise_set_s copy = copy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_bitwise_set(&test);
    destroy_bitwise_set(&copy);

    PASS();
}

TEST COPY_02(void) {
    bitwise_set_s test = create_bitwise_set();

    insert_bitwise_set(&test, 0);

    bitwise_set_s copy = copy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_bitwise_set(&test);
    destroy_bitwise_set(&copy);

    PASS();
}

TEST COPY_03(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&test, i);
    }

    bitwise_set_s copy = copy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_bitwise_set(&test);
    destroy_bitwise_set(&copy);

    PASS();
}

TEST COPY_04(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&test, i);
    }

    bitwise_set_s copy = copy_bitwise_set(&test);

    ASSERT_EQm("[ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_bitwise_set(&test);
    destroy_bitwise_set(&copy);

    PASS();
}

TEST IS_EMPTY_01(void) {
    bitwise_set_s test = create_bitwise_set();

    ASSERTm("[FABS-ERROR] Expected set to be empty.", is_empty_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_EMPTY_02(void) {
    bitwise_set_s test = create_bitwise_set();

    insert_bitwise_set(&test, 0);

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_EMPTY_03(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&test, i);
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_EMPTY_04(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&test, i);
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be empty.", is_empty_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_FULL_01(void) {
    bitwise_set_s test = create_bitwise_set();

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_FULL_02(void) {
    bitwise_set_s test = create_bitwise_set();

    insert_bitwise_set(&test, 0);

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_FULL_03(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&test, i);
    }

    ASSERT_FALSEm("[ERROR] Expected set to not be full.", is_full_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_FULL_04(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&test, i);
    }

    ASSERTm("[ERROR] Expected set to be full.", is_full_bitwise_set(&test));

    destroy_bitwise_set(&test);

    PASS();
}

TEST INSERT_01(void) {
    bitwise_set_s test = create_bitwise_set();

    insert_bitwise_set(&test, 0);

    remove_bitwise_set(&test, 0);

    destroy_bitwise_set(&test);

    PASS();
}

TEST INSERT_02(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&test, i);
    }

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        remove_bitwise_set(&test, i);
    }

    destroy_bitwise_set(&test);

    PASS();
}

TEST INSERT_03(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&test, i);
    }

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        remove_bitwise_set(&test, i);
    }

    destroy_bitwise_set(&test);

    PASS();
}

TEST REMOVE_01(void) {
    bitwise_set_s test = create_bitwise_set();

    insert_bitwise_set(&test, 0);

    remove_bitwise_set(&test, 0);

    destroy_bitwise_set(&test);

    PASS();
}

TEST REMOVE_02(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&test, i);
    }

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        remove_bitwise_set(&test, i);
    }

    destroy_bitwise_set(&test);

    PASS();
}

TEST REMOVE_03(void) {
    bitwise_set_s test = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&test, i);
    }

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        remove_bitwise_set(&test, i);
    }

    destroy_bitwise_set(&test);

    PASS();
}

TEST UNION_01(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    bitwise_set_s test = union_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST UNION_02(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    insert_bitwise_set(&one, 0);
    insert_bitwise_set(&two, 0);

    bitwise_set_s test = union_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 1, test.size);

    ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, 0));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST UNION_03(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = union_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BITWISE_SET_SIZE - 1, test.size);

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST UNION_04(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = union_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BITWISE_SET_SIZE, test.size);

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST UNION_05(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE - 1) >> 1; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = union_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BITWISE_SET_SIZE - 1, test.size);

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST UNION_06(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE) >> 1; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = union_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BITWISE_SET_SIZE, test.size);

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_01(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_02(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    insert_bitwise_set(&one, 0);
    insert_bitwise_set(&two, 0);

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 1, test.size);

    ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, 0));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_03(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BITWISE_SET_SIZE - 1, test.size);

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_04(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", BITWISE_SET_SIZE, test.size);

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_05(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE - 1) >> 1; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_06(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE) >> 1; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_07(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < 2 * ((BITWISE_SET_SIZE - 1) / 3); ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = ((BITWISE_SET_SIZE - 1) / 3); i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    for (size_t i = ((BITWISE_SET_SIZE - 1) / 3); i < 2 * ((BITWISE_SET_SIZE - 1) / 3); ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST INTERSECT_08(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < 2 * ((BITWISE_SET_SIZE) / 3); ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = ((BITWISE_SET_SIZE) / 3); i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = intersect_bitwise_set(&one, &two);

    for (size_t i = ((BITWISE_SET_SIZE) / 3); i < 2 * ((BITWISE_SET_SIZE) / 3); ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST SUBTRACT_01(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    bitwise_set_s test = subtract_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST SUBTRACT_02(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    insert_bitwise_set(&one, 0);
    insert_bitwise_set(&two, 0);

    bitwise_set_s test = subtract_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST SUBTRACT_03(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = subtract_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST SUBTRACT_04(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = subtract_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST SUBTRACT_05(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = subtract_bitwise_set(&one, &two);

    for (size_t i = (BITWISE_SET_SIZE - 1) >> 1; i < BITWISE_SET_SIZE - 1; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        ASSERTm("[ERROR] Expected set to NOT contain element.", !contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST SUBTRACT_06(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = subtract_bitwise_set(&one, &two);

    for (size_t i = (BITWISE_SET_SIZE) >> 1; i < BITWISE_SET_SIZE; ++i) {
        ASSERTm("[ERROR] Expected set to contain element.", contains_bitwise_set(&test, i));
    }

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        ASSERTm("[ERROR] Expected set to NOT contain element.", !contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_01(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_02(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    insert_bitwise_set(&one, 0);
    insert_bitwise_set(&two, 0);

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_03(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_04(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    ASSERT_EQm("[ERROR] Expected size to be correct.", 0, test.size);

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_05(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE - 1) >> 1; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        ASSERTm("[ERROR] Expected elements to be contained.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_06(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE) >> 1; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&two, i);
    }

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        ASSERTm("[ERROR] Expected elements to be contained.", contains_bitwise_set(&test, i));
    }

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_07(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE - 1) >> 1; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    if (!contains_bitwise_set(&one, 0)) {
        insert_bitwise_set(&one, 0);
    }

    if (!contains_bitwise_set(&two, 0)) {
        insert_bitwise_set(&two, 0);
    }

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    ASSERT_FALSEm("[ERROR] Expected elements to be contained.", contains_bitwise_set(&test, 0));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST EXCLUDE_08(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE) >> 1; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&two, i);
    }

    if (!contains_bitwise_set(&one, 0)) {
        insert_bitwise_set(&one, 0);
    }

    if (!contains_bitwise_set(&two, 0)) {
        insert_bitwise_set(&two, 0);
    }

    bitwise_set_s test = exclude_bitwise_set(&one, &two);

    ASSERT_FALSEm("[ERROR] Expected elements to be contained.", contains_bitwise_set(&test, 0));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);
    destroy_bitwise_set(&test);

    PASS();
}

TEST IS_SUBSET_01(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_SUBSET_02(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    insert_bitwise_set(&one, 0);
    insert_bitwise_set(&two, 0);

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_SUBSET_03(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_SUBSET_04(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_SUBSET_05(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1 - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&two, BITWISE_SET_SIZE - 2);

    ASSERT_FALSEm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_SUBSET_06(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&two, BITWISE_SET_SIZE - 1);

    ASSERT_FALSEm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_SUBSET_07(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1 - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&one, BITWISE_SET_SIZE - 2);

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_SUBSET_08(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&one, BITWISE_SET_SIZE - 1);

    ASSERTm("[ERROR] Expected sets to be equal.", is_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_01(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_02(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    insert_bitwise_set(&one, 0);
    insert_bitwise_set(&two, 0);

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_03(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_04(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_05(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1 - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&two, BITWISE_SET_SIZE - 2);

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_06(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&two, BITWISE_SET_SIZE - 1);

    ASSERT_FALSEm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_07(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1 - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&one, BITWISE_SET_SIZE - 2);

    ASSERTm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_PROPER_SUBSET_08(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }
    insert_bitwise_set(&one, BITWISE_SET_SIZE - 1);

    ASSERTm("[ERROR] Expected sets to be properly equal.", is_proper_subset_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_01(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_02(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    insert_bitwise_set(&one, 0);
    insert_bitwise_set(&two, 0);

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_03(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_04(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&one, i);
        insert_bitwise_set(&two, i);
    }

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_05(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE - 1) >> 1; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_06(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE) >> 1; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&two, i);
    }

    ASSERTm("[ERROR] Expected sets to be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_07(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE - 1) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE - 1) >> 1; i < BITWISE_SET_SIZE - 1; ++i) {
        insert_bitwise_set(&two, i);
    }

    insert_bitwise_set(&two, 0);

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

TEST IS_DISJOINT_08(void) {
    bitwise_set_s one = create_bitwise_set();
    bitwise_set_s two = create_bitwise_set();

    for (size_t i = 0; i < (BITWISE_SET_SIZE) >> 1; ++i) {
        insert_bitwise_set(&one, i);
    }

    for (size_t i = (BITWISE_SET_SIZE) >> 1; i < BITWISE_SET_SIZE; ++i) {
        insert_bitwise_set(&two, i);
    }

    insert_bitwise_set(&two, 0);

    ASSERT_FALSEm("[ERROR] Expected sets to not be disjoint.", is_disjoint_bitwise_set(&one, &two));

    destroy_bitwise_set(&one);
    destroy_bitwise_set(&two);

    PASS();
}

SUITE (bitwise_set_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01); RUN_TEST(DESTROY_02); RUN_TEST(DESTROY_03); RUN_TEST(DESTROY_04);
    // copy
    RUN_TEST(COPY_01); RUN_TEST(COPY_02); RUN_TEST(COPY_03); RUN_TEST(COPY_04);
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
