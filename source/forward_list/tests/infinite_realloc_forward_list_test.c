#include "forward_list_test.h"

#define FORWARD_LIST_MODE INFINITE_REALLOC_FORWARD_LIST
#define REALLOC_FORWARD_LIST_CHUNK (1 << 4)
#include <forward_list/forward_list.h>

TEST IRFL_CREATE_01(void) {
    forward_list_s test = create_forward_list();
    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_CREATE_02(void) {
    forward_list_s test = create_forward_list();
    destroy_forward_list(&test, destroy_element);

    PASS();
}

TEST IRFL_CREATE_03(void) {
    forward_list_s test = create_forward_list();

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's size is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's size is not NULL.", NULL, test.next);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_CREATE_04(void) {
    forward_list_s test = create_forward_list();

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's size is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's size is not NULL.", NULL, test.next);

    destroy_forward_list(&test, destroy_element);

    PASS();
}

TEST IRFL_DESTROY_01(void) {
    forward_list_s test = create_forward_list();

    destroy_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    destroy_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    destroy_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    destroy_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    destroy_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_06(void) {
    forward_list_s test = create_forward_list();

    destroy_forward_list(&test, destroy_element);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_07(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, 0, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    destroy_forward_list(&test, destroy_element);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_08(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_forward_list(&test, destroy_element);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_09(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_forward_list(&test, destroy_element);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_DESTROY_10(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    destroy_forward_list(&test, destroy_element);

    ASSERT_EQm("[IRFL-ERROR] test list's size is not 0.", 0, test.size);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.elements);
    ASSERT_EQm("[IRFL-ERROR] test list's tail is not NULL.", NULL, test.next);

    PASS();
}

TEST IRFL_INSERT_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRFL-ERROR] Expected size to be 1", 1, test.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.next);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_INSERT_02(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRFL-ERROR] Expected size to be 'REALLOC_FORWARD_LIST_CHUNK - 1'", count, test.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.next);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_INSERT_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRFL-ERROR] Expected size to be 'REALLOC_FORWARD_LIST_CHUNK'", count, test.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.next);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_INSERT_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, 0, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRFL-ERROR] Expected size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'", count, test.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected tail to not be NULL", NULL, test.next);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_INSERT_05(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRFL-ERROR] element not equal to 42.", 42, get_forward_list(test, 0).sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_INSERT_06(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK - 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK - 1; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_INSERT_07(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_INSERT_08(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK + 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK + 1; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] element not equal to i.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_FIRST_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, }, compare_int);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 42.", 42, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_FIRST_02(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK - 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_FIRST_03(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_FIRST_04(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK + 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_FIRST_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 'REALLOC_FORWARD_LIST_CHUNK - 2'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_FIRST_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 'REALLOC_FORWARD_LIST_CHUNK - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_FIRST_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_first_forward_list(&test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 'REALLOC_FORWARD_LIST_CHUNK + 1 - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_AT_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 42.", 42, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_AT_02(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK - 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_AT_03(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_AT_04(void) {
    forward_list_s test = create_forward_list();

    for (size_t i = 0; i < REALLOC_FORWARD_LIST_CHUNK + 1; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, 0);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 0.", 0, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_AT_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 'REALLOC_FORWARD_LIST_CHUNK - 2'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_AT_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 'REALLOC_FORWARD_LIST_CHUNK - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REMOVE_AT_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const FORWARD_LIST_DATA_TYPE element = remove_at_forward_list(&test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] element not equal to 'REALLOC_FORWARD_LIST_CHUNK + 1 - 1'.", count - 1, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_01(void) {
    forward_list_s test = create_forward_list();

    reverse_forward_list(&test); // reversing empty list has no effect, buit is not an error

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    reverse_forward_list(&test);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_03(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 1, });

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_04(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 1, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 2, });

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 2.", 2, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_05(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 1, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 2, });
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 3, });

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 3.", 3, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_FORWARD_LIST_CHUNK - 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_FORWARD_LIST_CHUNK' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_REVERSE_08(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    reverse_forward_list(&test);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE last = get_forward_list(test, test.size - 1);
    ASSERT_EQm("[IRFL-ERROR] Expected last element to be 0.", 0, last.sub_one);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_FORWARD_LIST_CHUNK + 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_01(void) {
    forward_list_s test = create_forward_list();

    shift_forward_list(&test, 42); // shifting empty list has no effect, buit is not an error

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    shift_forward_list(&test, 42);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 42.", 42, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 1.", 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size - 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_FORWARD_LIST_CHUNK - 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size - 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_FORWARD_LIST_CHUNK' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_08(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size - 1);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 'REALLOC_FORWARD_LIST_CHUNK + 1' - 1.", count - 1, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_09(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 0", 0, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_10(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 0", 0, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SHIFT_11(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    shift_forward_list(&test, test.size);

    const FORWARD_LIST_DATA_TYPE first = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected first element to be 0", 0, first.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_SPLICE_01(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 0", 0, test_one.size);
    ASSERT_EQm("[IRFL-ERROR] Expected test_one tail to be NULL", NULL, test_one.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected test_one tail to be NULL", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 0", 0, test_two.size);
    ASSERT_EQm("[IRFL-ERROR] Expected test_two tail to be NULL", NULL, test_two.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected test_two tail to be NULL", NULL, test_two.next);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_02(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    splice_forward_list(&test_two, &test_one, 0);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 0", 0, test_one.size);
    ASSERT_EQm("[IRFL-ERROR] Expected test_one tail to be NULL", NULL, test_one.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected test_one tail to be NULL", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 1", 1, test_two.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected test_two tail to not be NULL", NULL, test_two.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected test_two tail to not be NULL", NULL, test_two.next);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_03(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK - 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_04(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_05(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_06(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK - 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_07(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_08(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = (count / 2); i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test_two, test_two.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    splice_forward_list(&test_one, &test_two, 0);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLICE_09(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();
    forward_list_s test_tri = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
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

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);
    destroy_forward_list(&test_tri, NULL);

    PASS();
}

TEST IRFL_SPLICE_10(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();
    forward_list_s test_tri = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
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

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);
    destroy_forward_list(&test_tri, NULL);

    PASS();
}

TEST IRFL_SPLICE_11(void) {
    forward_list_s test_one = create_forward_list();
    forward_list_s test_two = create_forward_list();
    forward_list_s test_tri = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
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

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", count, test_one.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_one, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);
    destroy_forward_list(&test_tri, NULL);

    PASS();
}

TEST IRFL_SPLIT_01(void) {
    forward_list_s test_one = create_forward_list();

    insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    forward_list_s test_two = split_forward_list(&test_one, 0, 0);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 1.", 1, test_one.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, test_one.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 0.", 0, test_two.size);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, test_two.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, test_two.next);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_02(void) {
    forward_list_s test_one = create_forward_list();

    insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    forward_list_s test_two = split_forward_list(&test_one, 0, 1);

    ASSERT_EQm("[IRFL-ERROR] Expected test_one size to be 0.", 0, test_one.size);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, test_one.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, test_one.next);

    ASSERT_EQm("[IRFL-ERROR] Expected test_two size to be 1.", 1, test_two.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, test_two.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, test_two.next);

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_03(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s test_two = split_forward_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK - 1'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_04(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s test_two = split_forward_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_05(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s test_two = split_forward_list(&test_one, 0, test_one.size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", count, test_two.size);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_06(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK - 1'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_07(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_08(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, 0, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", one_size / 2, test_two.size);

    for (int i = 0; i < one_size / 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_09(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK - 1'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_10(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_11(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size / 2);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", one_size / 2, test_two.size);

    for (int i = one_size / 2; i < (one_size / 2) * 2; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (one_size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_12(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK - 1'.", one_size, test_two.size);

    for (int i = test_two.size / 2; i < test_two.size; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (test_two.size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    for (int i = 0; i < (test_two.size / 2); ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, test_two.size - (test_two.size / 2) + i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_13(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK'.", one_size, test_two.size);

    for (int i = test_two.size / 2; i < test_two.size; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (test_two.size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    for (int i = 0; i < (test_two.size / 2); ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, test_two.size - (test_two.size / 2) + i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_one's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_SPLIT_14(void) {
    forward_list_s test_one = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test_one, test_one.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    const size_t one_size = test_one.size;
    forward_list_s test_two = split_forward_list(&test_one, one_size / 2, one_size);

    ASSERT_EQm("[IADL-ERROR] Expected test_one's size to be 'REALLOC_FORWARD_LIST_CHUNK + 1'.", one_size, test_two.size);

    for (int i = test_two.size / 2; i < test_two.size; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, i - (test_two.size / 2));
        ASSERT_EQm("[IRFL-ERROR] Expected test_two's element at i to be i", i, element.sub_one);
    }

    for (int i = 0; i < (test_two.size / 2); ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test_two, test_two.size - (test_two.size / 2) + i);
        ASSERT_EQm("[IRFL-ERROR] Expected test_two's element at i to be i", i, element.sub_one);
    }

    destroy_forward_list(&test_one, NULL);
    destroy_forward_list(&test_two, NULL);

    PASS();
}

TEST IRFL_GET_01(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected test's first element to be 42", 42, element.sub_one);

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_GET_02(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_GET_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_GET_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected test's ith element to be i", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_IS_EMPTY_01(void) {
    forward_list_s test = create_forward_list();

    ASSERTm("[IRFL-ERROR] Expected list to be empty.", is_empty_forward_list(test));

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_IS_EMPTY_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_forward_list(test));

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_IS_EMPTY_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_forward_list(test));

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_IS_EMPTY_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_forward_list(test));

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_IS_EMPTY_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[IRFL-ERROR] Expected list to not be empty.", is_empty_forward_list(test));

    destroy_forward_list(&test, NULL);

    PASS();
}

TEST IRFL_COPY_01(void) {
    forward_list_s test = create_forward_list();
    forward_list_s copy = copy_forward_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, copy.next);

    destroy_forward_list(&test, NULL);
    destroy_forward_list(&copy, NULL);

    PASS();
}

TEST IRFL_COPY_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    forward_list_s copy = copy_forward_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);

    destroy_forward_list(&test, NULL);
    destroy_forward_list(&copy, NULL);

    PASS();
}

TEST IRFL_COPY_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s copy = copy_forward_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, i);
        const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    destroy_forward_list(&copy, NULL);

    PASS();
}

TEST IRFL_COPY_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s copy = copy_forward_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, i);
        const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    destroy_forward_list(&copy, NULL);

    PASS();
}

TEST IRFL_COPY_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    forward_list_s copy = copy_forward_list(test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, i);
        const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    destroy_forward_list(&copy, NULL);

    PASS();
}

TEST IRFL_COPY_06(void) {
    forward_list_s test = create_forward_list();
    forward_list_s copy = copy_forward_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[IRFL-ERROR] Expected copy tail to be NULL.", NULL, copy.next);

    destroy_forward_list(&test, destroy_element);
    destroy_forward_list(&copy, destroy_element);

    PASS();
}

TEST IRFL_COPY_07(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));

    forward_list_s copy = copy_forward_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, 0);
    const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, 0);
    ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

    destroy_forward_list(&test, destroy_element);
    destroy_forward_list(&copy, destroy_element);

    PASS();
}

TEST IRFL_COPY_08(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    forward_list_s copy = copy_forward_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, i);
        const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, i);
        ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_forward_list(&test, destroy_element);
    destroy_forward_list(&copy, destroy_element);

    PASS();
}

TEST IRFL_COPY_09(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    forward_list_s copy = copy_forward_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, i);
        const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, i);
        ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_forward_list(&test, destroy_element);
    destroy_forward_list(&copy, destroy_element);

    PASS();
}

TEST IRFL_COPY_10(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, copy_element((FORWARD_LIST_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    forward_list_s copy = copy_forward_list(test, copy_element);

    ASSERT_EQm("[IRFL-ERROR] Expected copy size to be test size.", test.size, copy.size);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[IRFL-ERROR] Expected copy tail to not be NULL.", NULL, copy.next);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE test_element = get_forward_list(test, i);
        const FORWARD_LIST_DATA_TYPE copy_element = get_forward_list(copy, i);
        ASSERT_STRN_EQm("[IRFL-ERROR] Expected copy element to be same as test.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);
    }

    destroy_forward_list(&test, destroy_element);
    destroy_forward_list(&copy, destroy_element);

    PASS();
}

TEST IRFL_SORT_01(void) {
    forward_list_s test = create_forward_list();

    all_forward_list(&test, sort_int, NULL);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_SORT_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    all_forward_list(&test, sort_int, NULL);

    const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, 0);
    ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", 42, element.sub_one);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_SORT_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - i - 1, });
    }
    if (count & 0X01) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = (count / 2), });
    }

    all_forward_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_SORT_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - i - 1, });
    }
    if (count & 0X01) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = (count / 2), });
    }

    all_forward_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_SORT_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < (count / 2); ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - i - 1, });
    }
    if (count & 0X01) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = (count / 2), });
    }

    all_forward_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected copy element to be same as test element.", i, element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_01(void) {
    forward_list_s test = create_forward_list();

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be false.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, }, NULL));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_02(void) {
    forward_list_s test = create_forward_list();
    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, }, NULL));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_06(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_07(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_08(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count - 1, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_09(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_10(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_11(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count / 2, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_12(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_13(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_14(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = count, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_15(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 1; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_16(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 1; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_17(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 1; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    ASSERT_FALSEm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = 0, }, compare_int));

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_18(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_19(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_BINARY_SEARCH_20(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    all_forward_list(&test, sort_int, NULL);

    for (int i = 0; i < count; ++i) {
        ASSERTm("[IRFL-ERROR] Expected search to be true.", binary_search_forward_list(test, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, }, compare_int));
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_CLEAR_01(void) {
    forward_list_s test = create_forward_list();

    clear_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_CLEAR_02(void) {
    forward_list_s test = create_forward_list();

    insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = 42, });

    clear_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_CLEAR_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    clear_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_CLEAR_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    clear_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_CLEAR_05(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    clear_forward_list(&test, NULL);

    ASSERT_EQm("[IRFL-ERROR] Expected size to be zero", 0, test.size);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_FOREACH_01(void) {
    forward_list_s test = create_forward_list();

    int arg = 1;
    foreach_forward_list(&test, operation_int, &arg);

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_FOREACH_02(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK - 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int arg = 1;
    foreach_forward_list(&test, operation_int, &arg);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected incremented ith element.", i + 1, element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_FOREACH_03(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int arg = 1;
    foreach_forward_list(&test, operation_int, &arg);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected incremented ith element.", i + 1, element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

TEST IRFL_FOREACH_04(void) {
    forward_list_s test = create_forward_list();

    const size_t count = REALLOC_FORWARD_LIST_CHUNK + 1;
    for (size_t i = 0; i < count; ++i) {
        insert_at_forward_list(&test, test.size, (FORWARD_LIST_DATA_TYPE) { .sub_one = i, });
    }

    int arg = 1;
    foreach_forward_list(&test, operation_int, &arg);

    for (size_t i = 0; i < count; ++i) {
        const FORWARD_LIST_DATA_TYPE element = get_forward_list(test, i);
        ASSERT_EQm("[IRFL-ERROR] Expected incremented ith element.", i + 1, element.sub_one);
    }

    destroy_forward_list(&test, NULL);
    PASS();
}

SUITE (infinite_realloc_forward_list_test) {
    // create test
    RUN_TEST(IRFL_CREATE_01); RUN_TEST(IRFL_CREATE_02); RUN_TEST(IRFL_CREATE_03); RUN_TEST(IRFL_CREATE_04);
    // destroy test
    RUN_TEST(IRFL_DESTROY_01); RUN_TEST(IRFL_DESTROY_02); RUN_TEST(IRFL_DESTROY_03); RUN_TEST(IRFL_DESTROY_04);
    RUN_TEST(IRFL_DESTROY_05); RUN_TEST(IRFL_DESTROY_06); RUN_TEST(IRFL_DESTROY_07); RUN_TEST(IRFL_DESTROY_08);
    RUN_TEST(IRFL_DESTROY_09); RUN_TEST(IRFL_DESTROY_10);
    // insert test
    RUN_TEST(IRFL_INSERT_01); RUN_TEST(IRFL_INSERT_02); RUN_TEST(IRFL_INSERT_03); RUN_TEST(IRFL_INSERT_04);
    RUN_TEST(IRFL_INSERT_05); RUN_TEST(IRFL_INSERT_06); RUN_TEST(IRFL_INSERT_07); RUN_TEST(IRFL_INSERT_08);
    // remove first test
    RUN_TEST(IRFL_REMOVE_FIRST_01); RUN_TEST(IRFL_REMOVE_FIRST_02); RUN_TEST(IRFL_REMOVE_FIRST_03); RUN_TEST(IRFL_REMOVE_FIRST_04);
    RUN_TEST(IRFL_REMOVE_FIRST_05); RUN_TEST(IRFL_REMOVE_FIRST_06); RUN_TEST(IRFL_REMOVE_FIRST_07);
    // remove at test
    RUN_TEST(IRFL_REMOVE_AT_01); RUN_TEST(IRFL_REMOVE_AT_02); RUN_TEST(IRFL_REMOVE_AT_03); RUN_TEST(IRFL_REMOVE_AT_04);
    RUN_TEST(IRFL_REMOVE_AT_05); RUN_TEST(IRFL_REMOVE_AT_06); RUN_TEST(IRFL_REMOVE_AT_07);
    // reverse test
    RUN_TEST(IRFL_REVERSE_01); RUN_TEST(IRFL_REVERSE_02); RUN_TEST(IRFL_REVERSE_03); RUN_TEST(IRFL_REVERSE_04);
    RUN_TEST(IRFL_REVERSE_05); RUN_TEST(IRFL_REVERSE_06); RUN_TEST(IRFL_REVERSE_07); RUN_TEST(IRFL_REVERSE_08);
    // shift next test
    RUN_TEST(IRFL_SHIFT_01); RUN_TEST(IRFL_SHIFT_02); RUN_TEST(IRFL_SHIFT_03); RUN_TEST(IRFL_SHIFT_04);
    RUN_TEST(IRFL_SHIFT_05); RUN_TEST(IRFL_SHIFT_06); RUN_TEST(IRFL_SHIFT_07); RUN_TEST(IRFL_SHIFT_08);
    RUN_TEST(IRFL_SHIFT_09); RUN_TEST(IRFL_SHIFT_10); RUN_TEST(IRFL_SHIFT_11);
    // splice test
    RUN_TEST(IRFL_SPLICE_01); RUN_TEST(IRFL_SPLICE_02); RUN_TEST(IRFL_SPLICE_03); RUN_TEST(IRFL_SPLICE_04);
    RUN_TEST(IRFL_SPLICE_05); RUN_TEST(IRFL_SPLICE_06); RUN_TEST(IRFL_SPLICE_07); RUN_TEST(IRFL_SPLICE_08);
    RUN_TEST(IRFL_SPLICE_09); RUN_TEST(IRFL_SPLICE_10); RUN_TEST(IRFL_SPLICE_11);
    // split test
    RUN_TEST(IRFL_SPLIT_01); RUN_TEST(IRFL_SPLIT_02); RUN_TEST(IRFL_SPLIT_03); RUN_TEST(IRFL_SPLIT_04);
    RUN_TEST(IRFL_SPLIT_05); RUN_TEST(IRFL_SPLIT_06); RUN_TEST(IRFL_SPLIT_07); RUN_TEST(IRFL_SPLIT_08);
    RUN_TEST(IRFL_SPLIT_09); RUN_TEST(IRFL_SPLIT_10); RUN_TEST(IRFL_SPLIT_11); RUN_TEST(IRFL_SPLIT_12);
    RUN_TEST(IRFL_SPLIT_13); RUN_TEST(IRFL_SPLIT_14);
    // get test
    RUN_TEST(IRFL_GET_01); RUN_TEST(IRFL_GET_02); RUN_TEST(IRFL_GET_03); RUN_TEST(IRFL_GET_04);
    // is empty test
    RUN_TEST(IRFL_IS_EMPTY_01); RUN_TEST(IRFL_IS_EMPTY_02); RUN_TEST(IRFL_IS_EMPTY_03); RUN_TEST(IRFL_IS_EMPTY_04);
    RUN_TEST(IRFL_IS_EMPTY_05);
    // copy test
    RUN_TEST(IRFL_COPY_01); RUN_TEST(IRFL_COPY_02); RUN_TEST(IRFL_COPY_03); RUN_TEST(IRFL_COPY_04);
    RUN_TEST(IRFL_COPY_05); RUN_TEST(IRFL_COPY_06); RUN_TEST(IRFL_COPY_07); RUN_TEST(IRFL_COPY_08);
    RUN_TEST(IRFL_COPY_09); RUN_TEST(IRFL_COPY_10);
    // sort test
    RUN_TEST(IRFL_SORT_01); RUN_TEST(IRFL_SORT_02); RUN_TEST(IRFL_SORT_03); RUN_TEST(IRFL_SORT_04);
    RUN_TEST(IRFL_SORT_05);
    // binary search test
    RUN_TEST(IRFL_BINARY_SEARCH_01); RUN_TEST(IRFL_BINARY_SEARCH_02); RUN_TEST(IRFL_BINARY_SEARCH_03); RUN_TEST(IRFL_BINARY_SEARCH_04);
    RUN_TEST(IRFL_BINARY_SEARCH_05); RUN_TEST(IRFL_BINARY_SEARCH_06); RUN_TEST(IRFL_BINARY_SEARCH_07); RUN_TEST(IRFL_BINARY_SEARCH_08);
    RUN_TEST(IRFL_BINARY_SEARCH_09); RUN_TEST(IRFL_BINARY_SEARCH_10); RUN_TEST(IRFL_BINARY_SEARCH_11); RUN_TEST(IRFL_BINARY_SEARCH_12);
    RUN_TEST(IRFL_BINARY_SEARCH_13); RUN_TEST(IRFL_BINARY_SEARCH_14); RUN_TEST(IRFL_BINARY_SEARCH_15); RUN_TEST(IRFL_BINARY_SEARCH_16);
    RUN_TEST(IRFL_BINARY_SEARCH_17); RUN_TEST(IRFL_BINARY_SEARCH_18); RUN_TEST(IRFL_BINARY_SEARCH_19); RUN_TEST(IRFL_BINARY_SEARCH_20);
    // clear test
    RUN_TEST(IRFL_CLEAR_01); RUN_TEST(IRFL_CLEAR_02); RUN_TEST(IRFL_CLEAR_03); RUN_TEST(IRFL_CLEAR_04);
    RUN_TEST(IRFL_CLEAR_05);
    // foreach test
    RUN_TEST(IRFL_FOREACH_01); RUN_TEST(IRFL_FOREACH_02); RUN_TEST(IRFL_FOREACH_03); RUN_TEST(IRFL_FOREACH_04);
}
