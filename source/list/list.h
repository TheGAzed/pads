#ifndef LIST_H
#define LIST_H

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
#define INFINITE_ALLOCATED_LIST  0xC
#define FINITE_ALLOCATED_LIST    0xD
#define INFINITE_REALLOC_LIST    0xE
#define FINITE_PRERPOCESSOR_LIST 0xF

#define INFINITE_LIST INFINITE_ALLOCATED_LIST
#define FINITE_LIST   FINITE_ALLOCATED_LIST

//#define LIST_MODE INFINITE_ALLOCATED_LIST
//#define LIST_MODE FINITE_ALLOCATED_LIST
//#define LIST_MODE INFINITE_REALLOC_LIST
//#define LIST_MODE FINITE_PRERPOCESSOR_LIST
// List mode that can be set to INFINITE_ALLOCATED_LIST, FINITE_ALLOCATED_LIST, INFINITE_REALLOC_LIST or
// FINITE_PRERPOCESSOR_LIST, or INFINITE_ALLOCATED_LIST or FINITE_ALLOCATED_LIST
// Default: INFINITE_ALLOCATED_LIST
#ifndef LIST_MODE

#define LIST_MODE INFINITE_ALLOCATED_LIST

#endif

#define IS_INFINITE_LIST (LIST_MODE & 0x01)

// Check to make sure a valid list mode is selected.
#if (LIST_MODE != INFINITE_ALLOCATED_LIST) && (LIST_MODE != FINITE_ALLOCATED_LIST)    && \
    (LIST_MODE != INFINITE_REALLOC_LIST)   && (LIST_MODE != FINITE_PRERPOCESSOR_LIST)

#error Invalid type of list mode.

#endif

// List data type to specify what datatype to list.
// DEFAULT: void *
#ifndef LIST_DATA_TYPE

#define LIST_DATA_TYPE void*

#endif

#ifndef LIST_ASSERT

#include <assert.h>  // imports assert for debugging
#define LIST_ASSERT assert

#endif

#ifndef LIST_ALLOC

#define LIST_ALLOC malloc

#endif

#ifndef LIST_REALLOC

#define LIST_REALLOC realloc

#endif

#ifndef LIST_FREE

#define LIST_FREE free

#endif

typedef LIST_DATA_TYPE (*copy_list_fn)    (const LIST_DATA_TYPE);
typedef void           (*destroy_list_fn) (LIST_DATA_TYPE *);
typedef int            (*compare_list_fn) (const void *, const void *);
typedef bool           (*operate_list_fn) (LIST_DATA_TYPE *, void *);
typedef void           (*sort_list_fn)    (void *, size_t, size_t, compare_list_fn);

#if   LIST_MODE == INFINITE_ALLOCATED_LIST

struct list_node {
    LIST_DATA_TYPE element;
    struct list_node * next;
    struct list_node * prev;
};

typedef struct list {
    size_t size;
    struct list_node * head;
} list_s;

static inline list_s create_list(void) {
    return (list_s) { 0 };
}

static inline void destroy_list(list_s * list, const destroy_list_fn destroy) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct list_node * current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(&(current->element));
        }

        struct list_node * temp = current;
        current = current->next;
        LIST_FREE(temp);
    }

    *list = (list_s) { 0 };
}

static inline void insert_at_list(list_s * list, const size_t index, const LIST_DATA_TYPE element) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    struct list_node * temp = LIST_ALLOC(sizeof(struct list_node));
    LIST_ASSERT(temp && "[ERROR] Memory allocation failed.");
    memcpy(&(temp->element), &element, sizeof(LIST_DATA_TYPE));

    struct list_node * current = list->head;
    if (index < (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = current->prev;
        }
    }

    if (list->head) {
        temp->next = current;
        temp->prev = current->prev;

        current->prev->next = temp;
        current->prev = temp;
    } else {
        list->head = temp->next = temp->prev = temp;
    }

    if (!index) {
        list->head = temp;
    }

    list->size++;
}

static inline LIST_DATA_TYPE remove_first_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    struct list_node ** current = &(list->head);
    for (size_t s = 0; s < list->size; ++s) {
        const int comparison = compare ? compare(&((*current)->element), &element) : memcmp(&((*current)->element), &element, sizeof(LIST_DATA_TYPE));
        if (0 == comparison) {
            LIST_DATA_TYPE found = (*current)->element;

            struct list_node * temp = *current;
            (*current)->next->prev = (*current)->prev;
            (*current)->prev->next = (*current)->next; // changes next pointer in previous node because current may not change it if pointing to head
            *current = (--list->size) ? (*current)->next : NULL; // changes head pointer to next if pointing to it
            LIST_FREE(temp);

            return found;
        }
        current = &((*current)->next);
    }

    LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_last_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    struct list_node * current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        current = current->prev;

        const int comparison = compare ? compare(&(current->element), &element) : memcmp(&(current->element), &element, sizeof(LIST_DATA_TYPE));
        if (0 != comparison) {
            continue;
        }

        LIST_DATA_TYPE found = current->element;
        list->size--;

        current->next->prev = current->prev;
        current->prev->next = current->next;

        if (current == list->head) {
            list->head = (list->size) ? current->next : NULL;
        }

        LIST_FREE(current);

        return found;
    }

    LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct list_node * temp = NULL;
    if (index < (list->size >> 1)) { // special case when index is 0 so head must change to next
        struct list_node ** current = &(list->head);
        for (size_t i = 0; i < index; ++i) {
            current = &((*current)->next);
        }

        temp = *current;
        *current = (*current)->next;
    } else { // head might change if size is one, but since the list is circular temp will point to head after loop
        temp = list->head;
        for (size_t i = 0; i < list->size - index; ++i) {
            temp = temp->prev;
        }
    }

    LIST_DATA_TYPE found = temp->element;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    LIST_FREE(temp);

    list->size--;

    if (!list->size) {
        list->head = NULL;
    }

    return found;
}

static inline void reverse_list(list_s * list) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct list_node * current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        list->head = current;

        struct list_node * temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        current = current->prev;
    }
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->head && (s < shift); ++s) {
        list->head = list->head->next;
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->head && (s < shift); ++s) {
        list->head = list->head->prev;
    }
}

static inline list_s splice_list(list_s * restrict list_one, list_s * restrict list_two, const size_t index) {
    LIST_ASSERT(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    LIST_ASSERT(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");
    LIST_ASSERT(list_one != list_two && "[ERROR] Lists can't be the same.");
    LIST_ASSERT(index <= list_one->size && "[ERROR] index can't exceed list_one's size");

    struct list_node * current = list_one->head;
    if (index < (list_one->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        for (size_t i = 0; i < list_one->size - index; ++i) {
            current = current->prev;
        }
    }

    if (current && list_two->head) {
        struct list_node * first_one = current;
        struct list_node * last_one  = current->prev;

        struct list_node * first_two = list_two->head;
        struct list_node * last_two  = list_two->head->prev;

        last_one->next = first_two;
        first_two->prev = last_one;

        last_two->next = first_one;
        first_one->prev = last_two;
    }

    const list_s list = {
        .size = list_one->size + list_two->size,
        .head = (index || !list_two->size) ? list_one->head : list_two->head,
    };

    *list_one = *list_two = (list_s) { 0 };

    return list;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size) {
    LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) {
        return (list_s) { 0 };
    }

    struct list_node * index_node = list->head;
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) { index_node = index_node->next; }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) { index_node = index_node->prev; }
    }

    struct list_node * size_node = index_node;
    if (size <= (list->size >> 1)) {
        for (size_t i = 0; i < size - 1; ++i) { size_node = size_node->next; }
    } else {
        for (size_t i = 0; i < list->size - size + 1; ++i) { size_node = size_node->prev; }
    }

    if (!index || ((index + size) >= list->size)) {
        list->head = size_node->next;
    }

    list->size -= size;
    if (!list->size) {
        list->head = NULL;
    }

    struct list_node * first_list = size_node->next;
    struct list_node * last_list  = index_node->prev;

    struct list_node * first_split = index_node;
    struct list_node * last_split  = size_node;

    first_list->prev = last_list;
    last_list->next = first_list;

    first_split->prev = last_split;
    last_split->next = first_split;

    return (list_s) { .head = first_split, .size = size };
}

static inline LIST_DATA_TYPE get_list(const list_s list, const size_t index) {
    LIST_ASSERT(list.head && "[ERROR] Can't get element from empty list.");
    LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct list_node const * current = list.head;
    if (index < (list.size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        for (size_t i = 0; i < list.size - index; ++i) {
            current = current->prev;
        }
    }

    return current->element;
}

static inline bool is_empty_list(const list_s list) {
    return (list.size == 0);
}

static inline bool is_full_list(const list_s list) {
    return !(~list.size);
}

static inline list_s copy_list(const list_s list, const copy_list_fn copy) {
    list_s list_copy = { .head = NULL, .size = list.size };

    struct list_node const * current_list = list.head;
    struct list_node ** current_copy = &(list_copy.head);
    for (size_t i = 0; i < list.size; ++i) {
        struct list_node * temp = LIST_ALLOC(sizeof(struct list_node));
        LIST_ASSERT(temp && "[ERROR] Memory allocation failed");
        temp->element = copy ? copy(current_list->element) : current_list->element;

        (*current_copy) = temp->prev = temp; // *current_copy and temp's prev will point to temp
        temp->next = list_copy.head; // temp's next points to head (if *current_copy is head then temp's next points to temp)
        // temp's prev points to list_copy.head's prev (if *current_copy is head then head/temp->prev is temp, else temp->prev is previous node)
        temp->prev = list_copy.head->prev;
        list_copy.head->prev = temp; // head's prev points to temp (if *current_copy is head then head/temp prev is temp, else head prev is last node)

        current_list = current_list->next;
        current_copy = &((*current_copy)->next);
    }

    return list_copy;
}

static inline void sort_list(list_s const * list, const sort_list_fn sort, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    LIST_ASSERT(sort && "[ERROR] 'sort' parameter pointer is NULL");

    LIST_DATA_TYPE * elements_array = LIST_ALLOC(sizeof(LIST_DATA_TYPE) * list->size);
    LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = current->element;
        current = current->next;
    }

    sort(elements_array, list->size, sizeof(LIST_DATA_TYPE), compare);

    current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current->element = elements_array[i];
        current = current->next;
    }
    LIST_FREE(elements_array);
}

static inline void foreach_list(const list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&current->element, args)) {
            return;
        }

        current = current->next;
    }
}

static inline void foreach_reverse_list(const list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = current->prev;

        if (!operate(&current->element, args)) {
            return;
        }
    }
}

#elif LIST_MODE == FINITE_ALLOCATED_LIST

#define NODE_COUNT 2
#define NEXT_IDX   0
#define PREV_IDX   1
typedef struct list {
    size_t size, max, head;

    LIST_DATA_TYPE * elements;
    size_t * node[NODE_COUNT];
} list_s;

static inline list_s create_list(const size_t max) {
    LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const list_s list = {
        .elements = LIST_ALLOC(sizeof(LIST_DATA_TYPE) * max),
        .node[NEXT_IDX] = LIST_ALLOC(sizeof(size_t) * max), .node[PREV_IDX] = LIST_ALLOC(sizeof(size_t) * max),

        .head = 0, .max = max, .size = 0,
    };

    LIST_ASSERT(list.elements && "[ERROR] Memory allocation failed.");
    LIST_ASSERT(list.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    LIST_ASSERT(list.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    return list;
}

static inline void destroy_list(list_s * list, const destroy_list_fn destroy) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy && (s < list->size); ++s) {
        destroy(list->elements + current);
        current = list->node[NEXT_IDX][current];
    }

    LIST_FREE(list->elements);
    LIST_FREE(list->node[NEXT_IDX]);
    LIST_FREE(list->node[PREV_IDX]);

    *list = (list_s) { 0 };
}

static inline void insert_at_list(list_s * list, const size_t index, const LIST_DATA_TYPE element) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size < list->max && "[ERROR] List reached maximum size.");
    LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t current = list->head;

    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    list->node[NEXT_IDX][list->size] = current;
    list->node[PREV_IDX][list->size] = list->node[PREV_IDX][current];

    list->node[PREV_IDX][current] = list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->size;
    if (!index) {
        list->head = list->size;
    }

    memcpy(list->elements + list->size, &element, sizeof(LIST_DATA_TYPE));
    list->size++;
}

static inline LIST_DATA_TYPE remove_first_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[NEXT_IDX] && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[PREV_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
		const int comparison = compare ? compare(&(list->elements[current]), &element) : memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE));
        if (0 != comparison) {
            current = list->node[NEXT_IDX][current];
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[NEXT_IDX][current] == list->size - 1) ? current : list->node[NEXT_IDX][current];
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        // move element at list->size - 1 to current's position to avoid 'holes' in array.
        list->size--;
        list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
        list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return found;
    }

    LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_last_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[NEXT_IDX] && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[PREV_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        current = list->node[PREV_IDX][current];

		const int comparison = compare ? compare(&(list->elements[current]), &element) : memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE));
        if (0 != comparison) {
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[NEXT_IDX][current] == list->size - 1) ? current : list->node[NEXT_IDX][current];
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        // move element at list->size - 1 to current's position to avoid 'holes' in array.
        list->size--;
        list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
        list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return found;
    }

    LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t current = list->head;
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    if (list->head == list->size - 1) {
        list->head = current;
    } else if (list->head == current) {
        list->head = (list->node[NEXT_IDX][current] == list->size - 1) ? current : list->node[NEXT_IDX][current];
    }

    LIST_DATA_TYPE found = list->elements[current];

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    // move element at list->size - 1 to current's position to avoid 'holes' in array.
    list->size--;
    list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
    list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

    list->elements[current] = list->elements[list->size];
    list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;

    return found;
}

static inline void reverse_list(list_s * list) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        list->head = current;

        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[PREV_IDX][current];
    }
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline list_s splice_list(list_s * restrict list_one, list_s * restrict list_two, const size_t index, const size_t max) {
    LIST_ASSERT(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    LIST_ASSERT(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");
    LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    LIST_ASSERT(list_one->size + list_two->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    LIST_ASSERT(list_one != list_two && "[ERROR] Lists can't be the same.");
    LIST_ASSERT(index <= list_one->size && "[ERROR] index can't exceed list_one's size");

    list_two->head += list_one->size;
    for (size_t i = 0; i < list_two->size; ++i) { // incrementing list_twos indexes since they get appended to list_one
        list_two->node[NEXT_IDX][i] += list_one->size;
        list_two->node[PREV_IDX][i] += list_one->size;
    }

    list_one->elements = LIST_REALLOC(list_one->elements, sizeof(LIST_DATA_TYPE) * max);
    list_one->node[NEXT_IDX] = LIST_REALLOC(list_one->node[NEXT_IDX], sizeof(size_t) * max);
    list_one->node[PREV_IDX] = LIST_REALLOC(list_one->node[PREV_IDX], sizeof(size_t) * max);

    size_t current = list_one->head;
    if (index < (list_one->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list_one->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list_one->size - index; ++i) {
            current = list_one->node[PREV_IDX][current];
        }
    }

    if (list_one->size && list_two->size) {
        const size_t first_one = current;
        const size_t last_one  = list_one->node[PREV_IDX][current];

        const size_t first_two = list_two->head;
        const size_t last_two  = list_two->node[PREV_IDX][list_two->head];

        list_one->node[NEXT_IDX][last_one] = first_two;
        list_two->node[PREV_IDX][first_two] = last_one;

        list_two->node[NEXT_IDX][last_two] = first_one;
        list_one->node[PREV_IDX][first_one] = last_two;
    }

    memcpy(list_one->elements + list_one->size, list_two->elements, sizeof(LIST_DATA_TYPE) * list_two->size);
    memcpy(list_one->node[NEXT_IDX] + list_one->size, list_two->node[NEXT_IDX], sizeof(size_t) * list_two->size);
    memcpy(list_one->node[PREV_IDX] + list_one->size, list_two->node[PREV_IDX], sizeof(size_t) * list_two->size);

    LIST_FREE(list_two->elements);
    LIST_FREE(list_two->node[NEXT_IDX]);
    LIST_FREE(list_two->node[PREV_IDX]);

    const list_s list = {
        .size = list_one->size + list_two->size, .head = (index || !list_two->size) ? list_one->head : list_two->head, .max = max,
        .node[NEXT_IDX] = list_one->node[NEXT_IDX], .node[PREV_IDX] = list_one->node[PREV_IDX],
        .elements = list_one->elements,
    };

    *list_one = *list_two = (list_s) { 0 };

    return list;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size, const size_t max) {
    LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    LIST_ASSERT(max && "[ERROR] max size can't be zero.");
    LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    LIST_ASSERT(size <= max && "[ERROR] List size exceed max size of new split list.");

    if (!size) {
        return (list_s) { 0 };
    }

    size_t current = list->head;
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    list_s const split_list = {
        .elements = LIST_ALLOC(sizeof(LIST_DATA_TYPE) * max), .head = 0, .size = size,
        .node[NEXT_IDX] = LIST_ALLOC(sizeof(size_t) * max), .node[PREV_IDX] = LIST_ALLOC(sizeof(size_t) * max),
    };

    LIST_ASSERT(split_list.elements && "[ERROR] Memory allocation failed");
    LIST_ASSERT(split_list.node[NEXT_IDX] && "[ERROR] Memory allocation failed");
    LIST_ASSERT(split_list.node[PREV_IDX] && "[ERROR] Memory allocation failed");

    for (size_t i = 0; i < split_list.size; ++i) {
        split_list.elements[i] = list->elements[current];
        split_list.node[NEXT_IDX][i] = i + 1, split_list.node[PREV_IDX][i] = i - 1;

        list->size--;
        list->elements[current] = list->elements[list->size];
        list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;

        current = list->node[NEXT_IDX][current];
    }
    split_list.node[NEXT_IDX][split_list.size - 1] = 0; split_list.node[PREV_IDX][0] = split_list.size - 1;

    if (!index || ((index + size) > list->size)) {
        list->head = current;
    }

    return split_list;
}

static inline LIST_DATA_TYPE get_list(const list_s list, const size_t index) {
    LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    if (index < (list.size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list.size - index; ++i) {
            current = list.node[PREV_IDX][current];
        }
    }

    return list.elements[current];
}

static inline bool is_empty_list(const list_s list) {
    return (list.size == 0);
}

static inline bool is_full_list(const list_s list) {
    return !(~list.size);
}

static inline list_s copy_list(const list_s list, const copy_list_fn copy) {
    const list_s list_copy = {
        .elements = LIST_ALLOC(sizeof(LIST_DATA_TYPE) * list.max),
        .node[NEXT_IDX] = LIST_ALLOC(sizeof(size_t) * list.max), .node[PREV_IDX] = LIST_ALLOC(sizeof(size_t) * list.max),
        .head = list.head, .max = list.max, .size = list.size,
    };

    LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    LIST_ASSERT(list_copy.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    LIST_ASSERT(list_copy.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t i = 0; i < list.size; ++i) {
            list_copy.elements[i] = copy(list.elements[i]);
            list_copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            list_copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(list_copy.elements, list.elements, list.size * sizeof(LIST_DATA_TYPE));
        memcpy(list_copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(list_copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return list_copy;
}

static inline void sort_list(list_s * list, const sort_list_fn sort, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    LIST_ASSERT(sort && "[ERROR] 'sort' function pointer parameter is NULL");

    sort(list->elements, list->size, sizeof(LIST_DATA_TYPE), compare);

    list->head = 0;
    for (size_t i = 0; i < list->size; ++i) {
        list->node[NEXT_IDX][i] = i + 1;
        list->node[PREV_IDX][i] = i - 1;
    }
    if (list->size) {
        list->node[NEXT_IDX][list->size - 1] = 0;
        list->node[PREV_IDX][0] = list->size - 1;
    }
}

static inline void foreach_list(const list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&(list->elements[current]), args)) {
            return;
        }

        current = list->node[NEXT_IDX][current];
    }
}

static inline void foreach_reverse_list(const list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[PREV_IDX][current];

        if (!operate(list->elements + current, args)) {
            return;
        }
    }
}

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#elif LIST_MODE == INFINITE_REALLOC_LIST

#ifndef REALLOC_LIST_CHUNK

#define REALLOC_LIST_CHUNK (1 << 10)

#endif

#define NEXT_IDX   0
#define PREV_IDX   1
#define NODE_COUNT 2
typedef struct list {
    size_t size, head;

    LIST_DATA_TYPE * elements;
    size_t * node[NODE_COUNT];
} list_s;

static inline list_s create_list(void) {
    return (list_s) { 0 };
}

static inline void destroy_list(list_s * list, const destroy_list_fn destroy) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy && (s < list->size); ++s) {
        destroy(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    LIST_FREE(list->elements);
    for (size_t i = 0; i < NODE_COUNT; ++i) {
        LIST_FREE(list->node[i]);
    }

    *list = (list_s) { 0 };
}

static inline void insert_at_list(list_s * list, const size_t index, const LIST_DATA_TYPE element) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    if (!(list->size % REALLOC_LIST_CHUNK)) {
        list->elements = LIST_REALLOC(list->elements, (list->size + REALLOC_LIST_CHUNK) * sizeof(LIST_DATA_TYPE));
        list->node[NEXT_IDX] = LIST_REALLOC(list->elements, (list->size + REALLOC_LIST_CHUNK) * sizeof(size_t));
        list->node[PREV_IDX] = LIST_REALLOC(list->elements, (list->size + REALLOC_LIST_CHUNK) * sizeof(size_t));
    }

    size_t current = list->head, smaller_size = list->size - index, node_index = PREV_IDX;
    if (index <= (list->size >> 1)) {
        smaller_size = index;
        node_index = NEXT_IDX;
    }
    for (size_t i = 0; i < smaller_size; ++i) {
        current = list->node[node_index][current];
    }

    list->node[NEXT_IDX][list->size] = current;
    list->node[PREV_IDX][list->size] = list->node[PREV_IDX][current];

    list->node[PREV_IDX][current] = list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->size;
    if (!index) {
        list->head = list->size;
    }

    memcpy(list->elements + list->size, &element, sizeof(LIST_DATA_TYPE));
    list->size++;
}

static inline LIST_DATA_TYPE remove_first_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[PREV_IDX] && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[NEXT_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
		const int comparison = compare ? compare(&(list->elements[current]), &element) : memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE));
        if (0 != comparison) {
            current = list->node[NEXT_IDX][current];
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[NEXT_IDX][current] == list->size - 1) ? current : list->node[NEXT_IDX][current];
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        // move element at list->size - 1 to current's position to avoid 'holes' in array.
        list->size--;
        list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
        list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        if (!(list->size % REALLOC_LIST_CHUNK)) {
            list->elements = list->size ? LIST_REALLOC(list->elements, list->size * sizeof(LIST_DATA_TYPE)) : NULL;
            list->node[PREV_IDX] = list->size ? LIST_REALLOC(list->node[PREV_IDX], list->size * sizeof(size_t)) : NULL;
            list->node[NEXT_IDX] = list->size ? LIST_REALLOC(list->node[NEXT_IDX], list->size * sizeof(size_t)) : NULL;
        }

        return found;
    }

    LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_last_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[PREV_IDX] && "[ERROR] No memory available.");
    LIST_ASSERT(list->node[NEXT_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        current = list->node[PREV_IDX][current];

		const int comparison = compare ? compare(&(list->elements[current]), &element) : memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE));
        if (0 != comparison) {
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[NEXT_IDX][current] == list->size - 1) ? current : list->node[NEXT_IDX][current];
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        // move element at list->size - 1 to current's position to avoid 'holes' in array.
        list->size--;
        list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
        list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        if (!(list->size % REALLOC_LIST_CHUNK)) {
            list->elements = list->size ? LIST_REALLOC(list->elements, list->size * sizeof(LIST_DATA_TYPE)) : NULL;
            list->node[PREV_IDX] = list->size ? LIST_REALLOC(list->node[PREV_IDX], list->size * sizeof(size_t)) : NULL;
            list->node[NEXT_IDX] = list->size ? LIST_REALLOC(list->node[NEXT_IDX], list->size * sizeof(size_t)) : NULL;
        }

        return found;
    }

    LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    LIST_ASSERT(index < list->size && "[ERROR] Index parameter greater than list size.");

    size_t current = list->head;
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    if (list->head == list->size - 1) {
        list->head = current;
    } else if (list->head == current) {
        list->head = (list->node[NEXT_IDX][current] == list->size - 1) ? current : list->node[NEXT_IDX][current];
    }

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    LIST_DATA_TYPE found = list->elements[current];

    // move element at list->size - 1 to current's position to avoid 'holes' in array.
    list->size--;
    list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
    list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

    list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
    list->elements[current] = list->elements[list->size];

    if (!(list->size % REALLOC_LIST_CHUNK)) {
        if (list->size) {
            list->elements = LIST_REALLOC(list->elements, list->size * sizeof(LIST_DATA_TYPE));
            list->node[PREV_IDX] = LIST_REALLOC(list->node[PREV_IDX], list->size * sizeof(size_t));
            list->node[NEXT_IDX] = LIST_REALLOC(list->node[NEXT_IDX], list->size * sizeof(size_t));
        } else {
            list->elements = (LIST_DATA_TYPE *) (list->node[PREV_IDX] = list->node[NEXT_IDX] = NULL);
        }
    }

    return found;
}

static inline void reverse_list(list_s * list) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        list->head = current;

        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[PREV_IDX][current];
    }
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline list_s splice_list(list_s * restrict list_one, list_s * restrict list_two, const size_t index) {
    LIST_ASSERT(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    LIST_ASSERT(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");
    LIST_ASSERT(list_one != list_two && "[ERROR] Lists can't be the same.");
    LIST_ASSERT(index <= list_one->size && "[ERROR] index can't exceed list_one's size");

    const size_t new_size = (list_one->size + list_two->size);
    if (!new_size) return (list_s) { 0 };

    const size_t alloc_size = new_size - (new_size % REALLOC_LIST_CHUNK) + REALLOC_LIST_CHUNK;

    list_two->head += list_one->size;
    for (size_t i = 0; i < list_two->size; ++i) { // incrementing list_twos indexes since they get appended to list_one
        list_two->node[NEXT_IDX][i] += list_one->size;
        list_two->node[PREV_IDX][i] += list_one->size;
    }

    list_one->elements = LIST_REALLOC(list_one->elements, sizeof(LIST_DATA_TYPE) * alloc_size);
    list_one->node[NEXT_IDX] = LIST_REALLOC(list_one->node[NEXT_IDX], sizeof(size_t) * alloc_size);
    list_one->node[PREV_IDX] = LIST_REALLOC(list_one->node[PREV_IDX], sizeof(size_t) * alloc_size);

    size_t current = list_one->head;
    if (index < (list_one->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list_one->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list_one->size - index; ++i) {
            current = list_one->node[PREV_IDX][current];
        }
    }

    if (list_one->size && list_two->size) {
        const size_t first_one = current;
        const size_t last_one  = list_one->node[PREV_IDX][current];

        const size_t first_two = list_two->head;
        const size_t last_two  = list_two->node[PREV_IDX][list_two->head];

        list_one->node[NEXT_IDX][last_one] = first_two;
        list_two->node[PREV_IDX][first_two] = last_one;

        list_two->node[NEXT_IDX][last_two] = first_one;
        list_one->node[PREV_IDX][first_one] = last_two;
    }

    memcpy(list_one->elements + list_one->size, list_two->elements, sizeof(LIST_DATA_TYPE) * list_two->size);
    memcpy(list_one->node[NEXT_IDX] + list_one->size, list_two->node[NEXT_IDX], sizeof(size_t) * list_two->size);
    memcpy(list_one->node[PREV_IDX] + list_one->size, list_two->node[PREV_IDX], sizeof(size_t) * list_two->size);

    LIST_FREE(list_two->elements);
    LIST_FREE(list_two->node[NEXT_IDX]);
    LIST_FREE(list_two->node[PREV_IDX]);

    const list_s list = {
        .head = (index || !list_two->size) ? list_one->head : list_two->head, .elements = list_one->elements, .size = new_size,
        .node[NEXT_IDX] = list_one->node[NEXT_IDX], .node[PREV_IDX] = list_one->node[PREV_IDX],
    };

    *list_one = *list_two = (list_s) { 0 };

    return list;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size) {
    LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) {
        return (list_s) { 0 };
    }

    const size_t split_chunk = size - (size % REALLOC_LIST_CHUNK) + REALLOC_LIST_CHUNK;
    list_s const split_list = {
        .elements = LIST_ALLOC(sizeof(LIST_DATA_TYPE) * split_chunk), .head = 0, .size = size,
        .node[NEXT_IDX] = LIST_ALLOC(sizeof(size_t) * split_chunk), .node[PREV_IDX] = LIST_ALLOC(sizeof(size_t) * split_chunk),
    };

    LIST_ASSERT(split_list.elements && "[ERROR] Memory allocation failed");
    LIST_ASSERT(split_list.node[NEXT_IDX] && "[ERROR] Memory allocation failed");
    LIST_ASSERT(split_list.node[PREV_IDX] && "[ERROR] Memory allocation failed");

    size_t current = list->head; // pointer to change head while splitting
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) { current = list->node[NEXT_IDX][current]; }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) { current = list->node[PREV_IDX][current];}
    }

    for (size_t i = 0; i < split_list.size; ++i) {
        split_list.elements[i] = list->elements[current];
        split_list.node[NEXT_IDX][i] = i + 1, split_list.node[PREV_IDX][i] = i - 1;

        list->size--;
        list->elements[current] = list->elements[list->size];
        list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;

        if (list->size) {
            if (!(list->size % REALLOC_LIST_CHUNK)) { // shorten chunk to save memory if possible
                list->elements = LIST_REALLOC(list->elements, list->size * sizeof(LIST_DATA_TYPE));
                list->node[PREV_IDX] = LIST_REALLOC(list->node[PREV_IDX], list->size * sizeof(size_t));
                list->node[NEXT_IDX] = LIST_REALLOC(list->node[NEXT_IDX], list->size * sizeof(size_t));
            }

            current = list->node[NEXT_IDX][current];
        } else {
            LIST_FREE(list->elements);
            LIST_FREE(list->node[PREV_IDX]);
            LIST_FREE(list->node[NEXT_IDX]);
            list->elements = (LIST_DATA_TYPE *) (list->node[PREV_IDX] = list->node[NEXT_IDX] = NULL);
        }
    }
    split_list.node[NEXT_IDX][split_list.size - 1] = 0; split_list.node[PREV_IDX][0] = split_list.size - 1;

    if (!index || ((index + size) > list->size)) {
        list->head = current;
    }

    return split_list;
}

static inline LIST_DATA_TYPE get_list(const list_s list, const size_t index) {
    LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    if (index < (list.size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list.size - index; ++i) {
            current = list.node[PREV_IDX][current];
        }
    }

    return list.elements[current];
}

static inline bool is_empty_list(const list_s list) {
    return (list.size == 0);
}

static inline bool is_full_list(const list_s list) {
    return !((~list.size) && (list.size < REALLOC_LIST_CHUNK));
}

static inline list_s copy_list(const list_s list, const copy_list_fn copy) {
    if (!list.size) return (list_s) { 0 };

    const size_t copy_chunk = list.size - (list.size % REALLOC_LIST_CHUNK) + REALLOC_LIST_CHUNK;
    const list_s list_copy = {
        .elements = LIST_ALLOC(sizeof(LIST_DATA_TYPE) * copy_chunk),
        .node[NEXT_IDX] = LIST_ALLOC(sizeof(size_t) * copy_chunk), .node[PREV_IDX] = LIST_ALLOC(sizeof(size_t) * copy_chunk),
        .head = list.head, .size = list.size,
    };

    LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    LIST_ASSERT(list_copy.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    LIST_ASSERT(list_copy.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t i = 0; i < list.size; ++i) {
            list_copy.elements[i] = copy(list.elements[i]);
            list_copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            list_copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(list_copy.elements, list.elements, list.size * sizeof(LIST_DATA_TYPE));
        memcpy(list_copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(list_copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return list_copy;
}

static inline void sort_list(list_s * list, const sort_list_fn sort, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    LIST_ASSERT(sort && "[ERROR] 'sort' function pointer parameter is NULL");

    sort(list->elements, list->size, sizeof(LIST_DATA_TYPE), compare);

    list->head = 0;
    for (size_t i = 0; i < list->size; ++i) {
        list->node[NEXT_IDX][i] = i + 1;
        list->node[PREV_IDX][i] = i - 1;
    }
    if (list->size) {
        list->node[NEXT_IDX][list->size - 1] = 0;
        list->node[PREV_IDX][0] = list->size - 1;
    }
}

static inline void foreach_list(const list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&(list->elements[current]), args)) {
            return;
        }

        current = list->node[NEXT_IDX][current];
    }
}

static inline void foreach_reverse_list(const list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[PREV_IDX][current];

        if (!operate(list->elements + current, args)) {
            return;
        }
    }
}

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#elif LIST_MODE == FINITE_PRERPOCESSOR_LIST

#ifndef PREPROCESSOR_LIST_SIZE

#define PREPROCESSOR_LIST_SIZE (1 << 10)

#elif PREPROCESSOR_LIST_SIZE == 0

#error 'PREPROCESSOR_LIST_SIZE' cannot be zero

#endif

#define NODE_COUNT 2
#define NEXT_IDX   0
#define PREV_IDX   1
typedef struct list {
    size_t size, head;

    LIST_DATA_TYPE elements[PREPROCESSOR_LIST_SIZE];
    size_t node[NODE_COUNT][PREPROCESSOR_LIST_SIZE];
} list_s;

static inline list_s create_list(void) {
    return (list_s) { .size = 0, .head = 0, };
}

static inline void destroy_list(list_s * list, const destroy_list_fn destroy) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy && (s < list->size); ++s) {
        destroy(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    list->size = list->head = 0;
}

static inline void insert_at_list(list_s * list, const size_t index, const LIST_DATA_TYPE element) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size < PREPROCESSOR_LIST_SIZE && "[ERROR] List reached maximum size.");
    LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t current = list->head;

    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    list->node[NEXT_IDX][list->size] = current;
    list->node[PREV_IDX][list->size] = list->node[PREV_IDX][current];

    list->node[PREV_IDX][current] = list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->size;
    if (!index) {
        list->head = list->size;
    }

    memcpy(list->elements + list->size, &element, sizeof(LIST_DATA_TYPE));
    list->size++;
}

static inline LIST_DATA_TYPE remove_first_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        const int comparison = compare ? compare(&(list->elements[current]), &element) : memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE));
        if (0 != comparison) {
            current = list->node[NEXT_IDX][current];
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[NEXT_IDX][current] == list->size - 1) ? current : list->node[NEXT_IDX][current];
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        list->size--;
        list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
        list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return found;
    }

    LIST_ASSERT(false && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_last_list(list_s * list, const LIST_DATA_TYPE element, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        current = list->node[PREV_IDX][current];

        const int comparison = compare ? compare(&(list->elements[current]), &element) : memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE));
        if (0 != comparison) {
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->size - 1 == list->node[NEXT_IDX][current]) ? current : list->node[NEXT_IDX][current];
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        list->size--;
        list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
        list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return found;
    }

    LIST_ASSERT(false && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t current = list->head;
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    if (list->head == list->size - 1) {
        list->head = current;
    } else if (list->head == current) {
        list->head = (list->size - 1 == list->node[NEXT_IDX][current]) ? current : list->node[NEXT_IDX][current];
    }

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    LIST_DATA_TYPE found = list->elements[current];

    list->size--;
    list->node[NEXT_IDX][current] = list->node[NEXT_IDX][list->size];
    list->node[PREV_IDX][current] = list->node[PREV_IDX][list->size];

    list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
    list->elements[current] = list->elements[list->size];

    return found;
}

static inline void reverse_list(list_s * list) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        list->head = current;

        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[PREV_IDX][current];
    }
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline list_s splice_list(list_s * restrict list_one, list_s * restrict list_two, const size_t index) {
    LIST_ASSERT(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    LIST_ASSERT(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");
    LIST_ASSERT(list_one != list_two && "[ERROR] Lists can't be the same.");
    LIST_ASSERT(index <= list_one->size && "[ERROR] index can't exceed list_one's size");
    LIST_ASSERT(list_one->size + list_two->size <= PREPROCESSOR_LIST_SIZE && "[ERROR] new list's size exceeds PREPROCESSOR_LIST_SIZE");

    list_two->head += list_one->size;
    for (size_t i = 0; i < list_two->size; ++i) { // incrementing list_twos indexes since they get appended to list_one
        list_two->node[NEXT_IDX][i] += list_one->size;
        list_two->node[PREV_IDX][i] += list_one->size;
    }

    size_t current = list_one->head;
    if (index < (list_one->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list_one->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list_one->size - index; ++i) {
            current = list_one->node[PREV_IDX][current];
        }
    }

    if (list_one->size && list_two->size) {
        const size_t first_one = current;
        const size_t last_one  = list_one->node[PREV_IDX][current];

        const size_t first_two = list_two->head;
        const size_t last_two  = list_two->node[PREV_IDX][list_two->head];

        list_one->node[NEXT_IDX][last_one] = first_two;
        list_two->node[PREV_IDX][first_two] = last_one;

        list_two->node[NEXT_IDX][last_two] = first_one;
        list_one->node[PREV_IDX][first_one] = last_two;
    }

    list_s list = { .head = (index || !list_two->size) ? list_one->head : list_two->head, .size = list_one->size + list_two->size, };
    memcpy(list.elements, list_one->elements, sizeof(LIST_DATA_TYPE) * list_one->size);
    memcpy(list.node[NEXT_IDX], list_one->node[NEXT_IDX], sizeof(size_t) * list_one->size);
    memcpy(list.node[PREV_IDX], list_one->node[PREV_IDX], sizeof(size_t) * list_one->size);

    memcpy(list.elements + list_one->size, list_two->elements, sizeof(LIST_DATA_TYPE) * list_two->size);
    memcpy(list.node[NEXT_IDX] + list_one->size, list_two->node[NEXT_IDX], sizeof(size_t) * list_two->size);
    memcpy(list.node[PREV_IDX] + list_one->size, list_two->node[PREV_IDX], sizeof(size_t) * list_two->size);

    list_one->size = list_two->size = 0;
    list_one->head = list_two->head = 0;

    return list;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size) {
    LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) {
        return (list_s) { .head = 0, .size = 0 };
    }

    size_t current = list->head;
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    list_s split_list = { .head = 0, .size = size, };

    for (size_t i = 0; i < split_list.size; ++i) {
        split_list.elements[i] = list->elements[current];
        split_list.node[NEXT_IDX][i] = i + 1, split_list.node[PREV_IDX][i] = i - 1;

        list->size--;
        list->elements[current] = list->elements[list->size];
        list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;

        current = list->node[NEXT_IDX][current];
    }
    split_list.node[NEXT_IDX][split_list.size - 1] = 0; split_list.node[PREV_IDX][0] = split_list.size - 1;

    if (!index || ((index + size) > list->size)) {
        list->head = current;
    }

    return split_list;
}

static inline LIST_DATA_TYPE get_list(const list_s list, const size_t index) {
    LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    if (index < (list.size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list.size - index; ++i) {
            current = list.node[PREV_IDX][current];
        }
    }

    return list.elements[current];
}

static inline bool is_empty_list(const list_s list) {
    return (list.size == 0);
}

static inline bool is_full_list(const list_s list) {
    return !((~list.size) && (list.size < PREPROCESSOR_LIST_SIZE));
}

static inline list_s copy_list(const list_s list, const copy_list_fn copy) {
    list_s list_copy = { .head = list.head, .size = list.size, };

    if (copy) {
        for (size_t i = 0; i < list.size; ++i) {
            list_copy.elements[i] = copy(list.elements[i]);
            list_copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            list_copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(list_copy.elements, list.elements, list.size * sizeof(LIST_DATA_TYPE));
        memcpy(list_copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(list_copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return list_copy;
}

static inline void sort_list(list_s * list, const sort_list_fn sort, const compare_list_fn compare) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    LIST_ASSERT(sort && "[ERROR] 'sort' function pointer parameter is NULL");

    sort(list->elements, list->size, sizeof(LIST_DATA_TYPE), compare);

    list->head = 0;
    for (size_t i = 0; i < list->size; ++i) {
        list->node[NEXT_IDX][i] = i + 1;
        list->node[PREV_IDX][i] = i - 1;
    } if (list->size) {
        list->node[NEXT_IDX][list->size - 1] = 0;
        list->node[PREV_IDX][0] = list->size - 1;
    }
}

static inline void foreach_list(list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&(list->elements[current]), args)) {
            return;
        }

        current = list->node[NEXT_IDX][current];
    }
}

static inline void foreach_reverse_list(list_s * list, const operate_list_fn operate, void * args) {
    LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[PREV_IDX][current];

        if (!operate(list->elements + current, args)) {
            return;
        }
    }
}

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#endif

#endif // LIST_H
