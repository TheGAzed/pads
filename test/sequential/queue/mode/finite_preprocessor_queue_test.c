#include "queue_test.h"

#include <functions.h>

#define QUEUE_DATA_TYPE DATA_TYPE
#define QUEUE_MODE FINITE_PREPROCESSOR_QUEUE_MODE
#define PREPROCESSOR_QUEUE_SIZE (1 << 4)
#include <sequential/queue/queue.h>

TEST FPQ_CREATE_01(void) {
    queue_s test = create_queue();

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_DESTROY_01(void) {
    queue_s test = create_queue();
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_DESTROY_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_DESTROY_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_DESTROY_04(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_DESTROY_05(void) {
    queue_s test = create_queue();
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_DESTROY_06(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_DESTROY_07(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_DESTROY_08(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);

    PASS();
}

TEST FPQ_IS_FULL_01(void) {
    queue_s test = create_queue();

    ASSERT_FALSEm("[FPQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_IS_FULL_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[FPQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_IS_FULL_03(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[FPQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_IS_FULL_04(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERTm("[FPQ-ERROR] Expected queue to be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_PEEK_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[FPQ-ERROR] Expected to peek 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_PEEK_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FPQ-ERROR] Expected to peek 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_PEEK_03(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[FPQ-ERROR] Expected to peek 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_ENQUEUE_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPQ-ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_ENQUEUE_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_ENQUEUE_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_DEQUEUE_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[FPQ-ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_DEQUEUE_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_DEQUEUE_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_COPY_01(void) {
    queue_s test = create_queue();

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FPQ_COPY_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[FPQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FPQ_COPY_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FPQ_COPY_04(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST FPQ_COPY_05(void) {
    queue_s test = create_queue();

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FPQ_COPY_06(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[FPQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FPQ_COPY_07(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_STRN_EQm("[FPQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FPQ_COPY_08(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[FPQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[FPQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_STRN_EQm("[FPQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST FPQ_IS_EMPTY_01(void) {
    queue_s test = create_queue();

    ASSERTm("[FPQ-ERROR] Expected queue to be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_IS_EMPTY_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPQ-ERROR] Expected queue to not be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_IS_EMPTY_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[FPQ-ERROR] Expected queue to not be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_CLEAR_01(void) {
    queue_s test = create_queue();

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_CLEAR_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_CLEAR_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_CLEAR_04(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_CLEAR_05(void) {
    queue_s test = create_queue();

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FPQ_CLEAR_06(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FPQ_CLEAR_07(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FPQ_CLEAR_08(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[FPQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_NEQm("[FPQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST FPQ_FOREACH_01(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    ASSERT_EQm("[FPQ-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FPQ_FOREACH_02(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FPQ_FOREACH_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST FPQ_FOREACH_04(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    QUEUE_DATA_TYPE element = dequeue(&test);
    ASSERT_STRN_EQm("[FPQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FPQ_FOREACH_05(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[FPQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FPQ_FOREACH_06(void) {
    queue_s test = create_queue();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[FPQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST FPQ_MAP_01(void) {
    queue_s test = create_queue();

    map_queue(&test, sort_int, compare_int);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_MAP_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });

    map_queue(&test, sort_int, compare_int);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_MAP_03(void) {
    queue_s test = create_queue();

    for (int i = (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_int);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_MAP_04(void) {
    queue_s test = create_queue();

    for (int i = (PREPROCESSOR_QUEUE_SIZE) >> 1; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_int);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_MAP_05(void) {
    queue_s test = create_queue();

    for (int i = (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_reverse_int);

    for (int i = PREPROCESSOR_QUEUE_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FPQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST FPQ_MAP_06(void) {
    queue_s test = create_queue();

    for (int i = (PREPROCESSOR_QUEUE_SIZE) >> 1; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    map_queue(&test, sort_int, compare_reverse_int);

    for (int i = PREPROCESSOR_QUEUE_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FPQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

SUITE (finite_preprocessor_queue_test) {
    // create
    RUN_TEST(FPQ_CREATE_01);
    // destroy
    RUN_TEST(FPQ_DESTROY_01); RUN_TEST(FPQ_DESTROY_02); RUN_TEST(FPQ_DESTROY_03); RUN_TEST(FPQ_DESTROY_04); RUN_TEST(FPQ_DESTROY_05);
    RUN_TEST(FPQ_DESTROY_06); RUN_TEST(FPQ_DESTROY_07); RUN_TEST(FPQ_DESTROY_08);
    // is full
    RUN_TEST(FPQ_IS_FULL_01); RUN_TEST(FPQ_IS_FULL_02); RUN_TEST(FPQ_IS_FULL_03); RUN_TEST(FPQ_IS_FULL_04);
    // peek
    RUN_TEST(FPQ_PEEK_01); RUN_TEST(FPQ_PEEK_02); RUN_TEST(FPQ_PEEK_03);
    // push
    RUN_TEST(FPQ_ENQUEUE_01); RUN_TEST(FPQ_ENQUEUE_02); RUN_TEST(FPQ_ENQUEUE_03);
    // pop
    RUN_TEST(FPQ_DEQUEUE_01); RUN_TEST(FPQ_DEQUEUE_02); RUN_TEST(FPQ_DEQUEUE_03);
    // copy
    RUN_TEST(FPQ_COPY_01); RUN_TEST(FPQ_COPY_02); RUN_TEST(FPQ_COPY_03); RUN_TEST(FPQ_COPY_04); RUN_TEST(FPQ_COPY_05);
    RUN_TEST(FPQ_COPY_06); RUN_TEST(FPQ_COPY_07); RUN_TEST(FPQ_COPY_08);
    // is empty
    RUN_TEST(FPQ_IS_EMPTY_01); RUN_TEST(FPQ_IS_EMPTY_02); RUN_TEST(FPQ_IS_EMPTY_03);
    // clear
    RUN_TEST(FPQ_CLEAR_01); RUN_TEST(FPQ_CLEAR_02); RUN_TEST(FPQ_CLEAR_03); RUN_TEST(FPQ_CLEAR_04); RUN_TEST(FPQ_CLEAR_05);
    RUN_TEST(FPQ_CLEAR_06); RUN_TEST(FPQ_CLEAR_07); RUN_TEST(FPQ_CLEAR_08);
    // foreach
    RUN_TEST(FPQ_FOREACH_01); RUN_TEST(FPQ_FOREACH_02); RUN_TEST(FPQ_FOREACH_03); RUN_TEST(FPQ_FOREACH_04); RUN_TEST(FPQ_FOREACH_05);
    RUN_TEST(FPQ_FOREACH_06);
    // map
    RUN_TEST(FPQ_MAP_01); RUN_TEST(FPQ_MAP_02); RUN_TEST(FPQ_MAP_03); RUN_TEST(FPQ_MAP_04); RUN_TEST(FPQ_MAP_05);
    RUN_TEST(FPQ_MAP_06);
}

