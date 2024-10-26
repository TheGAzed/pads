#include <greatest.h>

#ifndef TEST_LIST_MODE

#error No list mode was defined before testing ('TEST_LIST_MODE' is not defined).

#else

#define LIST_MODE TEST_LIST_MODE

#endif

//#define LIST_MODE INFINITE_ALLOCATED_LIST
#define LIST_ARRAY_LIST_CHUNK  10
#define REALLOC_LIST_CHUNK     10
#define PREPROCESSOR_LIST_SIZE 10
#include "list.h"

#if   LIST_MODE == INFINITE_ALLOCATED_LIST

SUITE (create_list_test) {
}

#elif LIST_MODE == FINITE_ALLOCATED_LIST

SUITE (create_list_test) {
}

#elif LIST_MODE == INFINITE_REALLOC_LIST

SUITE (create_list_test) {
}

#elif LIST_MODE == FINITE_PRERPOCESSOR_LIST

SUITE (create_list_test) {
}

#endif