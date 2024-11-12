#ifndef BINARY_SET_H
#define BINARY_SET_H

#ifdef BINARY_SET_HELP

#endif

// list mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_REALLOC_BINARY_SET    0x800
#define FINITE_ALLOCATED_BINARY_SET    0x400
#define FINITE_PRERPOCESSOR_BINARY_SET 0xC00

#define INFINITE_BINARY_SET INFINITE_REALLOC_BINARY_SET
#define FINITE_BINARY_SET   FINITE_ALLOCATED_BINARY_SET

//#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET
// List mode that can be set to INFINITE_REALLOC_BINARY_SET, FINITE_ALLOCATED_BINARY_SET, INFINITE_REALLOC_DOUBLE_BINARY_SET or
// FINITE_PRERPOCESSOR_BINARY_SET, or INFINITE_REALLOC_BINARY_SET or FINITE_ALLOCATED_BINARY_SET
// Default: INFINITE_REALLOC_BINARY_SET
#ifndef BINARY_SET_MODE

#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET

#endif

#define IS_INFINITE_BINARY_SET !((bool)(BINARY_SET_MODE & 0x400))

// Check to make sure a valid list mode is selected.
#if (BINARY_SET_MODE != INFINITE_REALLOC_BINARY_SET) && (BINARY_SET_MODE != FINITE_ALLOCATED_BINARY_SET)    && \
(BINARY_SET_MODE != FINITE_PRERPOCESSOR_BINARY_SET)

#error Invalid type of list mode.

#endif

// List data type to specify what datatype to list.
// DEFAULT: void *
#ifndef BINARY_SET_DATA_TYPE

#define BINARY_SET_DATA_TYPE void*

#endif

#include <stdlib.h>  // imports size_t and malloc
#include <assert.h>  // imports assert for debugging
#include <stdbool.h> // imports bool for conditional queue functions (is_[state]_queue())
#include <string.h>  // imports memcpy

#if BINARY_SET_MODE == INFINITE_REALLOC_BINARY_SET

#ifndef REALLOC_BINARY_SET_CHUNK

#define REALLOC_BINARY_SET_CHUNK (1 << 10)

#endif

typedef struct binary_set {
    size_t size;
    BINARY_SET_DATA_TYPE * elements;
    int (*compare_elements)(const BINARY_SET_DATA_TYPE, const BINARY_SET_DATA_TYPE);
} binary_set_s;

static inline binary_set_s create_binary_set(int (*compare_elements)(const BINARY_SET_DATA_TYPE, const BINARY_SET_DATA_TYPE)) {
    return (binary_set_s) { .compare_elements = compare_elements, .elements = NULL, .size = 0, };
}

static inline void destroy_binary_set(binary_set_s * set, void (*destroy_element)(BINARY_SET_DATA_TYPE *)) {
    assert(set && "[ERROR] 'set' pointer parameter is NULL");

    for (size_t i = 0; destroy_element && i < set->size; ++i) {
        destroy_element(set->elements + i);
    }
    free(set->elements);
    *set = (binary_set_s) { 0 };
}

static inline bool contains_binary_set(const binary_set_s set, BINARY_SET_DATA_TYPE element) {
    if (set.compare_elements) {
        return bsearch(&element, set.elements, set.size, sizeof(BINARY_SET_DATA_TYPE), set.compare_elements);
    }

    BINARY_SET_DATA_TYPE * current_element = set.elements;
    for (size_t limit = set.size; limit != 0; limit >>= 1) {
        current_element += (limit >> 1);
        const int comparison = memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE));
        if (comparison == 0) {
            return true;
        }
        if (comparison > 0) {
            current_element++;
            limit--;
        }
    }

    return false;
}

static inline void add_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    assert(set && "[ERROR] 'set' pointer parameter is NULL");

    if ((set->size % REALLOC_BINARY_SET_CHUNK) == 0) {
        set->elements = realloc(set->elements, (set->size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE));
        assert(set->elements && "[ERROR] Memory allocation failed.");
    }

    BINARY_SET_DATA_TYPE * current_element = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        current_element += (limit >> 1);
        const int comparison = memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE));
        if (comparison == 0) {
            assert(set->elements && "[ERROR] Set already contains element");
            exit(EXIT_FAILURE);
        }
        if (comparison > 0) {
            current_element++;
            limit--;
        }
    }

    memmove(current_element + 1, current_element, ((set->size) - (current_element - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));
    memcpy(*current_element, element, sizeof(BINARY_SET_DATA_TYPE));
    set->size++;
}

static inline BINARY_SET_DATA_TYPE remove_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    assert(set && "[ERROR] 'set' pointer parameter is NULL");
    assert(set->size && "[ERROR] Can't remove from empty set.");
    assert(set->elements && "[ERROR] Expected elements array to not be NULL.");

    BINARY_SET_DATA_TYPE * current_element = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        current_element += (limit >> 1);
        const int comparison = memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE));
        if (comparison == 0) {
            BINARY_SET_DATA_TYPE temp = current_element;
            --set->size;
            memmove(current_element, current_element + 1, (set->size - (current_element - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));

            if ((set->size % REALLOC_BINARY_SET_CHUNK) == 0) {
                set->elements = set->size ? realloc(set->elements, (set->size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)) : NULL;
                assert((!(set->size) || set->elements) && "[ERROR] Memory allocation failed.");
            }

            return temp;
        }
        if (comparison > 0) {
            current_element++;
            limit--;
        }
    }
    assert(set->elements && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE);
}

static inline binary_set_s union_binary_set(const binary_set_s * set_one, const binary_set_s * set_two, BINARY_SET_DATA_TYPE * (*copy_element)(BINARY_SET_DATA_TYPE *, const BINARY_SET_DATA_TYPE *)) {
    assert(set_one && "[ERROR] 'set_one' pointer parameter is NULL");
    assert(set_two && "[ERROR] 'set_two' pointer parameter is NULL");
    assert(set_one->compare_elements == set_two->compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");

    binary_set_s set = *set_one;
    const size_t chunk_size = set_one->size - (set_one->size % REALLOC_BINARY_SET_CHUNK) + REALLOC_BINARY_SET_CHUNK;
    set.elements = set.size ? malloc(chunk_size * sizeof(BINARY_SET_DATA_TYPE)) : set_one->elements;
    memcpy(set.elements, set_one->elements, set_one->size * sizeof(BINARY_SET_DATA_TYPE));

    BINARY_SET_DATA_TYPE * current_element = set.elements;
    for (size_t i = 0; i < set_two->size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set.size - (current_element - set.elements); limit != 0; limit >>= 1) {
            current_element += (limit >> 1);
            const int comparison = set.compare_elements ? set.compare_elements(current_element, set_two->elements + i) : memcmp(current_element, set_two->elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                break;
            }
            if (comparison > 0) {
                current_element++; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                BINARY_SET_DATA_TYPE * temp = set.elements; // store temp for the case that new address of set.elements array changes when using realloc
                set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                assert(set.elements && "[ERROR] Memory allocation failed.");
                current_element = set.elements + (current_element - temp); // reset current_element pointer to new memory position if set.elements array changes
            }
            // shift current element + rest to the right to make space for uncontained element
            memmove(current_element + 1, current_element, (set.size - (current_element - set.elements)) * sizeof(BINARY_SET_DATA_TYPE));

            *current_element = set_two->elements[i]; // push set to new point
            set.size++;
        }
    }

    for (size_t i = 0; copy_element && i < set.size; ++i) {
        BINARY_SET_DATA_TYPE copy = { 0 };
        const BINARY_SET_DATA_TYPE temp = set.elements[i];
        copy_element(&copy, &temp);
        set.elements[i] = copy;
    }

    return set;
}

static inline binary_set_s intersect_binary_set(const binary_set_s * set_one, const binary_set_s * set_two, BINARY_SET_DATA_TYPE * (*copy_element)(BINARY_SET_DATA_TYPE *, const BINARY_SET_DATA_TYPE *)) {
    assert(set_one && "[ERROR] 'set_one' pointer parameter is NULL");
    assert(set_two && "[ERROR] 'set_two' pointer parameter is NULL");
    assert(set_one->compare_elements == set_two->compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");

    binary_set_s set = { .compare_elements = set_one->compare_elements, .size = 0, .elements = NULL, };

    BINARY_SET_DATA_TYPE * current_element = set_one->elements;
    for (size_t i = 0; i < set_two->size; ++i) { // for each element in set two
        for (size_t limit = set_one->size - (current_element - set_one->elements); limit != 0; limit >>= 1) {
            current_element += (limit >> 1);
            const int comparison = set.compare_elements ? set.compare_elements(current_element, set_two->elements + i) : memcmp(current_element, set_two->elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                    set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                    assert(set.elements && "[ERROR] Memory allocation failed.");
                }

                set.elements[set.size++] = set_two->elements[i];
                current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                break;
            }
            if (comparison > 0) {
                current_element++; // increment element pointer to next
                limit--;
            }
        }
    }

    for (size_t i = 0; copy_element && i < set.size; ++i) {
        BINARY_SET_DATA_TYPE copy = { 0 };
        const BINARY_SET_DATA_TYPE temp = set.elements[i];
        copy_element(&copy, &temp);
        set.elements[i] = copy;
    }

    return set;
}

static inline binary_set_s difference_binary_set(const binary_set_s * set_one, const binary_set_s * set_two, BINARY_SET_DATA_TYPE * (*copy_element)(BINARY_SET_DATA_TYPE *, const BINARY_SET_DATA_TYPE *)) {
    assert(set_one && "[ERROR] 'set_one' pointer parameter is NULL");
    assert(set_two && "[ERROR] 'set_two' pointer parameter is NULL");
    assert(set_one->compare_elements == set_two->compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");

    binary_set_s set = { .compare_elements = set_one->compare_elements, .elements = NULL, .size = 0 };

    BINARY_SET_DATA_TYPE * current_element = set_two->elements;
    for (size_t i = 0; i < set_one->size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_two->size - (current_element - set.elements); limit != 0; limit >>= 1) {
            current_element += (limit >> 1);
            const int comparison = set.compare_elements ? set.compare_elements(current_element, set_one->elements + i) : memcmp(current_element, set_one->elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                break;
            }
            if (comparison > 0) {
                current_element++; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            // if set_one's element was not found in set_two push it to new set (set_one does not contain elements in set two)
            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                assert(set.elements && "[ERROR] Memory allocation failed.");
            }

            set.elements[set.size] = set_one->elements[i]; // push set to new point
            set.size++;
        }
    }

    for (size_t i = 0; copy_element && i < set.size; ++i) {
        BINARY_SET_DATA_TYPE copy = { 0 };
        const BINARY_SET_DATA_TYPE temp = set.elements[i];
        copy_element(&copy, &temp);
        set.elements[i] = copy;
    }

    return set;
}

static inline binary_set_s exclusive_union_binary_set(const binary_set_s * set_one, const binary_set_s * set_two, BINARY_SET_DATA_TYPE * (*copy_element)(BINARY_SET_DATA_TYPE *, const BINARY_SET_DATA_TYPE *)) {
    assert(set_one && "[ERROR] 'set_one' pointer parameter is NULL");
    assert(set_two && "[ERROR] 'set_two' pointer parameter is NULL");
    assert(set_one->compare_elements == set_two->compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");

    binary_set_s set = *set_one;
    const size_t chunk_size = set_one->size - (set_one->size % REALLOC_BINARY_SET_CHUNK) + REALLOC_BINARY_SET_CHUNK;
    set.elements = set.size ? malloc(chunk_size * sizeof(BINARY_SET_DATA_TYPE)) : set_one->elements;
    memcpy(set.elements, set_one->elements, set_one->size * sizeof(BINARY_SET_DATA_TYPE));

    BINARY_SET_DATA_TYPE * current_element = set.elements;
    for (size_t i = 0; i < set_two->size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set.size - (current_element - set.elements); limit != 0; limit >>= 1) {
            current_element += (limit >> 1);
            const int comparison = set.compare_elements ? set.compare_elements(current_element, set_two->elements + i) : memcmp(current_element, set_two->elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                --set.size;
                memmove(current_element, current_element + 1, (set.size - (current_element - set.elements)) * sizeof(BINARY_SET_DATA_TYPE)); // shift left if in both

                if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // contract set chunk size if element contained in both
                    BINARY_SET_DATA_TYPE * temp = set.elements; // store temp for the case that new address of set.elements array changes when using realloc
                    set.elements = realloc(set.elements, (set.size - REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                    assert(set.elements && "[ERROR] Memory allocation failed.");
                    current_element = set.elements + (current_element - temp); // reset current_element pointer to new memory position if set.elements array changes
                }
                break;
            }
            if (comparison > 0) {
                current_element++; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                BINARY_SET_DATA_TYPE * temp = set.elements; // store temp for the case that new address of set.elements array changes when using realloc
                set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                assert(set.elements && "[ERROR] Memory allocation failed.");
                current_element = set.elements + (current_element - temp); // reset current_element pointer to new memory position if set.elements array changes
            }
            // shift current element + rest to the right to make space for uncontained element
            memmove(current_element + 1, current_element, (set.size - (current_element - set.elements)) * sizeof(BINARY_SET_DATA_TYPE));

            *current_element = set_two->elements[i]; // push set to new point
            set.size++;
        }
    }

    for (size_t i = 0; copy_element && i < set.size; ++i) {
        BINARY_SET_DATA_TYPE copy = { 0 };
        const BINARY_SET_DATA_TYPE temp = set.elements[i];
        copy_element(&copy, &temp);
        set.elements[i] = copy;
    }

    return set;
}

static inline bool is_subset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    assert(set_one.compare_elements == set_two.compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");

    BINARY_SET_DATA_TYPE * current_element = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        bool found_element = false;
        for (size_t limit = set_two.size - (current_element - set_two.elements); limit != 0; limit >>= 1) {
            current_element += (limit >> 1);
            const int comparison = set_one.compare_elements ? set_one.compare_elements(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                break;
            }
            if (comparison > 0) {
                current_element++; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true;
}

static inline bool is_superset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    assert(set_one.compare_elements == set_two.compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");

    BINARY_SET_DATA_TYPE * current_element = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_one.size - (current_element - set_one.elements); limit != 0; limit >>= 1) {
            current_element += (limit >> 1);
            const int comparison = set_two.compare_elements ? set_two.compare_elements(current_element, set_two.elements + i) : memcmp(current_element, set_two.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                break;
            }
            if (comparison > 0) {
                current_element++; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }
    return true;
}

#endif

#endif //BINARY_SET_H
