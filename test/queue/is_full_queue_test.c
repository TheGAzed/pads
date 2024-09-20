#include <greatest.h>

#ifndef TEST_QUEUE_MODE

#error No queue mode was defined before testing ('TEST_QUEUE_MODE' is not defined).

#else

#define QUEUE_MODE TEST_QUEUE_MODE

#endif

//#define QUEUE_MODE FINITE_PRERPOCESSOR_QUEUE
#define LIST_ARRAY_QUEUE_CHUNK  10
#define REALLOC_QUEUE_CHUNK     10
#define PREPROCESSOR_QUEUE_SIZE 10
#define QUEUE_DATA_TYPE int
#include "queue.h"

#if   QUEUE_MODE == INFINITE_LIST_QUEUE

SUITE (is_full_queue_test) {
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Tests if empty queue of size 10 is not full.
TEST test_020_01(void) {
    queue_s test = create_queue(10);
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one value of size 10 is not full.
TEST test_020_02(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if enqueued, then dequeued queue of size 10 is not full.
TEST test_020_03(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 9 value of size 10 is not full.
TEST test_020_04(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, 42);
    }
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue enqueuend with 10 values and then dequeued once of size 10 is not full.
TEST test_020_05(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, 42);
    }
    dequeue(&test);
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue enqueuend with 10 values size 10 is full.
TEST test_020_06(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, 42);
    }
    ASSERTm("[ERROR] Queue must be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (is_full_queue_test) {
    RUN_TEST(test_020_01);
    RUN_TEST(test_020_02);
    RUN_TEST(test_020_03);
    RUN_TEST(test_020_04);
    RUN_TEST(test_020_05);
    RUN_TEST(test_020_06);
}

#elif QUEUE_MODE == INFINITE_REALLOC_QUEUE

SUITE (is_full_queue_test) {
}

#elif QUEUE_MODE == FINITE_PRERPOCESSOR_QUEUE

/// @brief Tests if empty queue of size 'PREPROCESSOR_QUEUE_SIZE' is not full.
TEST test_040_01(void) {
    queue_s test = create_queue();
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one value of size 'PREPROCESSOR_QUEUE_SIZE' is not full.
TEST test_040_02(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if enqueued, then dequeued queue of size 'PREPROCESSOR_QUEUE_SIZE' is not full.
TEST test_040_03(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 9 value of size 'PREPROCESSOR_QUEUE_SIZE' is not full.
TEST test_040_04(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, 42);
    }
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue enqueuend with 10 values and then dequeued once of size 'PREPROCESSOR_QUEUE_SIZE' is not full.
TEST test_040_05(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, 42);
    }
    dequeue(&test);
    ASSERT_FALSEm("[ERROR] Queue cannot be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue enqueuend with 10 values size 'PREPROCESSOR_QUEUE_SIZE' is full.
TEST test_040_06(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, 42);
    }
    ASSERTm("[ERROR] Queue must be full.", is_full_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (is_full_queue_test) {
    RUN_TEST(test_040_01);
    RUN_TEST(test_040_02);
    RUN_TEST(test_040_03);
    RUN_TEST(test_040_04);
    RUN_TEST(test_040_05);
    RUN_TEST(test_040_06);
}

#endif
