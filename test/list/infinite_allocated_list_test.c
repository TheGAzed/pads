#include "list_test.h"

#define LIST_MODE INFINITE_ALLOCATED_LIST
#define MAXIMUM_INFINITE_LIST (1 << 4)
#include <list.h>

TEST IADL_01(void) {
    list_s test = create_list();

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_02(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_03(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_04(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_05(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_06(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_07(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_08(void) {
    list_s test = create_list();
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_09(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_10(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_11(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_12(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, test.size - i - 1).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_13(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, test.size - i - 1).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_14(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, test.size - i - 1).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_15(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_16(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_17(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_18(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_LIST - 2; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_19(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_LIST - 1; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_20(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_LIST; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, remove_at_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_21(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", test.size / 2, remove_at_list(&test, test.size / 2).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_22(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test won't pass if it isn't written like this, idk why
    const size_t half = test.size / 2;
    const LIST_DATA_TYPE element = remove_at_list(&test, half);
    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", half, element.sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_23(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", test.size / 2, remove_at_list(&test, test.size / 2).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_24(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) - 1, remove_at_list(&test, (test.size / 2) - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_25(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test won't pass if it isn't written like this, idk why
    const size_t half = (test.size / 2) - 1;
    const LIST_DATA_TYPE element = remove_at_list(&test, half);
    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", half, element.sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_26(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) - 1, remove_at_list(&test, (test.size / 2) - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_27(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) + 1, remove_at_list(&test, (test.size / 2) + 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_28(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test won't pass if it isn't written like this, idk why
    const size_t half = (test.size / 2) + 1;
    const LIST_DATA_TYPE element = remove_at_list(&test, half);
    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", half, element.sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_29(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) + 1, remove_at_list(&test, (test.size / 2) + 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_30(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_list(&test);

    for (int i = MAXIMUM_INFINITE_LIST - 2; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_31(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_list(&test);

    for (int i = MAXIMUM_INFINITE_LIST - 1; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_32(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_list(&test);

    for (int i = MAXIMUM_INFINITE_LIST; i >= 0; --i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_33(void) {
    list_s test = create_list();

    reverse_list(&test);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_34(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_35(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_list(&test, 1, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_36(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 40, });
    insert_at_list(&test, 1, (LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_list(&test, 2, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_37(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    shift_next_list(&test, 1);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 2; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's ith element to be (i + 1)", i + 1, get_list(test, i).sub_one);
    }
    ASSERT_EQm("[IADL-ERROR] Expected reversed list's last element to be 0", 0, remove_at_list(&test, test.size - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_38(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    shift_next_list(&test, 1);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's ith element to be (i + 1)", i + 1, get_list(test, i).sub_one);
    }
    ASSERT_EQm("[IADL-ERROR] Expected reversed list's last element to be 0", 0, remove_at_list(&test, test.size - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_39(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    shift_next_list(&test, 1);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's ith element to be (i + 1)", i + 1, get_list(test, i).sub_one);
    }
    ASSERT_EQm("[IADL-ERROR] Expected reversed list's last element to be 0", 0, remove_at_list(&test, test.size - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_40(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i before shift.", i, get_list(test, 0).sub_one);
        shift_next_list(&test, 1);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_41(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i before shift.", i, get_list(test, 0).sub_one);
        shift_next_list(&test, 1);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_42(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be i before shift.", i, get_list(test, 0).sub_one);
        shift_next_list(&test, 1);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_43(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST - 1) / 2; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST - 1) / 2; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, test_one.size);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_44(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST) / 2; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST) / 2; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, test_one.size);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_45(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST + 1) / 2; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST + 1) / 2; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, test_one.size);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_46(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST - 1) / 2; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST - 1) / 2; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_two, &test_one, 0);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_47(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST) / 2; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST) / 2; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_two, &test_one, 0);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_48(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST + 1) / 2; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST + 1) / 2; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_two, &test_one, 0);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_49(void) {
    list_s test_one   = create_list();
    list_s test_two   = create_list();
    list_s test_three = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST - 1) / 3; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST - 1) / 3; i < ((MAXIMUM_INFINITE_LIST - 1) / 3) * 2; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = ((MAXIMUM_INFINITE_LIST - 1) / 3) * 2; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_three, test_three.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s temp = splice_list(&test_one, &test_three, test_one.size);
    list_s test = splice_list(&temp, &test_two, (MAXIMUM_INFINITE_LIST - 1) / 3);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test_three, NULL);

    destroy_list(&temp, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_50(void) {
    list_s test_one   = create_list();
    list_s test_two   = create_list();
    list_s test_three = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST) / 3; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST) / 3; i < ((MAXIMUM_INFINITE_LIST) / 3) * 2; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = ((MAXIMUM_INFINITE_LIST) / 3) * 2; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test_three, test_three.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s temp = splice_list(&test_one, &test_three, test_one.size);
    list_s test = splice_list(&temp, &test_two, (MAXIMUM_INFINITE_LIST) / 3);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test_three, NULL);

    destroy_list(&temp, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_51(void) {
    list_s test_one   = create_list();
    list_s test_two   = create_list();
    list_s test_three = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST + 1) / 3; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = (MAXIMUM_INFINITE_LIST + 1) / 3; i < ((MAXIMUM_INFINITE_LIST + 1) / 3) * 2; ++i) {
        insert_at_list(&test_two, test_two.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = ((MAXIMUM_INFINITE_LIST + 1) / 3) * 2; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test_three, test_three.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s temp = splice_list(&test_one, &test_three, test_one.size);
    list_s test = splice_list(&temp, &test_two, (MAXIMUM_INFINITE_LIST + 1) / 3);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test_three, NULL);

    destroy_list(&temp, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_52(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, test_one.size);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_53(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, 0);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_54(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, test_one.size / 2);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_55(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    list_s test = splice_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected test size to be 0.", 0, test.size);

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_56(void) {
    list_s test = create_list();

    shift_next_list(&test, 1);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_57(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, 1);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_58(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, MAXIMUM_INFINITE_LIST);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_59(void) {
    list_s test = create_list();

    shift_next_list(&test, 1);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_60(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, 1);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_61(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, MAXIMUM_INFINITE_LIST);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42.", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_62(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 0, (MAXIMUM_INFINITE_LIST - 1) / 2);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + (MAXIMUM_INFINITE_LIST - 1) / 2, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_63(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, (MAXIMUM_INFINITE_LIST - 1) / 2, test.size - ((MAXIMUM_INFINITE_LIST - 1) / 2));

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST - 1) / 2), get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_64(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, (MAXIMUM_INFINITE_LIST - 1) / 3, (MAXIMUM_INFINITE_LIST - 1) / 3);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST - 1) / 3), get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

SUITE (infinite_allocated_list_test) {
    RUN_TEST(IADL_01); RUN_TEST(IADL_02); RUN_TEST(IADL_03); RUN_TEST(IADL_04);
    RUN_TEST(IADL_05); RUN_TEST(IADL_06); RUN_TEST(IADL_07); RUN_TEST(IADL_08);
    RUN_TEST(IADL_09); RUN_TEST(IADL_10); RUN_TEST(IADL_11); RUN_TEST(IADL_12);
    RUN_TEST(IADL_13); RUN_TEST(IADL_14); RUN_TEST(IADL_15); RUN_TEST(IADL_16);
    RUN_TEST(IADL_17); RUN_TEST(IADL_18); RUN_TEST(IADL_19); RUN_TEST(IADL_20);
    RUN_TEST(IADL_21); RUN_TEST(IADL_22); RUN_TEST(IADL_23); RUN_TEST(IADL_24);
    RUN_TEST(IADL_25); RUN_TEST(IADL_26); RUN_TEST(IADL_27); RUN_TEST(IADL_28);
    RUN_TEST(IADL_29); RUN_TEST(IADL_30); RUN_TEST(IADL_31); RUN_TEST(IADL_32);
    RUN_TEST(IADL_33); RUN_TEST(IADL_34); RUN_TEST(IADL_35); RUN_TEST(IADL_36);
    RUN_TEST(IADL_37); RUN_TEST(IADL_38); RUN_TEST(IADL_39); RUN_TEST(IADL_40);
    RUN_TEST(IADL_41); RUN_TEST(IADL_42); RUN_TEST(IADL_43); RUN_TEST(IADL_44);
    RUN_TEST(IADL_45); RUN_TEST(IADL_46); RUN_TEST(IADL_47); RUN_TEST(IADL_48);
    RUN_TEST(IADL_49); RUN_TEST(IADL_50); RUN_TEST(IADL_51); RUN_TEST(IADL_52);
    RUN_TEST(IADL_53); RUN_TEST(IADL_54); RUN_TEST(IADL_55); RUN_TEST(IADL_56);
    RUN_TEST(IADL_57); RUN_TEST(IADL_58); RUN_TEST(IADL_59); RUN_TEST(IADL_60);
    RUN_TEST(IADL_61); RUN_TEST(IADL_62); RUN_TEST(IADL_63); RUN_TEST(IADL_64);
}
