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

/// @brief Tests if queue with one valid value peeked correctly.
TEST test_010_01(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and one invalid value peeked correctly.
TEST test_010_02(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'LIST_ARRAY_QUEUE_CHUNK' - 2 invalid value peeked correctly.
TEST test_010_03(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'LIST_ARRAY_QUEUE_CHUNK' - 1 invalid value peeked correctly.
TEST test_010_04(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'LIST_ARRAY_QUEUE_CHUNK' invalid value peeked correctly.
TEST test_010_05(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one invalid and one valid value peeked correctly after dequeueing once.
TEST test_010_06(void) {
    queue_s test = create_queue();
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'LIST_ARRAY_QUEUE_CHUNK' - 2 invalid value and one valid peeked correctly
/// after dequeueing 'LIST_ARRAY_QUEUE_CHUNK' - 2 times.
TEST test_010_07(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'LIST_ARRAY_QUEUE_CHUNK' - 1 invalid value and one valid peeked correctly
/// after dequeueing 'LIST_ARRAY_QUEUE_CHUNK' - 1 times.
TEST test_010_08(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'LIST_ARRAY_QUEUE_CHUNK' invalid value and one valid peeked correctly
/// after dequeueing 'LIST_ARRAY_QUEUE_CHUNK' times.
TEST test_010_09(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (peek_queue_test) {
    RUN_TEST(test_010_01);
    RUN_TEST(test_010_02);
    RUN_TEST(test_010_03);
    RUN_TEST(test_010_04);
    RUN_TEST(test_010_05);
    RUN_TEST(test_010_06);
    RUN_TEST(test_010_07);
    RUN_TEST(test_010_08);
    RUN_TEST(test_010_09);
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Tests if queue of size 10 with one valid value peeked correctly.
TEST test_020_01(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue of size 10 with one valid and one invalid value peeked correctly.
TEST test_020_02(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue of size 10 with one valid and 8 invalid value peeked correctly.
TEST test_020_03(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);

    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue of size 10 with one valid and 9 invalid value peeked correctly.
TEST test_020_04(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);

    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue of size 10 with one invalid and one valid value peeked correctly after dequeueing once.
TEST test_020_05(void) {
    queue_s test = create_queue(10);
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue of size 10 with 8 invalid value and one valid peeked correctly
/// after dequeueing 8 times.
TEST test_020_06(void) {
    queue_s test = create_queue(10);

    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < test.max - 2; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue of size 10 with 9 invalid value and one valid peeked correctly
/// after dequeueing 9 times.
TEST test_020_07(void) {
    queue_s test = create_queue(10);

    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < test.max - 1; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue oif size 10 with 10 invalid value and one valid peeked correctly after dequeueing 10 times.
TEST test_020_08(void) {
    queue_s test = create_queue(10);

    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < test.max; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (peek_queue_test) {
    RUN_TEST(test_020_01);
    RUN_TEST(test_020_02);
    RUN_TEST(test_020_03);
    RUN_TEST(test_020_04);
    RUN_TEST(test_020_05);
    RUN_TEST(test_020_06);
    RUN_TEST(test_020_07);
    RUN_TEST(test_020_08);
}

#elif QUEUE_MODE == INFINITE_REALLOC_QUEUE

/// @brief Tests if queue with one valid value peeked correctly.
TEST test_030_01(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and one invalid value peeked correctly.
TEST test_030_02(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'REALLOC_QUEUE_CHUNK' - 2 invalid value peeked correctly.
TEST test_030_03(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'REALLOC_QUEUE_CHUNK' - 1 invalid value peeked correctly.
TEST test_030_04(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'REALLOC_QUEUE_CHUNK' invalid value peeked correctly.
TEST test_030_05(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one invalid and one valid value peeked correctly after dequeueing once.
TEST test_030_06(void) {
    queue_s test = create_queue();
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'REALLOC_QUEUE_CHUNK' - 2 invalid value and one valid peeked correctly
/// after dequeueing 'REALLOC_QUEUE_CHUNK' - 2 times.
TEST test_030_07(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'REALLOC_QUEUE_CHUNK' - 1 invalid value and one valid peeked correctly
/// after dequeueing 'REALLOC_QUEUE_CHUNK' - 1 times.
TEST test_030_08(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'REALLOC_QUEUE_CHUNK' invalid value and one valid peeked correctly
/// after dequeueing 'REALLOC_QUEUE_CHUNK' times.
TEST test_030_09(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (peek_queue_test) {
    RUN_TEST(test_030_01);
    RUN_TEST(test_030_02);
    RUN_TEST(test_030_03);
    RUN_TEST(test_030_04);
    RUN_TEST(test_030_05);
    RUN_TEST(test_030_06);
    RUN_TEST(test_030_07);
    RUN_TEST(test_030_08);
    RUN_TEST(test_030_09);
}

#elif QUEUE_MODE == FINITE_PRERPOCESSOR_QUEUE

/// @brief Tests if queue with one valid value peeked correctly.
TEST test_020_01(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and one invalid value peeked correctly.
TEST test_020_02(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'PREPROCESSOR_QUEUE_SIZE' - 2 invalid value peeked correctly.
TEST test_020_03(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one valid and 'PREPROCESSOR_QUEUE_SIZE' - 1 invalid value peeked correctly.
TEST test_020_04(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with one invalid and one valid value peeked correctly after dequeueing once.
TEST test_020_05(void) {
    queue_s test = create_queue();
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'PREPROCESSOR_QUEUE_SIZE' - 2 invalid value and one valid peeked correctly
/// after dequeueing 'PREPROCESSOR_QUEUE_SIZE' - 2 times.
TEST test_020_06(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue of size 10 with 'PREPROCESSOR_QUEUE_SIZE' - 1 invalid value and one valid peeked correctly
/// after dequeueing 'PREPROCESSOR_QUEUE_SIZE' - 1 times.
TEST test_020_07(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if queue with 'PREPROCESSOR_QUEUE_SIZE' invalid value and one valid peeked correctly after
/// dequeueing 'PREPROCESSOR_QUEUE_SIZE' times.
TEST test_020_08(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, -1);
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        dequeue(&test);
    }
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Queue peeked wrong value.", 42, peek_queue(test));
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (peek_queue_test) {
    RUN_TEST(test_020_01);
    RUN_TEST(test_020_02);
    RUN_TEST(test_020_03);
    RUN_TEST(test_020_04);
    RUN_TEST(test_020_05);
    RUN_TEST(test_020_06);
    RUN_TEST(test_020_07);
    RUN_TEST(test_020_08);
}

#endif
