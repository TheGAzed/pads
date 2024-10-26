#include <greatest.h>

#ifndef TEST_QUEUE_MODE

#error No queue mode was defined before testing ('TEST_QUEUE_MODE' is not defined).

#else

#define QUEUE_MODE TEST_QUEUE_MODE

#endif

#define STRING_VALUE "thegazed"
typedef union copy_type {
    int    integer;
    char * char_ptr;
} copy_u;

//#define QUEUE_MODE FINITE_ALLOCATED_QUEUE
#define LIST_ARRAY_QUEUE_CHUNK  10
#define REALLOC_QUEUE_CHUNK     10
#define PREPROCESSOR_QUEUE_SIZE 10
#define QUEUE_DATA_TYPE copy_u
#include "queue.h"

QUEUE_DATA_TYPE create_string_c(void) {
    QUEUE_DATA_TYPE string = { 0 };
    string.char_ptr = malloc((sizeof(STRING_VALUE)));
    assert(string.char_ptr && "[ERROR] Memory allocation failed.");
    strncpy(string.char_ptr, STRING_VALUE, sizeof(STRING_VALUE) - sizeof(STRING_VALUE[0]));
    return string;
}

void destroy_string_c(QUEUE_DATA_TYPE * string) {
    free(string->char_ptr);
    string->char_ptr = NULL;
}

QUEUE_DATA_TYPE copy_string_c(const QUEUE_DATA_TYPE source) {
    QUEUE_DATA_TYPE copy = { 0 };
    copy.char_ptr = malloc(strnlen(source.char_ptr, sizeof(STRING_VALUE) - 1));
    assert(copy.char_ptr && "[ERROR] Memory allocation failed.");
    strncpy(copy.char_ptr, STRING_VALUE, sizeof(STRING_VALUE) - 1);
    return copy;
}

#if   QUEUE_MODE == INFINITE_LIST_QUEUE

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_010_01(void) {
    queue_s test = create_queue();
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer of NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected equal head pointer of NULL.", test.head, copy.head);

    ASSERT_EQm("[ERROR] Expected copy tail pointer of NULL.", NULL, copy.tail);
    ASSERT_EQm("[ERROR] Expected equal tail pointer of NULL.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_010_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_010_03(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 2 value has same data as test queue.
TEST test_010_04(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 2.", LIST_ARRAY_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_010_05(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 1.", LIST_ARRAY_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK value has same data as test queue.
TEST test_010_06(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK.", LIST_ARRAY_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK + 1 value has same data as test queue.
TEST test_010_07(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK + 1.", LIST_ARRAY_QUEUE_CHUNK + 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK + 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_08(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_09(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_10(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_11(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_12(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_13(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_010_14(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_010_15(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = -1 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_010_16(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_010_17(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK has same start value as test queue.
TEST test_010_18(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK + 1 has same start value as test queue.
TEST test_010_19(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same values as test queue.
TEST test_010_20(void) {
    queue_s test = create_queue();
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same values as test queue.
TEST test_010_21(void) {
    queue_s test = create_queue();
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK has same values as test queue.
TEST test_010_22(void) {
    queue_s test = create_queue();
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK + 1 has same values as test queue.
TEST test_010_23(void) {
    queue_s test = create_queue();
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_010_24(void) {
    queue_s test = create_queue();
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer of NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected equal head pointer of NULL.", test.head, copy.head);

    ASSERT_EQm("[ERROR] Expected copy tail pointer of NULL.", NULL, copy.tail);
    ASSERT_EQm("[ERROR] Expected equal tail pointer of NULL.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_010_25(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_010_26(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 2 value has same data as test queue.
TEST test_010_27(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 2.", LIST_ARRAY_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_010_28(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 1.", LIST_ARRAY_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK value has same data as test queue.
TEST test_010_29(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK.", LIST_ARRAY_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK + 1 value has same data as test queue.
TEST test_010_30(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK + 1.", LIST_ARRAY_QUEUE_CHUNK + 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK + 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.head);
    ASSERT_NEQm("[ERROR] Expected copy tail pointer to not be NULL.", NULL, copy.tail);

    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.head, copy.head);
    ASSERT_NEQm("[ERROR] Expected tail pointers to be different.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_31(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_32(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_33(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_34(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_35(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_010_36(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.head);
    ASSERT_EQm("[ERROR] Expected copy tail pointer to be NULL.", NULL, copy.tail);

    ASSERT_EQm("[ERROR] Expected head pointers to be equal NULL.", test.head, copy.head);
    ASSERT_EQm("[ERROR] Expected tail pointers to be equal NULL.", test.tail, copy.tail);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_010_37(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_010_38(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_010_39(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_010_40(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK has same start value as test queue.
TEST test_010_41(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK + 1 has same start value as test queue.
TEST test_010_42(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

SUITE (copy_queue_test) {
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
    RUN_TEST(test_010_16);
    RUN_TEST(test_010_17);
    RUN_TEST(test_010_18);
    RUN_TEST(test_010_19);
    RUN_TEST(test_010_20);
    RUN_TEST(test_010_21);
    RUN_TEST(test_010_22);
    RUN_TEST(test_010_23);
    RUN_TEST(test_010_24);
    RUN_TEST(test_010_25);
    RUN_TEST(test_010_26);
    RUN_TEST(test_010_27);
    RUN_TEST(test_010_28);
    RUN_TEST(test_010_29);
    RUN_TEST(test_010_30);
    RUN_TEST(test_010_31);
    RUN_TEST(test_010_32);
    RUN_TEST(test_010_33);
    RUN_TEST(test_010_34);
    RUN_TEST(test_010_35);
    RUN_TEST(test_010_36);
    RUN_TEST(test_010_37);
    RUN_TEST(test_010_38);
    RUN_TEST(test_010_39);
    RUN_TEST(test_010_40);
    RUN_TEST(test_010_41);
    RUN_TEST(test_010_42);
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_020_01(void) {
    queue_s test = create_queue(10);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_020_02(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_020_03(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with 8 value has same data as test queue.
TEST test_020_04(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 2.", LIST_ARRAY_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_020_05(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 1.", LIST_ARRAY_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK value has same data as test queue.
TEST test_020_06(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK.", LIST_ARRAY_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_07(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 1.", 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 1.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_08(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 2.", 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 2.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_09(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < test.max - 2; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at test.max - 2.", test.max - 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at test.max - 2.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_10(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < test.max - 1; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at test.max - 1.", test.max - 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at test.max - 1.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_11(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < test.max; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_020_12(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_020_13(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = -1 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_020_14(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_020_15(void) {
    queue_s test = create_queue(10);
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same values as test queue.
TEST test_020_16(void) {
    queue_s test = create_queue(10);
    for (int i = 0; i < test.max - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < copy.max - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same values as test queue.
TEST test_020_17(void) {
    queue_s test = create_queue(10);
    for (int i = 0; i < test.max - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < copy.max - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK has same values as test queue.
TEST test_020_18(void) {
    queue_s test = create_queue(10);
    for (int i = 0; i < test.max; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < copy.max; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue circled values are equal.
TEST test_020_19(void) {
    queue_s test = create_queue(10);
    for (int i = 0; i < test.max; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    for (int i = 0; i < test.max / 2; ++i) {
        dequeue(&test);
    }
    for (int i = 0; i < test.max / 2; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < copy.size; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_020_20(void) {
    queue_s test = create_queue(10);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_020_21(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_020_22(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 2 value has same data as test queue.
TEST test_020_23(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 2.", LIST_ARRAY_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_020_24(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 1.", LIST_ARRAY_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK value has same data as test queue.
TEST test_020_25(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK.", LIST_ARRAY_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_26(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 1.", 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 1.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_27(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 2.", 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 2.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_28(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < test.max - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at test.max - 2.", test.max - 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at test.max - 2.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_29(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < test.max - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at test.max - 1.", test.max - 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at test.max - 1.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_020_30(void) {
    queue_s test = create_queue(10);
    for (size_t i = 0; i < test.max; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < test.max; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy elements pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected elements pointer to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_020_31(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_020_32(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_020_33(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < test.max - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_020_34(void) {
    queue_s test = create_queue(10);
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < test.max - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

SUITE (copy_queue_test) {
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
    RUN_TEST(test_020_11);
    RUN_TEST(test_020_12);
    RUN_TEST(test_020_13);
    RUN_TEST(test_020_14);
    RUN_TEST(test_020_15);
    RUN_TEST(test_020_16);
    RUN_TEST(test_020_17);
    RUN_TEST(test_020_18);
    RUN_TEST(test_020_19);
    RUN_TEST(test_020_20);
    RUN_TEST(test_020_21);
    RUN_TEST(test_020_22);
    RUN_TEST(test_020_23);
    RUN_TEST(test_020_24);
    RUN_TEST(test_020_25);
    RUN_TEST(test_020_26);
    RUN_TEST(test_020_27);
    RUN_TEST(test_020_28);
    RUN_TEST(test_020_29);
    RUN_TEST(test_020_30);
    RUN_TEST(test_020_31);
    RUN_TEST(test_020_32);
    RUN_TEST(test_020_33);
    RUN_TEST(test_020_34);
}

#elif QUEUE_MODE == INFINITE_REALLOC_QUEUE

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_030_01(void) {
    queue_s test = create_queue();
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer of NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected equal head pointer of NULL.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_030_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_030_03(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK - 2 value has same data as test queue.
TEST test_030_04(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK - 2.", REALLOC_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_030_05(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK - 1.", REALLOC_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK value has same data as test queue.
TEST test_030_06(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK.", REALLOC_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK + 1 value has same data as test queue.
TEST test_030_07(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK + 1.", REALLOC_QUEUE_CHUNK + 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK + 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_08(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_09(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_10(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_11(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_12(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_13(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_030_14(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_030_15(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = -1 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_030_16(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_030_17(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK has same start value as test queue.
TEST test_030_18(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK + 1 has same start value as test queue.
TEST test_030_19(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK - 2 has same values as test queue.
TEST test_030_20(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK - 1 has same values as test queue.
TEST test_030_21(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK has same values as test queue.
TEST test_030_22(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK + 1 has same values as test queue.
TEST test_030_23(void) {
    queue_s test = create_queue();
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_030_24(void) {
    queue_s test = create_queue();
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_030_25(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_030_26(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK - 2 value has same data as test queue.
TEST test_030_27(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK - 2.", REALLOC_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_030_28(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK - 1.", REALLOC_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK value has same data as test queue.
TEST test_030_29(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK.", REALLOC_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with REALLOC_QUEUE_CHUNK + 1 value has same data as test queue.
TEST test_030_30(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of REALLOC_QUEUE_CHUNK + 1.", REALLOC_QUEUE_CHUNK + 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of REALLOC_QUEUE_CHUNK + 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_NEQm("[ERROR] Expected copy head pointer to not be NULL.", NULL, copy.elements);
    ASSERT_NEQm("[ERROR] Expected head pointers to be different.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_31(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_32(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_33(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_34(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_35(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_030_36(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    ASSERT_EQm("[ERROR] Expected copy head pointer to be NULL.", NULL, copy.elements);
    ASSERT_EQm("[ERROR] Expected head pointers to be equal.", test.elements, copy.elements);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_030_37(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_030_38(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_030_39(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_030_40(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK has same start value as test queue.
TEST test_030_41(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size REALLOC_QUEUE_CHUNK + 1 has same start value as test queue.
TEST test_030_42(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < REALLOC_QUEUE_CHUNK + 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

SUITE (copy_queue_test) {
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
    RUN_TEST(test_030_16);
    RUN_TEST(test_030_17);
    RUN_TEST(test_030_18);
    RUN_TEST(test_030_19);
    RUN_TEST(test_030_20);
    RUN_TEST(test_030_21);
    RUN_TEST(test_030_22);
    RUN_TEST(test_030_23);
    RUN_TEST(test_030_24);
    RUN_TEST(test_030_25);
    RUN_TEST(test_030_26);
    RUN_TEST(test_030_27);
    RUN_TEST(test_030_28);
    RUN_TEST(test_030_29);
    RUN_TEST(test_030_30);
    RUN_TEST(test_030_31);
    RUN_TEST(test_030_32);
    RUN_TEST(test_030_33);
    RUN_TEST(test_030_34);
    RUN_TEST(test_030_35);
    RUN_TEST(test_030_36);
    RUN_TEST(test_030_37);
    RUN_TEST(test_030_38);
    RUN_TEST(test_030_39);
    RUN_TEST(test_030_40);
    RUN_TEST(test_030_41);
    RUN_TEST(test_030_42);
}

#elif QUEUE_MODE == FINITE_PRERPOCESSOR_QUEUE

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_040_01(void) {
    queue_s test = create_queue();
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_040_02(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_040_03(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with 8 value has same data as test queue.
TEST test_040_04(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 2.", LIST_ARRAY_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_040_05(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 1.", LIST_ARRAY_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK value has same data as test queue.
TEST test_040_06(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK.", LIST_ARRAY_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_07(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 1.", 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 1.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_08(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = 42 } );
    dequeue(&test);
    dequeue(&test);
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 2.", 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 2.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_09(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at PREPROCESSOR_QUEUE_SIZE - 2.", PREPROCESSOR_QUEUE_SIZE - 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at PREPROCESSOR_QUEUE_SIZE - 2.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_10(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at PREPROCESSOR_QUEUE_SIZE - 1.", PREPROCESSOR_QUEUE_SIZE - 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at PREPROCESSOR_QUEUE_SIZE - 1.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_11(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (copy_u) { .integer = 42 } );
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        dequeue(&test);
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_040_12(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_040_13(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    enqueue(&test, (copy_u) { .integer = -1 } );
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_040_14(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_040_15(void) {
    queue_s test = create_queue();
    enqueue(&test, (copy_u) { .integer = 42 } );
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = -1 } );
    }
    queue_s copy = copy_queue(test, NULL);

    ASSERT_EQm("[ERROR] Expected equal peeked value of 42.", peek_queue(test).integer, peek_queue(copy).integer);

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same values as test queue.
TEST test_040_16(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same values as test queue.
TEST test_040_17(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK has same values as test queue.
TEST test_040_18(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied queue circled values are equal.
TEST test_040_19(void) {
    queue_s test = create_queue();
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE / 2; ++i) {
        dequeue(&test);
    }
    for (int i = 0; i < PREPROCESSOR_QUEUE_SIZE / 2; ++i) {
        enqueue(&test, (copy_u) { .integer = i } );
    }
    queue_s copy = copy_queue(test, NULL);
    for (int i = 0; i < copy.size; ++i) {
        ASSERT_EQm("[ERROR] Expected equal peeked value of i.", dequeue(&test).integer, dequeue(&copy).integer);
    }

    destroy_queue(&test, NULL);
    destroy_queue(&copy, NULL);

    PASS();
}

/// @brief Tests copyied empty queue has same data as test queue.
TEST test_040_20(void) {
    queue_s test = create_queue();
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with one value has same data as test queue.
TEST test_040_21(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 1.", 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with two value has same data as test queue.
TEST test_040_22(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 2.", 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 2 value has same data as test queue.
TEST test_040_23(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 2.", LIST_ARRAY_QUEUE_CHUNK - 2, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 2.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK - 1 value has same data as test queue.
TEST test_040_24(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK - 1.", LIST_ARRAY_QUEUE_CHUNK - 1, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK - 1.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue with LIST_ARRAY_QUEUE_CHUNK value has same data as test queue.
TEST test_040_25(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of LIST_ARRAY_QUEUE_CHUNK.", LIST_ARRAY_QUEUE_CHUNK, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of LIST_ARRAY_QUEUE_CHUNK.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy current index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_26(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 1.", 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 1.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_27(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    QUEUE_DATA_TYPE string = dequeue(&test);
    destroy_string_c(&string);
    string = dequeue(&test);
    destroy_string_c(&string);
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 2.", 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 2.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_28(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at PREPROCESSOR_QUEUE_SIZE - 2.", PREPROCESSOR_QUEUE_SIZE - 2, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at PREPROCESSOR_QUEUE_SIZE - 2.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_29(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at PREPROCESSOR_QUEUE_SIZE - 1.", PREPROCESSOR_QUEUE_SIZE - 1, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at PREPROCESSOR_QUEUE_SIZE - 1.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue has same data as test queue.
TEST test_040_30(void) {
    queue_s test = create_queue();
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        enqueue(&test, create_string_c());
    }
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE; ++i) {
        QUEUE_DATA_TYPE string = dequeue(&test);
        destroy_string_c(&string);
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERT_EQm("[ERROR] Expected copy size of 0.", 0, copy.size);
    ASSERT_EQm("[ERROR] Expected equal size of 0.", test.size, copy.size);

    ASSERT_EQm("[ERROR] Expected copy index at 0.", 0, copy.current);
    ASSERT_EQm("[ERROR] Expected equal current index at 0.", test.current, copy.current);

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue if size one has same start value as test queue.
TEST test_040_31(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size two has same start value as test queue.
TEST test_040_32(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    enqueue(&test, create_string_c());
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 2 has same start value as test queue.
TEST test_040_33(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 2; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

/// @brief Tests copyied queue of size LIST_ARRAY_QUEUE_CHUNK - 1 has same start value as test queue.
TEST test_040_34(void) {
    queue_s test = create_queue();
    enqueue(&test, create_string_c());
    for (size_t i = 0; i < PREPROCESSOR_QUEUE_SIZE - 1; ++i) {
        enqueue(&test, create_string_c());
    }
    queue_s copy = copy_queue(test, copy_string_c);

    ASSERTm(
        "[ERROR] Expected equal peeked value of 'thegazed'.",
        strncmp(peek_queue(test).char_ptr, peek_queue(copy).char_ptr, sizeof(STRING_VALUE) - 1) == 0
    );

    destroy_queue(&test, destroy_string_c);
    destroy_queue(&copy, destroy_string_c);

    PASS();
}

SUITE (copy_queue_test) {
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
    RUN_TEST(test_040_11);
    RUN_TEST(test_040_12);
    RUN_TEST(test_040_13);
    RUN_TEST(test_040_14);
    RUN_TEST(test_040_15);
    RUN_TEST(test_040_16);
    RUN_TEST(test_040_17);
    RUN_TEST(test_040_18);
    RUN_TEST(test_040_19);
    RUN_TEST(test_040_20);
    RUN_TEST(test_040_21);
    RUN_TEST(test_040_22);
    RUN_TEST(test_040_23);
    RUN_TEST(test_040_24);
    RUN_TEST(test_040_25);
    RUN_TEST(test_040_26);
    RUN_TEST(test_040_27);
    RUN_TEST(test_040_28);
    RUN_TEST(test_040_29);
    RUN_TEST(test_040_30);
    RUN_TEST(test_040_31);
    RUN_TEST(test_040_32);
    RUN_TEST(test_040_33);
    RUN_TEST(test_040_34);
}

#endif
