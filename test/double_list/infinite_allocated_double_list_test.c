#include "double_list_test.h"

#define DOUBLE_LIST_MODE INFINITE_ALLOCATED_DOUBLE_LIST
#define MAXIMUM_INFINITE_DOUBLE_LIST (1 << 4)
#include <double_list.h>

TEST IADL_01(void) {
    double_list_s test = create_double_list();

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_02(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_double_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_03(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_double_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_04(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_double_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_05(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, copy_element((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_double_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_06(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, copy_element((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_double_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_07(void) {
    double_list_s test = create_double_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, copy_element((DOUBLE_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_double_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_08(void) {
    double_list_s test = create_double_list();
    destroy_double_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_09(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_10(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_11(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_double_list(test, i).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_12(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_double_list(test, test.size - i - 1).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_13(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_double_list(test, test.size - i - 1).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_14(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_double_list(test, test.size - i - 1).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_15(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_double_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_16(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_double_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_17(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_double_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_18(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_DOUBLE_LIST - 2; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_double_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_19(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_DOUBLE_LIST - 1; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_double_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_20(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_DOUBLE_LIST; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_double_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_21(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", test.size / 2, remove_at_double_list(&test, test.size / 2).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_22(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test wonmt pass if it isn't written like this, idk why
    const size_t half = test.size / 2;
    const DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, half);
    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", half, element.sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_23(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", test.size / 2, remove_at_double_list(&test, test.size / 2).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_24(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) - 1, remove_at_double_list(&test, (test.size / 2) - 1).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_25(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test wonmt pass if it isn't written like this, idk why
    const size_t half = (test.size / 2) - 1;
    const DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, half);
    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", half, element.sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_26(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) - 1, remove_at_double_list(&test, (test.size / 2) - 1).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_27(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) + 1, remove_at_double_list(&test, (test.size / 2) + 1).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_28(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test wonmt pass if it isn't written like this, idk why
    const size_t half = (test.size / 2) + 1;
    const DOUBLE_LIST_DATA_TYPE element = remove_at_double_list(&test, half);
    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", half, element.sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_29(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) + 1, remove_at_double_list(&test, (test.size / 2) + 1).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_30(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST - 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_double_list(&test);

    for (int i = MAXIMUM_INFINITE_DOUBLE_LIST - 2; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i", i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_31(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_double_list(&test);

    for (int i = MAXIMUM_INFINITE_DOUBLE_LIST - 1; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i", i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_32(void) {
    double_list_s test = create_double_list();

    for (int i = 0; i < MAXIMUM_INFINITE_DOUBLE_LIST + 1; ++i) {
        insert_at_double_list(&test, i, (DOUBLE_LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_double_list(&test);

    for (int i = MAXIMUM_INFINITE_DOUBLE_LIST; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i", i, remove_at_double_list(&test, 0).sub_one);
    }

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_33(void) {
    double_list_s test = create_double_list();

    reverse_double_list(&test);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_34(void) {
    double_list_s test = create_double_list();
    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_double_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_35(void) {
    double_list_s test = create_double_list();
    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_double_list(&test, 1, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_double_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

TEST IADL_36(void) {
    double_list_s test = create_double_list();
    insert_at_double_list(&test, 0, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 40, });
    insert_at_double_list(&test, 1, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_double_list(&test, 2, (DOUBLE_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_double_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, remove_at_double_list(&test, 0).sub_one);

    destroy_double_list(&test, NULL);

    PASS();
}

SUITE (infinite_allocated_double_list_test) {
    RUN_TEST(IADL_01); RUN_TEST(IADL_02); RUN_TEST(IADL_03); RUN_TEST(IADL_04);
    RUN_TEST(IADL_05); RUN_TEST(IADL_06); RUN_TEST(IADL_07); RUN_TEST(IADL_08);
    RUN_TEST(IADL_09); RUN_TEST(IADL_10); RUN_TEST(IADL_11); RUN_TEST(IADL_12);
    RUN_TEST(IADL_13); RUN_TEST(IADL_14); RUN_TEST(IADL_15); RUN_TEST(IADL_16);
    RUN_TEST(IADL_17); RUN_TEST(IADL_18); RUN_TEST(IADL_19); RUN_TEST(IADL_20);
    RUN_TEST(IADL_21); RUN_TEST(IADL_22); RUN_TEST(IADL_23); RUN_TEST(IADL_24);
    RUN_TEST(IADL_25); RUN_TEST(IADL_26); RUN_TEST(IADL_27); RUN_TEST(IADL_28);
    RUN_TEST(IADL_29); RUN_TEST(IADL_30); RUN_TEST(IADL_31); RUN_TEST(IADL_32);
}
