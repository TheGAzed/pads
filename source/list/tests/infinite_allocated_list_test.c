#include "list_test.h"

#define LIST_MODE INFINITE_ALLOCATED_LIST
#define MAXIMUM_INFINITE_LIST (1 << 4)
#include <list/list.h>

TEST IADL_001(void) {
    list_s test = create_list();

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_002(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_003(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_004(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_005(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_006(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_007(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_008(void) {
    list_s test = create_list();
    destroy_list(&test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IADL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IADL_009(void) {
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

TEST IADL_010(void) {
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

TEST IADL_011(void) {
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

TEST IADL_012(void) {
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

TEST IADL_013(void) {
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

TEST IADL_014(void) {
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

TEST IADL_015(void) {
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

TEST IADL_016(void) {
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

TEST IADL_017(void) {
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

TEST IADL_018(void) {
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

TEST IADL_019(void) {
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

TEST IADL_020(void) {
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

TEST IADL_021(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", test.size / 2, remove_at_list(&test, test.size / 2).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_022(void) {
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

TEST IADL_023(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", test.size / 2, remove_at_list(&test, test.size / 2).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_024(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) - 1, remove_at_list(&test, (test.size / 2) - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_025(void) {
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

TEST IADL_026(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) - 1, remove_at_list(&test, (test.size / 2) - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_027(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) + 1, remove_at_list(&test, (test.size / 2) + 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_028(void) {
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

TEST IADL_029(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IADL-ERROR] Expected middle element to be list size divided by 2", (test.size / 2) + 1, remove_at_list(&test, (test.size / 2) + 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_030(void) {
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

TEST IADL_031(void) {
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

TEST IADL_032(void) {
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

TEST IADL_033(void) {
    list_s test = create_list();

    reverse_list(&test);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_034(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_035(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_list(&test, 1, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_036(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 40, });
    insert_at_list(&test, 1, (LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_list(&test, 2, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IADL-ERROR] Expected reversed list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_037(void) {
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

TEST IADL_038(void) {
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

TEST IADL_039(void) {
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

TEST IADL_040(void) {
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

TEST IADL_041(void) {
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

TEST IADL_042(void) {
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

TEST IADL_043(void) {
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

TEST IADL_044(void) {
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

TEST IADL_045(void) {
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

TEST IADL_046(void) {
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

TEST IADL_047(void) {
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

TEST IADL_048(void) {
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

TEST IADL_049(void) {
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

TEST IADL_050(void) {
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

TEST IADL_051(void) {
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

TEST IADL_052(void) {
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

TEST IADL_053(void) {
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

TEST IADL_054(void) {
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

TEST IADL_055(void) {
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

TEST IADL_056(void) {
    list_s test = create_list();

    shift_next_list(&test, 1);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_057(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, 1);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_058(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, MAXIMUM_INFINITE_LIST);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_059(void) {
    list_s test = create_list();

    shift_next_list(&test, 1);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_060(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, 1);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_061(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, MAXIMUM_INFINITE_LIST);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be 42.", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IADL_062(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 0, test.size / 2);

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

TEST IADL_063(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 2, test.size - (test.size / 2));

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

TEST IADL_064(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 3, test.size / 3);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST - 1) / 3), get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_065(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 0, test.size / 2);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + (MAXIMUM_INFINITE_LIST) / 2, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_066(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 2, test.size - (test.size / 2));

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST) / 2), get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_067(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 3, test.size / 3);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST) / 3), get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_068(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 0, test.size / 2);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + (MAXIMUM_INFINITE_LIST + 1) / 2, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_069(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 2, test.size - (test.size / 2));

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST + 1) / 2), get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_070(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 3, test.size / 3);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST + 1) / 3), get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_071(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 1, test.size);

    for (int i = 0; i < test_split.size - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + 1, get_list(test_split, i).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected last element to be first added.", 0, get_list(test_split, test_split.size - 1).sub_one);

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_072(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size - 1, test.size);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be last added.", MAXIMUM_INFINITE_LIST - 2, get_list(test_split, 0).sub_one);

    for (int i = 1; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i - 1, get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_073(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 1, test.size);

    for (int i = 0; i < test_split.size - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + 1, get_list(test_split, i).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected last element to be first added.", 0, get_list(test_split, test_split.size - 1).sub_one);

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_074(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size - 1, test.size);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be last added.", MAXIMUM_INFINITE_LIST - 1, get_list(test_split, 0).sub_one);

    for (int i = 1; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i - 1, get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_075(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 1, test.size);

    for (int i = 0; i < test_split.size - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i + 1, get_list(test_split, i).sub_one);
    }

    ASSERT_EQm("[IADL-ERROR] Expected last element to be first added.", 0, get_list(test_split, test_split.size - 1).sub_one);

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_076(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size - 1, test.size);

    ASSERT_EQm("[IADL-ERROR] Expected first element to be last added.", MAXIMUM_INFINITE_LIST, get_list(test_split, 0).sub_one);

    for (int i = 1; i < test_split.size; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected ith element to be i.", i - 1, get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IADL_077(void) {
    list_s test = create_list();

    ASSERTm("[IADL-ERROR] Expected list to be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_078(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42 });

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_079(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_080(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_081(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_FALSEm("[IADL-ERROR] Expected list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_082(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        remove_at_list(&test, test.size - 1);
    }

    ASSERTm("[IADL-ERROR] Expected list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_083(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        remove_at_list(&test, test.size - 1);
    }

    ASSERTm("[IADL-ERROR] Expected list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_084(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        remove_at_list(&test, test.size - 1);
    }

    ASSERTm("[IADL-ERROR] Expected list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IADL_085(void) {
    list_s test = create_list();
    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERT_EQm("[IADL-ERROR] Expected copy head to be equal to test head, so NULL", test.head, copy.head);

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IADL_086(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERTm("[IADL-ERROR] Expected copy head to not be NULL", copy.head);
    ASSERT_NEQm("[IADL-ERROR] Expected copy head to not be equal to test head, so not NULL", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected copy element at index 0 to be equal to test element at index 0", remove_at_list(&test, 0).sub_one, remove_at_list(&copy, 0).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IADL_087(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERTm("[IADL-ERROR] Expected copy head to not be NULL", copy.head);
    ASSERT_NEQm("[IADL-ERROR] Expected copy head to not be equal to test head, so not NULL", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected copy element at index 0 to be equal to test element at index 0", remove_at_list(&test, 0).sub_one, remove_at_list(&copy, 0).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IADL_088(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERTm("[IADL-ERROR] Expected copy head to not be NULL", copy.head);
    ASSERT_NEQm("[IADL-ERROR] Expected copy head to not be equal to test head, so not NULL", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected copy element at index 0 to be equal to test element at index 0", remove_at_list(&test, 0).sub_one, remove_at_list(&copy, 0).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IADL_089(void) {
    list_s test = create_list();
    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERT_EQm("[IADL-ERROR] Expected copy head to be equal to test head, so NULL.", test.head, copy.head);

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IADL_090(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, copy_element((LIST_DATA_TYPE) {.sub_two = TEST_STRING}));
    }

    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERTm("[IADL-ERROR] Expected copy head to not be NULL.", copy.head);
    ASSERT_NEQm("[IADL-ERROR] Expected copy head to not be equal to test head, so not NULL.", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        LIST_DATA_TYPE test_element = remove_at_list(&test, 0);
        LIST_DATA_TYPE copy_element = remove_at_list(&copy, 0);

        ASSERT_STRN_EQm("[IADL-ERROR] Expected copy element at index 0 to be equal to test element at index 0.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_element(&test_element);
        destroy_element(&copy_element);
    }

    destroy_list(&test, destroy_element);
    destroy_list(&copy, destroy_element);

    PASS();
}

TEST IADL_091(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, copy_element((LIST_DATA_TYPE) {.sub_two = TEST_STRING}));
    }

    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERTm("[IADL-ERROR] Expected copy head to not be NULL.", copy.head);
    ASSERT_NEQm("[IADL-ERROR] Expected copy head to not be equal to test head, so not NULL.", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        LIST_DATA_TYPE test_element = remove_at_list(&test, 0);
        LIST_DATA_TYPE copy_element = remove_at_list(&copy, 0);

        ASSERT_STRN_EQm("[IADL-ERROR] Expected copy element at index 0 to be equal to test element at index 0.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_element(&test_element);
        destroy_element(&copy_element);
    }

    destroy_list(&test, destroy_element);
    destroy_list(&copy, destroy_element);

    PASS();
}

TEST IADL_092(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, copy_element((LIST_DATA_TYPE) {.sub_two = TEST_STRING}));
    }

    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IADL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERTm("[IADL-ERROR] Expected copy head to not be NULL.", copy.head);
    ASSERT_NEQm("[IADL-ERROR] Expected copy head to not be equal to test head, so not NULL.", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        LIST_DATA_TYPE test_element = remove_at_list(&test, 0);
        LIST_DATA_TYPE copy_element = remove_at_list(&copy, 0);

        ASSERT_STRN_EQm("[IADL-ERROR] Expected copy element at index 0 to be equal to test element at index 0.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_element(&test_element);
        destroy_element(&copy_element);
    }

    destroy_list(&test, destroy_element);
    destroy_list(&copy, destroy_element);

    PASS();
}

TEST IADL_093(void) {
    list_s test = create_list();

    sort_list(&test, qsort, compare_int);

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IADL_094(void) {
    list_s test = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST - 1) / 2; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = (MAXIMUM_INFINITE_LIST - 2) - i });
    }
    if ((MAXIMUM_INFINITE_LIST - 1) & 0x01) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = (MAXIMUM_INFINITE_LIST - 1) / 2 });
    }

    sort_list(&test, qsort, compare_int);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected test element at index 0 to be equal to i.", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IADL_095(void) {
    list_s test = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST) / 2; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = (MAXIMUM_INFINITE_LIST - 1) - i });
    }
    if ((MAXIMUM_INFINITE_LIST) & 0x01) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = (MAXIMUM_INFINITE_LIST) / 2 });
    }

    sort_list(&test, qsort, compare_int);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected test element at index 0 to be equal to i.", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IADL_096(void) {
    list_s test = create_list();

    for (int i = 0; i < (MAXIMUM_INFINITE_LIST + 1) / 2; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = (MAXIMUM_INFINITE_LIST) - i });
    }
    if ((MAXIMUM_INFINITE_LIST + 1) & 0x01) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = (MAXIMUM_INFINITE_LIST + 1) / 2 });
    }

    sort_list(&test, qsort, compare_int);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected test element at index 0 to be equal to i.", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IADL_097(void) {
    list_s test = create_list();

    int add = 0;
    foreach_list(&test, operation_int, &add);

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IADL_098(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IADL_099(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IADL_100(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IADL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

SUITE (infinite_allocated_list_test) {
    RUN_TEST(IADL_001); RUN_TEST(IADL_002); RUN_TEST(IADL_003); RUN_TEST(IADL_004);
    RUN_TEST(IADL_005); RUN_TEST(IADL_006); RUN_TEST(IADL_007); RUN_TEST(IADL_008);
    RUN_TEST(IADL_009); RUN_TEST(IADL_010); RUN_TEST(IADL_011); RUN_TEST(IADL_012);
    RUN_TEST(IADL_013); RUN_TEST(IADL_014); RUN_TEST(IADL_015); RUN_TEST(IADL_016);
    RUN_TEST(IADL_017); RUN_TEST(IADL_018); RUN_TEST(IADL_019); RUN_TEST(IADL_020);
    RUN_TEST(IADL_021); RUN_TEST(IADL_022); RUN_TEST(IADL_023); RUN_TEST(IADL_024);
    RUN_TEST(IADL_025); RUN_TEST(IADL_026); RUN_TEST(IADL_027); RUN_TEST(IADL_028);
    RUN_TEST(IADL_029); RUN_TEST(IADL_030); RUN_TEST(IADL_031); RUN_TEST(IADL_032);
    RUN_TEST(IADL_033); RUN_TEST(IADL_034); RUN_TEST(IADL_035); RUN_TEST(IADL_036);
    RUN_TEST(IADL_037); RUN_TEST(IADL_038); RUN_TEST(IADL_039); RUN_TEST(IADL_040);
    RUN_TEST(IADL_041); RUN_TEST(IADL_042); RUN_TEST(IADL_043); RUN_TEST(IADL_044);
    RUN_TEST(IADL_045); RUN_TEST(IADL_046); RUN_TEST(IADL_047); RUN_TEST(IADL_048);
    RUN_TEST(IADL_049); RUN_TEST(IADL_050); RUN_TEST(IADL_051); RUN_TEST(IADL_052);
    RUN_TEST(IADL_053); RUN_TEST(IADL_054); RUN_TEST(IADL_055); RUN_TEST(IADL_056);
    RUN_TEST(IADL_057); RUN_TEST(IADL_058); RUN_TEST(IADL_059); RUN_TEST(IADL_060);
    RUN_TEST(IADL_061); RUN_TEST(IADL_062); RUN_TEST(IADL_063); RUN_TEST(IADL_064);
    RUN_TEST(IADL_065); RUN_TEST(IADL_066); RUN_TEST(IADL_067); RUN_TEST(IADL_068);
    RUN_TEST(IADL_069); RUN_TEST(IADL_070); RUN_TEST(IADL_071); RUN_TEST(IADL_072);
    RUN_TEST(IADL_073); RUN_TEST(IADL_074); RUN_TEST(IADL_075); RUN_TEST(IADL_076);
    RUN_TEST(IADL_077); RUN_TEST(IADL_078); RUN_TEST(IADL_079); RUN_TEST(IADL_080);
    RUN_TEST(IADL_081); RUN_TEST(IADL_082); RUN_TEST(IADL_083); RUN_TEST(IADL_084);
    RUN_TEST(IADL_085); RUN_TEST(IADL_086); RUN_TEST(IADL_087); RUN_TEST(IADL_088);
    RUN_TEST(IADL_089); RUN_TEST(IADL_090); RUN_TEST(IADL_091); RUN_TEST(IADL_092);
    RUN_TEST(IADL_093); RUN_TEST(IADL_094); RUN_TEST(IADL_095); RUN_TEST(IADL_096);
    RUN_TEST(IADL_097); RUN_TEST(IADL_098); RUN_TEST(IADL_099); RUN_TEST(IADL_100);
}
