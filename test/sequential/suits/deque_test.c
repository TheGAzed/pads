#include <suits.h>

#include <helper/functions.h>

#define DEQUE_DATA_TYPE DATA_TYPE
#define DEQUE_SIZE (1 << 4)
#include <sequential/deque.h>

TEST CREATE_01(void) {
    deque_s test = create_deque();

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DESTROY_01(void) {
    deque_s test = create_deque();
    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_05(void) {
    deque_s test = create_deque();

    enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST DESTROY_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be 0.", 0, test.size);

    PASS();
}

TEST COPY_01(void) {
    deque_s test = create_deque();

    deque_s copy = copy_deque(&test, copy_int);

    ASSERT_EQm("[ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST COPY_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(&test, copy_int);
    ASSERT_EQm("[ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_rear(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_rear(&copy);

        ASSERT_EQm("[ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST COPY_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(&test, copy_int);
    ASSERT_EQm("[ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_rear(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_rear(&copy);

        ASSERT_EQm("[ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST COPY_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(&test, copy_int);
    ASSERT_EQm("[ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST COPY_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(&test, copy_int);
    ASSERT_EQm("[ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST COPY_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(&test, copy_string);
    ASSERT_EQm("[ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST COPY_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(&test, copy_string);
    ASSERT_EQm("[ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST IS_EMPTY_01(void) {
    deque_s test = create_deque();

    ASSERTm("[ERROR] Expected created deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[ERROR] Expected created deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ERROR] Expected created deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ERROR] Expected created deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_05(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_front(&test);

    ASSERTm("[ERROR] Expected deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[ERROR] Expected deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[ERROR] Expected deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_08(void) {
    deque_s test = create_deque();

    enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[ERROR] Expected created deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_09(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ERROR] Expected created deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_10(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ERROR] Expected created deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_11(void) {
    deque_s test = create_deque();

    enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_rear(&test);

    ASSERTm("[ERROR] Expected deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_12(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        dequeue_rear(&test);
    }

    ASSERTm("[ERROR] Expected deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_EMPTY_13(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        dequeue_rear(&test);
    }

    ASSERTm("[ERROR] Expected deque to be empty.", is_empty_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_FULL_01(void) {
    deque_s test = create_deque();

    ASSERT_FALSEm("[ERROR] Expected created deque to not be full.", is_full_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IS_FULL_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[ERROR] Expected created deque to not be full.", is_full_deque(&test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ENQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ENQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ENQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ENQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ENQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ENQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, peek_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_FRONT_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 'DEQUE_SIZE - 2'.", DEQUE_SIZE - 2, peek_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_FRONT_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be DEQUE_SIZE - 1.", DEQUE_SIZE - 1, peek_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_FRONT_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, peek_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_FRONT_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, peek_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, peek_rear(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_BACK_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 'DEQUE_SIZE - 2'.", DEQUE_SIZE - 2, peek_rear(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_BACK_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be DEQUE_SIZE - 1.", DEQUE_SIZE - 1, peek_rear(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_BACK_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, peek_rear(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST PEEK_BACK_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, peek_rear(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", DEQUE_SIZE - 1 - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", DEQUE_SIZE - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_FRONT_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_FRONT_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ERROR] Expected peeked element to be 0.", 0, dequeue_rear(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", DEQUE_SIZE - 1 - 1 - i, dequeue_rear(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", DEQUE_SIZE - 1 - i, dequeue_rear(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_BACK_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE - 1'.", DEQUE_SIZE - 1, test.size);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", i, dequeue_rear(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST DEQUEUE_BACK_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ERROR] Expected size to be 'DEQUE_SIZE'.", DEQUE_SIZE, test.size);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected peeked element to be i.", i, dequeue_rear(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FOREACH_01(void) {
    deque_s test = create_deque();
    enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_front_deque(&test, operation_int, &increment);

    ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FOREACH_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_front_deque(&test, operation_int, &increment);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FOREACH_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_front_deque(&test, operation_int, &increment);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FOREACH_04(void) {
    deque_s test = create_deque();

    enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_front_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FOREACH_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_front_deque(&test, operation_string, new_string);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FOREACH_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_front_deque(&test, operation_string, new_string);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FOREACH_REVERSE_01(void) {
    deque_s test = create_deque();
    enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_rear_deque(&test, operation_int, &increment);

    ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FOREACH_REVERSE_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_rear_deque(&test, operation_int, &increment);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FOREACH_REVERSE_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_rear_deque(&test, operation_int, &increment);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST FOREACH_REVERSE_04(void) {
    deque_s test = create_deque();

    enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_rear_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FOREACH_REVERSE_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_rear_deque(&test, operation_string, new_string);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST FOREACH_REVERSE_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_rear_deque(&test, operation_string, new_string);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST MAP_01(void) {
    deque_s test = create_deque();

    map_deque(&test, sort_int, compare_int_generic);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST MAP_02(void) {
    deque_s test = create_deque();

    enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = 42 });

    map_deque(&test, sort_int, compare_int_generic);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST MAP_03(void) {
    deque_s test = create_deque();

    for (int i = (DEQUE_SIZE - 1) >> 1; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (DEQUE_SIZE - 1) >> 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_int_generic);

    for (int i = 0; i < DEQUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST MAP_04(void) {
    deque_s test = create_deque();

    for (int i = (DEQUE_SIZE) >> 1; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (DEQUE_SIZE) >> 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_int_generic);

    for (int i = 0; i < DEQUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST MAP_05(void) {
    deque_s test = create_deque();

    for (int i = (DEQUE_SIZE - 1) >> 1; i < DEQUE_SIZE - 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (DEQUE_SIZE - 1) >> 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_reverse_int_generic);

    for (int i = DEQUE_SIZE - 2; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST MAP_06(void) {
    deque_s test = create_deque();

    for (int i = (DEQUE_SIZE) >> 1; i < DEQUE_SIZE; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (DEQUE_SIZE) >> 1; ++i) {
        enqueue_rear(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_reverse_int_generic);

    for (int i = DEQUE_SIZE - 1; i >= 0; --i) {
        ASSERT_EQm("[ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

SUITE (deque_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01); RUN_TEST(DESTROY_02); RUN_TEST(DESTROY_03); RUN_TEST(DESTROY_04);
    RUN_TEST(DESTROY_05); RUN_TEST(DESTROY_06); RUN_TEST(DESTROY_07);
    // copy
    RUN_TEST(COPY_01); RUN_TEST(COPY_02); RUN_TEST(COPY_03); RUN_TEST(COPY_04);
    RUN_TEST(COPY_05); RUN_TEST(COPY_06); RUN_TEST(COPY_07);
    // is empty
    RUN_TEST(IS_EMPTY_01); RUN_TEST(IS_EMPTY_02); RUN_TEST(IS_EMPTY_03); RUN_TEST(IS_EMPTY_04);
    RUN_TEST(IS_EMPTY_05); RUN_TEST(IS_EMPTY_06); RUN_TEST(IS_EMPTY_07); RUN_TEST(IS_EMPTY_08);
    RUN_TEST(IS_EMPTY_09); RUN_TEST(IS_EMPTY_10); RUN_TEST(IS_EMPTY_11); RUN_TEST(IS_EMPTY_12);
    RUN_TEST(IS_EMPTY_13);
    // is full
    RUN_TEST(IS_FULL_01);  RUN_TEST(IS_FULL_02);
    // enqueue front
    RUN_TEST(ENQUEUE_FRONT_01); RUN_TEST(ENQUEUE_FRONT_02); RUN_TEST(ENQUEUE_FRONT_03);
    // enqueue back
    RUN_TEST(ENQUEUE_BACK_01); RUN_TEST(ENQUEUE_BACK_02); RUN_TEST(ENQUEUE_BACK_03);
    // peek front
    RUN_TEST(PEEK_FRONT_01); RUN_TEST(PEEK_FRONT_02); RUN_TEST(PEEK_FRONT_03); RUN_TEST(PEEK_FRONT_04);
    RUN_TEST(PEEK_FRONT_05);
    // peek back
    RUN_TEST(PEEK_BACK_01); RUN_TEST(PEEK_BACK_02); RUN_TEST(PEEK_BACK_03); RUN_TEST(PEEK_BACK_04);
    RUN_TEST(PEEK_BACK_05);
    // dequeue front
    RUN_TEST(DEQUEUE_FRONT_01); RUN_TEST(DEQUEUE_FRONT_02); RUN_TEST(DEQUEUE_FRONT_03); RUN_TEST(DEQUEUE_FRONT_04);
    RUN_TEST(DEQUEUE_FRONT_05);
    // dequeue back
    RUN_TEST(DEQUEUE_BACK_01); RUN_TEST(DEQUEUE_BACK_02); RUN_TEST(DEQUEUE_BACK_03); RUN_TEST(DEQUEUE_BACK_04);
    RUN_TEST(DEQUEUE_BACK_05);
    // foreach
    RUN_TEST(FOREACH_01); RUN_TEST(FOREACH_02); RUN_TEST(FOREACH_03); RUN_TEST(FOREACH_04);
    RUN_TEST(FOREACH_05); RUN_TEST(FOREACH_06);
    // foreach reverse
    RUN_TEST(FOREACH_REVERSE_01); RUN_TEST(FOREACH_REVERSE_02); RUN_TEST(FOREACH_REVERSE_03); RUN_TEST(FOREACH_REVERSE_04);
    RUN_TEST(FOREACH_REVERSE_05); RUN_TEST(FOREACH_REVERSE_06);
    // map
    RUN_TEST(MAP_01); RUN_TEST(MAP_02); RUN_TEST(MAP_03); RUN_TEST(MAP_04);
    RUN_TEST(MAP_05); RUN_TEST(MAP_06);
}
