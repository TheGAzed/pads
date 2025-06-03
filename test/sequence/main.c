#include <suits.h>

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(stack_test);
    RUN_SUITE(queue_test);
    RUN_SUITE(deque_test);

    GREATEST_MAIN_END();
}
