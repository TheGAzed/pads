#include <greatest.h>
#define BINARY_SET_DATA_TYPE int
#include <binary_set.h>

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
#ifndef TEST_BINARY_SET
    binary_set_s set_one = create_binary_set(NULL);
    add_binary_set(&set_one, 2);
    add_binary_set(&set_one, 4);
    add_binary_set(&set_one, 6);
    add_binary_set(&set_one, 5);
    add_binary_set(&set_one, 3);
    add_binary_set(&set_one, 1);

    binary_set_s set_two = create_binary_set(NULL);
    add_binary_set(&set_two, 4);
    add_binary_set(&set_two, 5);
    add_binary_set(&set_two, 6);
    add_binary_set(&set_two, 7);
    add_binary_set(&set_two, 8);
    add_binary_set(&set_two, 9);

    binary_set_s set = union_binary_set(set_one, set_two, NULL);
    destroy_binary_set(&set, NULL);

    set = intersect_binary_set(set_one, set_two, NULL);
    destroy_binary_set(&set, NULL);

    set = subtract_binary_set(set_one, set_two, NULL);
    destroy_binary_set(&set, NULL);

    set = exclude_binary_set(set_one, set_two, NULL);
    destroy_binary_set(&set, NULL);

    destroy_binary_set(&set_one, NULL);
    destroy_binary_set(&set_two, NULL);
#endif
    GREATEST_MAIN_END();
}
