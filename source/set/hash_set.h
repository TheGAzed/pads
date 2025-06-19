#ifndef HASH_SET_H
#define HASH_SET_H

#include <stddef.h>  // imports size_t
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy
#include <stdlib.h>  // imports exit

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

#ifndef HASH_SET_DATA_TYPE

/// @brief To change, use: #define HASH_SET_DATA_TYPE [type].
#define HASH_SET_DATA_TYPE void*

#endif

#ifndef HASH_SET_ASSERT

#include <assert.h>  // imports assert for debugging

/// @brief To change, use: #define HASH_SET_ASSERT [assert].
#define HASH_SET_ASSERT assert

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

#ifndef HASH_SET_SIZE

#define HASH_SET_SIZE (1 << 10)

#elif HASH_SET_SIZE <= 0

#error 'HASH_SET_SIZE' cannot be zero

#endif

typedef struct hash_set {
    hash_set_fn hash;
    size_t next[HASH_SET_SIZE];
    size_t head[HASH_SET_SIZE];
    size_t size, empty;
    HASH_SET_DATA_TYPE elements[HASH_SET_SIZE];
} hash_set_s;

static inline hash_set_s create_hash_set(const hash_set_fn hash) {
    HASH_SET_ASSERT(hash && "[ERROR] 'hash' parameter is NULL.");

    hash_set_s set = { .hash = hash, .size = 0, .empty = HASH_SET_SIZE, };

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        set.head[i] = HASH_SET_SIZE;
    }

    return set;
}

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
}

static inline void clear_hash_set(hash_set_s * set, const destroy_hash_set_fn destroy) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t * current = set->head + i; HASH_SET_SIZE != (*current); (*current) = set->next[(*current)]) {
            destroy(set->elements + (*current));
        }
    }

    set->size = 0;
}

static inline hash_set_s copy_hash_set(const hash_set_s * set, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    hash_set_s replica = { .empty = HASH_SET_SIZE, .hash = set->hash, .size = 0, };
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        replica.head[i] = HASH_SET_SIZE;

        for (size_t current = set->head[i]; HASH_SET_SIZE != current; current = set->next[current]) {
            const size_t free_index = replica.size;

            replica.elements[free_index] = copy(set->elements[current]);
            replica.size++;

            replica.next[free_index] = replica.head[i];
            replica.head[i] = free_index;
        }
    }

    return replica;
}

static inline bool is_empty_hash_set(const hash_set_s * set) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    return !(set->size);
}

static inline bool is_full_hash_set(const hash_set_s * set) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    return (HASH_SET_SIZE == set->size);
}

static inline void foreach_hash_set(hash_set_s * set, const operate_hash_set_fn operate, void * args) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    for (size_t i = 0; i < HASH_SET_SIZE; i++) {
        for (size_t current = set->head[i]; HASH_SET_SIZE != current && operate(set->elements + current, args); ) {
            current = set->next[current];
        }
    }
}

static inline void map_hash_set(hash_set_s * set, const manage_hash_set_fn manage, void * args) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_DATA_TYPE elements[HASH_SET_SIZE];
    for (size_t i = 0, index = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current = set->head[i]; HASH_SET_SIZE != current; current = set->next[current]) {
            elements[index++] = set->elements[current];
        }
    }

    manage(elements, set->size, args);

    for (size_t i = 0, index = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current = set->head[i]; HASH_SET_SIZE != current; current = set->next[current]) {
            set->elements[current] = elements[index++];
        }
    }
}

static inline bool contains_hash_set(const hash_set_s * set, const HASH_SET_DATA_TYPE element) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    const size_t element_hash = set->hash(element);
    const size_t element_modulo = element_hash % HASH_SET_SIZE;
    HASH_SET_ASSERT(element_modulo < HASH_SET_SIZE && "[ERROR] Normalized value out of bounds.");

    for (size_t current = set->head[element_modulo]; HASH_SET_SIZE != current; current = set->next[current]) {
        if (element_hash == set->hash(set->elements[current])) {
            return true;
        }
    }

    return false;
}

static inline void insert_hash_set(hash_set_s * set, const HASH_SET_DATA_TYPE element) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(set->size < HASH_SET_SIZE && "[ERROR] Can't insert into full set.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

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

static inline HASH_SET_DATA_TYPE remove_hash_set(hash_set_s * set, const HASH_SET_DATA_TYPE element) {
    HASH_SET_ASSERT(set && "[ERROR] 'set' parameter is NULL.");
    HASH_SET_ASSERT(set->size && "[ERROR] Can't remove from empty set.");

    HASH_SET_ASSERT(set->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    const size_t element_hash = set->hash(element);
    const size_t element_modulo = element_hash % HASH_SET_SIZE;
    HASH_SET_ASSERT(element_modulo < HASH_SET_SIZE && "[ERROR] Normalized value out of bounds.");

    // check if element is in set or not
    for (size_t * current = set->head + element_modulo; HASH_SET_SIZE != (*current); current = set->next + (*current)) {
        if (element_hash != set->hash(set->elements[(*current)])) {
            continue;
        }

        const size_t temp = (*current);

        // temporary save removed element
        HASH_SET_DATA_TYPE removed = set->elements[temp];
        set->size--;

        // change current index to next
        (*current) = set->next[temp];

        // minimize holes by checking if current is rightmost element in list
        if (temp != set->size) {
            set->next[temp] = set->empty;
            set->empty = temp;
        }

        return removed;
    }

    HASH_SET_ASSERT(false && "[ERROR] Set does not contain element.");
    exit(EXIT_FAILURE); // to have function return
}

static inline hash_set_s union_hash_set(const hash_set_s * set_one, const hash_set_s * set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    HASH_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one->hash == set_two->hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_ASSERT(set_two->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    // initialize union set
    hash_set_s union_set = { .empty = HASH_SET_SIZE, .hash = set_one->hash, .size = 0, };
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        union_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one directly into union
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current = set_one->head[i]; current != HASH_SET_SIZE; current = set_one->next[current]) {
            const size_t free_index = union_set.size;

            union_set.elements[free_index] = copy(set_one->elements[current]);
            union_set.size++;

            union_set.next[free_index] = union_set.head[i];
            union_set.head[i] = free_index;
        }
    }

    // copy non-contained elements from set two into union
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_two = set_two->head[i]; current_two != HASH_SET_SIZE; current_two = set_two->next[current_two]) {
            const size_t hash_two = set_two->hash(set_two->elements[current_two]);

            // check if set two's element is contained in union
            bool contains_two = false;
            for (size_t current_union = union_set.head[i]; current_union != HASH_SET_SIZE; current_union = union_set.next[current_union]) {
                if (hash_two == union_set.hash(union_set.elements[current_union])) {
                    contains_two = true;
                    break;
                }
            }

            if (!contains_two) { // if two's element is not contained in union push it into union
                const size_t free_index = union_set.size;

                union_set.elements[free_index] = copy(set_two->elements[current_two]);
                union_set.size++;

                union_set.next[free_index] = union_set.head[i];
                union_set.head[i] = free_index;
            }
        }
    }

    return union_set;
}

static inline hash_set_s intersect_hash_set(const hash_set_s * set_one, const hash_set_s * set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    HASH_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one->hash == set_two->hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_ASSERT(set_two->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    // initialize intersect set
    hash_set_s intersect_set = { .empty = HASH_SET_SIZE, .hash = set_one->hash, .size = 0, };
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        intersect_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one if they're in set two
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_one = set_one->head[i]; current_one != HASH_SET_SIZE; current_one = set_one->next[current_one]) {
            const size_t hash_one = set_one->hash(set_one->elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two->head[i]; current_two != HASH_SET_SIZE; current_two = set_two->next[current_two]) {
                if (hash_one == set_two->hash(set_two->elements[current_two])) {
                    contains_one = true;
                    break;
                }
            }

            // if two contains one's element push copy into intersect
            if (contains_one) {
                const size_t free_index = intersect_set.size;

                intersect_set.elements[free_index] = copy(set_one->elements[current_one]);
                intersect_set.size++;

                intersect_set.next[free_index] = intersect_set.head[i];
                intersect_set.head[i] = free_index;
            }
        }
    }

    return intersect_set;
}

static inline hash_set_s subtract_hash_set(const hash_set_s * set_one, const hash_set_s * set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    HASH_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one->hash == set_two->hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_ASSERT(set_two->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    // initialize subtract set
    hash_set_s subtract_set = { .empty = HASH_SET_SIZE, .hash = set_one->hash, .size = 0, };
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        subtract_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one if they're in set two
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_one = set_one->head[i]; current_one != HASH_SET_SIZE; current_one = set_one->next[current_one]) {
            const size_t hash_one = set_one->hash(set_one->elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two->head[i]; current_two != HASH_SET_SIZE; current_two = set_two->next[current_two]) {
                if (hash_one == set_two->hash(set_two->elements[current_two])) {
                    contains_one = true;
                    break;
                }
            }

            // if two doesn't contain one's element push copy into subtract
            if (!contains_one) {
                const size_t free_index = subtract_set.size;

                subtract_set.elements[free_index] = copy(set_one->elements[current_one]);
                subtract_set.size++;

                subtract_set.next[free_index] = subtract_set.head[i];
                subtract_set.head[i] = free_index;
            }
        }
    }

    return subtract_set;
}

static inline hash_set_s exclude_hash_set(const hash_set_s * set_one, const hash_set_s * set_two, const copy_hash_set_fn copy) {
    HASH_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    HASH_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    HASH_SET_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");
    HASH_SET_ASSERT(set_one->hash == set_two->hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_ASSERT(set_two->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    // initialize exclude set
    hash_set_s exclude_set = { .empty = HASH_SET_SIZE, .hash = set_one->hash, .size = 0, };
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        exclude_set.head[i] = HASH_SET_SIZE;
    }

    // copy elements from set one if they're in set two
    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        // add each element in one, but not in two
        for (size_t current_one = set_one->head[i]; current_one != HASH_SET_SIZE; current_one = set_one->next[current_one]) {
            const size_t hash_one = set_one->hash(set_one->elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two->head[i]; current_two != HASH_SET_SIZE; current_two = set_two->next[current_two]) {
                if (hash_one == set_two->hash(set_two->elements[current_two])) {
                    contains_one = true;
                    break;
                }
            }

            // if two doesn't contain one's element push copy into subtract
            if (!contains_one) {
                const size_t free_index = exclude_set.size;

                exclude_set.elements[free_index] = copy(set_one->elements[current_one]);
                exclude_set.size++;

                exclude_set.next[free_index] = exclude_set.head[i];
                exclude_set.head[i] = free_index;
            }
        }

        // add each element in two, but not in one
        for (size_t current_two = set_two->head[i]; current_two != HASH_SET_SIZE; current_two = set_two->next[current_two]) {
            const size_t hash_two = set_two->hash(set_two->elements[current_two]);

            // check if set two contains one's element
            bool contains_two = false;
            for (size_t current_one = set_one->head[i]; current_one != HASH_SET_SIZE; current_one = set_one->next[current_one]) {
                if (hash_two == set_one->hash(set_one->elements[current_one])) {
                    contains_two = true;
                    break;
                }
            }

            // if two doesn't contain one's element push copy into subtract
            if (!contains_two) {
                const size_t free_index = exclude_set.size;

                exclude_set.elements[free_index] = copy(set_two->elements[current_two]);
                exclude_set.size++;

                exclude_set.next[free_index] = exclude_set.head[i];
                exclude_set.head[i] = free_index;
            }
        }
    }


    return exclude_set;
}

static inline bool is_subset_hash_set(const hash_set_s * super, const hash_set_s * sub) {
    HASH_SET_ASSERT(super && "[ERROR] 'super' parameter is NULL.");
    HASH_SET_ASSERT(sub && "[ERROR] 'sub' parameter is NULL.");
    HASH_SET_ASSERT(super->hash == sub->hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(super->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(super->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_ASSERT(sub->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(sub->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_sub = sub->head[i]; current_sub != HASH_SET_SIZE; current_sub = sub->next[current_sub]) {
            const size_t hash_sub = sub->hash(sub->elements[current_sub]);

            // check if set super contains sub's element
            bool contains_sub = false;
            for (size_t current_super = super->head[i]; current_super != HASH_SET_SIZE; current_super = super->next[current_super]) {
                if (hash_sub == super->hash(super->elements[current_super])) {
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

static inline bool is_proper_subset_hash_set(const hash_set_s * super, const hash_set_s * sub) {
    HASH_SET_ASSERT(super && "[ERROR] 'super' parameter is NULL.");
    HASH_SET_ASSERT(sub && "[ERROR] 'sub' parameter is NULL.");
    HASH_SET_ASSERT(super->hash == sub->hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(super->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(super->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_ASSERT(sub->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(sub->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_sub = sub->head[i]; current_sub != HASH_SET_SIZE; current_sub = sub->next[current_sub]) {
            const size_t hash_sub = sub->hash(sub->elements[current_sub]);

            // check if set super contains sub's element
            bool contains_sub = false;
            for (size_t current_super = super->head[i]; current_super != HASH_SET_SIZE; current_super = super->next[current_super]) {
                if (hash_sub == sub->hash(sub->elements[current_sub])) {
                    contains_sub = true;
                    break;
                }
            }

            if (!contains_sub) {
                return false;
            }
        }
    }

    return (super->size != sub->size);
}

static inline bool is_disjoint_hash_set(const hash_set_s * set_one, const hash_set_s * set_two) {
    HASH_SET_ASSERT(set_one && "[ERROR] 'set_one' parameter is NULL.");
    HASH_SET_ASSERT(set_two && "[ERROR] 'set_two' parameter is NULL.");
    HASH_SET_ASSERT(set_one->hash == set_two->hash && "[ERROR] Hash functions are not the same.");

    HASH_SET_ASSERT(set_one->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_one->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    HASH_SET_ASSERT(set_two->hash && "[ERROR] Hash function is NULL.");
    HASH_SET_ASSERT(set_two->size <= HASH_SET_SIZE && "[ERROR] Invalid size.");

    for (size_t i = 0; i < HASH_SET_SIZE; ++i) {
        for (size_t current_one = set_one->head[i]; current_one != HASH_SET_SIZE; current_one = set_one->next[current_one]) {
            const size_t hash_one = set_one->hash(set_one->elements[current_one]);

            // check if set two contains one's element
            bool contains_one = false;
            for (size_t current_two = set_two->head[i]; current_two != HASH_SET_SIZE; current_two = set_two->next[current_two]) {
                if (hash_one == set_two->hash(set_two->elements[current_two])) {
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
