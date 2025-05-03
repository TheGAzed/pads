#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destroy_int(DATA_TYPE * element) {
    (*element) = (DATA_TYPE) { 0 };
}

void destroy_string(DATA_TYPE * element) {
    free(element->sub_two);
    (*element) = (DATA_TYPE) { 0 };
}

DATA_TYPE copy_int(const DATA_TYPE element) {
    return (DATA_TYPE) { .sub_one = element.sub_one, };
}

DATA_TYPE copy_string(const DATA_TYPE element) {
    return (DATA_TYPE) { .sub_two = strcpy(calloc((strlen(element.sub_two) + 1), sizeof(char)), element.sub_two), };
}

bool operation_int(DATA_TYPE * element, void * args) {
    element->sub_one += *((int *)(args));
    return true;
}

bool operation_string(DATA_TYPE * element, void * args) {
    free(element->sub_two);
    element->sub_two = strcpy(calloc((strlen(args) + 1), sizeof(char)), args);
    return true;
}

bool print_int(DATA_TYPE * element, void * format) {
    printf(format, element->sub_one);
    fflush(stdout);

    return true;
}

bool print_string(DATA_TYPE * element, void * format) {
    printf(format, element);
    fflush(stdout);

    return true;
}

int compare_int(const DATA_TYPE a, const DATA_TYPE b) {
    return a.sub_one - b.sub_one;
}

int compare_reverse_int(const DATA_TYPE a, const DATA_TYPE b) {
    return b.sub_one - a.sub_one;
}

int compare_string(const DATA_TYPE a, const DATA_TYPE b) {
    return strcmp(a.sub_two, b.sub_two);
}

int compare_reverse_string(const DATA_TYPE a, const DATA_TYPE b) {
    return strcmp(b.sub_two, a.sub_two);
}


int compare_int_generic(const void * a, const void * b) {
    //return memcmp(a, b, sizeof(int));
    return ((DATA_TYPE*)(a))->sub_one - ((DATA_TYPE*)(b))->sub_one;
}

int compare_reverse_int_generic(const void * a, const void * b) {
    //return memcmp(b, a, sizeof(int));
    return ((DATA_TYPE*)(b))->sub_one - ((DATA_TYPE*)(a))->sub_one;
}

int compare_string_generic(const void * a, const void * b) {
    // return strcmp(a, b);
    return strcmp(((DATA_TYPE*)(a))->sub_two, ((DATA_TYPE*)(b))->sub_two);
}

int compare_reverse_string_generic(const void * a, const void * b) {
    // return strcmp(b, a);
    return strcmp(((DATA_TYPE*)(b))->sub_two, ((DATA_TYPE*)(a))->sub_two);
}


void sort_int(DATA_TYPE * elements, const size_t size, void * args) {
    qsort(elements, size, sizeof(DATA_TYPE), args);
}
