#include "straight_list_test.h"

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_allocated_straight_list_test);
    RUN_SUITE(finite_allocated_straight_list_test);
    RUN_SUITE(infinite_realloc_straight_list_test);
    RUN_SUITE(finite_preprocessor_straight_list_test);

    GREATEST_MAIN_END();
}
