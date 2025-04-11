#include "queue_test.h"

#define QUEUE_MODE INFINITE_REALLOC_QUEUE
#define REALLOC_QUEUE_CHUNK (1 << 4)
#include <queue/queue.h>

TEST IRQ_CREATE_01(void) {
    queue_s test = create_queue();

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_DESTROY_01(void) {
    queue_s test = create_queue();
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_04(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_05(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    destroy_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_06(void) {
    queue_s test = create_queue();
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_07(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_08(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_09(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_DESTROY_10(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }
    destroy_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    PASS();
}

TEST IRQ_IS_FULL_01(void) {
    queue_s test = create_queue();

    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_IS_FULL_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_IS_FULL_03(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_IS_FULL_04(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_IS_FULL_05(void) {
    queue_s test = create_queue();

    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }
    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be full", is_full_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_PEEK_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    ASSERT_EQm("[IRQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_PEEK_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_PEEK_03(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_PEEK_04(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_PEEK_05(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = -1, });
    }

    ASSERT_EQm("[IRQ-ERROR] Expected to peep 42", 42, peek_queue(test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_ENQUEUE_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRQ-ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_ENQUEUE_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_ENQUEUE_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_ENQUEUE_04(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_DEQUEUE_01(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    ASSERT_EQm("[IRQ-ERROR] Expected to pop 42", 42, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_DEQUEUE_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_DEQUEUE_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_DEQUEUE_04(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_COPY_01(void) {
    queue_s test = create_queue();

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_EQm("[IRQ-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST IRQ_COPY_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_EQm("[IRQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST IRQ_COPY_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST IRQ_COPY_04(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST IRQ_COPY_05(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i, });
    }

    queue_s copy = copy_queue(test, copy_int);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected elements to be equal", dequeue(&test).sub_one, dequeue(&copy).sub_one);
    }

    destroy_queue(&test, destroy_int);
    destroy_queue(&copy, destroy_int);
    PASS();
}

TEST IRQ_COPY_06(void) {
    queue_s test = create_queue();

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_EQm("[IRQ-ERROR] Expected heads to be equal", test.elements, copy.elements);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST IRQ_COPY_07(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    ASSERT_STRN_EQm("[IRQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST IRQ_COPY_08(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST IRQ_COPY_09(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST IRQ_COPY_10(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    queue_s copy = copy_queue(test, copy_string);

    ASSERT_EQm("[IRQ-ERROR] Expected sizes to be equal", test.size, copy.size);
    ASSERT_NEQm("[IRQ-ERROR] Expected heads to not be equal", test.elements, copy.elements);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected elements to be equal", peek_queue(test).sub_two, peek_queue(copy).sub_two, sizeof(TEST_STRING) - 1);
        QUEUE_DATA_TYPE test_element = dequeue(&test);
        destroy_string(&test_element);
        QUEUE_DATA_TYPE copy_element = dequeue(&copy);
        destroy_string(&copy_element);
    }

    destroy_queue(&test, destroy_string);
    destroy_queue(&copy, destroy_string);
    PASS();
}

TEST IRQ_IS_EMPTY_01(void) {
    queue_s test = create_queue();

    ASSERTm("[IRQ-ERROR] Expected queue to be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_IS_EMPTY_02(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_IS_EMPTY_03(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_IS_EMPTY_04(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    ASSERT_FALSEm("[IRQ-ERROR] Expected queue to not be empty", is_empty_queue(test));

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_CLEAR_01(void) {
    queue_s test = create_queue();

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_CLEAR_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_CLEAR_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_CLEAR_04(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_CLEAR_05(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42, });
    }

    clear_queue(&test, destroy_int);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_CLEAR_06(void) {
    queue_s test = create_queue();

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST IRQ_CLEAR_07(void) {
    queue_s test = create_queue();
    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST IRQ_CLEAR_08(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST IRQ_CLEAR_09(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST IRQ_CLEAR_10(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    clear_queue(&test, destroy_string);

    ASSERT_EQm("[IRQ-ERROR] Test queue size is not zero.", 0, test.size);
    ASSERT_EQm("[IRQ-ERROR] Test queue head is not NULL.", NULL, test.elements);

    destroy_queue(&test, destroy_string);
    PASS();
}

TEST IRQ_FOREACH_01(void) {
    queue_s test = create_queue();
    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue(&test).sub_one);

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST IRQ_FOREACH_02(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST IRQ_FOREACH_03(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST IRQ_FOREACH_04(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_queue(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);

    PASS();
}

TEST IRQ_FOREACH_05(void) {
    queue_s test = create_queue();

    enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    QUEUE_DATA_TYPE element = dequeue(&test);
    ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST IRQ_FOREACH_06(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST IRQ_FOREACH_07(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST IRQ_FOREACH_08(void) {
    queue_s test = create_queue();

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, copy_string((QUEUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_queue(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        QUEUE_DATA_TYPE element = dequeue(&test);
        ASSERT_STRN_EQm("[IRQ-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_queue(&test, destroy_string);

    PASS();
}

TEST IRQ_FOREVERY_01(void) {
    queue_s test = create_queue();

    forevery_queue(&test, sort_int, compare_int);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_FOREVERY_02(void) {
    queue_s test = create_queue();

    enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = 42 });

    forevery_queue(&test, sort_int, compare_int);

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_FOREVERY_03(void) {
    queue_s test = create_queue();

    for (int i = (REALLOC_QUEUE_CHUNK - 1) >> 1; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_int);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_FOREVERY_04(void) {
    queue_s test = create_queue();

    for (int i = (REALLOC_QUEUE_CHUNK) >> 1; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_QUEUE_CHUNK) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_int);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_FOREVERY_05(void) {
    queue_s test = create_queue();

    for (int i = (REALLOC_QUEUE_CHUNK + 1) >> 1; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_QUEUE_CHUNK + 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_int);

    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_FOREVERY_06(void) {
    queue_s test = create_queue();

    for (int i = (REALLOC_QUEUE_CHUNK - 1) >> 1; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_QUEUE_CHUNK - 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_reverse_int);

    for (int i = REALLOC_QUEUE_CHUNK - 1 - 1; i > 0; --i) {
        ASSERT_EQm("[IRQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_FOREVERY_07(void) {
    queue_s test = create_queue();

    for (int i = (REALLOC_QUEUE_CHUNK) >> 1; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_QUEUE_CHUNK) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_reverse_int);

    for (int i = REALLOC_QUEUE_CHUNK - 1; i > 0; --i) {
        ASSERT_EQm("[IRQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

TEST IRQ_FOREVERY_08(void) {
    queue_s test = create_queue();

    for (int i = (REALLOC_QUEUE_CHUNK + 1) >> 1; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_QUEUE_CHUNK + 1) >> 1; ++i) {
        enqueue(&test, (QUEUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_queue(&test, sort_int, compare_reverse_int);

    for (int i = REALLOC_QUEUE_CHUNK; i > 0; --i) {
        ASSERT_EQm("[IRQ-ERROR] Expected sorted queue to pop i", i, dequeue(&test).sub_one);
    }

    destroy_queue(&test, destroy_int);
    PASS();
}

SUITE (infinite_realloc_queue_test) {
    // create
    RUN_TEST(IRQ_CREATE_01);
    // destroy
    RUN_TEST(IRQ_DESTROY_01); RUN_TEST(IRQ_DESTROY_02); RUN_TEST(IRQ_DESTROY_03); RUN_TEST(IRQ_DESTROY_04); RUN_TEST(IRQ_DESTROY_05);
    RUN_TEST(IRQ_DESTROY_06); RUN_TEST(IRQ_DESTROY_07); RUN_TEST(IRQ_DESTROY_08); RUN_TEST(IRQ_DESTROY_09); RUN_TEST(IRQ_DESTROY_10);
    // is full
    RUN_TEST(IRQ_IS_FULL_01); RUN_TEST(IRQ_IS_FULL_02); RUN_TEST(IRQ_IS_FULL_03); RUN_TEST(IRQ_IS_FULL_04); RUN_TEST(IRQ_IS_FULL_05);
    // peep
    RUN_TEST(IRQ_PEEK_01); RUN_TEST(IRQ_PEEK_02); RUN_TEST(IRQ_PEEK_03); RUN_TEST(IRQ_PEEK_04); RUN_TEST(IRQ_PEEK_05);
    // push
    RUN_TEST(IRQ_ENQUEUE_01); RUN_TEST(IRQ_ENQUEUE_02); RUN_TEST(IRQ_ENQUEUE_03); RUN_TEST(IRQ_ENQUEUE_04);
    // pop
    RUN_TEST(IRQ_DEQUEUE_01); RUN_TEST(IRQ_DEQUEUE_02); RUN_TEST(IRQ_DEQUEUE_03); RUN_TEST(IRQ_DEQUEUE_04);
    // copy
    RUN_TEST(IRQ_COPY_01); RUN_TEST(IRQ_COPY_02); RUN_TEST(IRQ_COPY_03); RUN_TEST(IRQ_COPY_04); RUN_TEST(IRQ_COPY_05);
    RUN_TEST(IRQ_COPY_06); RUN_TEST(IRQ_COPY_07); RUN_TEST(IRQ_COPY_08); RUN_TEST(IRQ_COPY_09); RUN_TEST(IRQ_COPY_10);
    // is empty
    RUN_TEST(IRQ_IS_EMPTY_01); RUN_TEST(IRQ_IS_EMPTY_02); RUN_TEST(IRQ_IS_EMPTY_03); RUN_TEST(IRQ_IS_EMPTY_04);
    // clear
    RUN_TEST(IRQ_CLEAR_01); RUN_TEST(IRQ_CLEAR_02); RUN_TEST(IRQ_CLEAR_03); RUN_TEST(IRQ_CLEAR_04); RUN_TEST(IRQ_CLEAR_05);
    RUN_TEST(IRQ_CLEAR_06); RUN_TEST(IRQ_CLEAR_07); RUN_TEST(IRQ_CLEAR_08); RUN_TEST(IRQ_CLEAR_09); RUN_TEST(IRQ_CLEAR_10);
    // foreach
    RUN_TEST(IRQ_FOREACH_01); RUN_TEST(IRQ_FOREACH_02); RUN_TEST(IRQ_FOREACH_03); RUN_TEST(IRQ_FOREACH_04); RUN_TEST(IRQ_FOREACH_05);
    RUN_TEST(IRQ_FOREACH_06); RUN_TEST(IRQ_FOREACH_07); RUN_TEST(IRQ_FOREACH_08);
    // foevery
    RUN_TEST(IRQ_FOREVERY_01); RUN_TEST(IRQ_FOREVERY_02); RUN_TEST(IRQ_FOREVERY_03); RUN_TEST(IRQ_FOREVERY_04); RUN_TEST(IRQ_FOREVERY_05);
    RUN_TEST(IRQ_FOREVERY_06); RUN_TEST(IRQ_FOREVERY_07); RUN_TEST(IRQ_FOREVERY_08);
}
