#include "binary_set_test.h"

void destroy_element(BINARY_SET_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (BINARY_SET_DATA_TYPE) { 0 };
}

BINARY_SET_DATA_TYPE copy_element(const BINARY_SET_DATA_TYPE element) {
    return (BINARY_SET_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

void operation_int(BINARY_SET_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));
}

void operation_string(BINARY_SET_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_realloc_binary_set_test);
    RUN_SUITE(finite_allocated_binary_set_test);
    RUN_SUITE(finite_preprocessor_binary_set_test);

    GREATEST_MAIN_END();
}
