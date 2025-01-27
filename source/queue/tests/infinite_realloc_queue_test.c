#include "queue_test.h"

#define QUEUE_MODE INFINITE_REALLOC_QUEUE
#define REALLOC_QUEUE_CHUNK (1 << 4)
#include <queue/queue.h>

/// Tests if queue is initialized correctly when creating it.
TEST IRQ_01(void) {
    queue_s test = create_queue();

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue current is not zero.", 0, test.current);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if queue is initialized correctly when creating and then destroying it.
TEST IRQ_02(void) {
    queue_s test = create_queue();
    destroy_queue(&test, NULL);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue current is not zero.", 0, test.current);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

/// Tests if one enqueued element is peeked correctly.
TEST IRQ_03(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_QUEUE_CHUNK' - 1 enqueued element is peeked correctly.
TEST IRQ_04(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_QUEUE_CHUNK' enqueued element is peeked correctly.
TEST IRQ_05(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_QUEUE_CHUNK' + 1 enqueued element is peeked correctly.
TEST IRQ_06(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if sequence of 'REALLOC_QUEUE_CHUNK' - 1 enqueued numbers is dequeued correctly
TEST IRQ_07(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if sequence of 'REALLOC_QUEUE_CHUNK' enqueued numbers is dequeued correctly
TEST IRQ_08(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if sequence of 'REALLOC_QUEUE_CHUNK' - 1 enqueued numbers is dequeued correctly
TEST IRQ_09(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST IRQ_10(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    peek_queue(test);

    ASSERT_EQm("[IRQ-ERROR] Expected queue size to not change after peek.", 1, test.size);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is empty when creating it.
TEST IRQ_11(void) {
    queue_s test = create_queue();

    ASSERTm("[IRQ-ERROR] Expected queue to be empty when creating it.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is not empty when enqueueing element.
TEST IRQ_12(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be empty when enqueueing element.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if one enqueued element is dequeued correctly.
TEST IRQ_13(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_QUEUE_CHUNK' - 1 enqueued element is dequeued correctly.
TEST IRQ_14(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_QUEUE_CHUNK' enqueued element is dequeued correctly.
TEST IRQ_15(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'REALLOC_QUEUE_CHUNK' + 1 enqueued element is dequeued correctly.
TEST IRQ_16(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Test queue dequeued element not 42.", 42, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if destroyed element
TEST IRQ_17(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRQ_18(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRQ_19(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if destroyed element
TEST IRQ_20(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    destroy_queue(&test, destroy_element);
    PASS();
}

/// Test if 1 copied int element
TEST IRQ_21(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[IRQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' - 1 copied int element
TEST IRQ_22(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK 'copied int element
TEST IRQ_23(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' + 1 copied int element
TEST IRQ_24(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 1 copied string element
TEST IRQ_25(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    queue_s copy = copy_queue(test, copy_element);

    QUEUE_DATA_TYPE elemen_test = dequeue(&test);
    QUEUE_DATA_TYPE element_copy = dequeue(&copy);
    ASSERT_STRN_EQm("[IRQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
    destroy_element(&elemen_test);
    destroy_element(&element_copy);

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' - 1 copied string element
TEST IRQ_26(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[IRQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' copied string element
TEST IRQ_27(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[IRQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' + 1 copied string element
TEST IRQ_28(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[IRQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if queue is not empty
TEST IRQ_29(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[IRQ-TEST] Stack is empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is not empty
TEST IRQ_30(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }

    ASSERT_FALSEm("[IRQ_TEST] Stack is empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 1 enqueue/dequeue
TEST IRQ_31(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    dequeue(&test);
    ASSERTm("[IRQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 'REALLOC_QUEUE_CHUNK' - 1 enqueue/dequeue
TEST IRQ_32(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }

    ASSERTm("[IRQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty after 'REALLOC_QUEUE_CHUNK' enqueue/dequeue
TEST IRQ_33(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }

    ASSERTm("[IRQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if queue is empty  'REALLOC_QUEUE_CHUNK' + 1 enqueue/dequeue
TEST IRQ_34(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        dequeue(&test);
    }

    ASSERTm("[IRQ-TEST] Stack is not empty.", is_empty_queue(test));

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 1 push and pop.
TEST IRQ_35(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    dequeue(&test);

    ASSERT_EQm("[IRQ-ERROR] Expected queue's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 'REALLOC_QUEUE_CHUNK' - 1 push and pop.
TEST IRQ_36(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }

    ASSERT_EQm("[IRQ-ERROR] Expected queue's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 'REALLOC_QUEUE_CHUNK' push and pop.
TEST IRQ_37(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }

    ASSERT_EQm("[IRQ-ERROR] Expected queue's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if elements is NULL after 'REALLOC_QUEUE_CHUNK' + 1 push and pop.
TEST IRQ_38(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        dequeue(&test);
    }

    ASSERT_EQm("[IRQ-ERROR] Expected queue's 'elements' parameter to be NULL.", NULL, test.elements);

    destroy_queue(&test, NULL);
    PASS();
}

/// Test if all one int values get incremented by 'increment'
TEST IRQ_39(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue(&test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all 'REALLOC_QUEUE_CHUNK' - 1 int values get incremented by 'increment'
TEST IRQ_40(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all 'REALLOC_QUEUE_CHUNK' int values get incremented by 'increment'
TEST IRQ_41(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all 'REALLOC_QUEUE_CHUNK' + 1 int values get incremented by 'increment'
TEST IRQ_42(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);

    PASS();
}

/// Test if all one string values have changed to new string value
TEST IRQ_43(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    QUEUE_DATA_TYPE element = dequeue(&test);
    ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_element(&element);

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Test if all 'REALLOC_QUEUE_CHUNK' - 1 string values have changed to new string value
TEST IRQ_44(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Test if all 'REALLOC_QUEUE_CHUNK' string values have changed to new string value
TEST IRQ_45(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Test if all 'REALLOC_QUEUE_CHUNK' + 1 string values have changed to new string value
TEST IRQ_46(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_element(&element);
    }

    destroy_queue(&test, destroy_element);

    PASS();
}

/// Tests if adding 'REALLOC_QUEUE_CHUNK' - 2, removing half and readding half elements is correct
TEST IRQ_47(void) {
    queue_s test = create_queue();
    queue_s temp = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 2) / 2; ++i) {
        enqueue(&temp, dequeue(&test));
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 2) / 2; ++i) {
        enqueue(&test, dequeue(&temp));
    }

    for (int i = (REALLOC_QUEUE_CHUNK - 2) / 2; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 2) / 2; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&temp, destroy_element);

    PASS();
}

/// Tests if adding 'REALLOC_QUEUE_CHUNK' - 1, removing half and readding half elements is correct
TEST IRQ_48(void) {
    queue_s test = create_queue();
    queue_s temp = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 1) / 2; ++i) {
        enqueue(&temp, dequeue(&test));
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 1) / 2; ++i) {
        enqueue(&test, dequeue(&temp));
    }

    for (int i = (REALLOC_QUEUE_CHUNK - 1) / 2; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 1) / 2; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&temp, destroy_element);

    PASS();
}

/// Tests if adding 'REALLOC_QUEUE_CHUNK', removing half and readding half elements is correct
TEST IRQ_49(void) {
    queue_s test = create_queue();
    queue_s temp = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK) / 2; ++i) {
        enqueue(&temp, dequeue(&test));
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK) / 2; ++i) {
        enqueue(&test, dequeue(&temp));
    }

    for (int i = (REALLOC_QUEUE_CHUNK) / 2; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK) / 2; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&temp, destroy_element);

    PASS();
}

/// Tests if adding 'REALLOC_QUEUE_CHUNK' + 1, removing half and readding half elements is correct
TEST IRQ_50(void) {
    queue_s test = create_queue();
    queue_s temp = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK + 1) / 2; ++i) {
        enqueue(&temp, dequeue(&test));
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK + 1) / 2; ++i) {
        enqueue(&test, dequeue(&temp));
    }

    for (int i = (REALLOC_QUEUE_CHUNK + 1) / 2; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }
    for (int i = 0; i < (REALLOC_QUEUE_CHUNK + 1) / 2; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Popped element not equal to i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&temp, destroy_element);

    PASS();
}

/// Tests if 3 * ('REALLOC_QUEUE_CHUNK' - 1) copied int element
TEST IRQ_51(void) {
    queue_s test = create_queue();
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK - 1); ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK - 1); ++i) {
        ASSERT_EQm("[IRQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Tests if 3 * ('REALLOC_QUEUE_CHUNK') copied int element
TEST IRQ_52(void) {
    queue_s test = create_queue();
    for (int i = 0; i < 3 * REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < 3 * REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Tests if 3 * ('REALLOC_QUEUE_CHUNK' + 1) copied int element
TEST IRQ_53(void) {
    queue_s test = create_queue();
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK + 1); ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK + 1); ++i) {
        ASSERT_EQm("[IRQ-TEST] Test queue is not equal to copy.", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' - 1 copied string element
TEST IRQ_54(void) {
    queue_s test = create_queue();
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK - 1); ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK - 1); ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[IRQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' copied string element
TEST IRQ_55(void) {
    queue_s test = create_queue();
    for (int i = 0; i < 3 * REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < 3 * REALLOC_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[IRQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

/// Test if 'REALLOC_QUEUE_CHUNK' + 1 copied string element
TEST IRQ_56(void) {
    queue_s test = create_queue();
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK + 1); ++i) {
        enqueue(&test, copy_element((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    queue_s copy = copy_queue(test, copy_element);
    for (int i = 0; i < 3 * (REALLOC_QUEUE_CHUNK + 1); ++i) {
        QUEUE_DATA_TYPE elemen_test = dequeue(&test);
        QUEUE_DATA_TYPE element_copy = dequeue(&copy);
        ASSERT_STRN_EQm("[IRQ-TEST] Test queue string is not equal to copy.", elemen_test.sub_two, element_copy.sub_two, sizeof(TEST_STRING) - 1);
        destroy_element(&elemen_test);
        destroy_element(&element_copy);
    }

    destroy_queue(&test, destroy_element);
    destroy_queue(&copy, destroy_element);
    PASS();
}

SUITE (infinite_realloc_queue_test) {
    RUN_TEST(IRQ_01); RUN_TEST(IRQ_02); RUN_TEST(IRQ_03); RUN_TEST(IRQ_04);
    RUN_TEST(IRQ_05); RUN_TEST(IRQ_06); RUN_TEST(IRQ_07); RUN_TEST(IRQ_08);
    RUN_TEST(IRQ_09); RUN_TEST(IRQ_10); RUN_TEST(IRQ_11); RUN_TEST(IRQ_12);
    RUN_TEST(IRQ_13); RUN_TEST(IRQ_14); RUN_TEST(IRQ_15); RUN_TEST(IRQ_16);
    RUN_TEST(IRQ_17); RUN_TEST(IRQ_18); RUN_TEST(IRQ_19); RUN_TEST(IRQ_20);
    RUN_TEST(IRQ_21); RUN_TEST(IRQ_22); RUN_TEST(IRQ_23); RUN_TEST(IRQ_24);
    RUN_TEST(IRQ_25); RUN_TEST(IRQ_26); RUN_TEST(IRQ_27); RUN_TEST(IRQ_28);
    RUN_TEST(IRQ_29); RUN_TEST(IRQ_30); RUN_TEST(IRQ_31); RUN_TEST(IRQ_32);
    RUN_TEST(IRQ_33); RUN_TEST(IRQ_34); RUN_TEST(IRQ_35); RUN_TEST(IRQ_36);
    RUN_TEST(IRQ_37); RUN_TEST(IRQ_38); RUN_TEST(IRQ_39); RUN_TEST(IRQ_40);
    RUN_TEST(IRQ_41); RUN_TEST(IRQ_42); RUN_TEST(IRQ_43); RUN_TEST(IRQ_44);
    RUN_TEST(IRQ_45); RUN_TEST(IRQ_46); RUN_TEST(IRQ_47); RUN_TEST(IRQ_48);
    RUN_TEST(IRQ_49); RUN_TEST(IRQ_50); RUN_TEST(IRQ_51); RUN_TEST(IRQ_52);
    RUN_TEST(IRQ_53); RUN_TEST(IRQ_54); RUN_TEST(IRQ_55); RUN_TEST(IRQ_56);
}

