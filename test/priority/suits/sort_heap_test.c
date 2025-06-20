#include <suits.h>

#define SORT_HEAP_DATA_TYPE DATA_TYPE
#define SORT_HEAP_SIZE (1 << 4)
#include <priority/sort_heap.h>

TEST CREATE_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);
    ASSERT_NEQm("[ERROR] Expected function pointer to not be NULL.", NULL, test.sort);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST DESTROY_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    destroy_sort_heap(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Expected function pointer to be NULL.", NULL, test.sort);

    PASS();
}

TEST DESTROY_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 42, });

    destroy_sort_heap(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Expected function pointer to be NULL.", NULL, test.sort);

    PASS();
}

TEST DESTROY_03(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    destroy_sort_heap(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Expected function pointer to be NULL.", NULL, test.sort);

    PASS();
}

TEST DESTROY_04(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    destroy_sort_heap(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Expected function pointer to be NULL.", NULL, test.sort);

    PASS();
}

TEST IS_EMPTY_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    ASSERTm("[ERROR] Expected heap to be empty.", is_empty_sort_heap(&test));

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected heap to not be empty.", is_empty_sort_heap(&test));

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_03(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected heap to not be empty.", is_empty_sort_heap(&test));

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_04(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected heap to not be empty.", is_empty_sort_heap(&test));

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST IS_FULL_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    ASSERT_FALSEm("[ERROR] Expected heap to be empty.", is_full_sort_heap(&test));

    destroy_sort_heap(&test, destroy_string);

    PASS();
}

TEST IS_FULL_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 42, });

    ASSERT_FALSEm("[ERROR] Expected heap to not be empty.", is_full_sort_heap(&test));

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST IS_FULL_03(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_FALSEm("[ERROR] Expected heap to not be empty.", is_full_sort_heap(&test));

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST IS_FULL_04(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    ASSERTm("[ERROR] Expected heap to not be empty.", is_full_sort_heap(&test));

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST COPY_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    sort_heap_s copy = copy_sort_heap(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal.", test.size, copy.size);
    ASSERT_EQm("[ERROR] Expected compare functions to be equal.", test.sort, copy.sort);

    destroy_sort_heap(&test, destroy_int);
    destroy_sort_heap(&copy, destroy_int);

    PASS();
}

TEST COPY_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 42, });

    sort_heap_s copy = copy_sort_heap(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal.", test.size, copy.size);
    ASSERT_EQm("[ERROR] Expected compare functions to be equal.", test.sort, copy.sort);

    const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
    const SORT_HEAP_DATA_TYPE b = pop_sort_heap(&copy);
    ASSERT_EQm("[ERROR] Expected poped elements to be equal.", a.sub_one, b.sub_one);

    destroy_sort_heap(&test, destroy_int);
    destroy_sort_heap(&copy, destroy_int);

    PASS();
}

TEST COPY_03(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    sort_heap_s copy = copy_sort_heap(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal.", test.size, copy.size);
    ASSERT_EQm("[ERROR] Expected compare functions to be equal.", test.sort, copy.sort);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
        const SORT_HEAP_DATA_TYPE b = pop_sort_heap(&copy);
        ASSERT_EQm("[ERROR] Expected poped elements to be equal.", a.sub_one, b.sub_one);
    }

    destroy_sort_heap(&test, destroy_int);
    destroy_sort_heap(&copy, destroy_int);

    PASS();
}

TEST COPY_04(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    sort_heap_s copy = copy_sort_heap(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal.", test.size, copy.size);
    ASSERT_EQm("[ERROR] Expected compare functions to be equal.", test.sort, copy.sort);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
        const SORT_HEAP_DATA_TYPE b = pop_sort_heap(&copy);
        ASSERT_EQm("[ERROR] Expected poped elements to be equal.", a.sub_one, b.sub_one);
    }

    destroy_sort_heap(&test, destroy_int);
    destroy_sort_heap(&copy, destroy_int);

    PASS();
}

TEST PUSH_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 42, });

    const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected poped element to be 42.", 42, a.sub_one);


    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST PUSH_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
        ASSERT_EQm("[ERROR] Expected poped element to be i.", i, a.sub_one);
    }

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST PUSH_03(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
        ASSERT_EQm("[ERROR] Expected poped element to be i.", i, a.sub_one);
    }

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST POP_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 42, });

    const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected poped element to be 42.", 42, a.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST POP_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
        ASSERT_EQm("[ERROR] Expected poped element to be i.", i, a.sub_one);
    }

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST POP_03(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&test);
        ASSERT_EQm("[ERROR] Expected poped element to be i.", i, a.sub_one);
    }

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST PEEP_01(void) {
    struct compare cmp = { .function = compare_reverse_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = SORT_HEAP_SIZE, });

    const SORT_HEAP_DATA_TYPE a = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be SORT_HEAP_SIZE.", SORT_HEAP_SIZE, a.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST PEEP_02(void) {
    struct compare cmp = { .function = compare_reverse_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 2; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }
    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = SORT_HEAP_SIZE, });

    const SORT_HEAP_DATA_TYPE a = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be SORT_HEAP_SIZE.", SORT_HEAP_SIZE, a.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST PEEP_03(void) {
    struct compare cmp = { .function = compare_reverse_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }
    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = SORT_HEAP_SIZE, });

    const SORT_HEAP_DATA_TYPE a = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be SORT_HEAP_SIZE.", SORT_HEAP_SIZE, a.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST REPLACE_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 1, });

    const SORT_HEAP_DATA_TYPE a = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 1.", 1, a.sub_one);

    replace_sort_heap(&test, 0, (SORT_HEAP_DATA_TYPE) { .sub_one = 0, });

    const SORT_HEAP_DATA_TYPE b = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 0.", 0, b.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST REPLACE_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = 1, });

    const SORT_HEAP_DATA_TYPE a = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 1.", 1, a.sub_one);

    replace_sort_heap(&test, 0, (SORT_HEAP_DATA_TYPE) { .sub_one = 0, });

    const SORT_HEAP_DATA_TYPE b = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 0.", 0, b.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST REPLACE_03(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i + 1, });
    }

    const SORT_HEAP_DATA_TYPE a = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 1.", 1, a.sub_one);

    replace_sort_heap(&test, 0, (SORT_HEAP_DATA_TYPE) { .sub_one = 0, });

    const SORT_HEAP_DATA_TYPE b = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 0.", 0, b.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST REPLACE_04(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s test = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        push_sort_heap(&test, (SORT_HEAP_DATA_TYPE) { .sub_one = i + 1, });
    }

    const SORT_HEAP_DATA_TYPE a = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 1.", 1, a.sub_one);

    replace_sort_heap(&test, 0, (SORT_HEAP_DATA_TYPE) { .sub_one = 0, });

    const SORT_HEAP_DATA_TYPE b = peep_sort_heap(&test);
    ASSERT_EQm("[ERROR] Expected peeped element to be 0.", 0, b.sub_one);

    destroy_sort_heap(&test, destroy_int);

    PASS();
}

TEST MELD_01(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s one = create_sort_heap(sort_int, &cmp);
    sort_heap_s two = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; i += 2) {
        push_sort_heap(&one, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i < SORT_HEAP_SIZE - 1; i += 2) {
        push_sort_heap(&two, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    meld_sort_heap(&one, &two);

    for (int i = 0; i < SORT_HEAP_SIZE - 1; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&one);
        ASSERT_EQm("[ERROR] Expected poped element to be i.", i, a.sub_one);
    }

    destroy_sort_heap(&one, destroy_int);
    destroy_sort_heap(&two, destroy_int);

    PASS();
}

TEST MELD_02(void) {
    struct compare cmp = { .function = compare_int_generic, };
    sort_heap_s one = create_sort_heap(sort_int, &cmp);
    sort_heap_s two = create_sort_heap(sort_int, &cmp);

    for (int i = 0; i < SORT_HEAP_SIZE; i += 2) {
        push_sort_heap(&one, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i < SORT_HEAP_SIZE; i += 2) {
        push_sort_heap(&two, (SORT_HEAP_DATA_TYPE) { .sub_one = i, });
    }

    meld_sort_heap(&one, &two);

    for (int i = 0; i < SORT_HEAP_SIZE; ++i) {
        const SORT_HEAP_DATA_TYPE a = pop_sort_heap(&one);
        ASSERT_EQm("[ERROR] Expected poped element to be i.", i, a.sub_one);
    }

    destroy_sort_heap(&one, destroy_int);
    destroy_sort_heap(&two, destroy_int);

    PASS();
}

SUITE (sort_heap_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01); RUN_TEST(DESTROY_02); RUN_TEST(DESTROY_03); RUN_TEST(DESTROY_04);
    // is empty
    RUN_TEST(IS_EMPTY_01); RUN_TEST(IS_EMPTY_02); RUN_TEST(IS_EMPTY_03); RUN_TEST(IS_EMPTY_04);
    // is full
    RUN_TEST(IS_FULL_01); RUN_TEST(IS_FULL_02); RUN_TEST(IS_FULL_03); RUN_TEST(IS_FULL_04);
    // copy
    RUN_TEST(COPY_01); RUN_TEST(COPY_02); RUN_TEST(COPY_03); RUN_TEST(COPY_04);
    // push
    RUN_TEST(PUSH_01); RUN_TEST(PUSH_02); RUN_TEST(PUSH_03);
    // pop
    RUN_TEST(POP_01); RUN_TEST(POP_02); RUN_TEST(POP_03);
    // peep
    RUN_TEST(PEEP_01); RUN_TEST(PEEP_02); RUN_TEST(PEEP_03);
    // replace
    RUN_TEST(REPLACE_01); RUN_TEST(REPLACE_02); RUN_TEST(REPLACE_03); RUN_TEST(REPLACE_04);
    // meld
    RUN_TEST(MELD_01); RUN_TEST(MELD_02);
}
