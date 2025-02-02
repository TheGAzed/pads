#ifndef FORWARD_FORWARD_FORWARD_LIST_H
#define FORWARD_FORWARD_FORWARD_LIST_H

#include <stdlib.h>  // imports size_t, malloc, realloc, free
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy, memmove

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


// list mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_ALLOCATED_FORWARD_LIST  0x10
#define FINITE_ALLOCATED_FORWARD_LIST    0x11
#define INFINITE_REALLOC_FORWARD_LIST    0x12
#define FINITE_PRERPOCESSOR_FORWARD_LIST 0x13

#define INFINITE_FORWARD_LIST INFINITE_ALLOCATED_FORWARD_LIST
#define FINITE_FORWARD_LIST   FINITE_ALLOCATED_FORWARD_LIST

#define FORWARD_LIST_MODE INFINITE_ALLOCATED_FORWARD_LIST
//#define FORWARD_LIST_MODE FINITE_ALLOCATED_FORWARD_LIST
//#define FORWARD_LIST_MODE INFINITE_REALLOC_FORWARD_LIST
//#define FORWARD_LIST_MODE FINITE_PRERPOCESSOR_FORWARD_LIST
// List mode that can be set to INFINITE_ALLOCATED_FORWARD_LIST, FINITE_ALLOCATED_FORWARD_LIST, INFINITE_REALLOC_FORWARD_LIST or
// FINITE_PRERPOCESSOR_FORWARD_LIST, or INFINITE_ALLOCATED_FORWARD_LIST or FINITE_ALLOCATED_FORWARD_LIST
// Default: INFINITE_ALLOCATED_FORWARD_LIST
#ifndef FORWARD_LIST_MODE

#define FORWARD_LIST_MODE INFINITE_ALLOCATED_FORWARD_LIST

#endif

#define IS_INFINITE_FORWARD_LIST (FORWARD_LIST_MODE & 0x01)

// Check to make sure a valid list mode is selected.
#if (FORWARD_LIST_MODE != INFINITE_ALLOCATED_FORWARD_LIST) && (FORWARD_LIST_MODE != FINITE_ALLOCATED_FORWARD_LIST)    && \
(FORWARD_LIST_MODE != INFINITE_REALLOC_FORWARD_LIST)   && (FORWARD_LIST_MODE != FINITE_PRERPOCESSOR_FORWARD_LIST)

#error Invalid type of list mode.

#endif

// List data type to specify what datatype to list.
// DEFAULT: void *
#ifndef FORWARD_LIST_DATA_TYPE

#define FORWARD_LIST_DATA_TYPE void*

#endif

#ifndef FORWARD_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
#define FORWARD_LIST_ASSERT assert

#endif

#ifndef FORWARD_LIST_ALLOC

#define FORWARD_LIST_ALLOC malloc

#endif

#ifndef FORWARD_LIST_REALLOC

#define FORWARD_LIST_REALLOC realloc

#endif

#ifndef FORWARD_LIST_FREE

#define FORWARD_LIST_FREE free

#endif

typedef FORWARD_LIST_DATA_TYPE (*copy_forward_list_fn)    (const FORWARD_LIST_DATA_TYPE);
typedef void                   (*destroy_forward_list_fn) (FORWARD_LIST_DATA_TYPE *);
typedef int                    (*compare_forward_list_fn) (const void *, const void *);
typedef bool                   (*operate_forward_list_fn) (FORWARD_LIST_DATA_TYPE *, void *);
typedef void                   (*sort_forward_list_fn)    (void *, size_t, size_t, compare_forward_list_fn);

#if   FORWARD_LIST_MODE == INFINITE_ALLOCATED_FORWARD_LIST

struct forward_list_node {
    FORWARD_LIST_DATA_TYPE element;
    struct forward_list_node * next;
};

typedef struct forward_list {
    size_t size;
    struct forward_list_node * tail;
} forward_list_s;

static inline forward_list_s create_forward_list(void) {
    return (forward_list_s) { 0 };
}

static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct forward_list_node * previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(&(previous->element));
        }

        struct forward_list_node * temp = previous;
        previous = previous->next;
        FORWARD_LIST_FREE(temp);
    }

    *list = (forward_list_s) { 0 };
}

static inline void insert_at_forward_list(forward_list_s * list, const size_t index, const FORWARD_LIST_DATA_TYPE element) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    FORWARD_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    struct forward_list_node * temp = FORWARD_LIST_ALLOC(sizeof(struct forward_list_node));
    FORWARD_LIST_ASSERT(temp && "[ERROR] Memory allocation failed.");
    memcpy(&(temp->element), &element, sizeof(FORWARD_LIST_DATA_TYPE));

    if (list->tail == NULL) {
        list->tail = temp->next = temp;
    } else if (index == list->size) {
        temp->next = list->tail->next;
        list->tail = list->tail->next = temp;
    } else {
        struct forward_list_node * previous = list->tail;
        for (size_t i = 0; i < index; ++i) {
            previous = previous->next;
        }
        temp->next = previous->next;
        previous->next = temp;
    }

    list->size++;
}

static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");

    struct forward_list_node * previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        struct forward_list_node * current = previous->next;

        const int comparison = compare ? compare(&(current->element), &element) : memcmp(&(current->element), &element, sizeof(FORWARD_LIST_DATA_TYPE));
        if (0 == comparison) {
            list->size--;
            FORWARD_LIST_DATA_TYPE found = current->element;

            if (current == list->tail) { // if current is the last element
                list->tail = (list->size) ? previous : NULL; // if list still has elements then tail will become the previous pointer else NULL
            }
            previous->next = current->next;
            FORWARD_LIST_FREE(current);

            return found;
        }
        previous = previous->next;
    }

    FORWARD_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}


static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct forward_list_node * previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = previous->next;
    }
    struct forward_list_node * current = previous->next;

    list->size--;
    FORWARD_LIST_DATA_TYPE found = current->element;

    previous->next = current->next;

    FORWARD_LIST_FREE(current);

    if (index == list->size) { // if last element is removed
        list->tail = (list->size) ? previous : NULL; // if list is not empty tail/last node becomes previous, else NULL
    }

    return found;
}

static inline void reverse_forward_list(forward_list_s * list) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    if (list->tail == NULL) {
        return;
    }

    struct forward_list_node * current = list->tail;
    struct forward_list_node * current_next = current->next;
    struct forward_list_node * current_next_next = current_next->next;
    list->tail = current_next;
    for (size_t i = 0; i < list->size; ++i) {
        current_next->next = current;
        current = current_next;
        current_next = current_next_next;
        current_next_next = current_next_next->next;
    }
}


static inline void shift_next_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->tail && (s < shift); ++s) {
        list->tail = list->tail->next;
    }
}

static inline forward_list_s splice_forward_list(forward_list_s * restrict list_one, forward_list_s * restrict list_two, const size_t index) {
    FORWARD_LIST_ASSERT(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(list_one != list_two && "[ERROR] Lists can't be the same.");
    FORWARD_LIST_ASSERT(index <= list_one->size && "[ERROR] index can't exceed list_one's size");

    struct forward_list_node * previous = list_one->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = previous->next;
    }

    if (previous && list_two->tail) {
        struct forward_list_node * current = previous->next;

        struct forward_list_node * first_one = current;
        struct forward_list_node * last_one  = previous;

        struct forward_list_node * first_two = list_two->tail->next;
        struct forward_list_node * last_two  = list_two->tail;

        last_one->next = first_two;
        last_two->next = first_one;
    }

    const forward_list_s list = {
        .size = list_one->size + list_two->size,
        .tail = (index != list_one->size - 1 || !list_two->size) ? list_one->tail : list_two->tail,
    };

    *list_one = *list_two = (forward_list_s) { 0 };

    return list;
}

static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size) {
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) {
        return (forward_list_s) { 0 };
    }

    struct forward_list_node * index_node_previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        index_node_previous = index_node_previous->next;
    }

    struct forward_list_node * size_node = index_node_previous;
    for (size_t i = 0; i < size; ++i) {
        size_node = size_node->next;
    }

    if ((index + size) >= list->size) {
        list->tail = index_node_previous;
    }

    list->size -= size;
    if (!list->size) {
        list->tail = NULL;
    }

    struct forward_list_node * first_list = size_node->next;
    struct forward_list_node * last_list  = index_node_previous;

    struct forward_list_node * first_split = index_node_previous->next;
    struct forward_list_node * last_split  = size_node;

    last_list->next = first_list;
    last_split->next = first_split;

    return (forward_list_s) { .tail = last_split, .size = size };
}

static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.tail && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct forward_list_node const * current = list.tail;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->element;
}

static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

static inline bool is_full_forward_list(const forward_list_s list) {
    return !(~list.size);
}

static inline forward_list_s copy_forward_list(const forward_list_s list, const copy_forward_list_fn copy) {
    forward_list_s list_copy = { .tail = NULL, .size = list.size };

    struct forward_list_node const * previous_list = list.tail;
    struct forward_list_node ** previous_copy = &(list_copy.tail);
    for (size_t i = 0; i < list.size; ++i) {
        struct forward_list_node * temp = FORWARD_LIST_ALLOC(sizeof(struct forward_list_node));
        FORWARD_LIST_ASSERT(temp && "[ERROR] Memory allocation failed");
        temp->element = copy ? copy(previous_list->element) : previous_list->element;

        (*previous_copy) = temp;
        temp->next = list_copy.tail;

        previous_list = previous_list->next;
        previous_copy = &((*previous_copy)->next);
    }

    return list_copy;
}

static inline void sort_forward_list(forward_list_s const * list, const sort_forward_list_fn sort, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    FORWARD_LIST_ASSERT(sort && "[ERROR] 'sort' parameter pointer is NULL");

    FORWARD_LIST_DATA_TYPE * elements_array = FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * list->size);
    FORWARD_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct forward_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = previous->element;
        previous = previous->next;
    }

    sort(elements_array, list->size, sizeof(FORWARD_LIST_DATA_TYPE), compare);

    previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next;
        previous->element = elements_array[i];
    }
    FORWARD_LIST_FREE(elements_array);
}

static inline void foreach_forward_list(const forward_list_s * list, const operate_forward_list_fn operate, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct forward_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next;

        if (!operate(&previous->element, args)) {
            return;
        }
    }
}

#elif FORWARD_LIST_MODE == FINITE_ALLOCATED_FORWARD_LIST
#elif FORWARD_LIST_MODE == INFINITE_REALLOC_FORWARD_LIST
#elif FORWARD_LIST_MODE == FINITE_PRERPOCESSOR_FORWARD_LIST
#endif

#endif //FORWARD_FORWARD_FORWARD_LIST_H
