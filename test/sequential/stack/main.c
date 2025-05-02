#include "stack_test.h"

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_list_stack_test);
    RUN_SUITE(finite_allocated_stack_test);
    RUN_SUITE(infinite_realloc_stack_test);
    RUN_SUITE(finite_preprocessor_stack_test);

    GREATEST_MAIN_END();
}
