#include "deque_test.h"

#include <functions.h>

#define DEQUE_DATA_TYPE DATA_TYPE
#define DEQUE_MODE FINITE_PREPROCESSOR_DEQUE_MODE
#define PREPROCESSOR_QUEUE_SIZE (1 << 4)
#include <sequential/deque/deque.h>

TEST FPD_CREATE_01(void) {
    deque_s test = create_deque();

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DESTROY_01(void) {
    deque_s test = create_deque();
    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPD_DESTROY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPD_DESTROY_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPD_DESTROY_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPD_DESTROY_05(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPD_DESTROY_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPD_DESTROY_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST FPD_CLEAR_01(void) {
    deque_s test = create_deque();

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_CLEAR_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_CLEAR_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_CLEAR_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_CLEAR_05(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_CLEAR_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_CLEAR_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[FPD-ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_COPY_01(void) {
    deque_s test = create_deque();

    deque_s copy = copy_deque(test, copy_int);

    ASSERT_EQm("[FPD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FPD_COPY_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FPD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[FPD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FPD_COPY_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FPD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[FPD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FPD_COPY_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FPD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[FPD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FPD_COPY_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[FPD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[FPD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST FPD_COPY_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[FPD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[FPD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST FPD_COPY_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[FPD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[FPD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST FPD_IS_EMPTY_01(void) {
    deque_s test = create_deque();

    ASSERTm("[FPD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[FPD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FPD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FPD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_05(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_front(&test);

    ASSERTm("[FPD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[FPD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[FPD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_08(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[FPD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_09(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FPD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_10(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[FPD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_11(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_back(&test);

    ASSERTm("[FPD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_12(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[FPD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_EMPTY_13(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[FPD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_FULL_01(void) {
    deque_s test = create_deque();

    ASSERT_FALSEm("[FPD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_IS_FULL_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[FPD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_ENQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FPD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_ENQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_ENQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_ENQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FPD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_ENQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_ENQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FPD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_FRONT_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 'PREPROCESSOR_QUEUE_SIZE - 2'.", PREPROCESSOR_QUEUE_SIZE - 2, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_FRONT_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be PREPROCESSOR_QUEUE_SIZE - 1.", PREPROCESSOR_QUEUE_SIZE - 1, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_FRONT_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_FRONT_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FPD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_BACK_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 'PREPROCESSOR_QUEUE_SIZE - 2'.", PREPROCESSOR_QUEUE_SIZE - 2, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_BACK_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be PREPROCESSOR_QUEUE_SIZE - 1.", PREPROCESSOR_QUEUE_SIZE - 1, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_BACK_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_PEEK_BACK_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FPD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", PREPROCESSOR_QUEUE_SIZE - 1 - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", PREPROCESSOR_QUEUE_SIZE - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_FRONT_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_FRONT_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[FPD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[FPD-ERROR] Expected peeked element to be 0.", 0, dequeue_back(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", PREPROCESSOR_QUEUE_SIZE - 1 - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", PREPROCESSOR_QUEUE_SIZE - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_BACK_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE - 1'.", PREPROCESSOR_QUEUE_SIZE - 1, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_DEQUEUE_BACK_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[FPD-ERROR] Expected size to be 'PREPROCESSOR_QUEUE_SIZE'.", PREPROCESSOR_QUEUE_SIZE, test.size);

    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_FOREACH_01(void) {
    deque_s test = create_deque();
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    ASSERT_EQm("[FPD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_FOREACH_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_FOREACH_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_FOREACH_04(void) {
    deque_s test = create_deque();

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[FPD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FPD_FOREACH_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FPD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FPD_FOREACH_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FPD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FPD_FOREACH_REVERSE_01(void) {
    deque_s test = create_deque();
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    ASSERT_EQm("[FPD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_FOREACH_REVERSE_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_FOREACH_REVERSE_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FPD_FOREACH_REVERSE_04(void) {
    deque_s test = create_deque();

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[FPD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FPD_FOREACH_REVERSE_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FPD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FPD_FOREACH_REVERSE_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[FPD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FPD_MAP_01(void) {
    deque_s test = create_deque();

    map_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FPD_MAP_02(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 42 });

    map_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FPD_MAP_03(void) {
    deque_s test = create_deque();

    for (int i = (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_int);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FPD_MAP_04(void) {
    deque_s test = create_deque();

    for (int i = (PREPROCESSOR_QUEUE_SIZE) >> 1; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_int);

    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[FPD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FPD_MAP_05(void) {
    deque_s test = create_deque();

    for (int i = (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_reverse_int);

    for (int i = PREPROCESSOR_QUEUE_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[FPD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST FPD_MAP_06(void) {
    deque_s test = create_deque();

    for (int i = (PREPROCESSOR_QUEUE_SIZE) >> 1; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (PREPROCESSOR_QUEUE_SIZE) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_reverse_int);

    for (int i = PREPROCESSOR_QUEUE_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[FPD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

SUITE (finite_preprocessor_deque_test) {
    // create
    RUN_TEST(FPD_CREATE_01);
    // destroy
    RUN_TEST(FPD_DESTROY_01); RUN_TEST(FPD_DESTROY_02); RUN_TEST(FPD_DESTROY_03); RUN_TEST(FPD_DESTROY_04);
    RUN_TEST(FPD_DESTROY_05); RUN_TEST(FPD_DESTROY_06); RUN_TEST(FPD_DESTROY_07);
    // clear
    RUN_TEST(FPD_CLEAR_01); RUN_TEST(FPD_CLEAR_02); RUN_TEST(FPD_CLEAR_03); RUN_TEST(FPD_CLEAR_04);
    RUN_TEST(FPD_CLEAR_05); RUN_TEST(FPD_CLEAR_06); RUN_TEST(FPD_CLEAR_07);
    // copy
    RUN_TEST(FPD_COPY_01); RUN_TEST(FPD_COPY_02); RUN_TEST(FPD_COPY_03); RUN_TEST(FPD_COPY_04);
    RUN_TEST(FPD_COPY_05); RUN_TEST(FPD_COPY_06); RUN_TEST(FPD_COPY_07);
    // is empty
    RUN_TEST(FPD_IS_EMPTY_01); RUN_TEST(FPD_IS_EMPTY_02); RUN_TEST(FPD_IS_EMPTY_03); RUN_TEST(FPD_IS_EMPTY_04);
    RUN_TEST(FPD_IS_EMPTY_05); RUN_TEST(FPD_IS_EMPTY_06); RUN_TEST(FPD_IS_EMPTY_07); RUN_TEST(FPD_IS_EMPTY_08);
    RUN_TEST(FPD_IS_EMPTY_09); RUN_TEST(FPD_IS_EMPTY_10); RUN_TEST(FPD_IS_EMPTY_11); RUN_TEST(FPD_IS_EMPTY_12);
    RUN_TEST(FPD_IS_EMPTY_13);
    // is full
    RUN_TEST(FPD_IS_FULL_01);  RUN_TEST(FPD_IS_FULL_02);
    // enqueue front
    RUN_TEST(FPD_ENQUEUE_FRONT_01); RUN_TEST(FPD_ENQUEUE_FRONT_02); RUN_TEST(FPD_ENQUEUE_FRONT_03);
    // enqueue back
    RUN_TEST(FPD_ENQUEUE_BACK_01); RUN_TEST(FPD_ENQUEUE_BACK_02); RUN_TEST(FPD_ENQUEUE_BACK_03);
    // peek front
    RUN_TEST(FPD_PEEK_FRONT_01); RUN_TEST(FPD_PEEK_FRONT_02); RUN_TEST(FPD_PEEK_FRONT_03); RUN_TEST(FPD_PEEK_FRONT_04);
    RUN_TEST(FPD_PEEK_FRONT_05);
    // peek back
    RUN_TEST(FPD_PEEK_BACK_01); RUN_TEST(FPD_PEEK_BACK_02); RUN_TEST(FPD_PEEK_BACK_03); RUN_TEST(FPD_PEEK_BACK_04);
    RUN_TEST(FPD_PEEK_BACK_05);
    // dequeue front
    RUN_TEST(FPD_DEQUEUE_FRONT_01); RUN_TEST(FPD_DEQUEUE_FRONT_02); RUN_TEST(FPD_DEQUEUE_FRONT_03); RUN_TEST(FPD_DEQUEUE_FRONT_04);
    RUN_TEST(FPD_DEQUEUE_FRONT_05);
    // dequeue back
    RUN_TEST(FPD_DEQUEUE_BACK_01); RUN_TEST(FPD_DEQUEUE_BACK_02); RUN_TEST(FPD_DEQUEUE_BACK_03); RUN_TEST(FPD_DEQUEUE_BACK_04);
    RUN_TEST(FPD_DEQUEUE_BACK_05);
    // foreach
    RUN_TEST(FPD_FOREACH_01); RUN_TEST(FPD_FOREACH_02); RUN_TEST(FPD_FOREACH_03); RUN_TEST(FPD_FOREACH_04);
    RUN_TEST(FPD_FOREACH_05); RUN_TEST(FPD_FOREACH_06);
    // foreach reverse
    RUN_TEST(FPD_FOREACH_REVERSE_01); RUN_TEST(FPD_FOREACH_REVERSE_02); RUN_TEST(FPD_FOREACH_REVERSE_03); RUN_TEST(FPD_FOREACH_REVERSE_04);
    RUN_TEST(FPD_FOREACH_REVERSE_05); RUN_TEST(FPD_FOREACH_REVERSE_06);
    // map
    RUN_TEST(FPD_MAP_01); RUN_TEST(FPD_MAP_02); RUN_TEST(FPD_MAP_03); RUN_TEST(FPD_MAP_04);
    RUN_TEST(FPD_MAP_05); RUN_TEST(FPD_MAP_06);
}
