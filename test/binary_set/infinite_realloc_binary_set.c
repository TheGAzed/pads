#include "binary_set_test.h"

#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET
#define REALLOC_BINARY_SET_CHUNK (1 << 4)
#include <binary_set.h>

/// Test if set is initialized properly when created
TEST IRBS_01(void) {
    binary_set_s set = create_binary_set(NULL);

    ASSERT_EQm("[IRBS-ERROR] expected set compare function pointer to be NULL.", NULL, set.compare);
    ASSERT_EQm("[IRBS-ERROR] expected set elements pointer to be NULL.", NULL, set.elements);
    ASSERT_EQm("[IRBS-ERROR] expected set size pointer to be NULL.", 0, set.size);

    destroy_binary_set(&set, NULL);
    PASS();
}

/// Tests if union of 0 to '(REALLOC_BINARY_SET_CHUNK - 1) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK - 1' to '(REALLOC_BINARY_SET_CHUNK - 1) * 3' will have elements
/// from 0 to '(REALLOC_BINARY_SET_CHUNK - 1) * 3'
TEST IRBS_02(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK - 1; i < (REALLOC_BINARY_SET_CHUNK - 1) * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s united = union_binary_set(set_one, set_two, NULL);
    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) * 3; ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(united, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&united, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if union of 0 to '(REALLOC_BINARY_SET_CHUNK) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK' to '(REALLOC_BINARY_SET_CHUNK) * 3' will have elements
/// from 0 to '(REALLOC_BINARY_SET_CHUNK) * 3'
TEST IRBS_03(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK; i < REALLOC_BINARY_SET_CHUNK * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s united = union_binary_set(set_one, set_two, NULL);
    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK * 3; ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(united, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&united, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if union of 0 to '(REALLOC_BINARY_SET_CHUNK + 1) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK + 1' to '(REALLOC_BINARY_SET_CHUNK + 1) * 3' will have elements
/// from 0 to '(REALLOC_BINARY_SET_CHUNK + 1) * 3'
TEST IRBS_04(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK + 1; i < (REALLOC_BINARY_SET_CHUNK + 1) * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s united = union_binary_set(set_one, set_two, NULL);
    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) * 3; ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(united, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&united, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if intersect of 0 to '(REALLOC_BINARY_SET_CHUNK - 1) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK - 1' to '(REALLOC_BINARY_SET_CHUNK - 1) * 3' will have elements
/// from 'REALLOC_BINARY_SET_CHUNK - 1' to '(REALLOC_BINARY_SET_CHUNK - 1) * 2'
TEST IRBS_05(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK - 1; i < (REALLOC_BINARY_SET_CHUNK - 1) * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s intersected = intersect_binary_set(set_one, set_two, NULL);
    for (int i = REALLOC_BINARY_SET_CHUNK - 1; i < (REALLOC_BINARY_SET_CHUNK - 1) * 2; ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(intersected, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&intersected, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if intersect of 0 to '(REALLOC_BINARY_SET_CHUNK) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK' to '(REALLOC_BINARY_SET_CHUNK) * 3' will have elements
/// from 'REALLOC_BINARY_SET_CHUNK' to '(REALLOC_BINARY_SET_CHUNK) * 2'
TEST IRBS_06(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK; i < REALLOC_BINARY_SET_CHUNK * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s intersected = intersect_binary_set(set_one, set_two, NULL);
    for (int i = REALLOC_BINARY_SET_CHUNK; i < (REALLOC_BINARY_SET_CHUNK) * 2; ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(intersected, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&intersected, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if intersect of 0 to '(REALLOC_BINARY_SET_CHUNK + 1) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK + 1' to '(REALLOC_BINARY_SET_CHUNK + 1) * 3' will have elements
/// from 'REALLOC_BINARY_SET_CHUNK + 1' to '(REALLOC_BINARY_SET_CHUNK + 1) * 2'
TEST IRBS_07(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK + 1; i < (REALLOC_BINARY_SET_CHUNK + 1) * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s intersected = intersect_binary_set(set_one, set_two, NULL);
    for (int i = REALLOC_BINARY_SET_CHUNK + 1; i < (REALLOC_BINARY_SET_CHUNK + 1) * 2; ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(intersected, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&intersected, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if subtract of 0 to '(REALLOC_BINARY_SET_CHUNK - 1) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK - 1' to '(REALLOC_BINARY_SET_CHUNK - 1) * 3' will have elements
/// from 0 to 'REALLOC_BINARY_SET_CHUNK - 1'
TEST IRBS_08(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1) * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK - 1; i < (REALLOC_BINARY_SET_CHUNK - 1) * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s subtract = subtract_binary_set(set_one, set_two, NULL);
    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK - 1); ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(subtract, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&subtract, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if subtract of 0 to '(REALLOC_BINARY_SET_CHUNK) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK' to '(REALLOC_BINARY_SET_CHUNK) * 3' will have elements
/// from 0 to 'REALLOC_BINARY_SET_CHUNK'
TEST IRBS_09(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK; i < REALLOC_BINARY_SET_CHUNK * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s subtract = subtract_binary_set(set_one, set_two, NULL);
    for (int i = 0; i < REALLOC_BINARY_SET_CHUNK; ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(subtract, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&subtract, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

/// Tests if subtract of 0 to '(REALLOC_BINARY_SET_CHUNK + 1) * 2' and
/// 'REALLOC_BINARY_SET_CHUNK + 1' to '(REALLOC_BINARY_SET_CHUNK + 1) * 3' will have elements
/// from 0 to 'REALLOC_BINARY_SET_CHUNK + 1'
TEST IRBS_10(void) {
    binary_set_s set_one = create_binary_set(NULL);
    binary_set_s set_two = create_binary_set(NULL);

    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1) * 2; ++i) {
        add_binary_set(&set_one, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = REALLOC_BINARY_SET_CHUNK + 1; i < (REALLOC_BINARY_SET_CHUNK + 1) * 3; ++i) {
        add_binary_set(&set_two, (BINARY_SET_DATA_TYPE) { .sub_one = i, });
    }

    binary_set_s subtract = subtract_binary_set(set_one, set_two, NULL);
    for (int i = 0; i < (REALLOC_BINARY_SET_CHUNK + 1); ++i) {
        ASSERTm("[IRBS-ERROR] expected set to contain i", contains_binary_set(subtract, (BINARY_SET_DATA_TYPE) { .sub_one = i, }));
    }

    destroy_binary_set(&subtract, NULL);
    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
    PASS();
}

SUITE (infinite_realloc_binary_set_test) {
    RUN_TEST(IRBS_01); RUN_TEST(IRBS_02); RUN_TEST(IRBS_03); RUN_TEST(IRBS_04);
    RUN_TEST(IRBS_05); RUN_TEST(IRBS_06); RUN_TEST(IRBS_07); RUN_TEST(IRBS_08);
    RUN_TEST(IRBS_09); RUN_TEST(IRBS_10);
}
