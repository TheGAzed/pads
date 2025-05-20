#include "binary_set_test.h"

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_realloc_binary_set_test);
    RUN_SUITE(finite_allocated_binary_set_test);
    RUN_SUITE(finite_preprocessor_binary_set_test);

    GREATEST_MAIN_END();
}
