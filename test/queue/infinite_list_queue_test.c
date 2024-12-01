#include "queue_test.h"

#define QUEUE_MODE INFINITE_LIST_QUEUE
#define LIST_ARRAY_QUEUE_CHUNK (1 << 4)
#include <queue.h>

/// Tests if queue is initialized correctly when creating it.
TEST ILQ_01(void) {
    queue_s test = create_queue();

    ASSERT_EQm("[ILQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[ILQ-ERROR] Test queue current is not zero.", 0, test.current);
    ASSERT_EQm("[ILQ-ERROR] Test queue head is not NULL.", NULL, test.head);
    ASSERT_EQm("[ILQ-ERROR] Test queue tail is not NULL.", NULL, test.tail);

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if queue is initialized correctly when creating and then destroying it.
TEST ILQ_02(void) {
    queue_s test = create_queue();
    destroy_queue(&test, NULL);

    ASSERT_EQm("[ILQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[ILQ-ERROR] Test queue current is not zero.", 0, test.current);
    ASSERT_EQm("[ILQ-ERROR] Test queue head is not NULL.", NULL, test.head);
    ASSERT_EQm("[ILQ-ERROR] Test queue tail is not NULL.", NULL, test.tail);

    PASS();
}

/// Tests if one enqueued element is correct.
TEST ILQ_03(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}


/// Tests if 'LIST_ARRAY_QUEUE_CHUNK' - 1 enqueued element is correct.
TEST ILQ_04(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_QUEUE_CHUNK' enqueued element is correct.
TEST ILQ_05(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_QUEUE_CHUNK' + 1 enqueued element is correct.
TEST ILQ_06(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if sequence of enqueued numbers is correct
TEST ILQ_07(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= LIST_ARRAY_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

SUITE (infinite_list_queue_test) {
    RUN_TEST(ILQ_01); RUN_TEST(ILQ_02); RUN_TEST(ILQ_03); RUN_TEST(ILQ_04);
    RUN_TEST(ILQ_05); RUN_TEST(ILQ_06); RUN_TEST(ILQ_07);
}
