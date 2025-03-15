#include "straight_list_test.h"

#define STRAIGHT_LIST_MODE INFINITE_REALLOC_STRAIGHT_LIST
#define REALLOC_STRAIGHT_LIST_CHUNK (1 << 4)
#include <straight_list/straight_list.h>

/// tests if create followed by destroy works
TEST IRSL_CREATE_01(void) {
    straight_list_s test = create_straight_list();
    destroy_straight_list(&test, NULL);

    PASS();
}

/// tests if create followed by destroy with function pointer works
TEST IRSL_CREATE_02(void) {
    straight_list_s test = create_straight_list();
    destroy_straight_list(&test, destroy_element);

    PASS();
}

/// creates and checks if list ahs size and hea set to zero and if destroy works properly
TEST IRSL_CREATE_03(void) {
    straight_list_s test = create_straight_list();

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    destroy_straight_list(&test, NULL);

    PASS();
}

/// creates and checks if list ahs size and hea set to zero and if destroy with function pointer works properly
TEST IRSL_CREATE_04(void) {
    straight_list_s test = create_straight_list();

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    destroy_straight_list(&test, destroy_element);

    PASS();
}

/// checks if list is destroyed properly with list size set to zero and head set to NULL
TEST IRSL_DESTROY_01(void) {
    straight_list_s test = create_straight_list();

    destroy_straight_list(&test, NULL);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed properly after inserting an element with list size set to zero and head set to NULL
TEST IRSL_DESTROY_02(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_straight_list(&test, NULL);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed properly after inserting 'REALLOC_STRAIGHT_LIST_CHUNK - 1' elements with list size
/// set to zero and head set to NULL
TEST IRSL_DESTROY_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    destroy_straight_list(&test, NULL);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed properly after inserting 'REALLOC_STRAIGHT_LIST_CHUNK' elements with list size
/// set to zero and head set to NULL
TEST IRSL_DESTROY_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    destroy_straight_list(&test, NULL);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed properly after inserting 'REALLOC_STRAIGHT_LIST_CHUNK + 1' elements with list size
/// set to zero and head set to NULL
TEST IRSL_DESTROY_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    destroy_straight_list(&test, NULL);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed with fuinction pointer properly, with list size set to zero and head set to NULL
TEST IRSL_DESTROY_06(void) {
    straight_list_s test = create_straight_list();

    destroy_straight_list(&test, destroy_element);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed with function pointer properly after inserting an element with list size set to zero
/// and head set to NULL
TEST IRSL_DESTROY_07(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, 0, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_straight_list(&test, destroy_element);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed with function pointer properly after inserting 'REALLOC_STRAIGHT_LIST_CHUNK - 1'
/// elements with list size set to zero and head set to NULL
TEST IRSL_DESTROY_08(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_straight_list(&test, destroy_element);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed with function pointer properly after inserting 'REALLOC_STRAIGHT_LIST_CHUNK'
/// elements with list size set to zero and head set to NULL
TEST IRSL_DESTROY_09(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_straight_list(&test, destroy_element);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list is destroyed with function pointer properly after inserting 'REALLOC_STRAIGHT_LIST_CHUNK + 1'
/// elements with list size set to zero and head set to NULL
TEST IRSL_DESTROY_10(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_straight_list(&test, destroy_element);

    ASSERT_EQm("[IRSL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_EQm("[IRSL-ERROR] test list's elements is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRSL-ERROR] test list's next is not NULL.", NULL, test.next);

    PASS();
}

/// checks if list size is one and head has allocated memory after inserting one element
TEST IRSL_INSERT_01(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRSL-ERROR] Expected size to be 1", 1, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_NEQm("[IRSL-ERROR] test list's elements is NULL.", NULL, test.elements);
    ASSERT_NEQm("[IRSL-ERROR] test list's next is NULL.", NULL, test.next);

    destroy_straight_list(&test, NULL);

    PASS();
}

/// checks if list size is 'REALLOC_STRAIGHT_LIST_CHUNK - 1' and head has allocated memory after inserting
/// 'REALLOC_STRAIGHT_LIST_CHUNK - 1' element
TEST IRSL_INSERT_02(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRSL-ERROR] Expected size to be 'REALLOC_STRAIGHT_LIST_CHUNK - 1'", count, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_NEQm("[IRSL-ERROR] test list's elements is NULL.", NULL, test.elements);
    ASSERT_NEQm("[IRSL-ERROR] test list's next is NULL.", NULL, test.next);

    destroy_straight_list(&test, NULL);

    PASS();
}

/// checks if list size is 'REALLOC_STRAIGHT_LIST_CHUNK' and head has allocated memory after inserting
/// 'REALLOC_STRAIGHT_LIST_CHUNK' element
TEST IRSL_INSERT_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRSL-ERROR] Expected size to be 'REALLOC_STRAIGHT_LIST_CHUNK'", count, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_NEQm("[IRSL-ERROR] test list's elements is NULL.", NULL, test.elements);
    ASSERT_NEQm("[IRSL-ERROR] test list's next is NULL.", NULL, test.next);

    destroy_straight_list(&test, NULL);

    PASS();
}

/// checks if list size is 'REALLOC_STRAIGHT_LIST_CHUNK + 1' and head has allocated memory after inserting
/// 'REALLOC_STRAIGHT_LIST_CHUNK + 1' element
TEST IRSL_INSERT_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, 0, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRSL-ERROR] Expected size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'", count, test.size);
    ASSERT_EQm("[IRSL-ERROR] test list's empty size is not 0.", 0, test.empty_size);
    ASSERT_NEQm("[IRSL-ERROR] test list's elements is NULL.", NULL, test.elements);
    ASSERT_NEQm("[IRSL-ERROR] test list's next is NULL.", NULL, test.next);

    destroy_straight_list(&test, NULL);

    PASS();
}

/// checks if inserted element is at correct index
TEST IRSL_INSERT_05(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRSL-ERROR] element not equal to 42.", 42, get_straight_list(test, 0).sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

/// checks if 'REALLOC_STRAIGHT_LIST_CHUNK - 1' inserted elements are at correct index
TEST IRSL_INSERT_06(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK - 1; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRSL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);

    PASS();
}

/// checks if 'REALLOC_STRAIGHT_LIST_CHUNK' inserted elements are at correct index
TEST IRSL_INSERT_07(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRSL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);

    PASS();
}

/// checks if 'REALLOC_STRAIGHT_LIST_CHUNK + 1' inserted elements are at correct index
TEST IRSL_INSERT_08(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK + 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK + 1; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRSL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_FIRST_01(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    const STRAIGHT_LIST_DATA_TYPE element = remove_first_straight_list(&test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, }, compare_int);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 42.", 42, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_FIRST_02(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_first_straight_list(&test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_FIRST_03(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_first_straight_list(&test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_FIRST_04(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK + 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_first_straight_list(&test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_FIRST_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_first_straight_list(&test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 'REALLOC_STRAIGHT_LIST_CHUNK - 2'.", count - 1, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_FIRST_06(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_first_straight_list(&test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 'REALLOC_STRAIGHT_LIST_CHUNK - 1'.", count - 1, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_FIRST_07(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_first_straight_list(&test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 'REALLOC_STRAIGHT_LIST_CHUNK + 1 - 1'.", count - 1, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_AT_01(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    const STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 42.", 42, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_AT_02(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK - 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_AT_03(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_AT_04(void) {
    straight_list_s test = create_straight_list();

    for (size_t i = 0; i < REALLOC_STRAIGHT_LIST_CHUNK + 1; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, 0);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_AT_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, test.size - 1);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 'REALLOC_STRAIGHT_LIST_CHUNK - 2'.", count - 1, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_AT_06(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, test.size - 1);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 'REALLOC_STRAIGHT_LIST_CHUNK - 1'.", count - 1, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REMOVE_AT_07(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const STRAIGHT_LIST_DATA_TYPE element = remove_at_straight_list(&test, test.size - 1);
    ASSERT_EQm("[IRSL-ERROR] element not equal to 'REALLOC_STRAIGHT_LIST_CHUNK + 1 - 1'.", count - 1, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_01(void) {
    straight_list_s test = create_straight_list();

    reverse_straight_list(&test); // reversing empty list has no effect, buit is not an error

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_02(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_straight_list(&test);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_03(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 1, });

    reverse_straight_list(&test);

    const STRAIGHT_LIST_DATA_TYPE first = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE last = get_straight_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_04(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 1, });
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 2, });

    reverse_straight_list(&test);

    const STRAIGHT_LIST_DATA_TYPE first = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE last = get_straight_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 2.", 2, first.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_05(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 1, });
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 2, });
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 3, });

    reverse_straight_list(&test);

    const STRAIGHT_LIST_DATA_TYPE first = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE last = get_straight_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 3.", 3, first.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_06(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_straight_list(&test);

    const STRAIGHT_LIST_DATA_TYPE first = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE last = get_straight_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_STRAIGHT_LIST_CHUNK - 1' - 1.", count - 1, first.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_07(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_straight_list(&test);

    const STRAIGHT_LIST_DATA_TYPE first = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE last = get_straight_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_STRAIGHT_LIST_CHUNK' - 1.", count - 1, first.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_REVERSE_08(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_straight_list(&test);

    const STRAIGHT_LIST_DATA_TYPE first = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE last = get_straight_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1' - 1.", count - 1, first.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_SPLICE_01(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    splice_straight_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 0", 0, test_one.size);
    ASSERT_EQm("[IRSL-ERROR] test_one list's elements is NULL.", NULL, test_one.elements);
    ASSERT_EQm("[IRSL-ERROR] test_one list's next is NULL.", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 0", 0, test_two.size);
    ASSERT_EQm("[IRSL-ERROR] test_two list's elements is NULL.", NULL, test_two.elements);
    ASSERT_EQm("[IRSL-ERROR] test_two list's next is NULL.", NULL, test_two.next);

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_02(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_straight_list(&test_two, &test_one, 0);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 0", 0, test_one.size);
    ASSERT_EQm("[IRSL-ERROR] test_one list's elements not is NULL.", NULL, test_one.elements);
    ASSERT_EQm("[IRSL-ERROR] test_one list's next not is NULL.", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 1", 1, test_two.size);
    ASSERT_NEQm("[IRSL-ERROR] test_two list's elements is NULL.", NULL, test_two.elements);
    ASSERT_NEQm("[IRSL-ERROR] test_two list's next is NULL.", NULL, test_two.next);

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_03(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK - 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_04(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_05(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_06(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK - 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_07(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_08(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_straight_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLICE_09(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();
    straight_list_s test_tri = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < (count / 3); ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 3); i < 2 * (count / 3); ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 2 * (count / 3); i < count; ++i) {
        insert_at_straight_list(&test_tri, test_tri.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    splice_straight_list(&test_one, &test_tri, one_size);
    splice_straight_list(&test_one, &test_two, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);
    destroy_straight_list(&test_tri, NULL);

    PASS();
}

TEST IRSL_SPLICE_10(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();
    straight_list_s test_tri = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < (count / 3); ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 3); i < 2 * (count / 3); ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 2 * (count / 3); i < count; ++i) {
        insert_at_straight_list(&test_tri, test_tri.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    splice_straight_list(&test_one, &test_tri, one_size);
    splice_straight_list(&test_one, &test_two, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);
    destroy_straight_list(&test_tri, NULL);

    PASS();
}

TEST IRSL_SPLICE_11(void) {
    straight_list_s test_one = create_straight_list();
    straight_list_s test_two = create_straight_list();
    straight_list_s test_tri = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < (count / 3); ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 3); i < 2 * (count / 3); ++i) {
        insert_at_straight_list(&test_two, test_two.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 2 * (count / 3); i < count; ++i) {
        insert_at_straight_list(&test_tri, test_tri.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    splice_straight_list(&test_one, &test_tri, one_size);
    splice_straight_list(&test_one, &test_two, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);
    destroy_straight_list(&test_tri, NULL);

    PASS();
}

TEST IRSL_SPLIT_01(void) {
    straight_list_s test_one = create_straight_list();

    insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    straight_list_s test_two = split_straight_list(&test_one, 0, 0);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 1.", 1, test_one.size);
    ASSERT_NEQm("[IRSL-ERROR] test_one list's elements is NULL.", NULL, test_one.elements);
    ASSERT_NEQm("[IRSL-ERROR] test_one list's next is NULL.", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 0.", 0, test_two.size);
    ASSERT_EQm("[IRSL-ERROR] test_two list's elements not is NULL.", NULL, test_two.elements);
    ASSERT_EQm("[IRSL-ERROR] test_two list's next not is NULL.", NULL, test_two.next);

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_02(void) {
    straight_list_s test_one = create_straight_list();

    insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    straight_list_s test_two = split_straight_list(&test_one, 0, 1);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 0.", 0, test_one.size);
    ASSERT_EQm("[IRSL-ERROR] test_one list's elements not is NULL.", NULL, test_one.elements);
    ASSERT_EQm("[IRSL-ERROR] test_one list's next not is NULL.", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 1.", 1, test_two.size);
    ASSERT_NEQm("[IRSL-ERROR] test_two list's elements is NULL.", NULL, test_two.elements);
    ASSERT_NEQm("[IRSL-ERROR] test_two list's next is NULL.", NULL, test_two.next);

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_03(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s test_two = split_straight_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK - 1'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_04(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s test_two = split_straight_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_05(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s test_two = split_straight_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_06(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    straight_list_s test_two = split_straight_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK - 1'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_07(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    straight_list_s test_two = split_straight_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_08(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    straight_list_s test_two = split_straight_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_09(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    straight_list_s test_two = split_straight_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK - 1'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_10(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    straight_list_s test_two = split_straight_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_SPLIT_11(void) {
    straight_list_s test_one = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test_one, test_one.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    straight_list_s test_two = split_straight_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_STRAIGHT_LIST_CHUNK + 1'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_straight_list(&test_one, NULL);
    destroy_straight_list(&test_two, NULL);

    PASS();
}

TEST IRSL_GET_01(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected test's first element to be 42", 42, element.sub_one);

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_GET_02(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_GET_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_GET_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_IS_EMPTY_01(void) {
    straight_list_s test = create_straight_list();

    ASSERTm("[IRFL-ERROR] Expected list to be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_IS_EMPTY_02(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_IS_EMPTY_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_IS_EMPTY_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_IS_EMPTY_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_straight_list(test));

    destroy_straight_list(&test, NULL);

    PASS();
}

TEST IRSL_COPY_01(void) {
    straight_list_s test = create_straight_list();
    straight_list_s copy = copy_straight_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_EQm("[IRFL-ERROR] Expected copy elements to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected copy next to be NULL.", NULL, copy.next);

    destroy_straight_list(&test, NULL);
    destroy_straight_list(&copy, NULL);

    PASS();
}

TEST IRSL_COPY_02(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    straight_list_s copy = copy_straight_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);

    destroy_straight_list(&test, NULL);
    destroy_straight_list(&copy, NULL);

    PASS();
}

TEST IRSL_COPY_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s copy = copy_straight_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    destroy_straight_list(&copy, NULL);

    PASS();
}

TEST IRSL_COPY_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s copy = copy_straight_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    destroy_straight_list(&copy, NULL);

    PASS();
}

TEST IRSL_COPY_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    straight_list_s copy = copy_straight_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    destroy_straight_list(&copy, NULL);

    PASS();
}

TEST IRSL_COPY_06(void) {
    straight_list_s test = create_straight_list();
    straight_list_s copy = copy_straight_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_EQm("[IRFL-ERROR] Expected copy elements to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected copy next to be NULL.", NULL, copy.next);

    destroy_straight_list(&test, destroy_element);
    destroy_straight_list(&copy, destroy_element);

    PASS();
}

TEST IRSL_COPY_07(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    straight_list_s copy = copy_straight_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, 0);
    const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, 0);
    ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_straight_list(&test, destroy_element);
    destroy_straight_list(&copy, destroy_element);

    PASS();
}

TEST IRSL_COPY_08(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    straight_list_s copy = copy_straight_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_element);
    destroy_straight_list(&copy, destroy_element);

    PASS();
}

TEST IRSL_COPY_09(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    straight_list_s copy = copy_straight_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_element);
    destroy_straight_list(&copy, destroy_element);

    PASS();
}

TEST IRSL_COPY_10(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, copy_element((STRAIGHT_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    straight_list_s copy = copy_straight_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy elements to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy next to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE test_element = get_straight_list(test, i);
        const STRAIGHT_LIST_DATA_TYPE copy_element = get_straight_list(copy, i);
        ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_straight_list(&test, destroy_element);
    destroy_straight_list(&copy, destroy_element);

    PASS();
}

TEST IRSL_FOREVERY_01(void) {
    straight_list_s test = create_straight_list();

    forevery_straight_list(&test, sort_int, NULL);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREVERY_02(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    forevery_straight_list(&test, sort_int, NULL);

    const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", 42, element.sub_one);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREVERY_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - i - 1, });
    }
    if (count & 0X01) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = (count / 2), });
    }

    forevery_straight_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREVERY_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - i - 1, });
    }
    if (count & 0X01) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = (count / 2), });
    }

    forevery_straight_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREVERY_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - i - 1, });
    }
    if (count & 0X01) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = (count / 2), });
    }

    forevery_straight_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", i, element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_01(void) {
    straight_list_s test = create_straight_list();

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be false.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, }, NULL));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_02(void) {
    straight_list_s test = create_straight_list();
    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, }, NULL));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_06(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_07(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_08(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_09(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_10(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_11(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_12(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_13(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_14(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_15(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 1; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_16(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 1; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_17(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 1; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_18(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_19(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_BINARY_SEARCH_20(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forevery_straight_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_straight_list(test, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_CLEAR_01(void) {
    straight_list_s test = create_straight_list();

    clear_straight_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_CLEAR_02(void) {
    straight_list_s test = create_straight_list();

    insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = 42, });

    clear_straight_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_CLEAR_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    clear_straight_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_CLEAR_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    clear_straight_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_CLEAR_05(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    clear_straight_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREACH_01(void) {
    straight_list_s test = create_straight_list();

    int arg = 1;
    foreach_straight_list(&test, operation_int, &arg);

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREACH_02(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int arg = 1;
    foreach_straight_list(&test, operation_int, &arg);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected incremented ith element.", i + 1, element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREACH_03(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int arg = 1;
    foreach_straight_list(&test, operation_int, &arg);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected incremented ith element.", i + 1, element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

TEST IRSL_FOREACH_04(void) {
    straight_list_s test = create_straight_list();

    const size_t count = REALLOC_STRAIGHT_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_straight_list(&test, test.size, (STRAIGHT_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int arg = 1;
    foreach_straight_list(&test, operation_int, &arg);

    for (size_t i = 0; i < count; ++i) {
        const STRAIGHT_LIST_DATA_TYPE element = get_straight_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected incremented ith element.", i + 1, element.sub_one);
    }

    destroy_straight_list(&test, NULL);
    PASS();
}

SUITE (infinite_realloc_straight_list_test) {
    // create test
    RUN_TEST(IRSL_CREATE_01); RUN_TEST(IRSL_CREATE_02); RUN_TEST(IRSL_CREATE_03); RUN_TEST(IRSL_CREATE_04);
    // destroy test
    RUN_TEST(IRSL_DESTROY_01); RUN_TEST(IRSL_DESTROY_02); RUN_TEST(IRSL_DESTROY_03); RUN_TEST(IRSL_DESTROY_04);
    RUN_TEST(IRSL_DESTROY_05); RUN_TEST(IRSL_DESTROY_06); RUN_TEST(IRSL_DESTROY_07); RUN_TEST(IRSL_DESTROY_08);
    RUN_TEST(IRSL_DESTROY_09); RUN_TEST(IRSL_DESTROY_10);
    // insert test
    RUN_TEST(IRSL_INSERT_01); RUN_TEST(IRSL_INSERT_02); RUN_TEST(IRSL_INSERT_03); RUN_TEST(IRSL_INSERT_04);
    RUN_TEST(IRSL_INSERT_05); RUN_TEST(IRSL_INSERT_06); RUN_TEST(IRSL_INSERT_07); RUN_TEST(IRSL_INSERT_08);
    // remove first test
    RUN_TEST(IRSL_REMOVE_FIRST_01); RUN_TEST(IRSL_REMOVE_FIRST_02); RUN_TEST(IRSL_REMOVE_FIRST_03); RUN_TEST(IRSL_REMOVE_FIRST_04);
    RUN_TEST(IRSL_REMOVE_FIRST_05); RUN_TEST(IRSL_REMOVE_FIRST_06); RUN_TEST(IRSL_REMOVE_FIRST_07);
    // remove at test
    RUN_TEST(IRSL_REMOVE_AT_01); RUN_TEST(IRSL_REMOVE_AT_02); RUN_TEST(IRSL_REMOVE_AT_03); RUN_TEST(IRSL_REMOVE_AT_04);
    RUN_TEST(IRSL_REMOVE_AT_05); RUN_TEST(IRSL_REMOVE_AT_06); RUN_TEST(IRSL_REMOVE_AT_07);
    // reverse test
    RUN_TEST(IRSL_REVERSE_01); RUN_TEST(IRSL_REVERSE_02); RUN_TEST(IRSL_REVERSE_03); RUN_TEST(IRSL_REVERSE_04);
    RUN_TEST(IRSL_REVERSE_05); RUN_TEST(IRSL_REVERSE_06); RUN_TEST(IRSL_REVERSE_07); RUN_TEST(IRSL_REVERSE_08);
    // splice test
    RUN_TEST(IRSL_SPLICE_01); RUN_TEST(IRSL_SPLICE_02); RUN_TEST(IRSL_SPLICE_03); RUN_TEST(IRSL_SPLICE_04);
    RUN_TEST(IRSL_SPLICE_05); RUN_TEST(IRSL_SPLICE_06); RUN_TEST(IRSL_SPLICE_07); RUN_TEST(IRSL_SPLICE_08);
    RUN_TEST(IRSL_SPLICE_09); RUN_TEST(IRSL_SPLICE_10); RUN_TEST(IRSL_SPLICE_11);
    // split test
    RUN_TEST(IRSL_SPLIT_01); RUN_TEST(IRSL_SPLIT_02); RUN_TEST(IRSL_SPLIT_03); RUN_TEST(IRSL_SPLIT_04);
    RUN_TEST(IRSL_SPLIT_05); RUN_TEST(IRSL_SPLIT_06); RUN_TEST(IRSL_SPLIT_07); RUN_TEST(IRSL_SPLIT_08);
    RUN_TEST(IRSL_SPLIT_09); RUN_TEST(IRSL_SPLIT_10); RUN_TEST(IRSL_SPLIT_11);
    // get test
    RUN_TEST(IRSL_GET_01); RUN_TEST(IRSL_GET_02); RUN_TEST(IRSL_GET_03); RUN_TEST(IRSL_GET_04);
    // is empty test
    RUN_TEST(IRSL_IS_EMPTY_01); RUN_TEST(IRSL_IS_EMPTY_02); RUN_TEST(IRSL_IS_EMPTY_03); RUN_TEST(IRSL_IS_EMPTY_04);
    RUN_TEST(IRSL_IS_EMPTY_05);
    // copy test
    RUN_TEST(IRSL_COPY_01); RUN_TEST(IRSL_COPY_02); RUN_TEST(IRSL_COPY_03); RUN_TEST(IRSL_COPY_04);
    RUN_TEST(IRSL_COPY_05); RUN_TEST(IRSL_COPY_06); RUN_TEST(IRSL_COPY_07); RUN_TEST(IRSL_COPY_08);
    RUN_TEST(IRSL_COPY_09); RUN_TEST(IRSL_COPY_10);
    // forevery test
    RUN_TEST(IRSL_FOREVERY_01); RUN_TEST(IRSL_FOREVERY_02); RUN_TEST(IRSL_FOREVERY_03); RUN_TEST(IRSL_FOREVERY_04);
    RUN_TEST(IRSL_FOREVERY_05);
    // binary search test
    RUN_TEST(IRSL_BINARY_SEARCH_01); RUN_TEST(IRSL_BINARY_SEARCH_02); RUN_TEST(IRSL_BINARY_SEARCH_03); RUN_TEST(IRSL_BINARY_SEARCH_04);
    RUN_TEST(IRSL_BINARY_SEARCH_05); RUN_TEST(IRSL_BINARY_SEARCH_06); RUN_TEST(IRSL_BINARY_SEARCH_07); RUN_TEST(IRSL_BINARY_SEARCH_08);
    RUN_TEST(IRSL_BINARY_SEARCH_09); RUN_TEST(IRSL_BINARY_SEARCH_10); RUN_TEST(IRSL_BINARY_SEARCH_11); RUN_TEST(IRSL_BINARY_SEARCH_12);
    RUN_TEST(IRSL_BINARY_SEARCH_13); RUN_TEST(IRSL_BINARY_SEARCH_14); RUN_TEST(IRSL_BINARY_SEARCH_15); RUN_TEST(IRSL_BINARY_SEARCH_16);
    RUN_TEST(IRSL_BINARY_SEARCH_17); RUN_TEST(IRSL_BINARY_SEARCH_18); RUN_TEST(IRSL_BINARY_SEARCH_19); RUN_TEST(IRSL_BINARY_SEARCH_20);
    // clear test
    RUN_TEST(IRSL_CLEAR_01); RUN_TEST(IRSL_CLEAR_02); RUN_TEST(IRSL_CLEAR_03); RUN_TEST(IRSL_CLEAR_04);
    RUN_TEST(IRSL_CLEAR_05);
    // foreach test
    RUN_TEST(IRSL_FOREACH_01); RUN_TEST(IRSL_FOREACH_02); RUN_TEST(IRSL_FOREACH_03); RUN_TEST(IRSL_FOREACH_04);
}
