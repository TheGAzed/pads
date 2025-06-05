#ifndef BITWISE_SET_H
#define BITWISE_SET_H

#include <stddef.h>  // imports size_t
#include <stdbool.h> // imports bool
#include <limits.h>  // imports CHAR_BIT

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

#ifndef BITWISE_SET_DATA_TYPE

/// @brief To change, use: #define BITWISE_SET_DATA_TYPE [type].
#define BITWISE_SET_DATA_TYPE unsigned long long

#endif

#ifndef BITWISE_SET_ASSERT

#include <assert.h>  // imports assert for debugging

/// @brief To change, use: #define BITWISE_SET_ASSERT [assert].
#define BITWISE_SET_ASSERT assert

#endif

// if either gcc or clang, and has __builtin_*ll support define POPCOUNT and CTZ
#if defined(__GNUC__) || defined(__clang__)

#define POPCOUNT_BITWISE_SET(bits) ((size_t)__builtin_popcountll((unsigned long long)(bits)))

#endif

/// @brief Function pointer to operate on a single set index based on generic arguments.
typedef bool (*operate_index_bitwise_set_fn) (const size_t index, void * args);
/// @brief Function pointer to operate on a single set bits based on generic arguments.
typedef bool (*operate_bits_bitwise_set_fn) (BITWISE_SET_DATA_TYPE * bits, void * args);
/// @brief Function pointer to manage an array of set elements based on generic arguments.
typedef void (*manage_bitwise_set_fn)  (BITWISE_SET_DATA_TYPE * array, const size_t size, void * args);

#ifndef BITWISE_SET_SIZE

#define BITWISE_SET_SIZE (1 << 5)

#elif BITWISE_SET_SIZE == 0

#error Size cannot be zero.

#endif

#define BITWISE_SET_BIT_COUNT (sizeof(BITWISE_SET_DATA_TYPE) * CHAR_BIT)

#define BITWISE_SET_DATA_TYPE_LENGTH ((((BITWISE_SET_SIZE) - 1) / (BITWISE_SET_BIT_COUNT)) + 1)

typedef struct bitwise_set {
    BITWISE_SET_DATA_TYPE bits[BITWISE_SET_DATA_TYPE_LENGTH];
    size_t size;
} bitwise_set_s;

/// @brief Creates and returns a set.
/// @return Newly created set.
static inline bitwise_set_s create_bitwise_set(void) {
    return (bitwise_set_s) { 0 }; // needs to be all zero to also mabe bits empty
}

/// @brief Destroys the set and all its elements.
/// @param set Set to destroy together with its elements.
static inline void destroy_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    memset(set->bits, 0, BITWISE_SET_DATA_TYPE_LENGTH * sizeof(BITWISE_SET_DATA_TYPE));
    set->size = 0;
}

/// @brief Clears the set and all its elements.
/// @param set Set to destroy together with its elements.
static inline void clear_bitwise_set(bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    memset(set->bits, 0, BITWISE_SET_DATA_TYPE_LENGTH * sizeof(BITWISE_SET_DATA_TYPE));
    set->size = 0;
}

/// @brief Creates a deep or shallow copy of a set depending on function pointer parameter.
/// @param set Set to copy together with its elements.
/// @return Copy of set parameter.
static inline bitwise_set_s copy_bitwise_set(const bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    return (*set);
}

/// @brief Checks if set is empty.
/// @param set Set to check.
/// @return 'true' if set is empty, 'false' otherwise.
static inline bool is_empty_bitwise_set(const bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    return !(set->size);
}

/// @brief Checks if set is full.
/// @param set Set to check.
/// @return 'true' if set is full, 'false' otherwise.
static inline bool is_full_bitwise_set(const bitwise_set_s * set) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    return (set->size == BITWISE_SET_SIZE);
}

/// @brief Iterates over each element in set calling operate function on it using generic arguments.
/// @param set Set to iterate over.
/// @param operate Function pointer to call on each element reference using generic arguments.
/// @param args Generic void pointer arguments used in 'operate' function.
static inline void foreach_index_bitwise_set(const bitwise_set_s * set, const operate_index_bitwise_set_fn operate, void * args) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) {
        for (size_t j = 0; j < BITWISE_SET_SIZE; ++j) {
            const size_t bitwise_index = BITWISE_SET_BIT_COUNT - j - 1;

            if (set->bits[i] & ((size_t)(1) << bitwise_index) && !operate(j, args)) {
                return;
            }
        }
    }
}

/// @brief Iterates over each element in set calling operate function on it using generic arguments.
/// @param set Set to iterate over.
/// @param operate Function pointer to call on each element reference using generic arguments.
/// @param args Generic void pointer arguments used in 'operate' function.
static inline void foreach_bits_bitwise_set(bitwise_set_s * set, const operate_bits_bitwise_set_fn operate, void * args) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    for (BITWISE_SET_DATA_TYPE * e = set->bits; e < set->bits + BITWISE_SET_DATA_TYPE_LENGTH && operate(e, args); ++e) {}
}

/// @brief Maps elements in set into array and calls manage function on it using set's size and generic arguments.
/// @param set Set to map elements into array.
/// @param manage Function pointer to call on all elements as array using set's size and generic arguments.
/// @param args Generic void pointer arguments used in 'manage' function.
static inline void manage_bitwise_set(bitwise_set_s * set, const manage_bitwise_set_fn manage, void * args) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(manage && "[ERROR] 'operate' parameter is NULL.");

    manage(set->bits, BITWISE_SET_DATA_TYPE_LENGTH, args);
}

/// @brief Checks if set contains the specified element.
/// @param set Set structure to check.
/// @param index Index to check if contained in set.
/// @return 'true' if element is contained in set, 'false' if not.
static inline bool contains_bitwise_set(const bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size && "[ERROR] Can't check from empty set.");
    BITWISE_SET_ASSERT(index < BITWISE_SET_SIZE && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    return (bool)(set->bits[type_index] & element_bit);
}

/// @brief Adds specified element to the set.
/// @param set Set to add element into.
/// @param index Index to add into set.
/// @note If element is contained in set the function terminates with error.
static inline void insert_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size < BITWISE_SET_SIZE && "[ERROR] Can't insert into full set.");
    BITWISE_SET_ASSERT(index < BITWISE_SET_SIZE && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    BITWISE_SET_ASSERT(!(set->bits[type_index] & element_bit) && "[ERROR] Set already contains element.");

    set->bits[type_index] |= element_bit;
    set->size++;
}

/// @brief Remove specified element from set.
/// @param set Set to remove element from.
/// @param index Index to remove from set.
/// @note If element is not contained in set the function terminates with an error.
/// @return Removed element.
static inline void remove_bitwise_set(bitwise_set_s * set, const size_t index) {
    BITWISE_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    BITWISE_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");
    BITWISE_SET_ASSERT(index < BITWISE_SET_SIZE && "[ERRRO] Index exceeds maximum size.");

    BITWISE_SET_ASSERT(set->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    const size_t type_index = index / BITWISE_SET_BIT_COUNT;
    const size_t true_index = index % BITWISE_SET_BIT_COUNT;
    const size_t element_bit = (size_t)(1) << (BITWISE_SET_BIT_COUNT - true_index - 1);

    BITWISE_SET_ASSERT((set->bits[type_index] & element_bit) && "[ERROR] Set does not contain element.");

    set->bits[type_index] ^= element_bit;
    set->size--;
}

/// @brief Creates and returns a union of two sets whose elements are copied into the new set.
/// @param set_one First set structure to unite.
/// @param set_two Second set structure to unite.
/// @return New union of set parameters.
static inline bitwise_set_s union_bitwise_set(const bitwise_set_s * set_one, const bitwise_set_s * set_two) {
    BITWISE_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    BITWISE_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    BITWISE_SET_ASSERT(set_one->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s union_set = { .size = 0, };

#ifdef POPCOUNT_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        union_set.bits[i] = set_one->bits[i] | set_two->bits[i];
        union_set.size += POPCOUNT_BITWISE_SET(union_set.bits[i]);
    }
#else
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use increment and remove to count bits
        union_set.bits[i] = set_one->bits[i] | set_two->bits[i];

        BITWISE_SET_DATA_TYPE current = union_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            union_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return union_set;
}

/// @brief Creates and returns an intersect of two sets whose elements are copied into the new set.
/// @param set_one First set structure to intersect.
/// @param set_two Second set structure to intersect.
/// @return New intersect of set parameters.
static inline bitwise_set_s intersect_bitwise_set(const bitwise_set_s * set_one, const bitwise_set_s * set_two) {
    BITWISE_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    BITWISE_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    BITWISE_SET_ASSERT(set_one->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s intersect_set = { .size = 0, };

#ifdef POPCOUNT_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        intersect_set.bits[i] = set_one->bits[i] & set_two->bits[i];
        intersect_set.size += POPCOUNT_BITWISE_SET(intersect_set.bits[i]);
    }
#else
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use increment and remove to count bits
        intersect_set.bits[i] = set_one->bits[i] & set_two->bits[i];

        BITWISE_SET_DATA_TYPE current = intersect_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            intersect_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return intersect_set;
}

/// @brief Creates and returns a subtraction of two sets whose elements are copied into the new set.
/// @param set_one First set structure that gets subtracted.
/// @param set_two Second set structure that subtracts.
/// @return New subtraction of set parameters.
static inline bitwise_set_s subtract_bitwise_set(const bitwise_set_s * set_one, const bitwise_set_s * set_two) {
    BITWISE_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    BITWISE_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    BITWISE_SET_ASSERT(set_one->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s subtract_set = { .size = 0, };

#ifdef POPCOUNT_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        subtract_set.bits[i] = set_one->bits[i] & ~(set_two->bits[i]);
        subtract_set.size += POPCOUNT_BITWISE_SET(subtract_set.bits[i]);
    }
#else
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use increment and remove to count bits
        subtract_set.bits[i] = set_one->bits[i] & ~(set_two->bits[i]);

        BITWISE_SET_DATA_TYPE current = subtract_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            subtract_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return subtract_set;
}

/// @brief Creates and returns an exclude (symmetric difference) of two sets whose elements are copied into the new set.
/// @param set_one First set structure to exclude.
/// @param set_two Second set structure to exclude.
/// @return New exclude of set parameters.
static inline bitwise_set_s exclude_bitwise_set(const bitwise_set_s * set_one, const bitwise_set_s * set_two) {
    BITWISE_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    BITWISE_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    BITWISE_SET_ASSERT(set_one->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    bitwise_set_s exclude_set = { .size = 0, };

#ifdef POPCOUNT_BITWISE_SET
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use OR and popcount to count bits
        exclude_set.bits[i] = set_one->bits[i] ^ set_two->bits[i];
        exclude_set.size += POPCOUNT_BITWISE_SET(exclude_set.bits[i]);
    }
#else
    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) { // for each bits type use increment and remove to count bits
        exclude_set.bits[i] = set_one->bits[i] ^ set_two->bits[i];

        BITWISE_SET_DATA_TYPE current = exclude_set.bits[i];
        while (current) { // while current is not 0 increment union set size and remove rightmost bit from current
            exclude_set.size++;
            current ^= current & (~current + 1); // extract and remove rightmost bit
        }
    }
#endif

    return exclude_set;
}

/// @brief Checks if sub is subset of super (sub <= super).
/// @param super Superset to check on.
/// @param sub Subset to check with superset.
/// @return 'true' if sub is subset of superset, 'false' if not.
static inline bool is_subset_bitwise_set(const bitwise_set_s * super, const bitwise_set_s * sub) {
    BITWISE_SET_ASSERT(super && "[ERROR] 'super' parameter is NULL.");
    BITWISE_SET_ASSERT(sub && "[ERROR] 'sub' parameter is NULL.");
    BITWISE_SET_ASSERT(super->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(sub->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) {
        if (sub->bits[i] != (sub->bits[i] & super->bits[i])) {
            return false;
        }
    }

    return true;
}


/// @brief Checks if sub is proper subset of super (sub < super).
/// @param super Superset to check on.
/// @param sub Subset to check with superset.
/// @return 'true' if sub is proper subset of superset, 'false' if not.
static inline bool is_proper_subset_bitwise_set(const bitwise_set_s * super, const bitwise_set_s * sub) {
    BITWISE_SET_ASSERT(super && "[ERROR] 'super' parameter is NULL.");
    BITWISE_SET_ASSERT(sub && "[ERROR] 'sub' parameter is NULL.");
    BITWISE_SET_ASSERT(super->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(sub->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) {
        if (sub->bits[i] != (sub->bits[i] & super->bits[i])) {
            return false;
        }
    }

    return (sub->size != super->size);
}


/// @brief Checks if two sets are disjoint or not, i.e. have no elements in common.
/// @param set_one First set to check.
/// @param set_two Second set to check.
/// @return 'true' if sets are disjoint, 'false' otherwise.
static inline bool is_disjoint_bitwise_set(const bitwise_set_s * set_one, const bitwise_set_s * set_two) {
    BITWISE_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    BITWISE_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    BITWISE_SET_ASSERT(set_one->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");
    BITWISE_SET_ASSERT(set_two->size <= BITWISE_SET_SIZE && "[ERROR] Set's size can't be more than maximum size.");

    for (size_t i = 0; i < BITWISE_SET_DATA_TYPE_LENGTH; ++i) {
        if (set_one->bits[i] & set_two->bits[i]) {
            return false;
        }
    }

    return true;
}

#else

#error Cannot include multiple headers in same unit.

#endif // BITWISE_SET_H
