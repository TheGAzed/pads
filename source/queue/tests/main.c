#include "queue_test.h"

void destroy_int(QUEUE_DATA_TYPE * element) {
    element->sub_one = 0;
}

void destroy_string(QUEUE_DATA_TYPE * element) {
    free(element->sub_two);
    element->sub_two = NULL;
}

QUEUE_DATA_TYPE copy_int(const QUEUE_DATA_TYPE element) {
    return (QUEUE_DATA_TYPE) { .sub_one = element.sub_one, };
}

QUEUE_DATA_TYPE copy_string(const QUEUE_DATA_TYPE element) {
    return (QUEUE_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

bool operation_int(QUEUE_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));

    return true;
}

bool operation_string(QUEUE_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);

    return true;
}

int compare_int(void * a, void * b) {
    return ((QUEUE_DATA_TYPE*)(a))->sub_one - ((QUEUE_DATA_TYPE*)(b))->sub_one;
}

int compare_reverse_int(void * a, void * b) {
    return ((QUEUE_DATA_TYPE*)(b))->sub_one - ((QUEUE_DATA_TYPE*)(a))->sub_one;
}

void sort_int(QUEUE_DATA_TYPE * elements, const size_t size, void * args) {
    qsort(elements, size, sizeof(QUEUE_DATA_TYPE), args);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(finite_allocated_queue_test);
    RUN_SUITE(infinite_list_queue_test);
    RUN_SUITE(infinite_realloc_queue_test);
    RUN_SUITE(finite_preprocessor_queue_test);

    GREATEST_MAIN_END();
}
