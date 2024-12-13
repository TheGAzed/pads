#include "queue_test.h"

#define QUEUE_MODE FINITE_PREPROCESSOR_QUEUE
#define PREPROCESSOR_QUEUE_SIZE (1 << 4)
#include <queue.h>

/// Tests if queue is initialized correctly when creating it.
TEST ILQ_01(void) {
    queue_s test = create_queue();

    ASSERT_EQm("[ILQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[ILQ-ERROR] Test queue current is not zero.", 0, test.current);

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if queue is initialized correctly when creating and then destroying it.
TEST ILQ_02(void) {
    queue_s test = create_queue();
    destroy_queue(&test, NULL);

    ASSERT_EQm("[ILQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[ILQ-ERROR] Test queue current is not zero.", 0, test.current);

    PASS();
}

/// Tests if one enqueued element is peeked correctly.
TEST ILQ_03(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_QUEUE_SIZE' - 1 enqueued element is peeked correctly.
TEST ILQ_04(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_QUEUE_SIZE' enqueued element is peeked correctly.
TEST ILQ_05(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if sequence of 'PREPROCESSOR_QUEUE_SIZE' - 1 enqueued numbers is dequeued correctly
TEST ILQ_06(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if sequence of 'PREPROCESSOR_QUEUE_SIZE' enqueued numbers is dequeued correctly
TEST ILQ_07(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST ILQ_08(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    peek_queue(test);

    ASSERT_EQm("[ILQ-ERROR] Expected queue size to not change after peek.", 1, test.size);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is empty when creating it.
TEST ILQ_09(void) {
    queue_s test = create_queue();

    ASSERTm("[ILQ-ERROR] Expected queue to be empty when creating it.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is not empty when enqueueing element.
TEST ILQ_10(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[ILQ-ERROR] Expected queue to not be empty when enqueueing element.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if one enqueued element is dequeued correctly.
TEST ILQ_11(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_QUEUE_SIZE' - 1 enqueued element is dequeued correctly.
TEST ILQ_12(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'PREPROCESSOR_QUEUE_SIZE' enqueued element is dequeued correctly.
TEST ILQ_13(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if destroyed element
TEST ILQ_14(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILQ_15(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST ILQ_16(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if 1 copied int element
TEST ILQ_17(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ILQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'PREPROCESSOR_QUEUE_SIZE' - 1 copied int element
TEST ILQ_18(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ILQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'PREPROCESSOR_QUEUE_SIZE 'copied int element
TEST ILQ_19(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ILQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 1 copied string element
TEST ILQ_20(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    queue_s copy = copy_queue(test, copy_element);

    QUEUE_DATA_TYPE elemen_test = dequeue(&test);
    QUEUE_DATA_TYPE element_copy = dequeue(&copy);
    ASSERT_STRN_EQm("[ILQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'PREPROCESSOR_QUEUE_SIZE' - 1 copied string element
TEST ILQ_21(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[ILQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'PREPROCESSOR_QUEUE_SIZE' copied string element
TEST ILQ_22(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[ILQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if queue is not empty
TEST ILQ_23(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[ILQ-TEST] Stack is empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 1 enqueue/dequeue
TEST ILQ_24(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    dequeue(&test);
    ASSERTm("[ILQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 'PREPROCESSOR_QUEUE_SIZE' - 1 enqueue/dequeue
TEST ILQ_25(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        dequeue(&test);
    }

    ASSERTm("[ILQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 'PREPROCESSOR_QUEUE_SIZE' enqueue/dequeue
TEST ILQ_26(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        dequeue(&test);
    }

    ASSERTm("[ILQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if all one int values get incremented by 'increment'
TEST ILQ_27(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    ASSERT_EQm("[ILQ-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all 'PREPROCESSOR_QUEUE_SIZE' - 1 int values get incremented by 'increment'
TEST ILQ_28(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ILQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all 'PREPROCESSOR_QUEUE_SIZE' int values get incremented by 'increment'
TEST ILQ_29(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ILQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all one string values have changed to new string value
TEST ILQ_30(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    QUEUE_DATA_TYPE element = dequeue(&test);
    ASSERT_STRN_EQm("[ILQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_element(&element);

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Test if all 'PREPROCESSOR_QUEUE_SIZE' - 1 string values have changed to new string value
TEST ILQ_31(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[ILQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Test if all 'PREPROCESSOR_QUEUE_SIZE' string values have changed to new string value
TEST ILQ_32(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[ILQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_queue(&test, destroy_element);

    PASS();
}

SUITE (finite_preprocessor_queue_test) {
    RUN_TEST(ILQ_01); RUN_TEST(ILQ_02); RUN_TEST(ILQ_03); RUN_TEST(ILQ_04);
    RUN_TEST(ILQ_05); RUN_TEST(ILQ_06); RUN_TEST(ILQ_07); RUN_TEST(ILQ_08);
    RUN_TEST(ILQ_09); RUN_TEST(ILQ_10); RUN_TEST(ILQ_11); RUN_TEST(ILQ_12);
    RUN_TEST(ILQ_13); RUN_TEST(ILQ_14); RUN_TEST(ILQ_15); RUN_TEST(ILQ_16);
    RUN_TEST(ILQ_17); RUN_TEST(ILQ_18); RUN_TEST(ILQ_19); RUN_TEST(ILQ_20);
    RUN_TEST(ILQ_21); RUN_TEST(ILQ_22); RUN_TEST(ILQ_23); RUN_TEST(ILQ_24);
    RUN_TEST(ILQ_25); RUN_TEST(ILQ_26); RUN_TEST(ILQ_27); RUN_TEST(ILQ_28);
    RUN_TEST(ILQ_29); RUN_TEST(ILQ_30); RUN_TEST(ILQ_31); RUN_TEST(ILQ_32);
}

