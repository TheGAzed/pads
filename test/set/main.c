#include <suits.h>

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(bsearch_set_test);
    RUN_SUITE(bitwise_set_test);
    RUN_SUITE(hash_set_test);

    GREATEST_MAIN_END();
}
