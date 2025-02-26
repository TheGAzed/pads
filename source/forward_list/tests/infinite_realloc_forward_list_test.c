#include "forward_list_test.h"

#define FORWARD_LIST_MODE INFINITE_REALLOC_FORWARD_LIST
#define REALLOC_FORWARD_LIST_CHUNK (1 << 4)
#include <forward_list/forward_list.h>

SUITE (infinite_realloc_forward_list_test) {
}
