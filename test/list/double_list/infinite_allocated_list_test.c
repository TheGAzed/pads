#include "list_test.h"

#define LIST_MODE INFINITE_ALLOCATED_LIST
#define MAXIMUM_INFINITE_LIST (1 << 4)
#include <list/list.h>

TEST IAL_001(void) {
    list_s test = create_list();

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_002(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IAL_003(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IAL_004(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }
    destroy_list(&test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IAL_005(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IAL_006(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IAL_007(void) {
    list_s test = create_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, copy_element((LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_list(&test, destroy_element);

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IAL_008(void) {
    list_s test = create_list();
    destroy_list(&test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected head to be NULL", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    PASS();
}

TEST IAL_009(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_010(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_011(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_012(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, test.size - i - 1).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_013(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, test.size - i - 1).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_014(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, test.size - i - 1).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_015(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_016(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_017(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_018(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_LIST - 2; i >= 0; --i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, remove_at_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_019(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_LIST - 1; i >= 0; --i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, remove_at_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_020(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = MAXIMUM_INFINITE_LIST; i >= 0; --i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, remove_at_list(&test, test.size - 1).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected size to be 0", 0, test.size);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_021(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", test.size / 2, remove_at_list(&test, test.size / 2).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_022(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test won't pass if it isn't written like this, idk why
    const size_t half = test.size / 2;
    const LIST_DATA_TYPE element = remove_at_list(&test, half);
    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", half, element.sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_023(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", test.size / 2, remove_at_list(&test, test.size / 2).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_024(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", (test.size / 2) - 1, remove_at_list(&test, (test.size / 2) - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_025(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test won't pass if it isn't written like this, idk why
    const size_t half = (test.size / 2) - 1;
    const LIST_DATA_TYPE element = remove_at_list(&test, half);
    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", half, element.sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_026(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", (test.size / 2) - 1, remove_at_list(&test, (test.size / 2) - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_027(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", (test.size / 2) + 1, remove_at_list(&test, (test.size / 2) + 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_028(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    // github actions windows test won't pass if it isn't written like this, idk why
    const size_t half = (test.size / 2) + 1;
    const LIST_DATA_TYPE element = remove_at_list(&test, half);
    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", half, element.sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_029(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected middle element to be double_list size divided by 2", (test.size / 2) + 1, remove_at_list(&test, (test.size / 2) + 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_030(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_list(&test);

    for (int i = MAXIMUM_INFINITE_LIST - 2; i >= 0; --i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_031(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_list(&test);

    for (int i = MAXIMUM_INFINITE_LIST - 1; i >= 0; --i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_032(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    reverse_list(&test);

    for (int i = MAXIMUM_INFINITE_LIST; i >= 0; --i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be i", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_033(void) {
    list_s test = create_list();

    reverse_list(&test);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_034(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_035(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_list(&test, 1, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_036(void) {
    list_s test = create_list();
    insert_at_list(&test, 0, (LIST_DATA_TYPE) { .sub_one = 40, });
    insert_at_list(&test, 1, (LIST_DATA_TYPE) { .sub_one = 41, });
    insert_at_list(&test, 2, (LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_list(&test);

    ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_037(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    shift_next_list(&test, 1);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 2; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's ith element to be (i + 1)", i + 1, get_list(test, i).sub_one);
    }
    ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's last element to be 0", 0, remove_at_list(&test, test.size - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_038(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    shift_next_list(&test, 1);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's ith element to be (i + 1)", i + 1, get_list(test, i).sub_one);
    }
    ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's last element to be 0", 0, remove_at_list(&test, test.size - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_039(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    shift_next_list(&test, 1);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's ith element to be (i + 1)", i + 1, get_list(test, i).sub_one);
    }
    ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's last element to be 0", 0, remove_at_list(&test, test.size - 1).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_040(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be i before shift.", i, get_list(test, 0).sub_one);
        shift_next_list(&test, 1);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_041(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be i before shift.", i, get_list(test, 0).sub_one);
        shift_next_list(&test, 1);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_042(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, i, (LIST_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected reversed double_list's 0th element to be i before shift.", i, get_list(test, 0).sub_one);
        shift_next_list(&test, 1);
    }

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_043(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_044(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_045(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_046(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_047(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_048(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_049(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test_three, NULL);

    destroy_list(&temp, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_050(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test_three, NULL);

    destroy_list(&temp, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_051(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test_three, NULL);

    destroy_list(&temp, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_052(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, test_one.size);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_053(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, 0);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_054(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test_one, test_one.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test = splice_list(&test_one, &test_two, test_one.size / 2);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_055(void) {
    list_s test_one = create_list();
    list_s test_two = create_list();

    list_s test = splice_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IAL-ERROR] Expected test head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected test size to be 0.", 0, test.size);

    destroy_list(&test_one, NULL);
    destroy_list(&test_two, NULL);
    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_056(void) {
    list_s test = create_list();

    shift_next_list(&test, 1);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_057(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, 1);

    ASSERT_EQm("[IAL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_058(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, MAXIMUM_INFINITE_LIST);

    ASSERT_EQm("[IAL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_059(void) {
    list_s test = create_list();

    shift_next_list(&test, 1);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_060(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, 1);

    ASSERT_EQm("[IAL-ERROR] Expected first element to be 42", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_061(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42, });

    shift_next_list(&test, MAXIMUM_INFINITE_LIST);

    ASSERT_EQm("[IAL-ERROR] Expected first element to be 42.", 42, get_list(test, 0).sub_one);

    destroy_list(&test, NULL);

    PASS();
}

TEST IAL_062(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 0, test.size / 2);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + (MAXIMUM_INFINITE_LIST - 1) / 2, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_063(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 2, test.size - (test.size / 2));

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST - 1) / 2), get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_064(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 3, test.size / 3);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST - 1) / 3), get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_065(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 0, test.size / 2);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + (MAXIMUM_INFINITE_LIST) / 2, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_066(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 2, test.size - (test.size / 2));

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST) / 2), get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_067(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 3, test.size / 3);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST) / 3), get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_068(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 0, test.size / 2);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + (MAXIMUM_INFINITE_LIST + 1) / 2, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_069(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 2, test.size - (test.size / 2));

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST + 1) / 2), get_list(test_split, i).sub_one);
    }
    for (int i = 0; i < test.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i, get_list(test, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_070(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size / 3, test.size / 3);

    for (int i = 0; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + ((MAXIMUM_INFINITE_LIST + 1) / 3), get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_071(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 1, test.size);

    for (int i = 0; i < test_split.size - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + 1, get_list(test_split, i).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected last element to be first added.", 0, get_list(test_split, test_split.size - 1).sub_one);

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_072(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size - 1, test.size);

    ASSERT_EQm("[IAL-ERROR] Expected first element to be last added.", MAXIMUM_INFINITE_LIST - 2, get_list(test_split, 0).sub_one);

    for (int i = 1; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i - 1, get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_073(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 1, test.size);

    for (int i = 0; i < test_split.size - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + 1, get_list(test_split, i).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected last element to be first added.", 0, get_list(test_split, test_split.size - 1).sub_one);

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_074(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size - 1, test.size);

    ASSERT_EQm("[IAL-ERROR] Expected first element to be last added.", MAXIMUM_INFINITE_LIST - 1, get_list(test_split, 0).sub_one);

    for (int i = 1; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i - 1, get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_075(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, 1, test.size);

    for (int i = 0; i < test_split.size - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i + 1, get_list(test_split, i).sub_one);
    }

    ASSERT_EQm("[IAL-ERROR] Expected last element to be first added.", 0, get_list(test_split, test_split.size - 1).sub_one);

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_076(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s test_split = split_list(&test, test.size - 1, test.size);

    ASSERT_EQm("[IAL-ERROR] Expected first element to be last added.", MAXIMUM_INFINITE_LIST, get_list(test_split, 0).sub_one);

    for (int i = 1; i < test_split.size; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected ith element to be i.", i - 1, get_list(test_split, i).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&test_split, NULL);

    PASS();
}

TEST IAL_077(void) {
    list_s test = create_list();

    ASSERTm("[IAL-ERROR] Expected double_list to be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_078(void) {
    list_s test = create_list();
    insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = 42 });

    ASSERT_FALSEm("[IAL-ERROR] Expected double_list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_079(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_FALSEm("[IAL-ERROR] Expected double_list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_080(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_FALSEm("[IAL-ERROR] Expected double_list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_081(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_FALSEm("[IAL-ERROR] Expected double_list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_082(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        remove_at_list(&test, test.size - 1);
    }

    ASSERTm("[IAL-ERROR] Expected double_list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_083(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        remove_at_list(&test, test.size - 1);
    }

    ASSERTm("[IAL-ERROR] Expected double_list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_084(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }
    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        remove_at_list(&test, test.size - 1);
    }

    ASSERTm("[IAL-ERROR] Expected double_list to not be empty.", is_empty_list(test));

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_085(void) {
    list_s test = create_list();
    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERT_EQm("[IAL-ERROR] Expected copy head to be equal to test head, so NULL", test.head, copy.head);

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IAL_086(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERTm("[IAL-ERROR] Expected copy head to not be NULL", copy.head);
    ASSERT_NEQm("[IAL-ERROR] Expected copy head to not be equal to test head, so not NULL", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected copy element at index 0 to be equal to test element at index 0", remove_at_list(&test, 0).sub_one, remove_at_list(&copy, 0).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IAL_087(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERTm("[IAL-ERROR] Expected copy head to not be NULL", copy.head);
    ASSERT_NEQm("[IAL-ERROR] Expected copy head to not be equal to test head, so not NULL", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected copy element at index 0 to be equal to test element at index 0", remove_at_list(&test, 0).sub_one, remove_at_list(&copy, 0).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IAL_088(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    list_s copy = copy_list(test, NULL);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero", test.size, copy.size);
    ASSERTm("[IAL-ERROR] Expected copy head to not be NULL", copy.head);
    ASSERT_NEQm("[IAL-ERROR] Expected copy head to not be equal to test head, so not NULL", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected copy element at index 0 to be equal to test element at index 0", remove_at_list(&test, 0).sub_one, remove_at_list(&copy, 0).sub_one);
    }

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IAL_089(void) {
    list_s test = create_list();
    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERT_EQm("[IAL-ERROR] Expected copy head to be equal to test head, so NULL.", test.head, copy.head);

    destroy_list(&test, NULL);
    destroy_list(&copy, NULL);

    PASS();
}

TEST IAL_090(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, copy_element((LIST_DATA_TYPE) {.sub_two = TEST_STRING}));
    }

    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERTm("[IAL-ERROR] Expected copy head to not be NULL.", copy.head);
    ASSERT_NEQm("[IAL-ERROR] Expected copy head to not be equal to test head, so not NULL.", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        LIST_DATA_TYPE test_element = remove_at_list(&test, 0);
        LIST_DATA_TYPE copy_element = remove_at_list(&copy, 0);

        ASSERT_STRN_EQm("[IAL-ERROR] Expected copy element at index 0 to be equal to test element at index 0.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_element(&test_element);
        destroy_element(&copy_element);
    }

    destroy_list(&test, destroy_element);
    destroy_list(&copy, destroy_element);

    PASS();
}

TEST IAL_091(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, copy_element((LIST_DATA_TYPE) {.sub_two = TEST_STRING}));
    }

    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERTm("[IAL-ERROR] Expected copy head to not be NULL.", copy.head);
    ASSERT_NEQm("[IAL-ERROR] Expected copy head to not be equal to test head, so not NULL.", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        LIST_DATA_TYPE test_element = remove_at_list(&test, 0);
        LIST_DATA_TYPE copy_element = remove_at_list(&copy, 0);

        ASSERT_STRN_EQm("[IAL-ERROR] Expected copy element at index 0 to be equal to test element at index 0.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_element(&test_element);
        destroy_element(&copy_element);
    }

    destroy_list(&test, destroy_element);
    destroy_list(&copy, destroy_element);

    PASS();
}

TEST IAL_092(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, copy_element((LIST_DATA_TYPE) {.sub_two = TEST_STRING}));
    }

    list_s copy = copy_list(test, copy_element);

    ASSERT_EQm("[IAL-ERROR] Expected copy size to be equal to test size, so zero.", test.size, copy.size);
    ASSERTm("[IAL-ERROR] Expected copy head to not be NULL.", copy.head);
    ASSERT_NEQm("[IAL-ERROR] Expected copy head to not be equal to test head, so not NULL.", test.head, copy.head);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        LIST_DATA_TYPE test_element = remove_at_list(&test, 0);
        LIST_DATA_TYPE copy_element = remove_at_list(&copy, 0);

        ASSERT_STRN_EQm("[IAL-ERROR] Expected copy element at index 0 to be equal to test element at index 0.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_element(&test_element);
        destroy_element(&copy_element);
    }

    destroy_list(&test, destroy_element);
    destroy_list(&copy, destroy_element);

    PASS();
}

TEST IAL_093(void) {
    list_s test = create_list();

    sort_list(&test, qsort, compare_int);

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IAL_094(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to i.", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IAL_095(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to i.", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IAL_096(void) {
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
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to i.", i, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);
    PASS();
}

TEST IAL_097(void) {
    list_s test = create_list();

    int add = 0;
    foreach_list(&test, operation_int, &add);

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IAL_098(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IAL_099(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IAL_100(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IAL_101(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_first_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_102(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_first_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_103(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_first_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_104(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_first_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_105(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_first_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_106(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_first_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_107(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_last_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_108(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_last_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_109(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_last_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_110(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_last_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_111(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_last_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_112(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_last_list(&test, element, compare_int).sub_one);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_113(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_first_list(&test, element, compare_int).sub_one);
    ASSERT_EQm("[IAL-ERROR] Expected test head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected test size to be zero.", 0, test.size);

    destroy_list(&test, NULL);
    PASS();
}

TEST IAL_114(void) {
    list_s test = create_list();

    const LIST_DATA_TYPE element = (LIST_DATA_TYPE) { .sub_one = 42 };
    insert_at_list(&test, test.size, element);

    ASSERT_EQm("[IAL-ERROR] Expected element to be removed.", element.sub_one, remove_last_list(&test, element, compare_int).sub_one);
    ASSERT_EQm("[IAL-ERROR] Expected test head to be NULL.", NULL, test.head);
    ASSERT_EQm("[IAL-ERROR] Expected test size to be zero.", 0, test.size);

    destroy_list(&test, NULL);
    PASS();
}


TEST IAL_115(void) {
    list_s test = create_list();

    int add = 0;
    foreach_reverse_list(&test, operation_int, &add);

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IAL_116(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_reverse_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST - 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IAL_117(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_reverse_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

TEST IAL_118(void) {
    list_s test = create_list();

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        insert_at_list(&test, test.size, (LIST_DATA_TYPE) { .sub_one = i });
    }

    int add = 1;
    foreach_reverse_list(&test, operation_int, &add);

    for (int i = 0; i < MAXIMUM_INFINITE_LIST + 1; ++i) {
        ASSERT_EQm("[IAL-ERROR] Expected test element at index 0 to be equal to (i + add).", i + add, remove_at_list(&test, 0).sub_one);
    }

    destroy_list(&test, destroy_element);

    PASS();
}

SUITE (infinite_allocated_list_test) {
    RUN_TEST(IAL_001); RUN_TEST(IAL_002); RUN_TEST(IAL_003); RUN_TEST(IAL_004);
    RUN_TEST(IAL_005); RUN_TEST(IAL_006); RUN_TEST(IAL_007); RUN_TEST(IAL_008);
    RUN_TEST(IAL_009); RUN_TEST(IAL_010); RUN_TEST(IAL_011); RUN_TEST(IAL_012);
    RUN_TEST(IAL_013); RUN_TEST(IAL_014); RUN_TEST(IAL_015); RUN_TEST(IAL_016);
    RUN_TEST(IAL_017); RUN_TEST(IAL_018); RUN_TEST(IAL_019); RUN_TEST(IAL_020);
    RUN_TEST(IAL_021); RUN_TEST(IAL_022); RUN_TEST(IAL_023); RUN_TEST(IAL_024);
    RUN_TEST(IAL_025); RUN_TEST(IAL_026); RUN_TEST(IAL_027); RUN_TEST(IAL_028);
    RUN_TEST(IAL_029); RUN_TEST(IAL_030); RUN_TEST(IAL_031); RUN_TEST(IAL_032);
    RUN_TEST(IAL_033); RUN_TEST(IAL_034); RUN_TEST(IAL_035); RUN_TEST(IAL_036);
    RUN_TEST(IAL_037); RUN_TEST(IAL_038); RUN_TEST(IAL_039); RUN_TEST(IAL_040);
    RUN_TEST(IAL_041); RUN_TEST(IAL_042); RUN_TEST(IAL_043); RUN_TEST(IAL_044);
    RUN_TEST(IAL_045); RUN_TEST(IAL_046); RUN_TEST(IAL_047); RUN_TEST(IAL_048);
    RUN_TEST(IAL_049); RUN_TEST(IAL_050); RUN_TEST(IAL_051); RUN_TEST(IAL_052);
    RUN_TEST(IAL_053); RUN_TEST(IAL_054); RUN_TEST(IAL_055); RUN_TEST(IAL_056);
    RUN_TEST(IAL_057); RUN_TEST(IAL_058); RUN_TEST(IAL_059); RUN_TEST(IAL_060);
    RUN_TEST(IAL_061); RUN_TEST(IAL_062); RUN_TEST(IAL_063); RUN_TEST(IAL_064);
    RUN_TEST(IAL_065); RUN_TEST(IAL_066); RUN_TEST(IAL_067); RUN_TEST(IAL_068);
    RUN_TEST(IAL_069); RUN_TEST(IAL_070); RUN_TEST(IAL_071); RUN_TEST(IAL_072);
    RUN_TEST(IAL_073); RUN_TEST(IAL_074); RUN_TEST(IAL_075); RUN_TEST(IAL_076);
    RUN_TEST(IAL_077); RUN_TEST(IAL_078); RUN_TEST(IAL_079); RUN_TEST(IAL_080);
    RUN_TEST(IAL_081); RUN_TEST(IAL_082); RUN_TEST(IAL_083); RUN_TEST(IAL_084);
    RUN_TEST(IAL_085); RUN_TEST(IAL_086); RUN_TEST(IAL_087); RUN_TEST(IAL_088);
    RUN_TEST(IAL_089); RUN_TEST(IAL_090); RUN_TEST(IAL_091); RUN_TEST(IAL_092);
    RUN_TEST(IAL_093); RUN_TEST(IAL_094); RUN_TEST(IAL_095); RUN_TEST(IAL_096);
    RUN_TEST(IAL_097); RUN_TEST(IAL_098); RUN_TEST(IAL_099); RUN_TEST(IAL_100);
    RUN_TEST(IAL_101); RUN_TEST(IAL_102); RUN_TEST(IAL_103); RUN_TEST(IAL_104);
    RUN_TEST(IAL_105); RUN_TEST(IAL_106); RUN_TEST(IAL_107); RUN_TEST(IAL_108);
    RUN_TEST(IAL_109); RUN_TEST(IAL_110); RUN_TEST(IAL_111); RUN_TEST(IAL_112);
    RUN_TEST(IAL_113); RUN_TEST(IAL_114); RUN_TEST(IAL_115); RUN_TEST(IAL_116);
    RUN_TEST(IAL_117); RUN_TEST(IAL_118);
}
