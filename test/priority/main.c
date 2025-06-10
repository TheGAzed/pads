#include <suits.h>

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(binary_heap_test);
    RUN_SUITE(sort_heap_test);

    GREATEST_MAIN_END();
}
