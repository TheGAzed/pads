#include <suits.h>

#define STACK_DATA_TYPE DATA_TYPE
#define STACK_SIZE  (1 << 4)
#include <sequence/stack.h>

TEST CREATE_01(void) {
    stack_s test = create_stack();

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);
    ASSERT_NEQm("[ERROR] Test stack head is not NULL.", NULL, test.elements);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST DESTROY_01(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_02(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_04(void) {
    stack_s test = create_stack();
    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_stack(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_05(void) {
    stack_s test = create_stack();
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_06(void) {
    stack_s test = create_stack();
    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_07(void) {
    stack_s test = create_stack();
    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_08(void) {
    stack_s test = create_stack();
    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_stack(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test stack size is not zero.", 0, test.size);

    PASS();
}

TEST IS_FULL_01(void) {
    stack_s test = create_stack();

    ASSERT_FALSEm("[ERROR] Expected stack to not be full", is_full_stack(&test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IS_FULL_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[ERROR] Expected stack to not be full", is_full_stack(&test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IS_FULL_03(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[ERROR] Expected stack to not be full", is_full_stack(&test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IS_FULL_04(void) {
    stack_s test = create_stack();

    for (size_t i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERTm("[ERROR] Expected stack to be full", is_full_stack(&test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST PEEP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[ERROR] Expected to peep 42", 42, peep_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST PEEP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 2; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected to peep 42", 42, peep_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST PEEP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = -1, });
    }
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected to peep 42", 42, peep_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST PUSH_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST PUSH_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST PUSH_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST POP_01(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected to pop 42", 42, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST POP_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST POP_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST COPY_01(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST COPY_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });

    stack_s copy = copy_stack(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST COPY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST COPY_04(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i, });
    }

    stack_s copy = copy_stack(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < STACK_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal", pop_stack(&test).sub_one, pop_stack(&copy).sub_one);
    }

    destroy_stack(&test, destroy_int);
    destroy_stack(&copy, destroy_int);
    PASS();
}

TEST COPY_05(void) {
    stack_s test = create_stack();

    stack_s copy = copy_stack(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST COPY_06(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));

    stack_s copy = copy_stack(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[ERROR] Expected elements to be equal", peep_stack(&test).sub_two, peep_stack(&copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST COPY_07(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal", peep_stack(&test).sub_two, peep_stack(&copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST COPY_08(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    stack_s copy = copy_stack(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < STACK_SIZE; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal", peep_stack(&test).sub_two, peep_stack(&copy).sub_two, sizeof(TEST_STRING) - 1);
        STACK_DATA_TYPE test_element = pop_stack(&test);
        destroy_string(&test_element);
        STACK_DATA_TYPE copy_element = pop_stack(&copy);
        destroy_string(&copy_element);
    }

    destroy_stack(&test, destroy_string);
    destroy_stack(&copy, destroy_string);
    PASS();
}

TEST IS_EMPTY_01(void) {
    stack_s test = create_stack();

    ASSERTm("[ERROR] Expected stack to be empty", is_empty_stack(&test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IS_EMPTY_02(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ERROR] Expected stack to not be empty", is_empty_stack(&test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST IS_EMPTY_03(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ERROR] Expected stack to not be empty", is_empty_stack(&test));

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST FOREACH_01(void) {
    stack_s test = create_stack();
    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", 0 + increment, pop_stack(&test).sub_one);

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FOREACH_02(void) {
    stack_s test = create_stack();
    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FOREACH_03(void) {
    stack_s test = create_stack();
    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_stack(&test, operation_int, &increment);

    for (int i = STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);

    PASS();
}

TEST FOREACH_04(void) {
    stack_s test = create_stack();

    push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    STACK_DATA_TYPE element = pop_stack(&test);
    ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FOREACH_05(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST FOREACH_06(void) {
    stack_s test = create_stack();

    for (int i = 0; i < STACK_SIZE; ++i) {
        push_stack(&test, copy_string((STACK_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_stack(&test, operation_string, new_string);

    for (int i = 0; i < STACK_SIZE; ++i) {
        STACK_DATA_TYPE element = pop_stack(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_stack(&test, destroy_string);

    PASS();
}

TEST MAP_01(void) {
    stack_s test = create_stack();

    map_stack(&test, sort_int, compare_int_generic);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST MAP_02(void) {
    stack_s test = create_stack();

    push_stack(&test, (STACK_DATA_TYPE) { .sub_one = 42 });

    map_stack(&test, sort_int, compare_int_generic);

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST MAP_03(void) {
    stack_s test = create_stack();

    for (int i = (STACK_SIZE - 1) >> 1; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (STACK_SIZE - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = STACK_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST MAP_04(void) {
    stack_s test = create_stack();

    for (int i = (STACK_SIZE) >> 1; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (STACK_SIZE) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_int_generic);

    for (int i = STACK_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST MAP_05(void) {
    stack_s test = create_stack();

    for (int i = (STACK_SIZE - 1) >> 1; i < STACK_SIZE - 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (STACK_SIZE - 1) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < STACK_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

TEST MAP_06(void) {
    stack_s test = create_stack();

    for (int i = (STACK_SIZE) >> 1; i < STACK_SIZE; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (STACK_SIZE) >> 1; ++i) {
        push_stack(&test, (STACK_DATA_TYPE) { .sub_one = i });
    }

    map_stack(&test, sort_int, compare_reverse_int_generic);

    for (int i = 0; i < STACK_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted stack to pop i", i, pop_stack(&test).sub_one);
    }

    destroy_stack(&test, destroy_int);
    PASS();
}

SUITE (stack_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01); RUN_TEST(DESTROY_02); RUN_TEST(DESTROY_03); RUN_TEST(DESTROY_04); RUN_TEST(DESTROY_05);
    RUN_TEST(DESTROY_06); RUN_TEST(DESTROY_07); RUN_TEST(DESTROY_08);
    // is full
    RUN_TEST(IS_FULL_01); RUN_TEST(IS_FULL_02); RUN_TEST(IS_FULL_03); RUN_TEST(IS_FULL_04);
    // peep
    RUN_TEST(PEEP_01); RUN_TEST(PEEP_02); RUN_TEST(PEEP_03);
    // push
    RUN_TEST(PUSH_01); RUN_TEST(PUSH_02); RUN_TEST(PUSH_03);
    // pop
    RUN_TEST(POP_01); RUN_TEST(POP_02); RUN_TEST(POP_03);
    // copy
    RUN_TEST(COPY_01); RUN_TEST(COPY_02); RUN_TEST(COPY_03); RUN_TEST(COPY_04); RUN_TEST(COPY_05);
    RUN_TEST(COPY_06); RUN_TEST(COPY_07); RUN_TEST(COPY_08);
    // is empty
    RUN_TEST(IS_EMPTY_01); RUN_TEST(IS_EMPTY_02); RUN_TEST(IS_EMPTY_03);
    // foreach
    RUN_TEST(FOREACH_01); RUN_TEST(FOREACH_02); RUN_TEST(FOREACH_03); RUN_TEST(FOREACH_04); RUN_TEST(FOREACH_05);
    RUN_TEST(FOREACH_06);
    // map
    RUN_TEST(MAP_01); RUN_TEST(MAP_02); RUN_TEST(MAP_03); RUN_TEST(MAP_04); RUN_TEST(MAP_05);
    RUN_TEST(MAP_06);
}
