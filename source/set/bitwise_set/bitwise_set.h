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

#define INFINITE_REALLOC_BITWISE_SET_MODE    2101
#define FINITE_ALLOCATED_BITWISE_SET_MODE    2102
#define FINITE_PRERPOCESSOR_BITWISE_SET_MODE 2103

//#define BITWISE_SET_MODE INFINITE_REALLOC_BITWISE_SET_MODE
//#define BITWISE_SET_MODE FINITE_ALLOCATED_BITWISE_SET_MODE
#define BITWISE_SET_MODE FINITE_PRERPOCESSOR_BITWISE_SET_MODE

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

#ifndef BITWISE_SET_BIT_TYPE

/// @brief To change, use: #define BITWISE_SET_BIT_TYPE [type].
#define BITWISE_SET_BIT_TYPE unsigned long long

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

#define BITWISE_SET_BIT_COUNT (sizeof(BITWISE_SET_BIT_TYPE) * CHAR_BIT)

// if either gcc or clang, and has __builtin_*ll support define POPCOUNT and CTZ
#if defined(__GNUC__) || defined(__clang__)

#define IS_BUILTIN_BITWISE_SET

#define TRAILING_BITWISE_SET(bits) ((size_t)__builtin_ctzll((unsigned long long)(bits)))

#define POPCOUNT_BITWISE_SET(bits) ((size_t)__builtin_popcountll((unsigned long long)(bits)))

#endif

/// @brief Function pointer to operate on a single set element based on generic arguments.
typedef bool                  (*operate_bitwise_set_fn) (BITWISE_SET_DATA_TYPE *, void *);

#if BITWISE_SET_MODE == INFINITE_REALLOC_BITWISE_SET_MODE

typedef struct bitwise_set {
    BITWISE_SET_BIT_TYPE * bits; // array of bits type or variables array where each can store a set number of bits
    size_t size, capacity; // size of set and current capacity to guarantee 'infinity'
} bitwise_set_s;

static inline bitwise_set_s create_bitwise_set(void) {
    return (bitwise_set_s) { 0 }; // just return a zero set set struct
}

static inline void destroy_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_FREE(set->bits); // destroy bits array
    (*set) = (bitwise_set_s) { 0 }; // zero set set struct
}

static inline void clear_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    // basically the same as destroy in this case
    BITWISE_SET_FREE(set->bits); // destroy bits array
    (*set) = (bitwise_set_s) { 0 }; // zero set set struct
}

static inline bitwise_set_s copy_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    const bitwise_set_s replica =  {
        // allocate memory if original set has capacity
        .bits = set.capacity ? BITWISE_SET_REALLOC(NULL, set.capacity * sizeof(BITWISE_SET_BIT_TYPE)) : NULL,
        .capacity = set.capacity, .size = set.size, // copy size and capacity
    };
    BITWISE_SET_ASSERT(replica.bits && "[ERROR] Memory allocation failed.");

    memcpy(replica.bits, set.bits, set.capacity * sizeof(BITWISE_SET_BIT_TYPE)); // copy set's bits into replica

    return replica;
}

static inline bool is_empty_bitwise_set(const bitwise_set_s set) {
    return !(set.size);
}

static inline bool is_full_bitwise_set(const bitwise_set_s set) {
    return !(~(set.size)); // if size will overflow then all bits are set to one, so just NOT it and check if it's zero
}

static inline void foreach_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE * universe, const operate_bitwise_set_fn operate, void * args) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");
    BITWISE_SET_ASSERT(universe && "[ERROR] 'universe' parameter is NULL.");

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < set->capacity; ++i) {
        BITWISE_SET_BIT_TYPE current = set->bits[i]; // save bit type to remove bits from after finding indexes

        // create a stack to operate over each element from left to right and not right to left
        // since only trailing or rightmost zeros can be count to make
        struct stack {
            size_t size;
            size_t elements[BITWISE_SET_BIT_COUNT];
        } stack = { .size = 0, };

        while (current) { // while current is not zero
            const size_t trailing = TRAILING_BITWISE_SET(current); // get typecast trailing zeros index
            stack.elements[stack.size++] = trailing + (i * BITWISE_SET_BIT_COUNT); // calculate universe index

            current ^= (1 << trailing); // remove bit at left of trailing zeros
        }

        while (stack.size) { // pop stack to get indexes in proper order
            if (!operate(universe + stack.elements[--stack.size], args)) { // operate on element left to last trailing zero in universe
                return;
            }
        }
    }
#else
    for (size_t i = 0; i < set->capacity; ++i) { // for each bit type
        for (size_t j = 0; j < BITWISE_SET_BIT_COUNT; ++j) {
            const size_t left = BITWISE_SET_BIT_COUNT - j - 1; // calculate left index of bit type
            const BITWISE_SET_BIT_TYPE bit = (BITWISE_SET_BIT_TYPE)(1) << left; // create single bit at left index

            // if single bit ANDS with bit type, and operate function halts then return, else continue
            if ((bit & set->bits[i]) && !operate(universe + (left + (i * BITWISE_SET_BIT_COUNT)), args)) {
                return;
            }
        }
    }
#endif
}

static inline bool contains_bitwise_set(const bitwise_set_s set, const size_t index) {
    BITWISE_SET_ASSERT(set.size && "[ERROR] Can't check from empty set.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    // if bit type index exceeds capacity the element's index is not contained, else check bits
    return (type_index < set.capacity) ? (bool)(set.bits[type_index] & element_bit) : false;
}

static inline void insert_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT((~(set->size)) && "[ERROR] Set size will overflow.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    if (type_index < set->capacity) { // if index in bits array is less than capacity just add the element
        BITWISE_SET_ASSERT(!(set->bits[type_index] & element_bit) && "[ERROR] Set already contains element.");
    } else { // else the bits array must be expanded to index in bits
        set->bits = BITWISE_SET_REALLOC(set->bits, sizeof(BITWISE_SET_BIT_TYPE) * (type_index + 1));
        BITWISE_SET_ASSERT(set->bits && "[ERROR] Memory allocation failed.");

        // initialize next added bits to zero
        memset(set->bits + set->capacity, 0, sizeof(BITWISE_SET_BIT_TYPE) * ((type_index + 1) - set->capacity));
    }

    set->bits[type_index] |= element_bit; // or-equal-add the bit index to set's bits

    set->size++;
}

static inline void remove_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");
    BITWISE_SET_ASSERT(set->capacity && "[ERROR] Can't remove from empty set.");
    BITWISE_SET_ASSERT(set->bits && "[ERROR] Can't remove from empty set.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    BITWISE_SET_ASSERT(type_index < set->capacity && "[ERROR] Can't remove index exceeding capacity.");

    BITWISE_SET_ASSERT((set->bits[type_index] & element_bit) && "[ERROR] Set does not contain element.");
    set->bits[type_index] ^= element_bit; // xor-equal-remove the bit index from set's bits

    size_t trailing = 0; // get trailing empty bits count
    for (; trailing < set->capacity && !(set->bits[set->capacity - trailing - 1]); trailing++) {}

    set->bits = BITWISE_SET_REALLOC(set->bits, sizeof(BITWISE_SET_BIT_TYPE) * (set->capacity - trailing));
    set->capacity -= trailing;

    if (!set->capacity) { // if set is empty free bits array and set capacity to zero
        BITWISE_SET_FREE(set->bits);
        set->bits = NULL;
    }

    set->size--;
}

static inline bitwise_set_s union_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    const bitwise_set_s smaller = set_one.capacity < set_two.capacity ? set_one : set_two;
    const bitwise_set_s larger = set_one.capacity > set_two.capacity ? set_one : set_two;

    if (!larger.capacity) { // early return if larger set is empty since union can't happen
        return (bitwise_set_s) { 0 };
    }

    bitwise_set_s union_set = { // create a union with allocated memory since early return returns an empty set
        .bits = BITWISE_SET_REALLOC(NULL, larger.capacity * sizeof(BITWISE_SET_BIT_TYPE)),
        .size = 0, .capacity = larger.capacity,
    };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < smaller.capacity; ++i) { // for each bits type use OR and popcount to count bits
        union_set.bits[i] = 0;
        union_set.bits[i] = set_one.bits[i] | set_two.bits[i];

        union_set.size += POPCOUNT_BITWISE_SET(union_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller.capacity; ++i) { // for each bits type use increment and remove to count bits
        union_set.bits[i] = set_one.bits[i] | set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = smaller.capacity; i < larger.capacity; ++i) { // simply copy the exceeding bits into union set
        union_set.bits[i] = larger.bits[i];
        union_set.size += POPCOUNT_BITWISE_SET(union_set.bits[i]);
    }
#else
    for (size_t i = smaller.capacity; i < larger.capacity; ++i) { // simply copy the exceeding bits into union set
        union_set.bits[i] = larger.bits[i];

        BITWISE_SET_BIT_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return union_set;
}

static inline bitwise_set_s intersect_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    const bitwise_set_s smaller = set_one.capacity < set_two.capacity ? set_one : set_two;

    if (!smaller.capacity) { // early return if smaller set is empty since intersect can't happen when too small
        return (bitwise_set_s) { 0 };
    }

    bitwise_set_s intersect_set = { // create an intersect with allocated memory since early return returns an empty set
        .bits = BITWISE_SET_REALLOC(NULL, smaller.capacity * sizeof(BITWISE_SET_BIT_TYPE)),
        .size = 0, .capacity = smaller.capacity,
    };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < smaller.capacity; ++i) { // for each bits type use AND and popcount to count bits
        intersect_set.bits[i] = set_one.bits[i] & set_two.bits[i];

        intersect_set.size += POPCOUNT_BITWISE_SET(intersect_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller.capacity; ++i) { // for each bits type use AND, then increment and remove to count bits
        intersect_set.bits[i] = set_one.bits[i] & set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = intersect_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            intersect_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    size_t trailing = 0; // get trailing empty bits count
    for (; trailing < intersect_set.capacity && !(intersect_set.bits[intersect_set.capacity - trailing - 1]); trailing++) {}

    intersect_set.bits = BITWISE_SET_REALLOC(intersect_set.bits, sizeof(BITWISE_SET_BIT_TYPE) * (intersect_set.capacity - trailing));
    intersect_set.capacity -= trailing;

    if (!intersect_set.capacity) { // if set is empty free bits array and set capacity to zero
        BITWISE_SET_FREE(intersect_set.bits);
        intersect_set.bits = NULL;
    }

    return intersect_set;
}

static inline bitwise_set_s subtract_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    if (!set_one.capacity) { // early return if larger set is empty
        return (bitwise_set_s) { 0 };
    }

    bitwise_set_s subtract_set = {
        .bits = BITWISE_SET_REALLOC(NULL, set_one.capacity * sizeof(BITWISE_SET_BIT_TYPE)),
        .size = 0, .capacity = set_one.capacity,
    };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < set_one.capacity && i < set_two.capacity; ++i) { // for each bits type use, idk SUB, and popcount to count bits
        subtract_set.bits[i] = set_one.bits[i] & ~(set_two.bits[i]);

        subtract_set.size += POPCOUNT_BITWISE_SET(subtract_set.bits[i]);
    }
#else
    for (size_t i = 0; i < set_one.capacity && i < set_two.capacity; ++i) { // for each bits type use, idk SUB, then increment and remove to count bits
        subtract_set.bits[i] = set_one.bits[i] & ~(set_two.bits[i]);

        BITWISE_SET_BIT_TYPE current = subtract_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            subtract_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    size_t trailing = 0; // get trailing empty bits count
    for (; trailing < subtract_set.capacity && !(subtract_set.bits[subtract_set.capacity - trailing - 1]); trailing++) {}

    subtract_set.bits = BITWISE_SET_REALLOC(subtract_set.bits, sizeof(BITWISE_SET_BIT_TYPE) * (subtract_set.capacity - trailing));
    subtract_set.capacity -= trailing;

    if (!subtract_set.capacity) { // if set is empty free bits array and set capacity to zero
        BITWISE_SET_FREE(subtract_set.bits);
        subtract_set.bits = NULL;
    }

    return subtract_set;
}

static inline bitwise_set_s exclude_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    const bitwise_set_s smaller = set_one.capacity < set_two.capacity ? set_one : set_two;
    const bitwise_set_s larger = set_one.capacity > set_two.capacity ? set_one : set_two;

    if (!larger.capacity) { // early return if larger set is empty since exclude depends on larger set
        return (bitwise_set_s) { 0 };
    }

    bitwise_set_s exclude_set = {
        .bits = BITWISE_SET_REALLOC(NULL, larger.capacity * sizeof(BITWISE_SET_BIT_TYPE)),
        .size = 0, .capacity = larger.capacity,
    };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < smaller.capacity; ++i) { // for each bits type use XOR and popcount to count bits
        exclude_set.bits[i] = set_one.bits[i] ^ set_two.bits[i];

        exclude_set.size += POPCOUNT_BITWISE_SET(exclude_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller.capacity; ++i) { // for each bits type use XOR, then increment and remove to count bits
        exclude_set.bits[i] = set_one.bits[i] ^ set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = exclude_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            exclude_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = smaller.capacity; i < larger.capacity; ++i) { // then for the remaining bits
        exclude_set.bits[i] = larger.bits[i];
        exclude_set.size += POPCOUNT_BITWISE_SET(exclude_set.bits[i]);
    }
#else
    for (size_t i = smaller.capacity; i < larger.capacity; ++i) {
        exclude_set.bits[i] = larger.bits[i];

        BITWISE_SET_BIT_TYPE current = exclude_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            exclude_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    size_t trailing = 0; // get trailing empty bits count
    for (; trailing < exclude_set.capacity && !(exclude_set.bits[exclude_set.capacity - trailing - 1]); trailing++) {}

    exclude_set.bits = BITWISE_SET_REALLOC(exclude_set.bits, sizeof(BITWISE_SET_BIT_TYPE) * (exclude_set.capacity - trailing));
    exclude_set.capacity -= trailing;

    if (!exclude_set.capacity) { // if set is empty free bits array and set capacity to zero
        BITWISE_SET_FREE(exclude_set.bits);
        exclude_set.bits = NULL;
    }

    return exclude_set;
}

static inline bool is_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub) {
    const size_t smaller_capacity = super.capacity < sub.capacity ? super.capacity : sub.capacity;

    for (size_t i = 0; i < smaller_capacity; ++i) {
        if ((super.bits[i] & sub.bits[i]) != sub.bits[i]) {
            return false;
        }
    }

    // if super is bigger or equal then sub is a subset of super
    return (super.capacity >= sub.capacity);
}
static inline bool is_proper_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub) {
    const size_t smaller_capacity = super.capacity < sub.capacity ? super.capacity : sub.capacity;

    for (size_t i = 0; i < smaller_capacity; ++i) { // check if on smallest set super and sub have overlapping bits
        if ((super.bits[i] & sub.bits[i]) != sub.bits[i]) {
            return false;
        }
    }

    // if super is bigger or equal and super and sub dont share all bits then it is a propper subset
    return (super.capacity >= sub.capacity) && (super.size != sub.size);
}

static inline bool is_disjoint_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    const size_t smaller_capacity = set_one.capacity < set_two.capacity ? set_one.capacity : set_two.capacity;

    for (size_t i = 0; i < smaller_capacity; ++i) { // only check if the smallest set doesn't have overlapping bits
        if (set_one.bits[i] & set_two.bits[i]) {
            return false;
        }
    }

    return true;
}

#elif BITWISE_SET_MODE == FINITE_ALLOCATED_BITWISE_SET_MODE

typedef struct bitwise_set {
    BITWISE_SET_BIT_TYPE * bits;
    size_t max, size;
} bitwise_set_s;

static inline bitwise_set_s create_bitwise_set(const size_t max) {
    BITWISE_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");

    const size_t type_size = ((max - (max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    const bitwise_set_s set = {
        .max = max, .size = 0,
        .bits = BITWISE_SET_REALLOC(NULL, sizeof(BITWISE_SET_BIT_TYPE) * type_size),
    };
    BITWISE_SET_ASSERT(set.bits && "[ERROR] Memory allocation failed.");

    memset(set.bits, 0, sizeof(BITWISE_SET_BIT_TYPE) * type_size);

    return set;
}

static inline void destroy_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set->size <= set->max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set->bits && "[ERROR] Set's elements pointer is NULL.");

    // basically the same as destroy in this case
    BITWISE_SET_FREE(set->bits); // destroy bits array
    (*set) = (bitwise_set_s) { 0 }; // zero set set struct
}

static inline void clear_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set->size <= set->max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set->bits && "[ERROR] Set's elements pointer is NULL.");

    set->max = set->size = 0;
}

static inline bitwise_set_s copy_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set.size <= set.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set.bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_size = ((set.max - (set.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    const bitwise_set_s replica = {
        .max = set.max, .size = 0,
        .bits = BITWISE_SET_REALLOC(NULL, sizeof(BITWISE_SET_BIT_TYPE) * type_size),
    };

    BITWISE_SET_ASSERT(set.bits && "[ERROR] Memory allocation failed.");

    memcpy(replica.bits, set.bits, sizeof(BITWISE_SET_BIT_TYPE) * type_size);

    return replica;
}

static inline bool is_empty_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set.size <= set.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set.bits && "[ERROR] Set's elements pointer is NULL.");

    return !(set.size);
}

static inline bool is_full_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set.size <= set.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set.bits && "[ERROR] Set's elements pointer is NULL.");

    return (set.size == set.max);
}

static inline void foreach_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE * universe, const operate_bitwise_set_fn operate, void * args) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(universe && "[ERROR] 'universe' parameter is NULL.");
    BITWISE_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BITWISE_SET_ASSERT(set->max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set->size <= set->max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set->bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_size = ((set->max - (set->max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < type_size; ++i) {
        BITWISE_SET_BIT_TYPE current = set->bits[i]; // save bit type to remove bits from after finding indexes

        // create a stack to operate over each element from left to right and not right to left
        // since only trailing or rightmost zeros can be count to make
        struct stack {
            size_t size;
            size_t elements[BITWISE_SET_BIT_COUNT];
        } stack = { .size = 0, };

        while (current) { // while current is not zero
            const size_t trailing = TRAILING_BITWISE_SET(current); // get typecast trailing zeros index
            stack.elements[stack.size++] = trailing + (i * BITWISE_SET_BIT_COUNT); // calculate universe index

            current ^= (1 << trailing); // remove bit at left of trailing zeros
        }

        while (stack.size) { // pop stack to get indexes in proper order
            if (!operate(universe + stack.elements[--stack.size], args)) { // operate on element left to last trailing zero in universe
                return;
            }
        }
    }
#else
    for (size_t i = 0; i < type_size; ++i) { // for each bit type
        for (size_t j = 0; j < BITWISE_SET_BIT_COUNT; ++j) {
            const size_t left = BITWISE_SET_BIT_COUNT - j - 1; // calculate left index of bit type
            const BITWISE_SET_BIT_TYPE bit = (BITWISE_SET_BIT_TYPE)(1) << left; // create single bit at left index

            // if single bit ANDS with bit type, and operate function halts then return, else continue
            if ((bit & set->bits[i]) && !operate(universe + (left + (i * BITWISE_SET_BIT_COUNT)), args)) {
                return;
            }
        }
    }
#endif
}

static inline bool contains_bitwise_set(const bitwise_set_s set, const size_t index) {
    BITWISE_SET_ASSERT(set.size && "[ERROR] Can't check from empty set.");
    BITWISE_SET_ASSERT(index < set.max && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set.size <= set.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set.bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    // if bit type index exceeds capacity the element's index is not contained, else check bits
    return (bool)(set.bits[type_index] & element_bit);
}

static inline void insert_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size < set->max && "[ERROR] Can't insert into full set.");
    BITWISE_SET_ASSERT(index < set->max && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set->max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set->size <= set->max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set->bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    BITWISE_SET_ASSERT(!(set->bits[type_index] & element_bit) && "[ERROR] Set already contains element.");

    set->bits[type_index] |= element_bit;
    set->size++;
}

static inline void remove_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");
    BITWISE_SET_ASSERT(index < set->max && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set->max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set->size <= set->max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set->bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    BITWISE_SET_ASSERT((set->bits[type_index] & element_bit) && "[ERROR] Set does not contain element.");

    set->bits[type_index] ^= element_bit;
    set->size--;
}

static inline bitwise_set_s union_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two, const size_t max) {
    BITWISE_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set one's maximum.");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set two's maximum.");

    BITWISE_SET_ASSERT(set_one.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_one.size <= set_one.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_one.bits && "[ERROR] Set's elements pointer is NULL.");

    BITWISE_SET_ASSERT(set_two.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_two.size <= set_two.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.bits && "[ERROR] Set's elements pointer is NULL.");

    const bitwise_set_s smaller = set_one.max < set_two.max ? set_one : set_two;
    const bitwise_set_s larger = set_one.max > set_two.max ? set_one : set_two;

    const size_t type_size = ((max - (max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    bitwise_set_s union_set = {
        .max = max, .size = 0,
        .bits = BITWISE_SET_REALLOC(NULL, sizeof(BITWISE_SET_BIT_TYPE) * type_size),
    };
    BITWISE_SET_ASSERT(union_set.bits && "[ERROR] Memory allocation failed.");

    const size_t larger_type_size = ((larger.max - (larger.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    const size_t smaller_type_size = ((smaller.max - (smaller.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use OR and popcount to count bits
        union_set.bits[i] = set_one.bits[i] | set_two.bits[i];
        union_set.size += POPCOUNT_BITWISE_SET(union_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use increment and remove to count bits
        union_set.bits[i] = set_one.bits[i] | set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = smaller_type_size; i < larger_type_size; ++i) { // simply copy the exceeding bits into union set
        union_set.bits[i] = larger.bits[i];
        union_set.size += POPCOUNT_BITWISE_SET(union_set.bits[i]);
    }
#else
    for (size_t i = smaller_type_size; i < larger_type_size; ++i) { // simply copy the exceeding bits into union set
        union_set.bits[i] = larger.bits[i];

        BITWISE_SET_BIT_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    memset(union_set.bits + larger.max, 0, sizeof(BITWISE_SET_BIT_TYPE) * (max - larger.max));

    return union_set;
}

static inline bitwise_set_s intersect_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two, const size_t max) {
    BITWISE_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set one's maximum.");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set two's maximum.");

    BITWISE_SET_ASSERT(set_one.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_one.size <= set_one.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_one.bits && "[ERROR] Set's elements pointer is NULL.");

    BITWISE_SET_ASSERT(set_two.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_two.size <= set_two.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_size = ((max - (max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    bitwise_set_s intersect_set = {
        .max = max, .size = 0,
        .bits = BITWISE_SET_REALLOC(NULL, sizeof(BITWISE_SET_BIT_TYPE) * type_size),
    };
    BITWISE_SET_ASSERT(intersect_set.bits && "[ERROR] Memory allocation failed.");

    const bitwise_set_s smaller = set_one.max < set_two.max ? set_one : set_two;
    const size_t smaller_type_size = ((smaller.max - (smaller.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use AND and popcount to count bits
        intersect_set.bits[i] = set_one.bits[i] & set_two.bits[i];
        intersect_set.size += POPCOUNT_BITWISE_SET(intersect_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use AND, then increment and remove to count bits
        intersect_set.bits[i] = set_one.bits[i] & set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = intersect_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            intersect_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    memset(intersect_set.bits + smaller.max, 0, sizeof(BITWISE_SET_BIT_TYPE) * (max - smaller.max));

    return intersect_set;
}

static inline bitwise_set_s subtract_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two, const size_t max) {
    BITWISE_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set one's maximum.");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set two's maximum.");

    BITWISE_SET_ASSERT(set_one.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_one.size <= set_one.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_one.bits && "[ERROR] Set's elements pointer is NULL.");

    BITWISE_SET_ASSERT(set_two.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_two.size <= set_two.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_size = ((max - (max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    bitwise_set_s subtract_set = {
        .max = max, .size = 0,
        .bits = BITWISE_SET_REALLOC(NULL, sizeof(BITWISE_SET_BIT_TYPE) * type_size),
    };
    BITWISE_SET_ASSERT(subtract_set.bits && "[ERROR] Memory allocation failed.");

    const bitwise_set_s smaller = set_one.max < set_two.max ? set_one : set_two;
    const size_t smaller_type_size = ((smaller.max - (smaller.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use, idk SUB, and popcount to count bits
        subtract_set.bits[i] = set_one.bits[i] & ~(set_two.bits[i]);
        subtract_set.size += POPCOUNT_BITWISE_SET(subtract_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use, idk SUB, then increment and remove to count bits
        subtract_set.bits[i] = set_one.bits[i] & ~(set_two.bits[i]);

        BITWISE_SET_BIT_TYPE current = subtract_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            subtract_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    memset(subtract_set.bits + smaller.max, 0, sizeof(BITWISE_SET_BIT_TYPE) * (max - smaller.max));

    return subtract_set;
}

static inline bitwise_set_s exclude_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two, const size_t max) {
    BITWISE_SET_ASSERT(max && "[ERROR] 'max' parameter can't be zero");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set one's maximum.");
    BITWISE_SET_ASSERT(set_one.max <= max && "[ERROR] Maximum size exceeds set two's maximum.");

    BITWISE_SET_ASSERT(set_one.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_one.size <= set_one.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_one.bits && "[ERROR] Set's elements pointer is NULL.");

    BITWISE_SET_ASSERT(set_two.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_two.size <= set_two.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t type_size = ((max - (max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    bitwise_set_s exclude_set = {
        .max = max, .size = 0,
        .bits = BITWISE_SET_REALLOC(NULL, sizeof(BITWISE_SET_BIT_TYPE) * type_size),
    };
    BITWISE_SET_ASSERT(exclude_set.bits && "[ERROR] Memory allocation failed.");

    const bitwise_set_s smaller = set_one.max < set_two.max ? set_one : set_two;
    const bitwise_set_s larger = set_one.max > set_two.max ? set_one : set_two;

    const size_t larger_type_size = ((larger.max - (larger.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    const size_t smaller_type_size = ((smaller.max - (smaller.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use XOR and popcount to count bits
        exclude_set.bits[i] = set_one.bits[i] ^ set_two.bits[i];
        exclude_set.size += POPCOUNT_BITWISE_SET(exclude_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use XOR, then increment and remove to count bits
        exclude_set.bits[i] = set_one.bits[i] ^ set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = exclude_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            exclude_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = smaller_type_size; i < larger_type_size; ++i) { // then for the remaining bits
        exclude_set.bits[i] = larger.bits[i];
        exclude_set.size += POPCOUNT_BITWISE_SET(exclude_set.bits[i]);
    }
#else
    for (size_t i = smaller_type_size; i < larger_type_size; ++i) {
        exclude_set.bits[i] = larger.bits[i];

        BITWISE_SET_BIT_TYPE current = exclude_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            exclude_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    memset(exclude_set.bits + larger.max, 0, sizeof(BITWISE_SET_BIT_TYPE) * (max - larger.max));

    return exclude_set;
}

static inline bool is_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub) {
    BITWISE_SET_ASSERT(super.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(super.size <= super.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(super.bits && "[ERROR] Set's elements pointer is NULL.");

    BITWISE_SET_ASSERT(sub.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(sub.size <= sub.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(sub.bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t smaller = super.max < sub.max ? super.max : sub.max;
    const size_t smaller_type_size = ((smaller - (smaller % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    for (size_t i = 0; i < smaller_type_size; ++i) {
        if (sub.bits[i] != (super.bits[i] & sub.bits[i])) {
            return false;
        }
    }

    // if sub is bigger than super and contains set bits then sub is not a subset of super
    const size_t sub_type_size = ((sub.max - (sub.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    for (size_t i = smaller_type_size; i < sub_type_size; ++i) {
        if (super.bits[i]) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub) {
    BITWISE_SET_ASSERT(super.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(super.size <= super.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(super.bits && "[ERROR] Set's elements pointer is NULL.");

    BITWISE_SET_ASSERT(sub.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(sub.size <= sub.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(sub.bits && "[ERROR] Set's elements pointer is NULL.");

    const size_t smaller = super.max < sub.max ? super.max : sub.max;
    const size_t smaller_type_size = ((smaller - (smaller % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    for (size_t i = 0; i < smaller_type_size; ++i) {
        if (sub.bits[i] != (super.bits[i] & sub.bits[i])) {
            return false;
        }
    }

    // if sub is bigger than super and contains set bits then sub is not a subset of super
    const size_t sub_type_size = ((sub.max - (sub.max % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    for (size_t i = smaller_type_size; i < sub_type_size; ++i) {
        if (super.bits[i]) {
            return false;
        }
    }

    return super.size != sub.size; // if super and sub have the same size they're subsets but not proper subsets
}

static inline bool is_disjoint_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    BITWISE_SET_ASSERT(set_one.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_one.size <= set_one.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_one.bits && "[ERROR] Set's elements pointer is NULL.");

    BITWISE_SET_ASSERT(set_two.max && "[ERROR] Set's maximum size can't be zero.");
    BITWISE_SET_ASSERT(set_two.size <= set_two.max && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.bits && "[ERROR] Set's elements pointer is NULL.");

    // sets are dosjoint if AND-ing their bits returns 0, we only need to check the smallest
    const size_t smaller = set_one.max < set_two.max ? set_one.max : set_two.max;
    const size_t smaller_type_size = ((smaller - (smaller % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1;
    for (size_t i = 0; i < smaller_type_size; ++i) {
        if (set_one.bits[i] & set_two.bits[i]) {
            return false;
        }
    }

    return true;
}

#elif BITWISE_SET_MODE == FINITE_PRERPOCESSOR_BITWISE_SET_MODE

#ifndef PREPROCESSOR_BITWISE_SET_SIZE

#define PREPROCESSOR_BITWISE_SET_SIZE (1 << 5)

#elif PREPROCESSOR_BITWISE_SET_SIZE == 0

#error 'PREPROCESSOR_BITWISE_SET_SIZE' cannot be zero

#endif

#define BITWISE_SET_TYPE_LENGTH (((PREPROCESSOR_BITWISE_SET_SIZE - (PREPROCESSOR_BITWISE_SET_SIZE % BITWISE_SET_BIT_COUNT)) / BITWISE_SET_BIT_COUNT) + 1)

typedef struct bitwise_set {
    BITWISE_SET_BIT_TYPE bits[BITWISE_SET_TYPE_LENGTH];
    size_t size;
} bitwise_set_s;

static inline bitwise_set_s create_bitwise_set(void) {
    return (bitwise_set_s) { 0 }; // needs to be all zero to also mabe bits empty
}

static inline void destroy_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    set->size = 0;
}

static inline void clear_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    (*set) = (bitwise_set_s) { 0 };
}

static inline bitwise_set_s copy_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    return set;
}

static inline bool is_empty_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    return !(set.size);
}

static inline bool is_full_bitwise_set(const bitwise_set_s set) {
    BITWISE_SET_ASSERT(set.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    return (set.size == PREPROCESSOR_BITWISE_SET_SIZE);
}

static inline void foreach_bitwise_set(bitwise_set_s const * set, BITWISE_SET_DATA_TYPE universe[static BITWISE_SET_TYPE_LENGTH], const operate_bitwise_set_fn operate, void * args) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(universe && "[ERROR] 'universe' parameter is NULL.");
    BITWISE_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) {
        BITWISE_SET_BIT_TYPE current = set->bits[i]; // save bit type to remove bits from after finding indexes

        // create a stack to operate over each element from left to right and not right to left
        // since only trailing or rightmost zeros can be count to make
        struct stack {
            size_t size;
            size_t elements[BITWISE_SET_BIT_COUNT];
        } stack = { .size = 0, };

        while (current) { // while current is not zero
            const size_t trailing = TRAILING_BITWISE_SET(current); // get typecast trailing zeros index
            stack.elements[stack.size++] = trailing + (i * BITWISE_SET_BIT_COUNT); // calculate universe index

            current ^= (1 << trailing); // remove bit at left of trailing zeros
        }

        while (stack.size) { // pop stack to get indexes in proper order
            if (!operate(universe + stack.elements[--stack.size], args)) { // operate on element left to last trailing zero in universe
                return;
            }
        }
    }
#else
    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) { // for each bit type
        for (size_t j = 0; j < BITWISE_SET_BIT_COUNT; ++j) {
            const size_t left = BITWISE_SET_BIT_COUNT - j - 1; // calculate left index of bit type
            const BITWISE_SET_BIT_TYPE bit = (BITWISE_SET_BIT_TYPE)(1) << left; // create single bit at left index

            // if single bit ANDS with bit type, and operate function halts then return, else continue
            if ((bit & set->bits[i]) && !operate(universe + (left + (i * BITWISE_SET_BIT_COUNT)), args)) {
                return;
            }
        }
    }
#endif
}

static inline bool contains_bitwise_set(const bitwise_set_s set, const size_t index) {
    BITWISE_SET_ASSERT(set.size && "[ERROR] Can't check from empty set.");
    BITWISE_SET_ASSERT(index < PREPROCESSOR_BITWISE_SET_SIZE && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    return (bool)(set.bits[type_index] & element_bit);
}

static inline void insert_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size < PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Can't insert into full set.");
    BITWISE_SET_ASSERT(index < PREPROCESSOR_BITWISE_SET_SIZE && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set->size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    BITWISE_SET_ASSERT(!(set->bits[type_index] & element_bit) && "[ERROR] Set already contains element.");

    set->bits[type_index] |= element_bit;
    set->size++;
}

static inline void remove_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");
    BITWISE_SET_ASSERT(index < PREPROCESSOR_BITWISE_SET_SIZE && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set->size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    BITWISE_SET_ASSERT((set->bits[type_index] & element_bit) && "[ERROR] Set does not contain element.");

    set->bits[type_index] ^= element_bit;
    set->size--;
}

static inline bitwise_set_s union_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    BITWISE_SET_ASSERT(set_one.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s union_set = { .size = 0, };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        union_set.bits[i] = set_one.bits[i] | set_two.bits[i];
        union_set.size += POPCOUNT_BITWISE_SET(union_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use increment and remove to count bits
        union_set.bits[i] = set_one.bits[i] | set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return union_set;
}

static inline bitwise_set_s intersect_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    BITWISE_SET_ASSERT(set_one.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s intersect_set = { .size = 0, };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        intersect_set.bits[i] = set_one.bits[i] & set_two.bits[i];
        intersect_set.size += POPCOUNT_BITWISE_SET(intersect_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use increment and remove to count bits
        intersect_set.bits[i] = set_one.bits[i] & set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = intersect_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            intersect_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return intersect_set;
}

static inline bitwise_set_s subtract_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    BITWISE_SET_ASSERT(set_one.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s subtract_set = { .size = 0, };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        subtract_set.bits[i] = set_one.bits[i] & ~(set_two.bits[i]);
        subtract_set.size += POPCOUNT_BITWISE_SET(subtract_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use increment and remove to count bits
        subtract_set.bits[i] = set_one.bits[i] & ~(set_two.bits[i]);

        BITWISE_SET_BIT_TYPE current = subtract_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            subtract_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return subtract_set;
}

static inline bitwise_set_s exclude_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    BITWISE_SET_ASSERT(set_one.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s exclude_set = { .size = 0, };

#ifdef IS_BUILTIN_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        exclude_set.bits[i] = set_one.bits[i] ^ set_two.bits[i];
        exclude_set.size += POPCOUNT_BITWISE_SET(exclude_set.bits[i]);
    }
#else
    for (size_t i = 0; i < smaller_type_size; ++i) { // for each bits type use increment and remove to count bits
        exclude_set.bits[i] = set_one.bits[i] ^ set_two.bits[i];

        BITWISE_SET_BIT_TYPE current = exclude_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            exclude_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return exclude_set;
}

static inline bool is_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub) {
    BITWISE_SET_ASSERT(super.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(sub.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) {
        if (sub.bits[i] != (sub.bits[i] & super.bits[i])) {
            return false;
        }
    }

    return true;
}

static inline bool is_proper_subset_bitwise_set(const bitwise_set_s super, const bitwise_set_s sub) {
    BITWISE_SET_ASSERT(super.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(sub.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) {
        if (sub.bits[i] != (sub.bits[i] & super.bits[i])) {
            return false;
        }
    }

    return (sub.size != super.size);
}

static inline bool is_disjoint_bitwise_set(const bitwise_set_s set_one, const bitwise_set_s set_two) {
    BITWISE_SET_ASSERT(set_one.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two.size <= PREPROCESSOR_BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    for (size_t i = 0; i < BITWISE_SET_TYPE_LENGTH; ++i) {
        if (set_one.bits[i] & set_two.bits[i]) {
            return false;
        }
    }

    return true;
}

#endif

#else

#error Cannot include multiple headers in same unit.

#endif //BITWISE_SET_H
