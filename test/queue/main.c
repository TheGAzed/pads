#include <greatest.h>

extern SUITE(create_queue_test);
extern SUITE(destroy_queue_test);

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(create_queue_test);
    RUN_SUITE(destroy_queue_test);

    GREATEST_MAIN_END();
}
