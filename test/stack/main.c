#include <greatest.h>

extern SUITE(create_stack_test);
extern SUITE(destroy_stack_test);
extern SUITE(is_full_stack_test);
extern SUITE(peep_stack_test);
extern SUITE(push_stack_test);
extern SUITE(pop_stack_test);
extern SUITE(copy_stack_test);
extern SUITE(sort_stack_test);

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(create_stack_test);
    RUN_SUITE(destroy_stack_test);
    RUN_SUITE(is_full_stack_test);
    RUN_SUITE(peep_stack_test);
    RUN_SUITE(push_stack_test);
    RUN_SUITE(pop_stack_test);
    RUN_SUITE(copy_stack_test);
    RUN_SUITE(sort_stack_test);

    GREATEST_MAIN_END();
}
