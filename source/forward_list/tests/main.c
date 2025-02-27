#include "forward_list_test.h"

void destroy_element(FORWARD_LIST_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (FORWARD_LIST_DATA_TYPE) { 0 };
}

FORWARD_LIST_DATA_TYPE copy_element(const FORWARD_LIST_DATA_TYPE element) {
    return (FORWARD_LIST_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

int compare_int(const void * a, const void * b) {
    return ((FORWARD_LIST_DATA_TYPE *)a)->sub_one - ((FORWARD_LIST_DATA_TYPE *)b)->sub_one;
}

int compare_string(const void * a, const void * b) {
    return strcmp(((FORWARD_LIST_DATA_TYPE *)a)->sub_two, ((FORWARD_LIST_DATA_TYPE *)b)->sub_two);
}

void sort_int(FORWARD_LIST_DATA_TYPE * elements, const size_t size) {
    qsort(elements, size, sizeof(FORWARD_LIST_DATA_TYPE), compare_int);
}

void sort_string(FORWARD_LIST_DATA_TYPE * elements, const size_t size) {
    qsort(elements, size, sizeof(FORWARD_LIST_DATA_TYPE), compare_string);
}

bool operation_int(FORWARD_LIST_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));

    return true;
}

bool operation_string(FORWARD_LIST_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);

    return true;
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_allocated_forward_list_test);
    RUN_SUITE(finite_allocated_forward_list_test);
    RUN_SUITE(infinite_realloc_forward_list_test);
    RUN_SUITE(finite_preprocessor_forward_list_test);

    GREATEST_MAIN_END();
}
