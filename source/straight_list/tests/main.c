#include "straight_list_test.h"

void destroy_element(STRAIGHT_LIST_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (STRAIGHT_LIST_DATA_TYPE) { 0 };
}

STRAIGHT_LIST_DATA_TYPE copy_element(const STRAIGHT_LIST_DATA_TYPE element) {
    return (STRAIGHT_LIST_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

int cmpint(const void * a, const void * b) {
    return ((STRAIGHT_LIST_DATA_TYPE*)a)->sub_one - ((STRAIGHT_LIST_DATA_TYPE*)b)->sub_one;
}

int cmpstr(const void * a, const void * b) {
    return strcmp(((STRAIGHT_LIST_DATA_TYPE*)a)->sub_two, ((STRAIGHT_LIST_DATA_TYPE*)b)->sub_two);
}

int compare_int(const STRAIGHT_LIST_DATA_TYPE a, const STRAIGHT_LIST_DATA_TYPE b) {
    return a.sub_one - b.sub_one;
}

int compare_string(const STRAIGHT_LIST_DATA_TYPE a, const STRAIGHT_LIST_DATA_TYPE b) {
    return strcmp(a.sub_two, b.sub_two);
}

void sort_int(STRAIGHT_LIST_DATA_TYPE * elements, const size_t size, void * args) {
    qsort(elements, size, sizeof(STRAIGHT_LIST_DATA_TYPE), cmpint);
}

void sort_string(STRAIGHT_LIST_DATA_TYPE * elements, const size_t size, void * args) {
    qsort(elements, size, sizeof(STRAIGHT_LIST_DATA_TYPE), cmpstr);
}

bool operation_int(STRAIGHT_LIST_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));

    return true;
}

bool operation_string(STRAIGHT_LIST_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);

    return true;
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_allocated_straight_list_test);
    RUN_SUITE(finite_allocated_straight_list_test);
    RUN_SUITE(infinite_realloc_straight_list_test);
    RUN_SUITE(finite_preprocessor_straight_list_test);

    GREATEST_MAIN_END();
}
