#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

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

#define INFINITE_ALLOCATED_CIRCULAR_LIST  1100
#define FINITE_ALLOCATED_CIRCULAR_LIST    1101
#define INFINITE_REALLOC_CIRCULAR_LIST    1102
#define FINITE_PRERPOCESSOR_CIRCULAR_LIST 1103

#define INFINITE_CIRCULAR_LIST INFINITE_ALLOCATED_CIRCULAR_LIST
#define FINITE_CIRCULAR_LIST   FINITE_ALLOCATED_CIRCULAR_LIST

//#define CIRCULAR_LIST_MODE INFINITE_ALLOCATED_CIRCULAR_LIST
//#define CIRCULAR_LIST_MODE FINITE_ALLOCATED_CIRCULAR_LIST
//#define CIRCULAR_LIST_MODE INFINITE_REALLOC_CIRCULAR_LIST
//#define CIRCULAR_LIST_MODE FINITE_PRERPOCESSOR_CIRCULAR_LIST
// List mode that can be set to INFINITE_ALLOCATED_CIRCULAR_LIST, FINITE_ALLOCATED_CIRCULAR_LIST, INFINITE_REALLOC_CIRCULAR_LIST or
// FINITE_PRERPOCESSOR_CIRCULAR_LIST, or INFINITE_ALLOCATED_CIRCULAR_LIST or FINITE_ALLOCATED_CIRCULAR_LIST
// Default: INFINITE_ALLOCATED_CIRCULAR_LIST
#ifndef CIRCULAR_LIST_MODE

#define CIRCULAR_LIST_MODE INFINITE_ALLOCATED_CIRCULAR_LIST

#endif

// Check to make sure a valid list mode is selected.
#if (CIRCULAR_LIST_MODE != INFINITE_ALLOCATED_CIRCULAR_LIST) && (CIRCULAR_LIST_MODE != FINITE_ALLOCATED_CIRCULAR_LIST)    && \
(CIRCULAR_LIST_MODE != INFINITE_REALLOC_CIRCULAR_LIST)   && (CIRCULAR_LIST_MODE != FINITE_PRERPOCESSOR_CIRCULAR_LIST)

#error Invalid type of list mode.

#endif

#ifndef CIRCULAR_LIST_DATA_TYPE

/// @brief Element datatype macro that can be changed  via '#define CIRCULAR_LIST_DATA_TYPE [datatype]'.
#define CIRCULAR_LIST_DATA_TYPE void*

#endif

#ifndef CIRCULAR_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief Assertion macro that can be changed  via '#define CIRCULAR_LIST_ASSERT [assert]'.
#define CIRCULAR_LIST_ASSERT assert

#endif

#if CIRCULAR_LIST_MODE != FINITE_PRERPOCESSOR_CIRCULAR_LIST

#if !defined(CIRCULAR_LIST_REALLOC) && !defined(CIRCULAR_LIST_FREE)

#include <stdlib.h>

#ifndef CIRCULAR_LIST_REALLOC

#define CIRCULAR_LIST_REALLOC realloc

#endif

#ifndef CIRCULAR_LIST_FREE

#define CIRCULAR_LIST_FREE free

#endif

#elif !defined(CIRCULAR_LIST_REALLOC)

#error Reallocator macro is not defined!

#elif !defined(CIRCULAR_LIST_FREE)

#error Free macro is not defined!

#endif

#endif

/// @brief Function pointer to create a deep/shallow copy for forward list element.
typedef CIRCULAR_LIST_DATA_TYPE (*copy_circular_list_fn)    (const CIRCULAR_LIST_DATA_TYPE);
/// @brief Function pointer to destroy/free an element for forward list element.
typedef void                    (*destroy_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE *);
/// @brief Function pointer to comapre two forward list elements. Returns zero if they're equal, a negative number if
/// 'less than', else a positive number if 'more than'.
typedef int                     (*compare_circular_list_fn) (const CIRCULAR_LIST_DATA_TYPE, const CIRCULAR_LIST_DATA_TYPE);
/// @brief Function pointer to operate on a single forward list element based on generic arguments.
typedef bool                    (*operate_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of forward list elements based on generic arguments.
typedef void                    (*manage_circular_list_fn)  (CIRCULAR_LIST_DATA_TYPE *, const size_t, void *);

#if   CIRCULAR_LIST_MODE == INFINITE_ALLOCATED_CIRCULAR_LIST

/// @brief Forward list node with element and pointer to next node.
struct circular_list_node {
    CIRCULAR_LIST_DATA_TYPE element;  // current element
    struct circular_list_node * next; // pointer to next node
};

/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct circular_list {
    size_t size;                      // size of forward list
    struct circular_list_node * tail; // pointer to tail/last node
} circular_list_s;

/// @brief Creates an empty forward list of zero size.
/// @return Forward list structure.
static inline circular_list_s create_circular_list(void) {
    return (circular_list_s) { 0 }; // sets forward list to zero
}

/// @brief Destroys the list and all its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
/// @note The destroyed list should not be used after calling this function, else create a new list.
static inline void destroy_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    for (size_t i = 0; i < list->size; ++i) { // for each node based on size
        struct circular_list_node * next = list->tail->next; // save next node as temporary in loop

        destroy(&(list->tail->element)); // destroy element in list's tail
        CIRCULAR_LIST_FREE(list->tail); // free list tail

        list->tail = next; // set list tail to temporary saved next node
    }

    (*list) = (circular_list_s) { 0 }; // sets destroyed list to zero
}

/// @brief Clears the list and destroys its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
static inline void clear_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    for (size_t i = 0; i < list->size; ++i) { // for each node based on size
        struct circular_list_node * next = list->tail->next; // save next node as temporary in loop

        destroy(&(list->tail->element)); // destroy element in list's tail
        CIRCULAR_LIST_FREE(list->tail); // free list tail

        list->tail = next; // set list tail to temporary saved next node
    }

    (*list) = (circular_list_s) { 0 };
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list List structure.
/// @param copy Function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline circular_list_s copy_circular_list(const circular_list_s list, const copy_circular_list_fn copy) {
    CIRCULAR_LIST_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");

    circular_list_s replica = { .tail = NULL, .size = list.size };

    struct circular_list_node const * previous_list = list.tail;
    // double pointer since this also works on copying forward list
    struct circular_list_node ** previous_copy = &(replica.tail);
    for (size_t i = 0; i < list.size; ++i) {
        // create new node and copy element from source list based on copy function pointer parameter
        struct circular_list_node * node = CIRCULAR_LIST_REALLOC(NULL, sizeof(struct circular_list_node));
        CIRCULAR_LIST_ASSERT(node && "[ERROR] Memory allocation failed.");
        // if copy is specified call it, else just assign it to variable
        node->element = copy(previous_list->element);

        (*previous_copy) = node; // change previous copy's node pointer to node
        node->next = replica.tail; // make node's next pointer point to list copy's tail

        previous_list = previous_list->next; // go to next list node
        previous_copy = &((*previous_copy)->next); // go to next copy list's pointer to node
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list List structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_circular_list(const circular_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure.
/// @return 'true' if list is full, 'false' otherwise.
/// @note Since list is infinite the function checks if its size will overflow.
static inline bool is_full_circular_list(const circular_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero
    // and negating it makes function return true only if full
    return !(~list.size);
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_circular_list(circular_list_s * list, const size_t index, const CIRCULAR_LIST_DATA_TYPE element) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    CIRCULAR_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    // creates node and copies element parameter into the node element
    struct circular_list_node * node = CIRCULAR_LIST_REALLOC(NULL, sizeof(struct circular_list_node));
    CIRCULAR_LIST_ASSERT(node && "[ERROR] Memory allocation failed.");
    memcpy(&(node->element), &element, sizeof(CIRCULAR_LIST_DATA_TYPE));

    if (list->tail == NULL) {
        list->tail = node->next = node;
    } else if (index == list->size) {
        node->next = list->tail->next;
        list->tail = list->tail->next = node;
    } else {
        struct circular_list_node * previous = list->tail;
        for (size_t i = 0; i < index; ++i) {
            previous = previous->next; // go to next node from previous
        }
        node->next = previous->next;
        previous->next = node; // if previous is node then node becomes circular, else previous' netx pointer becomes node
    }
    list->size++;
}

/// @brief Gets element at index.
/// @param list List structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline CIRCULAR_LIST_DATA_TYPE get_circular_list(const circular_list_s list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list.tail && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct circular_list_node const * current = list.tail;
    // if index is last element then don't iterate and return tail node
    for (size_t i = 0; (index != list.size - 1) && (i <= index); ++i) {
        current = current->next;
    }

    return current->element;
}

/// @brief Removes first element in list based on element parameter comparison.
/// @param list Pointer to list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_first_circular_list(circular_list_s * list, const CIRCULAR_LIST_DATA_TYPE element, const compare_circular_list_fn compare) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");

    struct circular_list_node * previous = list->tail; // pointer to previous
    for (size_t s = 0; s < list->size; ++s) {
        // since we need to start at nodes next to tail we check current node instead of previous
        struct circular_list_node * current = previous->next;
        // compares element parameter to current node's element, if compare function not is specified (is NULL) then memcmp is used
        if (0 == compare(current->element, element)) { // if elements are the 'same' based on comparison, i. e. comparison is zero
            // copy removed element from node as temporary to return and not lose it
            CIRCULAR_LIST_DATA_TYPE removed = current->element;
            list->size--;

            if (current == list->tail) { // if current is the last element
                // if list has elements then tail becomes the previous pointer, else NULL
                list->tail = (list->size) ? previous : NULL;
            }
            // remove pointer to current in list by changing previous' next pointer to current's next
            previous->next = current->next;
            CIRCULAR_LIST_FREE(current);

            return removed; // returns first removed found element
        }
        previous = previous->next; // go to next previous node
    }

    CIRCULAR_LIST_ASSERT(false && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned, since the function returns the removed element, element can contain allocated memory
    exit(EXIT_FAILURE);
}

/// @brief Removes list element at index.
/// @param list Pointer to list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_at_circular_list(circular_list_s * list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct circular_list_node * previous = list->tail; // previous is used in order to make removals easier
    for (size_t i = 0; i < index; ++i) { // iterate until node previous to node at index is reached
        previous = previous->next;
    }
    struct circular_list_node * current = previous->next; // save current node pointer

    CIRCULAR_LIST_DATA_TYPE removed = current->element;
    list->size--;

    previous->next = current->next; // remove pointer to current in list by changing previous' next pointer to current's next

    CIRCULAR_LIST_FREE(current); // free current pointer

    if (index == list->size) { // if last element is removed
        list->tail = (list->size) ? previous : NULL; // if list is not empty tail/last node becomes previous, else NULL
    }

    return removed;
}

/// @brief Reverses list.
/// @param list Pointer to list structure.
static inline void reverse_circular_list(circular_list_s * list) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct circular_list_node * previous = list->tail;
    struct circular_list_node * current = list->size ? previous->next : NULL;
    struct circular_list_node * next = list->size ? previous->next->next : NULL;
    list->tail = current; // since head changes to tail, tail also changes to head
    for (size_t i = 0; i < list->size; ++i) {
        current->next = previous;
        previous = current;
        current = next;
        next = next->next;
    }
}

/// @brief Shifts list to next number of elements.
/// @param list Pointer to list structure.
/// @param shift Nonnegative integer to shift list by.
/// @note The list can shit zero or more than list's size times.
static inline void shift_circular_list(circular_list_s * list, const size_t shift) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't shift an empty list.");

    for (size_t s = 0; s < shift; ++s) {
        list->tail = list->tail->next; // changes tail to next/head node
    }
}

/// @brief Splices two lists together while clearing source list.
/// @param destination Pointer to list structure to splice into.
/// @param source Pointer to list structure to splice from.
/// @param index Index at destination list to splice source list into.
/// @note If source list is zero destination list does not change.
static inline void splice_circular_list(circular_list_s * restrict destination, circular_list_s * restrict source, const size_t index) {
    CIRCULAR_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    CIRCULAR_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    if (source->tail == NULL) { // if source is empty early return
        return;
    }

    struct circular_list_node * previous = destination->tail;
    // iterate to node previous to index node or not if index is to the node after last
    for (size_t i = 0; index != destination->size && i < index; ++i) {
        previous = previous->next;
    }

    if (previous) { // if previous is not NULL
        struct circular_list_node * swap = previous->next; // store previous' next node in swap
        previous->next = source->tail->next; // change previous' next pointer to source's head
        source->tail->next = swap; // change source tail's next pointer to swap or saved previous' next node
    }
    // if index points to location after last destination node (concatenation)
    if (index == destination->size) {
        destination->tail = source->tail;
    }
    destination->size += source->size; // increment destination's size by source

    (*source) = (circular_list_s) { 0 }; // clear only source list (since nodes and elements became part of destionation)
}

/// @brief Splits list and returns new list with elements in range.
/// @param list Pointer to list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by.
/// @return New split list.
/// @note Since forward list is circular the new list can include elements beyond old list's last node.
static inline circular_list_s split_circular_list(circular_list_s * list, const size_t index, const size_t size) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(size && "[ERROR] 'size' parameter can't be zero.");

    CIRCULAR_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");

    struct circular_list_node * list_previous = list->tail;
    for (size_t i = 0; i < index; ++i) { // iterate to node previous to node at index
        list_previous = list_previous->next;
    }
    // if tail node becomes part of split list new tail node will be the node previous to index node
    if ((index + size) >= list->size) {
        list->tail = (size != list->size) ? list_previous : NULL; // if list becomes empty set tail to NULL
    }

    circular_list_s split = { .size = 0, .tail = NULL }; // create new split list to return
    struct circular_list_node * last = NULL;
    for (struct circular_list_node ** split_previous = &(split.tail); split.size < size; split.size++) {
        struct circular_list_node * current = list_previous->next;
        list_previous->next = list_previous->next->next; // remove previous' next and go to next node

        (*split_previous) = last = current; // set split's current and tail node to list previous' next
        (*split_previous)->next = split.tail; // set split's next node to tail

        split_previous = &((*split_previous)->next); // go to pointer to next node
    }
    split.tail = last;
    list->size -= size; // shorten parameter list by split size

    return split;
}

/// @brief Iterates through each list element.
/// @param list Pointer to list structure.
/// @param operate Function pointer to operate on every single element pointer using arguments.
/// @param args Generic arguments for 'operate' function pointer.
static inline void foreach_circular_list(circular_list_s const * list, const operate_circular_list_fn operate, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct circular_list_node const * previous = list->tail;
    for (size_t i = 0; i < list->size && operate(&previous->next->element, args); ++i) {
        previous = previous->next; // go to next node
    }
}

/// @brief Map function that maps elements into array, manages it using size and args, and maps it back.
/// @param list Pointer to list structure.
/// @param manage Function pointer to manage the array of elements based on element size and specified args.
/// @param args Void pointer arguments for 'manage' function.
static inline void map_circular_list(circular_list_s const * list, const manage_circular_list_fn manage, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(manage && "[ERROR] 'manage' pointer parameter pointer is NULL.");

    // create continuos array to store lis elements
    CIRCULAR_LIST_DATA_TYPE * elements_array = CIRCULAR_LIST_REALLOC(NULL, sizeof(CIRCULAR_LIST_DATA_TYPE) * list->size);
    CIRCULAR_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct circular_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next; // go to next node to add elements from head instead of from tail
        elements_array[i] = previous->element;
    }
    // manage function that takes an array as argument, its size and argument void pointer
    manage(elements_array, list->size, args);

    // previous = list->tail; // pointles since previous will return as tail
    for (size_t i = 0; i < list->size; ++i) { // loop to re-add new list element's ordering
        previous = previous->next;
        previous->element = elements_array[i];
    }

    CIRCULAR_LIST_FREE(elements_array); // free elements array
}

#elif CIRCULAR_LIST_MODE == FINITE_ALLOCATED_CIRCULAR_LIST

/// @note The FINITE_ALLOCATED_CIRCULAR_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the circular_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct circular_list {
    CIRCULAR_LIST_DATA_TYPE * elements;
    size_t tail;
    size_t * next;
    size_t size, max;
    size_t empty_size, empty_head;
} circular_list_s;

/// @brief Creates an empty forward list of zero size.
/// @param max Maximum positive nonzero size of forward list.
/// @return Forward list structure.
static inline circular_list_s create_circular_list(const size_t max) {
    CIRCULAR_LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const circular_list_s list = { // allocated memory and initialize everything else to zero
        .elements = CIRCULAR_LIST_REALLOC(NULL, sizeof(CIRCULAR_LIST_DATA_TYPE) * max),
        .next     = CIRCULAR_LIST_REALLOC(NULL, sizeof(size_t) * max),
        .tail = 0, .max = max, .size = 0, .empty_head = 0, .empty_size = 0,
    };

    // check if memory allocation failed
    CIRCULAR_LIST_ASSERT(list.elements && "[ERROR] Memory allocation failed.");
    CIRCULAR_LIST_ASSERT(list.next && "[ERROR] Memory allocation failed.");

    return list;
}

/// @brief Destroys the list and all its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
/// @note The destroyed list should not be used after calling this function, else create a new list.
static inline void destroy_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    size_t previous = list->tail; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    CIRCULAR_LIST_FREE(list->elements); // free elements array
    CIRCULAR_LIST_FREE(list->next); // free next index array
    (*list) = (circular_list_s) { 0 }; // set everything to zero
}

/// @brief Clears the list and destroys its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
static inline void clear_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    list->empty_size = list->size = list->tail = 0;
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list List structure.
/// @param copy Function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline circular_list_s copy_circular_list(const circular_list_s list, const copy_circular_list_fn copy) {
    CIRCULAR_LIST_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    CIRCULAR_LIST_ASSERT(list.elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list.size <= list.max && "[ERROR] Maximum size can't be greater than size.");

    circular_list_s replica = {
        .elements = CIRCULAR_LIST_REALLOC(NULL, list.max * sizeof(CIRCULAR_LIST_DATA_TYPE)), .empty_head = 0, .empty_size = 0,
        .next     = CIRCULAR_LIST_REALLOC(NULL, list.max * sizeof(size_t)), .max = list.max, .size = 0, .tail = 0,
    };
    CIRCULAR_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    CIRCULAR_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");

    size_t previous = list.tail;
    for (size_t * current_replica = &(replica.tail); replica.size < list.size; replica.size++) {
        (*current_replica) = replica.size;

        replica.elements[replica.size] = copy(list.elements[previous]);

        previous = list.next[previous];
        current_replica = replica.next + replica.size;
        (*current_replica) = 0;
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list List structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_circular_list(const circular_list_s list) {
    CIRCULAR_LIST_ASSERT(list.elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list.size <= list.max && "[ERROR] Maximum size can't be greater than size.");

    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_circular_list(const circular_list_s list) {
    CIRCULAR_LIST_ASSERT(list.elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list.size <= list.max && "[ERROR] Maximum size can't be greater than size.");

    return (list.size == list.max); // if size is equal to maximum size return true, else false
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_circular_list(circular_list_s * list, const size_t index, const CIRCULAR_LIST_DATA_TYPE element) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size < list->max && "[ERROR] List reached maximum size.");
    CIRCULAR_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    size_t previous = list->tail; // save previous pointer
    for (size_t i = 0; (index != list->size) && i < index; ++i) { // iterate until previous isn't the node previous to index node
        previous = list->next[previous];
    }

    size_t free_slot = list->size;
    if (list->empty_size) { // if 'empty stack' isn't empty pop empty slot index from it
        free_slot = list->empty_head; // change empty slot to empty stack's head index
        list->empty_head = list->next[list->empty_head]; // move new empty stack index to head
        list->empty_size--; // decrement empty stack's size
    }

    size_t * current = list->next + previous;
    memcpy(list->elements + free_slot, &element, sizeof(CIRCULAR_LIST_DATA_TYPE));
    list->next[free_slot] = (*current);
    (*current) = free_slot;

    if (index == list->size) { // if index is at last/tail element tail must point to last added element
        list->tail = free_slot;
    }

    list->size++;
}

/// @brief Gets element at index.
/// @param list List structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline CIRCULAR_LIST_DATA_TYPE get_circular_list(const circular_list_s list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    CIRCULAR_LIST_ASSERT(list.elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list.max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list.size <= list.max && "[ERROR] Maximum size can't be greater than size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Removes first element in list based on element parameter comparison.
/// @param list Pointer to list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_first_circular_list(circular_list_s * list, const CIRCULAR_LIST_DATA_TYPE element, const compare_circular_list_fn compare) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t current = list->next[previous];

        if (0 != compare(list->elements[current], element)) { // early continue in order to remove one needless nesting level
            previous = current;
            continue;
        }

        // decrement size and save found element to return
        CIRCULAR_LIST_DATA_TYPE found = list->elements[current];
        list->size--;

        list->next[previous] = list->next[current];

        if (!list->size) { // set empty stack size to zero
            list->empty_size = 0;
        } else if (current != list->size) { // push empty index to 'empty stack'
            list->next[current] = list->empty_head;
            list->empty_head = current;
            list->empty_size++;
        }

        if (current == list->tail) { // if current is the last element
            list->tail = previous; // if list still has elements then tail will become the previous index
        }

        return found;
    }

    CIRCULAR_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes list element at index.
/// @param list Pointer to list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_at_circular_list(circular_list_s * list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    const size_t current = list->next[previous];

    CIRCULAR_LIST_DATA_TYPE found = list->elements[current];
    list->size--;

    list->next[previous] = list->next[current];

    if (!list->size) {
        list->empty_size = 0;
    } else if (current != list->size) {
        // push empty index to 'empty stack'
        list->next[current] = list->empty_head;
        list->empty_head = current;
        list->empty_size++;
    }

    if (index == list->size) { // if last element is removed
        list->tail = previous; // if list still has elements then tail will become the previous index
    }

    return found;
}

/// @brief Reverses list.
/// @param list Pointer to list structure.
static inline void reverse_circular_list(circular_list_s * list) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    size_t previous = list->tail;
    size_t current  = list->size ? list->next[previous] : 0;
    size_t next     = list->size ? list->next[current] : 0;
    list->tail = current;
    for (size_t i = 0; i < list->size; ++i) {
        list->next[current] = previous;
        previous = current;
        current = next;
        next = list->next[next];
    }
}

/// @brief Shifts list to next number of elements.
/// @param list Pointer to list structure.
/// @param shift Nonnegative integer to shift list by.
/// @note The list can shit zero or more than list's size times.
static inline void shift_circular_list(circular_list_s * list, const size_t shift) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't shift an empty list.");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    for (size_t s = 0; s < shift; ++s) {
        list->tail = list->next[list->tail];
    }
}

/// @brief Splices two lists together while clearing source list.
/// @param destination Pointer to list structure to splice into.
/// @param source Pointer to list structure to splice from.
/// @param index Index at destination list to splice source list into.
/// @param max New maximum size of destination list.
/// @note If source list is zero destination list does not change.
static inline void splice_circular_list(circular_list_s * restrict destination, circular_list_s * restrict source, const size_t index, const size_t max) {
    CIRCULAR_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    CIRCULAR_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    CIRCULAR_LIST_ASSERT(destination->size + source->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    CIRCULAR_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    CIRCULAR_LIST_ASSERT(destination->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(destination->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(destination->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(destination->size <= destination->max && "[ERROR] Maximum size can't be greater than size.");

    CIRCULAR_LIST_ASSERT(source->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(source->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(source->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(source->size <= source->max && "[ERROR] Maximum size can't be greater than size.");

    destination->elements = CIRCULAR_LIST_REALLOC(destination->elements, sizeof(CIRCULAR_LIST_DATA_TYPE) * max);
    CIRCULAR_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed.");
    destination->next = CIRCULAR_LIST_REALLOC(destination->next, sizeof(size_t) * max);
    CIRCULAR_LIST_ASSERT(destination->next && "[ERROR] Memory allocation failed.");

    size_t previous_destination = destination->tail, previous_source = source->tail;
    // if index doesn't point to end and until index node is reached
    for (size_t i = 0; index != destination->size && i < index; ++i) {
        previous_destination = destination->next[previous_destination];
    }
    // fill empty stack indexes until empty stack is empty or source list is empty
    for (size_t source_size = source->size; source_size && destination->empty_size; source_size--, destination->size++) {
        const size_t current_source = source->next[previous_source];

        const size_t empty_pop = destination->empty_head; // pop empty stack's head
        destination->empty_head = destination->next[destination->empty_head]; // shift empty stack's head to next index
        destination->empty_size--; // decrement empty stack's size

        destination->elements[empty_pop] = source->elements[current_source];
        destination->next[empty_pop] = destination->next[previous_destination];
        destination->next[previous_destination] = empty_pop;

        previous_destination = destination->next[previous_destination];
        previous_source = current_source;
    }
    // fill destination until source list is empty
    for (size_t source_size = source->size; source_size; source_size--, destination->size++) {
        const size_t current_source = source->next[previous_source];

        destination->elements[destination->size] = source->elements[current_source];

        destination->next[destination->size] = destination->next[previous_destination];
        destination->next[previous_destination] = destination->size;

        previous_destination = destination->next[previous_destination];
        previous_source = current_source;
    }

    if (index == destination->size - source->size) { // if index splices from end then tail must change
        destination->tail = previous_destination;
    }

    // set source list's unallocated parameters to zero
    source->empty_size = source->size = source->tail = 0;
}

/// @brief Splits old list and returns new list with specified elements. Since forward list is circular the new list can
/// include elements beyond old list's last node.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @param max Maximum positive nonzero size of returned split list.
/// @return New split list.
/// @note Splitting the list also removes its 'empty stack' holes.
static inline circular_list_s split_circular_list(circular_list_s * list, const size_t index, const size_t size, const size_t max) {
    CIRCULAR_LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    CIRCULAR_LIST_ASSERT(size && "[ERROR] 'size' parameter can't be zero.");
    CIRCULAR_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    circular_list_s split = {
        .elements = CIRCULAR_LIST_REALLOC(NULL, max * sizeof(CIRCULAR_LIST_DATA_TYPE)),
        .next     = CIRCULAR_LIST_REALLOC(NULL, max * sizeof(size_t)),
        .empty_head = 0, .max = max, .empty_size = 0, .size = 0, .tail = size - 1,
    };
    CIRCULAR_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");
    CIRCULAR_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed.");

    circular_list_s replica = { // create replika to copy non-split elements from list and also remove holes from list
        .elements = CIRCULAR_LIST_REALLOC(NULL, list->max * sizeof(CIRCULAR_LIST_DATA_TYPE)),
        .next     = CIRCULAR_LIST_REALLOC(NULL, list->max * sizeof(size_t)),
        .empty_head = 0, .max = list->max, .empty_size = 0, .size = 0, .tail = 0,
    };
    CIRCULAR_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    CIRCULAR_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");

    size_t previous_list = list->tail;

    size_t * replica_previous = &(replica.tail);
    for (; replica.size < index; replica.size++) { // copy elements to replica until index
        const size_t current_list = list->next[previous_list];

        replica.elements[replica.size] = list->elements[current_list];
        replica.tail = (*replica_previous) = replica.size;

        previous_list = current_list;
        replica_previous = replica.next + replica.size;
        (*replica_previous) = 0; // set last element's next index to 0 to make list circular
    }

    for (size_t * split_previous = &(split.tail); split.size < size; split.size++) { // copy elements to split until size
        const size_t current_list = list->next[previous_list];

        split.elements[split.size] = list->elements[current_list];
        split.tail = (*split_previous) = split.size;

        previous_list = current_list;
        split_previous = split.next + split.size;
        (*split_previous) = 0; // set last element's next index to 0 to make list circular
    }

    for (; split.size + replica.size < list->size; replica.size++) { // copy elements until replica plus split isn't list size
        const size_t current_list = list->next[previous_list];

        replica.elements[replica.size] = list->elements[current_list];
        replica.tail = (*replica_previous) = replica.size;

        previous_list = current_list;
        replica_previous = replica.next + replica.size;
        (*replica_previous) = 0; // set last element's next index to 0 to make list circular
    }

    if (size != list->size) {
        CIRCULAR_LIST_FREE(list->elements);
        CIRCULAR_LIST_FREE(list->next);
        (*list) = replica;
    } else {
        CIRCULAR_LIST_FREE(replica.elements);
        CIRCULAR_LIST_FREE(replica.next);
        list->empty_size = list->tail = list->size = 0;
    }

    return split;
}

/// @brief Iterates through each list element.
/// @param list Pointer to list structure.
/// @param operate Function pointer to operate on every single element pointer using arguments.
/// @param args Generic arguments for 'operate' function pointer.
static inline void foreach_circular_list(circular_list_s const * list, const operate_circular_list_fn operate, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size && operate(list->elements + list->next[previous], args); ++i) {
        previous = list->next[previous];
    }
}

/// @brief Map function that maps elements into array, manages it using size and args, and maps it back.
/// @param list Pointer to list structure.
/// @param manage Function pointer to manage the array of elements based on element size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note The map function can also be used to remove holes in list.
static inline void map_circular_list(circular_list_s * list, const manage_circular_list_fn manage, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(manage && "[ERROR] 'manage' pointer parameter pointer is NULL.");

    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] List's element array is NULL.");
    CIRCULAR_LIST_ASSERT(list->max && "[ERROR] Maximum size can't be zero");
    CIRCULAR_LIST_ASSERT(list->size <= list->max && "[ERROR] Maximum size can't be greater than size.");

    // create temporary array to store list elements
    CIRCULAR_LIST_DATA_TYPE * elements_array = CIRCULAR_LIST_REALLOC(NULL, list->size * sizeof(CIRCULAR_LIST_DATA_TYPE));
    CIRCULAR_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = list->next[previous];
        elements_array[i] = list->elements[previous];
    }

    manage(elements_array, list->size, args);

    list->empty_size = list->tail = 0; // set empty stack size and list tail index to zero
    for (size_t * list_current = &(list->tail), i = 0; i < list->size; ++i) {
        list->elements[i] = elements_array[i];
        list->tail = (*list_current) = i;
        list_current = list->next + i;
    }

    CIRCULAR_LIST_FREE(elements_array);
}

#elif CIRCULAR_LIST_MODE == INFINITE_REALLOC_CIRCULAR_LIST

#if !defined(IS_CAPACITY_CIRCULAR_LIST) && !defined(EXPAND_CAPACITY_CIRCULAR_LIST)

#ifndef REALLOC_CIRCULAR_LIST_CHUNK

#define REALLOC_CIRCULAR_LIST_CHUNK (1 << 5)

#elif REALLOC_CIRCULAR_LIST_CHUNK <= 0

#error 'REALLOC_CIRCULAR_LIST_CHUNK' cannot be less than or equal to 0

#endif

/// @brief Checks if stack's 'size' has reached capacity.
#define IS_CAPACITY_CIRCULAR_LIST(size) (!((size) % REALLOC_CIRCULAR_LIST_CHUNK))

/// @brief Calculates next stack's capacity based on 'size'.
#define EXPAND_CAPACITY_CIRCULAR_LIST(capacity) ((capacity) + REALLOC_CIRCULAR_LIST_CHUNK)

#elif !defined(IS_CAPACITY_CIRCULAR_LIST)

#error Stack capacity reached check is not defined.

#elif !defined(EXPAND_CAPACITY_CIRCULAR_LIST)

#error Stack capacity expanded size is not defined.

#endif

/// @note The INFINITE_REALLOC_CIRCULAR_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the circular_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct circular_list {
    CIRCULAR_LIST_DATA_TYPE * elements;
    size_t * next, tail;
    size_t empty_size, empty_head;
    size_t size;
} circular_list_s;

/// @brief Creates an empty forward list of zero size.
/// @return Forward list structure.
static inline circular_list_s create_circular_list(void) {
    return (circular_list_s) { 0 };
}

/// @brief Destroys the list and all its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
/// @note The destroyed list should not be used after calling this function, else create a new list.
static inline void destroy_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    CIRCULAR_LIST_FREE(list->elements);
    CIRCULAR_LIST_FREE(list->next);
    (*list) = (circular_list_s) { 0 };
}

/// @brief Clears the list and destroys its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
static inline void clear_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    CIRCULAR_LIST_FREE(list->elements);
    CIRCULAR_LIST_FREE(list->next);
    *list = (circular_list_s) { 0 };
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list List structure.
/// @param copy Function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline circular_list_s copy_circular_list(const circular_list_s list, const copy_circular_list_fn copy) {
    CIRCULAR_LIST_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    circular_list_s replica = { 0 };
    size_t previous = list.tail;
    for (size_t * current_replica = &(replica.tail); replica.size < list.size; replica.size++) {
        (*current_replica) = replica.size;

        if (IS_CAPACITY_CIRCULAR_LIST(replica.size)) {
            const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(replica.size);

            replica.elements = CIRCULAR_LIST_REALLOC(replica.elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
            CIRCULAR_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");

            replica.next = CIRCULAR_LIST_REALLOC(replica.next, expand * sizeof(size_t));
            CIRCULAR_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");
        }
        replica.elements[replica.size] = copy(list.elements[previous]);

        previous = list.next[previous];
        current_replica = replica.next + replica.size;
        (*current_replica) = 0;
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list List structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_circular_list(const circular_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure.
/// @return 'true' if list is full, 'false' otherwise.
/// @note Since list is infinite the function checks if its size will overflow.
static inline bool is_full_circular_list(const circular_list_s list) {
    return !(~list.size);
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_circular_list(circular_list_s * list, const size_t index, const CIRCULAR_LIST_DATA_TYPE element) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    CIRCULAR_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    size_t previous = list->tail; // save previous pointer
    for (size_t i = 0; (index != list->size) && i < index; ++i) { // iterate until previous isn't the node previous to index node
        previous = list->next[previous];
    }

    size_t free_slot = list->size;
    if (list->empty_size) { // if 'empty stack' isn't empty pop empty slot index from it
        free_slot = list->empty_head; // change empty slot to empty stack's head index
        list->empty_head = list->next[list->empty_head]; // move new empty stack index to head
        list->empty_size--; // decrement empty stack's size
    } else if (IS_CAPACITY_CIRCULAR_LIST(list->size)) { // if list has reached capacity epxand elements and next arrays
        const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(list->size);
        list->elements = CIRCULAR_LIST_REALLOC(list->elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
        CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] Memory allocation failed.");

        list->next = CIRCULAR_LIST_REALLOC(list->next, expand * sizeof(size_t));
        CIRCULAR_LIST_ASSERT(list->next && "[ERROR] Memory allocation failed.");
    }

    size_t * current = list->next + previous;
    memcpy(list->elements + free_slot, &element, sizeof(CIRCULAR_LIST_DATA_TYPE));
    list->next[free_slot] = (*current);
    (*current) = free_slot;

    if (index == list->size) { // if index is at last/tail element tail must point to last added element
        list->tail = free_slot;
    }

    list->size++;
}

/// @brief Gets element at index.
/// @param list List structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline CIRCULAR_LIST_DATA_TYPE get_circular_list(const circular_list_s list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list.elements && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(list.next && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) { // equal to index to take tail into account
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Removes first element in list based on element parameter comparison.
/// @param list Pointer to list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_first_circular_list(circular_list_s * list, const CIRCULAR_LIST_DATA_TYPE element, const compare_circular_list_fn compare) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t current = list->next[previous];

        if (0 != compare(list->elements[current], element)) { // early continue in order to remove one needless nesting level
            previous = current;
            continue;
        }

        // decrement size and save found element to return
        CIRCULAR_LIST_DATA_TYPE found = list->elements[current];
        list->size--;

        list->next[previous] = list->next[current];

        if (!list->size) { // set empty stack size to zero
            list->empty_size = 0;
        } else if (current != list->size) { // push empty index to 'empty stack'
            list->next[current] = list->empty_head;
            list->empty_head = current;
            list->empty_size++;
        }

        if (current == list->tail) { // if current is the last element
            list->tail = previous; // if list still has elements then tail will become the previous index
        }

        if (!(IS_CAPACITY_CIRCULAR_LIST(list->size))) {
            return found;
        }

        previous = list->tail;
        circular_list_s replica = { 0 }; // create temporary replica of list
        for (size_t * replica_current = &(replica.tail); replica.size < list->size; replica.size++) {
            (*replica_current) = replica.size;

            if ((IS_CAPACITY_CIRCULAR_LIST(replica.size))) {
                const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(list->size);
                replica.elements = CIRCULAR_LIST_REALLOC(replica.elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
                CIRCULAR_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");

                replica.next = CIRCULAR_LIST_REALLOC(replica.next, expand * sizeof(size_t));
                CIRCULAR_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");
            }

            replica.elements[replica.size] = list->elements[previous];

            replica_current = replica.next + replica.size;
            (*replica_current) = 0;
            previous = list->next[previous];
        }

        CIRCULAR_LIST_FREE(list->elements);
        CIRCULAR_LIST_FREE(list->next);
        (*list) = replica;

        return found;
    }

    CIRCULAR_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes list element at index.
/// @param list Pointer to list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_at_circular_list(circular_list_s * list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    const size_t current = list->next[previous];

    CIRCULAR_LIST_DATA_TYPE found = list->elements[current];
    list->size--;

    list->next[previous] = list->next[current];

    if (!list->size) {
        list->empty_size = 0;
    } else if (current != list->size) {
        // push empty index to 'empty stack'
        list->next[current] = list->empty_head;
        list->empty_head = current;
        list->empty_size++;
    }

    if (index == list->size) { // if last element is removed
        list->tail = previous; // if list still has elements then tail will become the previous index
    }

    if (!(IS_CAPACITY_CIRCULAR_LIST(list->size))) { // if capacity wan not reached return found, else shrink list
        return found;
    }

    previous = list->tail;
    circular_list_s replica = { 0 }; // create temporary replica of list to shrink and remove holes from list
    for (size_t * replica_current = &(replica.tail); replica.size < list->size; replica.size++) {
        (*replica_current) = replica.size;

        if ((IS_CAPACITY_CIRCULAR_LIST(replica.size))) {
            const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(list->size);
            replica.elements = CIRCULAR_LIST_REALLOC(replica.elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
            CIRCULAR_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");

            replica.next = CIRCULAR_LIST_REALLOC(replica.next, expand * sizeof(size_t));
            CIRCULAR_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");
        }

        replica.elements[replica.size] = list->elements[previous];

        replica_current = replica.next + replica.size;
        (*replica_current) = 0;
        previous = list->next[previous];
    }

    CIRCULAR_LIST_FREE(list->elements);
    CIRCULAR_LIST_FREE(list->next);
    (*list) = replica;

    return found;
}

/// @brief Reverses list.
/// @param list Pointer to list structure.
static inline void reverse_circular_list(circular_list_s * list) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    size_t current  = list->size ? list->next[previous] : 0;
    size_t next     = list->size ? list->next[current] : 0;
    list->tail = current;
    for (size_t i = 0; i < list->size; ++i) {
        list->next[current] = previous;
        previous = current;
        current = next;
        next = list->next[next];
    }
}

/// @brief Shifts list to next number of elements.
/// @param list Pointer to list structure.
/// @param shift Nonnegative integer to shift list by.
/// @note The list can shit zero or more than list's size times.
static inline void shift_circular_list(circular_list_s * list, const size_t shift) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't shift an empty list.");

    for (size_t s = 0; s < shift; ++s) {
        list->tail = list->next[list->tail];
    }
}

/// @brief Splices two lists together while clearing source list.
/// @param destination Pointer to list structure to splice into.
/// @param source Pointer to list structure to splice from.
/// @param index Index at destination list to splice source list into.
/// @note If source list is zero destination list does not change.
static inline void splice_circular_list(circular_list_s * restrict destination, circular_list_s * restrict source, const size_t index) {
    CIRCULAR_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    CIRCULAR_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    size_t previous_destination = destination->tail, previous_source = source->tail;
    // if index doesn't point to end and until index node is reached
    for (size_t i = 0; index != destination->size && i < index; ++i) {
        previous_destination = destination->next[previous_destination];
    }
    // fill empty stack indexes until empty stack is empty or source list is empty
    for (size_t source_size = source->size; source_size && destination->empty_size; source_size--, destination->size++) {
        const size_t current_source = source->next[previous_source];

        const size_t empty_pop = destination->empty_head; // pop empty stack's head
        destination->empty_head = destination->next[destination->empty_head]; // shift empty stack's head to next index
        destination->empty_size--; // decrement empty stack's size

        destination->elements[empty_pop] = source->elements[current_source];
        destination->next[empty_pop] = destination->next[previous_destination];
        destination->next[previous_destination] = empty_pop;

        previous_destination = destination->next[previous_destination];
        previous_source = current_source;
    }
    // fill destination or source list is empty
    for (size_t source_size = source->size; source_size; source_size--, destination->size++) {
        if ((IS_CAPACITY_CIRCULAR_LIST(destination->size))) {
            const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(destination->size);

            destination->elements = CIRCULAR_LIST_REALLOC(destination->elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
            CIRCULAR_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed.");

            destination->next = CIRCULAR_LIST_REALLOC(destination->next, expand * sizeof(size_t));
            CIRCULAR_LIST_ASSERT(destination->next && "[ERROR] Memory allocation failed.");
        }

        const size_t current_source = source->next[previous_source];

        destination->elements[destination->size] = source->elements[current_source];

        destination->next[destination->size] = destination->next[previous_destination];
        destination->next[previous_destination] = destination->size;

        previous_destination = destination->next[previous_destination];
        previous_source = current_source;
    }

    if (index == destination->size - source->size) { // if index splices from end then tail must change
        destination->tail = previous_destination;
    }

    CIRCULAR_LIST_FREE(source->elements);
    CIRCULAR_LIST_FREE(source->next);
    (*source) = (circular_list_s) { 0 };
}

/// @brief Splits old list and returns new list with specified elements. Since forward list is circular the new list can
/// include elements beyond old list's last node.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline circular_list_s split_circular_list(circular_list_s * list, const size_t index, const size_t size) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    CIRCULAR_LIST_ASSERT(size && "[ERROR] 'size' parameter can't be zero.");
    CIRCULAR_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");

    size_t previous_list = list->tail;

    circular_list_s replica = { 0 }, split = { 0 };
    size_t * replica_previous = &(replica.tail);
    for (; replica.size < index; replica.size++) { // copy elements to replica until index
        const size_t current_list = list->next[previous_list];

        if ((IS_CAPACITY_CIRCULAR_LIST(replica.size))) {
            const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(replica.size);

            replica.elements = CIRCULAR_LIST_REALLOC(replica.elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
            CIRCULAR_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");

            replica.next = CIRCULAR_LIST_REALLOC(replica.next, expand * sizeof(size_t));
            CIRCULAR_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");
        }

        replica.elements[replica.size] = list->elements[current_list];
        replica.tail = (*replica_previous) = replica.size;

        previous_list = current_list;
        replica_previous = replica.next + replica.size;
        (*replica_previous) = 0; // set last element's next index to 0 to make list circular
    }

    for (size_t * split_previous = &(split.tail); split.size < size; split.size++) { // copy elements to split until size
        const size_t current_list = list->next[previous_list];

        if ((IS_CAPACITY_CIRCULAR_LIST(split.size))) {
            const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(split.size);

            split.elements = CIRCULAR_LIST_REALLOC(split.elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
            CIRCULAR_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");

            split.next = CIRCULAR_LIST_REALLOC(split.next, expand * sizeof(size_t));
            CIRCULAR_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed.");
        }

        split.elements[split.size] = list->elements[current_list];
        split.tail = (*split_previous) = split.size;

        previous_list = current_list;
        split_previous = split.next + split.size;
        (*split_previous) = 0; // set last element's next index to 0 to make list circular
    }

    for (; split.size + replica.size < list->size; replica.size++) { // copy elements until replica plus split isn't list size
        const size_t current_list = list->next[previous_list];

        if ((IS_CAPACITY_CIRCULAR_LIST(replica.size))) {
            const size_t expand = EXPAND_CAPACITY_CIRCULAR_LIST(replica.size);

            replica.elements = CIRCULAR_LIST_REALLOC(replica.elements, expand * sizeof(CIRCULAR_LIST_DATA_TYPE));
            CIRCULAR_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");

            replica.next = CIRCULAR_LIST_REALLOC(replica.next, expand * sizeof(size_t));
            CIRCULAR_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");
        }

        replica.elements[replica.size] = list->elements[current_list];
        replica.tail = (*replica_previous) = replica.size;

        previous_list = current_list;
        replica_previous = replica.next + replica.size;
        (*replica_previous) = 0; // set last element's next index to 0 to make list circular
    }

    CIRCULAR_LIST_FREE(list->elements);
    CIRCULAR_LIST_FREE(list->next);
    (*list) = replica;

    return split;
}

/// @brief Iterates through each list element.
/// @param list Pointer to list structure.
/// @param operate Function pointer to operate on every single element pointer using arguments.
/// @param args Generic arguments for 'operate' function pointer.
static inline void foreach_circular_list(circular_list_s const * list, const operate_circular_list_fn operate, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size && operate(list->elements + list->next[previous], args); ++i) {
        previous = list->next[previous];
    }
}

/// @brief Map function that maps elements into array, manages it using size and args, and maps it back.
/// @param list Pointer to list structure.
/// @param manage Function pointer to manage the array of elements based on element size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note The map function can also be used to remove holes in list.
static inline void map_circular_list(circular_list_s * list, const manage_circular_list_fn manage, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(manage && "[ERROR] 'manage' pointer parameter pointer is NULL.");

    // create temporary array to store list elements
    CIRCULAR_LIST_DATA_TYPE * elements_array = CIRCULAR_LIST_REALLOC(NULL, list->size * sizeof(CIRCULAR_LIST_DATA_TYPE));
    CIRCULAR_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = list->next[previous];
        elements_array[i] = list->elements[previous];
    }

    manage(elements_array, list->size, args);

    list->empty_size = list->tail = 0; // set empty stack size and list tail index to zero
    for (size_t * list_current = &(list->tail), i = 0; i < list->size; ++i) {
        list->elements[i] = elements_array[i];
        list->tail = (*list_current) = i;
        list_current = list->next + i;
    }

    CIRCULAR_LIST_FREE(elements_array);
}

#elif CIRCULAR_LIST_MODE == FINITE_PRERPOCESSOR_CIRCULAR_LIST

#ifndef PREPROCESSOR_CIRCULAR_LIST_SIZE

#define PREPROCESSOR_CIRCULAR_LIST_SIZE (1 << 10)

#elif PREPROCESSOR_CIRCULAR_LIST_SIZE <= 0

#error 'PREPROCESSOR_CIRCULAR_LIST_SIZE' cannot be zero

#endif

/// @note The FINITE_PRERPOCESSOR_CIRCULAR_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the circular_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct circular_list {
    size_t size, empty_size, tail, empty_head;
    CIRCULAR_LIST_DATA_TYPE elements[PREPROCESSOR_CIRCULAR_LIST_SIZE];
    size_t next[PREPROCESSOR_CIRCULAR_LIST_SIZE];
} circular_list_s;

/// @brief Creates an empty forward list of zero size.
/// @return Forward list structure.
static inline circular_list_s create_circular_list(void) {
    return (circular_list_s) { .tail = 0, .size = 0, .empty_head = 0, .empty_size = 0, };
}

/// @brief Destroys the list and all its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
/// @note The destroyed list should not be used after calling this function, else create a new list.
static inline void destroy_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    list->empty_head = list->empty_size = list->size = list->tail = 0;
}

/// @brief Clears the list and destroys its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
static inline void clear_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    list->empty_head = list->empty_size = list->size = list->tail = 0;
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list List structure.
/// @param copy Function pointer to create a copy of an element.
/// @return Returns a copy of a list.
/// @note Returned copy of list won't have holes.
static inline circular_list_s copy_circular_list(const circular_list_s list, const copy_circular_list_fn copy) {
    CIRCULAR_LIST_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    CIRCULAR_LIST_ASSERT(list.size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    circular_list_s replica = { .empty_head = 0, .empty_size = 0, .size = 0, .tail = 0, };

    size_t previous = list.tail;
    for (size_t * current_replica = &(replica.tail); replica.size < list.size; replica.size++) {
        (*current_replica) = replica.size;

        replica.elements[replica.size] = copy(list.elements[previous]);

        previous = list.next[previous];
        current_replica = replica.next + replica.size;
        (*current_replica) = 0;
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list List structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_circular_list(const circular_list_s list) {
    CIRCULAR_LIST_ASSERT(list.size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_circular_list(const circular_list_s list) {
    CIRCULAR_LIST_ASSERT(list.size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    return (list.size == PREPROCESSOR_CIRCULAR_LIST_SIZE);
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_circular_list(circular_list_s * list, const size_t index, const CIRCULAR_LIST_DATA_TYPE element) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size < PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] List reached maximum size.");
    CIRCULAR_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    CIRCULAR_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous = list->tail; // save previous pointer
    for (size_t i = 0; (index != list->size) && i < index; ++i) { // iterate until previous isn't the node previous to index node
        previous = list->next[previous];
    }

    size_t free_slot = list->size;
    if (list->empty_size) { // if 'empty stack' isn't empty pop empty slot index from it
        free_slot = list->empty_head; // change empty slot to empty stack's head index
        list->empty_head = list->next[list->empty_head]; // move new empty stack index to head
        list->empty_size--; // decrement empty stack's size
    }

    size_t * current = list->next + previous;
    memcpy(list->elements + free_slot, &element, sizeof(CIRCULAR_LIST_DATA_TYPE));
    list->next[free_slot] = (*current);
    (*current) = free_slot;

    if (index == list->size) { // if index is at last/tail element tail must point to last added element
        list->tail = free_slot;
    }

    list->size++;
}

/// @brief Gets element at index.
/// @param list List structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline CIRCULAR_LIST_DATA_TYPE get_circular_list(const circular_list_s list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list.elements && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(list.next && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    CIRCULAR_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    CIRCULAR_LIST_ASSERT(list.size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Removes first element in list based on element parameter comparison.
/// @param list Pointer to list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_first_circular_list(circular_list_s * list, const CIRCULAR_LIST_DATA_TYPE element, const compare_circular_list_fn compare) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(compare && "[ERROR] 'compare' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t current = list->next[previous];

        if (0 != compare(list->elements[current], element)) { // early continue in order to remove one needless nesting level
            previous = current;
            continue;
        }

        // decrement size and save found element to return
        CIRCULAR_LIST_DATA_TYPE found = list->elements[current];
        list->size--;

        list->next[previous] = list->next[current];

        if (!list->size) { // set empty stack size to zero
            list->empty_size = 0;
        } else if (current != list->size) { // push empty index to 'empty stack'
            list->next[current] = list->empty_head;
            list->empty_head = current;
            list->empty_size++;
        }

        if (current == list->tail) { // if current is the last element
            list->tail = previous; // if list still has elements then tail will become the previous index
        }

        return found;
    }

    CIRCULAR_LIST_ASSERT(0 && "[ERROR] Element not found in list.");
    exit(EXIT_FAILURE);
}

/// @brief Removes list element at index.
/// @param list Pointer to list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_at_circular_list(circular_list_s * list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    const size_t current = list->next[previous];

    CIRCULAR_LIST_DATA_TYPE found = list->elements[current];
    list->size--;

    list->next[previous] = list->next[current];

    if (!list->size) {
        list->empty_size = 0;
    } else if (current != list->size) {
        // push empty index to 'empty stack'
        list->next[current] = list->empty_head;
        list->empty_head = current;
        list->empty_size++;
    }

    if (index == list->size) { // if last element is removed
        list->tail = previous; // if list still has elements then tail will become the previous index
    }

    return found;
}

/// @brief Reverses list.
/// @param list Pointer to list structure.
static inline void reverse_circular_list(circular_list_s * list) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous = list->tail;
    size_t current  = list->size ? list->next[previous] : 0;
    size_t next     = list->size ? list->next[current] : 0;
    list->tail = current;
    for (size_t i = 0; i < list->size; ++i) {
        list->next[current] = previous;
        previous = current;
        current = next;
        next = list->next[next];
    }
}

/// @brief Shifts list to next number of elements.
/// @param list Pointer to list structure.
/// @param shift Nonnegative integer to shift list by.
/// @note The list can shit zero or more than list's size times.
static inline void shift_circular_list(circular_list_s * list, const size_t shift) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't shift an empty list.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    for (size_t s = 0; s < shift; ++s) {
        list->tail = list->next[list->tail];
    }
}

/// @brief Splices two lists together while clearing source list.
/// @param destination Pointer to list structure to splice into.
/// @param source Pointer to list structure to splice from.
/// @param index Index at destination list to splice source list into.
/// @note If source list is zero destination list does not change.
static inline void splice_circular_list(circular_list_s * restrict destination, circular_list_s * restrict source, const size_t index) {
    CIRCULAR_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    CIRCULAR_LIST_ASSERT(destination->size + source->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    CIRCULAR_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    CIRCULAR_LIST_ASSERT(destination->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous_destination = destination->tail, previous_source = source->tail;
    // if index doesn't point to end and until index node is reached
    for (size_t i = 0; index != destination->size && i < index; ++i) {
        previous_destination = destination->next[previous_destination];
    }
    // fill empty stack indexes until empty stack is empty or source list is empty
    for (size_t source_size = source->size; source_size && destination->empty_size; source_size--, destination->size++) {
        const size_t current_source = source->next[previous_source];

        const size_t empty_pop = destination->empty_head; // pop empty stack's head
        destination->empty_head = destination->next[destination->empty_head]; // shift empty stack's head to next index
        destination->empty_size--; // decrement empty stack's size

        destination->elements[empty_pop] = source->elements[current_source];

        destination->next[empty_pop] = destination->next[previous_destination];
        destination->next[previous_destination] = empty_pop;

        previous_destination = destination->next[previous_destination];
        previous_source = current_source;
    }
    // fill destination until source list is empty
    for (size_t source_size = source->size; source_size; source_size--, destination->size++) {
        const size_t current_source = source->next[previous_source];

        destination->elements[destination->size] = source->elements[current_source];

        destination->next[destination->size] = destination->next[previous_destination];
        destination->next[previous_destination] = destination->size;

        previous_destination = destination->next[previous_destination];
        previous_source = current_source;
    }

    if (index == destination->size - source->size) { // if index splices from end then tail must change
        destination->tail = previous_destination;
    }

    // set source list's unallocated parameters to zero
    source->empty_size = source->tail = source->size = 0;
}

/// @brief Splits old list and returns new list with specified elements. Since forward list is circular the new list can
/// include elements beyond old list's last node.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline circular_list_s split_circular_list(circular_list_s * list, const size_t index, const size_t size) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(size && "[ERROR] 'size' parameter can't be zero.");
    CIRCULAR_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous_list = list->tail;

    circular_list_s replica = { .size = 0, .empty_size = 0, }, split = { .size = 0, .empty_size = 0, };
    size_t * replica_previous = &(replica.tail);
    for (; replica.size < index; replica.size++) { // copy elements to replica until index
        const size_t current_list = list->next[previous_list];

        replica.elements[replica.size] = list->elements[current_list];
        replica.tail = (*replica_previous) = replica.size;

        previous_list = current_list;
        replica_previous = replica.next + replica.size;
        (*replica_previous) = 0; // set last element's next index to 0 to make list circular
    }

    for (size_t * split_previous = &(split.tail); split.size < size; split.size++) { // copy elements to split until size
        const size_t current_list = list->next[previous_list];

        split.elements[split.size] = list->elements[current_list];
        split.tail = (*split_previous) = split.size;

        previous_list = current_list;
        split_previous = split.next + split.size;
        (*split_previous) = 0; // set last element's next index to 0 to make list circular
    }

    for (; split.size + replica.size < list->size; replica.size++) { // copy elements until replica plus split isn't list size
        const size_t current_list = list->next[previous_list];

        replica.elements[replica.size] = list->elements[current_list];
        replica.tail = (*replica_previous) = replica.size;

        previous_list = current_list;
        replica_previous = replica.next + replica.size;
        (*replica_previous) = 0; // set last element's next index to 0 to make list circular
    }

    memcpy(list->elements, replica.elements, replica.size * sizeof(CIRCULAR_LIST_DATA_TYPE));
    memcpy(list->next, replica.next, replica.size * sizeof(size_t));
    list->size = replica.size;
    list->tail = replica.tail;

    return split;
}

/// @brief Iterates through each list element.
/// @param list Pointer to list structure.
/// @param operate Function pointer to operate on every single element pointer using arguments.
/// @param args Generic arguments for 'operate' function pointer.
static inline void foreach_circular_list(circular_list_s * list, const operate_circular_list_fn operate, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size && operate(list->elements + list->next[previous], args); ++i) {
        previous = list->next[previous];
    }
}

/// @brief Map function that maps elements into array, manages it using size and args, and maps it back.
/// @param list Pointer to list structure.
/// @param manage Function pointer to manage the array of elements based on element size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note The map function can also be used to remove holes in list.
static inline void map_circular_list(circular_list_s * list, const manage_circular_list_fn manage, void * args) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter pointer is NULL.");
    CIRCULAR_LIST_ASSERT(manage && "[ERROR] 'manage' pointer parameter pointer is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= PREPROCESSOR_CIRCULAR_LIST_SIZE && "[ERROR] list size exceeds maximum macro.");

    CIRCULAR_LIST_DATA_TYPE elements_array[PREPROCESSOR_CIRCULAR_LIST_SIZE]; // create temporary array to store list elements

    size_t previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = list->next[previous];
        elements_array[i] = list->elements[previous];
    }

    manage(elements_array, list->size, args);

    list->empty_size = list->tail = 0; // set empty stack size and list tail index to zero
    for (size_t * list_current = &(list->tail), i = 0; i < list->size; ++i) {
        list->elements[i] = elements_array[i];
        list->tail = (*list_current) = i;
        list_current = list->next + i;
    }
}

#endif

#else

#error Cannot include multiple headers in same unit.

#endif // CIRCULAR_LIST_H
