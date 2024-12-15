#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

// list mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_ALLOCATED_SINGLE_LIST  0x0D
#define FINITE_ALLOCATED_SINGLE_LIST    0x0E
#define INFINITE_REALLOC_SINGLE_LIST    0x0F
#define FINITE_PRERPOCESSOR_SINGLE_LIST 0x10

#define INFINITE_SINGLE_LIST INFINITE_ALLOCATED_SINGLE_LIST
#define FINITE_SINGLE_LIST   FINITE_ALLOCATED_SINGLE_LIST

//#define SINGLE_LIST_MODE INFINITE_ALLOCATED_SINGLE_LIST
//#define SINGLE_LIST_MODE FINITE_ALLOCATED_SINGLE_LIST
//#define SINGLE_LIST_MODE INFINITE_REALLOC_SINGLE_LIST
//#define SINGLE_LIST_MODE FINITE_PRERPOCESSOR_SINGLE_LIST
// List mode that can be set to INFINITE_ALLOCATED_DOUBLE_LIST, FINITE_ALLOCATED_DOUBLE_LIST, INFINITE_REALLOC_DOUBLE_LIST or
// FINITE_PRERPOCESSOR_DOUBLE_LIST, or INFINITE_ALLOCATED_DOUBLE_LIST or FINITE_ALLOCATED_DOUBLE_LIST
// Default: INFINITE_ALLOCATED_DOUBLE_LIST
#ifndef SINGLE_LIST_MODE

#define SINGLE_LIST_MODE INFINITE_ALLOCATED_SINGLE_LIST

#endif

#define IS_INFINITE_SINGLE_LIST ((bool)(SINGLE_LIST_MODE & 0x01))

// Check to make sure a valid list mode is selected.
#if (SINGLE_LIST_MODE != INFINITE_ALLOCATED_SINGLE_LIST) && (SINGLE_LIST_MODE != FINITE_ALLOCATED_SINGLE_LIST)    && \
    (SINGLE_LIST_MODE != INFINITE_REALLOC_SINGLE_LIST)   && (SINGLE_LIST_MODE != FINITE_PRERPOCESSOR_SINGLE_LIST)

#error Invalid type of list mode.

#endif

// List data type to specify what datatype to list.
// DEFAULT: void *
#ifndef SINGLE_LIST_DATA_TYPE

#define SINGLE_LIST_DATA_TYPE void*

#endif

#include <stdlib.h>  // imports size_t and malloc
#include <assert.h>  // imports assert for debugging
#include <stdbool.h> // imports bool for conditional queue functions (is_[state]_queue())
#include <string.h>  // imports memcpy

typedef SINGLE_LIST_DATA_TYPE (*copy_single_list_fn)    (const SINGLE_LIST_DATA_TYPE);
typedef void                  (*destroy_single_list_fn) (SINGLE_LIST_DATA_TYPE *);
typedef int                   (*compare_single_list_fn) (const void *, const void *);
typedef void                  (*operate_single_list_fn) (SINGLE_LIST_DATA_TYPE *, void *);
typedef void                  (*sort_single_list_fn)    (void * array, size_t number, size_t size, compare_single_list_fn);

#if SINGLE_LIST_MODE == INFINITE_ALLOCATED_SINGLE_LIST

struct single_list_node {
    SINGLE_LIST_DATA_TYPE element;
    struct single_list_node * next;
};

typedef struct single_list {
    size_t size;
    //struct single_list_node * head;
    struct single_list_node * tail;
} single_list_s;

static inline single_list_s create_single_list(void) {
    return (single_list_s) { 0 };
}

static inline void destroy_single_list(single_list_s * list, const destroy_single_list_fn destroy) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    struct single_list_node * current = list->tail;
    if (destroy) {
        for (size_t s = 0; s < list->size; ++s) {
            destroy(&(current->element));

            struct single_list_node * temp = current;
            current = current->next;
            free(temp);
        }
    } else {
        for (size_t s = 0; s < list->size; ++s) {
            struct single_list_node * temp = current;
            current = current->next;
            free(temp);
        }
    }

    *list = (single_list_s) { 0 };
}

static inline void insert_at_single_list(single_list_s * list, const size_t index, SINGLE_LIST_DATA_TYPE element) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(index <= list->size && "[ERROR] Index bigger than size");
    assert(~list->size && "[ERROR] List size will overflow.");

    struct single_list_node * node = malloc(sizeof(struct single_list_node));
    assert(node && "[ERROR] Memory allocation failed.");
    node->element = element;

    if (list->size - index) {
        struct single_list_node * previous = list->tail;
        for (size_t i = 0; i < index; ++i) {
            previous  = previous->next;
        }

        node->next = previous->next;
        previous->next = node;
    } else if (list->size) {
        node->next = list->tail->next;
        list->tail = node;
    } else {
        list->tail = node->next = node;
    }

    list->size++;
}

static inline SINGLE_LIST_DATA_TYPE remove_single_list(single_list_s * list, SINGLE_LIST_DATA_TYPE element, const compare_single_list_fn compare) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(list->tail && "[ERROR] Can't remove from empty list.");

    struct single_list_node ** current = &(list->tail);
    for (size_t s = 0; s < list->size; ++s) {
        const int comparison = compare ? compare(&((*current)->element), &element) : memcmp(&((*current)->element), &element, sizeof(SINGLE_LIST_DATA_TYPE));
        if (comparison == 0) {
            SINGLE_LIST_DATA_TYPE found = (*current)->element;

            struct single_list_node * temp = *current;
            *current = (--list->size) ? (*current)->next : NULL;
            free(temp);

            return found;
        }
        current = &((*current)->next);
    }

    assert(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline SINGLE_LIST_DATA_TYPE remove_at_single_list(single_list_s * list, const size_t index) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(list->tail && "[ERROR] Can't remove from empty list.");
    assert(index < list->size && "[ERROR] Index greater than size");

    struct single_list_node ** current = &(list->tail->next);
    for (size_t i = 0; i < index; ++i) {
        current = &((*current)->next);
    }

    SINGLE_LIST_DATA_TYPE found = (*current)->element;

    struct single_list_node * temp = *current;
    *current = (--list->size) ? (*current)->next : NULL;
    free(temp);

    return found;
}

static inline void reverse_single_list(single_list_s * list) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    if (list->tail == NULL || list->size == 1) {
        return;
    }

    struct single_list_node * current = list->tail;
    struct single_list_node * current_next = current->next;
    struct single_list_node * current_next_next = current_next->next;

    list->tail = list->tail->next;
    for (size_t i = 0; i < list->size; ++i) {
        current_next->next = current;

        current = current_next;
        current_next = current_next_next;
        current_next_next = current_next_next->next;
    }
}

static inline void shift_next_single_list(single_list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->tail = list->tail->next;
    }
}

static inline single_list_s concatenate_single_list(single_list_s * restrict list_one, single_list_s * restrict list_two) {
    assert(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    assert(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");
    assert(list_one != list_two && "[ERROR] Lists can't be the same.");

    const single_list_s list = { .size = list_one->size + list_two->size,
        .tail = list_one->tail ? list_one->tail : list_two->tail,
    };

    if (list_one->tail && list_two->tail) {
        struct single_list_node ** current = &(list_one->tail->next->next);
        for (size_t i = 0; i < list_one->size - 1; ++i) {
            current = &((*current)->next);
        }
        *current = list_two->tail->next;
        current = &(list_one->tail->next->next);
        for (size_t i = 0; i < list_one->size - 1; ++i) {
            current = &((*current)->next);
        }
        *current = list_one->tail->next;
    }
    *list_one = *list_two = (single_list_s) { 0 };

    return list;
}

static inline bool contains_single_list(const single_list_s list, SINGLE_LIST_DATA_TYPE element, const compare_single_list_fn compare) {
    struct single_list_node const * previous = list.tail;
    if (compare) {
        for (size_t i = 0; i < list.size; ++i) {
            if (compare(&(previous->element), &element) == 0) {
                return true;
            }

            previous = previous->next;
        }
    } else {
        for (size_t i = 0; i < list.size; ++i) {
            if (memcmp(&(previous->element), &element, sizeof(SINGLE_LIST_DATA_TYPE)) == 0) {
                return true;
            }

            previous = previous->next;
        }
    }

    return false;
}

static inline single_list_s split_single_list(single_list_s * list, const size_t index, const size_t size) {
    assert(list && "[ERROR] List pointer is NULL");
    assert(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    assert(index < list->size && "[ERROR] Index is above or equal to list size.");

    single_list_s split = { 0 };
    if (!size) {
        return split;
    }

    struct single_list_node * list_end  = list->tail;
    struct single_list_node * split_end = list->tail;
    for (size_t i = 0; i < index; ++i) {
        split_end = split_end->next;
        list_end = list_end->next;
    }
    for (size_t i = 0; i < size; ++i) {
        split_end = split_end->next;
    }

    split_end->next = list_end->next;
    list_end->next = split_end->next;

    split.tail = split_end;

    list->size -= size;
    if (!list->size) { // if initial list becomes empty
        list->tail = NULL;
    }

    if (index + size >= list->size) { // if list's tail pointer to node becomes part of split list change tail
        list->tail = list_end;
    }

    return split;
}

static inline SINGLE_LIST_DATA_TYPE get_single_list(const single_list_s list, const size_t index) {
    assert(list.size && "[ERROR] Can't get element from empty list.");
    assert(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct single_list_node * previous = list.tail;
    for (size_t i = 0; i < index + 1; ++i) {
        previous = previous->next;
    }

    return previous->element;
}

static inline size_t index_of_single_list(const single_list_s list, SINGLE_LIST_DATA_TYPE element, const compare_single_list_fn compare) {
    assert(list.size && "[ERROR] Can't get index from empty list.");

    struct single_list_node * previous = list.tail;
    for (size_t s = 0; s < list.size; ++s) {
        if (compare(&(previous->element), &element) == 0) {
            return s;
        }

        previous = previous->next;
    }

    assert(false && "[ERROR] Element index not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_single_list(const single_list_s list) {
    return list.size == 0;
}

static inline bool is_full_single_list(const single_list_s list) {
    return !(~list.size);
}

static inline single_list_s copy_single_list(const single_list_s list, const copy_single_list_fn copy) {
    single_list_s list_copy = { .tail = NULL, .size = list.size };

    struct single_list_node const * previous_list = list.tail;
    struct single_list_node ** previous_copy = &(list_copy.tail);
    for (size_t i = 0; i < list.size; ++i) {
        struct single_list_node * temp = malloc(sizeof(struct single_list_node));
        assert(temp && "[ERROR] Memory allocation failed");
        temp->element = copy ? copy(previous_list->element) : previous_list->element;

        (*previous_copy) = temp->next = temp; // (*previous_copy)->next will have reference to prev list node

        previous_list = previous_list->next;
        previous_copy = &((*previous_copy)->next);
    }

    if (*previous_copy != list_copy.tail) {
        (*previous_copy)->next = list_copy.tail;
    }

    return list_copy;
}

static inline void sort_single_list(single_list_s const * list, const sort_single_list_fn sort, const compare_single_list_fn compare) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL");
    assert(sort && "[ERROR] 'sort' parameter pointer is NULL");
    assert(compare && "[ERROR] 'compare' parameter pointer is NULL");

    SINGLE_LIST_DATA_TYPE * elements_array = malloc(sizeof(SINGLE_LIST_DATA_TYPE) * list->size);
    assert((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct single_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next; // gets to first element, since we start from tail
        elements_array[i] = previous->element;
    }

    sort(elements_array, list->size, sizeof(SINGLE_LIST_DATA_TYPE), compare);

    previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next; // gets to first element, since we start from tail
        previous->element = elements_array[i];
    }
    free(elements_array);
}

static inline void foreach_single_list(single_list_s * list, const operate_single_list_fn operate, void * args) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL.");
    assert(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct single_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next; // go to next early to start from the beginning/head
        operate(&(previous->element), args);
    }
}

#endif

#endif // SINGLE_LIST_H
