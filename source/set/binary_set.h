#ifndef BINARY_SET_H
#define BINARY_SET_H

// SOURCE AND LICENCE OF BINARY SEARCH IMPLEMENTATION
// https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
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

/*
    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <https://unlicense.org>
*/

#include <stddef.h>  // imports size_t
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy, memmove
#include <stdlib.h>  // imports exit

#ifndef BINARY_SET_DATA_TYPE
/// @brief To change, use: #define BINARY_SET_DATA_TYPE [type].
#   define BINARY_SET_DATA_TYPE void*
#endif

#ifndef BINARY_SET_ASSERT
#   include <assert.h>  // imports assert for debugging
/// @brief To change, use: #define BINARY_SET_ASSERT [assert].
#   define BINARY_SET_ASSERT assert
#endif

#if !defined(BINARY_SET_ALLOC) && !defined(BINARY_SET_FREE)
#   include <stdlib.h>
#   define BINARY_SET_ALLOC malloc
#   define BINARY_SET_FREE free
#elif !defined(BINARY_SET_ALLOC)
#   error Must also define BINARY_SET_ALLOC.
#elif !defined(BINARY_SET_FREE)
#   error Must also define BINARY_SET_FREE.
#endif

#ifndef BINARY_SET_SIZE
#   define BINARY_SET_SIZE (1 << 10)
#elif BINARY_SET_SIZE <= 0
#   error 'BINARY_SET_SIZE' cannot be zero
#endif

/// @brief Function pointer to create a deep/shallow copy for binary set element.
typedef BINARY_SET_DATA_TYPE (*copy_binary_set_fn)    (const BINARY_SET_DATA_TYPE element);
/// @brief Function pointer to destroy/free an element for binary set element.
typedef void                 (*destroy_binary_set_fn) (BINARY_SET_DATA_TYPE * element);
/// @brief Function pointer to compare two set elements. Returns zero if they're equal, a negative number if
/// 'less than', else a positive number if 'more than'.
typedef int                  (*compare_binary_set_fn) (const BINARY_SET_DATA_TYPE one, const BINARY_SET_DATA_TYPE two);
/// @brief Function pointer to operate on a single set element based on generic arguments.
typedef bool                 (*operate_binary_set_fn) (BINARY_SET_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of set elements based on generic arguments.
typedef void                 (*manage_binary_set_fn)  (BINARY_SET_DATA_TYPE * array, const size_t size, void * args);

typedef struct binary_set {
    BINARY_SET_DATA_TYPE * elements; // array of elements sorted based on compare
    compare_binary_set_fn compare; // compare function pointer to sort elements by
    size_t size; // number of elements in set
} binary_set_s;

/// @brief Creates and returns a set with compare function pointer.
/// @param compare Function pointer to compare elements to sort the set.
/// @return Newly created set.
static inline binary_set_s create_binary_set(const compare_binary_set_fn compare) {
    BINARY_SET_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");

    const binary_set_s set = {
        .elements = BINARY_SET_ALLOC(BINARY_SET_SIZE * sizeof(BINARY_SET_DATA_TYPE)),
        .compare = compare, .size = 0,
    };
    BINARY_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");

    return set;
}

/// @brief Destroys the set and all its elements.
/// @param set Set to destroy together with its elements.
/// @param destroy Function pointer to destroy each element in set.
static inline void destroy_binary_set(binary_set_s * set, const destroy_binary_set_fn destroy) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL");
    BINARY_SET_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL");

    BINARY_SET_ASSERT(set->compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set->size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set->elements && "[ERROR] 'elements' pointer is NULL.");

    for (BINARY_SET_DATA_TYPE * e = set->elements; e < set->elements + set->size; e++) {
        destroy(e);
    }

    set->compare = NULL;
    set->size = 0;
    BINARY_SET_FREE(set->elements);
}

/// @brief Clears the set and all its elements.
/// @param set Set to destroy together with its elements.
/// @param destroy Function pointer to destroy each element in set.
static inline void clear_binary_set(binary_set_s * set, const destroy_binary_set_fn destroy) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL");
    BINARY_SET_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL");

    BINARY_SET_ASSERT(set->compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set->size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set->elements && "[ERROR] 'elements' pointer is NULL.");

    for (BINARY_SET_DATA_TYPE * e = set->elements; e < set->elements + set->size; e++) {
        destroy(e);
    }

    set->size = 0;
}

/// @brief Creates a deep or shallow copy of a set depending on function pointer parameter.
/// @param set Set to copy together with its elements.
/// @param copy Function pointer to create a deep or shallow copy of each element in set.
/// @return Copy of set parameter.
static inline binary_set_s copy_binary_set(const binary_set_s set, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");

    BINARY_SET_ASSERT(set.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");

    binary_set_s replica = {
        .elements = BINARY_SET_ALLOC(BINARY_SET_SIZE * sizeof(BINARY_SET_DATA_TYPE)),
        .compare = set.compare, .size = 0,
    };
    BINARY_SET_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");

    for (replica.size = 0; replica.size < set.size; replica.size++) {
        replica.elements[replica.size] = copy(set.elements[replica.size]);
    }

    return replica;
}

/// @brief Checks if set is empty.
/// @param set Set to check.
/// @return 'true' if set is empty, 'false' otherwise.
static inline bool is_empty_binary_set(const binary_set_s set) {
    BINARY_SET_ASSERT(set.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");

    return !(set.size);
}

/// @brief Checks if set is full.
/// @param set Set to check.
/// @return 'true' if set is full, 'false' otherwise.
static inline bool is_full_binary_set(const binary_set_s set) {
    BINARY_SET_ASSERT(set.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");

    return (set.size == BINARY_SET_SIZE);
}

/// @brief Iterates over each element in set calling operate function on it using generic arguments.
/// @param set Set to iterate over.
/// @param operate Function pointer to call on each element reference using generic arguments.
/// @param args Generic void pointer arguments used in 'operate' function.
static inline void foreach_binary_set(const binary_set_s set, const operate_binary_set_fn operate, void * args) {
    BINARY_SET_ASSERT(operate && "[ERROR] 'operate' pointer parameter is NULL.");

    BINARY_SET_ASSERT(set.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");

    for (size_t i = 0; i < set.size && operate(set.elements + i, args); ++i) {}
}

/// @brief Maps elements in set into array and calls manage function on it using set's size and generic arguments.
/// @param set Set to map elements into array.
/// @param manage Function pointer to call on all elements as array using set's size and generic arguments.
/// @param args Generic void pointer arguments used in 'manage' function.
static inline void map_binary_set(const binary_set_s set, const manage_binary_set_fn manage, void * args) {
    BINARY_SET_ASSERT(manage && "[ERROR] 'manage' pointer parameter is NULL.");

    BINARY_SET_ASSERT(set.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");

    manage(set.elements, set.size, args);
}

/// @brief Checks if set contains the specified element.
/// @param set Set structure to check.
/// @param element Element to check if contained in set.
/// @return 'true' if element is contained in set, 'false' if not.
static inline bool contains_binary_set(const binary_set_s set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_DATA_TYPE const * base = set.elements;
    for (size_t limit = set.size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE const * current_element = base + (limit >> 1);

        const int comparison = set.compare(element, (*current_element));
        if (comparison == 0) {
            return true;
        }

        if (comparison > 0) {
            base = current_element + 1; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

/// @brief Adds specified element to the set.
/// @param set Set to add element into.
/// @param element Element to add into set.
/// @note If element is contained in set the function terminates with error.
static inline void insert_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set->size < BINARY_SET_SIZE && "[ERROR] Set is full.");

    BINARY_SET_ASSERT(set->compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set->size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set->elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);

        const int comparison = set->compare(element, (*current_element));
        if (comparison == 0) {
            BINARY_SET_ASSERT(false && "[ERROR] Set already contains element.");
        }

        if (comparison > 0) {
            base = current_element + 1;
            limit--;
        }
    }

    const size_t base_index = (size_t)(base - set->elements); // convert to size_t since the result is a positive ptrdiff_t
    memmove(base + 1, base, (set->size - base_index) * sizeof(BINARY_SET_DATA_TYPE));
    memcpy(base, &element, sizeof(BINARY_SET_DATA_TYPE));
    set->size++;
}

/// @brief Remove specified element from set.
/// @param set Set to remove element from.
/// @param element Element to remove from set.
/// @note If element is not contained in set the function terminates with an error.
/// @return Removed element.
static inline BINARY_SET_DATA_TYPE remove_binary_set(binary_set_s * set, const BINARY_SET_DATA_TYPE element) {
    BINARY_SET_ASSERT(set && "[ERROR] 'set' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");

    BINARY_SET_ASSERT(set->compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set->size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set->elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_DATA_TYPE * base = set->elements;
    for (size_t limit = set->size; limit != 0; limit >>= 1) {
        BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);

        const int comparison = set->compare(element, (*current_element));
        if (comparison == 0) {
            BINARY_SET_DATA_TYPE removed = (*current_element);
            set->size--;

            const size_t current_index = (size_t)(current_element - set->elements); // convert to size_t since the result is a positive ptrdiff_t
            memmove(current_element, current_element + 1, (set->size - current_index) * sizeof(BINARY_SET_DATA_TYPE));

            return removed;
        }

        if (comparison > 0) {
            base = current_element + 1;
            limit--;
        }
    }

    BINARY_SET_ASSERT(false && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE); // to have function return
}

/// @brief Creates and returns a union of two sets whose elements are copied into the new set.
/// @param set_one First set structure to unite.
/// @param set_two Second set structure to unite.
/// @param copy Function pointer that creates deep or shallow a copy for united elements.
/// @return New union of set parameters.
static inline binary_set_s union_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_ASSERT(set_one.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_one.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_ASSERT(set_two.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_two.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");

    binary_set_s set_union = {
        .elements = BINARY_SET_ALLOC(BINARY_SET_SIZE * sizeof(BINARY_SET_DATA_TYPE)),
        .compare = set_one.compare, .size = 0,
    };
    BINARY_SET_ASSERT(set_union.elements && "[ERROR] Memory allocation failed.");

    // copy set one's elements into union set
    for (set_union.size = 0; set_union.size < set_one.size; set_union.size++) {
        set_union.elements[set_union.size] = copy(set_one.elements[set_union.size]);
    }

    // copy set two's elements which are not in set one into union set
    BINARY_SET_DATA_TYPE * base = set_union.elements;
    for (size_t i = 0; i < set_two.size; ++i) {
        bool found_element = false;

        const size_t base_index = (size_t)(base - set_union.elements); // convert to size_t since the result is a positive ptrdiff_t
        for (size_t limit = set_union.size - base_index; limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);

            const int comparison = set_union.compare(set_two.elements[i], (*current_element));
            if (comparison == 0) {
                found_element = true;
                break;
            }

            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }

        if (!found_element) { // if set two's element was not found then push copy into set
            BINARY_SET_ASSERT(set_union.size <= BINARY_SET_SIZE && "[ERROR] Set's size above maximum");

            const size_t found_base_index = (size_t)(base - set_union.elements); // convert to size_t since the result is a positive ptrdiff_t
            memmove(base + 1, base, (set_union.size - found_base_index) * sizeof(BINARY_SET_DATA_TYPE));
            (*base) = copy(set_two.elements[i]);
            set_union.size++;
        }
    }

    return set_union;
}

/// @brief Creates and returns an intersect of two sets whose elements are copied into the new set.
/// @param set_one First set structure to intersect.
/// @param set_two Second set structure to intersect.
/// @param copy Function pointer that creates deep or shallow a copy for intersected elements.
/// @return New intersect of set parameters.
static inline binary_set_s intersect_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_ASSERT(set_one.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_one.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_ASSERT(set_two.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_two.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");

    binary_set_s set_intersect = {
        .elements = BINARY_SET_ALLOC(BINARY_SET_SIZE * sizeof(BINARY_SET_DATA_TYPE)),
        .compare = set_one.compare, .size = 0,
    };
    BINARY_SET_ASSERT(set_intersect.elements && "[ERROR] Memory allocation failed.");

    BINARY_SET_DATA_TYPE const * base = set_one.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        const size_t base_index = (size_t)(base - set_one.elements); // convert to size_t since the result is a positive ptrdiff_t
        for (size_t limit = set_one.size - base_index; limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE const * current_element = base + (limit >> 1);

            const int comparison = set_intersect.compare(set_two.elements[i], (*current_element));
            if (comparison == 0) {
                set_intersect.elements[set_intersect.size++] = copy((*current_element));
                break;
            }

            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }
    }

    return set_intersect;
}

/// @brief Creates and returns a subtraction of two sets whose elements are copied into the new set.
/// @param set_one First set structure that gets subtracted.
/// @param set_two Second set structure that subtracts.
/// @param copy Function pointer that creates deep or shallow a copy for subtracted elements.
/// @return New subtraction of set parameters.
static inline binary_set_s subtract_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_ASSERT(set_one.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_one.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_ASSERT(set_two.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_two.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");

    binary_set_s set_subtract = {
        .elements = BINARY_SET_ALLOC(BINARY_SET_SIZE * sizeof(BINARY_SET_DATA_TYPE)),
        .compare = set_one.compare, .size = 0,
    };
    BINARY_SET_ASSERT(set_subtract.elements && "[ERROR] Memory allocation failed.");

    BINARY_SET_DATA_TYPE const * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set two
        bool found_element = false;

        const size_t base_index = (size_t)(base - set_two.elements); // convert to size_t since the result is a positive ptrdiff_t
        for (size_t limit = set_two.size - base_index; limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE const * current_element = base + (limit >> 1);

            const int comparison = set_two.compare(set_one.elements[i], (*current_element));
            if (comparison == 0) {
                found_element = true;
                break;
            }

            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }

        if (!found_element) { // if one's element was not found in two push it to new set (one does not contain elements in set two)
            set_subtract.elements[(set_subtract.size)++] = copy(set_one.elements[i]); // push set to new point
        }
    }

    return set_subtract;
}

/// @brief Creates and returns an exclude (symmetric difference) of two sets whose elements are copied into the new set.
/// @param set_one First set structure to exclude.
/// @param set_two Second set structure to exclude.
/// @param copy Function pointer that creates deep or shallow a copy for exclude elements.
/// @return New exclude of set parameters.
static inline binary_set_s exclude_binary_set(const binary_set_s set_one, const binary_set_s set_two, const copy_binary_set_fn copy) {
    BINARY_SET_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't union sets with different compare functions.");

    BINARY_SET_ASSERT(set_one.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_one.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_ASSERT(set_two.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_two.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");

    // special case since we can't tell if exclude can fit all elements before adding them since exclude both adds and removes elements in new set
    struct array { BINARY_SET_DATA_TYPE elements[BINARY_SET_SIZE * 2]; size_t size; } extended = { .size = 0, };
    // shallow copy set one's elements into union set
    for (extended.size = 0; extended.size < set_one.size; extended.size++) {
        extended.elements[extended.size] = set_one.elements[extended.size]; // make a shallow copy since some elements may be removed
    }

    BINARY_SET_DATA_TYPE * base = extended.elements;
    for (size_t i = 0; i < set_two.size; ++i) { // for each element in set two
        bool found_element = false;

        const size_t base_index = (size_t)(base - extended.elements); // convert to size_t since the result is a positive ptrdiff_t
        for (size_t limit = extended.size - base_index; limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE * current_element = base + (limit >> 1);

            const int comparison = set_one.compare(set_two.elements[i], (*current_element));
            if (comparison == 0) { // if equal shift left to remove
                extended.size--;
                const size_t current_index = (size_t)(current_element - extended.elements); // convert to size_t since the result is a positive ptrdiff_t
                memmove(current_element, current_element + 1, (extended.size - current_index) * sizeof(BINARY_SET_DATA_TYPE));

                found_element = true;
                break;
            }

            if (comparison > 0) {
                base = current_element + 1; // increment element pointer to next
                limit--;
            }
        }

        if (!found_element) { // if not found shift current element + rest to the right to make space for uncontained element
            const size_t found_base_index = (size_t)(base - extended.elements); // convert to size_t since the result is a positive ptrdiff_t
            memmove(base + 1, base, (extended.size - found_base_index) * sizeof(BINARY_SET_DATA_TYPE));

            (*base) = set_two.elements[i]; // push set to new point
            extended.size++;
        }
    }
    BINARY_SET_ASSERT(extended.size <= BINARY_SET_SIZE && "[ERROR] Set exceeds maximum rpeprocessor size.");

    const binary_set_s exclude_set = {
        .elements = BINARY_SET_ALLOC(BINARY_SET_SIZE * sizeof(BINARY_SET_DATA_TYPE)),
        .compare = set_one.compare, .size = extended.size,
    };
    BINARY_SET_ASSERT(exclude_set.elements && "[ERROR] Memory allocation failed.");

    memcpy(exclude_set.elements, extended.elements, sizeof(BINARY_SET_DATA_TYPE) * extended.size);

    for (size_t i = 0; i < exclude_set.size; ++i) {
        exclude_set.elements[i] = copy(exclude_set.elements[i]);
    }

    return exclude_set;
}

/// @brief Checks if sub is subset of super (sub <= super).
/// @param super Superset to check on.
/// @param sub Subset to check with superset.
/// @return 'true' if sub is subset of superset, 'false' if not.
static inline bool is_subset_binary_set(const binary_set_s super, const binary_set_s sub) {
    BINARY_SET_ASSERT(super.compare == sub.compare && "[ERROR] Can't check subset with different compare functions.");

    BINARY_SET_ASSERT(super.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(super.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(super.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_ASSERT(sub.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(sub.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(sub.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_DATA_TYPE const * base = super.elements;
    for (size_t i = 0; i < sub.size; ++i) { // for each element in set one
        bool found_element = false;

        const size_t base_index = (size_t)(base - super.elements); // convert to size_t since the result is a positive ptrdiff_t
        for (size_t limit = super.size - base_index; limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE const * current_element = base + (limit >> 1);

            const int comparison = super.compare(sub.elements[i], (*current_element));
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

/// @brief Checks if sub is proper subset of super (sub < super).
/// @param super Superset to check on.
/// @param sub Subset to check with superset.
/// @return 'true' if sub is proper subset of superset, 'false' if not.
static inline bool is_proper_subset_binary_set(const binary_set_s super, const binary_set_s sub) {
    BINARY_SET_ASSERT(super.compare == sub.compare && "[ERROR] Can't check proper subset with different compare functions.");

    BINARY_SET_ASSERT(super.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(super.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(super.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_ASSERT(sub.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(sub.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(sub.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_DATA_TYPE const * base = super.elements;
    for (size_t i = 0; i < sub.size; ++i) { // for each element in set one
        bool found_element = false;

        const size_t base_index = (size_t)(base - super.elements); // convert to size_t since the result is a positive ptrdiff_t
        for (size_t limit = super.size - base_index; limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE const * current_element = base + (limit >> 1);

            const int comparison = super.compare(sub.elements[i], (*current_element));
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

    return super.size != sub.size;
}

/// @brief Checks if two sets are disjoint or not, i.e. have no shared elements.
/// @param set_one First set to check.
/// @param set_two Second set to check.
/// @return 'true' if sets are disjoint, 'false' otherwise.
static inline bool is_disjoint_binary_set(const binary_set_s set_one, const binary_set_s set_two) {
    BINARY_SET_ASSERT(set_one.compare == set_two.compare && "[ERROR] Can't check disjoint with different compare functions.");

    BINARY_SET_ASSERT(set_one.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_one.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_ASSERT(set_two.compare && "[ERROR] Set's compare function pointer is NULL.");
    BINARY_SET_ASSERT(set_two.size <= BINARY_SET_SIZE && "[ERROR] Invalid set size.");
    BINARY_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");

    BINARY_SET_DATA_TYPE const * base = set_two.elements;
    for (size_t i = 0; i < set_one.size; ++i) { // for each element in set one
        const size_t base_index = (size_t)(base - set_two.elements); // convert to size_t since the result is a positive ptrdiff_t
        for (size_t limit = set_two.size - base_index; limit != 0; limit >>= 1) {
            BINARY_SET_DATA_TYPE const * current_element = base + (limit >> 1);

            const int comparison = set_one.compare(set_one.elements[i], (*current_element));
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

#else

#error Cannot include multiple headers in same unit.

#endif // BINARY_SET_H
