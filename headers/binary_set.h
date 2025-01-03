#ifndef BINARY_SET_H
#define BINARY_SET_H

// SOURCE AND LICENCE OF BINARY SEARCH IMPLEMENTATION: https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. [rescinded 22 July 1999]
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef STACK_LICENCE

#error \
    This is free and unencumbered software released into the public domain. \
    \
    Anyone is free to copy, modify, publish, use, compile, sell, or         \
    distribute this software, either in source code form or as a compiled   \
    binary, for any purpose, commercial or non-commercial, and by any       \
    means.                                                                  \
    \
    In jurisdictions that recognize copyright laws, the author or authors   \
    of this software dedicate any and all copyright interest in the         \
    software to the public domain. We make this dedication for the benefit  \
    of the public at large and to the detriment of our heirs and            \
    successors. We intend this dedication to be an overt act of             \
    relinquishment in perpetuity of all present and future rights to this   \
    software under copyright law.                                           \
    \
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,         \
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF      \
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  \
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR       \
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,   \
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR   \
    OTHER DEALINGS IN THE SOFTWARE.                                         \
    \
    For more information, please refer to <https://unlicense.org>           \

#endif

// set mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_REALLOC_BINARY_SET    0x9
#define FINITE_ALLOCATED_BINARY_SET    0xA
#define FINITE_PRERPOCESSOR_BINARY_SET 0xC

#define INFINITE_BINARY_SET INFINITE_REALLOC_BINARY_SET
#define FINITE_BINARY_SET   FINITE_ALLOCATED_BINARY_SET

//#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET
//#define BINARY_SET_MODE FINITE_ALLOCATED_BINARY_SET
//#define BINARY_SET_MODE FINITE_PRERPOCESSOR_BINARY_SET
// Set mode that can be set to INFINITE_REALLOC_BINARY_SET, FINITE_ALLOCATED_BINARY_SET or
// FINITE_PRERPOCESSOR_BINARY_SET
// Default: INFINITE_REALLOC_BINARY_SET
#ifndef BINARY_SET_MODE

#define BINARY_SET_MODE INFINITE_REALLOC_BINARY_SET

#endif

#define IS_INFINITE_BINARY_SET ((bool)(BINARY_SET_MODE & 0x1))

// Check to make sure a valid list mode is selected.
#if (BINARY_SET_MODE != INFINITE_REALLOC_BINARY_SET) && (BINARY_SET_MODE != FINITE_ALLOCATED_BINARY_SET)    && \
(BINARY_SET_MODE != FINITE_PRERPOCESSOR_BINARY_SET)

#error Invalid type of list mode.

#endif

// Set data type to specify what datatype to set.
// DEFAULT: void *
#ifndef BINARY_SET_DATA_TYPE

#define BINARY_SET_DATA_TYPE void*

#endif

#include <stdlib.h>  // imports size_t and malloc
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy

#ifndef BINARY_SET_ASSERT

#include <assert.h>  // imports assert for debugging
#define BINARY_SET_ASSERT assert

#ifndef BINARY_SET_ALLOC

#define BINARY_SET_ALLOC malloc

#endif

#ifndef BINARY_SET_REALLOC

#define BINARY_SET_REALLOC realloc

#endif

#endif

typedef BINARY_SET_DATA_TYPE (* copy_binary_set_fn)    (const BINARY_SET_DATA_TYPE);     // copies and returns set element
typedef void                 (* destroy_binary_set_fn) (BINARY_SET_DATA_TYPE *);         // destroys and sets to zero set element
typedef int                  (* compare_binary_set_fn) (const void *, const void *);     // compares two set elements like strcmp or memcmp
typedef bool                 (* operate_binary_set_fn) (BINARY_SET_DATA_TYPE *, void *); // compares two set elements like strcmp or memcmp

#if BINARY_SET_MODE == INFINITE_REALLOC_BINARY_SET

#ifndef REALLOC_BINARY_SET_CHUNK

#define REALLOC_BINARY_SET_CHUNK (1 << 10)

#endif

/// Binary set data structure
typedef struct binary_set {
    size_t size;                     // set size/number of elements
    BINARY_SET_DATA_TYPE * elements; // elements array
    compare_binary_set_fn compare;   // comapre function pointer
} binary_set_s;

/// @brief Creates and returns an empty binary set structure.
/// @param compare Function pointer that compares two set elements like strcmp or memcmp does. 'memcmp' will be used if
/// parameter is NULL.
/// @return Empty binary set data structure.
static inline binary_set_s create_binary_set(const compare_binary_set_fn compare) {
    return (binary_set_s) { .compare = compare, .elements = NULL, .size = 0, };
}

/// @brief Destroys and frees/nullifies binary set structure.
/// @param set Pointer to binary set data structure to destroy.
/// @param destroy Function pointer that frees/nullifies a set element. Can be NULL if element doesn't use allocated
/// memory.
static inline void destroy_binary_set(binary_set_s * set, const destroy_binary_set_fn destroy) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL");

    for (size_t i = 0; destroy && i < set->size; ++i) {
        destroy(set->elements + i);
    }
    free(set->elements);
    *set = (binary_set_s) { 0 };
}

static inline bool contains_binary_set(const binary_set_s set, const BINARY_SET_DATA_TYPE element) {
    if (set.compare) { // uses buildin binary search implmentation if compare function is specified
        return bsearch(&element, set.elements, set.size, sizeof(BINARY_SET_DATA_TYPE), set.compare) != NULL;
    }
    // else custom binary search is used as memcmp takes three arguments as input
    // (bsearch requires a 2 argument compare function). IF ONLY NESTED FUNCTION WERE PART OF THE C STANDARD.

    BINARY_SET_DATA_TYPE * base = set.elements;
    for (size_t limit = set.size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int cmp = memcmp(&element, current_element, sizeof(BINARY_SET_DATA_TYPE));
        if (cmp == 0) {
            return true;
        }
        if (cmp > 0) {
            base = current_element + 1; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

static inline void add_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL");

    if ((set->size % REALLOC_BINARY_SET_CHUNK) == 0) {
        set->elements = BINARY_SET_REALLOC(set->elements, (set->size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE));
        BINARY_SET_ASSERT(set->elements && "[ERROR] Memory allocation failed.");
    }

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int cmp = set->compare ? set->compare(&element, current_element) : memcmp(&element, current_element, sizeof(BINARY_SET_DATA_TYPE));
        if (cmp == 0) {
            BINARY_SET_ASSERT(set->elements && "[ERROR] Set already contains element.");
            exit(EXIT_FAILURE);
        }
        if (cmp > 0) {
            base = current_element + 1;
            limit--;
        }
    }

    memmove(base + 1, base, (set->size - (base - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));
    memcpy(base, &element, sizeof(BINARY_SET_DATA_TYPE));
    set->size++;
}

static inline BINARY_SET_DATA_TYPE remove_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL");
    BINARY_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");
    BINARY_SET_ASSERT(set->elements && "[ERROR] Expected elements array to not be NULL.");

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int comparison = set->compare ? set->compare(current_element, &element) : memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE));
        if (comparison == 0) {
            BINARY_SET_DATA_TYPE temp = *current_element;
            --set->size;
            memmove(current_element, current_element + 1, (set->size - (current_element - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));

            if ((set->size % REALLOC_BINARY_SET_CHUNK) == 0) {
                set->elements = set->size ? BINARY_SET_REALLOC(set->elements, set->size * sizeof(BINARY_SET_DATA_TYPE)) : NULL;
                BINARY_SET_ASSERT((!(set->size) || set->elements) && "[ERROR] Memory allocation failed.");
            }

            return temp;
        }
        if (comparison > 0) {
            base = current_element + 1;
            limit--;
        }
    }
    BINARY_SET_ASSERT(set->elements && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE);
}

static inline binary_set_s union_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    binary_set_s set = { .compare = set_one.compare, .size = set_one.size, .elements = NULL, };
    if (set.size) {
        set.elements = malloc((set_one.size - (set_one.size % REALLOC_BINARY_SET_CHUNK) + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE));
        memcpy(set.elements, set_one.elements, set_one.size * sizeof(BINARY_SET_DATA_TYPE));
    }

    BINARY_SET_DATA_TYPE * base = set.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set.size - (base - set.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            const size_t index = (base - set.elements);
            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                set.elements = BINARY_SET_REALLOC(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");
                base = set.elements + index; // reset current_element pointer to new memory position if set.elements array changes
            }

            memmove(base + 1, base, (set.size - index) * sizeof(BINARY_SET_DATA_TYPE));
            *base = set_two.elements[i];
            set.size++;
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s intersect_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't intersect sets with different compare functions.");

    binary_set_s set = { .compare = set_one.compare, .size = 0, .elements = NULL, };

    BINARY_SET_DATA_TYPE * base = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set.compare ? set.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                    set.elements = BINARY_SET_REALLOC(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                    BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");
                }

                set.elements[set.size++] = set_two.elements[i];
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s subtract_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't subtract sets with different compare functions.");

    binary_set_s set = { .compare = set_one.compare, .elements = NULL, .size = 0 };

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(set_one.elements + i, current_element) : memcmp(set_one.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            // if set_one's element was not found in set_two push it to new set (set_one does not contain elements in set two)
            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                set.elements = BINARY_SET_REALLOC(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");
            }

            set.elements[(set.size)++] = set_one.elements[i]; // push set to new point
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s exclude_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't exclude sets with different compare functions.");

    binary_set_s set = { .compare = set_one.compare, .size = set_one.size, .elements = set_one.elements, };
    if (set_one.size) {
        set.elements = malloc((set_one.size - (set_one.size % REALLOC_BINARY_SET_CHUNK) + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE));
        memcpy(set.elements, set_one.elements, set_one.size * sizeof(BINARY_SET_DATA_TYPE));
    }

    BINARY_SET_DATA_TYPE * base = set.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set.size - (base - set.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set.compare ? set.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                --set.size;
                memmove(current_element, current_element + 1, (set.size - (current_element - set.elements)) * sizeof(BINARY_SET_DATA_TYPE)); // shift left if in both

                if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // contract set chunk size if it elements can fit
                    const size_t index = base - set.elements;
                    set.elements = BINARY_SET_REALLOC(set.elements, set.size * sizeof(BINARY_SET_DATA_TYPE)); // contract set's elements array
                    BINARY_SET_ASSERT((!(set.size) || set.elements) && "[ERROR] Memory allocation failed.");
                    base = set.elements + index; // reset current_element pointer to new memory position if set.elements array changes
                }
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            const size_t index = base - set.elements;
            if ((set.size % REALLOC_BINARY_SET_CHUNK) == 0) { // expand set chunk size if needed
                set.elements = BINARY_SET_REALLOC(set.elements, (set.size + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)); // expand set.elements array
                BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");
                base = set.elements + index; // reset current_element pointer to new memory position if set.elements array changes
            }
            // shift current element + rest to the right to make space for uncontained element
            memmove(base + 1, base, (set.size - index) * sizeof(BINARY_SET_DATA_TYPE));

            *base = set_two.elements[i]; // push set to new point
            set.size++;
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline bool is_subset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_subset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true && (set_one.size != set_two.size);
}

static inline bool is_superset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(current_element, set_two.elements + i) : memcmp(current_element, set_two.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_superset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(current_element, set_two.elements + i) : memcmp(current_element, set_two.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true && (set_one.size != set_two.size);
}

static inline bool is_disjoint_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                return false;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
    }

    return true;
}

static inline binary_set_s copy_binary_set(const binary_set_s set, const copy_binary_set_fn copy) {
    const binary_set_s set_copy = {
        .compare = set.compare, .size = set.size,
        .elements = set.size ? malloc((set.size - (set.size % REALLOC_BINARY_SET_CHUNK) + REALLOC_BINARY_SET_CHUNK) * sizeof(BINARY_SET_DATA_TYPE)) : NULL,
    };

    if (copy) {
        for (size_t i = 0; i < set_copy.size; ++i) {
            set_copy.elements[i] = copy(set.elements[i]);
        }
    } else {
        memcpy(set_copy.elements, set.elements, sizeof(BINARY_SET_DATA_TYPE) * set.size);
    }

    return set_copy;
}

static inline bool is_empty_binary_set(const binary_set_s set) {
    return !(set.size);
}

static inline bool is_full_binary_set(const binary_set_s set) {
    return !(~(set.size));
}

static inline void foreach_binary_set(binary_set_s * set, const operate_binary_set_fn operate, void * args) {
    for (size_t i = 0; i < set->size; ++i) {
        if (!operate(set->elements + i, args)) return;
    }
}

#elif BINARY_SET_MODE == FINITE_ALLOCATED_BINARY_SET

typedef struct binary_set {
    size_t size, max;
    BINARY_SET_DATA_TYPE * elements;
    compare_binary_set_fn compare;
} binary_set_s;

/// @brief Creates and returns an empty binary set structure.
/// @param max Maximum size of elements the sset can have/allocated memory array.
/// @param compare Function pointer that compares two set elements like strcmp or memcmp does. 'memcmp' will be used if
/// parameter is NULL.
/// @return Empty binary set data structure.
static inline binary_set_s create_binary_set(const size_t max, const compare_binary_set_fn compare) {
    BINARY_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    const binary_set_s set =  {
        .compare = compare, .size = 0, .max = max,
        .elements = malloc(sizeof(BINARY_SET_DATA_TYPE) * max),
    };

    BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");
    return set;
}

/// @brief Destroys and frees/nullifies binary set structure.
/// @param set Pointer to binary set data structure to destroy.
/// @param destroy Function pointer that frees/nullifies a set element. Can be NULL if element doesn't use allocated
/// memory.
static inline void destroy_binary_set(binary_set_s * set, const destroy_binary_set_fn destroy) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set->max && "[ERROR] Set's max size can't be zero");
    BINARY_SET_ASSERT(set->elements && "[ERROR] Set's elements pointer is NULL.");

    for (size_t i = 0; destroy && i < set->size; ++i) {
        destroy(set->elements + i);
    }
    free(set->elements);
    *set = (binary_set_s) { 0 };
}

static inline bool contains_binary_set(const binary_set_s set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set.max && "[ERROR] Set's max size can't be zero");
    BINARY_SET_ASSERT(set.elements && "[ERROR] Set's elements pointer is NULL.");

    if (set.compare) {
        return (bool) bsearch(&element, set.elements, set.size, sizeof(BINARY_SET_DATA_TYPE), set.compare);
    }

    BINARY_SET_DATA_TYPE * base = set.elements;
    for (size_t limit = set.size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int cmp = set.compare ? set.compare(&element, current_element) : memcmp(&element, current_element, sizeof(BINARY_SET_DATA_TYPE));
        if (cmp == 0) {
            return true;
        }
        if (cmp > 0) {
            base = current_element + 1; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

static inline void add_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set->max && "[ERROR] Set's max size can't be zero");
    BINARY_SET_ASSERT(set->elements && "[ERROR] Set's elements pointer is NULL.");
    BINARY_SET_ASSERT(set->size <= set->max && "[ERROR] Set is full.");

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int cmp = set->compare ? set->compare(&element, current_element) : memcmp(&element, current_element, sizeof(BINARY_SET_DATA_TYPE));
        if (cmp == 0) {
            BINARY_SET_ASSERT(set->elements && "[ERROR] Set already contains element.");
            exit(EXIT_FAILURE);
        }
        if (cmp > 0) {
            base = current_element + 1;
            limit--;
        }
    }

    memmove(base + 1, base, (set->size - (base - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));
    memcpy(base, &element, sizeof(BINARY_SET_DATA_TYPE));
    set->size++;
}

static inline BINARY_SET_DATA_TYPE remove_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set->max && "[ERROR] Set's max size can't be zero");
    BINARY_SET_ASSERT(set->elements && "[ERROR] Set's elements pointer is NULL.");
    BINARY_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int comparison = set->compare ? set->compare(current_element, &element) : memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE));
        if (comparison == 0) {
            BINARY_SET_DATA_TYPE temp = *current_element;
            --set->size;
            memmove(current_element, current_element + 1, (set->size - (current_element - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));

            return temp;
        }
        if (comparison > 0) {
            base = current_element + 1;
            limit--;
        }
    }
    BINARY_SET_ASSERT(set->elements && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE);
}

static inline binary_set_s union_binary_set(const binary_set_s set_one, const binary_set_s set_two, const size_t max, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");
    BINARY_SET_ASSERT(max >= set_one.size && "[ERROR] 'max' parameter smaller than set_one's size.");

    binary_set_s set = {
        .compare = set_one.compare, .size = set_one.size, .max = max,
        .elements = malloc(max * sizeof(BINARY_SET_DATA_TYPE)),
    };
    BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");
    memcpy(set.elements, set_one.elements, set_one.size * sizeof(BINARY_SET_DATA_TYPE));

    BINARY_SET_DATA_TYPE * base = set.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set.size - (base - set.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            BINARY_SET_ASSERT(set.size <= set.max && "[ERROR] Set is full.");
            memmove(base + 1, base, (set.size - (base - set.elements)) * sizeof(BINARY_SET_DATA_TYPE));
            *base = set_two.elements[i];
            set.size++;
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s intersect_binary_set(const binary_set_s set_one, const binary_set_s set_two, const size_t max, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't intersect sets with different compare functions.");

    binary_set_s set = {
        .compare = set_one.compare, .size = set_one.size, .max = max,
        .elements = malloc(max * sizeof(BINARY_SET_DATA_TYPE)),
    };
    BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");

    BINARY_SET_DATA_TYPE * base = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set.compare ? set.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                BINARY_SET_ASSERT(set.size <= set.max && "[ERROR] Set is full.");
                set.elements[set.size++] = set_two.elements[i];
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s subtract_binary_set(const binary_set_s set_one, const binary_set_s set_two, const size_t max, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't subtract sets with different compare functions.");

    binary_set_s set = {
        .compare = set_one.compare, .size = set_one.size, .max = max,
        .elements = malloc(max * sizeof(BINARY_SET_DATA_TYPE)),
    };
    BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(set_one.elements + i, current_element) : memcmp(set_one.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            BINARY_SET_ASSERT(set.size <= set.max && "[ERROR] Set is full.");
            set.elements[set.size++] = set_one.elements[i]; // push set to new point
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s exclude_binary_set(const binary_set_s set_one, const binary_set_s set_two, const size_t max, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't exclude sets with different compare functions.");

    // special case since we can't tell if exclude can fit all elements before adding them since exclude both adds and removes elements in new set
    binary_set_s set = {
        .compare = set_one.compare, .size = set_one.size, .max = max,
        .elements = malloc((set_one.size + set_two.size) * sizeof(BINARY_SET_DATA_TYPE)), // maximum possible size for any exclude
    };
    BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");

    BINARY_SET_DATA_TYPE * base = set.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set.size - (base - set.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set.compare ? set.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                --set.size;
                memmove(current_element, current_element + 1, (set.size - (current_element - set.elements)) * sizeof(BINARY_SET_DATA_TYPE)); // shift left if in both
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            // shift current element + rest to the right to make space for uncontained element
            memmove(base + 1, base, (set.size - (base - set.elements)) * sizeof(BINARY_SET_DATA_TYPE));

            *base = set_two.elements[i]; // push set to new point
            set.size++;
        }
    }

    BINARY_SET_ASSERT(set.size <= set.max && "[ERROR] Set is full.");
    set.elements = BINARY_SET_REALLOC(set.elements, set.max * sizeof(BINARY_SET_DATA_TYPE));  // shorten elements array to max

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline bool is_subset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check subset with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_subset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check proper subset with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true && (set_one.size != set_two.size);
}

static inline bool is_superset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check superset with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(current_element, set_two.elements + i) : memcmp(current_element, set_two.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_superset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check proper superset with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(current_element, set_two.elements + i) : memcmp(current_element, set_two.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true && (set_one.size != set_two.size);
}

static inline bool is_disjoint_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] set_one's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_two.max && "[ERROR] set_two's max size can't be zero");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] set_two's elements pointer is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check disjoint sets with different compare functions.");

    BINARY_SET_DATA_TYPE * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                return false;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
    }

    return true;
}

static inline binary_set_s copy_binary_set(const binary_set_s set, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set.max && "[ERROR] set_one's max size can't be zero");
    BINARY_SET_ASSERT(set.elements && "[ERROR] set_one's elements pointer is NULL.");

    const binary_set_s set_copy = {
        .compare = set.compare, .size = set.size, .max = set.max,
        .elements = malloc(set.max * sizeof(BINARY_SET_DATA_TYPE)),
    };
    BINARY_SET_ASSERT(set_copy.elements && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t i = 0; i < set_copy.size; ++i) {
            set_copy.elements[i] = copy(set.elements[i]);
        }
    } else {
        memcpy(set_copy.elements, set.elements, sizeof(BINARY_SET_DATA_TYPE) * set.size);
    }

    return set_copy;
}

static inline bool is_empty_binary_set(const binary_set_s set) {
    return !(set.size);
}

static inline bool is_full_binary_set(const binary_set_s set) {
    return !(set.size < set.max && ~set.size);
}

static inline void foreach_binary_set(binary_set_s * set, const operate_binary_set_fn operate, void * args) {
    for (size_t i = 0; i < set->size; ++i) {
        if (!operate(set->elements + i, args)) return;
    }
}

#elif BINARY_SET_MODE == FINITE_PRERPOCESSOR_BINARY_SET

#ifndef PREPROCESSOR_BINARY_SET_SIZE

#define PREPROCESSOR_BINARY_SET_SIZE (1 << 10)

#elif PREPROCESSOR_BINARY_SET_SIZE == 0

#error 'PREPROCESSOR_BINARY_SET_SIZE' cannot be zero

#endif

typedef struct binary_set {
    size_t size;
    BINARY_SET_DATA_TYPE elements[PREPROCESSOR_BINARY_SET_SIZE];
    compare_binary_set_fn compare;
} binary_set_s;

/// @brief Creates and returns an empty binary set structure.
/// @param compare Function pointer that compares two set elements like strcmp or memcmp does. 'memcmp' will be used if
/// parameter is NULL.
/// @return Empty binary set data structure.
static inline binary_set_s create_binary_set(const compare_binary_set_fn compare) {
    return (binary_set_s) {
        .compare = compare, .size = 0,
    };
}

/// @brief Destroys and frees/nullifies binary set structure.
/// @param set Pointer to binary set data structure to destroy.
/// @param destroy Function pointer that frees/nullifies a set element. Can be NULL if element doesn't use allocated
/// memory.
static inline void destroy_binary_set(binary_set_s * set, const destroy_binary_set_fn destroy) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");

    for (size_t i = 0; destroy && i < set->size; ++i) {
        destroy(set->elements + i);
    }
    set->compare = NULL;
    set->size = 0;
}

static inline bool contains_binary_set(const binary_set_s set, const BINARY_SET_DATA_TYPE element) {
    if (set.compare) {
        return (bool) bsearch(&element, set.elements, set.size, sizeof(BINARY_SET_DATA_TYPE), set.compare);
    }

    const BINARY_SET_DATA_TYPE * decay = set.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t limit = set.size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int cmp = set.compare ? set.compare(&element, current_element) : memcmp(&element, current_element, sizeof(BINARY_SET_DATA_TYPE));
        if (cmp == 0) {
            return true;
        }
        if (cmp > 0) {
            base = current_element + 1; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

static inline void add_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set->size <= PREPROCESSOR_BINARY_SET_SIZE && "[ERROR] Set is full.");

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int cmp = set->compare ? set->compare(&element, current_element) : memcmp(&element, current_element, sizeof(BINARY_SET_DATA_TYPE));
        if (cmp == 0) {
            BINARY_SET_ASSERT(set->elements && "[ERROR] Set already contains element.");
            exit(EXIT_FAILURE);
        }
        if (cmp > 0) {
            base = current_element + 1;
            limit--;
        }
    }

    memmove(base + 1, base, (set->size - (base - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));
    memcpy(base, &element, sizeof(BINARY_SET_DATA_TYPE));
    set->size++;
}

static inline BINARY_SET_DATA_TYPE remove_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
        const int comparison = set->compare ? set->compare(current_element, &element) : memcmp(current_element, &element, sizeof(BINARY_SET_DATA_TYPE));
        if (comparison == 0) {
            BINARY_SET_DATA_TYPE temp = *current_element;
            --set->size;
            memmove(current_element, current_element + 1, (set->size - (current_element - set->elements)) * sizeof(BINARY_SET_DATA_TYPE));

            return temp;
        }
        if (comparison > 0) {
            base = current_element + 1;
            limit--;
        }
    }
    BINARY_SET_ASSERT(set->elements && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE);
}

static inline binary_set_s union_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    binary_set_s set = { .compare = set_one.compare, .size = set_one.size, };
    memcpy(set.elements, set_one.elements, set_one.size * sizeof(BINARY_SET_DATA_TYPE));

    BINARY_SET_DATA_TYPE * base = set.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set.size - (base - set.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            BINARY_SET_ASSERT(set.size <= PREPROCESSOR_BINARY_SET_SIZE && "[ERROR] Set is full.");
            memmove(base + 1, base, (set.size - (base - set.elements)) * sizeof(BINARY_SET_DATA_TYPE));
            *base = set_two.elements[i];
            set.size++;
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s intersect_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't intersect sets with different compare functions.");

    binary_set_s set = { .compare = set_one.compare, .size = set_one.size, };

    const BINARY_SET_DATA_TYPE * decay = set_one.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set.compare ? set.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                BINARY_SET_ASSERT(set.size <= PREPROCESSOR_BINARY_SET_SIZE && "[ERROR] Set is full.");
                set.elements[set.size++] = set_two.elements[i];
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s subtract_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't subtract sets with different compare functions.");

    binary_set_s set = { .compare = set_one.compare, .size = set_one.size, };

    const BINARY_SET_DATA_TYPE * decay = set_two.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(set_one.elements + i, current_element) : memcmp(set_one.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            BINARY_SET_ASSERT(set.size <= PREPROCESSOR_BINARY_SET_SIZE && "[ERROR] Set is full.");
            set.elements[set.size++] = set_one.elements[i]; // push set to new point
        }
    }

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline binary_set_s exclude_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't exclude sets with different compare functions.");

    // special case since we can't tell if exclude can fit all elements before adding them since exclude both adds and removes elements in new set
    struct array {
        BINARY_SET_DATA_TYPE elements[PREPROCESSOR_BINARY_SET_SIZE * 2];
        size_t size;
        compare_binary_set_fn compare;
    } extended = { .size = set_one.size, .compare = set_one.compare };
    BINARY_SET_DATA_TYPE extended_elements[PREPROCESSOR_BINARY_SET_SIZE * 2];

    BINARY_SET_DATA_TYPE * base = extended.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = extended.size - (base - extended.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = extended.compare ? extended.compare(set_two.elements + i, current_element) : memcmp(set_two.elements + i, current_element, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                extended.size--;
                memmove(current_element, current_element + 1, (extended.size - (current_element - extended.elements)) * sizeof(BINARY_SET_DATA_TYPE)); // shift left if in both
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            // shift current element + rest to the right to make space for uncontained element
            memmove(base + 1, base, (extended.size - (base - extended.elements)) * sizeof(BINARY_SET_DATA_TYPE));

            *base = set_two.elements[i]; // push set to new point
            extended.size++;
        }
    }

    binary_set_s set = { .compare = extended.compare, .size = extended.size, };
    BINARY_SET_ASSERT(extended.size <= PREPROCESSOR_BINARY_SET_SIZE && "[ERROR] Set is full.");
    memcpy(set.elements, extended_elements, sizeof(BINARY_SET_DATA_TYPE) * extended.size);

    for (size_t i = 0; copy && i < set.size; ++i) {
        set.elements[i] = copy(set.elements[i]);
    }

    return set;
}

static inline bool is_subset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check subset with different compare functions.");

    const BINARY_SET_DATA_TYPE * decay = set_two.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_subset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check proper subset with different compare functions.");

    const BINARY_SET_DATA_TYPE * decay = set_two.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        bool found_element = false;
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true && (set_one.size != set_two.size);
}

static inline bool is_superset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check superset with different compare functions.");

    const BINARY_SET_DATA_TYPE * decay = set_one.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(current_element, set_two.elements + i) : memcmp(current_element, set_two.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_superset_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check proper superset with different compare functions.");

    const BINARY_SET_DATA_TYPE * decay = set_one.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;
        for (size_t limit = set_one.size - (base - set_one.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_two.compare ? set_two.compare(current_element, set_two.elements + i) : memcmp(current_element, set_two.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                found_element = true;
                break;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
        if (!found_element) {
            return false;
        }
    }

    return true && (set_one.size != set_two.size);
}

static inline bool is_disjoint_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check disjoint with different compare functions.");

    const BINARY_SET_DATA_TYPE * decay = set_two.elements;
    BINARY_SET_DATA_TYPE * base = NULL;
    memcpy(&base, &decay, sizeof(BINARY_SET_DATA_TYPE *));
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        for (size_t limit = set_two.size - (base - set_two.elements); limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);
            const int comparison = set_one.compare ? set_one.compare(current_element, set_one.elements + i) : memcmp(current_element, set_one.elements + i, sizeof(BINARY_SET_DATA_TYPE));
            if (comparison == 0) {
                return false;
            }
            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
    }

    return true;
}

static inline binary_set_s copy_binary_set(const binary_set_s set, const copy_binary_set_fn copy) {
    binary_set_s set_copy = {
        .compare = set.compare, .size = set.size,
    };
    BINARY_SET_ASSERT(set_copy.elements && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t i = 0; i < set_copy.size; ++i) {
            set_copy.elements[i] = copy(set.elements[i]);
        }
    } else {
        memcpy(set_copy.elements, set.elements, sizeof(BINARY_SET_DATA_TYPE) * set.size);
    }

    return set_copy;
}

static inline bool is_empty_binary_set(const binary_set_s set) {
    return !(set.size);
}

static inline bool is_full_binary_set(const binary_set_s set) {
    return !(set.size < PREPROCESSOR_BINARY_SET_SIZE && ~set.size);
}

static inline void foreach_binary_set(binary_set_s * set, const operate_binary_set_fn operate, void * args) {
    for (size_t i = 0; i < set->size; ++i) {
        if (!operate(set->elements + i, args)) return;
    }
}

#endif

#endif // BINARY_SET_H
