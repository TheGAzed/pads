#ifndef LIST_H
#define LIST_H

#ifdef LIST_HELP

#endif

// list mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_ALLOCATED_DOUBLE_LIST  0x040
#define FINITE_ALLOCATED_DOUBLE_LIST    0x080
#define INFINITE_REALLOC_DOUBLE_LIST    0x0C0
#define FINITE_PRERPOCESSOR_DOUBLE_LIST 0x100

#define INFINITE_ALLOCATED_SINGLE_LIST  0x140
#define FINITE_ALLOCATED_SINGLE_LIST    0x180
#define INFINITE_REALLOC_SINGLE_LIST    0x1C0
#define FINITE_PRERPOCESSOR_SINGLE_LIST 0x200

#define INFINITE_LIST INFINITE_ALLOCATED_DOUBLE_LIST
#define FINITE_LIST   FINITE_ALLOCATED_DOUBLE_LIST

//#define LIST_MODE INFINITE_ALLOCATED_SINGLE_LIST
// List mode that can be set to INFINITE_ALLOCATED_DOUBLE_LIST, FINITE_ALLOCATED_DOUBLE_LIST, INFINITE_REALLOC_DOUBLE_LIST or
// FINITE_PRERPOCESSOR_DOUBLE_LIST, or INFINITE_ALLOCATED_DOUBLE_LIST or FINITE_ALLOCATED_DOUBLE_LIST
// Default: INFINITE_ALLOCATED_DOUBLE_LIST
#ifndef LIST_MODE

#define LIST_MODE INFINITE_ALLOCATED_DOUBLE_LIST

#endif

#define IS_INFINITE_LIST ((bool)(LIST_MODE & 0x040))

// Check to make sure a valid list mode is selected.
#if (LIST_MODE != INFINITE_ALLOCATED_DOUBLE_LIST) && (LIST_MODE != FINITE_ALLOCATED_DOUBLE_LIST)    && \
    (LIST_MODE != INFINITE_REALLOC_DOUBLE_LIST)   && (LIST_MODE != FINITE_PRERPOCESSOR_DOUBLE_LIST) && \
    (LIST_MODE != INFINITE_ALLOCATED_SINGLE_LIST) && (LIST_MODE != FINITE_ALLOCATED_SINGLE_LIST)    && \
    (LIST_MODE != INFINITE_REALLOC_SINGLE_LIST)   && (LIST_MODE != FINITE_PRERPOCESSOR_SINGLE_LIST)

#error Invalid type of list mode.

#endif

// List data type to specify what datatype to list.
// DEFAULT: void *
#ifndef LIST_DATA_TYPE

#define LIST_DATA_TYPE void*

#endif

#include <stdlib.h>  // imports size_t and malloc
#include <assert.h>  // imports assert for debugging
#include <stdbool.h> // imports bool for conditional queue functions (is_[state]_queue())
#include <string.h>  // imports memcpy

#if   LIST_MODE == INFINITE_ALLOCATED_DOUBLE_LIST

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

static inline void destroy_list(list_s * list, void (*destroy_element)(LIST_DATA_TYPE *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    struct list_node * current = list->head;
    if (destroy_element) {
        for (size_t s = 0; s < list->size; ++s) {
            destroy_element(&(current->element));

            struct list_node * temp = current;
            current = current->next;
            free(temp);
        }
    } else {
        for (size_t s = 0; s < list->size; ++s) {
            struct list_node * temp = current;
            current = current->next;
            free(temp);
        }
    }

    *list = (list_s) { 0 };
}

static inline void insert_at_list(list_s * list, const size_t index, LIST_DATA_TYPE element) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(index <= list->size && "[ERROR] Index bigger than size");
    assert(~list->size && "[ERROR] List size will overflow.");

    struct list_node * temp = malloc(sizeof(struct list_node));
    assert(temp && "[ERROR] Memory allocation failed.");
    temp->element = element;

    struct list_node ** current = &(list->head);
    if (index < (list->size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = &((*current)->next);
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = &((*current)->prev);
        }
    }

    if (list->head) {
        temp->next = *current;
        temp->prev = (*current)->prev;
    } else {
        temp->next = temp->prev = temp;
    }

    *current = temp;

    list->size++;
}

static inline LIST_DATA_TYPE remove_list(list_s * list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(list->head && "[ERROR] Can't remove from empty list.");

    struct list_node ** current = &(list->head);
    if (compare_element) {
        for (size_t s = 0; s < list->size; ++s) {
            if (compare_element(&((*current)->element), &element) == 0) {
                LIST_DATA_TYPE found = (*current)->element;

                struct list_node * temp = *current;
                (*current)->next->prev = (*current)->prev;
                *current = (--list->size) ? (*current)->next : NULL;
                free(temp);

                return found;
            }
            current = &((*current)->next);
        }
    } else {
        for (size_t s = 0; s < list->size; ++s) {
            if (memcmp(&((*current)->element), &element, sizeof(LIST_DATA_TYPE)) == 0) {
                LIST_DATA_TYPE found = (*current)->element;

                struct list_node * temp = *current;
                (*current)->next->prev = (*current)->prev;
                *current = (--list->size) ? (*current)->next : NULL;
                free(temp);

                return found;
            }
            current = &((*current)->next);
        }
    }

    assert(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(list->head && "[ERROR] Can't remove from empty list.");
    assert(index < list->size && "[ERROR] Index greater than size");

    struct list_node ** current = &(list->head);
    if (index < (list->size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = &((*current)->next);
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = &((*current)->prev);
        }
    }

    LIST_DATA_TYPE found = (*current)->element;

    struct list_node * temp = *current;
    (*current)->next->prev = (*current)->prev;
    *current = (--list->size) ? (*current)->next : NULL;
    free(temp);

    return found;
}

static inline void reverse_list(list_s * list) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    struct list_node * current = list->head = list->head ? list->head->prev : list->head;
    for (size_t s = 0; s < list->size; ++s) {
        struct list_node * temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        current = current->next;
    }
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->head && (s < shift); ++s) {
        list->head = list->head->next;
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->head && (s < shift); ++s) {
        list->head = list->head->prev;
    }
}

static inline list_s concatenate_list(list_s * restrict list_one, list_s * restrict list_two) {
    assert(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    assert(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");

    const list_s list = {
        .size = list_one->size + list_two->size,
        .head = list_one->head ? list_one->head : list_two->head,
    };

    if (list_one->head && list_two->head) {
        list_one->head->prev->next = list_two->head;
        list_two->head->prev = list_one->head->prev;

        list_two->head->prev->next = list_one->head;
        list_one->head->prev = list_two->head->prev;
    }
    *list_one = *list_two = (list_s) { 0 };

    return list;
}

static inline bool contains_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    struct list_node const * current = list.head;
    if (compare_element) {
        for (size_t i = 0; i < list.size; ++i) {
            if (compare_element(&(current->element), &element) == 0) {
                return true;
            }

            current = current->next;
        }
    } else {
        for (size_t i = 0; i < list.size; ++i) {
            if (memcmp(&(current->element), &element, sizeof(LIST_DATA_TYPE)) == 0) {
                return true;
            }

            current = current->next;
        }
    }

    return false;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size) {
    assert(list && "[ERROR] List pointer is NULL");
    assert(size && "[ERROR] Can't split size zero.");
    assert(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    struct list_node * index_node = list->head;
    if (index < (list->size << 2)) {
        for (size_t i = 0; i < index; ++i) { index_node = index_node->next; }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) { index_node = index_node->prev; }
    }

    struct list_node * size_node = index_node;
    if (size < (list->size << 2)) {
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

    return (list_s) { .head = index_node, .size = size };
}

static inline LIST_DATA_TYPE get_list(const list_s list, const size_t index) {
    assert(list.head && "[ERROR] Can't get element from empty list.");
    assert(list.size && "[ERROR] Can't get element from empty list.");
    assert(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

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

static inline size_t index_of_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list.size && "[ERROR] Can't get index from empty list.");
    assert(list.head && "[ERROR] Can't get index from empty list.");

    struct list_node const * current = list.head;
    if (compare_element) {
        for (size_t s = 0; s < list.size; ++s) {
            if (compare_element(&(current->element), &element) == 0) {
                return s;
            }

            current = current->next;
        }
    } else {
        for (size_t s = 0; s < list.size; ++s) {
            if (memcmp(&(current->element), &element, sizeof(LIST_DATA_TYPE)) == 0) {
                return s;
            }

            current = current->next;
        }
    }

    assert(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_list(const list_s list) {
    return list.size == 0;
}

static inline bool is_full_list(const list_s list) {
    return !(~list.size);
}

static inline list_s copy_list(const list_s list, LIST_DATA_TYPE (*copy_element)(LIST_DATA_TYPE)) {
    list_s copy = { .head = NULL, .size = list.size };

    struct list_node const * current_list = list.head;
    struct list_node ** current_copy = &(copy.head);
    if (copy_element) {
        for (size_t i = 0; i < list.size; ++i) {
            struct list_node * temp = malloc(sizeof(struct list_node));
            assert(temp && "[ERROR] Memory allocation failed");
            temp->element = copy_element(current_list->element);

            temp->prev = (*current_copy); // prev reference is stored in *current_copy
            (*current_copy) = temp->next = temp; // (*current_copy)->next will have reference to prev list node

            current_list = current_list->next;
            current_copy = &((*current_copy)->next);
        }
    } else {
        for (size_t i = 0; i < list.size; ++i) {
            struct list_node * temp = malloc(sizeof(struct list_node));
            assert(temp && "[ERROR] Memory allocation failed");
            temp->element = current_list->element;

            temp->prev = (*current_copy); // prev reference is stored in *current_copy
            (*current_copy) = temp->next = temp; // (*current_copy)->next will have reference to prev list node

            current_list = current_list->next;
            current_copy = &((*current_copy)->next);
        }
    }
    if (current_copy != &(copy.head)) {
        copy.head->prev = (*current_copy); // copy.head won't have prev reference to last node
        (*current_copy)->next = copy.head; // *current_copy or last node won't have reference to head
    }

    return copy;
}

static inline void sort_list(list_s const * list, void (*sort_elements)(LIST_DATA_TYPE *, size_t)) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL");

    LIST_DATA_TYPE * elements_array = malloc(sizeof(LIST_DATA_TYPE) * list->size);
    assert((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = current->element;
        current = current->next;
    }

    if (sort_elements) {
        sort_elements(elements_array, list->size);
    } else {
        for (size_t s = 0; s < list->size - 1; ++s) {
            for (size_t i = 0; i < list->size - s - 1; ++i) {
                if (memcmp(&(elements_array[i]), &(elements_array[i + 1]), sizeof(LIST_DATA_TYPE)) > 0) {
                    LIST_DATA_TYPE temp = elements_array[i];
                    elements_array[i] = elements_array[i + 1];
                    elements_array[i + 1] = temp;
                }
            }
        }
    }

    current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current->element = elements_array[i];
        current = current->next;
    }
    free(elements_array);
}

#elif LIST_MODE == FINITE_ALLOCATED_DOUBLE_LIST

#define NODE_COUNT 2
#define NEXT_IDX   0
#define PREV_IDX   1
typedef struct list {
    size_t size, max, head;

    LIST_DATA_TYPE * elements;
    size_t * node[NODE_COUNT];
} list_s;

static inline list_s create_list(const size_t max) {
    assert(max && "[ERROR] Maximum size can't be zero.");

    const list_s list = {
        .elements = malloc(sizeof(LIST_DATA_TYPE) * max),
        .node[NEXT_IDX] = malloc(sizeof(size_t) * max), .node[PREV_IDX] = malloc(sizeof(size_t) * max),

        .head = 0, .max = max, .size = 0,
    };

    assert(list.elements && "[ERROR] Memory allocation failed.");
    assert(list.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    assert(list.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    return list;
}

static inline void destroy_list(list_s * list, void (*destroy_element)(LIST_DATA_TYPE *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy_element && (s < list->size); ++s) {
        destroy_element(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    free(list->elements); free(list->node[NEXT_IDX]); free(list->node[PREV_IDX]);

    *list = (list_s) { 0 };
}

static inline void insert_at_list(list_s * list, const size_t index, LIST_DATA_TYPE element) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size < list->max && "[ERROR] List reached maximum size.");
    assert(index <= list->size && "[ERROR] Index bigger than size.");
    assert(~list->size && "[ERROR] List size will overflow.");

    size_t current = list->head;

    if (index < (list->size << 2)) {
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

static inline LIST_DATA_TYPE remove_list(list_s * list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");

    assert(list->elements && "[ERROR] No memory available.");
    assert(list->node[NEXT_IDX] && "[ERROR] No memory available.");
    assert(list->node[PREV_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        if (compare_element) {
            if (compare_element(&(list->elements[current]), &element) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        } else {
            if (memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE)) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        list->node[NEXT_IDX][list->node[PREV_IDX][list->size - 1]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size - 1]] = current;
        list->elements[current] = list->elements[--(list->size)];

        return found;
    }

    assert(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(index < list->size && "[ERROR] Index greater than size");

    size_t current = list->head;
    if (index < (list->size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }
    LIST_DATA_TYPE found = list->elements[current];

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    list->size--;
    list->elements[current] = list->elements[list->size];

    list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;

    return found;
}

static inline void reverse_list(list_s * list) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[NEXT_IDX][current];
    }
    if (list->size) list->head = list->node[NEXT_IDX][list->head];
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline list_s concatenate_list(list_s * restrict list_one, list_s * restrict list_two, const size_t max) {
    assert(list_one->size + list_two->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    assert(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    assert(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");

    const list_s list = {
        .size = list_one->size + list_two->size, .max = max, .head = list_one->size ? list_one->head : list_two->head,

        .elements = malloc(sizeof(LIST_DATA_TYPE) * max),
        .node[NEXT_IDX] = malloc(sizeof(LIST_DATA_TYPE) * max), .node[PREV_IDX] = malloc(sizeof(LIST_DATA_TYPE) * max),
    };

    memcpy(list.elements, list_one->elements, sizeof(LIST_DATA_TYPE) * list_one->size);
    memcpy(&(list.elements[list_one->size]), list_two->elements, sizeof(LIST_DATA_TYPE) * list_two->size);
    for (size_t i = 0; i < NODE_COUNT; ++i) {
        memcpy(list.node[i], list_one->node[i], sizeof(size_t) * list_one->size);
        memcpy(&(list.node[i][list_one->size]), list_two->node[i], sizeof(size_t) * list_two->size);
    }

    if (list_one->size && list_two->size) {
        list.node[NEXT_IDX][list_one->node[PREV_IDX][list_one->head]] = list_two->head;
        list.node[PREV_IDX][list_two->head] = list_one->node[PREV_IDX][list_one->head];

        list.node[NEXT_IDX][list_two->node[PREV_IDX][list_two->head]] = list_one->head;
        list.node[PREV_IDX][list_one->head] = list_two->node[PREV_IDX][list_two->head];
    }
    list_one->size = list_two->size = 0;

    return list;
}

static inline bool contains_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    size_t current = list.head;
    if (compare_element) {
        for (size_t i = 0; i < list.size; ++i) {
            if (compare_element(&(list.elements[current]), &element) == 0) {
                return true;
            }

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list.size; ++i) {
            if (memcmp(&(list.elements[current]), &element, sizeof(LIST_DATA_TYPE)) == 0) {
                return true;
            }

            current = list.node[NEXT_IDX][current];
        }
    }

    return false;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size, const size_t max) {
    assert(list && "[ERROR] List pointer is NULL");
    assert(max && "[ERROR] max size can't be zero.");
    assert(index < list->size && "[ERROR] Can only split at index less than list size.");
    assert(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    assert(size <= max && "[ERROR] List size exceed max size of new split list.");

    if (!size) {
        return (list_s) { 0 };
    }

    size_t current = list->head;
    if (index < (list->size << 2)) {
        for (size_t i = 0; i < index; ++i) {
            current = list->node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list->size - index; ++i) {
            current = list->node[PREV_IDX][current];
        }
    }

    list_s const split_list = {
        .elements = malloc(sizeof(LIST_DATA_TYPE) * max), .head = 0, .size = size,
        .node[NEXT_IDX] = malloc(sizeof(size_t) * max), .node[PREV_IDX] = malloc(sizeof(size_t) * max),
    };

    assert(split_list.elements && "[ERROR] Memory allocation failed");
    assert(split_list.node[NEXT_IDX] && "[ERROR] Memory allocation failed");
    assert(split_list.node[PREV_IDX] && "[ERROR] Memory allocation failed");

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
    assert(list.size && "[ERROR] Can't get element from empty list.");
    assert(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

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

static inline size_t index_of_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list.size && "[ERROR] Can't get index from empty list.");

    size_t current = list.head;
    if (compare_element) {
        for (size_t s = 0; s < list.size; ++s) {
            if (compare_element(&(list.elements[current]), &element) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t s = 0; s < list.size; ++s) {
            if (memcmp(&(list.elements[current]), &element, sizeof(LIST_DATA_TYPE)) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    }

    assert(false && "[ERROR] Element index not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_list(const list_s list) {
    return list.size == 0;
}

static inline bool is_full_list(const list_s list) {
    return !(~list.size);
}

static inline list_s copy_list(const list_s list, LIST_DATA_TYPE (*copy_element)(LIST_DATA_TYPE)) {
    const list_s copy = {
        .elements = malloc(sizeof(LIST_DATA_TYPE) * list.max),
        .node[NEXT_IDX] = malloc(sizeof(size_t) * list.max), .node[PREV_IDX] = malloc(sizeof(size_t) * list.max),
        .head = list.head, .max = list.max, .size = list.size,
    };

    assert(copy.elements && "[ERROR] Memory allocation failed.");
    assert(copy.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    assert(copy.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    if (copy_element) {
        for (size_t i = 0; i < list.size; ++i) {
            copy.elements[i] = copy_element(list.elements[i]);
            copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(copy.elements, list.elements, list.size * sizeof(LIST_DATA_TYPE));
        memcpy(copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return copy;
}

static inline void sort_list(list_s * list, void (*sort_elements)(LIST_DATA_TYPE *, size_t)) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL");

    if (sort_elements) {
        sort_elements(list->elements, list->size);
    } else {
        for (size_t s = 0; s < list->size - 1; ++s) {
            for (size_t i = 0; i < list->size - s - 1; ++i) {
                if (memcmp(&(list->elements[i]), &(list->elements[i + 1]), sizeof(LIST_DATA_TYPE)) > 0) {
                    LIST_DATA_TYPE temp = list->elements[i];
                    list->elements[i] = list->elements[i + 1];
                    list->elements[i + 1] = temp;
                }
            }
        }
    }

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

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#elif LIST_MODE == INFINITE_REALLOC_DOUBLE_LIST

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

static inline void destroy_list(list_s * list, void (*destroy_element)(LIST_DATA_TYPE *)) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy_element && (s < list->size); ++s) {
        destroy_element(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    free(list->elements);
    for (size_t i = 0; i < NODE_COUNT; ++i) {
        free(list->node[i]);
    }

    *list = (list_s) { 0 };
}

static inline void insert_at_list(list_s * list, const size_t index, LIST_DATA_TYPE element) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL.");
    assert(index <= list->size && "[ERROR] Index bigger than size.");
    assert(~list->size && "[ERROR] List size will overflow.");

    if (!(list->size % REALLOC_LIST_CHUNK)) {
        list->elements = realloc(list->elements, (list->size + REALLOC_LIST_CHUNK) * sizeof(LIST_DATA_TYPE));
        list->node[NEXT_IDX] = realloc(list->elements, (list->size + REALLOC_LIST_CHUNK) * sizeof(size_t));
        list->node[PREV_IDX] = realloc(list->elements, (list->size + REALLOC_LIST_CHUNK) * sizeof(size_t));
    }

    size_t current = list->head, smaller_size = list->size - index, node_index = PREV_IDX;
    if (index < (list->size << 2)) {
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

static inline LIST_DATA_TYPE remove_list(list_s * list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");

    assert(list->elements && "[ERROR] No memory available.");
    assert(list->node[PREV_IDX] && "[ERROR] No memory available.");
    assert(list->node[NEXT_IDX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        if (compare_element) {
            if (compare_element(&(list->elements[current]), &element) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        } else {
            if (memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE)) != 0) {
                current = list->node[NEXT_IDX][current];
                continue;
            }
        }

        list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
        list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

        LIST_DATA_TYPE found = list->elements[current];

        list->node[PREV_IDX][list->node[NEXT_IDX][list->size - 1]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size - 1]] = current;
        list->elements[current] = list->elements[--(list->size)];

        if (!(list->size % REALLOC_LIST_CHUNK)) {
            list->elements = list->size ? realloc(list->elements, list->size * sizeof(LIST_DATA_TYPE)) : NULL;
            list->node[PREV_IDX] = list->size ? realloc(list->node[PREV_IDX], list->size * sizeof(size_t)) : NULL;
            list->node[NEXT_IDX] = list->size ? realloc(list->node[NEXT_IDX], list->size * sizeof(size_t)) : NULL;
        }

        return found;
    }

    assert(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(index < list->size && "[ERROR] Index parameter greater than list size.");

    size_t current = list->head, smaller_size = list->size - index, node_index = PREV_IDX;
    if (index < (list->size << 2)) {
        smaller_size = index;
        node_index = NEXT_IDX;
    }
    for (size_t i = 0; i < smaller_size; ++i) {
        current = list->node[node_index][current];
    }

    list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
    list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

    LIST_DATA_TYPE found = list->elements[current];

    list->node[PREV_IDX][list->node[NEXT_IDX][list->size - 1]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size - 1]] = current;
    list->elements[current] = list->elements[--(list->size)];

    if (!(list->size % REALLOC_LIST_CHUNK)) {
        if (list->size) {
            list->elements = realloc(list->elements, list->size * sizeof(LIST_DATA_TYPE));
            list->node[PREV_IDX] = realloc(list->node[PREV_IDX], list->size * sizeof(size_t));
            list->node[NEXT_IDX] = realloc(list->node[NEXT_IDX], list->size * sizeof(size_t));
        } else {
            list->elements = (LIST_DATA_TYPE *) (list->node[PREV_IDX] = list->node[NEXT_IDX] = NULL);
        }
    }

    return found;
}

static inline void reverse_list(list_s * list) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL.");

    size_t current = list->head = list->size ? list->node[PREV_IDX][list->head] : list->head;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[NEXT_IDX][current];
    }
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline list_s concatenate_list(list_s * restrict list_one, list_s * restrict list_two) {
    assert(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    assert(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");

    const size_t new_size = (list_one->size + list_two->size);
    const size_t alloc_size = new_size - (new_size % REALLOC_LIST_CHUNK) + REALLOC_LIST_CHUNK;

    list_s list = { .size = new_size, .head = list_one->size ? list_one->head : list_two->head, };
    list.elements = new_size ? realloc(list.elements, alloc_size * sizeof(LIST_DATA_TYPE)) : NULL;
    for (size_t i = 0; i < NODE_COUNT; ++i) {
        list.node[i] = new_size ? realloc(list.node[i], alloc_size * sizeof(size_t)) : NULL;
    }

    memcpy(list.elements, list_one->elements, sizeof(LIST_DATA_TYPE) * list_one->size);
    memcpy(&(list.elements[list_one->size]), list_two->elements, sizeof(LIST_DATA_TYPE) * list_two->size);
    for (size_t i = 0; i < NODE_COUNT; ++i) {
        memcpy(list.node[i], list_one->node[i], sizeof(size_t) * list_one->size);
        memcpy(&(list.node[i][list_one->size]), list_two->node[i], sizeof(size_t) * list_two->size);
    }

    if (list_one->size && list_two->size) {
        list.node[NEXT_IDX][list_one->node[PREV_IDX][list_one->head]] = list_two->head;
        list.node[PREV_IDX][list_two->head] = list_one->node[PREV_IDX][list_one->head];

        list.node[NEXT_IDX][list_two->node[PREV_IDX][list_two->head]] = list_one->head;
        list.node[PREV_IDX][list_one->head] = list_two->node[PREV_IDX][list_two->head];
    }
    list_one->size = list_two->size = 0;

    return list;
}

static inline bool contains_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    size_t current = list.head;
    if (compare_element) {
        for (size_t i = 0; i < list.size; ++i) {
            if (compare_element(&(list.elements[current]), &element) == 0) {
                return true;
            }

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list.size; ++i) {
            if (memcmp(&(list.elements[current]), &element, sizeof(LIST_DATA_TYPE)) == 0) {
                return true;
            }

            current = list.node[NEXT_IDX][current];
        }
    }

    return false;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size) {
    assert(list && "[ERROR] List pointer is NULL");
    assert(index < list->size && "[ERROR] Can only split at index less than list size.");
    assert(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) { return (list_s) { 0 }; }

    const size_t split_chunk = size - (size % REALLOC_LIST_CHUNK) + REALLOC_LIST_CHUNK;
    list_s const split_list = {
        .elements = malloc(sizeof(LIST_DATA_TYPE) * split_chunk), .head = 0, .size = size,
        .node[NEXT_IDX] = malloc(sizeof(size_t) * split_chunk), .node[PREV_IDX] = malloc(sizeof(size_t) * split_chunk),
    };

    assert(split_list.elements && "[ERROR] Memory allocation failed");
    assert(split_list.node[NEXT_IDX] && "[ERROR] Memory allocation failed");
    assert(split_list.node[PREV_IDX] && "[ERROR] Memory allocation failed");

    size_t current = list->head; // pointer to change head while splitting
    if (index < (list->size << 2)) {
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
                list->elements = realloc(list->elements, list->size * sizeof(LIST_DATA_TYPE));
                list->node[PREV_IDX] = realloc(list->node[PREV_IDX], list->size * sizeof(size_t));
                list->node[NEXT_IDX] = realloc(list->node[NEXT_IDX], list->size * sizeof(size_t));
            }

            current = list->node[NEXT_IDX][current];
        } else {
            free(list->elements);
            free(list->node[PREV_IDX]);
            free(list->node[NEXT_IDX]);
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
    assert(list.size && "[ERROR] Can't get element from empty list.");
    assert(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

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

static inline size_t index_of_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list.size && "[ERROR] Can't get index from empty list.");

    size_t current = list.head;
    if (compare_element) {
        for (size_t s = 0; s < list.size; ++s) {
            if (compare_element(&(list.elements[current]), &element) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t s = 0; s < list.size; ++s) {
            if (memcmp(&(list.elements[current]), &element, sizeof(LIST_DATA_TYPE)) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    }

    assert(false && "[ERROR] Element index not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_list(const list_s list) {
    return list.size == 0;
}

static inline bool is_full_list(const list_s list) {
    return !((~list.size) && (list.size < REALLOC_LIST_CHUNK));
}

static inline list_s copy_list(const list_s list, LIST_DATA_TYPE (*copy_element)(LIST_DATA_TYPE)) {
    if (!list.size) return (list_s) { 0 };

    const size_t copy_chunk = list.size - (list.size % REALLOC_LIST_CHUNK) + REALLOC_LIST_CHUNK;
    const list_s copy = {
        .elements = malloc(sizeof(LIST_DATA_TYPE) * copy_chunk),
        .node[NEXT_IDX] = malloc(sizeof(size_t) * copy_chunk), .node[PREV_IDX] = malloc(sizeof(size_t) * copy_chunk),
        .head = list.head, .size = list.size,
    };

    assert(copy.elements && "[ERROR] Memory allocation failed.");
    assert(copy.node[NEXT_IDX] && "[ERROR] Memory allocation failed.");
    assert(copy.node[PREV_IDX] && "[ERROR] Memory allocation failed.");

    if (copy_element) {
        for (size_t i = 0; i < list.size; ++i) {
            copy.elements[i] = copy_element(list.elements[i]);
            copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(copy.elements, list.elements, list.size * sizeof(LIST_DATA_TYPE));
        memcpy(copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return copy;
}

static inline void sort_list(list_s * list, void (*sort_elements)(LIST_DATA_TYPE *, size_t)) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL");

    if (sort_elements) {
        sort_elements(list->elements, list->size);
    } else {
        for (size_t s = 0; s < list->size - 1; ++s) {
            for (size_t i = 0; i < list->size - s - 1; ++i) {
                if (memcmp(&(list->elements[i]), &(list->elements[i + 1]), sizeof(LIST_DATA_TYPE)) > 0) {
                    LIST_DATA_TYPE temp = list->elements[i];
                    list->elements[i] = list->elements[i + 1];
                    list->elements[i + 1] = temp;
                }
            }
        }
    }

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

#undef NEXT_IDX
#undef PREV_IDX
#undef NODE_COUNT

#elif LIST_MODE == FINITE_PRERPOCESSOR_DOUBLE_LIST

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

static inline void destroy_list(list_s * list, void (*destroy_element)(LIST_DATA_TYPE *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; destroy_element && (s < list->size); ++s) {
        destroy_element(&(list->elements[current]));
        current = list->node[NEXT_IDX][current];
    }

    list->size = list->head = 0;
}

static inline void insert_at_list(list_s * list, const size_t index, LIST_DATA_TYPE element) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size < PREPROCESSOR_LIST_SIZE && "[ERROR] List reached maximum size.");
    assert(index <= list->size && "[ERROR] Index bigger than size.");
    assert(~list->size && "[ERROR] List size will overflow.");

    size_t current = list->head;

    if (index < (list->size << 2)) {
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

static inline LIST_DATA_TYPE remove_list(list_s * list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");

    size_t current = list->head;
    if (compare_element) {
        for (size_t s = 0; s < list->size; ++s) {
            if (compare_element(&(list->elements[current]), &element) != 0) {
                current = list->node[NEXT_IDX][current]; continue;
            }

            list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
            list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

            LIST_DATA_TYPE found = list->elements[current];

            list->size--;
            list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
            list->elements[current] = list->elements[list->size];

            return found;
        }
    } else {
        for (size_t s = 0; s < list->size; ++s) {
            if (memcmp(&(list->elements[current]), &element, sizeof(LIST_DATA_TYPE)) != 0) {
                current = list->node[NEXT_IDX][current]; continue;
            }

            list->node[NEXT_IDX][list->node[PREV_IDX][current]] = list->node[NEXT_IDX][current];
            list->node[PREV_IDX][list->node[NEXT_IDX][current]] = list->node[PREV_IDX][current];

            LIST_DATA_TYPE found = list->elements[current];

            list->size--;
            list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = current;
            list->elements[current] = list->elements[list->size];

            return found;
        }
    }

    assert(false && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(index < list->size && "[ERROR] Index greater than size");

    size_t current = list->head;
    if (index < (list->size << 2)) {
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

    LIST_DATA_TYPE found = list->elements[current];

    list->size--;
    list->node[PREV_IDX][list->node[NEXT_IDX][list->size]] = list->node[NEXT_IDX][list->node[PREV_IDX][list->size]] = current;
    list->elements[current] = list->elements[list->size];

    return found;
}

static inline void reverse_list(list_s * list) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t temp = list->node[NEXT_IDX][current];
        list->node[NEXT_IDX][current] = list->node[PREV_IDX][current];
        list->node[PREV_IDX][current] = temp;

        current = list->node[NEXT_IDX][current];
    }
    if (list->size) list->head = list->node[NEXT_IDX][list->head];
}

static inline void shift_next_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[NEXT_IDX][list->head];
    }
}

static inline void shift_prev_list(list_s * list, const size_t shift) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->head = list->node[PREV_IDX][list->head];
    }
}

static inline list_s concatenate_list(list_s * restrict list_one, list_s * restrict list_two) {
    assert(list_one->size + list_two->size <= PREPROCESSOR_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    assert(list_one && "[ERROR] 'list_one' parameter pointer is NULL.");
    assert(list_two && "[ERROR] 'list_two' parameter pointer is NULL.");

    list_s list = { .size = list_one->size + list_two->size, .head = list_one->size ? list_one->head : list_two->head, };

    memcpy(list.elements, list_one->elements, sizeof(LIST_DATA_TYPE) * list_one->size);
    memcpy(&(list.elements[list_one->size]), list_two->elements, sizeof(LIST_DATA_TYPE) * list_two->size);
    for (size_t i = 0; i < NODE_COUNT; ++i) {
        memcpy(list.node[i], list_one->node[i], sizeof(size_t) * list_one->size);
        memcpy(&(list.node[i][list_one->size]), list_two->node[i], sizeof(size_t) * list_two->size);
    }

    if (list_one->size && list_two->size) {
        list.node[NEXT_IDX][list_one->node[PREV_IDX][list_one->head]] = list_two->head;
        list.node[PREV_IDX][list_two->head] = list_one->node[PREV_IDX][list_one->head];

        list.node[NEXT_IDX][list_two->node[PREV_IDX][list_two->head]] = list_one->head;
        list.node[PREV_IDX][list_one->head] = list_two->node[PREV_IDX][list_two->head];
    }
    list_one->size = list_two->size = 0;

    return list;
}

static inline bool contains_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    size_t current = list.head;
    if (compare_element) {
        for (size_t i = 0; i < list.size; ++i) {
            if (compare_element(&(list.elements[current]), &element) == 0) return true;

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t i = 0; i < list.size; ++i) {
            if (memcmp(&(list.elements[current]), &element, sizeof(LIST_DATA_TYPE)) == 0) return true;

            current = list.node[NEXT_IDX][current];
        }
    }

    return false;
}

static inline list_s split_list(list_s * list, const size_t index, const size_t size) {
    assert(list && "[ERROR] List pointer is NULL");
    assert(index < list->size && "[ERROR] Can only split at index less than list size.");
    assert(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    if (!size) {
        return (list_s) { .head = 0, .size = 0 };
    }

    size_t current = list->head;
    if (index < (list->size << 2)) {
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
    assert(list.size && "[ERROR] Can't get element from empty list.");
    assert(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

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

static inline size_t index_of_list(const list_s list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list.size && "[ERROR] Can't get index from empty list.");

    size_t current = list.head;
    if (compare_element) {
        for (size_t s = 0; s < list.size; ++s) {
            if (compare_element(&(list.elements[current]), &element) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    } else {
        for (size_t s = 0; s < list.size; ++s) {
            if (memcmp(&(list.elements[current]), &element, sizeof(LIST_DATA_TYPE)) == 0) return s;

            current = list.node[NEXT_IDX][current];
        }
    }

    assert(false && "[ERROR] Element index not found in list.");
    exit(EXIT_FAILURE);
}

static inline bool is_empty_list(const list_s list) {
    return list.size == 0;
}

static inline bool is_full_list(const list_s list) {
    return !((~list.size) && (list.size < PREPROCESSOR_LIST_SIZE));
}

static inline list_s copy_list(const list_s list, LIST_DATA_TYPE (*copy_element)(LIST_DATA_TYPE)) {
    list_s copy = { .head = list.head, .size = list.size, };

    if (copy_element) {
        for (size_t i = 0; i < list.size; ++i) {
            copy.elements[i] = copy_element(list.elements[i]);
            copy.node[NEXT_IDX][i] = list.node[NEXT_IDX][i];
            copy.node[PREV_IDX][i] = list.node[PREV_IDX][i];
        }
    } else {
        memcpy(copy.elements, list.elements, list.size * sizeof(LIST_DATA_TYPE));
        memcpy(copy.node[NEXT_IDX], list.node[NEXT_IDX], list.size * sizeof(size_t));
        memcpy(copy.node[PREV_IDX], list.node[PREV_IDX], list.size * sizeof(size_t));
    }

    return copy;
}

static inline void sort_list(list_s * list, void (*sort_elements)(LIST_DATA_TYPE *, size_t)) {
    assert(list && "[ERROR] 'list' parameter pointer is NULL");

    if (sort_elements) {
        sort_elements(list->elements, list->size);
    } else {
        for (size_t s = 0; s < list->size - 1; ++s) { // bubble sort bad !!!!
            for (size_t i = 0; i < list->size - s - 1; ++i) {
                if (memcmp(&(list->elements[i]), &(list->elements[i + 1]), sizeof(LIST_DATA_TYPE)) > 0) {
                    LIST_DATA_TYPE temp = list->elements[i];
                    list->elements[i] = list->elements[i + 1];
                    list->elements[i + 1] = temp;
                }
            }
        }
    }

    list->head = 0;
    for (size_t i = 0; i < list->size; ++i) {
        list->node[NEXT_IDX][i] = i + 1;
        list->node[PREV_IDX][i] = i - 1;
    } if (list->size) {
        list->node[NEXT_IDX][list->size - 1] = 0;
        list->node[PREV_IDX][0] = list->size - 1;
    }
}

#elif LIST_MODE == INFINITE_ALLOCATED_SINGLE_LIST

struct list_node {
    LIST_DATA_TYPE element;
    struct list_node * next;
};

typedef struct list {
    size_t size;
    struct list_node * head;
} list_s;

static inline list_s create_list(void) {
    return (list_s) { 0 };
}

static inline void destroy_list(list_s * list, void (*destroy_element)(LIST_DATA_TYPE *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    struct list_node * current = list->head;
    if (destroy_element) {
        for (size_t s = 0; s < list->size; ++s) {
            destroy_element(&(current->element));

            struct list_node * temp = current;
            current = current->next;
            free(temp);
        }
    } else {
        for (size_t s = 0; s < list->size; ++s) {
            struct list_node * temp = current;
            current = current->next;
            free(temp);
        }
    }

    *list = (list_s) { 0 };
}

static inline void insert_at_list(list_s * list, const size_t index, LIST_DATA_TYPE element) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(index <= list->size && "[ERROR] Index bigger than size");
    assert(~list->size && "[ERROR] List size will overflow.");

    struct list_node * temp = malloc(sizeof(struct list_node));
    assert(temp && "[ERROR] Memory allocation failed.");
    temp->element = element;

    struct list_node ** current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = &((*current)->next);
    }

    temp->next = list->head ? temp : *current;
    *current = temp->next;

    list->size++;
}

static inline LIST_DATA_TYPE remove_list(list_s * list, LIST_DATA_TYPE element, int (*compare_element)(const void *, const void *)) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(list->head && "[ERROR] Can't remove from empty list.");

    struct list_node ** current = &(list->head);
    if (compare_element) {
        for (size_t s = 0; s < list->size; ++s) {
            if (compare_element(&((*current)->element), &element) == 0) {
                LIST_DATA_TYPE found = (*current)->element;

                struct list_node * temp = *current;
                *current = (--list->size) ? (*current)->next : NULL;
                free(temp);

                return found;
            }
            current = &((*current)->next);
        }
    } else {
        for (size_t s = 0; s < list->size; ++s) {
            if (memcmp(&((*current)->element), &element, sizeof(LIST_DATA_TYPE)) == 0) {
                LIST_DATA_TYPE found = (*current)->element;

                struct list_node * temp = *current;
                *current = (--list->size) ? (*current)->next : NULL;
                free(temp);

                return found;
            }
            current = &((*current)->next);
        }
    }

    assert(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

static inline LIST_DATA_TYPE remove_at_list(list_s * list, const size_t index) {
    assert(list && "[ERROR] 'list' parameter is NULL.");
    assert(list->size && "[ERROR] Can't remove from empty list.");
    assert(list->head && "[ERROR] Can't remove from empty list.");
    assert(index < list->size && "[ERROR] Index greater than size");

    struct list_node ** current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = &((*current)->next);
    }

    LIST_DATA_TYPE found = (*current)->element;

    struct list_node * temp = *current;
    *current = (--list->size) ? (*current)->next : NULL;
    free(temp);

    return found;
}

static inline void reverse_list(list_s * list) {
    assert(list && "[ERROR] 'list' parameter is NULL.");

    if (list->head == NULL) {
        return;
    }

    struct list_node * current = list->head;
    struct list_node * current_next = current->next;
    struct list_node * current_next_next = current_next->next;
    for (size_t i = 0; i < list->size; ++i) {
        current_next->next = current;

        current = current_next;
        current_next = current_next_next;
        current_next_next = current_next_next->next;
    }
    list->head = list->head->next;
}

#endif

#endif //LIST_H
