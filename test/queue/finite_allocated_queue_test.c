#include "queue_test.h"

#define QUEUE_MODE FINITE_ALLOCATED_QUEUE
#define MAXIMUM_QUEUE_SIZE  (1 << 4)
#include <queue.h>

/// Tests if queue is initialized correctly when creating it.
TEST FAQ_01(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue current is not zero.", 0, test.current);

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if queue is initialized correctly when creating and then destroying it.
TEST FAQ_02(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    destroy_queue(&test, NULL);

    ASSERT_EQm("[FAQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[FAQ-ERROR] Test queue current is not zero.", 0, test.current);

    PASS();
}

/// Tests if one enqueued element is peeked correctly.
TEST FAQ_03(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_QUEUE_SIZE' - 1 enqueued element is peeked correctly.
TEST FAQ_04(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FAQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_QUEUE_SIZE' enqueued element is peeked correctly.
TEST FAQ_05(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FAQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if sequence of 'MAXIMUM_QUEUE_SIZE' - 1 enqueued numbers is dequeued correctly
TEST FAQ_06(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 1; i <= MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if sequence of 'MAXIMUM_QUEUE_SIZE' enqueued numbers is dequeued correctly
TEST FAQ_07(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 1; i <= MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST FAQ_08(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    peek_queue(test);

    ASSERT_EQm("[FAQ-ERROR] Expected queue size to not change after peek.", 1, test.size);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is empty when creating it.
TEST FAQ_09(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    ASSERTm("[FAQ-ERROR] Expected queue to be empty when creating it.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is not empty when enqueueing element.
TEST FAQ_10(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[FAQ-ERROR] Expected queue to not be empty when enqueueing element.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if one enqueued element is dequeued correctly.
TEST FAQ_11(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FAQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_QUEUE_SIZE' - 1 enqueued element is dequeued correctly.
TEST FAQ_12(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FAQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'MAXIMUM_QUEUE_SIZE' enqueued element is dequeued correctly.
TEST FAQ_13(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FAQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if destroyed element
TEST FAQ_14(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST FAQ_15(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST FAQ_16(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if 1 copied int element
TEST FAQ_17(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[FAQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'MAXIMUM_QUEUE_SIZE' - 1 copied int element
TEST FAQ_18(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'MAXIMUM_QUEUE_SIZE 'copied int element
TEST FAQ_19(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 1 copied string element
TEST FAQ_20(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    queue_s copy = copy_queue(test, copy_element);

    QUEUE_DATA_TYPE elemen_test = dequeue(&test);
    QUEUE_DATA_TYPE element_copy = dequeue(&copy);
    ASSERT_STRN_EQm("[FAQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'MAXIMUM_QUEUE_SIZE' - 1 copied string element
TEST FAQ_21(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[FAQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'MAXIMUM_QUEUE_SIZE' copied string element
TEST FAQ_22(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[FAQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if queue is not empty
TEST FAQ_23(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[FAQ-TEST] Stack is empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 1 enqueue/dequeue
TEST FAQ_24(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    dequeue(&test);
    ASSERTm("[FAQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 'MAXIMUM_QUEUE_SIZE' - 1 enqueue/dequeue
TEST FAQ_25(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        dequeue(&test);
    }

    ASSERTm("[FAQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 'MAXIMUM_QUEUE_SIZE' enqueue/dequeue
TEST FAQ_26(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        dequeue(&test);
    }

    ASSERTm("[FAQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if all one int values get incremented by 'increment'
TEST FAQ_27(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    ASSERT_EQm("[FAQ-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all 'MAXIMUM_QUEUE_SIZE' - 1 int values get incremented by 'increment'
TEST FAQ_28(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all 'MAXIMUM_QUEUE_SIZE' int values get incremented by 'increment'
TEST FAQ_29(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all one string values have changed to new string value
TEST FAQ_30(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    QUEUE_DATA_TYPE element = dequeue(&test);
    ASSERT_STRN_EQm("[FAQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_element(&element);

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Test if all 'MAXIMUM_QUEUE_SIZE' - 1 string values have changed to new string value
TEST FAQ_31(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[FAQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Test if all 'MAXIMUM_QUEUE_SIZE' string values have changed to new string value
TEST FAQ_32(void) {
    queue_s test = create_queue(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[FAQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_queue(&test, destroy_element);

    PASS();
}

SUITE (finite_allocated_queue_test) {
    RUN_TEST(FAQ_01); RUN_TEST(FAQ_02); RUN_TEST(FAQ_03); RUN_TEST(FAQ_04);
    RUN_TEST(FAQ_05); RUN_TEST(FAQ_06); RUN_TEST(FAQ_07); RUN_TEST(FAQ_08);
    RUN_TEST(FAQ_09); RUN_TEST(FAQ_10); RUN_TEST(FAQ_11); RUN_TEST(FAQ_12);
    RUN_TEST(FAQ_13); RUN_TEST(FAQ_14); RUN_TEST(FAQ_15); RUN_TEST(FAQ_16);
    RUN_TEST(FAQ_17); RUN_TEST(FAQ_18); RUN_TEST(FAQ_19); RUN_TEST(FAQ_20);
    RUN_TEST(FAQ_21); RUN_TEST(FAQ_22); RUN_TEST(FAQ_23); RUN_TEST(FAQ_24);
    RUN_TEST(FAQ_25); RUN_TEST(FAQ_26); RUN_TEST(FAQ_27); RUN_TEST(FAQ_28);
    RUN_TEST(FAQ_29); RUN_TEST(FAQ_30); RUN_TEST(FAQ_31); RUN_TEST(FAQ_32);
}


