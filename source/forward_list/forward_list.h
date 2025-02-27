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
#define INFINITE_ALLOCATED_FORWARD_LIST  21
#define FINITE_ALLOCATED_FORWARD_LIST    22
#define INFINITE_REALLOC_FORWARD_LIST    23
#define FINITE_PRERPOCESSOR_FORWARD_LIST 24

#define INFINITE_FORWARD_LIST INFINITE_ALLOCATED_FORWARD_LIST
#define FINITE_FORWARD_LIST   FINITE_ALLOCATED_FORWARD_LIST

//#define FORWARD_LIST_MODE INFINITE_ALLOCATED_FORWARD_LIST
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
typedef void                   (*sort_forward_list_fn)    (FORWARD_LIST_DATA_TYPE *, const size_t);

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
    for (size_t i = 0; i < index; ++i) { // if index is last element then dont loop since list has tail pointer
        previous = previous->next;
    }
    struct forward_list_node * current = previous->next;

    list->size--;
    FORWARD_LIST_DATA_TYPE found = { 0 };
    memcpy(&found, &(current->element), sizeof(FORWARD_LIST_DATA_TYPE));

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

static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->tail && (s < shift); ++s) {
        list->tail = list->tail->next;
    }
}

static inline void splice_forward_list(forward_list_s * restrict destination, forward_list_s * restrict source, const size_t index) {
    FORWARD_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    FORWARD_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    struct forward_list_node * previous = destination->tail;
    for (size_t i = 0; index != destination->size - 1 && i < index; ++i) {
        previous = previous->next;
    }

    if (previous && source->tail) {
        struct forward_list_node * swap = previous->next;
        previous->next = source->tail->next;
        source->tail->next = swap;
    }

    if (index == destination->size && source->tail) {
        destination->tail = source->tail;
    }
    destination->size += source->size;

    *source = (forward_list_s) { 0 };
}

static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size) {
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    struct forward_list_node * prev_index_node = list->tail;
    for (size_t i = 0; i < index; ++i) {
        prev_index_node = prev_index_node->next;
    }
    if ((index + size) >= list->size) { // if tail node becomes part of split list new tail node will be the node previous to index/first-split node
        list->tail = prev_index_node;
    }

    forward_list_s split = { .size = size, .tail = NULL };

    struct forward_list_node * last_added = NULL;
    struct forward_list_node ** split_previous = &(split.tail);
    for (size_t i = 0; i < size; ++i) { // split's tail is treated as the head node and gets changed to tail after loop finishes via last_added
        struct forward_list_node * current = prev_index_node->next;
        (*split_previous) = last_added = current; // previous index node's next is part of split
        prev_index_node->next = prev_index_node->next->next; // remove current from list
        (*split_previous)->next = split.tail; // every new node added needs to point to the tail as next node

        split_previous = &((*split_previous)->next);
    }
    split.tail = last_added; // makes the last node added to split list the tail, or NULL if size parameter is zero

    list->size -= size;
    if (!list->size) { // if list size becomes zero list tail will be NULL/empty
        list->tail = NULL;
    }

    return split;
}

static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.tail && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct forward_list_node const * current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) { // if index is last element then don't iterate and return tail node
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
        FORWARD_LIST_ASSERT(temp && "[ERROR] Memory allocation failed.");
        temp->element = copy ? copy(previous_list->element) : previous_list->element;

        (*previous_copy) = temp;
        temp->next = list_copy.tail;

        previous_list = previous_list->next;
        previous_copy = &((*previous_copy)->next);
    }

    return list_copy;
}

static inline void sort_forward_list(forward_list_s const * list, const sort_forward_list_fn sort) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(sort && "[ERROR] 'sort' parameter pointer is NULL.");

    FORWARD_LIST_DATA_TYPE * elements_array = FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * list->size);
    FORWARD_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct forward_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = previous->element;
        previous = previous->next;
    }

    sort(elements_array, list->size);

    previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next;
        previous->element = elements_array[i];
    }
    FORWARD_LIST_FREE(elements_array);
}

static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    struct forward_list_node const * base = list.tail;
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        struct forward_list_node const * current = base->next; // start from next element to move from tail and to ignore compared element
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = current->next;
        }

        const int comparison = compare ? compare(&element, &(current->element)) : memcmp(&element, &(current->element), sizeof(FORWARD_LIST_DATA_TYPE));

        if (comparison == 0) {
            return true;
        }
        if (comparison > 0) {
            base = current; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
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

static inline void foreach_forward_list(forward_list_s const * list, const operate_forward_list_fn operate, void * args) {
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

/// @brief The FINITE_ALLOCATED_FORWARD_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the forward_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
typedef struct forward_list {
    size_t size, empty_size, tail, empty_head, max;
    FORWARD_LIST_DATA_TYPE * elements;
    size_t * next;
} forward_list_s;

static inline forward_list_s create_forward_list(const size_t max) {
    FORWARD_LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const forward_list_s list = {
        .elements = FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * max),
        .next = FORWARD_LIST_ALLOC(sizeof(size_t) * max),

        .tail = 0, .max = max, .size = 0, .empty_head = 0, .empty_size = 0,
    };

    FORWARD_LIST_ASSERT(list.elements && "[ERROR] Memory allocation failed.");
    FORWARD_LIST_ASSERT(list.next && "[ERROR] Memory allocation failed.");

    return list;
}

static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(list->elements + previous);
        }

        previous = list->next[previous];
    }

    FORWARD_LIST_FREE(list->elements);
    FORWARD_LIST_FREE(list->next);
    *list = (forward_list_s) { 0 };
}

static inline void insert_at_forward_list(forward_list_s * list, const size_t index, const FORWARD_LIST_DATA_TYPE element) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size < list->max && "[ERROR] List reached maximum size.");
    FORWARD_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    FORWARD_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }

    if (list->empty_size) { // if 'empty stack' isn't empty pop empty index from it
        memcpy(list->elements + list->empty_head, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        const size_t temp = list->empty_head;
        list->empty_head = list->next[list->empty_head];
        list->empty_size--;

        list->next[temp] = list->next[previous];
        list->next[previous] = temp;
    } else { // else 'empty stack' is empty, therefore push element to the top of the 'loaded stack'
        memcpy(list->elements + list->size, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        list->next[list->size] = list->next[previous];
        list->next[previous] = list->size;
    }
    if (index == list->size) { // if index is at last/tail element tail must index to last added element
        list->tail = list->next[previous];
    }

    list->size++;
}

static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        size_t current = list->next[previous];
        const int comparison = compare ? compare(list->elements + current, &element) : memcmp(list->elements + current, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        if (0 == comparison) {
            list->size--;
            FORWARD_LIST_DATA_TYPE found = list->elements[current];

            list->next[previous] = list->next[current];

            if (list->next[current] != list->size) { // push empty index to 'empty stack'
                list->next[current] = list->empty_head;
                list->empty_head = current;
                list->empty_size++;
            }

            if (current == list->tail) { // if current is the last element
                list->tail = previous; // if list still has elements then tail will become the previous index
            }

            if (!list->size) {
                list->empty_head = list->empty_size = list->tail = 0;
            }

            return found;
        }
        previous = list->next[previous];
    }

    FORWARD_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    const size_t current = list->next[previous];

    list->size--;
    FORWARD_LIST_DATA_TYPE found = list->elements[current];

    list->next[previous] = list->next[current];

    if (list->next[current] != list->size) { // push empty index to 'empty stack'
        list->next[current] = list->empty_head;
        list->empty_head = current;
        list->empty_size++;
    }

    if (index == list->size) { // if last element is removed
        list->tail = previous; // if list still has elements then tail will become the previous index
    }

    if (!list->size) {
        list->empty_head = list->empty_size = list->tail = 0;
    }

    return found;
}

static inline void reverse_forward_list(forward_list_s * list) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    if (!list->size) {
        return;
    }

    size_t current = list->tail;
    size_t current_next = list->next[current];
    size_t current_next_next = list->next[current_next];
    list->tail = current_next;
    for (size_t i = 0; i < list->size; ++i) {
        list->next[current_next] = current;
        current = current_next;
        current_next = current_next_next;
        current_next_next = list->next[current_next_next];
    }
}

static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->tail && (s < shift); ++s) {
        list->tail = list->next[list->tail];
    }
}

static inline void splice_forward_list(forward_list_s * restrict destination, forward_list_s * restrict source, const size_t index, const size_t max) {
    FORWARD_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    FORWARD_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    FORWARD_LIST_ASSERT(destination->size + source->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    FORWARD_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    const size_t size_dest = destination->size;

    destination->elements = FORWARD_LIST_REALLOC(destination->elements, sizeof(FORWARD_LIST_DATA_TYPE) * max);
    FORWARD_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed.");
    destination->next = FORWARD_LIST_REALLOC(destination->next, sizeof(size_t) * max);
    FORWARD_LIST_ASSERT(destination->next && "[ERROR] Memory allocation failed.");

    size_t previous_dest = destination->tail;
    for (size_t i = 0; size_dest && index != size_dest && i < index; ++i) {
        previous_dest = destination->next[previous_dest];
    }

    size_t previous_src = source->tail;
    while (source->size && destination->empty_size) {
        previous_src = destination->next[previous_src];
        memcpy(destination->elements + destination->empty_head, source->elements + previous_src, sizeof(FORWARD_LIST_DATA_TYPE));
        source->size--;

        const size_t temp = destination->empty_head;
        destination->empty_head = destination->next[destination->empty_head];
        destination->empty_size--;

        destination->next[temp] = destination->next[previous_dest];
        destination->next[previous_dest] = temp;
        destination->size++;

        previous_dest = destination->next[previous_dest];
    }

    while (source->size) {
        previous_src = destination->next[previous_src];
        memcpy(destination->elements + destination->size, source->elements + previous_src, sizeof(FORWARD_LIST_DATA_TYPE));
        source->size--;

        destination->next[destination->size] = destination->next[previous_dest];
        destination->next[previous_dest] = destination->size;
        destination->size++;

        previous_dest = destination->next[previous_dest];
    }

    if (size_dest && index == size_dest) {
        destination->tail = previous_dest;
    }

    source->empty_head = source->empty_size = source->size = source->tail = 0;
}

static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size, const size_t max) {
    FORWARD_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    forward_list_s split = {
        .elements = FORWARD_LIST_ALLOC(max * sizeof(FORWARD_LIST_DATA_TYPE)),
        .next = FORWARD_LIST_ALLOC(max * sizeof(size_t)),
        .empty_head = 0, .max = max, .empty_size = 0, .size = 0, .tail = 0
    };
    FORWARD_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");
    FORWARD_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed.");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    if ((index + size) >= list->size) { // if tail node becomes part of split list new tail node will be the node previous to index/first-split node
        list->tail = previous;
    }

    for (size_t i = 1; size && i <= size; ++i) {
        previous = list->next[previous];

        const size_t mod = i % size;
        memcpy(split.elements + mod, list->elements + previous, sizeof(FORWARD_LIST_DATA_TYPE));
        split.next[i - 1] = mod;
        list->size--;

        list->next[previous] = list->next[previous];
        if (list->next[previous] != list->size) { // push empty index to 'empty stack'
            list->next[previous] = list->empty_head;
            list->empty_head = previous;
            list->empty_size++;
        }
    }

    return split;
}

static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.tail && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

static inline bool is_full_forward_list(const forward_list_s list) {
    return !(~list.size);
}

static inline forward_list_s copy_forward_list(const forward_list_s list, const copy_forward_list_fn copy) {
    const forward_list_s list_copy = {
        .elements = FORWARD_LIST_ALLOC(list.max * sizeof(FORWARD_LIST_DATA_TYPE)),
        .next = FORWARD_LIST_ALLOC(list.max * sizeof(size_t)),
        .empty_head = 0, .empty_size = 0, .max = list.max, .size = list.size, .tail = 0,
    };
    FORWARD_LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    FORWARD_LIST_ASSERT(list_copy.next && "[ERROR] Memory allocation failed.");

    size_t previous = list.tail;
    for (size_t i = 0; list.size && i <= list.size; ++i) {
        previous = list.next[previous];

        const size_t mod = i % list.size;
        list_copy.elements[mod] = copy ? copy(list.elements[previous]) : list.elements[previous];
        list_copy.next[i - 1] = mod;
    }

    return list_copy;
}

static inline void sort_forward_list(forward_list_s * list, const sort_forward_list_fn sort) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    FORWARD_LIST_ASSERT(sort && "[ERROR] 'sort' parameter pointer is NULL");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (stack_size) { // removes holes at the expense of breaking the list
        if (empty_index > stack_size) {
            empty_index = list->next[empty_index];
        }

        FORWARD_LIST_DATA_TYPE element = list->elements[empty_index];
        list->elements[empty_index] = list->elements[stack_size];
        list->elements[stack_size] = element;

        const size_t index = list->next[empty_index];
        list->next[empty_index] = list->next[stack_size];
        list->next[stack_size] = empty_index;
        empty_index = index;

        stack_size--;
    }
    list->empty_size = 0;

    sort(list->elements, list->size);

    list->tail = list->size ? list->size - 1 : 0;
    for (size_t i = 1; list->size && i <= list->size; ++i) {
        const size_t mod = i % list->size;
        list->next[i - 1] = mod;
    }
}

static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    size_t base = list.tail;
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        size_t current = list.next[base]; // start from next element to move from tail and to ignore compared element
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(&element, list.elements + current) : memcmp(&element, list.elements + current, sizeof(FORWARD_LIST_DATA_TYPE));

        if (comparison == 0) {
            return true;
        }
        if (comparison > 0) {
            base = current; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(list->elements + previous);
        }

        previous = list->next[previous];
    }

    *list = (forward_list_s) { 0 };
}

static inline void foreach_forward_list(forward_list_s * list, const operate_forward_list_fn operate, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = list->next[previous];

        if (!operate(list->elements + previous, args)) {
            return;
        }
    }
}

#elif FORWARD_LIST_MODE == INFINITE_REALLOC_FORWARD_LIST

#ifndef REALLOC_FORWARD_LIST_CHUNK

#define REALLOC_FORWARD_LIST_CHUNK (1 << 10)

#endif

/// @brief The FINITE_ALLOCATED_FORWARD_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the forward_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
typedef struct forward_list {
    size_t size, empty_size, tail, empty_head;
    FORWARD_LIST_DATA_TYPE * elements;
    size_t * next;
} forward_list_s;

static inline forward_list_s create_forward_list(void) {
    return (forward_list_s) { 0 };
}

static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(list->elements + previous);
        }

        previous = list->next[previous];
    }

    FORWARD_LIST_FREE(list->elements);
    FORWARD_LIST_FREE(list->next);
    *list = (forward_list_s) { 0 };
}

static inline void insert_at_forward_list(forward_list_s * list, const size_t index, const FORWARD_LIST_DATA_TYPE element) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    FORWARD_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }

    if (list->empty_size) { // if 'empty stack' isn't empty pop empty index from it
        memcpy(list->elements + list->empty_head, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        const size_t temp = list->empty_head;
        list->empty_head = list->next[list->empty_head];
        list->empty_size--;

        list->next[temp] = list->next[previous];
        list->next[previous] = temp;
    } else { // else 'empty stack' is empty, therefore push element to the top of the 'loaded stack'
        if (0 == (list->size % REALLOC_FORWARD_LIST_CHUNK)) {
            list->elements = FORWARD_LIST_REALLOC(list->elements, sizeof(FORWARD_LIST_DATA_TYPE) * (list->size + REALLOC_FORWARD_LIST_CHUNK));
            list->next = FORWARD_LIST_REALLOC(list->next, sizeof(size_t) * (list->size + REALLOC_FORWARD_LIST_CHUNK));
        }
        memcpy(list->elements + list->size, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        list->next[list->size] = list->next[previous];
        list->next[previous] = list->size;
    }
    if (index == list->size) { // if index is at last/tail element tail must index to last added element
        list->tail = list->next[previous];
    }

    list->size++;
}

static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t current = list->next[previous];
        const int comparison = compare ? compare(list->elements + current, &element) : memcmp(list->elements + current, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        if (0 == comparison) {
            list->size--;
            FORWARD_LIST_DATA_TYPE found = list->elements[current];

            list->next[previous] = list->next[current];

            if (list->next[current] != list->size) { // push empty index to 'empty stack'
                list->next[current] = list->empty_head;
                list->empty_head = current;
                list->empty_size++;
            }

            if (current == list->tail) { // if current is the last element
                list->tail = previous; // if list still has elements then tail will become the previous index
            }

            if (0 == (list->size % REALLOC_FORWARD_LIST_CHUNK)) { // turn list into continuous array and reduce size via realloc
                FORWARD_LIST_DATA_TYPE * temp_elements = list->size ? FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * list->size) : NULL;
                size_t * temp_next = list->size ? FORWARD_LIST_ALLOC(sizeof(size_t) * list->size) : NULL;

                size_t realloc_index = list->tail;
                for (size_t i = 0; list->size && i < list->size; ++i) {
                    temp_elements[i] = list->elements[realloc_index];
                    temp_next[i] = i + 1;
                    temp_next[list->size - 1] = 0;

                    realloc_index = list->next[realloc_index];
                }

                list->empty_head = list->empty_size = list->size = list->tail = 0;

                FORWARD_LIST_FREE(list->elements);
                FORWARD_LIST_FREE(list->next);

                list->elements = temp_elements;
                list->next = temp_next;
            }

            return found;
        }
        previous = list->next[previous];
    }

    FORWARD_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    const size_t current = list->next[previous];

    list->size--;
    FORWARD_LIST_DATA_TYPE found = list->elements[current];

    list->next[previous] = list->next[current];

    if (list->next[current] != list->size) { // push empty index to 'empty stack'
        list->next[current] = list->empty_head;
        list->empty_head = current;
        list->empty_size++;
    }

    if (index == list->size) { // if last element is removed
        list->tail = previous; // if list still has elements then tail will become the previous index
    }

    if (0 == (list->size % REALLOC_FORWARD_LIST_CHUNK)) { // turn list into continuous array and reduce size via realloc
        FORWARD_LIST_DATA_TYPE * temp_elements = list->size ? FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * list->size) : NULL;
        size_t * temp_next = list->size ? FORWARD_LIST_ALLOC(sizeof(size_t) * list->size) : NULL;

        size_t realloc_index = list->tail;
        for (size_t i = 0; list->size && i < list->size; ++i) {
            temp_elements[i] = list->elements[realloc_index];
            temp_next[i] = i + 1;
            temp_next[list->size - 1] = 0;

            realloc_index = list->next[realloc_index];
        }

        list->empty_head = list->empty_size = list->size = list->tail = 0;

        FORWARD_LIST_FREE(list->elements);
        FORWARD_LIST_FREE(list->next);

        list->elements = temp_elements;
        list->next = temp_next;
    }

    return found;
}

static inline void reverse_forward_list(forward_list_s * list) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    if (!list->size) {
        return;
    }

    size_t current = list->tail;
    size_t current_next = list->next[current];
    size_t current_next_next = list->next[current_next];
    list->tail = current_next;
    for (size_t i = 0; i < list->size; ++i) {
        list->next[current_next] = current;
        current = current_next;
        current_next = current_next_next;
        current_next_next = list->next[current_next_next];
    }
}

static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->tail && (s < shift); ++s) {
        list->tail = list->next[list->tail];
    }
}

static inline void splice_forward_list(forward_list_s * restrict destination, forward_list_s * restrict source, const size_t index) {
    FORWARD_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    FORWARD_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    const size_t size_dest = destination->size;
    size_t previous_dest = destination->tail;
    for (size_t i = 0; index != destination->size && i < index; ++i) {
        previous_dest = destination->next[previous_dest];
    }

    size_t previous_src = source->tail;
    while (source->size && destination->empty_size) { // fill empty holes in destination with source elements
        previous_src = source->next[previous_src];
        memcpy(destination->elements + destination->empty_head, source->elements + previous_src, sizeof(FORWARD_LIST_DATA_TYPE));
        source->size--;
        destination->size++;

        const size_t temp = destination->empty_head;
        destination->empty_head = destination->next[destination->empty_head];
        destination->empty_size--;

        destination->next[temp] = destination->next[previous_dest];
        destination->next[previous_dest] = temp;
        previous_dest = destination->next[previous_dest];
    }

    const size_t capacity = destination->size - (destination->size % REALLOC_FORWARD_LIST_CHUNK) + REALLOC_FORWARD_LIST_CHUNK;
    if (destination->size + source->size > capacity) { // increase destination capacity
        const size_t new_capacity = destination->size + source->size;
        const size_t split_chunk = new_capacity - (new_capacity % REALLOC_FORWARD_LIST_CHUNK) + REALLOC_FORWARD_LIST_CHUNK;

        destination->elements = FORWARD_LIST_REALLOC(destination->elements, sizeof(FORWARD_LIST_DATA_TYPE) * split_chunk);
        destination->next = FORWARD_LIST_REALLOC(destination->next, sizeof(size_t) * split_chunk);
    }

    while (source->size) { // fill to the end of source size
        previous_src = source->next[previous_src];
        memcpy(destination->elements + destination->size, source->elements + previous_src, sizeof(FORWARD_LIST_DATA_TYPE));
        source->size--;

        destination->next[destination->size] = destination->next[previous_dest];
        destination->next[previous_dest] = destination->size;
        destination->size++;
        previous_dest = destination->next[previous_dest];
    }

    if (index == size_dest) {
        destination->tail = previous_dest;
    }

    FORWARD_LIST_FREE(source->elements);
    FORWARD_LIST_FREE(source->next);
    *source = (forward_list_s) { 0 };
}

static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size) {
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    forward_list_s split = { .size = size, .elements = NULL, .empty_head = 0, .empty_size = 0, .next = NULL, .tail = 0 };

    if (size) {
        const size_t capacity = size - (size % REALLOC_FORWARD_LIST_CHUNK) + REALLOC_FORWARD_LIST_CHUNK;
        split.elements = FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * capacity);
        split.next = FORWARD_LIST_ALLOC(sizeof(size_t) * capacity);

        FORWARD_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");
        FORWARD_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed.");
    }

    size_t previous = list->tail;
    for (size_t i = 0; list->size && i < index + 1; ++i) {
        previous = list->next[previous];
    }
    if ((index + size) >= list->size) { // if tail node becomes part of split list new tail node will be the node previous to index/first-split node
        list->tail = previous;
    }

    for (size_t i = 1; size && i <= size; ++i) {
        previous = list->next[previous];

        const size_t mod = i % size;
        memcpy(split.elements + mod, list->elements + previous, sizeof(FORWARD_LIST_DATA_TYPE));
        split.next[i - 1] = mod;
        list->size--;

        list->next[previous] = list->next[previous];
        if (list->next[previous] != list->size) { // push empty index to 'empty stack'
            list->next[previous] = list->empty_head;
            list->empty_head = previous;
            list->empty_size++;
        }
    }

    if (list->size) {
        FORWARD_LIST_FREE(list->elements);
        FORWARD_LIST_FREE(list->next);
        *list = (forward_list_s) { 0 };
    }

    return split;
}

static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.tail && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) { // equal to index to take tail into account
        current = list.next[current];
    }

    return list.elements[current];
}

static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

static inline bool is_full_forward_list(const forward_list_s list) {
    return !(~list.size);
}

static inline forward_list_s copy_forward_list(const forward_list_s list, const copy_forward_list_fn copy) {
    forward_list_s list_copy = { 0 };
    list_copy.size = list.size;
    if (list.size) {
        const size_t capacity = list.size - (list.size % REALLOC_FORWARD_LIST_CHUNK) + REALLOC_FORWARD_LIST_CHUNK;
        list_copy.elements = FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * capacity);
        list_copy.next = FORWARD_LIST_ALLOC(sizeof(size_t) * capacity);

        FORWARD_LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
        FORWARD_LIST_ASSERT(list_copy.next && "[ERROR] Memory allocation failed.");
    }

    size_t previous = list.tail;
    for (size_t i = 0; list.size && i <= list.size; ++i) {
        previous = list.next[previous];

        const size_t mod = i % list.size;
        list_copy.elements[mod] = copy ? copy(list.elements[previous]) : list.elements[previous];
        list_copy.next[i - 1] = mod;
    }

    return list_copy;
}

static inline void sort_forward_list(forward_list_s * list, const sort_forward_list_fn sort) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    FORWARD_LIST_ASSERT(sort && "[ERROR] 'sort' parameter pointer is NULL");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (stack_size) { // removes holes at the expense of breaking the list
        if (empty_index > stack_size) {
            empty_index = list->next[empty_index];
        }

        FORWARD_LIST_DATA_TYPE element = list->elements[empty_index];
        list->elements[empty_index] = list->elements[stack_size];
        list->elements[stack_size] = element;

        const size_t index = list->next[empty_index];
        list->next[empty_index] = list->next[stack_size];
        list->next[stack_size] = empty_index;
        empty_index = index;

        stack_size--;
    }
    list->empty_size = 0;

    sort(list->elements, list->size);

    list->tail = list->size ? list->size - 1 : 0;
    for (size_t i = 1; list->size && i <= list->size; ++i) {
        const size_t mod = i % list->size;
        list->next[i - 1] = mod;
    }
}

static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    size_t base = list.tail;
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        size_t current = list.next[base]; // start from next element to move from tail and to ignore compared element
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(&element, list.elements + current) : memcmp(&element, list.elements + current, sizeof(FORWARD_LIST_DATA_TYPE));

        if (comparison == 0) {
            return true;
        }
        if (comparison > 0) {
            base = current; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(list->elements + previous);
        }

        previous = list->next[previous];
    }

    FORWARD_LIST_FREE(list->elements);
    FORWARD_LIST_FREE(list->next);
    *list = (forward_list_s) { 0 };
}

static inline void foreach_forward_list(forward_list_s * list, const operate_forward_list_fn operate, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = list->next[previous];

        if (!operate(list->elements + previous, args)) {
            return;
        }
    }
}

#elif FORWARD_LIST_MODE == FINITE_PRERPOCESSOR_FORWARD_LIST

#ifndef PREPROCESSOR_FORWARD_LIST_SIZE

#define PREPROCESSOR_FORWARD_LIST_SIZE (1 << 10)

#elif PREPROCESSOR_FORWARD_LIST_SIZE == 0

#error 'PREPROCESSOR_FORWARD_LIST_SIZE' cannot be zero

#endif

/// @brief The FINITE_ALLOCATED_FORWARD_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the forward_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
typedef struct forward_list {
    size_t size, empty_size, tail, empty_head;
    FORWARD_LIST_DATA_TYPE elements[PREPROCESSOR_FORWARD_LIST_SIZE];
    size_t next[PREPROCESSOR_FORWARD_LIST_SIZE];
} forward_list_s;

static inline forward_list_s create_forward_list(void) {
    const forward_list_s list = { .tail = 0, .size = 0, .empty_head = 0, .empty_size = 0, };

    return list;
}

static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(list->elements + previous);
        }

        previous = list->next[previous];
    }

    list->empty_head = list->empty_size = list->size = list->tail = 0;
}

static inline void insert_at_forward_list(forward_list_s * list, const size_t index, const FORWARD_LIST_DATA_TYPE element) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size < PREPROCESSOR_FORWARD_LIST_SIZE && "[ERROR] List reached maximum size.");
    FORWARD_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    FORWARD_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }

    if (list->empty_size) { // if 'empty stack' isn't empty pop empty index from it
        memcpy(list->elements + list->empty_head, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        const size_t temp = list->empty_head;
        list->empty_head = list->next[list->empty_head];
        list->empty_size--;

        list->next[temp] = list->next[previous];
        list->next[previous] = temp;
    } else { // else 'empty stack' is empty, therefore push element to the top of the 'loaded stack'
        memcpy(list->elements + list->size, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        list->next[list->size] = list->next[previous];
        list->next[previous] = list->size;
    }
    if (index == list->size) { // if index is at last/tail element tail must index to last added element
        list->tail = list->next[previous];
    }

    list->size++;
}

static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t current = list->next[previous];
        const int comparison = compare ? compare(list->elements + current, &element) : memcmp(list->elements + current, &element, sizeof(FORWARD_LIST_DATA_TYPE));
        if (0 == comparison) {
            list->size--;
            FORWARD_LIST_DATA_TYPE found = list->elements[current];

            list->next[previous] = list->next[current];

            if (list->next[current] != list->size) { // push empty index to 'empty stack'
                list->next[current] = list->empty_head;
                list->empty_head = current;
                list->empty_size++;
            }

            if (current == list->tail) { // if current is the last element
                list->tail = previous; // if list still has elements then tail will become the previous index
            }

            if (!list->size) {
                list->empty_head = list->empty_size = list->tail = 0;
            }

            return found;
        }
        previous = list->next[previous];
    }

    FORWARD_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    const size_t current = list->next[previous];

    list->size--;
    FORWARD_LIST_DATA_TYPE found = list->elements[current];

    list->next[previous] = list->next[current];

    if (list->next[current] != list->size) { // push empty index to 'empty stack'
        list->next[current] = list->empty_head;
        list->empty_head = current;
        list->empty_size++;
    }

    if (index == list->size) { // if last element is removed
        list->tail = previous; // if list still has elements then tail will become the previous index
    }

    if (!list->size) {
        list->empty_head = list->empty_size = list->tail = 0;
    }

    return found;
}

static inline void reverse_forward_list(forward_list_s * list) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    if (!list->size) {
        return;
    }

    size_t current = list->tail;
    size_t current_next = list->next[current];
    size_t current_next_next = list->next[current_next];
    list->tail = current_next;
    for (size_t i = 0; i < list->size; ++i) {
        list->next[current_next] = current;
        current = current_next;
        current_next = current_next_next;
        current_next_next = list->next[current_next_next];
    }
}

static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->tail && (s < shift); ++s) {
        list->tail = list->next[list->tail];
    }
}

static inline void splice_forward_list(forward_list_s * restrict destination, forward_list_s * restrict source, const size_t index) {
    FORWARD_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    FORWARD_LIST_ASSERT(destination->size + source->size <= PREPROCESSOR_FORWARD_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    FORWARD_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    const size_t size_dest = destination->size;

    size_t previous_dest = destination->tail;
    for (size_t i = 0; size_dest && index != size_dest && i < index; ++i) {
        previous_dest = destination->next[previous_dest];
    }

    size_t previous_src = source->tail;
    while (source->size && destination->empty_size) {
        previous_src = destination->next[previous_src];
        memcpy(destination->elements + destination->empty_head, source->elements + previous_src, sizeof(FORWARD_LIST_DATA_TYPE));
        source->size--;

        const size_t temp = destination->empty_head;
        destination->empty_head = destination->next[destination->empty_head];
        destination->empty_size--;

        destination->next[temp] = destination->next[previous_dest];
        destination->next[previous_dest] = temp;
        destination->size++;

        previous_dest = destination->next[previous_dest];
    }

    while (source->size) {
        previous_src = destination->next[previous_src];
        memcpy(destination->elements + destination->size, source->elements + previous_src, sizeof(FORWARD_LIST_DATA_TYPE));
        source->size--;

        destination->next[destination->size] = destination->next[previous_dest];
        destination->next[previous_dest] = destination->size;
        destination->size++;

        previous_dest = destination->next[previous_dest];
    }

    if (size_dest && index == size_dest) {
        destination->tail = previous_dest;
    }

    source->empty_head = source->empty_size = source->size = source->tail = 0;
}

static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size) {
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    forward_list_s split = { .empty_head = 0, .empty_size = 0, .size = 0, .tail = 0 };

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    if ((index + size) >= list->size) { // if tail node becomes part of split list new tail node will be the node previous to index/first-split node
        list->tail = previous;
    }

    for (size_t i = 1; size && i <= size; ++i) {
        previous = list->next[previous];

        const size_t mod = i % size;
        memcpy(split.elements + mod, list->elements + previous, sizeof(FORWARD_LIST_DATA_TYPE));
        split.next[i - 1] = mod;
        list->size--;

        list->next[previous] = list->next[previous];
        if (list->next[previous] != list->size) { // push empty index to 'empty stack'
            list->next[previous] = list->empty_head;
            list->empty_head = previous;
            list->empty_size++;
        }
    }

    return split;
}

static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.tail && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

static inline bool is_full_forward_list(const forward_list_s list) {
    return !(~list.size);
}

static inline forward_list_s copy_forward_list(const forward_list_s list, const copy_forward_list_fn copy) {
    forward_list_s list_copy = { .empty_head = 0, .empty_size = 0, .size = list.size, .tail = 0, };

    size_t previous = list.tail;
    for (size_t i = 0; list.size && i <= list.size; ++i) {
        previous = list.next[previous];

        const size_t mod = i % list.size;
        list_copy.elements[mod] = copy ? copy(list.elements[previous]) : list.elements[previous];
        list_copy.next[i - 1] = mod;
    }

    return list_copy;
}

static inline void sort_forward_list(forward_list_s * list, const sort_forward_list_fn sort) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    FORWARD_LIST_ASSERT(sort && "[ERROR] 'sort' parameter pointer is NULL");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (stack_size) { // removes holes at the expense of breaking the list
        if (empty_index > stack_size) {
            empty_index = list->next[empty_index];
        }

        FORWARD_LIST_DATA_TYPE element = list->elements[empty_index];
        list->elements[empty_index] = list->elements[stack_size];
        list->elements[stack_size] = element;

        const size_t index = list->next[empty_index];
        list->next[empty_index] = list->next[stack_size];
        list->next[stack_size] = empty_index;
        empty_index = index;

        stack_size--;
    }
    list->empty_size = 0;

    sort(list->elements, list->size);

    list->tail = list->size ? list->size - 1 : 0;
    for (size_t i = 1; list->size && i <= list->size; ++i) {
        const size_t mod = i % list->size;
        list->next[i - 1] = mod;
    }
}

static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    size_t base = list.tail;
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        size_t current = list.next[base]; // start from next element to move from tail and to ignore compared element
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(&element, list.elements + current) : memcmp(&element, list.elements + current, sizeof(FORWARD_LIST_DATA_TYPE));

        if (comparison == 0) {
            return true;
        }
        if (comparison > 0) {
            base = current; // increment element pointer to next
            limit--;
        }
    }

    return false;
}

static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(list->elements + previous);
        }

        previous = list->next[previous];
    }

    list->empty_head = list->empty_size = list->size = list->tail = 0;
}

static inline void foreach_forward_list(forward_list_s * list, const operate_forward_list_fn operate, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = list->next[previous];

        if (!operate(list->elements + previous, args)) {
            return;
        }
    }
}

#endif

#endif //FORWARD_FORWARD_FORWARD_LIST_H
