#ifndef BITWISE_SET_H
#define BITWISE_SET_H

#include <stddef.h>  // imports size_t
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy, memmove
#include <limits.h>  // imports CHAR_BIT
#include <stdint.h>  // imports SIZE_MAX

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

#define INFINITE_REALLOC_BITWISE_SET_MODE    2001
#define FINITE_ALLOCATED_BITWISE_SET_MODE    2002
#define FINITE_PRERPOCESSOR_BITWISE_SET_MODE 2003

//#define BITWISE_SET_MODE INFINITE_REALLOC_BITWISE_SET_MODE
//#define BITWISE_SET_MODE FINITE_ALLOCATED_BITWISE_SET_MODE
//#define BITWISE_SET_MODE FINITE_PRERPOCESSOR_BITWISE_SET_MODE

#ifndef BITWISE_SET_MODE

/// @brief To change, use: #define BITWISE_SET_MODE [mode].
#define BITWISE_SET_MODE INFINITE_REALLOC_BITWISE_SET_MODE

#endif

// Check to make sure a valid double_list mode is selected.
#if (BITWISE_SET_MODE != INFINITE_REALLOC_BITWISE_SET_MODE) && (BITWISE_SET_MODE != FINITE_ALLOCATED_BITWISE_SET_MODE) && \
    (BITWISE_SET_MODE != FINITE_PRERPOCESSOR_BITWISE_SET_MODE)

#error Invalid type of list mode.

#endif

#ifndef BITWISE_SET_DATA_TYPE

/// @brief To change, use: #define BITWISE_SET_DATA_TYPE [type].
#define BITWISE_SET_DATA_TYPE void*

#endif

#ifndef BITWISE_SET_TYPE

/// @brief To change, use: #define BITWISE_SET_TYPE [type].
#define BITWISE_SET_TYPE size_t

#endif

#ifndef BITWISE_SET_ASSERT

#include <assert.h>  // imports assert for debugging

/// @brief To change, use: #define BITWISE_SET_ASSERT [assert].
#define BITWISE_SET_ASSERT assert

#endif

#if BITWISE_SET_MODE != FINITE_PRERPOCESSOR_BITWISE_SET_MODE

#if !defined(BITWISE_SET_REALLOC) && !defined(BITWISE_SET_FREE)

#include <stdlib.h>

#ifndef BITWISE_SET_REALLOC

#define BITWISE_SET_REALLOC realloc

#endif

#ifndef BITWISE_SET_FREE

#define BITWISE_SET_FREE free

#endif

#elif !defined(BITWISE_SET_REALLOC)

#error Reallocator macro is not defined!

#elif !defined(BITWISE_SET_FREE)

#error Free macro is not defined!

#endif

#endif

/// @brief Function pointer to operate on a single set element based on generic arguments.
typedef bool                  (*operate_bitwise_set_fn) (BITWISE_SET_DATA_TYPE *, void *);

#if BITWISE_SET_MODE == INFINITE_REALLOC_BITWISE_SET_MODE

typedef struct bitwise_set {
    size_t size, capacity;
    BITWISE_SET_TYPE * bits;
} bitwise_set_s;

static inline bitwise_set_s create_bitwise_set(void) {
    return (bitwise_set_s) { 0 };
}

static inline void destroy_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_FREE(set->bits);
    (*set) = (bitwise_set_s) { 0 };
}

static inline void clear_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_FREE(set->bits);
    (*set) = (bitwise_set_s) { 0 };
}

static inline bitwise_set_s copy_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    const bitwise_set_s replica =  {
        .bits = BITWISE_SET_REALLOC(NULL, set.capacity * sizeof(BITWISE_SET_TYPE)),
        .capacity = set.capacity, .size = set.size,
    };
    BITWISE_SET_ASSERT(replica.bits && "[ERROR] Memory allocation failed.");

    memcpy(replica.bits, set.bits, set.capacity * sizeof(BITWISE_SET_TYPE));

    return replica;
}

static inline bool is_empty_bitwise_set(const bitwise_set_s set) {
    return !(set.size);
}

static inline bool is_full_bitwise_set(const bitwise_set_s set) {
    return !(~(set.size));
}

static inline void foreach_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE * universe, const operate_bitwise_set_fn operate, void * args) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");
    BITWISE_SET_ASSERT(universe && "[ERROR] 'universe' parameter is NULL.");

#if (defined(__GNUC__) || (defined(__clang__) && __has_builtin(__builtin_clz))) && (SIZE_MAX <= ULLONG_MAX)
    for (size_t i = 0; i < set->capacity; ++i) {
        BITWISE_SET_TYPE current = set->bits[i];

        while (current) { // while current is not zero
            const int trailing = __builtin_ctzll((unsigned long long)current); // get typecast trailing zeros index
            if (!operate(universe + (trailing + 1), args)) { // operate on element left to last trailing zero in universe
                return;
            }

            current ^= (1 << trailing); // remove bit at left of trailing zeros
        }
    }
#else
    // sizeof returns number of chars a value can store, thus multiplying by CHAR_BIT gets the bit count
    const size_t bit_count = sizeof(BITWISE_SET_TYPE) * CHAR_BIT;
    for (size_t i = 0; i < set->capacity; ++i) {
        for (size_t j = 0; j < bit_count; j <<= 1) {
            if (((size_t)1 << j) & set->bits[i] && !operate(universe + (j + (i * bit_count)), args)) {
                return;
            }
        }
    }
#endif
}

static inline bool contains_bitwise_set(const bitwise_set_s set, const size_t index) {
    const size_t type_index = index / (sizeof(BITWISE_SET_TYPE) * CHAR_BIT);
    const size_t true_index = index % (sizeof(BITWISE_SET_TYPE) * CHAR_BIT);
    const size_t element_bit = (size_t)(1) << ((sizeof(BITWISE_SET_TYPE) * CHAR_BIT) - true_index - 1);

    return (type_index < set.capacity) ? (bool)(set.bits[type_index] & element_bit) : false;
}

static inline void insert_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT((~(set->size)) && "[ERROR] Set size will overflow.");

    const size_t type_index = index / (sizeof(BITWISE_SET_TYPE) * CHAR_BIT);
    const size_t true_index = index % (sizeof(BITWISE_SET_TYPE) * CHAR_BIT);
    const size_t element_bit = (size_t)(1) << ((sizeof(BITWISE_SET_TYPE) * CHAR_BIT) - true_index - 1);

    if (type_index < set->capacity) { // if index in bits array is less than capacity just add the element
        BITWISE_SET_ASSERT(!(set->bits[type_index] & element_bit) && "[ERROR] Set already contains element.");
        set->bits[type_index] |= element_bit;
    } else { // else the bits array must be expanded to index in bits + 1
        set->bits = BITWISE_SET_REALLOC(set->bits, sizeof(BITWISE_SET_TYPE) * (type_index + 1));
        BITWISE_SET_ASSERT(set->bits && "[ERROR] Memory allocation failed.");

        for (size_t i = set->capacity; i < type_index + 1; ++i) { // initialize next added bits to zero
            set->bits[i] = 0;
        }

        set->bits[type_index] |= element_bit;
    }

    set->size++;
}

static inline void remove_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");
    BITWISE_SET_ASSERT(set->capacity && "[ERROR] Can't remove from empty set.");
    BITWISE_SET_ASSERT(set->bits && "[ERROR] Can't remove from empty set.");

    const size_t type_index = index / (sizeof(BITWISE_SET_TYPE) * CHAR_BIT);
    const size_t true_index = index % (sizeof(BITWISE_SET_TYPE) * CHAR_BIT);
    const size_t element_bit = (size_t)(1) << ((sizeof(BITWISE_SET_TYPE) * CHAR_BIT) - true_index - 1);

    BITWISE_SET_ASSERT(type_index < set->capacity && "[ERROR] Can't remove index exceeding capacity.");

    BITWISE_SET_ASSERT((set->bits[type_index] & element_bit) && "[ERROR] Set does not contain element.");
    set->bits[type_index] ^= element_bit;

    size_t trailing_empty_count = 0;
    while (trailing_empty_count < set->capacity && set->bits[set->capacity - trailing_empty_count - 1]) {
        trailing_empty_count++;
    }

    const size_t new_capacity = set->capacity - trailing_empty_count;
    if (new_capacity) {
        set->bits = BITWISE_SET_REALLOC(set->bits, new_capacity * sizeof(BITWISE_SET_TYPE));
    } else {
        BITWISE_SET_FREE(set->bits);
        set->bits = NULL;
    }

    set->size--;
}

static inline bitwise_set_s union_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    const bitwise_set_s smaller = set_one.capacity < set_two.capacity ? set_one : set_two;
    const bitwise_set_s larger = set_one.capacity > set_two.capacity ? set_one : set_two;

    if (!larger.capacity) { // early return if larger set is empty
        return (bitwise_set_s) { 0 };
    }

    bitwise_set_s union_set = {
        .bits = BITWISE_SET_REALLOC(NULL, larger.capacity * sizeof(BITWISE_SET_DATA_TYPE)),
        .size = 0, .capacity = larger.capacity,
    };

    for (size_t i = 0; i < smaller.capacity; ++i) {
        union_set.bits[i] = 0;
        union_set.bits[i] = set_one.bits[i] | set_two.bits[i];

#if (defined(__GNUC__) || (defined(__clang__) && __has_builtin(__builtin_popcount))) && (SIZE_MAX <= ULLONG_MAX)
        union_set.size += __builtin_popcountll((unsigned long long)union_set.bits[i]);
#else
        const BITWISE_SET_DATA_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
#endif
    }

    for (size_t i = smaller.capacity; i < larger.capacity; ++i) {
        union_set.bits[i] = larger.bits[i];

#if (defined(__GNUC__) || (defined(__clang__) && __has_builtin(__builtin_popcount))) && (SIZE_MAX <= ULLONG_MAX)
        union_set.size += __builtin_popcountll((unsigned long long)union_set.bits[i]);
#else
        const BITWISE_SET_DATA_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
#endif
    }

    return union_set;
}

static inline bitwise_set_s intersect_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    const bitwise_set_s smaller = set_one.capacity < set_two.capacity ? set_one : set_two;
    const bitwise_set_s larger = set_one.capacity > set_two.capacity ? set_one : set_two;

    if (!smaller.capacity) { // early return if larger set is empty
        return (bitwise_set_s) { 0 };
    }

    bitwise_set_s intersect_set = {
        .bits = BITWISE_SET_REALLOC(NULL, smaller.capacity * sizeof(BITWISE_SET_DATA_TYPE)),
        .size = 0, .capacity = smaller.capacity,
    };

    for (size_t i = 0; i < smaller.capacity; ++i) {
        intersect_set.bits[i] = 0;
        intersect_set.bits[i] = set_one.bits[i] & set_two.bits[i];

#if (defined(__GNUC__) || (defined(__clang__) && __has_builtin(__builtin_popcount))) && (SIZE_MAX <= ULLONG_MAX)
        intersect_set.size += __builtin_popcountll((unsigned long long)intersect_set.bits[i]);
#else
        const BITWISE_SET_DATA_TYPE current = intersect_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            intersect_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
#endif
    }

    return intersect_set;
}

static inline bitwise_set_s subtract_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bitwise_set_s exclude_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bool is_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub)
static inline bool is_proper_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub)
static inline bool is_disjoint_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)

#elif BITWISE_SET_MODE == FINITE_ALLOCATED_BITWISE_SET_MODE

static inline bitwise_set_s create_bitwise_set(size_t max)
static inline void destroy_bitwise_set(bitwise_set_s * set)
static inline void clear_bitwise_set(bitwise_set_s * set)
static inline bitwise_set_s copy_bitwise_set(const bitwise_set_s set)
static inline bool is_empty_bitwise_set(const bitwise_set_s set)
static inline bool is_full_bitwise_set(const bitwise_set_s set)
static inline void foreach_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE * universe, const operate_bitwise_set_fn operate, void * args)
static inline void map_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE * universe, const manage_bitwise_set_fn manage, void * args)
static inline bool contains_bitwise_set(const bitwise_set_s set, const size_t index)
static inline void insert_bitwise_set(bitwise_set_s * set, const size_t index)
static inline void remove_bitwise_set(bitwise_set_s * set, const size_t index)
static inline bitwise_set_s union_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bitwise_set_s intersect_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bitwise_set_s subtract_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bitwise_set_s exclude_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bool is_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub)
static inline bool is_proper_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub)
static inline bool is_disjoint_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)

#elif BITWISE_SET_MODE == FINITE_PRERPOCESSOR_BITWISE_SET_MODE

static inline bitwise_set_s create_bitwise_set(void)
static inline void destroy_bitwise_set(bitwise_set_s * set)
static inline void clear_bitwise_set(bitwise_set_s * set)
static inline bitwise_set_s copy_bitwise_set(const bitwise_set_s set)
static inline bool is_empty_bitwise_set(const bitwise_set_s set)
static inline bool is_full_bitwise_set(const bitwise_set_s set)
static inline void foreach_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE * universe, const operate_bitwise_set_fn operate, void * args)
static inline void map_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE * universe, const manage_bitwise_set_fn manage, void * args)
static inline bool contains_bitwise_set(const bitwise_set_s set, const size_t index)
static inline void insert_bitwise_set(bitwise_set_s * set, const size_t index)
static inline void remove_bitwise_set(bitwise_set_s * set, const size_t index)
static inline bitwise_set_s union_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bitwise_set_s intersect_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bitwise_set_s subtract_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bitwise_set_s exclude_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)
static inline bool is_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub)
static inline bool is_proper_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub)
static inline bool is_disjoint_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two)

#endif

#else

#error Cannot include multiple headers in same unit.

#endif //BITWISE_SET_H
