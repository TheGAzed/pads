#include <greatest.h>

extern SUITE(create_queue_test);
extern SUITE(destroy_queue_test);
extern SUITE(is_full_queue_test);
extern SUITE(peek_queue_test);
extern SUITE(enqueue_test);
extern SUITE(dequeue_test);
extern SUITE(copy_queue_test);

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(create_queue_test);
    RUN_SUITE(destroy_queue_test);
    RUN_SUITE(is_full_queue_test);
    RUN_SUITE(peek_queue_test);
    RUN_SUITE(enqueue_test);
    RUN_SUITE(dequeue_test);
    RUN_SUITE(copy_queue_test);

    GREATEST_MAIN_END();
}
