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

#ifndef FORWARD_LIST_DATA_TYPE

/// @brief Element datatype macro that can be changed  via '#define FORWARD_LIST_DATA_TYPE [datatype]'.
#define FORWARD_LIST_DATA_TYPE void*

#endif

#ifndef FORWARD_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief Assertion macro that can be changed  via '#define FORWARD_LIST_ALLOC [assert]'.
#define FORWARD_LIST_ASSERT assert

#endif

#ifndef FORWARD_LIST_ALLOC

/// @brief Memory allocation macro that can be changed via '#define FORWARD_LIST_ALLOC [allocator]'.
#define FORWARD_LIST_ALLOC malloc

#endif

#ifndef FORWARD_LIST_REALLOC

/// @brief Memory reallocation macro that can be changed via '#define FORWARD_LIST_REALLOC [reallocator]'.
#define FORWARD_LIST_REALLOC realloc

#endif

#ifndef FORWARD_LIST_FREE

/// @brief Memory freeing macro that can be changed via '#define FORWARD_LIST_FREE [free]'.
#define FORWARD_LIST_FREE free

#endif

/// @brief Function pointer to create a deep/shallow copy for forward list element.
typedef FORWARD_LIST_DATA_TYPE (*copy_forward_list_fn)    (const FORWARD_LIST_DATA_TYPE);
/// @brief Function pointer to destroy/free an element for forward list element.
typedef void                   (*destroy_forward_list_fn) (FORWARD_LIST_DATA_TYPE *);
/// @brief Function pointer to comapre two forward list elements. Returns zero if they're equal, a negative number if
/// 'less than', else a positive number if 'more than'.
typedef int                    (*compare_forward_list_fn) (const FORWARD_LIST_DATA_TYPE, const FORWARD_LIST_DATA_TYPE);
/// @brief Function pointer to operate on a single forward list element based on generic arguments.
typedef bool                   (*operate_forward_list_fn) (FORWARD_LIST_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of forward list elements based on generic arguments.
typedef void                   (*manage_forward_list_fn)  (FORWARD_LIST_DATA_TYPE *, const size_t, void *);

#if   FORWARD_LIST_MODE == INFINITE_ALLOCATED_FORWARD_LIST

/// @brief Forward list node with element and pointer to next node.
struct forward_list_node {
    FORWARD_LIST_DATA_TYPE element; // current element
    struct forward_list_node * next; // pointer to next node
};

/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct forward_list {
    size_t size; // size of forward list
    struct forward_list_node * tail; // pointer to tail/last node
} forward_list_s;

/// @brief Creates an empty forward list of zero size.
/// @return Forward list structure.
static inline forward_list_s create_forward_list(void) {
    return (forward_list_s) { 0 }; // sets forward list to zero
}

/// @brief Destroys the forward list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct forward_list_node * previous = list->tail; // previous pointer since order does not matter in deletion
    for (size_t s = 0; s < list->size; ++s) { // iterates for each element
        if (destroy) { // if destroy function pointer is specified then destroys element
            destroy(&(previous->element));
        }

        struct forward_list_node * temp = previous; // temporary node pointer to not lose it while freeing
        previous = previous->next; // go to next node
        FORWARD_LIST_FREE(temp); // frees temporary node
    }

    *list = (forward_list_s) { 0 }; // sets destroyed list to zero
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_forward_list(forward_list_s * list, const size_t index, const FORWARD_LIST_DATA_TYPE element) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    FORWARD_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    // creates node and copies element parameter into the node element
    struct forward_list_node * temp = FORWARD_LIST_ALLOC(sizeof(struct forward_list_node));
    FORWARD_LIST_ASSERT(temp && "[ERROR] Memory allocation failed.");
    memcpy(&(temp->element), &element, sizeof(FORWARD_LIST_DATA_TYPE));

    if (list->tail == NULL) { // if list is empty
        // push element to tail and make it circular (if list has size one then head element is also its tail)
        list->tail = temp->next = temp;
    } else if (index == list->size) { // else if index is equal to size then append to end of list (list size is equal to index to append last element)
        temp->next = list->tail->next; // temporary node's next pointer points to tail's next node (i. e. list's head)
        list->tail = list->tail->next = temp; // change tail's next node to temp and make temp node the new tail
    } else { // else node is between first and last node
        struct forward_list_node * previous = list->tail; // get tail node since we need the node at the position previous to index node
        for (size_t i = 0; i < index; ++i) { // iterates to node previous to node at index
            previous = previous->next;
        }
        temp->next = previous->next; // temp points to previous' next pointer (i. e. to node at index position)
        previous->next = temp; // previous' next pointer is assigned temp (so no pointer to pointer needed)
    }

    list->size++;
}

/// @brief Removes first element in forward list based on element parameter comparison.
/// @param list Pointer to forward list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");

    struct forward_list_node * previous = list->tail; // pointer to previous
    for (size_t s = 0; s < list->size; ++s) {
        struct forward_list_node * current = previous->next; // since we need to start at nodes next to tail we check current node instead of previous
        // compares element parameter to current node's element, if compare function not is specified (is NULL) then memcmp is used
        const int comparison = compare ? compare(current->element, element) : memcmp(&(current->element), &element, sizeof(FORWARD_LIST_DATA_TYPE));
        if (0 == comparison) { // if elements are the 'same' based on comparison, i. e. comparison is zero
            // copy removed element from node as temporary to return and not lose it
            list->size--;
            FORWARD_LIST_DATA_TYPE found = current->element;

            if (current == list->tail) { // if current is the last element
                list->tail = (list->size) ? previous : NULL; // if list still has elements then tail will become the previous pointer else NULL
            }
            previous->next = current->next; // remove pointer to current in list by changing previous' next pointer to current's next
            FORWARD_LIST_FREE(current);

            return found; // returns first removed found element
        }
        previous = previous->next; // go to next previous node
    }

    FORWARD_LIST_ASSERT(0 && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    exit(EXIT_FAILURE); // and exit failure is returned, since the function returns the removed element, element can contain allocated memory
}

/// @brief Removes element at index in forward list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->tail && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct forward_list_node * previous = list->tail; // previous is used in order to make removals easier
    for (size_t i = 0; i < index; ++i) { // iterate until node previous to node at index is reached
        previous = previous->next;
    }
    struct forward_list_node * current = previous->next; // save current node pointer

    list->size--;
    FORWARD_LIST_DATA_TYPE found = current->element;

    previous->next = current->next; // remove pointer to current in list by changing previous' next pointer to current's next

    FORWARD_LIST_FREE(current); // free current pointer

    if (index == list->size) { // if last element is removed
        list->tail = (list->size) ? previous : NULL; // if list is not empty tail/last node becomes previous, else NULL
    }

    return found;
}

/// @brief Reverses forward list.
/// @param list Pointer to forward list structure.
static inline void reverse_forward_list(forward_list_s * list) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    if (list->tail == NULL) { // we must first check if list in not empty/tail is not NULL
        return;
    }

    struct forward_list_node * previous = list->tail;
    struct forward_list_node * current = previous->next;
    struct forward_list_node * next = current->next;
    list->tail = current; // since head changes to tail, tail also changes to head
    for (size_t i = 0; i < list->size; ++i) {
        current->next = previous;
        previous = current;
        current = next;
        next = next->next;
    }
}

/// @brief Shifts forward list to next number of elements.
/// @param list Pointer to forward list structure.
/// @param shift Nonnegative integer to shift list by.
static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->tail = list->tail->next; // changes tail to next/head node
    }
}

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to forward list structure to splice into.
/// @param source Pointer to forward list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
static inline void splice_forward_list(forward_list_s * restrict destination, forward_list_s * restrict source, const size_t index) {
    FORWARD_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    FORWARD_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    struct forward_list_node * previous = destination->tail;
    for (size_t i = 0; index != destination->size && i < index; ++i) { // iterate to node previous to index node or not if index is to the node after last
        previous = previous->next;
    }

    if (previous && source->tail) { // if previous points to memory/is not NULL and source tail also points to memory/is not NULL
        struct forward_list_node * swap = previous->next; // store previous' next node in swap
        previous->next = source->tail->next; // change previous' next pointer to source's head
        source->tail->next = swap; // change source tail's next pointer to swap or saved previous' next node
    }
    // if index points to location after last destination node (concatenation) and source points to memory (avoids adding NULL pointer since function allows splicing empty source list)
    if (index == destination->size && source->tail) {
        destination->tail = source->tail;
    }
    destination->size += source->size; // increment destination's size by source

    *source = (forward_list_s) { 0 }; // destroy only source list (since nodes and elements became part of destionation)
}

/// @brief Splits list and returns new list with specified elements. Since forward list is circular the new list can
/// include elements beyond old list's last node.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size) {
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    struct forward_list_node * list_previous = list->tail;
    for (size_t i = 0; i < index; ++i) { // iterate to node previous to node at index
        list_previous = list_previous->next;
    }
    if ((index + size) >= list->size) { // if tail node becomes part of split list new tail node will be the node previous to index/first-split node
        list->tail = list_previous;
    }

    forward_list_s split = { .size = size, .tail = NULL }; // create new split list to return

    struct forward_list_node * last_added = NULL; // save last added node outside loop to change split list's tail into, since loop treats tail as head
    struct forward_list_node ** split_previous = &(split.tail);
    for (size_t i = 0; i < size; ++i) { // split's tail is treated as the head node and gets changed to tail after loop finishes via last_added
        struct forward_list_node * current = list_previous->next;
        (*split_previous) = last_added = current; // previous index node's next is part of split
        list_previous->next = list_previous->next->next; // remove current from list
        (*split_previous)->next = split.tail; // every new node added needs to point to the tail as next node

        split_previous = &((*split_previous)->next);
    }
    split.tail = last_added; // makes the last node added to split list the tail, or NULL if size parameter is zero

    list->size -= size; // shorten parameter list by split size
    if (!list->size) { // if list size becomes zero list tail will be NULL/empty
        list->tail = NULL;
    }

    return split;
}

/// @brief Gets element at index.
/// @param list Forward list structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
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

/// @brief Checks if list is empty.
/// @param list Forward list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Forward list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_forward_list(const forward_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero and negating it makes function return true only if full
    return !(~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Forward list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
static inline forward_list_s copy_forward_list(const forward_list_s list, const copy_forward_list_fn copy) {
    forward_list_s list_copy = { .tail = NULL, .size = list.size };

    struct forward_list_node const * previous_list = list.tail;
    struct forward_list_node ** previous_copy = &(list_copy.tail); // double pointer since this also works on copying forward list
    for (size_t i = 0; i < list.size; ++i) {
        // create new node and copy element from source list based on copy function pointer parameter
        struct forward_list_node * node = FORWARD_LIST_ALLOC(sizeof(struct forward_list_node));
        FORWARD_LIST_ASSERT(node && "[ERROR] Memory allocation failed.");
        node->element = copy ? copy(previous_list->element) : previous_list->element; // if copy is specified call it, else just assign it to variable

        (*previous_copy) = node; // change previous copy's node pointer to node
        node->next = list_copy.tail; // make node's next pointer point to list copy's tail

        previous_list = previous_list->next; // go to next list node
        previous_copy = &((*previous_copy)->next); // go to next copy list's pointer to node
    }

    return list_copy;
}

/// @brief Clears the list of elements.  Similar to 'destroy_forward_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list.
static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    // in this case clearing is the same as destroying the list
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

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to forward list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering WILL remain.
/// This may not apply for other forward list 'all_forward_list' implementations and a note will reflect that.
static inline void all_forward_list(forward_list_s const * list, const manage_forward_list_fn manage, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    // create continuos array to store lis elements
    FORWARD_LIST_DATA_TYPE * elements_array = FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * list->size);
    FORWARD_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct forward_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next; // go to next node to add elements from head instead of from tail
        elements_array[i] = previous->element;
    }

    manage(elements_array, list->size, args); // manage function that takes an array as argument, its size and argument void pointer

    previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) { // loop to re-add new list element's ordering
        previous = previous->next;
        previous->element = elements_array[i];
    }
    FORWARD_LIST_FREE(elements_array); // free elements array
}

/// @brief Performs a binary search on sorted forward list.
/// @param list Forward list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'all_forward_list' can be used to sort the list.
static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    // this implementation is based on similar array based binary search algorithm: https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    struct forward_list_node const * base = list.tail; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        struct forward_list_node const * current = base->next; // start from next element to move from tail and to ignore alread compared elements
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = current->next;
        }

        const int comparison = compare ? compare(element, current->element) : memcmp(&element, &(current->element), sizeof(FORWARD_LIST_DATA_TYPE));

        if (comparison == 0) {
            return true;
        }
        if (comparison > 0) {
            base = current; // increment element pointer to next
            limit--; // decrement limit to avoid 'out of bounds' access (if we ignore circularity)
        }
    }

    return false;
}

/// @brief Iterates through forward list elements without changing list ordering.
/// @param list Pointer to forward list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_forward_list(forward_list_s const * list, const operate_forward_list_fn operate, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct forward_list_node * previous = list->tail;
    for (size_t i = 0; i < list->size; ++i) {
        previous = previous->next; // make sure to start from list's head

        if (!operate(&previous->element, args)) { // if operate returns false thene stop loop
            return;
        }
    }
}

#elif FORWARD_LIST_MODE == FINITE_ALLOCATED_FORWARD_LIST

/// @note The FINITE_ALLOCATED_FORWARD_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the forward_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct forward_list {
    size_t size, empty_size, tail, empty_head, max;
    FORWARD_LIST_DATA_TYPE * elements;
    size_t * next;
} forward_list_s;

/// @brief Creates an empty forward list of zero size.
/// @param max Maximum positive nonzero size of forward list.
/// @return Forward list structure.
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

/// @brief Destroys the forward list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; destroy && s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    FORWARD_LIST_FREE(list->elements);
    FORWARD_LIST_FREE(list->next);
    *list = (forward_list_s) { 0 };
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
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

/// @brief Removes first element in forward list based on element parameter comparison.
/// @param list Pointer to forward list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        size_t current = list->next[previous];
        const int comparison = compare ? compare(list->elements[current], element) : memcmp(list->elements + current, &element, sizeof(FORWARD_LIST_DATA_TYPE));
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

/// @brief Removes element at index in forward list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");
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

/// @brief Reverses forward list.
/// @param list Pointer to forward list structure.
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

/// @brief Shifts forward list to next number of elements.
/// @param list Pointer to forward list structure.
/// @param shift Nonnegative integer to shift list by.
static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->tail = list->next[list->tail];
    }
}

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to forward list structure to splice into.
/// @param source Pointer to forward list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
/// @param max New maximum positive nonzero size of destination list.
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
    for (size_t i = 0; index != size_dest && i < index; ++i) {
        previous_dest = destination->next[previous_dest];
    }

    size_t previous_src = source->tail;
    while (source->size && destination->empty_size) {
        previous_src = source->next[previous_src];
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
        previous_src = source->next[previous_src];
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

/// @brief Splits old list and returns new list with specified elements. Since forward list is circular the new list can
/// include elements beyond old list's last node.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @param max Maximum positive nonzero size of returned split list.
/// @return New split list.
static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size, const size_t max) {
    FORWARD_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    forward_list_s split = {
        .elements = FORWARD_LIST_ALLOC(max * sizeof(FORWARD_LIST_DATA_TYPE)),
        .next = FORWARD_LIST_ALLOC(max * sizeof(size_t)),
        .empty_head = 0, .max = max, .empty_size = 0, .size = size, .tail = 0
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
        const size_t current = list->next[previous];

        const size_t mod = i % size;
        memcpy(split.elements + mod, list->elements + current, sizeof(FORWARD_LIST_DATA_TYPE));
        split.next[i - 1] = mod;
        list->size--;

        list->next[previous] = list->next[current];
        if (list->next[current] != list->size) { // push empty index to 'empty stack'
            list->next[current] = list->empty_head;
            list->empty_head = current;
            list->empty_size++;
        }
    }

    return split;
}

/// @brief Gets element at index.
/// @param list Forward list structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.elements && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.next && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Checks if list is empty.
/// @param list Forward list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Forward list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_forward_list(const forward_list_s list) {
    return !(list.size < list.max && ~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Forward list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
static inline forward_list_s copy_forward_list(const forward_list_s list, const copy_forward_list_fn copy) {
    const forward_list_s list_copy = {
        .elements = FORWARD_LIST_ALLOC(list.max * sizeof(FORWARD_LIST_DATA_TYPE)),
        .next = FORWARD_LIST_ALLOC(list.max * sizeof(size_t)),
        .empty_head = 0, .empty_size = 0, .max = list.max, .size = list.size, .tail = 0,
    };
    FORWARD_LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    FORWARD_LIST_ASSERT(list_copy.next && "[ERROR] Memory allocation failed.");

    size_t previous = list.tail;
    for (size_t i = 1; list.size && i <= list.size; ++i) {
        previous = list.next[previous];

        const size_t mod = i % list.size;
        list_copy.elements[mod] = copy ? copy(list.elements[previous]) : list.elements[previous];
        list_copy.next[i - 1] = mod;
    }

    return list_copy;
}

/// @brief Clears the list of elements. Similar to 'destroy_forward_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list.
static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; destroy && s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    list->empty_head = list->empty_size = list->size = list->tail = 0;
}

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to forward list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering may NOT remain
/// (it may change if there are holes in the list). This may not apply for other forward list 'all_forward_list'
/// implementations and a note will reflect that.
static inline void all_forward_list(forward_list_s * list, const manage_forward_list_fn manage, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (list->empty_size) { // removes holes at the expense of breaking the list
        stack_size--;

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

        list->empty_size--;
    }

    manage(list->elements, list->size, args);

    list->tail = list->size ? list->size - 1 : 0;
    for (size_t i = 1; list->size && i <= list->size; ++i) {
        const size_t mod = i % list->size;
        list->next[i - 1] = mod;
    }
}

/// @brief Performs a binary search on sorted forward list.
/// @param list Forward list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if 'less than',
/// positive if 'greater than'.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'all_forward_list' can be used to sort the list.
static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    size_t base = list.tail;
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        size_t current = list.next[base]; // start from next element to move from tail and to ignore compared element
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(element, list.elements[current]) : memcmp(&element, list.elements + current, sizeof(FORWARD_LIST_DATA_TYPE));

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

/// @brief Iterates through forward list elements without changing list ordering.
/// @param list Pointer to forward list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_forward_list(forward_list_s const * list, const operate_forward_list_fn operate, void * args) {
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

/// @brief Chunk size to expand/shrink elements array.
#define REALLOC_FORWARD_LIST_CHUNK (1 << 10)

#elif REALLOC_FORWARD_LIST_CHUNK <= 0

#error 'REALLOC_FORWARD_LIST_CHUNK' cannot be zero

#endif

/// @note The INFINITE_REALLOC_FORWARD_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the forward_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct forward_list {
    size_t size, empty_size, tail, empty_head;
    FORWARD_LIST_DATA_TYPE * elements;
    size_t * next;
} forward_list_s;

/// @brief Creates an empty forward list of zero size.
/// @return Forward list structure.
static inline forward_list_s create_forward_list(void) {
    return (forward_list_s) { 0 };
}

/// @brief Destroys the forward list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; destroy && s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    FORWARD_LIST_FREE(list->elements);
    FORWARD_LIST_FREE(list->next);
    *list = (forward_list_s) { 0 };
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
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

/// @brief Removes first element in forward list based on element parameter comparison.
/// @param list Pointer to forward list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t current = list->next[previous];
        const int comparison = compare ? compare(list->elements[current], element) : memcmp(list->elements + current, &element, sizeof(FORWARD_LIST_DATA_TYPE));
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

/// @brief Removes element at index in forward list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");
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

/// @brief Reverses forward list.
/// @param list Pointer to forward list structure.
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

/// @brief Shifts forward list to next number of elements.
/// @param list Pointer to forward list structure.
/// @param shift Nonnegative integer to shift list by.
static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->tail = list->next[list->tail];
    }
}

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to forward list structure to splice into.
/// @param source Pointer to forward list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
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

    const size_t new_size = destination->size + source->size;
    if (new_size) {
        const size_t split_chunk = new_size - (new_size % REALLOC_FORWARD_LIST_CHUNK) + REALLOC_FORWARD_LIST_CHUNK;
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

/// @brief Splits old list and returns new list with specified elements. Since forward list is circular the new list can
/// include elements beyond old list's last node.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size) {
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    forward_list_s split = { .size = size, .elements = NULL, .empty_head = 0, .empty_size = 0, .next = NULL, .tail = 0, };

    if (size) {
        const size_t capacity = size - (size % REALLOC_FORWARD_LIST_CHUNK) + REALLOC_FORWARD_LIST_CHUNK;
        split.elements = FORWARD_LIST_ALLOC(sizeof(FORWARD_LIST_DATA_TYPE) * capacity);
        split.next = FORWARD_LIST_ALLOC(sizeof(size_t) * capacity);

        FORWARD_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");
        FORWARD_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed.");
    }

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    if ((index + size) >= list->size) { // if tail node becomes part of split list new tail node will be the node previous to index/first-split node
        list->tail = previous;
    }

    for (size_t i = 1; size && i <= size; ++i) {
        const size_t current = list->next[previous];

        const size_t mod = i % size;
        memcpy(split.elements + mod, list->elements + current, sizeof(FORWARD_LIST_DATA_TYPE));
        split.next[i - 1] = mod;
        list->size--;

        list->next[previous] = list->next[current];
        if (list->next[current] != list->size) { // push empty index to 'empty stack'
            list->next[current] = list->empty_head;
            list->empty_head = current;
            list->empty_size++;
        }
    }

    if (!list->size) {
        FORWARD_LIST_FREE(list->elements);
        FORWARD_LIST_FREE(list->next);
        *list = (forward_list_s) { 0 };
    }

    return split;
}

/// @brief Gets element at index.
/// @param list Forward list structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.elements && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.next && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) { // equal to index to take tail into account
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Checks if list is empty.
/// @param list Forward list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Forward list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_forward_list(const forward_list_s list) {
    return !(~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Forward list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
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
    for (size_t i = 1; list.size && i <= list.size; ++i) {
        previous = list.next[previous];

        const size_t mod = i % list.size;
        list_copy.elements[mod] = copy ? copy(list.elements[previous]) : list.elements[previous];
        list_copy.next[i - 1] = mod;
    }

    return list_copy;
}

/// @brief Clears the list of elements. Similar to 'destroy_forward_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list.
static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; destroy && s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    FORWARD_LIST_FREE(list->elements);
    FORWARD_LIST_FREE(list->next);
    *list = (forward_list_s) { 0 };
}

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to forward list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering may NOT remain
/// (it may change if there are holes in the list). This may not apply for other forward list 'all_forward_list'
/// implementations and a note will reflect that.
static inline void all_forward_list(forward_list_s * list, const manage_forward_list_fn manage, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (list->empty_size) { // removes holes at the expense of breaking the list
        stack_size--;

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

        list->empty_size--;
    }

    manage(list->elements, list->size, args);

    list->tail = list->size ? list->size - 1 : 0;
    for (size_t i = 1; list->size && i <= list->size; ++i) {
        const size_t mod = i % list->size;
        list->next[i - 1] = mod;
    }
}

/// @brief Performs a binary search on sorted forward list.
/// @param list Forward list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if 'less than',
/// positive if 'greater than'.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'all_forward_list' can be used to sort the list.
static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    size_t base = list.tail;
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        size_t current = list.next[base]; // start from next element to move from tail and to ignore compared element
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(element, list.elements[current]) : memcmp(&element, list.elements + current, sizeof(FORWARD_LIST_DATA_TYPE));

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

/// @brief Iterates through forward list elements without changing list ordering.
/// @param list Pointer to forward list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_forward_list(forward_list_s const * list, const operate_forward_list_fn operate, void * args) {
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

#elif PREPROCESSOR_FORWARD_LIST_SIZE <= 0

#error 'PREPROCESSOR_FORWARD_LIST_SIZE' cannot be zero

#endif

/// @note The FINITE_PRERPOCESSOR_FORWARD_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the forward_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the forward list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The forward list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct forward_list {
    size_t size, empty_size, tail, empty_head;
    FORWARD_LIST_DATA_TYPE elements[PREPROCESSOR_FORWARD_LIST_SIZE];
    size_t next[PREPROCESSOR_FORWARD_LIST_SIZE];
} forward_list_s;

/// @brief Creates an empty forward list of zero size.
/// @return Forward list structure.
static inline forward_list_s create_forward_list(void) {
    const forward_list_s list = { .tail = 0, .size = 0, .empty_head = 0, .empty_size = 0, };

    return list;
}

/// @brief Destroys the forward list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; destroy && s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    list->empty_head = list->empty_size = list->size = list->tail = 0;
}

/// @brief Inserts an element to any place in the list. Forward list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
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

/// @brief Removes first element in forward list based on element parameter comparison.
/// @param list Pointer to forward list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_first_forward_list(forward_list_s * list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    FORWARD_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");

    size_t previous = list->tail;
    for (size_t s = 0; s < list->size; ++s) {
        const size_t current = list->next[previous];
        const int comparison = compare ? compare(list->elements[current], element) : memcmp(list->elements + current, &element, sizeof(FORWARD_LIST_DATA_TYPE));
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

/// @brief Removes element at index in forward list.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline FORWARD_LIST_DATA_TYPE remove_at_forward_list(forward_list_s * list, const size_t index) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    FORWARD_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
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

/// @brief Reverses forward list.
/// @param list Pointer to forward list structure.
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

/// @brief Shifts forward list to next number of elements.
/// @param list Pointer to forward list structure.
/// @param shift Nonnegative integer to shift list by.
static inline void shift_forward_list(forward_list_s * list, const size_t shift) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    for (size_t s = 0; list->size && (s < shift); ++s) {
        list->tail = list->next[list->tail];
    }
}

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to forward list structure to splice into.
/// @param source Pointer to forward list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
static inline void splice_forward_list(forward_list_s * restrict destination, forward_list_s * restrict source, const size_t index) {
    FORWARD_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    FORWARD_LIST_ASSERT(destination->size + source->size <= PREPROCESSOR_FORWARD_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    FORWARD_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    const size_t size_dest = destination->size;

    size_t previous_dest = destination->tail;
    for (size_t i = 0; index != size_dest && i < index; ++i) {
        previous_dest = destination->next[previous_dest];
    }

    size_t previous_src = source->tail;
    while (source->size && destination->empty_size) {
        previous_src = source->next[previous_src];
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
        previous_src = source->next[previous_src];
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

/// @brief Splits old list and returns new list with specified elements. Since forward list is circular the new list can
/// include elements beyond old list's last node.
/// @param list Pointer to forward list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline forward_list_s split_forward_list(forward_list_s * list, const size_t index, const size_t size) {
    FORWARD_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    FORWARD_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    FORWARD_LIST_ASSERT(index <= list->size && !(index && (index == list->size)) && "[ERROR] Can only split at index less than list size, or equal to if list size is zero.");

    forward_list_s split = { .empty_head = 0, .empty_size = 0, .size = size, .tail = 0 };

    size_t previous = list->tail;
    for (size_t i = 0; i < index; ++i) {
        previous = list->next[previous];
    }
    if ((index + size) >= list->size) { // if tail node becomes part of split list new tail node will be the node previous to index/first-split node
        list->tail = previous;
    }

    for (size_t i = 1; size && i <= size; ++i) {
        const size_t current = list->next[previous];

        const size_t mod = i % size;
        memcpy(split.elements + mod, list->elements + current, sizeof(FORWARD_LIST_DATA_TYPE));
        split.next[i - 1] = mod;
        list->size--;

        list->next[previous] = list->next[current];
        if (list->next[current] != list->size) { // push empty index to 'empty stack'
            list->next[current] = list->empty_head;
            list->empty_head = current;
            list->empty_size++;
        }
    }

    return split;
}

/// @brief Gets element at index.
/// @param list Forward list structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline FORWARD_LIST_DATA_TYPE get_forward_list(const forward_list_s list, const size_t index) {
    FORWARD_LIST_ASSERT(list.elements && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.next && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    FORWARD_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.tail;
    for (size_t i = 0; index != list.size - 1 && i <= index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Checks if list is empty.
/// @param list Forward list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_forward_list(const forward_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Forward list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_forward_list(const forward_list_s list) {
    return !(list.size < PREPROCESSOR_FORWARD_LIST_SIZE && ~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Forward list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
static inline forward_list_s copy_forward_list(const forward_list_s list, const copy_forward_list_fn copy) {
    forward_list_s list_copy = { .empty_head = 0, .empty_size = 0, .size = list.size, .tail = 0, };

    size_t previous = list.tail;
    for (size_t i = 1; list.size && i <= list.size; ++i) {
        previous = list.next[previous];

        const size_t mod = i % list.size;
        list_copy.elements[mod] = copy ? copy(list.elements[previous]) : list.elements[previous];
        list_copy.next[i - 1] = mod;
    }

    return list_copy;
}

/// @brief Clears the list of elements. Similar to 'destroy_forward_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in forward list.
static inline void clear_forward_list(forward_list_s * list, const destroy_forward_list_fn destroy) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t previous = list->tail;
    for (size_t s = 0; destroy && s < list->size; ++s) {
        destroy(list->elements + previous);
        previous = list->next[previous];
    }

    list->empty_head = list->empty_size = list->size = list->tail = 0;
}

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to forward list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering may NOT remain
/// (it may change if there are holes in the list). This may not apply for other forward list 'all_forward_list'
/// implementations and a note will reflect that.
static inline void all_forward_list(forward_list_s * list, const manage_forward_list_fn manage, void * args) {
    FORWARD_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    FORWARD_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (list->empty_size) { // removes holes at the expense of breaking the list and turning it into an array
        stack_size--;

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

        list->empty_size--;
    }

    manage(list->elements, list->size, args);

    list->tail = list->size ? list->size - 1 : 0;
    for (size_t i = 1; list->size && i <= list->size; ++i) {
        const size_t mod = i % list->size;
        list->next[i - 1] = mod;
    }
}

/// @brief Performs a binary search on sorted forward list.
/// @param list Forward list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if 'less than',
/// positive if 'greater than'.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'all_forward_list' can be used to sort the list.
static inline bool binary_search_forward_list(const forward_list_s list, const FORWARD_LIST_DATA_TYPE element, const compare_forward_list_fn compare) {
    size_t base = list.tail;
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        size_t current = list.next[base]; // start from next element to move from tail and to ignore compared element
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(element, list.elements[current]) : memcmp(&element, list.elements + current, sizeof(FORWARD_LIST_DATA_TYPE));

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

/// @brief Iterates through forward list elements without changing list ordering.
/// @param list Pointer to forward list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
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
