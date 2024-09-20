#include <greatest.h>

#ifndef TEST_QUEUE_MODE

#error No queue mode was defined before testing ('TEST_QUEUE_MODE' is not defined).

#else

#define QUEUE_MODE TEST_QUEUE_MODE

#endif

//#define QUEUE_MODE FINITE_ALLOCATED_QUEUE
#define LIST_ARRAY_QUEUE_CHUNK  10
#define REALLOC_QUEUE_CHUNK     10
#define PREPROCESSOR_QUEUE_SIZE 10
#define QUEUE_DATA_TYPE int
#include "queue.h"

#if   QUEUE_MODE == INFINITE_LIST_QUEUE

/// @brief Tests if start value is valid after enqueue.
TEST test_010_01(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and one invalud value.
TEST test_010_02(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'LIST_ARRAY_QUEUE_CHUNK' - 2 invalid values.
TEST test_010_03(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'LIST_ARRAY_QUEUE_CHUNK' - 1 invalid values.
TEST test_010_04(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'LIST_ARRAY_QUEUE_CHUNK' invalid values.
TEST test_010_05(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'LIST_ARRAY_QUEUE_CHUNK' + 1 invalid values.
TEST test_010_06(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one invalid,one valid value and then dequeueing once.
TEST test_010_07(void) {
    queue_s test = create_queue();
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' - 2 invalid values
/// and one valid value.
TEST test_010_08(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' - 1 invalid values
/// and one valid value.
TEST test_010_09(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' invalid values
/// and one valid value.
TEST test_010_10(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' + 1 invalid values
/// and one valid value.
TEST test_010_11(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' - 2 invalid values
/// and one valid value.
TEST test_010_12(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' - 1 invalid values
/// and one valid value.
TEST test_010_13(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' invalid values
/// and one valid value.
TEST test_010_14(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' + 1 invalid values
/// and one valid value.
TEST test_010_15(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (dequeue_test) {
    RUN_TEST(test_010_01);
    RUN_TEST(test_010_02);
    RUN_TEST(test_010_03);
    RUN_TEST(test_010_04);
    RUN_TEST(test_010_05);
    RUN_TEST(test_010_06);
    RUN_TEST(test_010_07);
    RUN_TEST(test_010_08);
    RUN_TEST(test_010_09);
    RUN_TEST(test_010_10);
    RUN_TEST(test_010_11);
    RUN_TEST(test_010_12);
    RUN_TEST(test_010_13);
    RUN_TEST(test_010_14);
    RUN_TEST(test_010_15);
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Tests if start value is valid after enqueue.
TEST test_020_01(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and one invalud value.
TEST test_020_02(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 8 invalid values.
TEST test_020_03(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 9 invalid values.
TEST test_020_04(void) {
    queue_s test = create_queue(10);
    enqueue(&test, 42);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one invalid, one valid value and then dequeueing once.
TEST test_020_05(void) {
    queue_s test = create_queue(10);
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 8 invalid values and one valid value.
TEST test_020_06(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < test.max - 2; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 9 invalid values and one valid value.
TEST test_020_07(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < test.max - 1; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 8 values.
TEST test_020_08(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < test.max - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 9 invalid values and one valid value.
TEST test_020_09(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < test.max - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 9 invalid values and one valid value.
TEST test_020_10(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < test.max; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (dequeue_test) {
    RUN_TEST(test_020_01);
    RUN_TEST(test_020_02);
    RUN_TEST(test_020_03);
    RUN_TEST(test_020_04);
    RUN_TEST(test_020_05);
    RUN_TEST(test_020_06);
    RUN_TEST(test_020_07);
    RUN_TEST(test_020_08);
    RUN_TEST(test_020_09);
    RUN_TEST(test_020_10);
}

#elif QUEUE_MODE == INFINITE_REALLOC_QUEUE

/// @brief Tests if start value is valid after enqueue.
TEST test_030_01(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and one invalud value.
TEST test_030_02(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'REALLOC_QUEUE_CHUNK' - 2 invalid values.
TEST test_030_03(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'REALLOC_QUEUE_CHUNK' - 1 invalid values.
TEST test_030_04(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'REALLOC_QUEUE_CHUNK' invalid values.
TEST test_030_05(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'REALLOC_QUEUE_CHUNK' + 1 invalid values.
TEST test_030_06(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one invalid,one valid value and then dequeueing once.
TEST test_030_07(void) {
    queue_s test = create_queue();
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' - 2 invalid values
/// and one valid value.
TEST test_030_08(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' - 1 invalid values
/// and one valid value.
TEST test_030_09(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' invalid values
/// and one valid value.
TEST test_030_10(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' + 1 invalid values
/// and one valid value.
TEST test_030_11(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' - 2 invalid values
/// and one valid value.
TEST test_030_12(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' - 1 invalid values
/// and one valid value.
TEST test_030_13(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' invalid values
/// and one valid value.
TEST test_030_14(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' + 1 invalid values
/// and one valid value.
TEST test_030_15(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (dequeue_test) {
    RUN_TEST(test_030_01);
    RUN_TEST(test_030_02);
    RUN_TEST(test_030_03);
    RUN_TEST(test_030_04);
    RUN_TEST(test_030_05);
    RUN_TEST(test_030_06);
    RUN_TEST(test_030_07);
    RUN_TEST(test_030_08);
    RUN_TEST(test_030_09);
    RUN_TEST(test_030_10);
    RUN_TEST(test_030_11);
    RUN_TEST(test_030_12);
    RUN_TEST(test_030_13);
    RUN_TEST(test_030_14);
    RUN_TEST(test_030_15);
}

#elif QUEUE_MODE == FINITE_PRERPOCESSOR_QUEUE


/// @brief Tests if start value is valid after enqueue.
TEST test_040_01(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and one invalud value.
TEST test_040_02(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    enqueue(&test, -1);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'PREPROCESSOR_QUEUE_SIZE' - 2 invalid values.
TEST test_040_03(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one valid and 'PREPROCESSOR_QUEUE_SIZE' - 1 invalid values.
TEST test_040_04(void) {
    queue_s test = create_queue();
    enqueue(&test, 42);
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, -1);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if start value is valid after enqueueing one invalid, one valid value and then dequeueing once.
TEST test_040_05(void) {
    queue_s test = create_queue();
    enqueue(&test, -1);
    enqueue(&test, 42);
    dequeue(&test);
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'PREPROCESSOR_QUEUE_SIZE' - 2 values.
TEST test_040_06(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'PREPROCESSOR_QUEUE_SIZE' - 1 values.
TEST test_040_07(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, -1);
    }
    enqueue(&test, 42);
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        dequeue(&test);
    }
    ASSERT_EQm("[ERROR] Expected peek equal to 42.", 42, dequeue(&test));
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'PREPROCESSOR_QUEUE_SIZE' - 2 values.
TEST test_040_08(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'PREPROCESSOR_QUEUE_SIZE' - 1 values.
TEST test_040_09(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if all values are valid after enqueueing and dequeueing 'PREPROCESSOR_QUEUE_SIZE' values.
TEST test_040_10(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, i);
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected peek equal to i.", i, dequeue(&test));
    }
    destroy_queue(&test, NULL);

    PASS();
}


SUITE (dequeue_test) {
    RUN_TEST(test_040_01);
    RUN_TEST(test_040_02);
    RUN_TEST(test_040_03);
    RUN_TEST(test_040_04);
    RUN_TEST(test_040_05);
    RUN_TEST(test_040_06);
    RUN_TEST(test_040_07);
    RUN_TEST(test_040_08);
    RUN_TEST(test_040_09);
    RUN_TEST(test_040_10);
}

#endif
