#include <greatest.h>

#ifndef TEST_QUEUE_MODE

#error No queue mode was defined before testing ('TEST_QUEUE_MODE' is not defined).

#else

#define QUEUE_MODE TEST_QUEUE_MODE

#endif

//#define QUEUE_MODE INFINITE_LIST_QUEUE
#define LIST_ARRAY_QUEUE_CHUNK  10
#define REALLOC_QUEUE_CHUNK     10
#define PREPROCESSOR_QUEUE_SIZE 10
#include "queue.h"

#if   QUEUE_MODE == INFINITE_LIST_QUEUE

/// @brief Tests if size of queue is zero when creating it.
TEST test_010_01(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if current index of queue is zero when creating it.
TEST test_010_02(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if head of queue is NULL when creating it.
TEST test_010_03(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue head must be NULL.", NULL, test.head);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if tail of queue is NULL when creating it.
TEST test_010_04(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue tail must be NULL.", NULL, test.tail);
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (create_queue_test) {
    RUN_TEST(test_010_01);
    RUN_TEST(test_010_02);
    RUN_TEST(test_010_03);
    RUN_TEST(test_010_04);
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Tests if size of queue is zero when creating it.
TEST test_020_01(void) {
    queue_s test = create_queue(10);
    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if current index of queue is zero when creating it.
TEST test_020_02(void) {
    queue_s test = create_queue(10);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if maximum size of queue is 10 when creating it.
TEST test_020_03(void) {
    queue_s test = create_queue(10);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 10, test.max);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if elements pointer of queue is initialized when creating it.
TEST test_020_04(void) {
    queue_s test = create_queue(10);
    ASSERT_NEQm("[ERROR] Queue elements pointer must not be NULL.", NULL, test.elements);
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (create_queue_test) {
    RUN_TEST(test_020_01);
    RUN_TEST(test_020_02);
    RUN_TEST(test_020_03);
    RUN_TEST(test_020_04);
}

#elif QUEUE_MODE == INFINITE_REALLOC_QUEUE

/// @brief Tests if size of queue is zero when creating it.
TEST test_030_01(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if current index of queue is zero when creating it.
TEST test_030_02(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if elements pointer of queue is NULL when creating it.
TEST test_030_03(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue current index must be zero.", NULL, test.elements);
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (create_queue_test) {
    RUN_TEST(test_030_01);
    RUN_TEST(test_030_02);
    RUN_TEST(test_030_03);
}

#elif QUEUE_MODE == FINITE_PRERPOCESSOR_QUEUE

/// @brief Tests if size of queue is zero when creating it.
TEST test_040_01(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if current index of queue is zero when creating it.
TEST test_040_02(void) {
    queue_s test = create_queue();
    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.current);
    destroy_queue(&test, NULL);

    PASS();
}

/// @brief Tests if elements array of queue is correct size when creating it.
TEST test_040_03(void) {
    queue_s test = create_queue();
    ASSERT_EQm(
        "[ERROR] Queue size must be zero.",
        PREPROCESSOR_QUEUE_SIZE, sizeof(test.elements) / sizeof(QUEUE_DATA_TYPE)
    );
    destroy_queue(&test, NULL);

    PASS();
}

SUITE (create_queue_test) {
    RUN_TEST(test_040_01);
    RUN_TEST(test_040_02);
    RUN_TEST(test_040_03);
}

#endif
