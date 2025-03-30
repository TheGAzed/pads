#include "stack_test.h"

void destroy_element(STACK_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (STACK_DATA_TYPE) { 0 };
}

STACK_DATA_TYPE copy_element(const STACK_DATA_TYPE element) {
    return (STACK_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

bool operation_int(STACK_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));
    return true;
}

bool operation_string(STACK_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);
    return true;
}

int compare_element(void * a, void * b) {
    return ((STACK_DATA_TYPE*)(a))->sub_one - ((STACK_DATA_TYPE*)(b))->sub_one;
}

int compare_reverse_element(void * a, void * b) {
    return ((STACK_DATA_TYPE*)(b))->sub_one - ((STACK_DATA_TYPE*)(a))->sub_one;
}

void sort_element(STACK_DATA_TYPE * elements, const size_t size, void * args) {
    qsort(elements, size, sizeof(STACK_DATA_TYPE), args);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_list_stack_test);
    RUN_SUITE(finite_allocated_stack_test);
    RUN_SUITE(infinite_realloc_stack_test);
    RUN_SUITE(finite_preprocessor_stack_test);
    RUN_SUITE(finite_wrapper_stack_test);

    GREATEST_MAIN_END();
}
