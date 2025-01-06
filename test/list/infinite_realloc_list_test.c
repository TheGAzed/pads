#include "list_test.h"

#define LIST_MODE INFINITE_REALLOC_LIST
#define REALLOC_LIST_CHUNK (1 << 4)
#include <list.h>

SUITE (infinite_realloc_list_test) {
}
