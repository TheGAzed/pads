#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stdlib.h>  // imports size_t and malloc
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy

// list mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_ALLOCATED_DOUBLE_LIST  0x11
#define FINITE_ALLOCATED_DOUBLE_LIST    0x12
#define INFINITE_REALLOC_DOUBLE_LIST    0x13
#define FINITE_PRERPOCESSOR_DOUBLE_LIST 0x14

#define INFINITE_DOUBLE_LIST INFINITE_ALLOCATED_DOUBLE_LIST
#define FINITE_DOUBLE_LIST   FINITE_ALLOCATED_DOUBLE_LIST

//#define DOUBLE_LIST_MODE INFINITE_ALLOCATED_DOUBLE_LIST
//#define DOUBLE_LIST_MODE FINITE_ALLOCATED_DOUBLE_LIST
//#define DOUBLE_LIST_MODE INFINITE_REALLOC_DOUBLE_LIST
//#define DOUBLE_LIST_MODE FINITE_PRERPOCESSOR_DOUBLE_LIST
// List mode that can be set to INFINITE_ALLOCATED_DOUBLE_LIST, FINITE_ALLOCATED_DOUBLE_LIST, INFINITE_REALLOC_DOUBLE_LIST or
// FINITE_PRERPOCESSOR_DOUBLE_LIST, or INFINITE_ALLOCATED_DOUBLE_LIST or FINITE_ALLOCATED_DOUBLE_LIST
// Default: INFINITE_ALLOCATED_DOUBLE_LIST
#ifndef DOUBLE_LIST_MODE

#define DOUBLE_LIST_MODE INFINITE_ALLOCATED_DOUBLE_LIST

#endif

#define IS_INFINITE_DOUBLE_LIST ((bool)(DOUBLE_LIST_MODE & 0x01))

// Check to make sure a valid list mode is selected.
#if (DOUBLE_LIST_MODE != INFINITE_ALLOCATED_DOUBLE_LIST) && (DOUBLE_LIST_MODE != FINITE_ALLOCATED_DOUBLE_LIST)    && \
    (DOUBLE_LIST_MODE != INFINITE_REALLOC_DOUBLE_LIST)   && (DOUBLE_LIST_MODE != FINITE_PRERPOCESSOR_DOUBLE_LIST)

#error Invalid type of list mode.

#endif

// List data type to specify what datatype to list.
// DEFAULT: void *
#ifndef DOUBLE_LIST_DATA_TYPE

#define DOUBLE_LIST_DATA_TYPE void*

#endif

#ifndef DOUBLE_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
#define DOUBLE_LIST_ASSERT assert

#endif

#ifndef DOUBLE_LIST_ALLOC

#define DOUBLE_LIST_ALLOC malloc

#endif

#ifndef DOUBLE_LIST_REALLOC

#define DOUBLE_LIST_REALLOC realloc

#endif

#ifndef DOUBLE_LIST_FREE

#define DOUBLE_LIST_FREE free

#endif

typedef DOUBLE_LIST_DATA_TYPE (*copy_double_list_fn)    (const DOUBLE_LIST_DATA_TYPE);
typedef void                  (*destroy_double_list_fn) (DOUBLE_LIST_DATA_TYPE *);
typedef int                   (*compare_double_list_fn) (const void *, const void *);
typedef bool                  (*operate_double_list_fn) (DOUBLE_LIST_DATA_TYPE *, void *);
typedef void                  (*sort_double_list_fn)    (void * array, size_t number, size_t size, compare_double_list_fn);

#if   DOUBLE_LIST_MODE == INFINITE_ALLOCATED_DOUBLE_LIST

struct double_list_node {
    DOUBLE_LIST_DATA_TYPE element;
    struct double_list_node * next;
    struct double_list_node * prev;
};

typedef struct double_list {
    size_t size;
    struct double_list_node * head;
} double_list_s;

static inline double_list_s create_double_list(void) {
    return (double_list_s) { 0 };
}

static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct double_list_node * current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        if (destroy) {
            destroy(&(current->element));
        }

        struct double_list_node * temp = current;
        current = current->next;
        DOUBLE_LIST_FREE(temp);
    }

    *list = (double_list_s) { 0 };
}

static inline void insert_at_double_list(double_list_s * list, const size_t index, DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    struct double_list_node * temp = DOUBLE_LIST_ALLOC(sizeof(struct double_list_node));
    DOUBLE_LIST_ASSERT(temp && "[ERROR] Memory allocation failed.");
    temp->element = element;

    struct double_list_node * current = list->head;
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

static inline DOUBLE_LIST_DATA_TYPE remove_element_double_list(double_list_s * list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    struct double_list_node ** current = &(list->head);
    for (size_t s = 0; s < list->size; ++s) {
        const int cmp = compare ? compare(&((*current)->element), &element) : memcmp(&((*current)->element), &element, sizeof(DOUBLE_LIST_DATA_TYPE));
        if (cmp == 0) {
            DOUBLE_LIST_DATA_TYPE found = (*current)->element;

            struct double_list_node * temp = *current;
            (*current)->next->prev = (*current)->prev;
            *current = (--list->size) ? (*current)->next : NULL;
            DOUBLE_LIST_FREE(temp);

            return found;
        }
        current = &((*current)->next);
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct double_list_node * temp = NULL;
    if (index < (list->size >> 1)) { // special case when index is 0 so head must change to next
        struct double_list_node ** current = &(list->head);
        for (size_t i = 0; i < index; ++i) {
            current = &((*current)->next);
        }

        temp = *current;
        *current = (*current)->next;
    } else { // no special case that head might change
        temp = list->head;
        for (size_t i = 0; i < list->size - index; ++i) {
            temp = temp->prev;
        }
    }

    DOUBLE_LIST_DATA_TYPE found = temp->element;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    DOUBLE_LIST_FREE(temp);

    list->size--;

    if (!list->size) {
        list->head = NULL;
    }

    return found;
}

static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct double_list_node * current = list->head = list->head ? list->head->prev : list->head;
    for (size_t s = 0; s < list->size; ++s) {
        struct double_list_node * temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        current = current->next;
    }
}

static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->head && (s < shift); ++s) {
        list->head = list->head->next;
    }
}

static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->head && (s < shift); ++s) {
        list->head = list->head->prev;
    }
}

static inline double_list_s splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'destination' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'source' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed destination's size");

    struct double_list_node * current = destination->head;
    if (index < (destination->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        for (size_t i = 0; i < destination->size - index; ++i) {
            current = current->prev;
        }
    }

    if (current && source->head) {
        current->prev->next = source->head;
        source->head->prev = current->prev;

        source->head->prev->next = current;
        current->prev = source->head->prev;
    }

    double_list_s list = { .size = destination->size + source->size, .head = index ? destination->head : source->head, };

    *destination = *source = (double_list_s) { 0 };

    return list;
}

static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(size && "[ERROR] Can't split size zero.");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    struct double_list_node * index_node = list->head;
    if (index <= (list->size >> 1)) {
        for (size_t i = 0; i < index; ++i) { index_node = index_node->next; }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) { index_node = index_node->prev; }
    }

    struct double_list_node * size_node = index_node;
    if (size <= (list->size >> 1)) {
        for (size_t i = 0; i < size - 1; ++i) { size_node = size_node->next; }
    } else {
        for (size_t i = 0; i < list->size - size - 1; ++i) { size_node = size_node->prev; }
    }

    list->size -= size;
    if (!index || ((index + size) > list->size)) list->head = size_node->next;
    if (!list->size) list->head = NULL;

    index_node->prev->next = size_node->next;
    size_node->next->prev = index_node->prev;

    index_node->prev = size_node;
    size_node->next = index_node;

    return (double_list_s) { .head = index_node, .size = size };
}

static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.head && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct double_list_node const * current = list.head;
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

static inline size_t index_of_double_list(const double_list_s list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get index from empty list.");
    DOUBLE_LIST_ASSERT(list.head && "[ERROR] Can't get index from empty list.");

    struct double_list_node const * current = list.head;
    for (size_t s = 0; s < list.size; ++s) {
        const int cmp = compare ? compare(&(current->element), &element) : memcmp(&(current->element), &element, sizeof(DOUBLE_LIST_DATA_TYPE));
        if (cmp == 0) {
            return s;
        }

        current = current->next;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_double_list(const double_list_s list) {
    return list.size == 0;
}

static inline bool is_full_double_list(const double_list_s list) {
    return !(~list.size);
}

static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    double_list_s list_copy = { .head = NULL, .size = list.size };

    struct double_list_node const * current_list = list.head;
    struct double_list_node ** current_copy = &(list_copy.head);
    for (size_t i = 0; i < list.size; ++i) {
        struct double_list_node * temp = DOUBLE_LIST_ALLOC(sizeof(struct double_list_node));
        DOUBLE_LIST_ASSERT(temp && "[ERROR] Memory allocation failed");
        temp->element = copy ? copy(current_list->element) : current_list->element;

        temp->prev = (*current_copy); // prev reference is stored in *current_copy
        (*current_copy) = temp->next = temp; // (*current_copy)->next will have reference to prev list node

        current_list = current_list->next;
        current_copy = &((*current_copy)->next);
    }

    if (current_copy != &(list_copy.head)) {
        list_copy.head->prev = (*current_copy); // copy.head won't have prev reference to last node
        (*current_copy)->next = list_copy.head; // *current_copy or last node won't have reference to head
    }

    return list_copy;
}

static inline void sort_double_list(double_list_s const * list, const sort_double_list_fn sort, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    DOUBLE_LIST_ASSERT(sort && "[ERROR] 'sort' parameter pointer is NULL");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' parameter pointer is NULL");

    DOUBLE_LIST_DATA_TYPE * elements_array = DOUBLE_LIST_ALLOC(sizeof(DOUBLE_LIST_DATA_TYPE) * list->size);
    DOUBLE_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct double_list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = current->element;
        current = current->next;
    }

    sort(elements_array, list->size, sizeof(DOUBLE_LIST_DATA_TYPE), compare);

    current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current->element = elements_array[i];
        current = current->next;
    }
    DOUBLE_LIST_FREE(elements_array);
}

static inline void foreach_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct double_list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&current->element, args)) return;

        current = current->next;
    }
}

#elif DOUBLE_LIST_MODE == FINITE_ALLOCATED_DOUBLE_LIST

#define NODE_COUNT 2
#define NEXT_IDX   0
#define PREV_IDX   1
typedef struct list {
    size_t size, max, head;

    DOUBLE_LIST_DATA_TYPE * elements;
    size_t * node[NODE_COUNT];
} double_list_s;

static inline double_list_s create_double_list(const size_t max) {
    DOUBLE_LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const double_list_s list = {
        .elements = DOUBLE_LIST_ALLOC(sizeof(DOUBLE_LIST_DATA_TYPE) * max),
        .node[NEXT_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * max), .node[PREV_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * max),

        .head = 0, .max = max, .size = 0,
    };

    DOUBLE_LIST_ASSERT(list.elements && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    return list;
}

static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy && (s < list->size); ++s) {
        destroy(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    DOUBLE_LIST_FREE(list->elements); DOUBLE_LIST_FREE(list->node[NEXT_IDX]); DOUBLE_LIST_FREE(list->node[PREV_IDX]);

    *list = (double_list_s) { 0 };
}

static inline void insert_at_double_list(double_list_s * list, const size_t index, DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size < list->max && "[ERROR] List reached maximum size.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

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
    if (!index) list->head = list->size;

    list->elements[(list->size)++] = element;
}

static inline DOUBLE_LIST_DATA_TYPE remove_element_double_list(double_list_s * list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    DOUBLE_LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[NEXT_IDX] && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[PREV_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        if (compare) {
            if (compare(&(list->elements[current]), &element) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        } else {
            if (memcmp(&(list->elements[current]), &element, sizeof(DOUBLE_LIST_DATA_TYPE)) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        DOUBLE_LIST_DATA_TYPE found = list->elements[current];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size - 1]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size - 1]] = current;
        list->elements[current] = list->elements[--(list->size)];

        return found;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

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
    DOUBLE_LIST_DATA_TYPE found = list->elements[current];

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    list->size--;
    list->elements[current] = list->elements[list->size];

    list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;

    return found;
}

static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[NEXT_IDX][current];
    }
    if (list->size) list->head = list->node[NEXT_IDX][list->head];
}

static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline double_list_s splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index, const size_t max) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'destination' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'source' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    DOUBLE_LIST_ASSERT(destination->size + source->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed destination's size");

    source->head += destination->size;
    for (size_t i = 0; i < source->size; ++i) { // incrementing sources indexes since they get appended to destination
        source->node[NEXT_IDX][i] += destination->size;
        source->node[PREV_IDX][i] += destination->size;
    }

    destination->elements = DOUBLE_LIST_REALLOC(destination->elements, sizeof(DOUBLE_LIST_DATA_TYPE) * max);
    destination->node[NEXT_IDX] = DOUBLE_LIST_REALLOC(destination->node[NEXT_IDX], sizeof(size_t) * max);
    destination->node[PREV_IDX] = DOUBLE_LIST_REALLOC(destination->node[PREV_IDX], sizeof(size_t) * max);

    size_t current = destination->head;
    if (index < (destination->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = destination->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < destination->size - index; ++i) {
            current = destination->node[PREV_IDX][current];
        }
    }

    if (destination->size && source->size) {
        destination->node[NEXT_IDX][destination->node[PREV_IDX][current]] = source->head;
        source->node[PREV_IDX][source->head] = destination->node[PREV_IDX][current];

        source->node[NEXT_IDX][source->node[PREV_IDX][source->head]] = current;
        destination->node[PREV_IDX][current] = source->node[PREV_IDX][source->head];
    }

    memcpy(destination->elements + destination->size, source->elements, sizeof(DOUBLE_LIST_DATA_TYPE) * source->size);
    memcpy(destination->node[NEXT_IDX] + destination->size, source->node[NEXT_IDX], sizeof(size_t) * source->size);
    memcpy(destination->node[PREV_IDX] + destination->size, source->node[PREV_IDX], sizeof(size_t) * source->size);

    DOUBLE_LIST_FREE(source->elements);
    DOUBLE_LIST_FREE(source->node[NEXT_IDX]);
    DOUBLE_LIST_FREE(source->node[PREV_IDX]);

    double_list_s list = {
        .size = destination->size + source->size, .head = index ? destination->head : source->head, .max = max,
        .node[NEXT_IDX] = destination->node[NEXT_IDX], .node[PREV_IDX] = destination->node[PREV_IDX],
        .elements = destination->elements,
    };

    *destination = *source = (double_list_s) { 0 };

    return list;
}

static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size, const size_t max) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(max && "[ERROR] max size can't be zero.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    DOUBLE_LIST_ASSERT(size <= max && "[ERROR] List size exceed max size of new split list.");

    if (!size) {
        return (double_list_s) { 0 };
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

    double_list_s const split_list = {
        .elements = DOUBLE_LIST_ALLOC(sizeof(DOUBLE_LIST_DATA_TYPE) * max), .head = 0, .size = size,
        .node[NEXT_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * max), .node[PREV_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * max),
    };

    DOUBLE_LIST_ASSERT(split_list.elements && "[ERROR] Memory allocation failed");
    DOUBLE_LIST_ASSERT(split_list.node[NEXT_IDX] && "[ERROR] Memory allocation failed");
    DOUBLE_LIST_ASSERT(split_list.node[PREV_IDX] && "[ERROR] Memory allocation failed");

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

static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

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

static inline size_t index_of_double_list(const double_list_s list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get index from empty list.");

    size_t current = list.head;
    if (compare) {
        for (size_t s = 0; s < list.size; ++s) {
            if (compare(&(list.elements[current]), &element) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t s = 0; s < list.size; ++s) {
            if (memcmp(&(list.elements[current]), &element, sizeof(DOUBLE_LIST_DATA_TYPE)) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    }

    DOUBLE_LIST_ASSERT(false && "[ERROR] Element index not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_double_list(const double_list_s list) {
    return list.size == 0;
}

static inline bool is_full_double_list(const double_list_s list) {
    return !(~list.size);
}

static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    const double_list_s list_copy = {
        .elements = DOUBLE_LIST_ALLOC(sizeof(DOUBLE_LIST_DATA_TYPE) * list.max),
        .node[NEXT_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * list.max), .node[PREV_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * list.max),
        .head = list.head, .max = list.max, .size = list.size,
    };

    DOUBLE_LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list_copy.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list_copy.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t i = 0; i < list.size; ++i) {
            list_copy.elements[i] = copy(list.elements[i]);
            list_copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            list_copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(list_copy.elements, list.elements, list.size * sizeof(DOUBLE_LIST_DATA_TYPE));
        memcpy(list_copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(list_copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return list_copy;
}

static inline void sort_double_list(double_list_s * list, const sort_double_list_fn sort, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    DOUBLE_LIST_ASSERT(sort && "[ERROR] 'sort' function pointer parameter is NULL");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' function pointer parameter is NULL");

    sort(list->elements, list->size, sizeof(DOUBLE_LIST_DATA_TYPE), compare);

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

static inline void foreach_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&(list->elements[current]), args)) return;

        current = list->node[NEXT_IDX][current];
    }
}

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#elif DOUBLE_LIST_MODE == INFINITE_REALLOC_DOUBLE_LIST

#ifndef REALLOC_DOUBLE_LIST_CHUNK

#define REALLOC_DOUBLE_LIST_CHUNK (1 << 10)

#endif

#define NEXT_IDX   0
#define PREV_IDX   1
#define NODE_COUNT 2
typedef struct list {
    size_t size, head;

    DOUBLE_LIST_DATA_TYPE * elements;
    size_t * node[NODE_COUNT];
} double_list_s;

static inline double_list_s create_double_list(void) {
    return (double_list_s) { 0 };
}

static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy && (s < list->size); ++s) {
        destroy(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    DOUBLE_LIST_FREE(list->elements);
    for (size_t i = 0; i < NODE_COUNT; ++i) {
        DOUBLE_LIST_FREE(list->node[i]);
    }

    *list = (double_list_s) { 0 };
}

static inline void insert_at_double_list(double_list_s * list, const size_t index, DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    if (!(list->size % REALLOC_DOUBLE_LIST_CHUNK)) {
        list->elements = DOUBLE_LIST_REALLOC(list->elements, (list->size + REALLOC_DOUBLE_LIST_CHUNK) * sizeof(DOUBLE_LIST_DATA_TYPE));
        list->node[NEXT_IDX] = DOUBLE_LIST_REALLOC(list->elements, (list->size + REALLOC_DOUBLE_LIST_CHUNK) * sizeof(size_t));
        list->node[PREV_IDX] = DOUBLE_LIST_REALLOC(list->elements, (list->size + REALLOC_DOUBLE_LIST_CHUNK) * sizeof(size_t));
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

    list->elements[(list->size)++] = element;
}

static inline DOUBLE_LIST_DATA_TYPE remove_element_double_list(double_list_s * list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    DOUBLE_LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[PREV_IDX] && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[NEXT_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        if (compare) {
            if (compare(list->elements + current, &element) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        } else {
            if (memcmp(&(list->elements[current]), &element, sizeof(DOUBLE_LIST_DATA_TYPE)) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        DOUBLE_LIST_DATA_TYPE found = list->elements[current];

        list->node[PREV_IDX][list->node[NEXT_IDX][list->size - 1]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size - 1]] = current;
        list->elements[current] = list->elements[--(list->size)];

        if (!(list->size % REALLOC_DOUBLE_LIST_CHUNK)) {
            list->elements = list->size ? DOUBLE_LIST_REALLOC(list->elements, list->size * sizeof(DOUBLE_LIST_DATA_TYPE)) : NULL;
            list->node[PREV_IDX] = list->size ? DOUBLE_LIST_REALLOC(list->node[PREV_IDX], list->size * sizeof(size_t)) : NULL;
            list->node[NEXT_IDX] = list->size ? DOUBLE_LIST_REALLOC(list->node[NEXT_IDX], list->size * sizeof(size_t)) : NULL;
        }

        return found;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index parameter greater than list size.");

    size_t current = list->head, smaller_size = list->size - index, node_index = PREV_IDX;
    if (index <= (list->size >> 1)) {
        smaller_size = index;
        node_index = NEXT_IDX;
    }
    for (size_t i = 0; i < smaller_size; ++i) {
        current = list->node[node_index][current];
    }

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    DOUBLE_LIST_DATA_TYPE found = list->elements[current];

    list->node[PREV_IDX][list->node[NEXT_IDX][list->size - 1]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size - 1]] = current;
    list->elements[current] = list->elements[--(list->size)];

    if (!(list->size % REALLOC_DOUBLE_LIST_CHUNK)) {
        if (list->size) {
            list->elements = DOUBLE_LIST_REALLOC(list->elements, list->size * sizeof(DOUBLE_LIST_DATA_TYPE));
            list->node[PREV_IDX] = DOUBLE_LIST_REALLOC(list->node[PREV_IDX], list->size * sizeof(size_t));
            list->node[NEXT_IDX] = DOUBLE_LIST_REALLOC(list->node[NEXT_IDX], list->size * sizeof(size_t));
        } else {
            list->elements = (DOUBLE_LIST_DATA_TYPE *) (list->node[PREV_IDX] = list->node[NEXT_IDX] = NULL);
        }
    }

    return found;
}

static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    size_t current = list->head = list->size ? list->node[PREV_IDX][list->head] : list->head;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[NEXT_IDX][current];
    }
}

static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline double_list_s splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'destination' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'source' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed destination's size");

    const size_t new_size = (destination->size + source->size);
    if (!new_size) return (double_list_s) { 0 };

    const size_t alloc_size = new_size - (new_size % REALLOC_DOUBLE_LIST_CHUNK) + REALLOC_DOUBLE_LIST_CHUNK;

    source->head += destination->size;
    for (size_t i = 0; i < source->size; ++i) { // incrementing sources indexes since they get appended to destination
        source->node[NEXT_IDX][i] += destination->size;
        source->node[PREV_IDX][i] += destination->size;
    }

    destination->elements = DOUBLE_LIST_REALLOC(destination->elements, sizeof(DOUBLE_LIST_DATA_TYPE) * alloc_size);
    destination->node[NEXT_IDX] = DOUBLE_LIST_REALLOC(destination->node[NEXT_IDX], sizeof(size_t) * alloc_size);
    destination->node[PREV_IDX] = DOUBLE_LIST_REALLOC(destination->node[PREV_IDX], sizeof(size_t) * alloc_size);

    size_t current = destination->head;
    if (index < (destination->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = destination->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < destination->size - index; ++i) {
            current = destination->node[PREV_IDX][current];
        }
    }

    if (destination->size && source->size) {
        destination->node[NEXT_IDX][destination->node[PREV_IDX][current]] = source->head;
        source->node[PREV_IDX][source->head] = destination->node[PREV_IDX][current];

        source->node[NEXT_IDX][source->node[PREV_IDX][source->head]] = current;
        destination->node[PREV_IDX][current] = source->node[PREV_IDX][source->head];
    }

    memcpy(destination->elements + destination->size, source->elements, sizeof(DOUBLE_LIST_DATA_TYPE) * source->size);
    memcpy(destination->node[NEXT_IDX] + destination->size, source->node[NEXT_IDX], sizeof(size_t) * source->size);
    memcpy(destination->node[PREV_IDX] + destination->size, source->node[PREV_IDX], sizeof(size_t) * source->size);

    DOUBLE_LIST_FREE(source->elements);
    DOUBLE_LIST_FREE(source->node[NEXT_IDX]);
    DOUBLE_LIST_FREE(source->node[PREV_IDX]);

    double_list_s list = {
        .head = index ? destination->head : source->head, .elements = destination->elements, .size = new_size,
        .node[NEXT_IDX] = destination->node[NEXT_IDX], .node[PREV_IDX] = destination->node[PREV_IDX],
    };

    *destination = *source = (double_list_s) { 0 };

    return list;
}

static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) { return (double_list_s) { 0 }; }

    const size_t split_chunk = size - (size % REALLOC_DOUBLE_LIST_CHUNK) + REALLOC_DOUBLE_LIST_CHUNK;
    double_list_s const split_list = {
        .elements = DOUBLE_LIST_ALLOC(sizeof(DOUBLE_LIST_DATA_TYPE) * split_chunk), .head = 0, .size = size,
        .node[NEXT_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * split_chunk), .node[PREV_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * split_chunk),
    };

    DOUBLE_LIST_ASSERT(split_list.elements && "[ERROR] Memory allocation failed");
    DOUBLE_LIST_ASSERT(split_list.node[NEXT_IDX] && "[ERROR] Memory allocation failed");
    DOUBLE_LIST_ASSERT(split_list.node[PREV_IDX] && "[ERROR] Memory allocation failed");

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
            if (!(list->size % REALLOC_DOUBLE_LIST_CHUNK)) { // shorten chunk to save memory if possible
                list->elements = DOUBLE_LIST_REALLOC(list->elements, list->size * sizeof(DOUBLE_LIST_DATA_TYPE));
                list->node[PREV_IDX] = DOUBLE_LIST_REALLOC(list->node[PREV_IDX], list->size * sizeof(size_t));
                list->node[NEXT_IDX] = DOUBLE_LIST_REALLOC(list->node[NEXT_IDX], list->size * sizeof(size_t));
            }

            current = list->node[NEXT_IDX][current];
        } else {
            DOUBLE_LIST_FREE(list->elements);
            DOUBLE_LIST_FREE(list->node[PREV_IDX]);
            DOUBLE_LIST_FREE(list->node[NEXT_IDX]);
            list->elements = (DOUBLE_LIST_DATA_TYPE *) (list->node[PREV_IDX] = list->node[NEXT_IDX] = NULL);
        }
    }
    split_list.node[NEXT_IDX][split_list.size - 1] = 0; split_list.node[PREV_IDX][0] = split_list.size - 1;

    if (!index || ((index + size) > list->size)) {
        list->head = current;
    }

    return split_list;
}

static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

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

static inline size_t index_of_double_list(const double_list_s list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get index from empty list.");

    size_t current = list.head;
    if (compare) {
        for (size_t s = 0; s < list.size; ++s) {
            if (compare(&(list.elements[current]), &element) == 0) {
                return s;
            }

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t s = 0; s < list.size; ++s) {
            if (memcmp(&(list.elements[current]), &element, sizeof(DOUBLE_LIST_DATA_TYPE)) == 0) {
                return s;
            }

            current = list.node[NEXT_IDX][current];
        }
    }

    DOUBLE_LIST_ASSERT(false && "[ERROR] Element index not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_double_list(const double_list_s list) {
    return list.size == 0;
}

static inline bool is_full_double_list(const double_list_s list) {
    return !((~list.size) && (list.size < REALLOC_DOUBLE_LIST_CHUNK));
}

static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    if (!list.size) return (double_list_s) { 0 };

    const size_t copy_chunk = list.size - (list.size % REALLOC_DOUBLE_LIST_CHUNK) + REALLOC_DOUBLE_LIST_CHUNK;
    const double_list_s list_copy = {
        .elements = DOUBLE_LIST_ALLOC(sizeof(DOUBLE_LIST_DATA_TYPE) * copy_chunk),
        .node[NEXT_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * copy_chunk), .node[PREV_IDX] = DOUBLE_LIST_ALLOC(sizeof(size_t) * copy_chunk),
        .head = list.head, .size = list.size,
    };

    DOUBLE_LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list_copy.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list_copy.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t i = 0; i < list.size; ++i) {
            list_copy.elements[i] = copy(list.elements[i]);
            list_copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            list_copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(list_copy.elements, list.elements, list.size * sizeof(DOUBLE_LIST_DATA_TYPE));
        memcpy(list_copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(list_copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return list_copy;
}

static inline void sort_double_list(double_list_s * list, const sort_double_list_fn sort, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    DOUBLE_LIST_ASSERT(sort && "[ERROR] 'sort' function pointer parameter is NULL");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' function pointer parameter is NULL");

    sort(list->elements, list->size, sizeof(DOUBLE_LIST_DATA_TYPE), compare);

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

static inline void foreach_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&(list->elements[current]), args)) return;

        current = list->node[NEXT_IDX][current];
    }
}

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#elif DOUBLE_LIST_MODE == FINITE_PRERPOCESSOR_DOUBLE_LIST

#ifndef PREPROCESSOR_DOUBLE_LIST_SIZE

#define PREPROCESSOR_DOUBLE_LIST_SIZE (1 << 10)

#elif PREPROCESSOR_DOUBLE_LIST_SIZE == 0

#error 'PREPROCESSOR_DOUBLE_LIST_SIZE' cannot be zero

#endif

#define NODE_COUNT 2
#define NEXT_IDX   0
#define PREV_IDX   1
typedef struct list {
    size_t size, head;

    DOUBLE_LIST_DATA_TYPE elements[PREPROCESSOR_DOUBLE_LIST_SIZE];
    size_t node[NODE_COUNT][PREPROCESSOR_DOUBLE_LIST_SIZE];
} double_list_s;

static inline double_list_s create_double_list(void) {
    return (double_list_s) { .size = 0, .head = 0, };
}

static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy && (s < list->size); ++s) {
        destroy(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    list->size = list->head = 0;
}

static inline void insert_at_double_list(double_list_s * list, const size_t index, DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size < PREPROCESSOR_DOUBLE_LIST_SIZE && "[ERROR] List reached maximum size.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

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
    if (!index) list->head = list->size;

    list->elements[(list->size)++] = element;
}

static inline DOUBLE_LIST_DATA_TYPE remove_element_double_list(double_list_s * list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        int comparison = compare ? compare(&(list->elements[current]), &element) : memcmp(&(list->elements[current]), &element, sizeof(DOUBLE_LIST_DATA_TYPE));
        if (comparison != 0) {
            current = list->node[NEXT_IDX][current];
            continue;
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        DOUBLE_LIST_DATA_TYPE found = list->elements[current];

        list->size--;
        list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return found;
    }

    DOUBLE_LIST_ASSERT(false && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

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

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    DOUBLE_LIST_DATA_TYPE found = list->elements[current];

    list->size--;
    list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;
    list->elements[current] = list->elements[list->size];

    return found;
}

static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[NEXT_IDX][current];
    }
    if (list->size) list->head = list->node[NEXT_IDX][list->head];
}

static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline double_list_s splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'destination' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'source' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed destination's size");
    DOUBLE_LIST_ASSERT(destination->size + source->size <= PREPROCESSOR_DOUBLE_LIST_SIZE && "[ERROR] new list's size exceeds PREPROCESSOR_DOUBLE_LIST_SIZE");

    source->head += destination->size;
    for (size_t i = 0; i < source->size; ++i) { // incrementing sources indexes since they get appended to destination
        source->node[NEXT_IDX][i] += destination->size;
        source->node[PREV_IDX][i] += destination->size;
    }

    size_t current = destination->head;
    if (index < (destination->size >> 1)) {
        for (size_t i = 0; i < index; ++i) {
            current = destination->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < destination->size - index; ++i) {
            current = destination->node[PREV_IDX][current];
        }
    }

    if (destination->size && source->size) {
        destination->node[NEXT_IDX][destination->node[PREV_IDX][current]] = source->head;
        source->node[PREV_IDX][source->head] = destination->node[PREV_IDX][current];

        source->node[NEXT_IDX][source->node[PREV_IDX][source->head]] = current;
        destination->node[PREV_IDX][current] = source->node[PREV_IDX][source->head];
    }

    double_list_s list = { .head = index ? destination->head : source->head, .size = destination->size + source->size, };
    memcpy(list.elements, destination->elements, sizeof(DOUBLE_LIST_DATA_TYPE) * destination->size);
    memcpy(list.node[NEXT_IDX], destination->node[NEXT_IDX], sizeof(size_t) * destination->size);
    memcpy(list.node[PREV_IDX], destination->node[PREV_IDX], sizeof(size_t) * destination->size);

    memcpy(list.elements + destination->size, source->elements, sizeof(DOUBLE_LIST_DATA_TYPE) * source->size);
    memcpy(list.node[NEXT_IDX] + destination->size, source->node[NEXT_IDX], sizeof(size_t) * source->size);
    memcpy(list.node[PREV_IDX] + destination->size, source->node[PREV_IDX], sizeof(size_t) * source->size);

    destination->size = source->size = 0;
    destination->head = source->head = 0;

    return list;
}

static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) {
        return (double_list_s) { .head = 0, .size = 0 };
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

    double_list_s split_list = { .head = 0, .size = size, };

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

static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

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

static inline size_t index_of_double_list(const double_list_s list, DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get index from empty list.");

    size_t current = list.head;
    if (compare) {
        for (size_t s = 0; s < list.size; ++s) {
            if (compare(&(list.elements[current]), &element) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t s = 0; s < list.size; ++s) {
            if (memcmp(&(list.elements[current]), &element, sizeof(DOUBLE_LIST_DATA_TYPE)) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    }

    DOUBLE_LIST_ASSERT(false && "[ERROR] Element index not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_double_list(const double_list_s list) {
    return list.size == 0;
}

static inline bool is_full_double_list(const double_list_s list) {
    return !((~list.size) && (list.size < PREPROCESSOR_DOUBLE_LIST_SIZE));
}

static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    double_list_s list_copy = { .head = list.head, .size = list.size, };

    if (copy) {
        for (size_t i = 0; i < list.size; ++i) {
            list_copy.elements[i] = copy(list.elements[i]);
            list_copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            list_copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(list_copy.elements, list.elements, list.size * sizeof(DOUBLE_LIST_DATA_TYPE));
        memcpy(list_copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(list_copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return list_copy;
}

static inline void sort_double_list(double_list_s * list, const sort_double_list_fn sort, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    DOUBLE_LIST_ASSERT(sort && "[ERROR] 'sort' function pointer parameter is NULL");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' function pointer parameter is NULL");

    sort(list->elements, list->size, sizeof(DOUBLE_LIST_DATA_TYPE), compare);

    list->head = 0;
    for (size_t i = 0; i < list->size; ++i) {
        list->node[NEXT_IDX][i] = i + 1;
        list->node[PREV_IDX][i] = i - 1;
    } if (list->size) {
        list->node[NEXT_IDX][list->size - 1] = 0;
        list->node[PREV_IDX][0] = list->size - 1;
    }
}

static inline void foreach_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&(list->elements[current]), args)) return;
        current = list->node[NEXT_IDX][current];
    }
}

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#endif

#endif // DOUBLE_LIST_H
