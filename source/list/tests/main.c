#include "list_test.h"

void destroy_element(LIST_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (LIST_DATA_TYPE) { 0 };
}

LIST_DATA_TYPE copy_element(const LIST_DATA_TYPE element) {
    return (LIST_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

int compare_int(const void * a, const void * b) {
    return ((LIST_DATA_TYPE *)a)->sub_one - ((LIST_DATA_TYPE *)b)->sub_one;
}

int compare_string(const void * a, const void * b) {
    return strcmp(((LIST_DATA_TYPE *)a)->sub_two, ((LIST_DATA_TYPE *)b)->sub_two);
}

bool operation_int(LIST_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));

    return true;
}

bool operation_string(LIST_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);

    return true;
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_allocated_list_test);
    RUN_SUITE(finite_allocated_list_test);
    RUN_SUITE(infinite_realloc_list_test);
    RUN_SUITE(finite_preprocessor_list_test);

    GREATEST_MAIN_END();
}
