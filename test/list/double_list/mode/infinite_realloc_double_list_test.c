#include "double_list_test.h"

#include <functions.h>

#define DOUBLE_LIST_MODE INFINITE_REALLOC_DOUBLE_LIST
#define REALLOC_DOUBLE_LIST_CHUNK (1 << 4)
#include <list/double_list/double_list.h>

SUITE (infinite_realloc_double_list_test) {
}
