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

#ifndef CIRCULAR_LIST_DATA_TYPE

/// @brief Element datatype macro that can be changed  via '#define CIRCULAR_LIST_DATA_TYPE [datatype]'.
#define CIRCULAR_LIST_DATA_TYPE void*

#endif

#ifndef CIRCULAR_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief Assertion macro that can be changed  via '#define CIRCULAR_LIST_ASSERT [assert]'.
#define CIRCULAR_LIST_ASSERT assert

#endif

/// @brief Function pointer to create a deep/shallow copy for circular list element.
typedef CIRCULAR_LIST_DATA_TYPE (*copy_circular_list_fn)    (const CIRCULAR_LIST_DATA_TYPE element);
/// @brief Function pointer to destroy/free an element for circular list element.
typedef void                    (*destroy_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE * element);
/// @brief Function pointer to comapre two circular list elements. Returns zero if they're equal, a negative number if
/// 'less than', else a positive number if 'more than'.
typedef int                     (*compare_circular_list_fn) (const CIRCULAR_LIST_DATA_TYPE one, const CIRCULAR_LIST_DATA_TYPE two);
/// @brief Function pointer to operate on a single circular list element based on generic arguments.
typedef bool                    (*operate_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of circular list elements based on generic arguments.
typedef void                    (*manage_circular_list_fn)  (CIRCULAR_LIST_DATA_TYPE * array, const size_t size, void * args);

#ifndef CIRCULAR_LIST_SIZE

#define CIRCULAR_LIST_SIZE (1 << 10)

#elif CIRCULAR_LIST_SIZE <= 0

#error 'CIRCULAR_LIST_SIZE' cannot be zero

#endif

/// @note The FINITE_PRERPOCESSOR_CIRCULAR_LIST_MODE is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the circular_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when therea are no holes (meaning 'empty stack' is empty) the circular list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The circular list is a circular linked list which allows appending and getting the last element without
/// iterating through the entire list.
typedef struct circular_list {
    size_t next[CIRCULAR_LIST_SIZE];
    CIRCULAR_LIST_DATA_TYPE elements[CIRCULAR_LIST_SIZE];
    size_t size, tail; // list size and tail index parameter
    size_t empty_size, empty_head; // empty stack's size and head
} circular_list_s;

/// @brief Creates an empty circular list of zero size.
/// @return Circular list structure.
static inline circular_list_s create_circular_list(void) {
    return (circular_list_s) { .tail = 0, .size = 0, .empty_head = 0, .empty_size = 0, };
}

/// @brief Destroys the list and all its elements.
/// @param list Pointer to list structure.
/// @param destroy Function pointer to destroy each element in list.
static inline void destroy_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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
static inline circular_list_s copy_circular_list(const circular_list_s * list, const copy_circular_list_fn copy) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

    circular_list_s replica = { .empty_head = 0, .empty_size = 0, .size = 0, .tail = 0, };

    size_t previous = list->tail;
    for (size_t * current_replica = &(replica.tail); replica.size < list->size; replica.size++) {
        (*current_replica) = replica.size;

        replica.elements[replica.size] = copy(list->elements[previous]);

        previous = list->next[previous];
        current_replica = replica.next + replica.size;
        (*current_replica) = 0;
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list List structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_circular_list(const circular_list_s * list) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

    return (list->size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_circular_list(const circular_list_s * list) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

    return (list->size == CIRCULAR_LIST_SIZE);
}

/// @brief Inserts an element to any place in the list. Circular list allows appending to the end without
/// iterating the entire list.
/// @param list Pointer to circular list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_circular_list(circular_list_s * list, const size_t index, const CIRCULAR_LIST_DATA_TYPE element) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size < CIRCULAR_LIST_SIZE && "[ERROR] List reached maximum size.");
    CIRCULAR_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    CIRCULAR_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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
static inline CIRCULAR_LIST_DATA_TYPE get_circular_list(const circular_list_s * list, const size_t index) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] Can't get element from empty list->");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] Can't get element from empty list->");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't get element from empty list->");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] 'index' parameter exceeds list size.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

    size_t current = list->tail;
    for (size_t i = 0; index != list->size - 1 && i <= index; ++i) {
        current = list->next[current];
    }

    return list->elements[current];
}

/// @brief Removes first element in list based on element parameter comparison.
/// @param list Pointer to list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline CIRCULAR_LIST_DATA_TYPE remove_first_circular_list(circular_list_s * list, const CIRCULAR_LIST_DATA_TYPE element, const compare_circular_list_fn compare) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->elements && "[ERROR] Can't remove from empty list.");
    CIRCULAR_LIST_ASSERT(list->next && "[ERROR] Can't remove from empty list.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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
    CIRCULAR_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(source && "[ERROR] 'list_two' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    CIRCULAR_LIST_ASSERT(destination->size + source->size <= CIRCULAR_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    CIRCULAR_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    CIRCULAR_LIST_ASSERT(destination->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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

/// @brief Splits list and returns new list with elements in range.
/// @param list Pointer to list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by.
/// @return New split list.
/// @note Since circular list is circular the new list can include elements beyond old list's last node.
static inline circular_list_s split_circular_list(circular_list_s * list, const size_t index, const size_t size) {
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(size && "[ERROR] 'size' parameter can't be zero.");
    CIRCULAR_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    CIRCULAR_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    CIRCULAR_LIST_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

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
    CIRCULAR_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    CIRCULAR_LIST_ASSERT(manage && "[ERROR] 'manage' pointer parameter is NULL.");

    CIRCULAR_LIST_ASSERT(list->size <= CIRCULAR_LIST_SIZE && "[ERROR] Invalid list size.");

    CIRCULAR_LIST_DATA_TYPE elements_array[CIRCULAR_LIST_SIZE]; // create temporary array to store list elements

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

#else

#error Cannot include multiple headers in same unit.

#endif // CIRCULAR_LIST_H
