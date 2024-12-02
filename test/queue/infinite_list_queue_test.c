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

/// Tests if one enqueued element is peeked correctly.
TEST ILQ_03(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[ILQ-ERROR] Test queue peeked element not 42.", 42, peek_queue(test).sub_one);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if 'LIST_ARRAY_QUEUE_CHUNK' - 1 enqueued element is peeked correctly.
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

/// Tests if 'LIST_ARRAY_QUEUE_CHUNK' enqueued element is peeked correctly.
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

/// Tests if 'LIST_ARRAY_QUEUE_CHUNK' + 1 enqueued element is peeked correctly.
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

/// Tests if sequence of 'LIST_ARRAY_QUEUE_CHUNK' - 1 enqueued numbers is dequeued correctly
TEST ILQ_07(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if sequence of 'LIST_ARRAY_QUEUE_CHUNK' enqueued numbers is dequeued correctly
TEST ILQ_08(void) {
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

/// Tests if sequence of 'LIST_ARRAY_QUEUE_CHUNK' - 1 enqueued numbers is dequeued correctly
TEST ILQ_09(void) {
    queue_s test = create_queue();

    for (int i = 1; i <= LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 1; i <= LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILQ-ERROR] Test queue dequeued element not 'i'.", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, NULL);
    PASS();
}

/// Tests if peek does not change size
TEST ILQ_10(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    peek_queue(test);

    ASSERT_EQm("[ILQ-ERROR] Expected queue size to not change after peek.", 1, test.size);

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is empty when creating it.
TEST ILQ_11(void) {
    queue_s test = create_queue();

    ASSERTm("[ELQ-ERROR] Expected queue to be empty when creating it.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

/// Tests if queue is not empty when enqueueing element.
TEST ILQ_12(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERTm("[ELQ-ERROR] Expected queue to not be empty when enqueueing element.", is_empty_queue(test));

    destroy_queue(&test, NULL);

    PASS();
}

SUITE (infinite_list_queue_test) {
    RUN_TEST(ILQ_01); RUN_TEST(ILQ_02); RUN_TEST(ILQ_03); RUN_TEST(ILQ_04);
    RUN_TEST(ILQ_05); RUN_TEST(ILQ_06); RUN_TEST(ILQ_07); RUN_TEST(ILQ_08);
    RUN_TEST(ILQ_09); RUN_TEST(ILQ_10); RUN_TEST(ILQ_11); RUN_TEST(ILQ_12);
}
