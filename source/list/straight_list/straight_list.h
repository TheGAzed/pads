#ifndef STRAIGHT_LIST_H
#define STRAIGHT_LIST_H

#include <stddef.h>  // imports size_t
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

#define INFINITE_ALLOCATED_STRAIGHT_LIST  1001
#define FINITE_ALLOCATED_STRAIGHT_LIST    1002
#define INFINITE_REALLOC_STRAIGHT_LIST    1003
#define FINITE_PRERPOCESSOR_STRAIGHT_LIST 1004

//#define STRAIGHT_LIST_MODE INFINITE_ALLOCATED_STRAIGHT_LIST
//#define STRAIGHT_LIST_MODE FINITE_ALLOCATED_STRAIGHT_LIST
//#define STRAIGHT_LIST_MODE INFINITE_REALLOC_STRAIGHT_LIST
//#define STRAIGHT_LIST_MODE FINITE_PRERPOCESSOR_STRAIGHT_LIST
// List mode that can be set to INFINITE_ALLOCATED_STRAIGHT_LIST, FINITE_ALLOCATED_STRAIGHT_LIST, INFINITE_REALLOC_STRAIGHT_LIST or
// FINITE_PRERPOCESSOR_STRAIGHT_LIST, or INFINITE_ALLOCATED_STRAIGHT_LIST or FINITE_ALLOCATED_STRAIGHT_LIST
// Default: INFINITE_ALLOCATED_STRAIGHT_LIST
#ifndef STRAIGHT_LIST_MODE

#define STRAIGHT_LIST_MODE INFINITE_ALLOCATED_STRAIGHT_LIST

#endif

// Check to make sure a valid list mode is selected.
#if (STRAIGHT_LIST_MODE != INFINITE_ALLOCATED_STRAIGHT_LIST) && (STRAIGHT_LIST_MODE != FINITE_ALLOCATED_STRAIGHT_LIST)    && \
(STRAIGHT_LIST_MODE != INFINITE_REALLOC_STRAIGHT_LIST)   && (STRAIGHT_LIST_MODE != FINITE_PRERPOCESSOR_STRAIGHT_LIST)

#error Invalid type of list mode.

#endif

#ifndef STRAIGHT_LIST_DATA_TYPE

/// @brief Element datatype macro that can be changed via '#define STRAIGHT_LIST_DATA_TYPE [datatype]'.
#define STRAIGHT_LIST_DATA_TYPE void*

#endif

#ifndef STRAIGHT_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief Assertion macro that can be changed  via '#define STRAIGHT_LIST_ASSERT [assert]'.
#define STRAIGHT_LIST_ASSERT assert

#endif

#if STRAIGHT_LIST_MODE != FINITE_PRERPOCESSOR_STRAIGHT_LIST

#if !defined(STRAIGHT_LIST_REALLOC) && !defined(STRAIGHT_LIST_FREE)

#include <stdlib.h>

#ifndef STRAIGHT_LIST_REALLOC

#define STRAIGHT_LIST_REALLOC realloc

#endif

#ifndef STRAIGHT_LIST_FREE

#define STRAIGHT_LIST_FREE free

#endif

#elif !defined(STRAIGHT_LIST_REALLOC)

#error Queue reallocator macro is not defined!

#elif !defined(STRAIGHT_LIST_FREE)

#error Queue free macro is not defined!

#endif

#endif

/// @brief Function pointer to create a deep/shallow copy for straight list element.
typedef STRAIGHT_LIST_DATA_TYPE (*copy_straight_list_fn)    (const STRAIGHT_LIST_DATA_TYPE);
/// @brief Function pointer to destroy/free an element for straight list element.
typedef void                    (*destroy_straight_list_fn) (STRAIGHT_LIST_DATA_TYPE *);
/// @brief Function pointer to comapre two straight list elements. Returns zero if they're equal, a negative number if
/// 'less than', else a positive number if 'more than'.
typedef int                     (*compare_straight_list_fn) (const STRAIGHT_LIST_DATA_TYPE, const STRAIGHT_LIST_DATA_TYPE);
/// @brief Function pointer to operate on a single straight list element based on generic arguments.
typedef bool                    (*operate_straight_list_fn) (STRAIGHT_LIST_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of straight list elements based on generic arguments.
typedef void                    (*manage_straight_list_fn)  (STRAIGHT_LIST_DATA_TYPE *, const size_t, void *);

#if   STRAIGHT_LIST_MODE == INFINITE_ALLOCATED_STRAIGHT_LIST

// Many functions use Linus Torvalds' Tastes in code for linked lists from his TED Talk
// at https://www.youtube.com/watch?v=o8NPllzkFhE&t=858s (yeah, this comment only applies to this straight list mode)
// I think this idea is also mentioned in the book Pointers on C by Kenneth A. Reek
// (this book also inspired me to created PADS)

/// @brief Straight list node with element and pointer to next node.
struct straight_list_node {
    STRAIGHT_LIST_DATA_TYPE element; // current element
    struct straight_list_node * next; // pointer to next node
};

/// @brief The straight list is a non-circular linked list which functions like the classic linked list example.
typedef struct straight_list {
    size_t size; // size of straight list
    struct straight_list_node * head; // pointer to head/first node
} straight_list_s;

/// @brief Creates an empty straight list of zero size.
/// @return Straight list structure.
static inline straight_list_s create_straight_list(void) {
    return (straight_list_s) { 0 }; // sets straight list to zero
}

/// @brief Destroys the straight list with all its elements and sets size to zero.
/// @param list Pointer to straight list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
/// @note When list is destroyed it can't be used by any other function. To make the list usable create new list on it.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    while (list->head) { // change head to head's next node after every iteration until NULL is reached
        destroy(&(list->head->element)); // destroy function call to destroy/free element at head

        // free current head node
        struct straight_list_node * temp = list->head->next; // save node next to head in temporary
        STRAIGHT_LIST_FREE(list->head); // free head
        list->head = temp; // save temporary to head (guarantees head will be NULL at the end)
    }
    list->size = 0; // need to only set list size to zero since head will be NULL after while loop ends
}

/// @brief Clears the list of elements. Similar to destroy, but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    while (list->head) { // change head to head's next node after every iteration until NULL is reached
        destroy(&(list->head->element));

        struct straight_list_node * temp = list->head->next;
        STRAIGHT_LIST_FREE(list->head);
        list->head = temp;
    }
    list->size = 0; // need to only set list size to zero since head will be NULL after while loop ends
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Readonly straight list structure.
/// @param copy Readonly function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    STRAIGHT_LIST_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    straight_list_s replica = { .head = NULL, .size = list.size };

    for (struct straight_list_node * list_current = list.head, ** replica_current = &(replica.head); list_current; list_current = list_current->next, replica_current = &((*replica_current)->next)) {
        // create new node and copy element from source list based on copy function pointer parameter
        (*replica_current) = STRAIGHT_LIST_REALLOC(NULL, sizeof(struct straight_list_node));
        STRAIGHT_LIST_ASSERT((*replica_current) && "[ERROR] Memory allocation failed.");
        // if copy is specified call it, else just assign it to variable
        (*replica_current)->element = copy(list_current->element);
        (*replica_current)->next = NULL;
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list Readonly straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Readonly straight list structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero
    // and negating it makes function return true only if full
    return !(~list.size);
}

/// @brief Iterates through each straight list element.
/// @param list Pointer to readonly straight list structure.
/// @param operate Readonly function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s const * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    for (struct straight_list_node * current = list->head; current && operate(&current->element, args); current = current->next) {}
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param list Pointer to readonly straight list structure.
/// @param manage Readonly function pointer to manage the array of elements based on list size and specified arguments.
/// @param args Void pointer arguments for 'manage' function.
static inline void map_straight_list(straight_list_s const * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'manage' parameter pointer is NULL.");

    // create continuos array to store lis elements
    STRAIGHT_LIST_DATA_TYPE * elements_array = STRAIGHT_LIST_REALLOC(NULL, sizeof(STRAIGHT_LIST_DATA_TYPE) * list->size);
    STRAIGHT_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    size_t index = 0;
    for (struct straight_list_node * current = list->head; current; current = current->next) {
        elements_array[index++] = current->element;
    }

    manage(elements_array, list->size, args);

    index = 0;
    for (struct straight_list_node * current = list->head; current; current = current->next) {
        current->element = elements_array[index++];
    }

    STRAIGHT_LIST_FREE(elements_array);
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Readonly straight list structure.
/// @param element Readonly element to search in list.
/// @param compare Readonly function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than element parameter.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. Map function can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter pointer is NULL.");
    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    struct straight_list_node const * base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        struct straight_list_node const * current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = current->next;
        }

        const int comparison = compare(element, current->element);

        if (0 == comparison) {
            return true;
        }
        if (0 < comparison) {
            base = current->next; // increment element pointer to next
            limit--; // decrement limit to avoid 'out of bounds' access (if we ignore circularity)
        }
    }

    return false;
}

/// @brief Inserts an element at any index in the list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zeero based index to insert element at.
/// @param element Readonly element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    STRAIGHT_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    struct straight_list_node ** current = &(list->head); // current double pointer to be able to save new node into it
    for (size_t i = 0; i < index; ++i) { // iterate until pointer index node is reached
        current = &((*current)->next); // go to address of next's pointer from current
    }

    // creates node and copies element parameter into the node element
    struct straight_list_node * node = STRAIGHT_LIST_REALLOC(NULL, sizeof(struct straight_list_node));
    STRAIGHT_LIST_ASSERT(node && "[ERROR] Memory allocation failed.");

    memcpy(&(node->element), &element, sizeof(STRAIGHT_LIST_DATA_TYPE));
    list->size++; // increment list size to reflect adding a new element

    node->next = (*current); // make new node's next pointer point to current
    (*current) = node; // change pointer to current node to new node
}

/// @brief Gets element at any index in the list.
/// @param list Readonly straight list structure.
/// @param index Readonly zero based index of element in list.
/// @return Element at index in list.
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list.head && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    struct straight_list_node const * current = list.head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->element;
}

/// @brief Removes first element in straight list that matches parameter element comparison.
/// @param list Pointer to straight list structure.
/// @param element Readonly element to compare and remove from list.
/// @param compare Readonly function pointer that compares element parameter to elements in list. Returns zero if equal.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    // interate while derefernced pointer is not NULL
    for (struct straight_list_node ** current = &(list->head); (*current); current = &((*current)->next)) {
        if (0 == compare((*current)->element, element)) { // if comparison returns zero, i.e. elements are equal
            STRAIGHT_LIST_DATA_TYPE removed = (*current)->element; // save removed element to not lose it
            list->size--; // decrement list size to reflect removal

            struct straight_list_node * temp = (*current); // save current note as temporary
            (*current) = (*current)->next; // change current's value to its next
            STRAIGHT_LIST_FREE(temp); // free temporary saved current node

            return removed;
        }
    }

    STRAIGHT_LIST_ASSERT(false && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned
    exit(EXIT_FAILURE); // since function must return an element exit must be called to avoid function return
}

/// @brief Removes element at index in list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct straight_list_node ** current = &(list->head); // current double pointer to be able to save new node into it
    for (size_t i = 0; i < index; ++i) { // iterate to node at index
        current = &((*current)->next); // go to next's pointer
    }

    STRAIGHT_LIST_DATA_TYPE removed = (*current)->element; // save removed element to not lose it
    list->size--; // decrement list size to reflect removal

    struct straight_list_node * temp = (*current); // save current note as temporary
    (*current) = (*current)->next; // change current's value to its next
    STRAIGHT_LIST_FREE(temp); // free temporary saved current node

    return removed;
}

/// @brief Reverses list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct straight_list_node * previous = NULL; // set previous node pointer to NULL
    for (struct straight_list_node * current = list->head, * next = NULL; current; previous = current, current = next) {
        next = current->next; // save current's next pointer
        current->next = previous; // set current's next pointer to previous
    }
    list->head = previous; // make head start from last node, i.e. previous
}

/// @brief Splices source into destination list while clearing source list.
/// @param destination Rescricted pointer to straight list structure to splice into.
/// @param source Rescricted pointer to straight list structure to splice from.
/// @param index Readonly zero-based index at destination list to splice source list into.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index) {
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    struct straight_list_node ** current_destination = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        current_destination = &((*current_destination)->next); // go to destination's next's pointer
    }

    struct straight_list_node ** last_source = &(source->head);
    while ((*last_source)) { // iterate while pointer to node dereferenced is not NULL to get pointer to last source node
        last_source = &((*last_source)->next); // go to next's pointer
    }

    (*last_source) = (*current_destination); // change last source node pointer to destination's current
    (*current_destination) = source->head; // change destination's index node pointer to source's head

    destination->size += source->size;

    (*source) = (straight_list_s) { 0 }; // set source list to zero (i. e. destroy it)
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Non-zero size of new split list.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(size && "[ERROR] Split size can't be zero.");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size.");

    struct straight_list_node ** start = &(list->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index if size is not zero
        start = &((*start)->next);
    }

    struct straight_list_node ** end = start;
    straight_list_s split = { .head = (*start), .size = 0, }; // set initial split head to start node
    for (; split.size < size; ++split.size) {
        end = &((*end)->next); // go to end node at index + size
    }

    (*start) = (*end); // set node at start pointer to end
    (*end) = NULL; // set node at end pointer to NULL
    list->size -= size; // decrement list size by parameter size

    return split;
}

#elif STRAIGHT_LIST_MODE == FINITE_ALLOCATED_STRAIGHT_LIST

/// @note The FINITE_ALLOCATED_STRAIGHT_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the straight_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when there are no holes (meaning 'empty stack' is empty) the straight list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The straight list is a linked list.
typedef struct straight_list {
    size_t size, head, max; // size, head index and maximum allowed size
    size_t empty_size, empty_head; // empty stack's head and size
    STRAIGHT_LIST_DATA_TYPE * elements; // elements array pointer
    size_t * next; // next indexes pointer
} straight_list_s;

/// @brief Creates an empty straight list of zero size.
/// @param max Maximum positive nonzero size of straight list.
/// @return Straight list structure.
static inline straight_list_s create_straight_list(const size_t max) {
    STRAIGHT_LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const straight_list_s list = {
        .elements = STRAIGHT_LIST_REALLOC(NULL, max * sizeof(STRAIGHT_LIST_DATA_TYPE)), // allocate array of 'max' STRAIGHT_LIST_DATA_TYPE's
        .next = STRAIGHT_LIST_REALLOC(NULL, max * sizeof(size_t)), // allocate array of 'max' size_t's
        .head = 0, .max = max, .size = 0, .empty_head = 0, .empty_size = 0, // set everything but max to 0 (.max to max)
    };
    // check if memory allocation failed
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] Memory allocation failed.");

    return list;
}

/// @brief Destroys the straight list with all its elements and sets size to zero.
/// @param list Pointer to straight list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
/// @note When list is destroyed it can't be used by any other function. To make the list usable create new list on it.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current); // destroy element at current position
        current = list->next[current]; // go to next index from current
    }

    STRAIGHT_LIST_FREE(list->elements); // free elements array
    STRAIGHT_LIST_FREE(list->next); // free next index array
    (*list) = (straight_list_s) { 0 }; // set everything in list to zero to make it an 'invalid list'
}

/// @brief Clears the list of elements. Similar to destroy, but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current); // destroy element at current position
        current = list->next[current]; // go to next index from current
    }

    // set cleared list's empty stack and head to zero and keep allocated memory
    list->size = list->empty_head = list->empty_size = list->head = 0;
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Readonly straight list structure.
/// @param copy Readonly function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    STRAIGHT_LIST_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list.max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.size <= list.max && "[ERROR] List's size can't exceed its maximum size.");

    straight_list_s list_copy = {
        .next = STRAIGHT_LIST_REALLOC(NULL, list.max * sizeof(size_t)), .head = 0, .size = list.size, .max = list.max,
        .elements = STRAIGHT_LIST_REALLOC(NULL, list.max * sizeof(STRAIGHT_LIST_DATA_TYPE)), .empty_head = 0, .empty_size = 0,
    };
    STRAIGHT_LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(list_copy.next && "[ERROR] Memory allocation failed.");

    size_t current_list = list.head;
    // double pointer since this also works on copying straight list
    size_t * current_copy = &(list_copy.head);
    for (size_t i = 0; i < list.size; ++i) {
        // set element copy to list copy at index i to automatically remove holes from copy
        list_copy.elements[i] = copy(list.elements[current_list]);
        (*current_copy) = i; // set head and indexes at list copy's next array to proper index

        current_list = list.next[current_list]; // go to next list node
        current_copy = list_copy.next + (*current_copy); // go to next copy list's pointer to node
    }

    return list_copy;
}

/// @brief Checks if list is empty.
/// @param list Readonly straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    STRAIGHT_LIST_ASSERT(list.max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.size <= list.max && "[ERROR] List's size can't exceed its maximum size.");

    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Readonly straight list structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    STRAIGHT_LIST_ASSERT(list.max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.size <= list.max && "[ERROR] List's size can't exceed its maximum size.");
    // if size is equal to maximum
    return (list.size == list.max);
}

/// @brief Iterates through each straight list element.
/// @param list Pointer to readonly straight list structure.
/// @param operate Readonly function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s const * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    for (size_t i = 0, current = list->head; i < list->size && operate(list->elements + current, args); ++i) {
        current = list->next[current];
    }
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param list Pointer to readonly straight list structure.
/// @param manage Readonly function pointer to manage the array of elements based on list size and specified arguments.
/// @param args Void pointer arguments for 'manage' function.
/// @note This function can also be used to remove holes in list.
static inline void map_straight_list(straight_list_s * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    straight_list_s replica = {
        .empty_head = 0, .empty_size = 0, .size = 0, .head = 0, .max = list->max,
        .elements = STRAIGHT_LIST_REALLOC(NULL, sizeof(STRAIGHT_LIST_DATA_TYPE) * list->max),
        .next = STRAIGHT_LIST_REALLOC(NULL, sizeof(size_t) * list->max),
    };
    STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");

    for (size_t list_current = list->head, * replica_current = &(replica.head); replica.size < list->size; replica.size++) {
        replica.elements[replica.size] = list->elements[list_current];
        (*replica_current) = replica.size;

        replica_current = replica.next + replica.size;
        list_current = list->next[list_current];
    }

    STRAIGHT_LIST_FREE(list->elements);
    STRAIGHT_LIST_FREE(list->next);
    (*list) = replica;

    manage(list->elements, list->size, args);
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Readonly straight list structure.
/// @param element Readonly element to search in list.
/// @param compare Readonly function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than element parameter.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. Map function can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list.max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.size <= list.max && "[ERROR] List's size can't exceed its maximum size.");

    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    size_t base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        size_t current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare(element, list.elements[current]);

        if (0 == comparison) {
            return true;
        }
        if (0 < comparison) {
            base = list.next[current]; // increment element pointer to next
            limit--; // decrement limit to avoid 'out of bounds' access (if we ignore circularity)
        }
    }

    return false;
}

/// @brief Inserts an element at any index in the list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zeero based index to insert element at.
/// @param element Readonly element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size < list->max && "[ERROR] List reached maximum size.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) { // iterate to current index node pointer
        current = list->next + (*current);
    }

    size_t push = list->size; // if empty stack has no empty node indexes then push node at list size like an array stack
    if (list->empty_size) { // if stack with empty nodes has nodes, then pop empty node index to push as new node
        push = list->empty_head; // get empty node index to set push to if there are empty nodes
        list->empty_head = list->next[list->empty_head]; // set empty head to new nod eindex
        list->empty_size--; // decrement empty size
    }
    memcpy(list->elements + push, &element, sizeof(STRAIGHT_LIST_DATA_TYPE));
    list->size++; // increment list size

    list->next[push] = (*current); // set push's next index to current index
    (*current) = push; // set node which points to current index value, previous' next, to push index
}

/// @brief Gets element at any index in the list.
/// @param list Readonly straight list structure.
/// @param index Readonly zero based index of element in list.
/// @return Element at index in list.
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    STRAIGHT_LIST_ASSERT(list.max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list.size <= list.max && "[ERROR] List's size can't exceed its maximum size.");

    size_t current = list.head;
    for (size_t i = 0; i < index; ++i) {
        current = list.next[current]; // go to next index from current
    }

    return list.elements[current];
}

/// @brief Removes first element in straight list that matches parameter element comparison.
/// @param list Pointer to straight list structure.
/// @param element Readonly element to compare and remove from list.
/// @param compare Readonly function pointer that compares element parameter to elements in list. Returns zero if equal.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < list->size; ++i) {
        if (0 != compare(list->elements[(*current)], element)) { // early continue in order to remove one needless nesting level
            current = list->next + (*current);
            continue;
        }

        STRAIGHT_LIST_DATA_TYPE removed = list->elements[(*current)];
        list->size--;

        const size_t temp = (*current);
        (*current) = list->next[(*current)];
        if (!list->size) { // if list is empty set empty stack elements to zero
            list->empty_size = 0;
        } else if (temp != list->size) {
            // push empty index to 'empty stack'
            list->next[temp] = list->empty_head;
            list->empty_head = temp;
            list->empty_size++;
        }

        return removed;
    }

    STRAIGHT_LIST_ASSERT(0 && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned, since the function returns the removed element, element can contain allocated memory
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index in list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = list->next + (*current);
    }

    STRAIGHT_LIST_DATA_TYPE removed = list->elements[(*current)];
    list->size--;

    const size_t temp = (*current);
    (*current) = list->next[(*current)];
    if (!list->size) { // if list is empty set empty stack elements to zero
        list->empty_size = 0;
    } else if (temp != list->size) { // else if current index is not the last element in elements array
        // push empty index to 'empty stack'
        list->next[temp] = list->empty_head;
        list->empty_head = temp;
        list->empty_size++;
    }


    return removed;
}

/// @brief Reverses list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    size_t previous = 0;
    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        const size_t next = list->next[current];
        list->next[current] = previous;
        previous = current;
        current = next;
    }
    list->head = previous;
}

/// @brief Splices source into destination list while clearing source list.
/// @param destination Rescricted pointer to straight list structure to splice into.
/// @param source Rescricted pointer to straight list structure to splice from.
/// @param index Readonly zero-based index at destination list to splice source list into.
/// @param max New maximum positive nonzero size of destination list.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index, const size_t max) {
    STRAIGHT_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(destination->size + source->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    STRAIGHT_LIST_ASSERT(destination->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(destination->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(destination->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(destination->size <= destination->max && "[ERROR] List's size can't exceed its maximum size.");

    STRAIGHT_LIST_ASSERT(source->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(source->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(source->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(source->size <= source->max && "[ERROR] List's size can't exceed its maximum size.");

    destination->elements = STRAIGHT_LIST_REALLOC(destination->elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * max);
    STRAIGHT_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed.");
    destination->next = STRAIGHT_LIST_REALLOC(destination->next, sizeof(size_t) * max);
    STRAIGHT_LIST_ASSERT(destination->next && "[ERROR] Memory allocation failed.");
    destination->max = max;

    size_t * destination_current = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        destination_current = destination->next + (*destination_current);
    }

    size_t const * last_source = &(source->head);
    for (; source->size && destination->empty_size; source->size--, destination->size++, destination->empty_size--) {
        memcpy(destination->elements + destination->empty_head, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));

        const size_t temp = destination->empty_head; // save empty head index as tempt to not lose it
        destination->empty_head = destination->next[destination->empty_head]; // set empty head to next empty index

        destination->next[temp] = (*destination_current); // set temp's next index to index at current pointer
        (*destination_current) = temp; // set index at current pointer, previous' next index, to temp

        destination_current = destination->next + (*destination_current);
        last_source = source->next + (*last_source);
    }

    for (; source->size; source->size--, destination->size++) {
        memcpy(destination->elements + destination->size, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->next[destination->size] = (*destination_current);
        (*destination_current) = destination->size;

        destination_current = destination->next + (*destination_current);
        last_source = source->next + (*last_source);
    }

    source->empty_size = source->head = 0;
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Non-zero size of new split list.
/// @param max Maximum positive nonzero size of newly returned split list.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size, const size_t max) {
    STRAIGHT_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    STRAIGHT_LIST_ASSERT(size && "[ERROR] Split size can't be zero.");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    STRAIGHT_LIST_ASSERT(list->max && "[ERROR] List's maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] List's elements array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] List's next array can't be NULL.");
    STRAIGHT_LIST_ASSERT(list->size <= list->max && "[ERROR] List's size can't exceed its maximum size.");

    straight_list_s split = {
        .elements = STRAIGHT_LIST_REALLOC(NULL, max * sizeof(STRAIGHT_LIST_DATA_TYPE)),
        .next = STRAIGHT_LIST_REALLOC(NULL, max * sizeof(size_t)),
        .empty_head = 0, .empty_size = 0, .size = 0, .head = 0, .max = max,
    };
    STRAIGHT_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed.");

    straight_list_s replica = {
        .elements = STRAIGHT_LIST_REALLOC(NULL, list->max * sizeof(STRAIGHT_LIST_DATA_TYPE)),
        .next = STRAIGHT_LIST_REALLOC(NULL, list->max * sizeof(size_t)),
        .size = 0, .head = 0, .max = list->max, .empty_head = 0, .empty_size = 0,
    };
    STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed.");

    size_t list_current = list->head;
    size_t * replica_current = &(replica.head);
    // put elements from start to index to replica list if size is not 0
    for (; replica.size < index; replica.size++) {
        replica.elements[replica.size] = list->elements[list_current];
        (*replica_current) = replica.size;

        replica_current = replica.next + replica.size;
        list_current = list->next[list_current];
    }
    // put elements from index to size to split list
    for (size_t * split_current = &(split.head); split.size < size; split.size++) {
        split.elements[split.size] = list->elements[list_current];
        (*split_current) = split.size;

        split_current = split.next + split.size;
        list_current = list->next[list_current];
    }
    // put elements from (index + size) to end of list to replica list if size is not 0
    for (size_t i = index + size; i < list->size; ++i, replica.size++) {
        replica.elements[replica.size] = list->elements[list_current];
        (*replica_current) = replica.size;

        replica_current = replica.next + replica.size;
        list_current = list->next[list_current];
    }

    STRAIGHT_LIST_FREE(list->elements);
    STRAIGHT_LIST_FREE(list->next);
    (*list) = replica; // turn list to replica

    return split;
}

#elif STRAIGHT_LIST_MODE == INFINITE_REALLOC_STRAIGHT_LIST

#if !defined(IS_CAPACITY_STRAIGHT_LIST) && !defined(EXPAND_CAPACITY_STRAIGHT_LIST)

#ifndef REALLOC_STRAIGHT_LIST_CHUNK

#define REALLOC_STRAIGHT_LIST_CHUNK (1 << 5)

#elif REALLOC_STRAIGHT_LIST_CHUNK <= 0

#error 'REALLOC_STRAIGHT_LIST_CHUNK' cannot be less than or equal to 0

#endif

/// @brief Checks if stack's 'size' has reached capacity.
#define IS_CAPACITY_STRAIGHT_LIST(size) (!((size) % REALLOC_STRAIGHT_LIST_CHUNK))

/// @brief Calculates next stack's capacity based on 'size'.
#define EXPAND_CAPACITY_STRAIGHT_LIST(capacity) ((capacity) + REALLOC_STRAIGHT_LIST_CHUNK)

#elif !defined(IS_CAPACITY_STRAIGHT_LIST)

#error Stack capacity reached check is not defined.

#elif !defined(EXPAND_CAPACITY_STRAIGHT_LIST)

#error Stack capacity expanded size is not defined.

#endif

/// @note The FINITE_ALLOCATED_STRAIGHT_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the straight_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when there are no holes (meaning 'empty stack' is empty) the straight list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The straight list is a linked list.
typedef struct straight_list {
    size_t size, empty_size, head, empty_head;
    STRAIGHT_LIST_DATA_TYPE * elements;
    size_t * next;
} straight_list_s;

/// @brief Creates an empty straight list of zero size.
/// @return Straight list structure.
static inline straight_list_s create_straight_list(void) {
    return (straight_list_s) { 0 }; // sets straight list to zero
}

/// @brief Destroys the straight list with all its elements and sets size to zero.
/// @param list Pointer to straight list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
/// @note When list is destroyed it can't be used by any other function. To make the list usable create new list on it.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }

    STRAIGHT_LIST_FREE(list->elements); // free elements array
    STRAIGHT_LIST_FREE(list->next); // free next index array
    (*list) = (straight_list_s) { 0 }; // set everything to zero
}

/// @brief Clears the list of elements. Similar to destroy, but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }
    STRAIGHT_LIST_FREE(list->elements);
    STRAIGHT_LIST_FREE(list->next);

    (*list) = (straight_list_s) { 0 }; // clear list data
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Readonly straight list structure.
/// @param copy Readonly function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    STRAIGHT_LIST_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL");

    straight_list_s replica = { 0 };
    for (size_t list_current = list.head, * replica_current = &(replica.head); replica.size < list.size; replica.size++) {
        (*replica_current) = replica.size;

        if ((IS_CAPACITY_STRAIGHT_LIST(replica.size))) {
            const size_t expand = (EXPAND_CAPACITY_STRAIGHT_LIST(replica.size));

            replica.elements = STRAIGHT_LIST_REALLOC(replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
            STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed");

            replica.next = STRAIGHT_LIST_REALLOC(replica.next, sizeof(size_t) * expand);
            STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed");
        }

        replica.elements[replica.size] = copy(list.elements[list_current]);

        replica_current = replica.next + replica.size;
        list_current = list.next[list_current];
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list Readonly straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Readonly straight list structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero
    // and negating it makes function return true only if full
    return !(~list.size);
}

/// @brief Iterates through each straight list element.
/// @param list Pointer to readonly straight list structure.
/// @param operate Readonly function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s const * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    for (size_t i = 0, current = list->head; i < list->size && operate(list->elements + current, args); ++i) {
        current = list->next[current];
    }
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param list Pointer to readonly straight list structure.
/// @param manage Readonly function pointer to manage the array of elements based on list size and specified arguments.
/// @param args Void pointer arguments for 'manage' function.
/// @note This function can also be used to remove holes in list.
static inline void map_straight_list(straight_list_s * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'manage' parameter pointer is NULL.");

    straight_list_s replica = { 0 };
    for (size_t list_current = list->head, * replica_current = &(replica.head); replica.size < list->size; replica.size++) {
        // make head and next pointers index to next (it won't set the last element's next index since it doesn't point anywhere)
        (*replica_current) = replica.size;

        if ((IS_CAPACITY_STRAIGHT_LIST(replica.size))) {
            const size_t expand = (EXPAND_CAPACITY_STRAIGHT_LIST(replica.size));

            replica.elements = STRAIGHT_LIST_REALLOC(replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
            STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed");

            replica.next = STRAIGHT_LIST_REALLOC(replica.next, sizeof(size_t) * expand);
            STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed");
        }

        replica.elements[replica.size] = list->elements[list_current];

        replica_current = replica.next + replica.size;
        list_current = list->next[list_current];
    }

    STRAIGHT_LIST_FREE(list->elements);
    STRAIGHT_LIST_FREE(list->next);
    (*list) = replica;

    manage(list->elements, list->size, args);
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Readonly straight list structure.
/// @param element Readonly element to search in list.
/// @param compare Readonly function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than element parameter.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. Map function can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter pointer is NULL.");
    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    size_t base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        size_t current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare(element, list.elements[current]);

        if (0 == comparison) {
            return true;
        }
        if (0 < comparison) {
            base = list.next[current]; // increment element pointer to next
            limit--; // decrement limit to avoid 'out of bounds' access (if we ignore circularity)
        }
    }

    return false;
}

/// @brief Inserts an element at any index in the list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zeero based index to insert element at.
/// @param element Readonly element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    STRAIGHT_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    if ((IS_CAPACITY_STRAIGHT_LIST(list->size))) { // if list has reached its capacity allocate new array
        const size_t expand = (EXPAND_CAPACITY_STRAIGHT_LIST(list->size));
        list->elements = STRAIGHT_LIST_REALLOC(list->elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
        STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] Memory allocation failed.");

        list->next = STRAIGHT_LIST_REALLOC(list->next, sizeof(size_t) * expand);
        STRAIGHT_LIST_ASSERT(list->next && "[ERROR] Memory allocation failed.");
    }

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) { // go to node at index
        current = list->next + (*current);
    }

    size_t push = list->size; // set index where element will be pushed
    if (list->empty_size) { // if 'empty stack' is not empty change push index to stack's head
        push = list->empty_head;
        list->empty_head = list->next[list->empty_head];
        list->empty_size--;
    }

    memcpy(list->elements + push, &element, sizeof(STRAIGHT_LIST_DATA_TYPE));
    list->size++;

    list->next[push] = (*current);
    (*current) = push;
}

/// @brief Gets element at any index in the list.
/// @param list Readonly straight list structure.
/// @param index Readonly zero based index of element in list.
/// @return Element at index in list.
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    for (size_t i = 0; i < index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Removes first element in straight list that matches parameter element comparison.
/// @param list Pointer to straight list structure.
/// @param element Readonly element to compare and remove from list.
/// @param compare Readonly function pointer that compares element parameter to elements in list. Returns zero if equal.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");

    size_t * current = &(list->head); // save pointer to list's head as current index pointer
    for (size_t i = 0; i < list->size; ++i) {
        if (0 != compare(list->elements[(*current)], element)) { // early continue in order to remove one needless nesting level
            current = list->next + (*current); // go to next index
            continue; // continue if comparison is not equal, i.e. 0
        }

        list->size--; // decrement list size
        STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)]; // get found element

        const size_t temp = (*current);
        (*current) = list->next[(*current)];
        if (temp != list->size) { // if current index is not at last element in elements array add to empty stack
            // push empty index to 'empty stack'
            list->next[temp] = list->empty_head; // make current's next index into empty stack's head
            list->empty_head = temp; // save current index at empty stack head
            list->empty_size++; // increment empty stack
        }

        (*current) = list->next[(*current)]; // change current index to its next node

        if (!(IS_CAPACITY_STRAIGHT_LIST(list->size))) { // if list can't be shrunk just return the removed found element
            return found;
        }

        straight_list_s replica = { 0 }; // create temporary replica of list
        // while replica's size is less than list's increment its size
        for (size_t list_current = list->head, * replica_current = &(replica.head); replica.size < list->size; ++(replica.size)) {
            if ((IS_CAPACITY_STRAIGHT_LIST(replica.size))) { // if replica's size has hit its capacity
                const size_t expand = EXPAND_CAPACITY_STRAIGHT_LIST(replica.size); // save new expanded size for replica
                // reallocate new expanded memory for elements' and next's array based on 'expand'
                replica.elements = STRAIGHT_LIST_REALLOC(replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
                STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed");

                replica.next = STRAIGHT_LIST_REALLOC(replica.next, sizeof(size_t) * expand);
                STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed");
            }

            (*replica_current) = replica.size; // save replica's current size to head and next indexes
            replica.elements[replica.size] = list->elements[list_current]; // shallow copy list's elements into replica

            replica_current = replica.next + replica.size; // go to replica's next index pointer
            list_current = list->next[list_current]; // go to list's next index
        }

        STRAIGHT_LIST_FREE(list->elements); // free list's elements
        STRAIGHT_LIST_FREE(list->next); // free list's next indexes
        (*list) = replica; // change list into replica

        return found;
    }

    STRAIGHT_LIST_ASSERT(false && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned, since the function returns the removed element equal to parameter element
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index in list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = list->next + (*current);
    }

    list->size--; // decrement list size
    STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)]; // get found element

    const size_t temp = (*current);
    (*current) = list->next[(*current)];
    if (temp != list->size) { // if current index is not at last element in elements array add to empty stack
        // push empty index to 'empty stack'
        list->next[temp] = list->empty_head; // make current's next index into empty stack's head
        list->empty_head = temp; // save current index at empty stack head
        list->empty_size++; // increment empty stack
    }

    if (!(IS_CAPACITY_STRAIGHT_LIST(list->size))) { // if list can't be shrunk just return the removed found element
        return found;
    }

    straight_list_s replica = { 0 }; // create temporary replica of list
    // while replica's size is less than list's increment its size
    for (size_t list_current = list->head, * replica_current = &(replica.head); replica.size < list->size; ++(replica.size)) {
        (*replica_current) = replica.size; // save replica's current size to head and next indexes

        if ((IS_CAPACITY_STRAIGHT_LIST(replica.size))) { // if replica's size has hit its capacity
            const size_t expand = EXPAND_CAPACITY_STRAIGHT_LIST(replica.size); // save new expanded size for replica
            // reallocate new expanded memory for elements' and next's array based on 'expand'
            replica.elements = STRAIGHT_LIST_REALLOC(replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
            STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed");

            replica.next = STRAIGHT_LIST_REALLOC(replica.next, sizeof(size_t) * expand);
            STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed");
        }

        replica.elements[replica.size] = list->elements[list_current]; // shallow copy list's elements into replica

        replica_current = replica.next + replica.size; // go to replica's next index pointer
        list_current = list->next[list_current]; // go to list's next index
    }

    STRAIGHT_LIST_FREE(list->elements); // free list's elements
    STRAIGHT_LIST_FREE(list->next); // free list's next indexes
    (*list) = replica; // change list into replica

    return found;
}

/// @brief Reverses list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = 0; // set previous index to zero
    size_t current = list->head; // set current index to list's head index
    for (size_t i = 0; i < list->size; ++i) { // iterate for list size
        const size_t next = list->next[current]; // set current's next index
        list->next[current] = previous; // change current's next index to previous
        previous = current; // set previous index to current
        current = next; // set current index to next
    }
    list->head = previous; // set  list's head to previous index
}

/// @brief Splices source into destination list while clearing source list.
/// @param destination Rescricted pointer to straight list structure to splice into.
/// @param source Rescricted pointer to straight list structure to splice from.
/// @param index Readonly zero-based index at destination list to splice source list into.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index) {
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    size_t * current_dest = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        current_dest = destination->next + (*current_dest); // go to next pointer to destination's current index
    }

    size_t const * last_source = &(source->head);
    for (; source->size && destination->empty_size; source->size--, destination->size++, destination->empty_size--) {
        memcpy(destination->elements + destination->empty_head, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));

        const size_t temp = destination->empty_head;
        destination->empty_head = destination->next[destination->empty_head];

        destination->next[temp] = (*current_dest);
        (*current_dest) = temp;

        current_dest = destination->next + (*current_dest);
        last_source = source->next + (*last_source);
    }

    for (; source->size; source->size--) {
        const size_t temp = (*current_dest); // if realloc is performed we may loose the pointer to destinations's current index
        (*current_dest) = destination->size; // before reallocation may happen we change the index at current destination's pointer

        if ((IS_CAPACITY_STRAIGHT_LIST(destination->size))) {
            const size_t expand = EXPAND_CAPACITY_STRAIGHT_LIST(destination->size);

            destination->elements = STRAIGHT_LIST_REALLOC(destination->elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
            STRAIGHT_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed");

            destination->next = STRAIGHT_LIST_REALLOC(destination->next, sizeof(size_t) * expand);
            STRAIGHT_LIST_ASSERT(destination->next && "[ERROR] Memory allocation failed");
        }

        memcpy(destination->elements + destination->size, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->next[destination->size++] = temp;

        current_dest = destination->next + destination->size - 1;
        last_source = source->next + (*last_source);
    }

    STRAIGHT_LIST_FREE(source->elements);
    STRAIGHT_LIST_FREE(source->next);
    (*source) = (straight_list_s) { 0 }; // set source list to zero (i. e. destroy it)
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Non-zero size of new split list.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL");
    STRAIGHT_LIST_ASSERT(size && "[ERROR] Split size can't be zero.");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    straight_list_s replica = { 0 }, split = { 0 };

    size_t current = (list->head);
    size_t * replica_current = &(replica.head);
    // create list replica with element from start to index if size is not zero
    for (; replica.size < index; replica.size++) {
        (*replica_current) = replica.size;

        if ((IS_CAPACITY_STRAIGHT_LIST(replica.size))) {
            const size_t expand = EXPAND_CAPACITY_STRAIGHT_LIST(replica.size);

            replica.elements = STRAIGHT_LIST_REALLOC(replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
            STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed");

            replica.next = STRAIGHT_LIST_REALLOC(replica.next, sizeof(size_t) * expand);
            STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed");
        }

        replica.elements[replica.size] = list->elements[current];

        replica_current = replica.next + replica.size;
        current = list->next[current];
    }

    // create split list of 'size parameter' size with elements from index onwards
    for (size_t * split_current = &(split.head); split.size < size; split.size++) {
        (*split_current) = split.size;

        if ((IS_CAPACITY_STRAIGHT_LIST(split.size))) {
            const size_t expand = EXPAND_CAPACITY_STRAIGHT_LIST(replica.size);

            split.elements = STRAIGHT_LIST_REALLOC(split.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
            STRAIGHT_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed");

            split.next = STRAIGHT_LIST_REALLOC(split.next, sizeof(size_t) * expand);
            STRAIGHT_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed");
        }

        split.elements[split.size] = list->elements[current];

        split_current = split.next + split.size;
        current = list->next[current];
    }

    for (size_t i = index + size; i < list->size; ++i, replica.size++) {
        (*replica_current) = replica.size;

        if ((IS_CAPACITY_STRAIGHT_LIST(replica.size))) {
            const size_t expand = EXPAND_CAPACITY_STRAIGHT_LIST(replica.size);

            replica.elements = STRAIGHT_LIST_REALLOC(replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * expand);
            STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed");

            replica.next = STRAIGHT_LIST_REALLOC(replica.next, sizeof(size_t) * expand);
            STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed");
        }

        replica.elements[replica.size] = list->elements[current];

        replica_current = replica.next + replica.size;
        current = list->next[current];
    }

    STRAIGHT_LIST_FREE(list->elements);
    STRAIGHT_LIST_FREE(list->next);
    (*list) = replica;

    return split;
}

#elif STRAIGHT_LIST_MODE == FINITE_PRERPOCESSOR_STRAIGHT_LIST

#ifndef PREPROCESSOR_STRAIGHT_LIST_SIZE

#define PREPROCESSOR_STRAIGHT_LIST_SIZE (1 << 5)

#elif PREPROCESSOR_STRAIGHT_LIST_SIZE <= 0

#error 'PREPROCESSOR_STRAIGHT_LIST_SIZE' cannot be zero

#endif

/// @note The FINITE_ALLOCATED_STRAIGHT_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the straight_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when there are no holes (meaning 'empty stack' is empty) the straight list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The straight list is a linked list.
typedef struct straight_list {
    size_t size, head; // list size and head index parameter
    size_t empty_size, empty_head; // empty stack's size and head
    STRAIGHT_LIST_DATA_TYPE elements[PREPROCESSOR_STRAIGHT_LIST_SIZE]; // array to store elements
    size_t next[PREPROCESSOR_STRAIGHT_LIST_SIZE]; // array to store next indexes
} straight_list_s;

/// @brief Creates an empty straight list of zero size.
/// @return Straight list structure.
static inline straight_list_s create_straight_list(void) {
    return (straight_list_s) { .empty_head = 0, .empty_size = 0, .head = 0, .size = 0, };
}

/// @brief Destroys the straight list with all its elements and sets size to zero.
/// @param list Pointer to straight list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
/// @note When list is destroyed it can't be used by any other function. To make the list usable create new list on it.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current); // destroy element at current index
        current = list->next[current]; // go to next index
    }

    list->empty_head = list->empty_size = list->head = list->size = 0; // list and its empty stack to zero
}

/// @brief Clears the list of elements. Similar to destroy, but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current); // destroy element at current index
        current = list->next[current]; // go to next index
    }

    // set cleared list's empty stack and head to zero and keep allocated memory
    list->empty_head = list->empty_size = list->head = list->size = 0; // list and its empty stack to zero
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Readonly straight list structure.
/// @param copy Readonly function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    STRAIGHT_LIST_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list.size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    straight_list_s replice = { .head = 0, .size = 0, .empty_head = 0, .empty_size = 0, };

    for (size_t current_list = list.head, * current_copy = &(replice.head); replice.size < list.size; replice.size++) {
        // set element copy to list copy at index i to automatically remove holes from copy
        replice.elements[replice.size] = copy(list.elements[current_list]);
        (*current_copy) = replice.size; // set head and indexes at list copy's next array to proper index

        current_list = list.next[current_list]; // go to next list node
        current_copy = replice.next + replice.size; // go to next copy list's pointer to node
    }

    return replice;
}

/// @brief Checks if list is empty.
/// @param list Readonly straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    STRAIGHT_LIST_ASSERT(list.size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Readonly straight list structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    STRAIGHT_LIST_ASSERT(list.size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");
    // if size is equal to macro size
    return (list.size == PREPROCESSOR_STRAIGHT_LIST_SIZE);
}

/// @brief Iterates through each straight list element.
/// @param list Pointer to readonly straight list structure.
/// @param operate Readonly function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    for (size_t i = 0, current = list->head; i < list->size && operate(list->elements + current, args); ++i) {
        current = list->next[current];
    }
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param list Pointer to readonly straight list structure.
/// @param manage Readonly function pointer to manage the array of elements based on list size and specified arguments.
/// @param args Void pointer arguments for 'manage' function.
/// @note This function can also be used to remove holes in list.
static inline void map_straight_list(straight_list_s * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'manage' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    straight_list_s replica = { .empty_head = 0, .empty_size = 0, .size = 0, .head = 0, };
    for (size_t list_current = list->head, * replica_current = &(replica.head); replica.size < list->size; replica.size++) {
        replica.elements[replica.size] = list->elements[list_current];
        (*replica_current) = replica.size;

        replica_current = replica.next + replica.size;
        list_current = list->next[list_current];
    }

    memcpy(replica.elements, list->elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * replica.size);
    memcpy(replica.next, list->next, sizeof(size_t) * replica.size);
    list->empty_size = list->head = 0;

    manage(list->elements, list->size, args);
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Readonly straight list structure.
/// @param element Readonly element to search in list.
/// @param compare Readonly function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than element parameter.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. Map function can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter pointer is NULL.");

    STRAIGHT_LIST_ASSERT(list.size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    size_t base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        size_t current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare(element, list.elements[current]);

        if (0 == comparison) {
            return true;
        }
        if (0 < comparison) {
            base = list.next[current]; // increment element pointer to next
            limit--; // decrement limit to avoid 'out of bounds' access (if we ignore circularity)
        }
    }

    return false;
}

/// @brief Inserts an element at any index in the list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zeero based index to insert element at.
/// @param element Readonly element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size < PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List reached maximum size.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = list->next + (*current);
    }

    size_t push = list->size;
    if (list->empty_size) {
        push = list->empty_head;
        list->empty_head = list->next[list->empty_head];
        list->empty_size--;
    }
    memcpy(list->elements + push, &element, sizeof(STRAIGHT_LIST_DATA_TYPE));
    list->next[push] = (*current);
    (*current) = push;

    list->size++;
}

/// @brief Gets element at any index in the list.
/// @param list Readonly straight list structure.
/// @param index Readonly zero based index of element in list.
/// @return Element at index in list.
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    STRAIGHT_LIST_ASSERT(list.size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t current = list.head;
    for (size_t i = 0; i < index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Removes first element in straight list that matches parameter element comparison.
/// @param list Pointer to straight list structure.
/// @param element Readonly element to compare and remove from list.
/// @param compare Readonly function pointer that compares element parameter to elements in list. Returns zero if equal.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < list->size; ++i) {
        if (0 != compare(list->elements[(*current)], element)) { // early continue in order to remove one needless nesting level
            current = list->next + (*current);
            continue;
        }

        list->size--;
        STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)];

        const size_t temp = (*current);
        (*current) = list->next[(*current)];
        if (temp != list->size) { // if current index is not at last element in elements array add to empty stack
            // push empty index to 'empty stack'
            list->next[temp] = list->empty_head;
            list->empty_head = temp;
            list->empty_size++;
        }

        if (!list->size) { // if list is empty set empty stack elements to zero
            list->empty_head = list->empty_size = 0;
        }

        return found;
    }

    STRAIGHT_LIST_ASSERT(0 && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned, since the function returns the removed element, element can contain allocated memory
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index in list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = list->next + (*current);
    }

    list->size--;
    STRAIGHT_LIST_DATA_TYPE removed = list->elements[(*current)];

    const size_t temp = (*current);
    (*current) = list->next[(*current)];
    if (!list->size) {
        list->empty_size = 0;
    } else if (temp != list->size) { // if current index is not at last element in elements array add to empty stack
        // push empty index to 'empty stack'
        list->next[temp] = list->empty_head;
        list->empty_head = temp;
        list->empty_size++;
    }

    return removed;
}

/// @brief Reverses list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t previous = 0;
    for (size_t i = 0, current = list->head, next; i < list->size; ++i, previous = current, current = next) {
        next = list->next[current];
        list->next[current] = previous;
    }
    list->head = previous;
}

/// @brief Splices source into destination list while clearing source list.
/// @param destination Rescricted pointer to straight list structure to splice into.
/// @param source Rescricted pointer to straight list structure to splice from.
/// @param index Readonly zero-based index at destination list to splice source list into.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index) {
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(destination->size + source->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    STRAIGHT_LIST_ASSERT(destination->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");
    STRAIGHT_LIST_ASSERT(source->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t * destination_current = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        destination_current = destination->next + (*destination_current);
    }

    size_t * last_source = &(source->head);
    for (; source->size && destination->empty_size; source->size--, destination->size++, destination->empty_size--) {
        memcpy(destination->elements + destination->empty_head, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));

        const size_t temp = destination->empty_head; // save empty head index as tempt to not lose it
        destination->empty_head = destination->next[destination->empty_head]; // set empty head to next empty index

        destination->next[temp] = (*destination_current); // set temp's next index to index at current pointer
        (*destination_current) = temp; // set index at current pointer, previous' next index, to temp

        destination_current = destination->next + (*destination_current);
        last_source = source->next + (*last_source);
    }

    for (; source->size; source->size--, destination->size++) {
        memcpy(destination->elements + destination->size, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->next[destination->size] = (*destination_current);
        (*destination_current) = destination->size;

        destination_current = destination->next + (*destination_current);
        last_source = source->next + (*last_source);
    }

    source->empty_size = source->head = 0;
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Non-zero size of new split list.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(size && "[ERROR] Split size can't be zero.");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    STRAIGHT_LIST_ASSERT(list->size <= PREPROCESSOR_STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    straight_list_s replica = { .empty_head = 0, .empty_size = 0, .size = 0, .head = 0, };
    straight_list_s split = { .empty_head = 0, .empty_size = 0, .size = 0, .head = 0, };

    size_t list_current = list->head;
    size_t * replica_current = &(replica.head);
    for (;replica.size < index; replica.size++) {
        replica.elements[replica.size] = list->elements[list_current];
        (*replica_current) = replica.size;

        replica_current = replica.next + replica.size;
        list_current = list->next[list_current];
    }

    for (size_t * split_current = &(split.head); split.size < size; split.size++) {
        split.elements[split.size] = list->elements[list_current];
        (*split_current) = split.size;

        split_current = split.next + split.size;
        list_current = list->next[list_current];
    }

    for (size_t i = index + size; i < list->size; ++i, replica.size++) {
        replica.elements[replica.size] = list->elements[list_current];
        (*replica_current) = replica.size;

        replica_current = replica.next + replica.size;
        list_current = list->next[list_current];
    }

    list->empty_size = list->head = 0;
    memcpy(list->elements, replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * replica.size);
    memcpy(list->next, replica.next, sizeof(size_t) * replica.size);

    list->size -= size;

    return split;
}

#endif

#else

#error Cannot include multiple headers in same unit.

#endif // STRAIGHT_LIST_H
