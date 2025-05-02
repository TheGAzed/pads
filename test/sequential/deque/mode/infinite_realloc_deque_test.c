#include "deque_test.h"

#include <functions.h>

#define DEQUE_DATA_TYPE DATA_TYPE
#define DEQUE_MODE INFINITE_REALLOC_DEQUE_MODE
#define REALLOC_DEQUE_CHUNK (1 << 4)
#include <sequential/deque/deque.h>

TEST IRD_CREATE_01(void) {
    deque_s test = create_deque();

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DESTROY_01(void) {
    deque_s test = create_deque();
    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_06(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_DESTROY_09(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    destroy_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    PASS();
}

TEST IRD_CLEAR_01(void) {
    deque_s test = create_deque();

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_06(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_CLEAR_09(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    clear_deque(&test, destroy_int);

    ASSERT_EQm("[IRD-ERROR] Expected size to be 0.", 0, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected head to be NULL.", NULL, test.elements);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_COPY_01(void) {
    deque_s test = create_deque();

    deque_s copy = copy_deque(test, copy_int);

    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);
    ASSERT_EQm("[IRD-ERROR] Expected copy head to be NULL.", NULL, copy.elements);

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST IRD_COPY_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST IRD_COPY_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST IRD_COPY_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_back(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_back(&copy);

        ASSERT_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST IRD_COPY_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST IRD_COPY_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST IRD_COPY_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    deque_s copy = copy_deque(test, copy_int);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        const DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        const DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_one, copy_element.sub_one);
    }

    destroy_deque(&test, destroy_int);
    destroy_deque(&copy, destroy_int);

    PASS();
}

TEST IRD_COPY_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST IRD_COPY_09(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST IRD_COPY_10(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING, }));
    }

    deque_s copy = copy_deque(test, copy_string);
    ASSERT_EQm("[IRD-ERROR] Expected copy size to equal test size of 0.", test.size, copy.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        DEQUE_DATA_TYPE test_element = dequeue_front(&test);
        DEQUE_DATA_TYPE copy_element = dequeue_front(&copy);

        ASSERT_STRN_EQm("[IRD-ERROR] Expected elements to be equal.", test_element.sub_two, copy_element.sub_two, sizeof(TEST_STRING) - 1);

        destroy_string(&test_element);
        destroy_string(&copy_element);
    }

    destroy_deque(&test, destroy_string);
    destroy_deque(&copy, destroy_string);

    PASS();
}

TEST IRD_IS_EMPTY_01(void) {
    deque_s test = create_deque();

    ASSERTm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_06(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_front(&test);

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_09(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        dequeue_front(&test);
    }

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_10(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_11(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_12(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_13(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    ASSERT_FALSEm("[IRD-ERROR] Expected created deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_14(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    dequeue_back(&test);

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_15(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_16(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_EMPTY_17(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });
    }

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        dequeue_back(&test);
    }

    ASSERTm("[IRD-ERROR] Expected deque to be empty.", is_empty_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_FULL_01(void) {
    deque_s test = create_deque();

    ASSERT_FALSEm("[IRD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_IS_FULL_02(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_FALSEm("[IRD_ERROR] Expected created deque to not be full.", is_full_deque(test));

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[IRD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_FRONT_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[IRD-ERROR] Expected size to be 1.", 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_ENQUEUE_BACK_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[IRD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_FRONT_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 'REALLOC_DEQUE_CHUNK - 2'.", REALLOC_DEQUE_CHUNK - 2, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_FRONT_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be REALLOC_DEQUE_CHUNK - 1.", REALLOC_DEQUE_CHUNK - 1, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_FRONT_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be REALLOC_DEQUE_CHUNK.", REALLOC_DEQUE_CHUNK, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_FRONT_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_FRONT_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_FRONT_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_front(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[IRD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_BACK_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 'REALLOC_DEQUE_CHUNK - 2'.", REALLOC_DEQUE_CHUNK - 2, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_BACK_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be REALLOC_DEQUE_CHUNK - 1.", REALLOC_DEQUE_CHUNK - 1, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_BACK_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be REALLOC_DEQUE_CHUNK.", REALLOC_DEQUE_CHUNK, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_BACK_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_BACK_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_PEEK_BACK_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, peek_back(test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_FRONT_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[IRD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_FRONT_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", REALLOC_DEQUE_CHUNK - 1 - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_FRONT_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", REALLOC_DEQUE_CHUNK - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_FRONT_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", REALLOC_DEQUE_CHUNK + 1 - 1 - i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_FRONT_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_FRONT_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_FRONT_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_BACK_01(void) {
    deque_s test = create_deque();

    enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = 0, });

    ASSERT_EQm("[IRD-ERROR] Expected size to be 1.", 1, test.size);
    ASSERT_EQm("[IRD-ERROR] Expected peeked element to be 0.", 0, dequeue_back(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_BACK_02(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", REALLOC_DEQUE_CHUNK - 1 - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_BACK_03(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", REALLOC_DEQUE_CHUNK - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_BACK_04(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", REALLOC_DEQUE_CHUNK + 1 - 1 - i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_BACK_05(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK - 1'.", REALLOC_DEQUE_CHUNK - 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_BACK_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK'.", REALLOC_DEQUE_CHUNK, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_DEQUEUE_BACK_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_front(&test, (DEQUE_DATA_TYPE) { .sub_one = i, });
    }

    ASSERT_EQm("[IRD-ERROR] Expected size to be 'REALLOC_DEQUE_CHUNK + 1'.", REALLOC_DEQUE_CHUNK + 1, test.size);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected peeked element to be i.", i, dequeue_back(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_01(void) {
    deque_s test = create_deque();
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_04(void) {
    deque_s test = create_deque();
    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_deque(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_05(void) {
    deque_s test = create_deque();

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_FOREACH_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_FOREACH_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_FOREACH_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_deque(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_FOREACH_REVERSE_01(void) {
    deque_s test = create_deque();
    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 0 });

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", 0 + increment, dequeue_front(&test).sub_one);

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_REVERSE_02(void) {
    deque_s test = create_deque();
    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_REVERSE_03(void) {
    deque_s test = create_deque();
    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_REVERSE_04(void) {
    deque_s test = create_deque();
    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    int increment = 5;
    foreach_reverse_deque(&test, operation_int, &increment);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected incremented element by 'increment'.", i + increment, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);

    PASS();
}

TEST IRD_FOREACH_REVERSE_05(void) {
    deque_s test = create_deque();

    enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    DEQUE_DATA_TYPE element = dequeue_front(&test);
    ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
    destroy_string(&element);

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_FOREACH_REVERSE_06(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_FOREACH_REVERSE_07(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_FOREACH_REVERSE_08(void) {
    deque_s test = create_deque();

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, copy_string((DEQUE_DATA_TYPE) { .sub_two = TEST_STRING }));
    }

    char new_string[] = "[REDACTED]";
    foreach_reverse_deque(&test, operation_string, new_string);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        DEQUE_DATA_TYPE element = dequeue_front(&test);
        ASSERT_STRN_EQm("[IRD-ERROR] Expected element strings to be equal.", new_string, element.sub_two, sizeof(new_string) - 1);
        destroy_string(&element);
    }

    destroy_deque(&test, destroy_string);

    PASS();
}

TEST IRD_MAP_01(void) {
    deque_s test = create_deque();

    map_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST IRD_MAP_02(void) {
    deque_s test = create_deque();

    enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = 42 });

    map_deque(&test, sort_int, compare_int);

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST IRD_MAP_03(void) {
    deque_s test = create_deque();

    for (int i = (REALLOC_DEQUE_CHUNK - 1) >> 1; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_DEQUE_CHUNK - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_int);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST IRD_MAP_04(void) {
    deque_s test = create_deque();

    for (int i = (REALLOC_DEQUE_CHUNK) >> 1; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_DEQUE_CHUNK) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_int);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST IRD_MAP_05(void) {
    deque_s test = create_deque();

    for (int i = (REALLOC_DEQUE_CHUNK + 1) >> 1; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_DEQUE_CHUNK + 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_int);

    for (int i = 0; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[IRD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST IRD_MAP_06(void) {
    deque_s test = create_deque();

    for (int i = (REALLOC_DEQUE_CHUNK - 1) >> 1; i < REALLOC_DEQUE_CHUNK - 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_DEQUE_CHUNK - 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_reverse_int);

    for (int i = REALLOC_DEQUE_CHUNK - 2; i >= 0; --i) {
        ASSERT_EQm("[IRD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST IRD_MAP_07(void) {
    deque_s test = create_deque();

    for (int i = (REALLOC_DEQUE_CHUNK) >> 1; i < REALLOC_DEQUE_CHUNK; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_DEQUE_CHUNK) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_reverse_int);

    for (int i = REALLOC_DEQUE_CHUNK - 1; i >= 0; --i) {
        ASSERT_EQm("[IRD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

TEST IRD_MAP_08(void) {
    deque_s test = create_deque();

    for (int i = (REALLOC_DEQUE_CHUNK + 1) >> 1; i < REALLOC_DEQUE_CHUNK + 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    for (int i = 0; i < (REALLOC_DEQUE_CHUNK + 1) >> 1; ++i) {
        enqueue_back(&test, (DEQUE_DATA_TYPE) { .sub_one = i });
    }

    map_deque(&test, sort_int, compare_reverse_int);

    for (int i = REALLOC_DEQUE_CHUNK; i >= 0; --i) {
        ASSERT_EQm("[IRD-ERROR] Expected sorted queue to dequeue i", i, dequeue_front(&test).sub_one);
    }

    destroy_deque(&test, destroy_int);
    PASS();
}

SUITE (infinite_realloc_deque_test) {
    // create
    RUN_TEST(IRD_CREATE_01);
    // destroy
    RUN_TEST(IRD_DESTROY_01); RUN_TEST(IRD_DESTROY_02); RUN_TEST(IRD_DESTROY_03); RUN_TEST(IRD_DESTROY_04);
    RUN_TEST(IRD_DESTROY_05); RUN_TEST(IRD_DESTROY_06); RUN_TEST(IRD_DESTROY_07); RUN_TEST(IRD_DESTROY_08);
    RUN_TEST(IRD_DESTROY_09);
    // clear
    RUN_TEST(IRD_CLEAR_01); RUN_TEST(IRD_CLEAR_02); RUN_TEST(IRD_CLEAR_03); RUN_TEST(IRD_CLEAR_04);
    RUN_TEST(IRD_CLEAR_05); RUN_TEST(IRD_CLEAR_06); RUN_TEST(IRD_CLEAR_07); RUN_TEST(IRD_CLEAR_08);
    RUN_TEST(IRD_CLEAR_09);
    // copy
    RUN_TEST(IRD_COPY_01); RUN_TEST(IRD_COPY_02); RUN_TEST(IRD_COPY_03); RUN_TEST(IRD_COPY_04);
    RUN_TEST(IRD_COPY_05); RUN_TEST(IRD_COPY_06); RUN_TEST(IRD_COPY_07); RUN_TEST(IRD_COPY_08);
    RUN_TEST(IRD_COPY_09); RUN_TEST(IRD_COPY_10);
    // is empty
    RUN_TEST(IRD_IS_EMPTY_01); RUN_TEST(IRD_IS_EMPTY_02); RUN_TEST(IRD_IS_EMPTY_03); RUN_TEST(IRD_IS_EMPTY_04);
    RUN_TEST(IRD_IS_EMPTY_05); RUN_TEST(IRD_IS_EMPTY_06); RUN_TEST(IRD_IS_EMPTY_07); RUN_TEST(IRD_IS_EMPTY_08);
    RUN_TEST(IRD_IS_EMPTY_09); RUN_TEST(IRD_IS_EMPTY_10); RUN_TEST(IRD_IS_EMPTY_11); RUN_TEST(IRD_IS_EMPTY_12);
    RUN_TEST(IRD_IS_EMPTY_13); RUN_TEST(IRD_IS_EMPTY_14); RUN_TEST(IRD_IS_EMPTY_15); RUN_TEST(IRD_IS_EMPTY_16);
    RUN_TEST(IRD_IS_EMPTY_17);
    // is full
    RUN_TEST(IRD_IS_FULL_01);  RUN_TEST(IRD_IS_FULL_02);
    // enqueue front
    RUN_TEST(IRD_ENQUEUE_FRONT_01); RUN_TEST(IRD_ENQUEUE_FRONT_02); RUN_TEST(IRD_ENQUEUE_FRONT_03); RUN_TEST(IRD_ENQUEUE_FRONT_04);
    // enqueue back
    RUN_TEST(IRD_ENQUEUE_BACK_01); RUN_TEST(IRD_ENQUEUE_BACK_02); RUN_TEST(IRD_ENQUEUE_BACK_03); RUN_TEST(IRD_ENQUEUE_BACK_04);
    // peek front
    RUN_TEST(IRD_PEEK_FRONT_01); RUN_TEST(IRD_PEEK_FRONT_02); RUN_TEST(IRD_PEEK_FRONT_03); RUN_TEST(IRD_PEEK_FRONT_04);
    RUN_TEST(IRD_PEEK_FRONT_05); RUN_TEST(IRD_PEEK_FRONT_06); RUN_TEST(IRD_PEEK_FRONT_07);
    // peek back
    RUN_TEST(IRD_PEEK_BACK_01); RUN_TEST(IRD_PEEK_BACK_02); RUN_TEST(IRD_PEEK_BACK_03); RUN_TEST(IRD_PEEK_BACK_04);
    RUN_TEST(IRD_PEEK_BACK_05); RUN_TEST(IRD_PEEK_BACK_06); RUN_TEST(IRD_PEEK_BACK_07);
    // dequeue front
    RUN_TEST(IRD_DEQUEUE_FRONT_01); RUN_TEST(IRD_DEQUEUE_FRONT_02); RUN_TEST(IRD_DEQUEUE_FRONT_03); RUN_TEST(IRD_DEQUEUE_FRONT_04);
    RUN_TEST(IRD_DEQUEUE_FRONT_05); RUN_TEST(IRD_DEQUEUE_FRONT_06); RUN_TEST(IRD_DEQUEUE_FRONT_07);
    // dequeue back
    RUN_TEST(IRD_DEQUEUE_BACK_01); RUN_TEST(IRD_DEQUEUE_BACK_02); RUN_TEST(IRD_DEQUEUE_BACK_03); RUN_TEST(IRD_DEQUEUE_BACK_04);
    RUN_TEST(IRD_DEQUEUE_BACK_05); RUN_TEST(IRD_DEQUEUE_BACK_06); RUN_TEST(IRD_DEQUEUE_BACK_07);
    // foreach
    RUN_TEST(IRD_FOREACH_01); RUN_TEST(IRD_FOREACH_02); RUN_TEST(IRD_FOREACH_03); RUN_TEST(IRD_FOREACH_04);
    RUN_TEST(IRD_FOREACH_05); RUN_TEST(IRD_FOREACH_06); RUN_TEST(IRD_FOREACH_07); RUN_TEST(IRD_FOREACH_08);
    // foreach reverse
    RUN_TEST(IRD_FOREACH_REVERSE_01); RUN_TEST(IRD_FOREACH_REVERSE_02); RUN_TEST(IRD_FOREACH_REVERSE_03); RUN_TEST(IRD_FOREACH_REVERSE_04);
    RUN_TEST(IRD_FOREACH_REVERSE_05); RUN_TEST(IRD_FOREACH_REVERSE_06); RUN_TEST(IRD_FOREACH_REVERSE_07); RUN_TEST(IRD_FOREACH_REVERSE_08);
    // map
    RUN_TEST(IRD_MAP_01); RUN_TEST(IRD_MAP_02); RUN_TEST(IRD_MAP_03); RUN_TEST(IRD_MAP_04);
    RUN_TEST(IRD_MAP_05); RUN_TEST(IRD_MAP_06); RUN_TEST(IRD_MAP_07); RUN_TEST(IRD_MAP_08);
}
