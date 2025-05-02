#include "deque_test.h"

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_list_deque_test);
    RUN_SUITE(finite_allocated_deque_test);
    RUN_SUITE(infinite_realloc_deque_test);
    RUN_SUITE(finite_preprocessor_deque_test);

    GREATEST_MAIN_END();
}
