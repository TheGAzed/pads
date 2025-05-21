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

TEST IRBS_MAP_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    map_binary_set(&test, sort_int, compare_int_generic);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    map_binary_set(&test, sort_int, compare_int_generic);

    ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", 42, test.elements[0].sub_one);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    map_binary_set(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", (int)(i), test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    map_binary_set(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", (int)(i), test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_05(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    map_binary_set(&test, sort_int, compare_int_generic);

    for (size_t i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", (int)(i), test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_06(void) {
    binary_set_s test = create_binary_set(compare_int);

    map_binary_set(&test, sort_int, compare_reverse_int_generic);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_07(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    map_binary_set(&test, sort_int, compare_reverse_int_generic);

    ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", 42, test.elements[0].sub_one);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_08(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    map_binary_set(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < test.size; ++i) {
        const int expected = (int)(test.size) - 1 - (int)i;
        ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", expected, test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_09(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    map_binary_set(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < test.size; ++i) {
        const int expected = (int)(test.size) - 1 - (int)i;
        ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", expected, test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_MAP_10(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    map_binary_set(&test, sort_int, compare_reverse_int_generic);

    for (size_t i = 0; i < test.size; ++i) {
        const int expected = (int)(test.size) - 1 - (int)i;
        ASSERT_EQm("[IRBS-ERROR] Expected sorted elements to be equal.", expected, test.elements[i].sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INSERT_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INSERT_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INSERT_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INSERT_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_REMOVE_01(void) {
    binary_set_s test = create_binary_set(compare_int);

    insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERT_EQm("[IRBS-ERROR] Expected removed element to be valid.", 42, remove_binary_set(&test, element).sub_one);

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_REMOVE_02(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERT_EQm("[IRBS-ERROR] Expected removed element to be valid.", i, remove_binary_set(&test, element).sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_REMOVE_03(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERT_EQm("[IRBS-ERROR] Expected removed element to be valid.", i, remove_binary_set(&test, element).sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_REMOVE_04(void) {
    binary_set_s test = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&test, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERT_EQm("[IRBS-ERROR] Expected removed element to be valid.", i, remove_binary_set(&test, element).sub_one);
    }

    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 1, test.size);

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK - 1, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK + 1, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK - 1) >> 1; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK - 1, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK) >> 1; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_UNION_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK + 1) >> 1; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = union_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK + 1, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 1, test.size);

    const BINARY_SET_DATA_TYPE element = { .sub_one = 42, };
    ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK - 1, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", REALLOC_BINARY_SET_CHUNK + 1, test.size);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK - 1) >> 1; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK) >> 1; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK + 1) >> 1; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_09(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < 2 * ((REALLOC_BINARY_SET_CHUNK - 1) / 3); ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = ((REALLOC_BINARY_SET_CHUNK - 1) / 3); i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    for (int i = ((REALLOC_BINARY_SET_CHUNK - 1) / 3); i < 2 * ((REALLOC_BINARY_SET_CHUNK - 1) / 3); ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_10(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < 2 * ((REALLOC_BINARY_SET_CHUNK) / 3); ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = ((REALLOC_BINARY_SET_CHUNK) / 3); i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    for (int i = ((REALLOC_BINARY_SET_CHUNK) / 3); i < 2 * ((REALLOC_BINARY_SET_CHUNK) / 3); ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_INTERSECT_11(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < 2 * ((REALLOC_BINARY_SET_CHUNK + 1) / 3); ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = ((REALLOC_BINARY_SET_CHUNK + 1) / 3); i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = intersect_binary_set(one, two, copy_int);

    for (int i = ((REALLOC_BINARY_SET_CHUNK + 1) / 3); i < 2 * ((REALLOC_BINARY_SET_CHUNK + 1) / 3); ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    ASSERT_EQm("[IRBS-ERROR] Expected size to be correct.", 0, test.size);

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) >> 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    for (int i = (REALLOC_BINARY_SET_CHUNK - 1) >> 1; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) >> 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to NOT contain element.", !contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK) >> 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    for (int i = (REALLOC_BINARY_SET_CHUNK) >> 1; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK) >> 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to NOT contain element.", !contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_SUBTRACT_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) >> 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s test = subtract_binary_set(one, two, copy_int);

    for (int i = (REALLOC_BINARY_SET_CHUNK + 1) >> 1; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to contain element.", contains_binary_set(test, element));
    }

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) >> 1; ++i) {
        const BINARY_SET_DATA_TYPE element = { .sub_one = i, };
        ASSERTm("[IRBS-ERROR] Expected set to NOT contain element.", !contains_binary_set(test, element));
    }

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);
    destroy_binary_set(&test, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 2, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 1, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_09(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 2, });

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_10(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 1, });

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_SUBSET_11(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK, });

    ASSERTm("[IRBS-ERROR] Expected sets to be equal.", is_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 2, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 1, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_09(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1 - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 2, });

    ASSERTm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_10(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK - 1, });

    ASSERTm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_PROPER_SUBSET_11(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = REALLOC_BINARY_SET_CHUNK, });

    ASSERTm("[IRBS-ERROR] Expected sets to be properly equal.", is_proper_subset_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_01(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    ASSERTm("[IRBS-ERROR] Expected sets to be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_02(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_03(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_04(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_05(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_06(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK - 1) >> 1; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[IRBS-ERROR] Expected sets to be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_07(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK) >> 1; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[IRBS-ERROR] Expected sets to be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_08(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK + 1) >> 1; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[IRBS-ERROR] Expected sets to be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_09(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK - 1) >> 1; i < REALLOC_BINARY_SET_CHUNK - 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_10(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK) >> 1; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

    PASS();
}

TEST IRBS_IS_DISJOINT_11(void) {
    binary_set_s one = create_binary_set(compare_int);
    binary_set_s two = create_binary_set(compare_int);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) >> 1; ++i) {
        insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = (REALLOC_BINARY_SET_CHUNK + 1) >> 1; i < REALLOC_BINARY_SET_CHUNK + 1; ++i) {
        insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    insert_binary_set(&one, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });
    insert_binary_set(&two, (BINARY_SET_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRBS-ERROR] Expected sets to not be disjoint.", is_disjoint_binary_set(one, two));

    destroy_binary_set(&one, destroy_int);
    destroy_binary_set(&two, destroy_int);

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
    // map
    RUN_TEST(IRBS_MAP_01); RUN_TEST(IRBS_MAP_02); RUN_TEST(IRBS_MAP_03); RUN_TEST(IRBS_MAP_04);
    RUN_TEST(IRBS_MAP_05); RUN_TEST(IRBS_MAP_06); RUN_TEST(IRBS_MAP_07); RUN_TEST(IRBS_MAP_08);
    RUN_TEST(IRBS_MAP_09); RUN_TEST(IRBS_MAP_10);
    // insert
    RUN_TEST(IRBS_INSERT_01); RUN_TEST(IRBS_INSERT_02); RUN_TEST(IRBS_INSERT_03); RUN_TEST(IRBS_INSERT_04);
    // remove
    RUN_TEST(IRBS_REMOVE_01); RUN_TEST(IRBS_REMOVE_02); RUN_TEST(IRBS_REMOVE_03); RUN_TEST(IRBS_REMOVE_04);
    // union
    RUN_TEST(IRBS_UNION_01); RUN_TEST(IRBS_UNION_02); RUN_TEST(IRBS_UNION_03); RUN_TEST(IRBS_UNION_04);
    RUN_TEST(IRBS_UNION_05); RUN_TEST(IRBS_UNION_06); RUN_TEST(IRBS_UNION_07); RUN_TEST(IRBS_UNION_08);
    // intersect
    RUN_TEST(IRBS_INTERSECT_01); RUN_TEST(IRBS_INTERSECT_02); RUN_TEST(IRBS_INTERSECT_03); RUN_TEST(IRBS_INTERSECT_04);
    RUN_TEST(IRBS_INTERSECT_05); RUN_TEST(IRBS_INTERSECT_06); RUN_TEST(IRBS_INTERSECT_07); RUN_TEST(IRBS_INTERSECT_08);
    RUN_TEST(IRBS_INTERSECT_09); RUN_TEST(IRBS_INTERSECT_10); RUN_TEST(IRBS_INTERSECT_11);
    // subtract
    RUN_TEST(IRBS_SUBTRACT_01); RUN_TEST(IRBS_SUBTRACT_02); RUN_TEST(IRBS_SUBTRACT_03); RUN_TEST(IRBS_SUBTRACT_04);
    RUN_TEST(IRBS_SUBTRACT_05); RUN_TEST(IRBS_SUBTRACT_06); RUN_TEST(IRBS_SUBTRACT_07); RUN_TEST(IRBS_SUBTRACT_08);
    // is subset
    RUN_TEST(IRBS_IS_SUBSET_01); RUN_TEST(IRBS_IS_SUBSET_02); RUN_TEST(IRBS_IS_SUBSET_03); RUN_TEST(IRBS_IS_SUBSET_04);
    RUN_TEST(IRBS_IS_SUBSET_05); RUN_TEST(IRBS_IS_SUBSET_06); RUN_TEST(IRBS_IS_SUBSET_07); RUN_TEST(IRBS_IS_SUBSET_08);
    RUN_TEST(IRBS_IS_SUBSET_09); RUN_TEST(IRBS_IS_SUBSET_10); RUN_TEST(IRBS_IS_SUBSET_11);
    // is proper subset
    RUN_TEST(IRBS_IS_PROPER_SUBSET_01); RUN_TEST(IRBS_IS_PROPER_SUBSET_02); RUN_TEST(IRBS_IS_PROPER_SUBSET_03); RUN_TEST(IRBS_IS_PROPER_SUBSET_04);
    RUN_TEST(IRBS_IS_PROPER_SUBSET_05); RUN_TEST(IRBS_IS_PROPER_SUBSET_06); RUN_TEST(IRBS_IS_PROPER_SUBSET_07); RUN_TEST(IRBS_IS_PROPER_SUBSET_08);
    RUN_TEST(IRBS_IS_PROPER_SUBSET_09); RUN_TEST(IRBS_IS_PROPER_SUBSET_10); RUN_TEST(IRBS_IS_PROPER_SUBSET_11);
    // is disjoint
    RUN_TEST(IRBS_IS_DISJOINT_01); RUN_TEST(IRBS_IS_DISJOINT_02); RUN_TEST(IRBS_IS_DISJOINT_03); RUN_TEST(IRBS_IS_DISJOINT_04);
    RUN_TEST(IRBS_IS_DISJOINT_05); RUN_TEST(IRBS_IS_DISJOINT_06); RUN_TEST(IRBS_IS_DISJOINT_07); RUN_TEST(IRBS_IS_DISJOINT_08);
    RUN_TEST(IRBS_IS_DISJOINT_09); RUN_TEST(IRBS_IS_DISJOINT_10); RUN_TEST(IRBS_IS_DISJOINT_11);
}
