#include "deque_test.h"

#include <functions.h>

#define DEQUE_DATA_TYPE DATA_TYPE
#define DEQUE_MODE INFINITE_LIST_DEQUE_MODE
#define LIST_ARRAY_DEQUE_CHUNK (1 << 4)
#include <deque/deque.h>

TEST ILD_CREATE_01(void) {
    deque_s test = create_deque();

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DESTROY_01(void) {
    deque_s test = create_deque();
    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_06(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_08(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_DESTROY_09(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    PASS();
}

TEST ILD_CLEAR_01(void) {
    deque_s test = create_deque();

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_06(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_08(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_CLEAR_09(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[ILD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected head to be NULL.", NULL, test.head);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_COPY_01(void) {
    deque_s test = create_deque();

    deque_s copy = copy_deque(test, copy_int);

    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);
    ASSERT_EQm("[ILD-ERROR] Expected copy head to be NULL.", NULL, copy.head);

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST ILD_COPY_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST ILD_COPY_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST ILD_COPY_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST ILD_COPY_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST ILD_COPY_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST ILD_COPY_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST ILD_COPY_08(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST ILD_COPY_09(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST ILD_COPY_10(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[ILD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[ILD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST ILD_IS_EMPTY_01(void) {
    deque_s test = create_deque();

    ASSERTm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_06(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_front(&test);

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_08(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_09(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_10(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_11(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_12(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_13(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[ILD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_14(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_back(&test);

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_15(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_16(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_EMPTY_17(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[ILD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_FULL_01(void) {
    deque_s test = create_deque();

    ASSERT_FALSEm("[ILD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_IS_FULL_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[ILD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ILD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_FRONT_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ILD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_ENQUEUE_BACK_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ILD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_FRONT_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 'LIST_ARRAY_DEQUE_CHUNK - 2'.", LIST_ARRAY_DEQUE_CHUNK - 2, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_FRONT_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be LIST_ARRAY_DEQUE_CHUNK - 1.", LIST_ARRAY_DEQUE_CHUNK - 1, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_FRONT_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be LIST_ARRAY_DEQUE_CHUNK.", LIST_ARRAY_DEQUE_CHUNK, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_FRONT_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_FRONT_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_FRONT_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ILD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_BACK_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 'LIST_ARRAY_DEQUE_CHUNK - 2'.", LIST_ARRAY_DEQUE_CHUNK - 2, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_BACK_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be LIST_ARRAY_DEQUE_CHUNK - 1.", LIST_ARRAY_DEQUE_CHUNK - 1, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_BACK_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be LIST_ARRAY_DEQUE_CHUNK.", LIST_ARRAY_DEQUE_CHUNK, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_BACK_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_BACK_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_PEEK_BACK_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ILD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", LIST_ARRAY_DEQUE_CHUNK - 1 - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", LIST_ARRAY_DEQUE_CHUNK - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_FRONT_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", LIST_ARRAY_DEQUE_CHUNK + 1 - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_FRONT_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_FRONT_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_FRONT_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[ILD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[ILD-ERROR] Expected peeked element to be 0.", 0, dequeue_back(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", LIST_ARRAY_DEQUE_CHUNK - 1 - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", LIST_ARRAY_DEQUE_CHUNK - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_BACK_04(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", LIST_ARRAY_DEQUE_CHUNK + 1 - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_BACK_05(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK - 1'.", LIST_ARRAY_DEQUE_CHUNK - 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_BACK_06(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK'.", LIST_ARRAY_DEQUE_CHUNK, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_DEQUEUE_BACK_07(void) {
    deque_s test = create_deque();

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[ILD-ERROR] Expected size to be 'LIST_ARRAY_DEQUE_CHUNK + 1'.", LIST_ARRAY_DEQUE_CHUNK + 1, test.size);

    for (size_t i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_01(void) {
    deque_s test = create_deque();
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_04(void) {
    deque_s test = create_deque();
    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_05(void) {
    deque_s test = create_deque();

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREACH_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREACH_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREACH_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREACH_REVERSE_01(void) {
    deque_s test = create_deque();
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_REVERSE_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_REVERSE_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_REVERSE_04(void) {
    deque_s test = create_deque();
    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST ILD_FOREACH_REVERSE_05(void) {
    deque_s test = create_deque();

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREACH_REVERSE_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREACH_REVERSE_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREACH_REVERSE_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[ILD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST ILD_FOREVERY_01(void) {
    deque_s test = create_deque();

    forevery_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST ILD_FOREVERY_02(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 42 });

    forevery_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST ILD_FOREVERY_03(void) {
    deque_s test = create_deque();

    for (int i = (LIST_ARRAY_DEQUE_CHUNK - 1) >> 1; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_DEQUE_CHUNK - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_int);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST ILD_FOREVERY_04(void) {
    deque_s test = create_deque();

    for (int i = (LIST_ARRAY_DEQUE_CHUNK) >> 1; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_DEQUE_CHUNK) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_int);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST ILD_FOREVERY_05(void) {
    deque_s test = create_deque();

    for (int i = (LIST_ARRAY_DEQUE_CHUNK + 1) >> 1; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_DEQUE_CHUNK + 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_int);

    for (int i = 0; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ILD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST ILD_FOREVERY_06(void) {
    deque_s test = create_deque();

    for (int i = (LIST_ARRAY_DEQUE_CHUNK - 1) >> 1; i < LIST_ARRAY_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_DEQUE_CHUNK - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_reverse_int);

    for (int i = LIST_ARRAY_DEQUE_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[ILD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST ILD_FOREVERY_07(void) {
    deque_s test = create_deque();

    for (int i = (LIST_ARRAY_DEQUE_CHUNK) >> 1; i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_DEQUE_CHUNK) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_reverse_int);

    for (int i = LIST_ARRAY_DEQUE_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[ILD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST ILD_FOREVERY_08(void) {
    deque_s test = create_deque();

    for (int i = (LIST_ARRAY_DEQUE_CHUNK + 1) >> 1; i < LIST_ARRAY_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (LIST_ARRAY_DEQUE_CHUNK + 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    forevery_deque(&test, sort_int, compare_reverse_int);

    for (int i = LIST_ARRAY_DEQUE_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[ILD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

SUITE (infinite_list_deque_test) {
    // create
    RUN_TEST(ILD_CREATE_01);
    // destroy
    RUN_TEST(ILD_DESTROY_01); RUN_TEST(ILD_DESTROY_02); RUN_TEST(ILD_DESTROY_03); RUN_TEST(ILD_DESTROY_04);
    RUN_TEST(ILD_DESTROY_05); RUN_TEST(ILD_DESTROY_06); RUN_TEST(ILD_DESTROY_07); RUN_TEST(ILD_DESTROY_08);
    RUN_TEST(ILD_DESTROY_09);
    // clear
    RUN_TEST(ILD_CLEAR_01); RUN_TEST(ILD_CLEAR_02); RUN_TEST(ILD_CLEAR_03); RUN_TEST(ILD_CLEAR_04);
    RUN_TEST(ILD_CLEAR_05); RUN_TEST(ILD_CLEAR_06); RUN_TEST(ILD_CLEAR_07); RUN_TEST(ILD_CLEAR_08);
    RUN_TEST(ILD_CLEAR_09);
    // copy
    RUN_TEST(ILD_COPY_01); RUN_TEST(ILD_COPY_02); RUN_TEST(ILD_COPY_03); RUN_TEST(ILD_COPY_04);
    RUN_TEST(ILD_COPY_05); RUN_TEST(ILD_COPY_06); RUN_TEST(ILD_COPY_07); RUN_TEST(ILD_COPY_08);
    RUN_TEST(ILD_COPY_09); RUN_TEST(ILD_COPY_10);
    // is empty
    RUN_TEST(ILD_IS_EMPTY_01); RUN_TEST(ILD_IS_EMPTY_02); RUN_TEST(ILD_IS_EMPTY_03); RUN_TEST(ILD_IS_EMPTY_04);
    RUN_TEST(ILD_IS_EMPTY_05); RUN_TEST(ILD_IS_EMPTY_06); RUN_TEST(ILD_IS_EMPTY_07); RUN_TEST(ILD_IS_EMPTY_08);
    RUN_TEST(ILD_IS_EMPTY_09); RUN_TEST(ILD_IS_EMPTY_10); RUN_TEST(ILD_IS_EMPTY_11); RUN_TEST(ILD_IS_EMPTY_12);
    RUN_TEST(ILD_IS_EMPTY_13); RUN_TEST(ILD_IS_EMPTY_14); RUN_TEST(ILD_IS_EMPTY_15); RUN_TEST(ILD_IS_EMPTY_16);
    RUN_TEST(ILD_IS_EMPTY_17);
    // is full
    RUN_TEST(ILD_IS_FULL_01);  RUN_TEST(ILD_IS_FULL_02);
    // enqueue front
    RUN_TEST(ILD_ENQUEUE_FRONT_01); RUN_TEST(ILD_ENQUEUE_FRONT_02); RUN_TEST(ILD_ENQUEUE_FRONT_03); RUN_TEST(ILD_ENQUEUE_FRONT_04);
    // enqueue back
    RUN_TEST(ILD_ENQUEUE_BACK_01); RUN_TEST(ILD_ENQUEUE_BACK_02); RUN_TEST(ILD_ENQUEUE_BACK_03); RUN_TEST(ILD_ENQUEUE_BACK_04);
    // peek front
    RUN_TEST(ILD_PEEK_FRONT_01); RUN_TEST(ILD_PEEK_FRONT_02); RUN_TEST(ILD_PEEK_FRONT_03); RUN_TEST(ILD_PEEK_FRONT_04);
    RUN_TEST(ILD_PEEK_FRONT_05); RUN_TEST(ILD_PEEK_FRONT_06); RUN_TEST(ILD_PEEK_FRONT_07);
    // peek back
    RUN_TEST(ILD_PEEK_BACK_01); RUN_TEST(ILD_PEEK_BACK_02); RUN_TEST(ILD_PEEK_BACK_03); RUN_TEST(ILD_PEEK_BACK_04);
    RUN_TEST(ILD_PEEK_BACK_05); RUN_TEST(ILD_PEEK_BACK_06); RUN_TEST(ILD_PEEK_BACK_07);
    // dequeue front
    RUN_TEST(ILD_DEQUEUE_FRONT_01); RUN_TEST(ILD_DEQUEUE_FRONT_02); RUN_TEST(ILD_DEQUEUE_FRONT_03); RUN_TEST(ILD_DEQUEUE_FRONT_04);
    RUN_TEST(ILD_DEQUEUE_FRONT_05); RUN_TEST(ILD_DEQUEUE_FRONT_06); RUN_TEST(ILD_DEQUEUE_FRONT_07);
    // dequeue back
    RUN_TEST(ILD_DEQUEUE_BACK_01); RUN_TEST(ILD_DEQUEUE_BACK_02); RUN_TEST(ILD_DEQUEUE_BACK_03); RUN_TEST(ILD_DEQUEUE_BACK_04);
    RUN_TEST(ILD_DEQUEUE_BACK_05); RUN_TEST(ILD_DEQUEUE_BACK_06); RUN_TEST(ILD_DEQUEUE_BACK_07);
    // foreach
    RUN_TEST(ILD_FOREACH_01); RUN_TEST(ILD_FOREACH_02); RUN_TEST(ILD_FOREACH_03); RUN_TEST(ILD_FOREACH_04);
    RUN_TEST(ILD_FOREACH_05); RUN_TEST(ILD_FOREACH_06); RUN_TEST(ILD_FOREACH_07); RUN_TEST(ILD_FOREACH_08);
    // foreach reverse
    RUN_TEST(ILD_FOREACH_REVERSE_01); RUN_TEST(ILD_FOREACH_REVERSE_02); RUN_TEST(ILD_FOREACH_REVERSE_03); RUN_TEST(ILD_FOREACH_REVERSE_04);
    RUN_TEST(ILD_FOREACH_REVERSE_05); RUN_TEST(ILD_FOREACH_REVERSE_06); RUN_TEST(ILD_FOREACH_REVERSE_07); RUN_TEST(ILD_FOREACH_REVERSE_08);
    // forevery
    RUN_TEST(ILD_FOREVERY_01); RUN_TEST(ILD_FOREVERY_02); RUN_TEST(ILD_FOREVERY_03); RUN_TEST(ILD_FOREVERY_04);
    RUN_TEST(ILD_FOREVERY_05); RUN_TEST(ILD_FOREVERY_06); RUN_TEST(ILD_FOREVERY_07); RUN_TEST(ILD_FOREVERY_08);
}
