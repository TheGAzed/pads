#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include <stddef.h>

typedef union type_dst {
    int    sub_one;
    char * sub_two;
} type_dst_u;

struct compare {
    int (*function) (const void * a, const void * b);
};

#define DATA_TYPE type_dst_u

#define TEST_STRING "thegazed"

void destroy_int(DATA_TYPE * element);
void destroy_string(DATA_TYPE * element);

DATA_TYPE copy_int(const DATA_TYPE element);
DATA_TYPE copy_string(const DATA_TYPE element);

bool operation_int(DATA_TYPE * element, void * args);
bool operation_string(DATA_TYPE * element, void * args);

bool print_int(DATA_TYPE * element, void * format);
bool print_string(DATA_TYPE * element, void * format);

int compare_int(const DATA_TYPE a, const DATA_TYPE b);
int compare_reverse_int(const DATA_TYPE a, const DATA_TYPE b);

int compare_string(const DATA_TYPE a, const DATA_TYPE b);
int compare_reverse_string(const DATA_TYPE a, const DATA_TYPE b);

int compare_int_generic(const void * a, const void * b);
int compare_reverse_int_generic(const void * a, const void * b);

int compare_string_generic(const void * a, const void * b);
int compare_reverse_string_generic(const void * a, const void * b);

void sort_int(DATA_TYPE * elements, const size_t size, void * args);

size_t hash_int(const DATA_TYPE element);

size_t hash_string(const DATA_TYPE element);

#endif // FUNCTIONS_H
