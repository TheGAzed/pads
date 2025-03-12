#include "straight_list_test.h"

#define STRAIGHT_LIST_MODE INFINITE_REALLOC_STRAIGHT_LIST
#define REALLOC_STRAIGHT_LIST_CHUNK (1 << 4)
#include <straight_list/straight_list.h>


SUITE (infinite_realloc_straight_list_test) {
}
