#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stddef.h>  // imports size_t
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy

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

#define INFINITE_ALLOCATED_DOUBLE_LIST  1201
#define FINITE_ALLOCATED_DOUBLE_LIST    1202
#define INFINITE_REALLOC_DOUBLE_LIST    1203
#define FINITE_PREPROCESSOR_DOUBLE_LIST 1204

#define INFINITE_DOUBLE_LIST INFINITE_ALLOCATED_DOUBLE_LIST
#define FINITE_DOUBLE_LIST   FINITE_ALLOCATED_DOUBLE_LIST

//#define DOUBLE_LIST_MODE INFINITE_ALLOCATED_DOUBLE_LIST
//#define DOUBLE_LIST_MODE FINITE_ALLOCATED_DOUBLE_LIST
//#define DOUBLE_LIST_MODE INFINITE_REALLOC_DOUBLE_LIST
//#define DOUBLE_LIST_MODE FINITE_PREPROCESSOR_DOUBLE_LIST
// List mode that can be set to INFINITE_ALLOCATED_DOUBLE_LIST, FINITE_ALLOCATED_DOUBLE_LIST, INFINITE_REALLOC_DOUBLE_LIST or
// FINITE_PREPROCESSOR_DOUBLE_LIST, or INFINITE_ALLOCATED_DOUBLE_LIST or FINITE_ALLOCATED_DOUBLE_LIST
// Default: INFINITE_ALLOCATED_DOUBLE_LIST
#ifndef DOUBLE_LIST_MODE

#define DOUBLE_LIST_MODE INFINITE_ALLOCATED_DOUBLE_LIST

#endif

// Check to make sure a valid double_list mode is selected.
#if (DOUBLE_LIST_MODE != INFINITE_ALLOCATED_DOUBLE_LIST) && (DOUBLE_LIST_MODE != FINITE_ALLOCATED_DOUBLE_LIST)    && \
    (DOUBLE_LIST_MODE != INFINITE_REALLOC_DOUBLE_LIST)   && (DOUBLE_LIST_MODE != FINITE_PREPROCESSOR_DOUBLE_LIST)

#error Invalid type of list mode.

#endif

// List data type to specify what datatype to double_list.
// DEFAULT: void *
#ifndef DOUBLE_LIST_DATA_TYPE

#define DOUBLE_LIST_DATA_TYPE void*

#endif

#ifndef DOUBLE_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
#define DOUBLE_LIST_ASSERT assert

#endif

#if DOUBLE_LIST_MODE != FINITE_PREPROCESSOR_DOUBLE_LIST

#if !defined(DOUBLE_LIST_REALLOC) && !defined(DOUBLE_LIST_FREE)

#include <stdlib.h>

#ifndef DOUBLE_LIST_REALLOC

#define DOUBLE_LIST_REALLOC realloc

#endif

#ifndef DOUBLE_LIST_FREE

#define DOUBLE_LIST_FREE free

#endif

#elif !defined(DOUBLE_LIST_REALLOC)

#error Reallocator macro is not defined!

#elif !defined(DOUBLE_LIST_FREE)

#error Free macro is not defined!

#endif

#endif

typedef DOUBLE_LIST_DATA_TYPE (*copy_double_list_fn)    (const DOUBLE_LIST_DATA_TYPE);
typedef void                  (*destroy_double_list_fn) (DOUBLE_LIST_DATA_TYPE *);
typedef int                   (*compare_double_list_fn) (const DOUBLE_LIST_DATA_TYPE, const DOUBLE_LIST_DATA_TYPE);
typedef bool                  (*operate_double_list_fn) (DOUBLE_LIST_DATA_TYPE *, void *);
typedef void                  (*manage_double_list_fn)  (DOUBLE_LIST_DATA_TYPE *, size_t, void *);

#define DOUBLE_LIST_NODE_COUNT 2
#define DOUBLE_LIST_NEXT_INDEX 0
#define DOUBLE_LIST_PREV_INDEX 1

#if   DOUBLE_LIST_MODE == INFINITE_ALLOCATED_DOUBLE_LIST

struct double_list_node {
    struct double_list_node * node[DOUBLE_LIST_NODE_COUNT]; // array of pointers to nodes
    DOUBLE_LIST_DATA_TYPE element;
};

/// Doubly linked circular list data structure.
typedef struct list {
    struct double_list_node * head; // pointer to head/start index
    size_t size;
} double_list_s;

/// @brief Creates an empty list.
/// @return Empty list.
static inline double_list_s create_double_list(void) {
    return (double_list_s) { 0 };
}

/// @brief Destroys a list and its elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
/// @note The list is unusable after destroying it, otherwise use the clear function or create a new list.
static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    for (size_t s = 0; s < list->size; ++s) {
        struct double_list_node * next = list->head->node[DOUBLE_LIST_NEXT_INDEX]; // pointer to next node from head

        destroy(&(list->head->element)); // destroy element at head
        DOUBLE_LIST_FREE(list->head); // then free node at head
        list->head = next; // set node next to head as new head
    }

    (*list) = (double_list_s) { 0 }; // set list to zero (similar to creating it, so the list is actually usable)
}

/// @brief Clears a list's elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
static inline void clear_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    for (size_t s = 0; s < list->size; ++s) {
        struct double_list_node * next = list->head->node[DOUBLE_LIST_NEXT_INDEX];

        destroy(&(list->head->element)); // destroy element at head
        DOUBLE_LIST_FREE(list->head); // then free node at head
        list->head = next; // set node next to head as new head
    }

    (*list) = (double_list_s) { 0 }; // set list to zero (similar to creating it)
}

/// @brief Inserts element into list based on index number.
/// @param list Pointer of list to insert element into.
/// @param index Zero-based index to specify where to insert element.
/// @param element Element to insert into list at index.
static inline void insert_at_double_list(double_list_s * list, const size_t index, const DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index is bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    // create new node to insert
    struct double_list_node * node = DOUBLE_LIST_REALLOC(NULL, sizeof(struct double_list_node));
    DOUBLE_LIST_ASSERT(node && "[ERROR] Memory allocation failed.");

    // iterate and calculate real position in doubly linked list where to insert node
    const size_t real_index = index < (list->size >> 1) ? index : list->size - index; // actual index to limit traversal
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    struct double_list_node * current = list->head; // node pointer to node at index
    for (size_t i = 0; i < real_index; ++i) { // iterate until node at real index position and direction is reached
        current = current->node[node_index];
    }

    if (list->head) { // if head isn't NULL place it between current node and its previous sibling
        node->node[DOUBLE_LIST_NEXT_INDEX] = current;
        node->node[DOUBLE_LIST_PREV_INDEX] = current->node[DOUBLE_LIST_PREV_INDEX];

        current->node[DOUBLE_LIST_PREV_INDEX]->node[DOUBLE_LIST_NEXT_INDEX] = node;
        current->node[DOUBLE_LIST_PREV_INDEX] = node;

        if (!index) { // if index is zero, i.e. points to head, then list's head must be set to node
            list->head = node;
        }
    } else { // else head is NULL thus node is made circular and placed as first head
        list->head = node->node[DOUBLE_LIST_NEXT_INDEX] = node->node[DOUBLE_LIST_PREV_INDEX] = node;
    }

    memcpy(&(node->element), &element, sizeof(DOUBLE_LIST_DATA_TYPE));
    list->size++;
}

/// Gets the element at specified index without changing the list.
/// @param list List structure to get element from.
/// @param index Zero-based index of element in list.
/// @return Element at index position.
static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.head && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct double_list_node const * current = list.head; // set current node as head to later return index node element
    const size_t real_index = index < (list.size >> 1) ? index : list.size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) {
        current = current->node[node_index];
    }

    return current->element; // return element at index node
}

/// @brief Removes first instance of element in list.
/// @param list Pointer of list to remove first instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return First element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_first_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    struct double_list_node ** current = &(list->head); // set pointer to node as head
    for (size_t i = 0; i < list->size; ++i) { // iterate for each element until parameter is reached
        if (0 == compare((*current)->element, element)) { // if parameter equals current element remove and return it
            DOUBLE_LIST_DATA_TYPE removed = (*current)->element; // save removed element to not loose it
            list->size--;
            // pointer magic
            struct double_list_node * node = (*current); // save temporary node to not loose it later
            // changes next pointer in previous node because current may not change it if pointing to head
            (*current)->node[DOUBLE_LIST_NEXT_INDEX]->node[DOUBLE_LIST_PREV_INDEX] = (*current)->node[DOUBLE_LIST_PREV_INDEX];
            (*current)->node[DOUBLE_LIST_PREV_INDEX]->node[DOUBLE_LIST_NEXT_INDEX] = (*current)->node[DOUBLE_LIST_NEXT_INDEX];

            (*current) = list->size ? (*current)->node[DOUBLE_LIST_NEXT_INDEX] : NULL; // changes head pointer to next if pointing to it
            DOUBLE_LIST_FREE(node);

            return removed;
        }

        current = (*current)->node + DOUBLE_LIST_NEXT_INDEX;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes last instance of element in list by traversing backwards.
/// @param list Pointer of list to remove last instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return Last element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_last_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    struct double_list_node * current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        current = current->node[DOUBLE_LIST_PREV_INDEX]; // save next as current since we start from head and not tail

        if (0 != compare(current->element, element)) { // if elements are not equal then continue iteration
            continue;
        }

        DOUBLE_LIST_DATA_TYPE removed = current->element; // save removed element to not loose it
        list->size--;

        current->node[DOUBLE_LIST_NEXT_INDEX]->node[DOUBLE_LIST_PREV_INDEX] = current->node[DOUBLE_LIST_PREV_INDEX];
        current->node[DOUBLE_LIST_PREV_INDEX]->node[DOUBLE_LIST_NEXT_INDEX] = current->node[DOUBLE_LIST_NEXT_INDEX];

        if (current == list->head) { // if head is removed then either change it to next node or NULL if list is empty
            list->head = (list->size) ? current->node[DOUBLE_LIST_NEXT_INDEX] : NULL;
        }

        DOUBLE_LIST_FREE(current);

        return removed;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index position in list.
/// @param list Pointer of list to remove element from.
/// @param index Zero-based index to remove element at.
/// @return Element in list at index.
static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct double_list_node * current = list->head; // save current pointer to iterate over
    const size_t real_index = index < (list->size >> 1) ? index : list->size - index; // get index size to iterate over
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX; // get node's index
    for (size_t i = 0; i < real_index; ++i) { // iterate nodes until node to remove is found
        current = current->node[node_index];
    }

    DOUBLE_LIST_DATA_TYPE removed = current->element; // save element to remove to not lose it when destroying node
    list->size--;

    // make previous node's next pointer to current's next and vice verse
    current->node[DOUBLE_LIST_PREV_INDEX]->node[DOUBLE_LIST_NEXT_INDEX] = current->node[DOUBLE_LIST_NEXT_INDEX];
    current->node[DOUBLE_LIST_NEXT_INDEX]->node[DOUBLE_LIST_PREV_INDEX] = current->node[DOUBLE_LIST_PREV_INDEX];

    DOUBLE_LIST_FREE(current); // destroy removed node

    if (!list->size) { // if list is empty then make head NULL
        list->head = NULL;
    }

    return removed;
}

/// @brief Reverses list element ordering.
/// @param list Pointer of list to reverse.
static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    struct double_list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        list->head = current;

        struct double_list_node * next = current->node[DOUBLE_LIST_NEXT_INDEX];
        current->node[DOUBLE_LIST_NEXT_INDEX] = current->node[DOUBLE_LIST_PREV_INDEX];
        current->node[DOUBLE_LIST_PREV_INDEX] = next;

        current = current->node[DOUBLE_LIST_PREV_INDEX];
    }
}

/// @brief Shifts list node by next n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->head->node[DOUBLE_LIST_NEXT_INDEX];
    }
}

/// @brief Shifts list node by previous n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->head->node[DOUBLE_LIST_PREV_INDEX];
    }
}

/// @brief Splices source list into destination list at specified index.
/// @param destination Pointer of list to splice into.
/// @param source Pointer of list to splice from.
/// @param index Zero-based index at destination list to start splicing.
static inline void splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    struct double_list_node * current = destination->head;
    const size_t real_index = index < (destination->size >> 1) ? index : destination->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) {
        current = current->node[node_index];
    }

    if (current && source->head) {
        struct double_list_node * first_destination = current;
        struct double_list_node * last_destination  = current->node[DOUBLE_LIST_PREV_INDEX];

        struct double_list_node * first_source = source->head;
        struct double_list_node * last_source  = source->head->node[DOUBLE_LIST_PREV_INDEX];

        last_destination->node[DOUBLE_LIST_NEXT_INDEX] = first_source;
        first_source->node[DOUBLE_LIST_PREV_INDEX] = last_destination;

        last_source->node[DOUBLE_LIST_NEXT_INDEX] = first_destination;
        first_destination->node[DOUBLE_LIST_PREV_INDEX] = last_source;
    }

    if (!index) {
        destination->head = source->head;
    }

    destination->size += source->size;

    (*source) = (double_list_s) { 0 };
}

/// @brief Splits list at index and removes size parameter elements as new list.
/// @param list Pointer of list to split.
/// @param index Zero-based index at list to start splitting.
/// @param size Number of elements to split and return as new list.
/// @return Split list with size number of elements at index.
/// @note Since the list is circular the function can be used to split it as a circle at any index.
static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size && "[ERROR] Size parameter can't be zero");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    struct double_list_node * current_index = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) { // go to node at index
        current_index = current_index->node[node_index];
    }

    struct double_list_node * current_size = current_index;
    const size_t real_size = size <= (list->size >> 1) ? size - 1 : list->size - size + 1;
    const bool node_size = real_size == size - 1 ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_size; ++i) { // go to node at index plus size starting from index node
        current_size = current_size->node[node_size];
    }

    if (!index || ((index + size) >= list->size)) { // if head node becomes part of split then change list's head node
        list->head = list->size ? current_size->node[DOUBLE_LIST_NEXT_INDEX] : NULL; // if list becomes empty make head NULL
    }

    list->size -= size;

    struct double_list_node * first_list = current_size->node[DOUBLE_LIST_NEXT_INDEX];
    struct double_list_node * last_list  = current_index->node[DOUBLE_LIST_PREV_INDEX];

    struct double_list_node * first_split = current_index;
    struct double_list_node * last_split  = current_size;

    first_list->node[DOUBLE_LIST_PREV_INDEX] = last_list;
    last_list->node[DOUBLE_LIST_NEXT_INDEX] = first_list;

    first_split->node[DOUBLE_LIST_PREV_INDEX] = last_split;
    last_split->node[DOUBLE_LIST_NEXT_INDEX] = first_split;

    return (double_list_s) { .head = first_split, .size = size };
}

/// @brief Checks if list is empty.
/// @param list List structure to check.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_double_list(const double_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure to check.
/// @return 'true' if list is full, 'false' otherwise.
/// @note Since the list is infinite the function checks if size will overflows.
static inline bool is_full_double_list(const double_list_s list) {
    return !(~list.size);
}

/// @brief Creates and returns a copy of the list with all elements based on copy function poniter.
/// @param list List structure to replicate.
/// @param copy Function pointer that returns a deep or shallow copy of an element.
/// @return Replicated list with all elements.
static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    DOUBLE_LIST_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");

    double_list_s replica = { .head = list.head, .size = list.size };

    struct double_list_node const * current_list = list.head;
    struct double_list_node ** current_copy = &(replica.head);
    for (size_t i = 0; i < list.size; ++i) {
        struct double_list_node * node = DOUBLE_LIST_REALLOC(NULL, sizeof(struct double_list_node));
        DOUBLE_LIST_ASSERT(node && "[ERROR] Memory allocation failed");
        node->element = copy(current_list->element);

        (*current_copy) = node->node[DOUBLE_LIST_PREV_INDEX] = node; // *current_copy and temp's prev will point to temp
        node->node[DOUBLE_LIST_NEXT_INDEX] = replica.head; // temp's next points to head (if *current_copy is head then temp's next points to temp)
        // temp's prev points to replica.head's prev (if *current_copy is head then head/temp->prev is temp, else temp->prev is previous node)
        node->node[DOUBLE_LIST_PREV_INDEX] = replica.head->node[DOUBLE_LIST_PREV_INDEX];
        // head's prev points to temp (if *current_copy is head then head/temp prev is temp, else head prev is last node)
        replica.head->node[DOUBLE_LIST_PREV_INDEX] = node;

        current_list = current_list->node[DOUBLE_LIST_NEXT_INDEX];
        current_copy = &((*current_copy)->node[DOUBLE_LIST_NEXT_INDEX]);
    }

    return replica;
}

/// @brief Iterates over elements in list and operates on each of them based on arguments.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_double_list(double_list_s const * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct double_list_node * current = list->head;
    for (size_t i = 0; i < list->size && operate(&current->element, args); ++i) {
        current = current->node[DOUBLE_LIST_NEXT_INDEX];
    }
}

/// @brief Iterates over elements in list and operates on each of them based on arguments, but in reverse order.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_reverse_double_list(const double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct double_list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = current->node[DOUBLE_LIST_PREV_INDEX];

        if (!operate(&current->element, args)) {
            return;
        }
    }
}

/// Maps list into array and manages it using list size and arguments.
/// @param list Pointer of list to map.
/// @param manage Function pointer to manage list as array using its size, and arguments.
/// @param args Generic arguments to use in manage function, or can be NULL.
static inline void map_double_list(double_list_s const * list, const manage_double_list_fn manage, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(manage && "[ERROR] 'manage' parameter pointer is NULL.");

    DOUBLE_LIST_DATA_TYPE * elements_array = DOUBLE_LIST_REALLOC(NULL, list->size);
    DOUBLE_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct double_list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = current->element;
        current = current->node[DOUBLE_LIST_NEXT_INDEX];
    }

    manage(elements_array, list->size, args);

    for (size_t i = 0; i < list->size; ++i) {
        current->element = elements_array[i];
        current = current->node[DOUBLE_LIST_NEXT_INDEX];
    }

    DOUBLE_LIST_FREE(elements_array);
}

#elif DOUBLE_LIST_MODE == FINITE_ALLOCATED_DOUBLE_LIST

typedef struct list {
    size_t size, max, head;

    DOUBLE_LIST_DATA_TYPE * elements;
    size_t * node[DOUBLE_LIST_NODE_COUNT];
} double_list_s;

/// @brief Creates an empty list.
/// @return Empty list.
static inline double_list_s create_double_list(const size_t max) {
    DOUBLE_LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const double_list_s list = {
        .elements                     = DOUBLE_LIST_REALLOC(NULL, sizeof(DOUBLE_LIST_DATA_TYPE) * max),
        .node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(NULL, sizeof(size_t) * max),
        .node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(NULL, sizeof(size_t) * max),

        .head = 0, .max = max, .size = 0,
    };

    DOUBLE_LIST_ASSERT(list.elements && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list.node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(list.node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] Memory allocation failed.");

    return list;
}

/// @brief Destroys a list and its elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
/// @note The list is unusable after destroying it, otherwise use the clear function or create a new list.
static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        destroy(list->elements + current);
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    DOUBLE_LIST_FREE(list->elements);
    DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_NEXT_INDEX]);
    DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_PREV_INDEX]);

    (*list) = (double_list_s) { 0 };
}

/// @brief Clears a list's elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
static inline void clear_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        destroy(list->elements + current);
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    list->head = list->size = 0;
}

/// @brief Inserts element into list based on index number.
/// @param list Pointer of list to insert element into.
/// @param index Zero-based index to specify where to insert element.
/// @param element Element to insert into list at index.
static inline void insert_at_double_list(double_list_s * list, const size_t index, const DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size < list->max && "[ERROR] List reached maximum size.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[node_index][current];
    }

    list->node[DOUBLE_LIST_NEXT_INDEX][list->size] = current;
    list->node[DOUBLE_LIST_PREV_INDEX][list->size] = list->node[DOUBLE_LIST_PREV_INDEX][current];

    list->node[DOUBLE_LIST_PREV_INDEX][current] = list->size;
    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->size;

    if (!index) {
        list->head = list->size;
    }

    memcpy(list->elements + list->size, &element, sizeof(DOUBLE_LIST_DATA_TYPE));
    list->size++;
}

/// Gets the element at specified index without changing the list.
/// @param list List structure to get element from.
/// @param index Zero-based index of element in list.
/// @return Element at index position.
static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    const size_t real_index = index < (list.size >> 1) ? index : list.size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) {
        current = list.node[node_index][current];
    }

    return list.elements[current];
}

/// @brief Removes first instance of element in list.
/// @param list Pointer of list to remove first instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return First element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_first_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    DOUBLE_LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (0 != compare(list->elements[current], element)) {
            current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[DOUBLE_LIST_NEXT_INDEX][current] == list->size - 1) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
        }

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

        DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
        list->size--;

        // move element at double_list->size - 1 to current's position to avoid 'holes' in array.
        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return removed;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes last instance of element in list by traversing backwards.
/// @param list Pointer of list to remove last instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return Last element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_last_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    DOUBLE_LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[DOUBLE_LIST_PREV_INDEX][current];

        if (0 != compare(list->elements[current], element)) {
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[DOUBLE_LIST_NEXT_INDEX][current] == list->size - 1) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
        }

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

        DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
        list->size--;

        // move element at double_list->size - 1 to current's position to avoid 'holes' in array.
        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return removed;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index position in list.
/// @param list Pointer of list to remove element from.
/// @param index Zero-based index to remove element at.
/// @return Element in list at index.
static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) {
        current = list->node[node_index][current];
    }

    if (list->head == list->size - 1) {
        list->head = current;
    } else if (list->head == current) {
        list->head = (list->node[DOUBLE_LIST_NEXT_INDEX][current] == list->size - 1) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
    list->size--;

    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

    // move element at double_list->size - 1 to current's position to avoid 'holes' in array.
    list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
    list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

    list->elements[current] = list->elements[list->size];
    list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;

    return removed;
}

/// @brief Reverses list element ordering.
/// @param list Pointer of list to reverse.
static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        list->head = current;

        const size_t temp = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = temp;

        current = list->node[DOUBLE_LIST_PREV_INDEX][current];
    }
}

/// @brief Shifts list node by next n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_NEXT_INDEX][list->head];
    }
}

/// @brief Shifts list node by previous n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_PREV_INDEX][list->head];
    }
}

/// @brief Splices source list into destination list at specified index.
/// @param destination Pointer of list to splice into.
/// @param source Pointer of list to splice from.
/// @param index Zero-based index at destination list to start splicing.
/// @param max New non-zero maximum size of destination list.
static inline void splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index, const size_t max) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    DOUBLE_LIST_ASSERT(destination->size + source->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    size_t current = destination->head;
    const size_t real_index = index < (destination->size >> 1) ? index : destination->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) {
        current = destination->node[node_index][current];
    }

    destination->max = max;
    destination->elements = DOUBLE_LIST_REALLOC(destination->elements, sizeof(DOUBLE_LIST_DATA_TYPE) * max);
    destination->node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(destination->node[DOUBLE_LIST_NEXT_INDEX], sizeof(size_t) * max);
    destination->node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(destination->node[DOUBLE_LIST_PREV_INDEX], sizeof(size_t) * max);

    for (size_t i = 0; i < source->size; ++i) {
        destination->elements[destination->size + i] = source->elements[i];
        destination->node[DOUBLE_LIST_NEXT_INDEX][destination->size + i] = source->node[DOUBLE_LIST_NEXT_INDEX][i] + destination->size;
        destination->node[DOUBLE_LIST_PREV_INDEX][destination->size + i] = source->node[DOUBLE_LIST_PREV_INDEX][i] + destination->size;
    }
    // source elements and its nodes were copied in destination, thus source and destination are spliced only in destination
    if (destination->size && source->size) {
        const size_t first_destination = current;
        const size_t last_destination  = destination->node[DOUBLE_LIST_PREV_INDEX][current];

        const size_t first_source = source->head + destination->size;
        const size_t last_source  = source->node[DOUBLE_LIST_PREV_INDEX][source->head] + destination->size;

        destination->node[DOUBLE_LIST_NEXT_INDEX][last_destination] = first_source;
        destination->node[DOUBLE_LIST_PREV_INDEX][first_source] = last_destination; // source is in destination

        destination->node[DOUBLE_LIST_NEXT_INDEX][last_source] = first_destination; // source is in destination
        destination->node[DOUBLE_LIST_PREV_INDEX][first_destination] = last_source;
    }

    if (!index && source->size) { // if source isn't empty and inedx points to head node destination's make head to source's
        destination->head = source->head + destination->size;
    }

    destination->size += source->size;

    source->size = source->head = 0; // clear source, DON'T DESTROY IT
}

/// @brief Splits list at index and removes size parameter elements as new list.
/// @param list Pointer of list to split.
/// @param index Zero-based index at list to start splitting.
/// @param size Number of elements to split and return as new list.
/// @param max Non-zero maximum size of new split list.
/// @return Split list with size number of elements at index.
/// @note Since the list is circular the function can be used to split it as a circle at any index.
static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size, const size_t max) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(max && "[ERROR] max size can't be zero.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size && "[ERROR] Size parameter can't be zero");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    DOUBLE_LIST_ASSERT(size <= max && "[ERROR] List size exceed max size of new split list.");

    size_t list_current = list->head;
    const size_t real_index = index < (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) {
        list_current = list->node[node_index][list_current];
    }

    double_list_s split = {
        .head = 0, .size = 0,
        .elements                     = DOUBLE_LIST_REALLOC(NULL, sizeof(DOUBLE_LIST_DATA_TYPE) * max),
        .node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(NULL, sizeof(size_t) * max),
        .node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(NULL, sizeof(size_t) * max),
    };

    DOUBLE_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed");
    DOUBLE_LIST_ASSERT(split.node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] Memory allocation failed");
    DOUBLE_LIST_ASSERT(split.node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] Memory allocation failed");

    size_t * split_current = &(split.head);
    for (; split.size < list->size; split.size++) {
        split.elements[split.size] = list->elements[list_current];
        (*split_current) = split.size; // set head and next nodes to next index
        split.node[DOUBLE_LIST_PREV_INDEX][split.size] = split.size - 1; // set previous node indexes to one minus current
        list->size--;

        // swap element and node indexes at current index with last in elements and nodes arrays
        list->elements[list_current] = list->elements[list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = list_current;
        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = list_current;

        list_current = list->node[DOUBLE_LIST_NEXT_INDEX][list_current]; // go to next list node
        split_current = split.node[DOUBLE_LIST_NEXT_INDEX] + split.size; // go to next split list node pointer
    }
    split.node[DOUBLE_LIST_PREV_INDEX][0] = size - 1; // to make list circular first index in previous must point to last element
    (*split_current) = 0;

    if (!index || (index > list->size)) {
        list->head = list_current;
    }

    return split;
}

/// @brief Checks if list is empty.
/// @param list List structure to check.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_double_list(const double_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure to check.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_double_list(const double_list_s list) {
    return (list.size == list.max);
}

/// @brief Creates and returns a copy of the list with all elements based on copy function poniter.
/// @param list List structure to replicate.
/// @param copy Function pointer that returns a deep or shallow copy of an element.
/// @return Replicated list with all elements.
static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    DOUBLE_LIST_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");

    double_list_s replica = {
        .elements                     = DOUBLE_LIST_REALLOC(NULL, sizeof(DOUBLE_LIST_DATA_TYPE) * list.max),
        .node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(NULL, sizeof(size_t) * list.max),
        .node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(NULL, sizeof(size_t) * list.max),
        .head = list.head, .max = list.max, .size = 0,
    };

    DOUBLE_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(replica.node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] Memory allocation failed.");
    DOUBLE_LIST_ASSERT(replica.node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] Memory allocation failed.");

    for (; replica.size < list.size; replica.size++) {
        replica.elements[replica.size] = copy(list.elements[replica.size]);
        replica.node[DOUBLE_LIST_NEXT_INDEX][replica.size] = list.node[DOUBLE_LIST_NEXT_INDEX][replica.size];
        replica.node[DOUBLE_LIST_PREV_INDEX][replica.size] = list.node[DOUBLE_LIST_PREV_INDEX][replica.size];
    }

    return replica;
}

/// @brief Iterates over elements in list and operates on each of them based on arguments.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_double_list(double_list_s const * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size && operate(list->elements + current, args); ++i) {
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }
}

/// @brief Iterates over elements in list and operates on each of them based on arguments, but in reverse order.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_reverse_double_list(const double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[DOUBLE_LIST_PREV_INDEX][current];

        if (!operate(list->elements + current, args)) {
            return;
        }
    }
}

/// Maps list into array and manages it using list size and arguments.
/// @param list Pointer of list to map.
/// @param manage Function pointer to manage list as array using its size, and arguments.
/// @param args Generic arguments to use in manage function, or can be NULL.
static inline void map_double_list(double_list_s const * list, const manage_double_list_fn manage, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(manage && "[ERROR] 'manage' parameter pointer is NULL.");

    DOUBLE_LIST_DATA_TYPE * elements_array = DOUBLE_LIST_REALLOC(NULL, sizeof(DOUBLE_LIST_DATA_TYPE) * list->size);
    DOUBLE_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = list->elements[current];
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    manage(elements_array, list->size, args);

    for (size_t i = 0; i < list->size; ++i) {
        list->elements[current] = elements_array[i];
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    DOUBLE_LIST_FREE(elements_array);
}

#elif DOUBLE_LIST_MODE == INFINITE_REALLOC_DOUBLE_LIST

#if !defined(IS_CAPACITY_DOUBLE_LIST) && !defined(EXPAND_CAPACITY_DOUBLE_LIST)

#ifndef REALLOC_DOUBLE_LIST_CHUNK

#define REALLOC_DOUBLE_LIST_CHUNK (1 << 5)

#elif REALLOC_DOUBLE_LIST_CHUNK <= 0

#error 'REALLOC_DOUBLE_LIST_CHUNK' cannot be less than or equal to 0

#endif

/// @brief Checks if stack's 'size' has reached capacity.
#define IS_CAPACITY_DOUBLE_LIST(size) (!((size) % REALLOC_DOUBLE_LIST_CHUNK))

/// @brief Calculates next stack's capacity based on 'size'.
#define EXPAND_CAPACITY_DOUBLE_LIST(capacity) ((capacity) + REALLOC_DOUBLE_LIST_CHUNK)

#elif !defined(IS_CAPACITY_DOUBLE_LIST)

#error Stack capacity reached check is not defined.

#elif !defined(EXPAND_CAPACITY_DOUBLE_LIST)

#error Stack capacity expanded size is not defined.

#endif

typedef struct list {
    size_t size, head;

    DOUBLE_LIST_DATA_TYPE * elements;
    size_t * node[DOUBLE_LIST_NODE_COUNT];
} double_list_s;

/// @brief Creates an empty list.
/// @return Empty list.
static inline double_list_s create_double_list(void) {
    return (double_list_s) { 0 };
}

/// @brief Destroys a list and its elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
/// @note The list is unusable after destroying it, otherwise use the clear function or create a new list.
static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        destroy(&(list->elements[current]));
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    DOUBLE_LIST_FREE(list->elements);
    DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_NEXT_INDEX]);
    DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_PREV_INDEX]);

    (*list) = (double_list_s) { 0 };
}

/// @brief Clears a list's elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
static inline void clear_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        destroy(&(list->elements[current]));
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    DOUBLE_LIST_FREE(list->elements);
    DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_NEXT_INDEX]);
    DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_PREV_INDEX]);

    (*list) = (double_list_s) { 0 };
}

/// @brief Inserts element into list based on index number.
/// @param list Pointer of list to insert element into.
/// @param index Zero-based index to specify where to insert element.
/// @param element Element to insert into list at index.
static inline void insert_at_double_list(double_list_s * list, const size_t index, const DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    if ((IS_CAPACITY_DOUBLE_LIST(list->size))) { // if size reached capacity expand elements and nodes arrays
        const size_t expand = EXPAND_CAPACITY_DOUBLE_LIST(list->size);

        list->elements = DOUBLE_LIST_REALLOC(list->elements, expand * sizeof(DOUBLE_LIST_DATA_TYPE));
        list->node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(list->elements, expand * sizeof(size_t));
        list->node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(list->elements, expand * sizeof(size_t));
    }

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[node_index][current];
    }

    list->node[DOUBLE_LIST_NEXT_INDEX][list->size] = current;
    list->node[DOUBLE_LIST_PREV_INDEX][list->size] = list->node[DOUBLE_LIST_PREV_INDEX][current];

    list->node[DOUBLE_LIST_PREV_INDEX][current] = list->size;
    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->size;
    if (!index) {
        list->head = list->size;
    }

    memcpy(list->elements + list->size, &element, sizeof(DOUBLE_LIST_DATA_TYPE));
    list->size++;
}

/// Gets the element at specified index without changing the list.
/// @param list List structure to get element from.
/// @param index Zero-based index of element in list.
/// @return Element at index position.
static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    const size_t real_index = index <= (list.size >> 1) ? index : list.size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list.size; ++i) {
        current = list.node[node_index][current];
    }

    return list.elements[current];
}

/// @brief Removes first instance of element in list.
/// @param list Pointer of list to remove first instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return First element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_first_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    DOUBLE_LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (0 != compare(list->elements[current], element)) {
            current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[DOUBLE_LIST_NEXT_INDEX][current] == list->size - 1) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
        }

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

        DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
        list->size--;

        // move element at double_list->size - 1 to current's position to avoid 'holes' in array.
        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        if (!list->size) { // if list bacomes empty free elements and nodes arrays and set thme to zero
            DOUBLE_LIST_FREE(list->elements);
            DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_NEXT_INDEX]);
            DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_PREV_INDEX]);
            list->elements = NULL;
            list->node[DOUBLE_LIST_NEXT_INDEX] = NULL;
            list->node[DOUBLE_LIST_PREV_INDEX] = NULL;
        } else if ((IS_CAPACITY_DOUBLE_LIST(list->size))) { // else if bottom capacity is reached shrink arrays
            list->elements = DOUBLE_LIST_REALLOC(list->elements, list->size * sizeof(DOUBLE_LIST_DATA_TYPE));
            list->node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_NEXT_INDEX], list->size * sizeof(size_t));
            list->node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_PREV_INDEX], list->size * sizeof(size_t));
        }

        return removed;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in double_list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes last instance of element in list by traversing backwards.
/// @param list Pointer of list to remove last instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return Last element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_last_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    DOUBLE_LIST_ASSERT(list->elements && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] No memory available.");
    DOUBLE_LIST_ASSERT(list->node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] No memory available.");

    size_t current = list->head;
    for (size_t s = 0; s < list->size; ++s) {
        current = list->node[DOUBLE_LIST_PREV_INDEX][current];

        if (0 != compare(list->elements[current], element)) {
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[DOUBLE_LIST_NEXT_INDEX][current] == list->size - 1) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
        }

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

        DOUBLE_LIST_DATA_TYPE found = list->elements[current];

        // move element at double_list->size - 1 to current's position to avoid 'holes' in array.
        list->size--;
        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        if (!list->size) { // if list bacomes empty free elements and nodes arrays and set thme to zero
            DOUBLE_LIST_FREE(list->elements);
            DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_NEXT_INDEX]);
            DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_PREV_INDEX]);
            list->elements = NULL;
            list->node[DOUBLE_LIST_NEXT_INDEX] = NULL;
            list->node[DOUBLE_LIST_PREV_INDEX] = NULL;
        } else if ((IS_CAPACITY_DOUBLE_LIST(list->size))) { // else if bottom capacity is reached shrink arrays
            list->elements = DOUBLE_LIST_REALLOC(list->elements, list->size * sizeof(DOUBLE_LIST_DATA_TYPE));
            list->node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_NEXT_INDEX], list->size * sizeof(size_t));
            list->node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_PREV_INDEX], list->size * sizeof(size_t));
        }

        return found;
    }

    DOUBLE_LIST_ASSERT(0 && "[ERROR] Element not found in double_list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index position in list.
/// @param list Pointer of list to remove element from.
/// @param index Zero-based index to remove element at.
/// @return Element in list at index.
static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index parameter greater than list size.");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[node_index][current];
    }

    if (list->head == list->size - 1) {
        list->head = current;
    } else if (list->head == current) {
        list->head = (list->node[DOUBLE_LIST_NEXT_INDEX][current] == list->size - 1) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

    DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
    list->size--;

    // move element at double_list->size - 1 to current's position to avoid 'holes' in array.
    list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
    list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
    list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
    list->elements[current] = list->elements[list->size];

    if (!list->size) { // if list bacomes empty free elements and nodes arrays and set thme to zero
        DOUBLE_LIST_FREE(list->elements);
        DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_NEXT_INDEX]);
        DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_PREV_INDEX]);
        list->elements = NULL;
        list->node[DOUBLE_LIST_NEXT_INDEX] = NULL;
        list->node[DOUBLE_LIST_PREV_INDEX] = NULL;
    } else if ((IS_CAPACITY_DOUBLE_LIST(list->size))) { // else if bottom capacity is reached shrink arrays
        list->elements = DOUBLE_LIST_REALLOC(list->elements, list->size * sizeof(DOUBLE_LIST_DATA_TYPE));
        list->node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_NEXT_INDEX], list->size * sizeof(size_t));
        list->node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_PREV_INDEX], list->size * sizeof(size_t));
    }

    return removed;
}

/// @brief Reverses list element ordering.
/// @param list Pointer of list to reverse.
static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        list->head = current;

        const size_t temp = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = temp;

        current = list->node[DOUBLE_LIST_PREV_INDEX][current];
    }
}

/// @brief Shifts list node by next n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_NEXT_INDEX][list->head];
    }
}

/// @brief Shifts list node by previous n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_PREV_INDEX][list->head];
    }
}

/// @brief Splices source list into destination list at specified index.
/// @param destination Pointer of list to splice into.
/// @param source Pointer of list to splice from.
/// @param index Zero-based index at destination list to start splicing.
static inline void splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    size_t current = destination->head;
    const size_t real_index = index <= (destination->size >> 1) ? index : destination->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < destination->size; ++i) {
        current = destination->node[node_index][current];
    }

    for (size_t i = 0; i < source->size; ++i) { // push source elements and nodes with proper node indexes to destination
        if ((IS_CAPACITY_DOUBLE_LIST((destination->size + i)))) { // expand destination capacity if needed
            const size_t expand = EXPAND_CAPACITY_DOUBLE_LIST(destination->size);

            destination->elements = DOUBLE_LIST_REALLOC(destination->elements, expand * sizeof(DOUBLE_LIST_DATA_TYPE));
            DOUBLE_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed.");
            destination->node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(destination->node[DOUBLE_LIST_NEXT_INDEX], expand * sizeof(size_t));
            DOUBLE_LIST_ASSERT(destination->node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] Memory allocation failed.");
            destination->node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(destination->node[DOUBLE_LIST_PREV_INDEX], expand * sizeof(size_t));
            DOUBLE_LIST_ASSERT(destination->node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] Memory allocation failed.");
        }

        destination->elements[destination->size + i] = source->elements[i];
        destination->node[DOUBLE_LIST_NEXT_INDEX][destination->size + i] = source->node[DOUBLE_LIST_NEXT_INDEX][i] + destination->size;
        destination->node[DOUBLE_LIST_PREV_INDEX][destination->size + i] = source->node[DOUBLE_LIST_PREV_INDEX][i] + destination->size;
    }
    // source elements and its nodes were copied in destination, thus source and destination are spliced only in destination
    if (destination->size && source->size) { // if there is something to splice
        const size_t first_destination = current;
        const size_t last_destination  = destination->node[DOUBLE_LIST_PREV_INDEX][current];

        const size_t first_source = source->head;
        const size_t last_source  = source->node[DOUBLE_LIST_PREV_INDEX][source->head];

        destination->node[DOUBLE_LIST_NEXT_INDEX][last_destination] = first_source;
        destination->node[DOUBLE_LIST_PREV_INDEX][first_source] = last_destination;

        destination->node[DOUBLE_LIST_NEXT_INDEX][last_source] = first_destination;
        destination->node[DOUBLE_LIST_PREV_INDEX][first_destination] = last_source;
    }

    DOUBLE_LIST_FREE(source->elements);
    DOUBLE_LIST_FREE(source->node[DOUBLE_LIST_NEXT_INDEX]);
    DOUBLE_LIST_FREE(source->node[DOUBLE_LIST_PREV_INDEX]);

    if (!index && source->size) { // if source isn't empty and inedx points to head node destination's make head to source's
        destination->head = source->head + destination->size;
    }

    destination->size += source->size;

    (*source) = (double_list_s) { 0 }; // clear source
}

/// @brief Splits list at index and removes size parameter elements as new list.
/// @param list Pointer of list to split.
/// @param index Zero-based index at list to start splitting.
/// @param size Number of elements to split and return as new list.
/// @return Split list with size number of elements at index.
/// @note Since the list is circular the function can be used to split it as a circle at any index.
static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size && "[ERROR] Size parameter can't be zero");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    double_list_s split = { 0 }; // create empty list to push list's split elements into

    size_t list_current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list->size; ++i) { // go to list element index at parameter index
        list_current = list->node[node_index][list_current];
    }

    size_t * split_current = &(split.head);
    for (; split.size < size; split.size++) {
        if (IS_CAPACITY_DOUBLE_LIST(split.size)) { // if split list reached capacity expand it
            const size_t expand = EXPAND_CAPACITY_DOUBLE_LIST(split.size);

            split.elements = DOUBLE_LIST_REALLOC(split.elements, expand * sizeof(DOUBLE_LIST_DATA_TYPE));
            DOUBLE_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");
            split.node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(split.node[DOUBLE_LIST_NEXT_INDEX], expand * sizeof(size_t));
            DOUBLE_LIST_ASSERT(split.node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] Memory allocation failed.");
            split.node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(split.node[DOUBLE_LIST_PREV_INDEX], expand * sizeof(size_t));
            DOUBLE_LIST_ASSERT(split.node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] Memory allocation failed.");
        }

        split.elements[split.size] = list->elements[list_current];
        (*split_current) = split.size; // set head and next nodes to next index
        split.node[DOUBLE_LIST_PREV_INDEX][split.size] = split.size - 1; // set previous node indexes to one minus current
        list->size--;

        // swap element and node indexes at current index with last in elements and nodes arrays
        list->elements[list_current] = list->elements[list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = list_current;
        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = list_current;

        if (IS_CAPACITY_DOUBLE_LIST(list->size)) { // if list reached bottom capacity shrink it to its size
            list->elements = DOUBLE_LIST_REALLOC(list->elements, list->size * sizeof(DOUBLE_LIST_DATA_TYPE));
            DOUBLE_LIST_ASSERT((!(list->size) || list->elements) && "[ERROR] Memory allocation failed.");
            list->node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_NEXT_INDEX], list->size * sizeof(size_t));
            DOUBLE_LIST_ASSERT((!(list->size) || list->node[DOUBLE_LIST_NEXT_INDEX]) && "[ERROR] Memory allocation failed.");
            list->node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(list->node[DOUBLE_LIST_PREV_INDEX], list->size * sizeof(size_t));
            DOUBLE_LIST_ASSERT((!(list->size) || list->node[DOUBLE_LIST_PREV_INDEX]) && "[ERROR] Memory allocation failed.");
        }

        list_current = list->node[DOUBLE_LIST_NEXT_INDEX][list_current]; // go to next list node
        split_current = split.node[DOUBLE_LIST_NEXT_INDEX] + split.size; // go to next split list node pointer
    }
    split.node[DOUBLE_LIST_PREV_INDEX][0] = size - 1; // to make list circular first index in previous must point to last element
    (*split_current) = 0; // make next index of last element in array 0 to make list circular

    if (!list->size) {
        DOUBLE_LIST_FREE(list->elements);
        DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_NEXT_INDEX]);
        DOUBLE_LIST_FREE(list->node[DOUBLE_LIST_PREV_INDEX]);

        list->elements = NULL;
        list->node[DOUBLE_LIST_NEXT_INDEX] = NULL;
        list->node[DOUBLE_LIST_PREV_INDEX] = NULL;
    }

    if (!index || (index > list->size)) {
        list->head = list_current;
    }

    return split;
}

/// @brief Checks if list is empty.
/// @param list List structure to check.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_double_list(const double_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure to check.
/// @return 'true' if list is full, 'false' otherwise.
/// @note Since the list is infinite the function checks if size will overflows.
static inline bool is_full_double_list(const double_list_s list) {
    return !(~list.size);
}

/// @brief Creates and returns a copy of the list with all elements based on copy function poniter.
/// @param list List structure to replicate.
/// @param copy Function pointer that returns a deep or shallow copy of an element.
/// @return Replicated list with all elements.
static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    DOUBLE_LIST_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");

    double_list_s replica = { .head = list.head, .size = 0 };
    for (; replica.size < list.size; replica.size++) {
        if (IS_CAPACITY_DOUBLE_LIST(replica.size)) { // if remlica size reached capacity expand it
            const size_t expand = EXPAND_CAPACITY_DOUBLE_LIST(replica.size);

            replica.elements = DOUBLE_LIST_REALLOC(replica.elements, expand * sizeof(DOUBLE_LIST_DATA_TYPE));
            DOUBLE_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");

            replica.node[DOUBLE_LIST_NEXT_INDEX] = DOUBLE_LIST_REALLOC(replica.node[DOUBLE_LIST_NEXT_INDEX], expand * sizeof(size_t));
            DOUBLE_LIST_ASSERT(replica.node[DOUBLE_LIST_NEXT_INDEX] && "[ERROR] Memory allocation failed.");

            replica.node[DOUBLE_LIST_PREV_INDEX] = DOUBLE_LIST_REALLOC(replica.node[DOUBLE_LIST_PREV_INDEX], expand * sizeof(size_t));
            DOUBLE_LIST_ASSERT(replica.node[DOUBLE_LIST_PREV_INDEX] && "[ERROR] Memory allocation failed.");
        }

        replica.elements[replica.size] = copy(list.elements[replica.size]);
        replica.node[DOUBLE_LIST_NEXT_INDEX][replica.size] = list.node[DOUBLE_LIST_NEXT_INDEX][replica.size];
        replica.node[DOUBLE_LIST_PREV_INDEX][replica.size] = list.node[DOUBLE_LIST_PREV_INDEX][replica.size];
    }

    return replica;
}

/// @brief Iterates over elements in list and operates on each of them based on arguments.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_double_list(double_list_s const * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size && operate(list->elements + current, args); ++i) {
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }
}

/// @brief Iterates over elements in list and operates on each of them based on arguments, but in reverse order.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_reverse_double_list(const double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[DOUBLE_LIST_PREV_INDEX][current]; // first go to previous node from current

        if (!operate(list->elements + current, args)) { // then operate on it
            return;
        }
    }
}

/// Maps list into array and manages it using list size and arguments.
/// @param list Pointer of list to map.
/// @param manage Function pointer to manage list as array using its size, and arguments.
/// @param args Generic arguments to use in manage function, or can be NULL.
static inline void map_double_list(double_list_s const * list, const manage_double_list_fn manage, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(manage && "[ERROR] 'manage' parameter pointer is NULL.");

    DOUBLE_LIST_DATA_TYPE * elements_array = DOUBLE_LIST_REALLOC(NULL, sizeof(DOUBLE_LIST_DATA_TYPE) * list->size);
    DOUBLE_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) { // copy elements in order into elements array
        elements_array[i] = list->elements[current];
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    manage(elements_array, list->size, args);

    for (size_t i = 0; i < list->size; ++i) { // copy elements back in order to list
        list->elements[current] = elements_array[i];
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    DOUBLE_LIST_FREE(elements_array);
}

#elif DOUBLE_LIST_MODE == FINITE_PREPROCESSOR_DOUBLE_LIST

#ifndef PREPROCESSOR_DOUBLE_LIST_SIZE

#define PREPROCESSOR_DOUBLE_LIST_SIZE (1 << 5)

#elif PREPROCESSOR_DOUBLE_LIST_SIZE == 0

#error 'PREPROCESSOR_DOUBLE_LIST_SIZE' cannot be zero

#endif

typedef struct list {
    size_t node[DOUBLE_LIST_NODE_COUNT][PREPROCESSOR_DOUBLE_LIST_SIZE];
    DOUBLE_LIST_DATA_TYPE elements[PREPROCESSOR_DOUBLE_LIST_SIZE];

    size_t size, head;
} double_list_s;

/// @brief Creates an empty list.
/// @return Empty list.
static inline double_list_s create_double_list(void) {
    return (double_list_s) { .size = 0, .head = 0, };
}

/// @brief Destroys a list and its elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
/// @note The list is unusable after destroying it, otherwise use the clear function or create a new list.
static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        destroy(&(list->elements[current]));
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    list->size = list->head = 0;
}

/// @brief Clears a list's elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
static inline void clear_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        destroy(&(list->elements[current]));
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    list->size = list->head = 0;
}

/// @brief Inserts element into list based on index number.
/// @param list Pointer of list to insert element into.
/// @param index Zero-based index to specify where to insert element.
/// @param element Element to insert into list at index.
static inline void insert_at_double_list(double_list_s * list, const size_t index, const DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size < PREPROCESSOR_DOUBLE_LIST_SIZE && "[ERROR] List reached maximum size.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[node_index][current];
    }

    list->node[DOUBLE_LIST_NEXT_INDEX][list->size] = current;
    list->node[DOUBLE_LIST_PREV_INDEX][list->size] = list->node[DOUBLE_LIST_PREV_INDEX][current];

    list->node[DOUBLE_LIST_PREV_INDEX][current]  = list->size;
    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->size;
    if (!index) {
        list->head = list->size;
    }

    memcpy(list->elements + list->size, &element, sizeof(DOUBLE_LIST_DATA_TYPE));
    list->size++;
}

/// Gets the element at specified index without changing the list.
/// @param list List structure to get element from.
/// @param index Zero-based index of element in list.
/// @return Element at index position.
static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s list, const size_t index) {
    DOUBLE_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    DOUBLE_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    const size_t real_index = index <= (list.size >> 1) ? index : list.size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list.size; ++i) {
        current = list.node[node_index][current];
    }

    return list.elements[current];
}

/// @brief Removes first instance of element in list.
/// @param list Pointer of list to remove first instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return First element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_first_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (0 != compare(list->elements[current], element)) {
            current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->node[DOUBLE_LIST_NEXT_INDEX][current] == list->size - 1) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
        }

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

        DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
        list->size--;

        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return removed;
    }

    DOUBLE_LIST_ASSERT(false && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes last instance of element in list by traversing backwards.
/// @param list Pointer of list to remove last instance of element from.
/// @param element Element to remove from list.
/// @param compare Compare function pointer to compare elements in list with parameter, 0 if equal.
/// @return Last element in list that is equal to parameter.
static inline DOUBLE_LIST_DATA_TYPE remove_last_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[DOUBLE_LIST_PREV_INDEX][current];

        if (0 != compare(list->elements[current], element)) {
            continue;
        }

        if (list->head == list->size - 1) {
            list->head = current;
        } else if (list->head == current) {
            list->head = (list->size - 1 == list->node[DOUBLE_LIST_NEXT_INDEX][current]) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
        }

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

        DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
        list->size--;

        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
        list->elements[current] = list->elements[list->size];

        return removed;
    }

    DOUBLE_LIST_ASSERT(false && "[ERROR] Element not found in double_list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index position in list.
/// @param list Pointer of list to remove element from.
/// @param index Zero-based index to remove element at.
/// @return Element in list at index.
static inline DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[node_index][current];
    }

    if (list->head == list->size - 1) {
        list->head = current;
    } else if (list->head == current) {
        list->head = (list->size - 1 == list->node[DOUBLE_LIST_NEXT_INDEX][current]) ? current : list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][current]] = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][current]] = list->node[DOUBLE_LIST_PREV_INDEX][current];

    DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
    list->size--;

    list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_NEXT_INDEX][list->size];
    list->node[DOUBLE_LIST_PREV_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][list->size];

    list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = current;
    list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = current;
    list->elements[current] = list->elements[list->size];

    return removed;
}

/// @brief Reverses list element ordering.
/// @param list Pointer of list to reverse.
static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        list->head = current;

        const size_t temp = list->node[DOUBLE_LIST_NEXT_INDEX][current];
        list->node[DOUBLE_LIST_NEXT_INDEX][current] = list->node[DOUBLE_LIST_PREV_INDEX][current];
        list->node[DOUBLE_LIST_PREV_INDEX][current] = temp;

        current = list->node[DOUBLE_LIST_PREV_INDEX][current];
    }
}

/// @brief Shifts list node by next n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_NEXT_INDEX][list->head];
    }
}

/// @brief Shifts list node by previous n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_PREV_INDEX][list->head];
    }
}

/// @brief Splices source list into destination list at specified index.
/// @param destination Pointer of list to splice into.
/// @param source Pointer of list to splice from.
/// @param index Zero-based index at destination list to start splicing.
static inline void splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");
    DOUBLE_LIST_ASSERT(destination->size + source->size <= PREPROCESSOR_DOUBLE_LIST_SIZE && "[ERROR] new list's size exceeds PREPROCESSOR_DOUBLE_LIST_SIZE");

    size_t current = destination->head;
    const size_t real_index = index <= (destination->size >> 1) ? index : destination->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < destination->size; ++i) {
        current = destination->node[node_index][current];
    }

    for (size_t i = 0; i < source->size; ++i) {
        destination->elements[destination->size + i] = source->elements[i];
        destination->node[DOUBLE_LIST_NEXT_INDEX][destination->size + i] = source->node[DOUBLE_LIST_NEXT_INDEX][i] + destination->size;
        destination->node[DOUBLE_LIST_PREV_INDEX][destination->size + i] = source->node[DOUBLE_LIST_PREV_INDEX][i] + destination->size;
    }

    if (destination->size && source->size) {
        const size_t first_destination = current;
        const size_t last_destination  = destination->node[DOUBLE_LIST_PREV_INDEX][current];

        const size_t first_source = source->head + destination->size;
        const size_t last_source  = source->node[DOUBLE_LIST_PREV_INDEX][source->head] + destination->size;

        destination->node[DOUBLE_LIST_NEXT_INDEX][last_destination] = first_source;
        destination->node[DOUBLE_LIST_PREV_INDEX][first_source] = last_destination;

        destination->node[DOUBLE_LIST_NEXT_INDEX][last_source] = first_destination;
        destination->node[DOUBLE_LIST_PREV_INDEX][first_destination] = last_source;
    }

    if (!index && source->size) { // if source isn't empty and inedx points to head node destination's make head to source's
        destination->head = source->head + destination->size;
    }

    destination->size += source->size;

    source->size = source->head = 0; // clear source, DON'T DESTROY IT
}

/// @brief Splits list at index and removes size parameter elements as new list.
/// @param list Pointer of list to split.
/// @param index Zero-based index at list to start splitting.
/// @param size Number of elements to split and return as new list.
/// @return Split list with size number of elements at index.
/// @note Since the list is circular the function can be used to split it as a circle at any index.
static inline double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size && "[ERROR] Size parameter can't be zero");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    size_t list_current = list->head;
    const size_t real_index = index < (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT_INDEX : DOUBLE_LIST_PREV_INDEX;
    for (size_t i = 0; i < real_index; ++i) {
        list_current = list->node[node_index][list_current];
    }

    double_list_s split = { .head = 0, .size = 0, };

    size_t * split_current = &(split.head);
    for (; split.size < list->size; split.size++) {
        split.elements[split.size] = list->elements[list_current];
        (*split_current) = split.size; // set head and next nodes to next index
        split.node[DOUBLE_LIST_PREV_INDEX][split.size] = split.size - 1; // set previous node indexes to one minus current
        list->size--;

        // swap element and node indexes at current index with last in elements and nodes arrays
        list->elements[list_current] = list->elements[list->size];
        list->node[DOUBLE_LIST_PREV_INDEX][list->node[DOUBLE_LIST_NEXT_INDEX][list->size]] = list_current;
        list->node[DOUBLE_LIST_NEXT_INDEX][list->node[DOUBLE_LIST_PREV_INDEX][list->size]] = list_current;

        list_current = list->node[DOUBLE_LIST_NEXT_INDEX][list_current]; // go to next list node
        split_current = split.node[DOUBLE_LIST_NEXT_INDEX] + split.size; // go to next split list node pointer
    }
    split.node[DOUBLE_LIST_PREV_INDEX][0] = size - 1; // to make list circular first index in previous must point to last element
    (*split_current) = 0;

    if (!index || (index > list->size)) {
        list->head = list_current;
    }

    return split;
}

/// @brief Checks if list is empty.
/// @param list List structure to check.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_double_list(const double_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure to check.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_double_list(const double_list_s list) {
    return (list.size == PREPROCESSOR_DOUBLE_LIST_SIZE);
}

/// @brief Creates and returns a copy of the list with all elements based on copy function poniter.
/// @param list List structure to replicate.
/// @param copy Function pointer that returns a deep or shallow copy of an element.
/// @return Replicated list with all elements.
static inline double_list_s copy_double_list(const double_list_s list, const copy_double_list_fn copy) {
    DOUBLE_LIST_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");

    double_list_s replica = { .head = list.head, .size = 0, };
    for (; replica.size < list.size; replica.size++) {
        replica.elements[replica.size] = copy(list.elements[replica.size]);
        replica.node[DOUBLE_LIST_NEXT_INDEX][replica.size] = list.node[DOUBLE_LIST_NEXT_INDEX][replica.size];
        replica.node[DOUBLE_LIST_PREV_INDEX][replica.size] = list.node[DOUBLE_LIST_PREV_INDEX][replica.size];
    }

    return replica;
}

/// @brief Iterates over elements in list and operates on each of them based on arguments.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size && operate(list->elements + current, args); ++i) {
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }
}

/// @brief Iterates over elements in list and operates on each of them based on arguments, but in reverse order.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_reverse_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[DOUBLE_LIST_PREV_INDEX][current];

        if (!operate(list->elements + current, args)) {
            return;
        }
    }
}

/// Maps list into array and manages it using list size and arguments.
/// @param list Pointer of list to map.
/// @param manage Function pointer to manage list as array using its size, and arguments.
/// @param args Generic arguments to use in manage function, or can be NULL.
static inline void map_double_list(double_list_s * list, const manage_double_list_fn manage, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    DOUBLE_LIST_ASSERT(manage && "[ERROR] 'manage' parameter pointer is NULL.");

    DOUBLE_LIST_DATA_TYPE elements_array[PREPROCESSOR_DOUBLE_LIST_SIZE];

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = list->elements[current];
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }

    manage(elements_array, list->size, args);

    for (size_t i = 0; i < list->size; ++i) {
        list->elements[current] = elements_array[i];
        current = list->node[DOUBLE_LIST_NEXT_INDEX][current];
    }
}

#endif

#else

#error Cannot include multiple headers in same unit.

#endif // DOUBLE_LIST_H
