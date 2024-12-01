#include "queue_test.h"

void destroy_element(QUEUE_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (QUEUE_DATA_TYPE) { 0 };
}

QUEUE_DATA_TYPE copy_element(const QUEUE_DATA_TYPE element) {
    return (QUEUE_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

int compare_int_asc(const void * a, const void * b) {
    return ((QUEUE_DATA_TYPE*)(a))->sub_one - ((QUEUE_DATA_TYPE*)(b))->sub_one;
}
int compare_int_desc(const void * a, const void * b) {
    return ((QUEUE_DATA_TYPE*)(b))->sub_one - ((QUEUE_DATA_TYPE*)(a))->sub_one;
}

int compare_string_asc(const void * a, const void * b) {
    return strncmp(((QUEUE_DATA_TYPE*)(a))->sub_two, ((QUEUE_DATA_TYPE*)(b))->sub_two, sizeof(TEST_STRING) - 1);
}
int compare_string_desc(const void * a, const void * b) {
    return strncmp(((QUEUE_DATA_TYPE*)(b))->sub_two, ((QUEUE_DATA_TYPE*)(a))->sub_two, sizeof(TEST_STRING) - 1);
}

void operation_int(QUEUE_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));
}

void operation_string(QUEUE_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_list_queue_test);
    RUN_SUITE(finite_allocated_queue_test);
    RUN_SUITE(infinite_realloc_queue_test);
    RUN_SUITE(finite_preprocessor_queue_test);

    GREATEST_MAIN_END();
}
