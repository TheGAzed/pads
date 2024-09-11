#include <greatest.h>

extern SUITE(create_stack_test);
extern SUITE(destroy_stack_test);
extern SUITE(is_full_stack_test);
extern SUITE(peep_stack_test);

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(create_stack_test);
    RUN_SUITE(destroy_stack_test);
    RUN_SUITE(is_full_stack_test);
    RUN_SUITE(peep_stack_test);

    GREATEST_MAIN_END();
    return 0;
}