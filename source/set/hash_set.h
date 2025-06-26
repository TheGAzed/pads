#ifndef HASH_SET_H
#define HASH_SET_H

/*
    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    hash, for any purpose, commercial or non-commercial, and by any
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
#include <string.h>  // imports memcpy
#include <stdlib.h>  // imports exit

#ifndef HASH_SET_DATA_TYPE
/// @brief To change, use: #define HASH_SET_DATA_TYPE [type].
#   define HASH_SET_DATA_TYPE void*
#endif

#ifndef HASH_SET_ASSERT
#   include <assert.h>  // imports assert for debugging
/// @brief To change, use: #define HASH_SET_ASSERT [assert].
#   define HASH_SET_ASSERT assert
#endif

#if !defined(HASH_SET_ALLOC) && !defined(HASH_SET_FREE)
#   include <stdlib.h>
#   define HASH_SET_ALLOC malloc
#   define HASH_SET_FREE free
#elif !defined(HASH_SET_ALLOC)
#   error Must also define HASH_SET_ALLOC.
#elif !defined(HASH_SET_FREE)
#   error Must also define HASH_SET_FREE.
#endif

#ifndef HASH_SET_SIZE
#   define HASH_SET_SIZE (1 << 10)
#elif HASH_SET_SIZE <= 0
#   error 'HASH_SET_SIZE' cannot be zero
#endif

/// @brief Function pointer to create a deep/shallow copy for hash set element.
typedef HASH_SET_DATA_TYPE  (*copy_hash_set_fn)    (const HASH_SET_DATA_TYPE element);
/// @brief Function pointer to destroy/free an element for hash set element.
typedef void                (*destroy_hash_set_fn) (HASH_SET_DATA_TYPE * element);
/// @brief Function pointer to hash a set element into a value.
typedef size_t              (*hash_set_fn)         (const HASH_SET_DATA_TYPE element);
/// @brief Function pointer to operate on a single set element based on generic arguments.
typedef bool                (*operate_hash_set_fn) (HASH_SET_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of set elements based on generic arguments.
typedef void                (*manage_hash_set_fn)  (HASH_SET_DATA_TYPE * array, const size_t size, void * args);

typedef struct hash_set {
    hash_set_fn hash;
    HASH_SET_DATA_TYPE * elements;
    size_t * next;
    size_t * head;
    size_t size, empty;
} hash_set_s;

/// @brief Creates and returns a set with compare function pointer.
/// @param hash Function pointer to hash elements to index in set
/// @return Newly created set.
static inline hash_set_s create_hash_set(const hash_set_fn hash) {
    HASH_SET_ASSERT(hash && "[ERROR] 'hash' parameter is NULL.");

    const hash_set_s set = {
        .elements = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(HASH_SET_DATA_TYPE)),
        .head = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),
        .next = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),

        .hash = hash, .size = 0, .empty = HASH_SET_SIZE,
    };
    HASH_SET_ASSERT(set.elements && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(set.head && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(set.next && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        set.head[i] = HASH_SET_SIZE;
    }

    return set;
}

/// @brief Destroys the set and all its elements.
/// @param set Set to destroy together with its elements.
/// @param destroy Function pointer to destroy each element in set.
static inline void destroy_hash_set(hash_set_s * set, const destroy_hash_set_fn destroy) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t * current = set->head + i; HASH_SET_SIZE != (*current); (*current) = set->next[(*current)]) {
            destroy(set->elements + (*current));
        }
    }

    set->hash = NULL;
    set->size = 0;
    HASH_SET_FREE(set->elements);
    HASH_SET_FREE(set->head);
    HASH_SET_FREE(set->next);
}

/// @brief Clears the set and all its elements.
/// @param set Set to destroy together with its elements.
/// @param destroy Function pointer to destroy each element in set.
static inline void clear_hash_set(hash_set_s * set, const destroy_hash_set_fn destroy) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set->elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set->head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set->next && "[ERROR] 'next' pointer is NULL.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t * current = set->head + i; HASH_SET_SIZE != (*current); (*current) = set->next[(*current)]) {
            destroy(set->elements + (*current));
        }
    }

    set->size = 0;
}

/// @brief Creates a deep or shallow copy of a set depending on function pointer parameter.
/// @param set Set to copy together with its elements.
/// @param copy Function pointer to create a deep or shallow copy of each element in set.
/// @return Copy of set parameter.
static inline hash_set_s copy_hash_set(const hash_set_s set, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    HASH_SET_ASSERT(set.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set.next && "[ERROR] 'next' pointer is NULL.");

    hash_set_s replica = {
        .elements = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(HASH_SET_DATA_TYPE)),
        .head = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),
        .next = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),

        .hash = set.hash, .size = 0, .empty = HASH_SET_SIZE,
    };
    HASH_SET_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(replica.head && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(replica.next && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        replica.head[i] = HASH_SET_SIZE;

        for (size_t current = set.head[i]; HASH_SET_SIZE != current; current = set.next[current]) {
            const size_t free_index = replica.size;

            replica.elements[free_index] = copy(set.elements[current]);
            replica.size++;

            replica.next[free_index] = replica.head[i];
            replica.head[i] = free_index;
        }
    }

    return replica;
}

/// @brief Checks if set is empty.
/// @param set Set to check.
/// @return 'true' if set is empty, 'false' otherwise.
static inline bool is_empty_hash_set(const hash_set_s set) {
    HASH_SET_ASSERT(set.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set.next && "[ERROR] 'next' pointer is NULL.");

    return !(set.size);
}

/// @brief Checks if set is full.
/// @param set Set to check.
/// @return 'true' if set is full, 'false' otherwise.
static inline bool is_full_hash_set(const hash_set_s set) {
    HASH_SET_ASSERT(set.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set.next && "[ERROR] 'next' pointer is NULL.");

    return (HASH_SET_SIZE == set.size);
}

/// @brief Iterates over each element in set calling operate function on it using generic arguments.
/// @param set Set to iterate over.
/// @param operate Function pointer to call on each element reference using generic arguments.
/// @param args Generic void pointer arguments used in 'operate' function.
static inline void foreach_hash_set(const hash_set_s set, const operate_hash_set_fn operate, void * args) {
    HASH_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    HASH_SET_ASSERT(set.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set.next && "[ERROR] 'next' pointer is NULL.");

    for (size_t i = 0; i < HASH_SET_SIZE; i++) {
        for (size_t current = set.head[i]; HASH_SET_SIZE != current && operate(set.elements + current, args); ) {
            current = set.next[current];
        }
    }
}

/// @brief Maps elements in set into array and calls manage function on it using set's size and generic arguments.
/// @param set Set to map elements into array.
/// @param manage Function pointer to call on all elements as array using set's size and generic arguments.
/// @param args Generic void pointer arguments used in 'manage' function.
static inline void map_hash_set(const hash_set_s set, const manage_hash_set_fn manage, void * args) {
    HASH_SET_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    HASH_SET_ASSERT(set.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_DATA_TYPE * elements = HASH_SET_ALLOC(set.size * sizeof(HASH_SET_DATA_TYPE));
    for (size_t i = 0, index = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current = set.head[i]; HASH_SET_SIZE != current; current = set.next[current]) {
            elements[index++] = set.elements[current];
        }
    }

    manage(elements, set.size, args);

    for (size_t i = 0, index = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current = set.head[i]; HASH_SET_SIZE != current; current = set.next[current]) {
            set.elements[current] = elements[index++];
        }
    }

    HASH_SET_FREE(elements);
}

/// @brief Checks if set contains the specified element.
/// @param set Set structure to check.
/// @param element Element to check if contained in set.
/// @return 'true' if element is contained in set, 'false' if not.
static inline bool contains_hash_set(const hash_set_s set, const HASH_SET_DATA_TYPE element) {
    HASH_SET_ASSERT(set.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set.next && "[ERROR] 'next' pointer is NULL.");

    const size_t element_hash = set.hash(element);
    const size_t element_modulo = element_hash % HASH_SET_SIZE;
    HASH_SET_ASSERT(element_modulo < HASH_SET_SIZE && "[ERROR] Normalized value out of bounds.");

    for (size_t current = set.head[element_modulo]; HASH_SET_SIZE != current; current = set.next[current]) {
        if (element_hash == set.hash(set.elements[current])) {
            return true;
        }
    }

    return false;
}

/// @brief Adds specified element to the set.
/// @param set Set to add element into.
/// @param element Element to add into set.
/// @note If element is contained in set the function terminates with error.
static inline void insert_hash_set(hash_set_s * set, const HASH_SET_DATA_TYPE element) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(set->size < HASH_SET_SIZE && "[ERROR] Can't insert into full set.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set->elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set->head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set->next && "[ERROR] 'next' pointer is NULL.");

    const size_t element_hash = set->hash(element);
    const size_t element_modulo = element_hash % HASH_SET_SIZE;
    HASH_SET_ASSERT(element_modulo < HASH_SET_SIZE && "[ERROR] Normalized value out of bounds.");

    // get free/hole index for element to insert
    size_t free_index = set->size;
    if (HASH_SET_SIZE != set->empty) { // if empty stack has hole index then pop it to free index
        free_index = set->empty;
        set->empty = set->next[set->empty];
    }

    // check if element is in set or not
    for (size_t current = set->head[element_modulo]; HASH_SET_SIZE != current; current = set->next[current]) {
        HASH_SET_ASSERT(element_hash != set->hash(set->elements[current]) && "[ERROR] Element already in set.");
    }

    // set free index' next index to element's head and make first index in element head the free one
    set->next[free_index] = set->head[element_modulo];
    set->head[element_modulo] = free_index;

    // insert element into set
    memcpy(set->elements + free_index, &element, sizeof(HASH_SET_DATA_TYPE));
    set->size++;
}

/// @brief Remove specified element from set.
/// @param set Set to remove element from.
/// @param element Element to remove from set.
/// @note If element is not contained in set the function terminates with an error.
/// @return Removed element.
static inline HASH_SET_DATA_TYPE remove_hash_set(hash_set_s * set, const HASH_SET_DATA_TYPE element) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set->elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set->head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set->next && "[ERROR] 'next' pointer is NULL.");

    const size_t element_hash = set->hash(element);
    const size_t element_modulo = element_hash % HASH_SET_SIZE;
    HASH_SET_ASSERT(element_modulo < HASH_SET_SIZE && "[ERROR] Normalized value out of bounds.");

    // check if element is in set or not
    for (size_t * current = set->head + element_modulo; HASH_SET_SIZE != (*current); current = set->next + (*current)) {
        if (element_hash != set->hash(set->elements[(*current)])) {
            continue;
        }

        // temporary save removed element
        HASH_SET_DATA_TYPE removed = set->elements[(*current)];
        set->size--;

        const size_t temp = (*current);

        // change current index to next
        (*current) = set->next[temp];

        // minimize holes by checking if current is rightmost element in list
        if (temp != set->size) {
            set->next[temp] = set->empty;
            set->empty = temp;
        }

        // if set is empty reset empty stack
        if (!set->size) {
            set->empty = HASH_SET_SIZE;
        }

        return removed;
    }

    HASH_SET_ASSERT(false && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE); // to have function return
}

/// @brief Creates and returns a union of two sets whose elements are copied into the new set.
/// @param set_one First set structure to unite.
/// @param set_two Second set structure to unite.
/// @param copy Function pointer that creates deep or shallow a copy for united elements.
/// @return New union of set parameters.
static inline hash_set_s union_hash_set(const hash_set_s set_one, const hash_set_s set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one.hash == set_two.hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_one.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_one.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_ASSERT(set_two.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_two.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_two.next && "[ERROR] 'next' pointer is NULL.");


    // initialize union set
    hash_set_s union_set = {
        .elements = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(HASH_SET_DATA_TYPE)),
        .head = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),
        .next = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),

        .hash = set_one.hash, .size = 0, .empty = HASH_SET_SIZE,
    };
    HASH_SET_ASSERT(union_set.elements && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(union_set.head && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(union_set.next && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        union_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one directly into union
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current = set_one.head[i]; current != HASH_SET_SIZE; current = set_one.next[current]) {
            const size_t free_index = union_set.size;

            union_set.elements[free_index] = copy(set_one.elements[current]);
            union_set.size++;

            union_set.next[free_index] = union_set.head[i];
            union_set.head[i] = free_index;
        }
    }

    // copy non-contained elements from set two into union
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_two = set_two.head[i]; current_two != HASH_SET_SIZE; current_two = set_two.next[current_two]) {
            const size_t hash_two = set_two.hash(set_two.elements[current_two]);

            // check if set two's element is contained in union
            bool contains_two = false;
            for (size_t current_union = union_set.head[i]; current_union != HASH_SET_SIZE; current_union = union_set.next[current_union]) {
                if (hash_two == union_set.hash(union_set.elements[current_union])) {
                    contains_two = true;
                    break;
                }
            }

            if (!contains_two) { // if two's element is not contained in union push it into union
                HASH_SET_ASSERT(union_set.size < HASH_SET_SIZE && "[ERROR] Can't insert into full set.");

                const size_t free_index = union_set.size;

                union_set.elements[free_index] = copy(set_two.elements[current_two]);
                union_set.size++;

                union_set.next[free_index] = union_set.head[i];
                union_set.head[i] = free_index;
            }
        }
    }

    return union_set;
}

/// @brief Creates and returns an intersect of two sets whose elements are copied into the new set.
/// @param set_one First set structure to intersect.
/// @param set_two Second set structure to intersect.
/// @param copy Function pointer that creates deep or shallow a copy for intersected elements.
/// @return New intersect of set parameters.
static inline hash_set_s intersect_hash_set(const hash_set_s set_one, const hash_set_s set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one.hash == set_two.hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_one.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_one.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_ASSERT(set_two.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_two.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_two.next && "[ERROR] 'next' pointer is NULL.");

    // initialize intersect set
    hash_set_s intersect_set = {
        .elements = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(HASH_SET_DATA_TYPE)),
        .head = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),
        .next = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),

        .hash = set_one.hash, .size = 0, .empty = HASH_SET_SIZE,
    };
    HASH_SET_ASSERT(intersect_set.elements && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(intersect_set.head && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(intersect_set.next && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        intersect_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one if they're in set two
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_one = set_one.head[i]; current_one != HASH_SET_SIZE; current_one = set_one.next[current_one]) {
            const size_t hash_one = set_one.hash(set_one.elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two.head[i]; current_two != HASH_SET_SIZE; current_two = set_two.next[current_two]) {
                if (hash_one == set_two.hash(set_two.elements[current_two])) {
                    contains_one = true;
                    break;
                }
            }

            // if two contains one's element push copy into intersect
            if (contains_one) {
                const size_t free_index = intersect_set.size;

                intersect_set.elements[free_index] = copy(set_one.elements[current_one]);
                intersect_set.size++;

                intersect_set.next[free_index] = intersect_set.head[i];
                intersect_set.head[i] = free_index;
            }
        }
    }

    return intersect_set;
}

/// @brief Creates and returns a subtraction of two sets whose elements are copied into the new set.
/// @param set_one First set structure that gets subtracted.
/// @param set_two Second set structure that subtracts.
/// @param copy Function pointer that creates deep or shallow a copy for subtracted elements.
/// @return New subtraction of set parameters.
static inline hash_set_s subtract_hash_set(const hash_set_s set_one, const hash_set_s set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one.hash == set_two.hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_one.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_one.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_ASSERT(set_two.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_two.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_two.next && "[ERROR] 'next' pointer is NULL.");

    // initialize subtract set
    hash_set_s subtract_set = {
        .elements = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(HASH_SET_DATA_TYPE)),
        .head = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),
        .next = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),

        .hash = set_one.hash, .size = 0, .empty = HASH_SET_SIZE,
    };
    HASH_SET_ASSERT(subtract_set.elements && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(subtract_set.head && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(subtract_set.next && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        subtract_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one if they're in set two
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_one = set_one.head[i]; current_one != HASH_SET_SIZE; current_one = set_one.next[current_one]) {
            const size_t hash_one = set_one.hash(set_one.elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two.head[i]; current_two != HASH_SET_SIZE; current_two = set_two.next[current_two]) {
                if (hash_one == set_two.hash(set_two.elements[current_two])) {
                    contains_one = true;
                    break;
                }
            }

            // if two doesn't contain one's element push copy into subtract
            if (!contains_one) {
                const size_t free_index = subtract_set.size;

                subtract_set.elements[free_index] = copy(set_one.elements[current_one]);
                subtract_set.size++;

                subtract_set.next[free_index] = subtract_set.head[i];
                subtract_set.head[i] = free_index;
            }
        }
    }

    return subtract_set;
}

/// @brief Creates and returns an exclude (symmetric difference) of two sets whose elements are copied into the new set.
/// @param set_one First set structure to exclude.
/// @param set_two Second set structure to exclude.
/// @param copy Function pointer that creates deep or shallow a copy for exclude elements.
/// @return New exclude of set parameters.
static inline hash_set_s exclude_hash_set(const hash_set_s set_one, const hash_set_s set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one.hash == set_two.hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_one.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_one.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_ASSERT(set_two.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_two.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_two.next && "[ERROR] 'next' pointer is NULL.");

    // initialize exclude set
    hash_set_s exclude_set = {
        .elements = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(HASH_SET_DATA_TYPE)),
        .head = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),
        .next = HASH_SET_ALLOC(HASH_SET_SIZE * sizeof(size_t)),

        .hash = set_one.hash, .size = 0, .empty = HASH_SET_SIZE,
    };
    HASH_SET_ASSERT(exclude_set.elements && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(exclude_set.head && "[ERROR] Memory allocation failed.");
    HASH_SET_ASSERT(exclude_set.next && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        exclude_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one if they're in set two
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        // add each element in one, but not in two
        for (size_t current_one = set_one.head[i]; current_one != HASH_SET_SIZE; current_one = set_one.next[current_one]) {
            const size_t hash_one = set_one.hash(set_one.elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two.head[i]; current_two != HASH_SET_SIZE; current_two = set_two.next[current_two]) {
                if (hash_one == set_two.hash(set_two.elements[current_two])) {
                    contains_one = true;
                    break;
                }
            }

            // if two doesn't contain one's element push copy into subtract
            if (!contains_one) {
                HASH_SET_ASSERT(exclude_set.size < HASH_SET_SIZE && "[ERROR] Can't insert into full set.");

                const size_t free_index = exclude_set.size;

                exclude_set.elements[free_index] = copy(set_one.elements[current_one]);
                exclude_set.size++;

                exclude_set.next[free_index] = exclude_set.head[i];
                exclude_set.head[i] = free_index;
            }
        }

        // add each element in two, but not in one
        for (size_t current_two = set_two.head[i]; current_two != HASH_SET_SIZE; current_two = set_two.next[current_two]) {
            const size_t hash_two = set_two.hash(set_two.elements[current_two]);

            // check if set two contains one's element
            bool contains_two = false;
            for (size_t current_one = set_one.head[i]; current_one != HASH_SET_SIZE; current_one = set_one.next[current_one]) {
                if (hash_two == set_one.hash(set_one.elements[current_one])) {
                    contains_two = true;
                    break;
                }
            }

            // if two doesn't contain one's element push copy into subtract
            if (!contains_two) {
                HASH_SET_ASSERT(exclude_set.size < HASH_SET_SIZE && "[ERROR] Can't insert into full set.");

                const size_t free_index = exclude_set.size;

                exclude_set.elements[free_index] = copy(set_two.elements[current_two]);
                exclude_set.size++;

                exclude_set.next[free_index] = exclude_set.head[i];
                exclude_set.head[i] = free_index;
            }
        }
    }


    return exclude_set;
}

/// @brief Checks if sub is subset of super (sub <= super).
/// @param super Superset to check on.
/// @param sub Subset to check with superset.
/// @return 'true' if sub is subset of superset, 'false' if not.
static inline bool is_subset_hash_set(const hash_set_s super, const hash_set_s sub) {
    HASH_SET_ASSERT(super.hash == sub.hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(super.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(super.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(super.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(super.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(super.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_ASSERT(sub.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(sub.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(sub.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(sub.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(sub.next && "[ERROR] 'next' pointer is NULL.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_sub = sub.head[i]; current_sub != HASH_SET_SIZE; current_sub = sub.next[current_sub]) {
            const size_t hash_sub = sub.hash(sub.elements[current_sub]);

            // check if superset contains subset's element
            bool contains_sub = false;
            for (size_t current_super = super.head[i]; current_super != HASH_SET_SIZE; current_super = super.next[current_super]) {
                if (hash_sub == super.hash(super.elements[current_super])) {
                    contains_sub = true;
                    break;
                }
            }

            if (!contains_sub) {
                return false;
            }
        }
    }

    return true;
}

/// @brief Checks if sub is proper subset of super (sub < super).
/// @param super Superset to check on.
/// @param sub Subset to check with superset.
/// @return 'true' if sub is proper subset of superset, 'false' if not.
static inline bool is_proper_subset_hash_set(const hash_set_s super, const hash_set_s sub) {
    HASH_SET_ASSERT(super.hash == sub.hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(super.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(super.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(super.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(super.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(super.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_ASSERT(sub.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(sub.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(sub.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(sub.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(sub.next && "[ERROR] 'next' pointer is NULL.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_sub = sub.head[i]; current_sub != HASH_SET_SIZE; current_sub = sub.next[current_sub]) {
            const size_t hash_sub = sub.hash(sub.elements[current_sub]);

            // check if superset contains subset's element
            bool contains_sub = false;
            for (size_t current_super = super.head[i]; current_super != HASH_SET_SIZE; current_super = super.next[current_super]) {
                if (hash_sub == sub.hash(sub.elements[current_sub])) {
                    contains_sub = true;
                    break;
                }
            }

            if (!contains_sub) {
                return false;
            }
        }
    }

    return (super.size != sub.size);
}

/// @brief Checks if two sets are disjoint or not, i.e. have no shared elements.
/// @param set_one First set to check.
/// @param set_two Second set to check.
/// @return 'true' if sets are disjoint, 'false' otherwise.
static inline bool is_disjoint_hash_set(const hash_set_s set_one, const hash_set_s set_two) {
    HASH_SET_ASSERT(set_one.hash == set_two.hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_one.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_one.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_one.next && "[ERROR] 'next' pointer is NULL.");

    HASH_SET_ASSERT(set_two.hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two.size <= HASH_SET_SIZE && "[ERROR] Invalid size.");
    HASH_SET_ASSERT(set_two.elements && "[ERROR] 'elements' pointer is NULL.");
    HASH_SET_ASSERT(set_two.head && "[ERROR] 'head' pointer is NULL.");
    HASH_SET_ASSERT(set_two.next && "[ERROR] 'next' pointer is NULL.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_one = set_one.head[i]; current_one != HASH_SET_SIZE; current_one = set_one.next[current_one]) {
            const size_t hash_one = set_one.hash(set_one.elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two.head[i]; current_two != HASH_SET_SIZE; current_two = set_two.next[current_two]) {
                if (hash_one == set_two.hash(set_two.elements[current_two])) {
                    contains_one = true;
                    break;
                }
            }

            if (contains_one) {
                return false;
            }
        }
    }

    return true;
}

#else

#error Cannot include multiple headers in same unit.

#endif // HASH_SET_H
