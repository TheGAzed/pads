#ifndef STRAIGHT_LIST_H
#define STRAIGHT_LIST_H

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

#ifndef STRAIGHT_LIST_DATA_TYPE

/// @brief Element datatype macro that can be changed via '#define STRAIGHT_LIST_DATA_TYPE [datatype]'.
#define STRAIGHT_LIST_DATA_TYPE void*

#endif

#ifndef STRAIGHT_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief Assertion macro that can be changed  via '#define STRAIGHT_LIST_ASSERT [assert]'.
#define STRAIGHT_LIST_ASSERT assert

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

#ifndef STRAIGHT_LIST_SIZE

#define STRAIGHT_LIST_SIZE (1 << 5)

#elif STRAIGHT_LIST_SIZE <= 0

#error 'STRAIGHT_LIST_SIZE' cannot be zero

#endif

/// @note The FINITE_ALLOCATED_STRAIGHT_LIST_MODE is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the straight_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when there are no holes (meaning 'empty stack' is empty) the straight list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The straight list is a linked list.
typedef struct straight_list {
    size_t next[STRAIGHT_LIST_SIZE]; // array to store next indexes
    STRAIGHT_LIST_DATA_TYPE elements[STRAIGHT_LIST_SIZE]; // array to store elements
    size_t size, head; // list size and head index parameter
    size_t empty_size, empty_head; // empty stack's size and head
} straight_list_s;

/// @brief Creates an empty straight list of zero size.
/// @return Straight list structure.
static inline straight_list_s create_straight_list(void) {
    return (straight_list_s) { .empty_head = 0, .empty_size = 0, .head = 0, .size = 0, };
}

/// @brief Destroys the straight list with all its elements and sets size to zero.
/// @param list Pointer to straight list structure.
/// @param destroy Readonly function pointer to destroy/free each element in straight list.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current); // destroy element at current index
        current = list->next[current]; // go to next index
    }

    list->empty_head = list->empty_size = list->head = list->size = 0; // list and its empty stack to zero
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Readonly straight list structure.
/// @param copy Readonly function pointer to create a copy of an element.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s * list, const copy_straight_list_fn copy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    straight_list_s replice = { .head = 0, .size = 0, .empty_head = 0, .empty_size = 0, };

    for (size_t current_list = list->head, * current_copy = &(replice.head); replice.size < list->size; replice.size++) {
        // set element copy to list copy at index i to automatically remove holes from copy
        replice.elements[replice.size] = copy(list->elements[current_list]);
        (*current_copy) = replice.size; // set head and indexes at list copy's next array to proper index

        current_list = list->next[current_list]; // go to next list node
        current_copy = replice.next + replice.size; // go to next copy list's pointer to node
    }

    return replice;
}

/// @brief Checks if list is empty.
/// @param list Readonly straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    return (list->size == 0);
}

/// @brief Checks if list is full.
/// @param list Readonly straight list structure.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");
    // if size is equal to macro size
    return (list->size == STRAIGHT_LIST_SIZE);
}

/// @brief Iterates through each straight list element.
/// @param list Pointer to readonly straight list structure.
/// @param operate Readonly function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

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
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

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

/// @brief Inserts an element at any index in the list.
/// @param list Pointer to straight list structure.
/// @param index Readonly zeero based index to insert element at.
/// @param element Readonly element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size < STRAIGHT_LIST_SIZE && "[ERROR] List reached maximum size.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

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
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't get element from empty list->");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] 'index' parameter exceeds list size.");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t current = list->head;
    for (size_t i = 0; i < index; ++i) {
        current = list->next[current];
    }

    return list->elements[current];
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

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

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

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

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

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

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
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(destination->size + source->size <= STRAIGHT_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    STRAIGHT_LIST_ASSERT(destination->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");
    STRAIGHT_LIST_ASSERT(source->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

    size_t * destination_current = &(destination->head), current_source = source->head;
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        destination_current = destination->next + (*destination_current);
    }

    for (; source->size && destination->empty_size; source->size--, destination->size++) {
        const size_t empty_pop = destination->empty_head; // pop empty head from empty stack
        destination->empty_head = destination->next[destination->empty_head]; // set empty head to next empty index
        destination->empty_size--; // decrement empty stack size

        destination->elements[destination->size] = source->elements[empty_pop];
        destination->next[empty_pop] = (*destination_current); // set temp's next index to index at current pointer
        (*destination_current) = empty_pop; // set index at current pointer, previous' next index, to temp

        destination_current = destination->next + (*destination_current);
        current_source = source->next[current_source];
    }

    for (; source->size; source->size--, destination->size++) {
        destination->elements[destination->size] = source->elements[current_source];
        destination->next[destination->size] = (*destination_current);
        (*destination_current) = destination->size;

        destination_current = destination->next + (*destination_current);
        current_source = source->next[current_source];
    }

    source->empty_size = source->head = 0;
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Non-zero size of new split list.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(size && "[ERROR] Split size can't be zero.");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    STRAIGHT_LIST_ASSERT(list->size <= STRAIGHT_LIST_SIZE && "[ERROR] List size exceeds maximum size.");

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

#else

#error Cannot include multiple headers in same unit.

#endif // STRAIGHT_LIST_H
