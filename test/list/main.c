#include <suits.h>

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(straight_list_test);
    RUN_SUITE(circular_list_test);
    RUN_SUITE(double_list_test);

    GREATEST_MAIN_END();
}
