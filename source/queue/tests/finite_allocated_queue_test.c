#include "queue_test.h"

#define QUEUE_MODE FINITE_ALLOCATED_QUEUE
#define MAXIMUM_QUEUE_SIZE  (1 << 4)
#include <queue/queue.h>

TEST FAQ_CREATE_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_DESTROY_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_DESTROY_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_DESTROY_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_DESTROY_04(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_DESTROY_05(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_DESTROY_06(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_DESTROY_07(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_DESTROY_08(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST FAQ_IS_FULL_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    ASSERT_FALSEm("[FAQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_IS_FULL_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[FAQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_IS_FULL_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[FAQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_IS_FULL_04(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERTm("[FAQ-ERROR] Expected queue to be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_PEEK_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[FAQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_PEEK_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FAQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_PEEK_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FAQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_ENQUEUE_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAQ-ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_ENQUEUE_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_ENQUEUE_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_DEQUEUE_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAQ-ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_DEQUEUE_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_DEQUEUE_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_COPY_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FAQ_COPY_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[FAQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FAQ_COPY_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FAQ_COPY_04(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FAQ_COPY_05(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FAQ_COPY_06(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[FAQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FAQ_COPY_07(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[FAQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FAQ_COPY_08(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FAQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FAQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_STRN_EQm("[FAQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FAQ_IS_EMPTY_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    ASSERTm("[FAQ-ERROR] Expected queue to be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_IS_EMPTY_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FAQ-ERROR] Expected queue to not be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_IS_EMPTY_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FAQ-ERROR] Expected queue to not be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_CLEAR_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_CLEAR_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_CLEAR_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_CLEAR_04(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_CLEAR_05(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FAQ_CLEAR_06(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FAQ_CLEAR_07(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FAQ_CLEAR_08(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FAQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FAQ_FOREACH_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    ASSERT_EQm("[FAQ-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FAQ_FOREACH_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FAQ_FOREACH_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FAQ_FOREACH_04(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    QUEUE_DATA_TYPE element = dequeue(&test);
    ASSERT_STRN_EQm("[FAQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FAQ_FOREACH_05(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[FAQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FAQ_FOREACH_06(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[FAQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FAQ_FOREVERY_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    forevery_queue(&test, sort_int, compare_int);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_FOREVERY_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });

    forevery_queue(&test, sort_int, compare_int);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_FOREVERY_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE - 1) >> 1; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_int);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_FOREVERY_04(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE) >> 1; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_int);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_FOREVERY_05(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE - 1) >> 1; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_reverse_int);

    for (int i = MAXIMUM_QUEUE_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FAQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FAQ_FOREVERY_06(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE) >> 1; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_reverse_int);

    for (int i = MAXIMUM_QUEUE_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FAQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

SUITE (finite_allocated_queue_test) {
    // create
    RUN_TEST(FAQ_CREATE_01);
    // destroy
    RUN_TEST(FAQ_DESTROY_01); RUN_TEST(FAQ_DESTROY_02); RUN_TEST(FAQ_DESTROY_03); RUN_TEST(FAQ_DESTROY_04); RUN_TEST(FAQ_DESTROY_05);
    RUN_TEST(FAQ_DESTROY_06); RUN_TEST(FAQ_DESTROY_07); RUN_TEST(FAQ_DESTROY_08);
    // is full
    RUN_TEST(FAQ_IS_FULL_01); RUN_TEST(FAQ_IS_FULL_02); RUN_TEST(FAQ_IS_FULL_03); RUN_TEST(FAQ_IS_FULL_04);
    // peep
    RUN_TEST(FAQ_PEEK_01); RUN_TEST(FAQ_PEEK_02); RUN_TEST(FAQ_PEEK_03);
    // push
    RUN_TEST(FAQ_ENQUEUE_01); RUN_TEST(FAQ_ENQUEUE_02); RUN_TEST(FAQ_ENQUEUE_03);
    // pop
    RUN_TEST(FAQ_DEQUEUE_01); RUN_TEST(FAQ_DEQUEUE_02); RUN_TEST(FAQ_DEQUEUE_03);
    // copy
    RUN_TEST(FAQ_COPY_01); RUN_TEST(FAQ_COPY_02); RUN_TEST(FAQ_COPY_03); RUN_TEST(FAQ_COPY_04); RUN_TEST(FAQ_COPY_05);
    RUN_TEST(FAQ_COPY_06); RUN_TEST(FAQ_COPY_07); RUN_TEST(FAQ_COPY_08);
    // is empty
    RUN_TEST(FAQ_IS_EMPTY_01); RUN_TEST(FAQ_IS_EMPTY_02); RUN_TEST(FAQ_IS_EMPTY_03);
    // clear
    RUN_TEST(FAQ_CLEAR_01); RUN_TEST(FAQ_CLEAR_02); RUN_TEST(FAQ_CLEAR_03); RUN_TEST(FAQ_CLEAR_04); RUN_TEST(FAQ_CLEAR_05);
    RUN_TEST(FAQ_CLEAR_06); RUN_TEST(FAQ_CLEAR_07); RUN_TEST(FAQ_CLEAR_08);
    // foreach
    RUN_TEST(FAQ_FOREACH_01); RUN_TEST(FAQ_FOREACH_02); RUN_TEST(FAQ_FOREACH_03); RUN_TEST(FAQ_FOREACH_04); RUN_TEST(FAQ_FOREACH_05);
    RUN_TEST(FAQ_FOREACH_06);
    // foevery
    RUN_TEST(FAQ_FOREVERY_01); RUN_TEST(FAQ_FOREVERY_02); RUN_TEST(FAQ_FOREVERY_03); RUN_TEST(FAQ_FOREVERY_04); RUN_TEST(FAQ_FOREVERY_05);
    RUN_TEST(FAQ_FOREVERY_06);
}
