#ifndef BINARY_SET_H
#define BINARY_SET_H

#ifdef BINARY_SET_HELP

#endif

// list mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_REALLOC_BINARY_SET  0x040
#define FINITE_ALLOCATED_BINARY_SET    0x080
#define FINITE_PRERPOCESSOR_BINARY_SET 0x100

#define INFINITE_BINARY_SET INFINITE_REALLOC_BINARY_SET
#define FINITE_BINARY_SET   FINITE_ALLOCATED_BINARY_SET

//#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET
// List mode that can be set to INFINITE_REALLOC_BINARY_SET, FINITE_ALLOCATED_BINARY_SET, INFINITE_REALLOC_DOUBLE_BINARY_SET or
// FINITE_PRERPOCESSOR_BINARY_SET, or INFINITE_REALLOC_BINARY_SET or FINITE_ALLOCATED_BINARY_SET
// Default: INFINITE_REALLOC_BINARY_SET
#ifndef BINARY_SET_MODE

#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET

#endif

#define IS_INFINITE_BINARY_SET ((bool)(BINARY_SET_MODE & 0x040))

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
    if (destroy_element) {
        for (size_t i = 0; i < set->size; ++i) {
            destroy_element(set->elements + i);
        }
    }
    free(set->elements);
    *set = (binary_set_s) { 0 };
}

static inline bool contains_binary_set(const binary_set_s set, BINARY_SET_DATA_TYPE element) {
    if (set.compare_elements) {
        return bsearch(&element, set.elements, set.size, sizeof(BINARY_SET_DATA_TYPE), set.compare_elements);
    }

    const BINARY_SET_DATA_TYPE * current_element = set.elements;
    for (size_t limit = set.size; limit != 0; limit >>= 1) {
        current_element += (limit >> 1);
        if (memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE)) == 0) {
            return true;
        }
        if (memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE)) > 0) {
            current_element++;
            limit--;
        }
    }

    return false;
}

static inline void add_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    if ((set->size % REALLOC_BINARY_SET_CHUNK) == 0) {
        set->elements = realloc(set->elements, (set->size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE));
        assert(set->elements && "[ERROR] Memory allocation failed.");
    }

    const BINARY_SET_DATA_TYPE * current_element = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        current_element += (limit >> 1);
        if (memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE)) == 0) {
            assert(set->elements && "[ERROR] Set already contains element");
            exit(EXIT_FAILURE);
        }
        if (memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE)) > 0) {
            current_element++;
            limit--;
        }
    }

    memmove(current_element + 1, current_element, ((set->size) - (current_element - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));
    *current_element = element;
    set->size++;
}

static inline BINARY_SET_DATA_TYPE remove_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    const BINARY_SET_DATA_TYPE * current_element = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        current_element += (limit >> 1);
        if (memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE)) == 0) {
            BINARY_SET_DATA_TYPE temp = current_element;
            memmove(current_element, current_element + 1, ((--set->size) - (current_element - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));

            if ((set->size % REALLOC_BINARY_SET_CHUNK) == 0) {
                set->elements = set->size ? realloc(set->elements, (set->size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)) : NULL;
                assert((!(set->size) || set->elements) && "[ERROR] Memory allocation failed.");
            }

            return temp;
        }
        if (memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE)) > 0) {
            current_element++;
            limit--;
        }
    }
    assert(set->elements && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE);
}

static inline binary_set_s union_binary_set(binary_set_s * set_one, binary_set_s * set_two) {
    assert(set_one->compare_elements == set_two->compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");

    if (set_one->size == 0 && set_two->size == 0) {
        return (binary_set_s) { .compare_elements = set_one->compare_elements, .elements = NULL, .size = 0, };;
    }
    const size_t chunk_size = set_one->size - (set_one->size % REALLOC_BINARY_SET_CHUNK) + REALLOC_BINARY_SET_CHUNK;
    binary_set_s set = {
        .compare_elements = set_one->compare_elements, .size = 0,
        .elements = malloc(sizeof(BINARY_SET_DATA_TYPE) * chunk_size),
    };
    memcpy(set.elements, set_one->elements, set_one->size * sizeof(BINARY_SET_DATA_TYPE));

    const BINARY_SET_DATA_TYPE * current_element = set.elements;
    if (set.compare_elements) {
        for (size_t i = 0; i < set_two->size; ++i) { // for each element in set two
            for (size_t limit = set_one->size - (current_element - set_one->elements); limit != 0; limit >>= 1) {
                current_element += (limit >> 1);
                if (set.compare_elements(current_element, set_two->elements + i) == 0) {
                    current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                    // if set (copy of set one) contains an element of set two then skip to first loop end (guarantee uniqueue values in new set)
                    goto LOOP_END;
                }
                if (set.compare_elements(current_element, set_two->elements + i) > 0) {
                    current_element++; // increment element pointer to next
                    limit--;
                }
            }

            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                const BINARY_SET_DATA_TYPE * temp = set.elements; // store temp for the case that new address of set.elements array changes when using realloc
                set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                assert(set.elements && "[ERROR] Memory allocation failed.");
                current_element = set.elements + (temp - current_element); // reset current_element pointer to new memory position if set.elements array changes
            }
            // shift current element + rest to the right to make space for uncontained element
            memmove(current_element + 1, current_element, (set.size - (current_element - set.elements)) * sizeof(BINARY_SET_DATA_TYPE));
            *current_element = set_two->elements[i]; // push set to new point
            set.size++;

            LOOP_END:
        }
    } else {
        for (size_t i = 0; i < set_two->size; ++i) { // for each element in set two
            for (size_t limit = set_one->size - (current_element - set_one->elements); limit != 0; limit >>= 1) {
                current_element += (limit >> 1);
                if (memcmp(current_element, set_two->elements + i, sizeof(BINARY_SET_DATA_TYPE)) == 0) {
                    current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                    // if set (copy of set one) contains an element of set two then skip to first loop end (guarantee uniqueue values in new set)
                    goto LOOP_END;
                }
                if (memcmp(current_element, set_two->elements + i, sizeof(BINARY_SET_DATA_TYPE)) > 0) {
                    current_element++; // increment element pointer to next
                    limit--;
                }
            }

            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                const BINARY_SET_DATA_TYPE * temp = set.elements; // store temp for the case that new address of set.elements array changes when using realloc
                set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                assert(set.elements && "[ERROR] Memory allocation failed.");
                current_element = set.elements + (temp - current_element); // reset current_element pointer to new memory position if set.elements array changes
            }
            // shift current element + rest to the right to make space for uncontained element
            memmove(current_element + 1, current_element, (set.size - (current_element - set.elements)) * sizeof(BINARY_SET_DATA_TYPE));
            *current_element = set_two->elements[i]; // push set to new point
            set.size++;

            LOOP_END:
        }
    }

    *set_one = *set_two = (binary_set_s) { 0 };
    return set;
}

static inline binary_set_s intersect_binary_set(binary_set_s * set_one, binary_set_s * set_two) {
    assert(set_one->compare_elements == set_two->compare_elements && "[ERROR] Can't union sets with different comapre funcitons.");
    binary_set_s set = { .compare_elements = set_one->compare_elements, .size = 0, .elements = NULL, };

    const BINARY_SET_DATA_TYPE * current_element = set_one->elements;
    if (set.compare_elements) {
        for (size_t i = 0; i < set_two->size; ++i) { // for each element in set two
            for (size_t limit = set_one->size - (current_element - set_one->elements); limit != 0; limit >>= 1) {
                current_element += (limit >> 1);
                if (set.compare_elements(current_element, set_two->elements + i) == 0) {
                    if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                        set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                        assert(set.elements && "[ERROR] Memory allocation failed.");
                    }

                    set.elements[set.size++] = set_two->elements[i];
                    current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                    break;
                }
                if (set.compare_elements(*current_element, set_two->elements + i) > 0) {
                    current_element++; // increment element pointer to next
                    limit--;
                }
            }
        }
    } else {
        for (size_t i = 0; i < set_two->size; ++i) { // for each element in set two
            for (size_t limit = set_one->size - (current_element - set_one->elements); limit != 0; limit >>= 1) {
                current_element += (limit >> 1);
                if (memcmp(current_element, set_two->elements + i, sizeof(BINARY_SET_DATA_TYPE)) == 0) {
                    if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                        set.elements = realloc(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                        assert(set.elements && "[ERROR] Memory allocation failed.");
                    }

                    set.elements[set.size++] = set_two->elements[i];
                    current_element++; // increment pointer to make sure that binary searches don't get repeated on found element
                    break;
                }
                if (memcmp(*current_element, set_two->elements + i, sizeof(BINARY_SET_DATA_TYPE)) > 0) {
                    current_element++; // increment element pointer to next
                    limit--;
                }
            }
        }
    }

    *set_one = *set_two = (binary_set_s) { 0 };
    return set;
}

#endif

#endif //BINARY_SET_H
