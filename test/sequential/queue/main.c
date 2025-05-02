#include "queue_test.h"

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(finite_allocated_queue_test);
    RUN_SUITE(infinite_list_queue_test);
    RUN_SUITE(infinite_realloc_queue_test);
    RUN_SUITE(finite_preprocessor_queue_test);

    GREATEST_MAIN_END();
}
