#include "stack_test.h"

void destroy_element(STACK_DATA_TYPE * element) {
    free(element->sub_two);
    *element = (STACK_DATA_TYPE) { 0 };
}

STACK_DATA_TYPE copy_element(const STACK_DATA_TYPE element) {
    return (STACK_DATA_TYPE) { .sub_two = strdup(element.sub_two), };
}

int compare_int_asc(const void * a, const void * b) {
    return ((STACK_DATA_TYPE*)(a))->sub_one - ((STACK_DATA_TYPE*)(b))->sub_one;
}
int compare_int_desc(const void * a, const void * b) {
    return ((STACK_DATA_TYPE*)(b))->sub_one - ((STACK_DATA_TYPE*)(a))->sub_one;
}

int compare_string_asc(const void * a, const void * b) {
    return strncmp(((STACK_DATA_TYPE*)(a))->sub_two, ((STACK_DATA_TYPE*)(b))->sub_two, sizeof(TEST_STRING) - 1);
}
int compare_string_desc(const void * a, const void * b) {
    return strncmp(((STACK_DATA_TYPE*)(b))->sub_two, ((STACK_DATA_TYPE*)(a))->sub_two, sizeof(TEST_STRING) - 1);
}

void operation_int(STACK_DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));
}

void operation_string(STACK_DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strdup(args);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(infinite_list_stack_test);

    GREATEST_MAIN_END();
}
