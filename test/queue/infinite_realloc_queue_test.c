#include "queue_test.h"

#define QUEUE_MODE INFINITE_REALLOC_QUEUE
#define REALLOC_QUEUE_CHUNK (1 << 4)
#include <queue.h>

SUITE (infinite_realloc_queue_test) {
}
