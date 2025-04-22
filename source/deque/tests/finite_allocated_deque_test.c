#include "deque_test.h"

#include <functions.h>

#define DEQUE_DATA_TYPE DATA_TYPE
#define DEQUE_MODE FINITE_ALLOCATED_DEQUE_MODE
#include <deque/deque.h>

#define MAXIMUM_QUEUE_SIZE  (1 << 4)

TEST FAD_CREATE_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DESTROY_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);
    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST FAD_DESTROY_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST FAD_DESTROY_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST FAD_DESTROY_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST FAD_DESTROY_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST FAD_DESTROY_06(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST FAD_DESTROY_07(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST FAD_CLEAR_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_CLEAR_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_CLEAR_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_CLEAR_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_CLEAR_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_CLEAR_06(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_CLEAR_07(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FAD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_COPY_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    deque_s copy = copy_deque(test, copy_int);

    ASSERT_EQm("[FAD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FAD_COPY_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FAD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[FAD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FAD_COPY_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FAD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[FAD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FAD_COPY_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FAD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[FAD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FAD_COPY_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FAD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[FAD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FAD_COPY_06(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[FAD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[FAD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST FAD_COPY_07(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[FAD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[FAD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST FAD_IS_EMPTY_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    ASSERTm("[FAD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[FAD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FAD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FAD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_front(&test);

    ASSERTm("[FAD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_06(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[FAD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_07(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[FAD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_08(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[FAD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_09(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FAD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_10(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FAD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_11(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_back(&test);

    ASSERTm("[FAD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_12(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[FAD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_EMPTY_13(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[FAD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_FULL_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    ASSERT_FALSEm("[FAD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_IS_FULL_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[FAD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_ENQUEUE_FRONT_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FAD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_ENQUEUE_FRONT_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_ENQUEUE_FRONT_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_ENQUEUE_BACK_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FAD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_ENQUEUE_BACK_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_ENQUEUE_BACK_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_FRONT_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FAD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_FRONT_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 'MAXIMUM_QUEUE_SIZE - 2'.", MAXIMUM_QUEUE_SIZE - 2, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_FRONT_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be MAXIMUM_QUEUE_SIZE - 1.", MAXIMUM_QUEUE_SIZE - 1, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_FRONT_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_FRONT_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_BACK_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FAD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_BACK_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 'MAXIMUM_QUEUE_SIZE - 2'.", MAXIMUM_QUEUE_SIZE - 2, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_BACK_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be MAXIMUM_QUEUE_SIZE - 1.", MAXIMUM_QUEUE_SIZE - 1, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_BACK_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_PEEK_BACK_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_FRONT_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FAD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_FRONT_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", MAXIMUM_QUEUE_SIZE - 1 - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_FRONT_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", MAXIMUM_QUEUE_SIZE - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_FRONT_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_FRONT_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_BACK_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FAD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FAD-ERROR] Expected peeked element to be 0.", 0, dequeue_back(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_BACK_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", MAXIMUM_QUEUE_SIZE - 1 - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_BACK_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", MAXIMUM_QUEUE_SIZE - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_BACK_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE - 1'.", MAXIMUM_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_DEQUEUE_BACK_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FAD-ERROR] Expected size to be 'MAXIMUM_QUEUE_SIZE'.", MAXIMUM_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_FOREACH_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    ASSERT_EQm("[FAD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_FOREACH_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_FOREACH_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_FOREACH_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[FAD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FAD_FOREACH_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FAD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FAD_FOREACH_06(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FAD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FAD_FOREACH_REVERSE_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    ASSERT_EQm("[FAD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_FOREACH_REVERSE_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_FOREACH_REVERSE_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);
    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FAD_FOREACH_REVERSE_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[FAD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FAD_FOREACH_REVERSE_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FAD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FAD_FOREACH_REVERSE_06(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FAD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FAD_FOREVERY_01(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    forevery_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FAD_FOREVERY_02(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 42 });

    forevery_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FAD_FOREVERY_03(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE - 1) >> 1; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_int);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FAD_FOREVERY_04(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE) >> 1; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_int);

    for (int i = 0; i < MAXIMUM_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FAD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FAD_FOREVERY_05(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE - 1) >> 1; i < MAXIMUM_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_reverse_int);

    for (int i = MAXIMUM_QUEUE_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FAD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FAD_FOREVERY_06(void) {
    deque_s test = create_deque(MAXIMUM_QUEUE_SIZE);

    for (int i = (MAXIMUM_QUEUE_SIZE) >> 1; i < MAXIMUM_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (MAXIMUM_QUEUE_SIZE) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_reverse_int);

    for (int i = MAXIMUM_QUEUE_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FAD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

SUITE (finite_allocated_deque_test) {
    // create
    RUN_TEST(FAD_CREATE_01);
    // destroy
    RUN_TEST(FAD_DESTROY_01); RUN_TEST(FAD_DESTROY_02); RUN_TEST(FAD_DESTROY_03); RUN_TEST(FAD_DESTROY_04);
    RUN_TEST(FAD_DESTROY_05); RUN_TEST(FAD_DESTROY_06); RUN_TEST(FAD_DESTROY_07);
    // clear
    RUN_TEST(FAD_CLEAR_01); RUN_TEST(FAD_CLEAR_02); RUN_TEST(FAD_CLEAR_03); RUN_TEST(FAD_CLEAR_04);
    RUN_TEST(FAD_CLEAR_05); RUN_TEST(FAD_CLEAR_06); RUN_TEST(FAD_CLEAR_07);
    // copy
    RUN_TEST(FAD_COPY_01); RUN_TEST(FAD_COPY_02); RUN_TEST(FAD_COPY_03); RUN_TEST(FAD_COPY_04);
    RUN_TEST(FAD_COPY_05); RUN_TEST(FAD_COPY_06); RUN_TEST(FAD_COPY_07);
    // is empty
    RUN_TEST(FAD_IS_EMPTY_01); RUN_TEST(FAD_IS_EMPTY_02); RUN_TEST(FAD_IS_EMPTY_03); RUN_TEST(FAD_IS_EMPTY_04);
    RUN_TEST(FAD_IS_EMPTY_05); RUN_TEST(FAD_IS_EMPTY_06); RUN_TEST(FAD_IS_EMPTY_07); RUN_TEST(FAD_IS_EMPTY_08);
    RUN_TEST(FAD_IS_EMPTY_09); RUN_TEST(FAD_IS_EMPTY_10); RUN_TEST(FAD_IS_EMPTY_11); RUN_TEST(FAD_IS_EMPTY_12);
    RUN_TEST(FAD_IS_EMPTY_13);
    // is full
    RUN_TEST(FAD_IS_FULL_01);  RUN_TEST(FAD_IS_FULL_02);
    // enqueue front
    RUN_TEST(FAD_ENQUEUE_FRONT_01); RUN_TEST(FAD_ENQUEUE_FRONT_02); RUN_TEST(FAD_ENQUEUE_FRONT_03);
    // enqueue back
    RUN_TEST(FAD_ENQUEUE_BACK_01); RUN_TEST(FAD_ENQUEUE_BACK_02); RUN_TEST(FAD_ENQUEUE_BACK_03);
    // peek front
    RUN_TEST(FAD_PEEK_FRONT_01); RUN_TEST(FAD_PEEK_FRONT_02); RUN_TEST(FAD_PEEK_FRONT_03); RUN_TEST(FAD_PEEK_FRONT_04);
    RUN_TEST(FAD_PEEK_FRONT_05);
    // peek back
    RUN_TEST(FAD_PEEK_BACK_01); RUN_TEST(FAD_PEEK_BACK_02); RUN_TEST(FAD_PEEK_BACK_03); RUN_TEST(FAD_PEEK_BACK_04);
    RUN_TEST(FAD_PEEK_BACK_05);
    // dequeue front
    RUN_TEST(FAD_DEQUEUE_FRONT_01); RUN_TEST(FAD_DEQUEUE_FRONT_02); RUN_TEST(FAD_DEQUEUE_FRONT_03); RUN_TEST(FAD_DEQUEUE_FRONT_04);
    RUN_TEST(FAD_DEQUEUE_FRONT_05);
    // dequeue back
    RUN_TEST(FAD_DEQUEUE_BACK_01); RUN_TEST(FAD_DEQUEUE_BACK_02); RUN_TEST(FAD_DEQUEUE_BACK_03); RUN_TEST(FAD_DEQUEUE_BACK_04);
    RUN_TEST(FAD_DEQUEUE_BACK_05);
    // foreach
    RUN_TEST(FAD_FOREACH_01); RUN_TEST(FAD_FOREACH_02); RUN_TEST(FAD_FOREACH_03); RUN_TEST(FAD_FOREACH_04);
    RUN_TEST(FAD_FOREACH_05); RUN_TEST(FAD_FOREACH_06);
    // foreach reverse
    RUN_TEST(FAD_FOREACH_REVERSE_01); RUN_TEST(FAD_FOREACH_REVERSE_02); RUN_TEST(FAD_FOREACH_REVERSE_03); RUN_TEST(FAD_FOREACH_REVERSE_04);
    RUN_TEST(FAD_FOREACH_REVERSE_05); RUN_TEST(FAD_FOREACH_REVERSE_06);
    // forevery
    RUN_TEST(FAD_FOREVERY_01); RUN_TEST(FAD_FOREVERY_02); RUN_TEST(FAD_FOREVERY_03); RUN_TEST(FAD_FOREVERY_04);
    RUN_TEST(FAD_FOREVERY_05); RUN_TEST(FAD_FOREVERY_06);
}
