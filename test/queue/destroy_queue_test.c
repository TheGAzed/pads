#include <greatest.h>

#ifndef TEST_QUEUE_MODE

#error No queue mode was defined before testing ('TEST_QUEUE_MODE' is not defined).

#else

#define QUEUE_MODE TEST_QUEUE_MODE

#endif

//#define QUEUE_MODE FINITE_PRERPOCESSOR_QUEUE
#define QUEUE_DATA_TYPE         char*
#define LIST_ARRAY_QUEUE_CHUNK  10
#define REALLOC_QUEUE_CHUNK     10
#define PREPROCESSOR_QUEUE_SIZE 10
#include "queue.h"

#define STRING_VALUE "thegazed"
QUEUE_DATA_TYPE create_string_d(void) {
    QUEUE_DATA_TYPE string = calloc((sizeof(STRING_VALUE)), sizeof(char));
    assert(string && "[ERROR] Memory allocation failed.");
    strncpy(string, STRING_VALUE, sizeof(STRING_VALUE) - 1);
    return string;
}

void destroy_string_d(QUEUE_DATA_TYPE * string) {
    free(*string);
}

#if   QUEUE_MODE == INFINITE_LIST_QUEUE

/// @brief Tests if queue is uninitialized correctly when enqueueing one value and destroying it.
TEST test_010_01(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_d());
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing one value and destroying it.
TEST test_010_02(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_d());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_d(&string);
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'LIST_ARRAY_QUEUE_CHUNK' - 1
/// values and destroying it.
TEST test_010_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'LIST_ARRAY_QUEUE_CHUNK' values and destroying it.
TEST test_010_04(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'LIST_ARRAY_QUEUE_CHUNK' + 1
/// values and destroying it.
TEST test_010_05(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' - 1 values
/// and destroying it.
TEST test_010_06(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' values
/// and destroying it.
TEST test_010_07(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_d());
    }
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is destroyed when enqueueing and dequeueing 'LIST_ARRAY_QUEUE_CHUNK' + 1 values
/// and destroying it.
TEST test_010_08(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is destroyed when enqueueing 'LIST_ARRAY_QUEUE_CHUNK' - 1 and dequeueing only
/// 'LIST_ARRAY_QUEUE_CHUNK' - 2 values and destroying it.
TEST test_010_09(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is destroyed when enqueueing 'LIST_ARRAY_QUEUE_CHUNK' and dequeueing only
/// 'LIST_ARRAY_QUEUE_CHUNK' - 2 values and destroying it.
TEST test_010_10(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_d());
    }
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

/// @brief Tests if queue is destroyed when enqueueing 'LIST_ARRAY_QUEUE_CHUNK' + 1 and dequeueing only
/// 'LIST_ARRAY_QUEUE_CHUNK' values and destroying it.
TEST test_010_11(void) {
    queue_s test = create_queue();

    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue head must be zero.", NULL, test.head);
    ASSERT_EQm("[ERROR] Queue tail must be zero.", NULL, test.tail);

    PASS();
}

SUITE (destroy_queue_test) {
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
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Tests if queue is uninitialized correctly when enqueueing one value and destroying it.
TEST test_020_01(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_d());
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequqeueing one value and destroying it.
TEST test_020_02(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_d());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_d(&string);
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 9 values and destroying it.
TEST test_020_03(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 10 values and destroying it.
TEST test_020_04(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 9 values and destroying it.
TEST test_020_05(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < test.max - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 10 values and destroying it.
TEST test_020_06(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < test.max; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 9 and dequeueing 8 values and destroying it.
TEST test_020_07(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < test.max - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 10 and ddequeueing 9 values and destroying it.
TEST test_020_08(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < test.max - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

SUITE (destroy_queue_test) {
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

/// @brief Tests if queue is uninitialized correctly when enqueueing one value and destroying it.
TEST test_030_01(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_d());
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing one value and destroying it.
TEST test_030_02(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_d());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_d(&string);
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'REALLOC_QUEUE_CHUNK' - 1 value and destroying it.
TEST test_030_03(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'REALLOC_QUEUE_CHUNK' value and destroying it.
TEST test_030_04(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'REALLOC_QUEUE_CHUNK' + 1 value and destroying it.
TEST test_030_05(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' - 1
/// value and destroying it.
TEST test_030_06(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing end dequeueing 'REALLOC_QUEUE_CHUNK'
/// value and destroying it.
TEST test_030_07(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 'REALLOC_QUEUE_CHUNK' + 1
/// value and destroying it.
TEST test_030_08(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'REALLOC_QUEUE_CHUNK' - 1, but dequeueing only
/// 'REALLOC_QUEUE_CHUNK' - 2 value and destroying it.
TEST test_030_09(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'REALLOC_QUEUE_CHUNK', but dequeueing only
/// 'REALLOC_QUEUE_CHUNK' - 1 value and destroying it.
TEST test_030_10(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 'REALLOC_QUEUE_CHUNK' + 1, but dequeueign only
/// 'REALLOC_QUEUE_CHUNK' value and destroying it.
TEST test_030_11(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);
    ASSERT_EQm("[ERROR] Queue elements array must be zero.", NULL, test.elements);

    PASS();
}

SUITE (destroy_queue_test) {
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
}

#elif QUEUE_MODE == FINITE_PRERPOCESSOR_QUEUE

/// @brief Tests if queue is uninitialized correctly when enqueueing one value and destroying it.
TEST test_040_01(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_d());
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequqeueing one value and destroying it.
TEST test_040_02(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_d());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_d(&string);
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 9 values and destroying it.
TEST test_040_03(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 10 values and destroying it.
TEST test_040_04(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, create_string_d());
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 9 values and destroying it.
TEST test_040_05(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing and dequeueing 10 values and destroying it.
TEST test_040_06(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 9 and dequeueing 8 values and destroying it.
TEST test_040_07(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

/// @brief Tests if queue is uninitialized correctly when enqueueing 10 and ddequeueing 9 values and destroying it.
TEST test_040_08(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, create_string_d());
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_d(&string);
    }
    destroy_queue(&test, destroy_string_d);

    ASSERT_EQm("[ERROR] Queue size must be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Queue current index must be zero.", 0, test.current);

    PASS();
}

SUITE (destroy_queue_test) {
    RUN_TEST(test_040_01);
    RUN_TEST(test_040_02);
    RUN_TEST(test_040_03);
    RUN_TEST(test_040_04);
    RUN_TEST(test_040_05);
    RUN_TEST(test_040_06);
    RUN_TEST(test_040_07);
    RUN_TEST(test_040_08);
}

#endif
