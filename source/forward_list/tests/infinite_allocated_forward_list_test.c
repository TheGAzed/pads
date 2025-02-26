#include "forward_list_test.h"

#define FORWARD_LIST_MODE INFINITE_ALLOCATED_FORWARD_LIST
#define MAXIMUM_INFINITE_FORWARD_LIST (1 << 4)
#include <forward_list/forward_list.h>

TEST IAFL_CREATE_01(void) {
    forward_list_s test = create_forward_list();
    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_CREATE_02(void) {
    forward_list_s test = create_forward_list();
    destroy_forward_list(&test, destroy_element);

    PASS();
}

TEST IAFL_CREATE_03(void) {
    forward_list_s test = create_forward_list();

    ASSERT_EQm("[IAFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IAFL-ERROR] test list's size is not NULL.", NULL, test.tail);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_CREATE_04(void) {
    forward_list_s test = create_forward_list();

    ASSERT_EQm("[IAFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IAFL-ERROR] test list's size is not NULL.", NULL, test.tail);

    destroy_forward_list(&test, destroy_element);

    PASS();
}

TEST IAFL_INSERT_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IAFL-ERROR] Expected size to be 1", 1, test.size);
    ASSERT_NEQm("[IAFL-ERROR] Expected tail to not be NULL", NULL, test.tail);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_INSERT_02(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST - 1; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IAFL-ERROR] Expected size to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1'", MAXIMUM_INFINITE_FORWARD_LIST - 1, test.size);
    ASSERT_NEQm("[IAFL-ERROR] Expected tail to not be NULL", NULL, test.tail);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_INSERT_03(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IAFL-ERROR] Expected size to be 'MAXIMUM_INFINITE_FORWARD_LIST'", MAXIMUM_INFINITE_FORWARD_LIST, test.size);
    ASSERT_NEQm("[IAFL-ERROR] Expected tail to not be NULL", NULL, test.tail);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_INSERT_04(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST + 1; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IAFL-ERROR] Expected size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'", MAXIMUM_INFINITE_FORWARD_LIST + 1, test.size);
    ASSERT_NEQm("[IAFL-ERROR] Expected tail to not be NULL", NULL, test.tail);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_INSERT_05(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IAFL-ERROR] element not equal to 42.", 42, get_forward_list(test, 0).sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_INSERT_06(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST - 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST - 1; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IAFL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_INSERT_07(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IAFL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_INSERT_08(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST + 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST + 1; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IAFL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_FIRST_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, }, compare_int);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 42.", 42, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_FIRST_02(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST - 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_FIRST_03(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_FIRST_04(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST + 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_FIRST_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 'MAXIMUM_INFINITE_FORWARD_LIST - 2'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_FIRST_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_FIRST_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 'MAXIMUM_INFINITE_FORWARD_LIST + 1 - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_AT_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 42.", 42, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_AT_02(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST - 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_AT_03(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_AT_04(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < MAXIMUM_INFINITE_FORWARD_LIST + 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_AT_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 'MAXIMUM_INFINITE_FORWARD_LIST - 2'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_AT_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REMOVE_AT_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] element not equal to 'MAXIMUM_INFINITE_FORWARD_LIST + 1 - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_01(void) {
    forward_list_s test = create_forward_list();

    reverse_forward_list(&test); // reversing empty list has no effect, buit is not an error

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_forward_list(&test);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_03(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 1, });

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_04(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 1, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 2, });

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 2.", 2, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_05(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 1, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 2, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 3, });

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 3.", 3, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 'MAXIMUM_INFINITE_FORWARD_LIST' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_REVERSE_08(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IAFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_01(void) {
    forward_list_s test = create_forward_list();

    shift_forward_list(&test, 42); // shifting empty list has no effect, buit is not an error

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_forward_list(&test, 42);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 42.", 42, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size - 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size - 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 'MAXIMUM_INFINITE_FORWARD_LIST' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_08(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size - 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_09(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 0", 0, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_10(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 0", 0, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SHIFT_11(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected first element to be 0", 0, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_SPLICE_01(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IAFL-ERROR] Expected test_one size to be 0", 0, test_one.size);
    ASSERT_EQm("[IAFL-ERROR] Expected test_one tail to be NULL", NULL, test_one.tail);

    ASSERT_EQm("[IAFL-ERROR] Expected test_two size to be 0", 0, test_two.size);
    ASSERT_EQm("[IAFL-ERROR] Expected test_two tail to be NULL", NULL, test_two.tail);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_02(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_forward_list(&test_two, &test_one, 0);

    ASSERT_EQm("[IAFL-ERROR] Expected test_one size to be 0", 0, test_one.size);
    ASSERT_EQm("[IAFL-ERROR] Expected test_one tail to be NULL", NULL, test_one.tail);

    ASSERT_EQm("[IAFL-ERROR] Expected test_two size to be 1", 1, test_two.size);
    ASSERT_NEQm("[IAFL-ERROR] Expected test_two tail to not be NULL", NULL, test_two.tail);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_03(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_04(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_05(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_06(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_07(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_08(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLICE_09(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();
    forward_list_s test_tri = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < (count / 3); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 3); i < 2 * (count / 3); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 2 * (count / 3); i < count; ++i) {
        insert_at_forward_list(&test_tri, test_tri.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    splice_forward_list(&test_one, &test_tri, one_size);
    splice_forward_list(&test_one, &test_two, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);
    destroy_forward_list(&test_tri, NULL);

    PASS();
}

TEST IAFL_SPLICE_10(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();
    forward_list_s test_tri = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < (count / 3); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 3); i < 2 * (count / 3); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 2 * (count / 3); i < count; ++i) {
        insert_at_forward_list(&test_tri, test_tri.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    splice_forward_list(&test_one, &test_tri, one_size);
    splice_forward_list(&test_one, &test_two, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);
    destroy_forward_list(&test_tri, NULL);

    PASS();
}

TEST IAFL_SPLICE_11(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();
    forward_list_s test_tri = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < (count / 3); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 3); i < 2 * (count / 3); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 2 * (count / 3); i < count; ++i) {
        insert_at_forward_list(&test_tri, test_tri.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    splice_forward_list(&test_one, &test_tri, one_size);
    splice_forward_list(&test_one, &test_two, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);
    destroy_forward_list(&test_tri, NULL);

    PASS();
}

TEST IAFL_SPLIT_01(void) {
    forward_list_s test_one = create_forward_list();

    insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    forward_list_s test_two = split_forward_list(&test_one, 0, 0);

    ASSERT_EQm("[IAFL-ERROR] Expected test_one size to be 1.", 1, test_one.size);
    ASSERT_NEQm("[IAFL-ERROR] Expected test_one tail to not be NULL.", NULL, test_one.tail);

    ASSERT_EQm("[IAFL-ERROR] Expected test_two size to be 0.", 0, test_two.size);
    ASSERT_EQm("[IAFL-ERROR] Expected test_two tail to be NULL.", NULL, test_two.tail);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_02(void) {
    forward_list_s test_one = create_forward_list();

    insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    forward_list_s test_two = split_forward_list(&test_one, 0, 1);

    ASSERT_EQm("[IAFL-ERROR] Expected test_one size to be 0.", 0, test_one.size);
    ASSERT_EQm("[IAFL-ERROR] Expected test_one tail to be NULL.", NULL, test_one.tail);

    ASSERT_EQm("[IAFL-ERROR] Expected test_two size to be 1.", 1, test_two.size);
    ASSERT_NEQm("[IAFL-ERROR] Expected test_two tail to not be NULL.", NULL, test_two.tail);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_03(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s test_two = split_forward_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_04(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s test_two = split_forward_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_05(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s test_two = split_forward_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_06(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_07(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_08(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_09(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_10(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_11(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_12(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST - 1'.", one_size, test_two.size);

    for (int i = test_two.size / 2; i < test_two.size; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (test_two.size / 2));
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    for (int i = 0; i < (test_two.size / 2); ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, test_two.size - (test_two.size / 2) + i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_13(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST'.", one_size, test_two.size);

    for (int i = test_two.size / 2; i < test_two.size; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (test_two.size / 2));
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    for (int i = 0; i < (test_two.size / 2); ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, test_two.size - (test_two.size / 2) + i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_SPLIT_14(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'MAXIMUM_INFINITE_FORWARD_LIST + 1'.", one_size, test_two.size);

    for (int i = test_two.size / 2; i < test_two.size; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (test_two.size / 2));
        ASSERT_EQm("[IAFL-ERROR] Expected test_two's element at i to be i", i, element.sub_one);
    }

    for (int i = 0; i < (test_two.size / 2); ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, test_two.size - (test_two.size / 2) + i);
        ASSERT_EQm("[IAFL-ERROR] Expected test_two's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IAFL_GET_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, 0);
    ASSERT_EQm("[IAFL-ERROR] Expected test's first element to be 42", 42, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_GET_02(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_GET_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IAFL_GET_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = MAXIMUM_INFINITE_FORWARD_LIST + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IAFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

SUITE (infinite_allocated_forward_list_test) {
    // create test
    RUN_TEST(IAFL_CREATE_01); RUN_TEST(IAFL_CREATE_02); RUN_TEST(IAFL_CREATE_03); RUN_TEST(IAFL_CREATE_04);
    // insert test
    RUN_TEST(IAFL_INSERT_01); RUN_TEST(IAFL_INSERT_02); RUN_TEST(IAFL_INSERT_03); RUN_TEST(IAFL_INSERT_04);
    RUN_TEST(IAFL_INSERT_05); RUN_TEST(IAFL_INSERT_06); RUN_TEST(IAFL_INSERT_07); RUN_TEST(IAFL_INSERT_08);
    // remove first test
    RUN_TEST(IAFL_REMOVE_FIRST_01); RUN_TEST(IAFL_REMOVE_FIRST_02); RUN_TEST(IAFL_REMOVE_FIRST_03); RUN_TEST(IAFL_REMOVE_FIRST_04);
    RUN_TEST(IAFL_REMOVE_FIRST_05); RUN_TEST(IAFL_REMOVE_FIRST_06); RUN_TEST(IAFL_REMOVE_FIRST_07);
    // remove at test
    RUN_TEST(IAFL_REMOVE_AT_01); RUN_TEST(IAFL_REMOVE_AT_02); RUN_TEST(IAFL_REMOVE_AT_03); RUN_TEST(IAFL_REMOVE_AT_04);
    RUN_TEST(IAFL_REMOVE_AT_05); RUN_TEST(IAFL_REMOVE_AT_06); RUN_TEST(IAFL_REMOVE_AT_07);
    // reverse test
    RUN_TEST(IAFL_REVERSE_01); RUN_TEST(IAFL_REVERSE_02); RUN_TEST(IAFL_REVERSE_03); RUN_TEST(IAFL_REVERSE_04);
    RUN_TEST(IAFL_REVERSE_05); RUN_TEST(IAFL_REVERSE_06); RUN_TEST(IAFL_REVERSE_07); RUN_TEST(IAFL_REVERSE_08);
    // shift next test
    RUN_TEST(IAFL_SHIFT_01); RUN_TEST(IAFL_SHIFT_02); RUN_TEST(IAFL_SHIFT_03); RUN_TEST(IAFL_SHIFT_04);
    RUN_TEST(IAFL_SHIFT_05); RUN_TEST(IAFL_SHIFT_06); RUN_TEST(IAFL_SHIFT_07); RUN_TEST(IAFL_SHIFT_08);
    RUN_TEST(IAFL_SHIFT_09); RUN_TEST(IAFL_SHIFT_10); RUN_TEST(IAFL_SHIFT_11);
    // splice test
    RUN_TEST(IAFL_SPLICE_01); RUN_TEST(IAFL_SPLICE_02); RUN_TEST(IAFL_SPLICE_03); RUN_TEST(IAFL_SPLICE_04);
    RUN_TEST(IAFL_SPLICE_05); RUN_TEST(IAFL_SPLICE_06); RUN_TEST(IAFL_SPLICE_07); RUN_TEST(IAFL_SPLICE_08);
    RUN_TEST(IAFL_SPLICE_09); RUN_TEST(IAFL_SPLICE_10); RUN_TEST(IAFL_SPLICE_11);
    // split test
    RUN_TEST(IAFL_SPLIT_01); RUN_TEST(IAFL_SPLIT_02); RUN_TEST(IAFL_SPLIT_03); RUN_TEST(IAFL_SPLIT_04);
    RUN_TEST(IAFL_SPLIT_05); RUN_TEST(IAFL_SPLIT_06); RUN_TEST(IAFL_SPLIT_07); RUN_TEST(IAFL_SPLIT_08);
    RUN_TEST(IAFL_SPLIT_09); RUN_TEST(IAFL_SPLIT_10); RUN_TEST(IAFL_SPLIT_11); RUN_TEST(IAFL_SPLIT_12);
    RUN_TEST(IAFL_SPLIT_13); RUN_TEST(IAFL_SPLIT_14);
    // get test
    RUN_TEST(IAFL_GET_01); RUN_TEST(IAFL_GET_02); RUN_TEST(IAFL_GET_03); RUN_TEST(IAFL_GET_04);
}
