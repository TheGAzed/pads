#include <suits.h>

#define QUEUE_DATA_TYPE DATA_TYPE
#define QUEUE_SIZE (1 << 4)
#include <sequential/queue.h>

TEST CREATE_01(void) {
    queue_s test = create_queue();

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST DESTROY_01(void) {
    queue_s test = create_queue();
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_04(void) {
    queue_s test = create_queue();
    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_05(void) {
    queue_s test = create_queue();
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_06(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_07(void) {
    queue_s test = create_queue();
    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST DESTROY_08(void) {
    queue_s test = create_queue();
    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST IS_FULL_01(void) {
    queue_s test = create_queue();

    ASSERT_FALSEm("[ERROR] Expected queue to not be full", is_full_queue(&test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IS_FULL_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[ERROR] Expected queue to not be full", is_full_queue(&test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IS_FULL_03(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[ERROR] Expected queue to not be full", is_full_queue(&test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IS_FULL_04(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERTm("[ERROR] Expected queue to be full", is_full_queue(&test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST PEEK_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[ERROR] Expected to peek 42", 42, peek_queue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST PEEK_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ERROR] Expected to peek 42", 42, peek_queue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST PEEK_03(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ERROR] Expected to peek 42", 42, peek_queue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST ENQUEUE_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST ENQUEUE_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST ENQUEUE_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST DEQUEUE_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST DEQUEUE_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST DEQUEUE_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST COPY_01(void) {
    queue_s test = create_queue();

    queue_s copy = copy_queue(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST COPY_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    queue_s copy = copy_queue(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST COPY_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST COPY_04(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST COPY_05(void) {
    queue_s test = create_queue();

    queue_s copy = copy_queue(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST COPY_06(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));

    queue_s copy = copy_queue(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[ERROR] Expected elements to be equal", peek_queue(&test).sub_two, peek_queue(&copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST COPY_07(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal", peek_queue(&test).sub_two, peek_queue(&copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST COPY_08(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(&test, copy_string);

    ASSERT_EQm("[ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal", peek_queue(&test).sub_two, peek_queue(&copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST IS_EMPTY_01(void) {
    queue_s test = create_queue();

    ASSERTm("[ERROR] Expected queue to be empty", is_empty_queue(&test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IS_EMPTY_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ERROR] Expected queue to not be empty", is_empty_queue(&test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IS_EMPTY_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[ERROR] Expected queue to not be empty", is_empty_queue(&test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FOREACH_01(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FOREACH_02(void) {
    queue_s test = create_queue();
    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FOREACH_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FOREACH_04(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    QUEUE_DATA_TYPE element = dequeue(&test);
    ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FOREACH_05(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FOREACH_06(void) {
    queue_s test = create_queue();

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST MAP_01(void) {
    queue_s test = create_queue();

    map_queue(&test, sort_int, compare_int_generic);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST MAP_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });

    map_queue(&test, sort_int, compare_int_generic);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST MAP_03(void) {
    queue_s test = create_queue();

    for (int i = (QUEUE_SIZE - 1) >> 1; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_int_generic);

    for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST MAP_04(void) {
    queue_s test = create_queue();

    for (int i = (QUEUE_SIZE) >> 1; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (QUEUE_SIZE) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_int_generic);

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST MAP_05(void) {
    queue_s test = create_queue();

    for (int i = (QUEUE_SIZE - 1) >> 1; i < QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_reverse_int_generic);

    for (int i = QUEUE_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST MAP_06(void) {
    queue_s test = create_queue();

    for (int i = (QUEUE_SIZE) >> 1; i < QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (QUEUE_SIZE) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_reverse_int_generic);

    for (int i = QUEUE_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

SUITE (queue_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01); RUN_TEST(DESTROY_02); RUN_TEST(DESTROY_03); RUN_TEST(DESTROY_04); RUN_TEST(DESTROY_05);
    RUN_TEST(DESTROY_06); RUN_TEST(DESTROY_07); RUN_TEST(DESTROY_08);
    // is full
    RUN_TEST(IS_FULL_01); RUN_TEST(IS_FULL_02); RUN_TEST(IS_FULL_03); RUN_TEST(IS_FULL_04);
    // peek
    RUN_TEST(PEEK_01); RUN_TEST(PEEK_02); RUN_TEST(PEEK_03);
    // push
    RUN_TEST(ENQUEUE_01); RUN_TEST(ENQUEUE_02); RUN_TEST(ENQUEUE_03);
    // pop
    RUN_TEST(DEQUEUE_01); RUN_TEST(DEQUEUE_02); RUN_TEST(DEQUEUE_03);
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

