#include "binary_set_test.h"

#include <functions.h>

#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET
#define REALLOC_BINARY_SET_CHUNK (1 << 4)
#define BINARY_SET_DATA_TYPE DATA_TYPE
#include <set/binary_set/binary_set.h>

TEST IRBS_CREATE_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_DESTROY_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST IRBS_DESTROY_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST IRBS_DESTROY_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST IRBS_DESTROY_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST IRBS_DESTROY_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    destroy_binary_set(&test, destroy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST IRBS_DESTROY_06(void) {
    binary_set_s test = create_binary_set(compare_string);

    destroy_binary_set(&test, destroy_string);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST IRBS_DESTROY_07(void) {
    binary_set_s test = create_binary_set(compare_string);

    insert_binary_set(&test, copy_string((BINARY_SET_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_binary_set(&test, destroy_string);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    PASS();
}

TEST IRBS_CLEAR_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    clear_binary_set(&test, destroy_int);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_CLEAR_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    clear_binary_set(&test, destroy_int);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_CLEAR_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    clear_binary_set(&test, destroy_int);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_CLEAR_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    clear_binary_set(&test, destroy_int);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_CLEAR_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    clear_binary_set(&test, destroy_int);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_CLEAR_06(void) {
    binary_set_s test = create_binary_set(compare_string);

    clear_binary_set(&test, destroy_string);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_string);

    PASS();
}

TEST IRBS_CLEAR_07(void) {
    binary_set_s test = create_binary_set(compare_string);

    insert_binary_set(&test, copy_string((BINARY_SET_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_binary_set(&test, destroy_string);

    ASSERT_NEQm("[IRBS-ERROR] Expected compare to not be NULL.", NULL, test.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, test.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be zero.", 0, test.size);

    destroy_binary_set(&test, destroy_string);

    PASS();
}

TEST IRBS_COPY_01(void) {
    binary_set_s test = create_binary_set(compare_int);
    binary_set_s copy = copy_binary_set(test, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST IRBS_COPY_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s copy = copy_binary_set(test, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_NEQm("[IRBS-ERROR] Expected elements to not be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST IRBS_COPY_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s copy = copy_binary_set(test, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_NEQm("[IRBS-ERROR] Expected elements to not be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST IRBS_COPY_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s copy = copy_binary_set(test, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_NEQm("[IRBS-ERROR] Expected elements to not be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST IRBS_COPY_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s copy = copy_binary_set(test, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_NEQm("[IRBS-ERROR] Expected elements to not be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_int);
    destroy_binary_set(&copy, destroy_int);

    PASS();
}

TEST IRBS_COPY_06(void) {
    binary_set_s test = create_binary_set(compare_string);
    binary_set_s copy = copy_binary_set(test, copy_string);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_EQm("[IRBS-ERROR] Expected elements to not be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_string);
    destroy_binary_set(&copy, destroy_string);

    PASS();
}

TEST IRBS_COPY_07(void) {
    binary_set_s test = create_binary_set(compare_string);

    insert_binary_set(&test, copy_string((BINARY_SET_DATA_TYPE) { .sub_two = TEST_STRING, }));

    binary_set_s copy = copy_binary_set(test, copy_string);

    ASSERT_EQm("[IRBS-ERROR] Expected compare to be equal.", test.compare, copy.compare);
    ASSERT_NEQm("[IRBS-ERROR] Expected elements to not be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRBS-ERROR] Expected size to be equal.", copy.size, test.size);

    destroy_binary_set(&test, destroy_string);
    destroy_binary_set(&copy, destroy_string);

    PASS();
}

TEST IRBS_IS_EMPTY_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    ASSERTm("[IRBS-ERROR] Expected set to be empty.", is_empty_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_EMPTY_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be empty.", is_empty_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_EMPTY_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be empty.", is_empty_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_EMPTY_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be empty.", is_empty_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_EMPTY_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be empty.", is_empty_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_FULL_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be full.", is_full_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_FULL_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be full.", is_full_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_FULL_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be full.", is_full_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_FULL_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be full.", is_full_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_FULL_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected set to not be full.", is_full_binary_set(test));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_FOREACH_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_FOREACH_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    const BINARY_SET_DATA_TYPE element = (BINARY_SET_DATA_TYPE) { .sub_one = 42 + increment, };
    ASSERTm("[IRBS-ERROR] Expected value to be incremented.", contains_binary_set(test, element));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_FOREACH_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = (BINARY_SET_DATA_TYPE) { .sub_one = i + increment, };
        ASSERTm("[IRBS-ERROR] Expected value to be incremented.", contains_binary_set(test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_FOREACH_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        const BINARY_SET_DATA_TYPE element = (BINARY_SET_DATA_TYPE) { .sub_one = i + increment, };
        ASSERTm("[IRBS-ERROR] Expected value to be incremented.", contains_binary_set(test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_FOREACH_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    int increment = 5;
    foreach_binary_set(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        const BINARY_SET_DATA_TYPE element = (BINARY_SET_DATA_TYPE) { .sub_one = i + increment, };
        ASSERTm("[IRBS-ERROR] Expected value to be incremented.", contains_binary_set(test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

SUITE (infinite_realloc_binary_set_test) {
    // create
    RUN_TEST(IRBS_CREATE_01);
    // destroy
    RUN_TEST(IRBS_DESTROY_01); RUN_TEST(IRBS_DESTROY_02); RUN_TEST(IRBS_DESTROY_03); RUN_TEST(IRBS_DESTROY_04);
    RUN_TEST(IRBS_DESTROY_05); RUN_TEST(IRBS_DESTROY_06); RUN_TEST(IRBS_DESTROY_07);
    // clear
    RUN_TEST(IRBS_CLEAR_01); RUN_TEST(IRBS_CLEAR_02); RUN_TEST(IRBS_CLEAR_03); RUN_TEST(IRBS_CLEAR_04);
    RUN_TEST(IRBS_CLEAR_05); RUN_TEST(IRBS_CLEAR_06); RUN_TEST(IRBS_CLEAR_07);
    // copy
    RUN_TEST(IRBS_COPY_01); RUN_TEST(IRBS_COPY_02); RUN_TEST(IRBS_COPY_03); RUN_TEST(IRBS_COPY_04);
    RUN_TEST(IRBS_COPY_05); RUN_TEST(IRBS_COPY_06); RUN_TEST(IRBS_COPY_07);
    // is empty
    RUN_TEST(IRBS_IS_EMPTY_01); RUN_TEST(IRBS_IS_EMPTY_02); RUN_TEST(IRBS_IS_EMPTY_03); RUN_TEST(IRBS_IS_EMPTY_04);
    RUN_TEST(IRBS_IS_EMPTY_05);
    // is full
    RUN_TEST(IRBS_IS_FULL_01); RUN_TEST(IRBS_IS_FULL_02); RUN_TEST(IRBS_IS_FULL_03); RUN_TEST(IRBS_IS_FULL_04);
    RUN_TEST(IRBS_IS_FULL_05);
    // foreach
    RUN_TEST(IRBS_FOREACH_01); RUN_TEST(IRBS_FOREACH_02); RUN_TEST(IRBS_FOREACH_03); RUN_TEST(IRBS_FOREACH_04);
    RUN_TEST(IRBS_FOREACH_05);
}
