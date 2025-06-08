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

#ifndef DOUBLE_LIST_DATA_TYPE

/// @brief redefine using #define DOUBLE_LIST_DATA_TYPE [type] (default: void*)
#define DOUBLE_LIST_DATA_TYPE void*

#endif

#ifndef DOUBLE_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief redefine using #define DOUBLE_LIST_ASSERT [asserter] (default: assert)
#define DOUBLE_LIST_ASSERT assert

#endif

/// @brief Function pointer to copy an element and return new one.
typedef DOUBLE_LIST_DATA_TYPE (*copy_double_list_fn)    (const DOUBLE_LIST_DATA_TYPE element);
/// @brief Function pointer to destroy or free an element.
typedef void                  (*destroy_double_list_fn) (DOUBLE_LIST_DATA_TYPE * element);
/// @brief Function pointer to compare two elements, returns 0 if equal, positive if more than and negative otherwise
typedef int                   (*compare_double_list_fn) (const DOUBLE_LIST_DATA_TYPE one, const DOUBLE_LIST_DATA_TYPE two);
/// @brief Function pointer to operate on a pointer to an element in data structure usign generic arguments.
typedef bool                  (*operate_double_list_fn) (DOUBLE_LIST_DATA_TYPE * elements, void * args);
/// @brief Function pointer to manage an array of elements in data structure usign generic arguments.
typedef void                  (*manage_double_list_fn)  (DOUBLE_LIST_DATA_TYPE * array, const size_t size, void * args);

/// @brief Number of node directions for node array, i.e. one 'next' plus one 'previous'.
#define DOUBLE_LIST_NODE_COUNT 2
/// @brief Index to next pointer/index.
#define DOUBLE_LIST_NEXT 0
/// @brief Index to previous pointer/index.
#define DOUBLE_LIST_PREV 1

#ifndef DOUBLE_LIST_SIZE

#define DOUBLE_LIST_SIZE (1 << 5)

#elif DOUBLE_LIST_SIZE == 0

#error 'DOUBLE_LIST_SIZE' cannot be zero

#endif

typedef struct double_list {
    size_t node[DOUBLE_LIST_NODE_COUNT][DOUBLE_LIST_SIZE];
    size_t size, head;
    DOUBLE_LIST_DATA_TYPE elements[DOUBLE_LIST_SIZE];
} double_list_s;

/// @brief Creates an empty list.
/// @return Empty list.
static inline double_list_s create_double_list(void) {
    return (double_list_s) { .size = 0, .head = 0, };
}

/// @brief Destroys a list and its elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
static inline void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        destroy(list->elements + current);
        current = list->node[DOUBLE_LIST_NEXT][current];
    }

    list->size = list->head = 0;
}

/// @brief Destroys a list and its elements using a function pointer.
/// @param list Pointer of list to destroy.
/// @param destroy Destroy function pointer to destroy/free each element in list.
static inline void clear_double_list(double_list_s * list, const destroy_double_list_fn destroy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(destroy && "[ERROR] 'destroy' pointer parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        destroy(list->elements + current);
        current = list->node[DOUBLE_LIST_NEXT][current];
    }

    list->size = list->head = 0;
}

/// @brief Creates and returns a copy of the list with all elements based on copy function poniter.
/// @param list List structure to replicate.
/// @param copy Function pointer that returns a deep or shallow copy of an element.
/// @return Replicated list with all elements.
static inline double_list_s copy_double_list(const double_list_s * list, const copy_double_list_fn copy) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(copy && "[ERROR] 'copy' pointer parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    double_list_s replica = { .head = list->head, .size = 0, };
    for (; replica.size < list->size; replica.size++) {
        replica.elements[replica.size] = copy(list->elements[replica.size]);
        replica.node[DOUBLE_LIST_NEXT][replica.size] = list->node[DOUBLE_LIST_NEXT][replica.size];
        replica.node[DOUBLE_LIST_PREV][replica.size] = list->node[DOUBLE_LIST_PREV][replica.size];
    }

    return replica;
}

/// @brief Checks if list is empty.
/// @param list List structure to check.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_double_list(const double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    return (list->size == 0);
}

/// @brief Checks if list is full.
/// @param list List structure to check.
/// @return 'true' if list is full, 'false' otherwise.
static inline bool is_full_double_list(const double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    return (list->size == DOUBLE_LIST_SIZE);
}

/// @brief Inserts element into list based on index number.
/// @param list Pointer of list to insert element into.
/// @param index Zero-based index to specify where to insert element.
/// @param element Element to insert into list at index.
static inline void insert_at_double_list(double_list_s * list, const size_t index, const DOUBLE_LIST_DATA_TYPE element) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size < DOUBLE_LIST_SIZE && "[ERROR] List reached maximum size.");
    DOUBLE_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size.");
    DOUBLE_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT : DOUBLE_LIST_PREV;
    for (size_t i = 0; i < real_index; ++i) {
        current = list->node[node_index][current];
    }

    if (list->size) {
        list->node[DOUBLE_LIST_NEXT][list->size] = current;
        list->node[DOUBLE_LIST_PREV][list->size] = list->node[DOUBLE_LIST_PREV][current];

        list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][current]] = list->size;
        list->node[DOUBLE_LIST_PREV][current] = list->size;
    } else {
        list->head = list->node[DOUBLE_LIST_NEXT][0] = list->node[DOUBLE_LIST_PREV][0] = 0;
    }

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
static inline DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s * list, const size_t index) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't get element from empty list->");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] 'index' parameter exceeds list size.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT : DOUBLE_LIST_PREV;
    for (size_t i = 0; i < real_index; ++i) {
        current = list->node[node_index][current];
    }

    return list->elements[current];
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

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (0 != compare(list->elements[current], element)) {
            current = list->node[DOUBLE_LIST_NEXT][current];
            continue;
        }

        DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
        list->size--;

        // solely there to prevent bad head index
        if (list->head == current) { // if head is current change head to proper next node
            list->head = list->node[DOUBLE_LIST_NEXT][current] == list->size ? current : list->node[DOUBLE_LIST_NEXT][current];
        } else if (list->head == list->size) { // else if list head is last node make head to current (where last is moved)
            list->head = current;
        }

        // cut current node and stitch its previous and next nodes
        list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][current]] = list->node[DOUBLE_LIST_NEXT][current];
        list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][current]] = list->node[DOUBLE_LIST_PREV][current];

        // replace element at current index with popped last element like in a stack
        list->elements[current] = list->elements[list->size];
        list->node[DOUBLE_LIST_NEXT][current] = list->node[DOUBLE_LIST_NEXT][list->size];
        list->node[DOUBLE_LIST_PREV][current] = list->node[DOUBLE_LIST_PREV][list->size];

        if (current != list->size) { // if current index is not last stitch last previous and next indexes to current
            list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][list->size]] = current;
            list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][list->size]] = current;
        }

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

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        current = list->node[DOUBLE_LIST_PREV][current];

        if (0 != compare(list->elements[current], element)) {
            continue;
        }

        DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
        list->size--;

        // solely there to prevent bad head index
        if (list->head == current) { // if head is current change head to proper next node
            list->head = list->node[DOUBLE_LIST_NEXT][current] == list->size ? current : list->node[DOUBLE_LIST_NEXT][current];
        } else if (list->head == list->size) {
            list->head = current;
        }

        // cut current node and stitch its previous and next nodes
        list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][current]] = list->node[DOUBLE_LIST_NEXT][current];
        list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][current]] = list->node[DOUBLE_LIST_PREV][current];

        // replace element at current index with popped last element like in a stack
        list->elements[current] = list->elements[list->size];
        list->node[DOUBLE_LIST_NEXT][current] = list->node[DOUBLE_LIST_NEXT][list->size];
        list->node[DOUBLE_LIST_PREV][current] = list->node[DOUBLE_LIST_PREV][list->size];

        if (current != list->size) { // if current index is not last stitch last previous and next indexes to current
            list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][list->size]] = current;
            list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][list->size]] = current;
        }

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

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    const size_t real_index = index <= (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT : DOUBLE_LIST_PREV;
    for (size_t i = 0; i < real_index; ++i) {
        current = list->node[node_index][current];
    }

    DOUBLE_LIST_DATA_TYPE removed = list->elements[current];
    list->size--;

    // solely there to prevent bad head index
    if (list->head == current) { // if head is current change head to proper next node
        list->head = list->node[DOUBLE_LIST_NEXT][current] == list->size ? current : list->node[DOUBLE_LIST_NEXT][current];
    } else if (list->head == list->size) {
        list->head = current;
    }

    // cut current node and stitch its previous and next nodes
    list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][current]] = list->node[DOUBLE_LIST_NEXT][current];
    list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][current]] = list->node[DOUBLE_LIST_PREV][current];

    // replace element at current index with popped last element like in a stack
    list->elements[current] = list->elements[list->size];
    list->node[DOUBLE_LIST_NEXT][current] = list->node[DOUBLE_LIST_NEXT][list->size];
    list->node[DOUBLE_LIST_PREV][current] = list->node[DOUBLE_LIST_PREV][list->size];

    if (current != list->size) { // if current index is not last stitch last previous and next indexes to current
        list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][list->size]] = current;
        list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][list->size]] = current;
    }

    return removed;
}

/// @brief Reverses list element ordering.
/// @param list Pointer of list to reverse.
static inline void reverse_double_list(double_list_s * list) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        list->head = current;

        const size_t temp = list->node[DOUBLE_LIST_NEXT][current];
        list->node[DOUBLE_LIST_NEXT][current] = list->node[DOUBLE_LIST_PREV][current];
        list->node[DOUBLE_LIST_PREV][current] = temp;

        current = list->node[DOUBLE_LIST_PREV][current];
    }
}

/// @brief Shifts list node by next n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_next_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_NEXT][list->head];
    }
}

/// @brief Shifts list node by previous n-nodes.
/// @param list Pointer of list to shift.
/// @param shift Number of shifts to perform.
static inline void shift_prev_double_list(double_list_s * list, const size_t shift) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' pointer parameter is NULL.");
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't shift empty list.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    for (size_t i = 0; i < shift; ++i) {
        list->head = list->node[DOUBLE_LIST_PREV][list->head];
    }
}

/// @brief Splices source list into destination list at specified index.
/// @param destination Pointer of list to splice into.
/// @param source Pointer of list to splice from.
/// @param index Zero-based index at destination list to start splicing.
static inline void splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index) {
    DOUBLE_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter is NULL.");
    DOUBLE_LIST_ASSERT(source && "[ERROR] 'list_two' parameter is NULL.");
    DOUBLE_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    DOUBLE_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");
    DOUBLE_LIST_ASSERT(destination->size + source->size <= DOUBLE_LIST_SIZE && "[ERROR] new list's size exceeds DOUBLE_LIST_SIZE");

    DOUBLE_LIST_ASSERT(destination->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    DOUBLE_LIST_ASSERT(source->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = destination->head;
    const size_t real_index = index <= (destination->size >> 1) ? index : destination->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT : DOUBLE_LIST_PREV;
    for (size_t i = 0; i < real_index; ++i) {
        current = destination->node[node_index][current];
    }

    for (size_t i = 0; i < source->size; ++i) {
        destination->elements[destination->size + i] = source->elements[i];
        destination->node[DOUBLE_LIST_NEXT][destination->size + i] = source->node[DOUBLE_LIST_NEXT][i] + destination->size;
        destination->node[DOUBLE_LIST_PREV][destination->size + i] = source->node[DOUBLE_LIST_PREV][i] + destination->size;
    }

    if (destination->size && source->size) {
        const size_t first_destination = current;
        const size_t last_destination  = destination->node[DOUBLE_LIST_PREV][current];

        const size_t first_source = source->head + destination->size;
        const size_t last_source  = source->node[DOUBLE_LIST_PREV][source->head] + destination->size;

        destination->node[DOUBLE_LIST_NEXT][last_destination] = first_source;
        destination->node[DOUBLE_LIST_PREV][first_source] = last_destination;

        destination->node[DOUBLE_LIST_NEXT][last_source] = first_destination;
        destination->node[DOUBLE_LIST_PREV][first_destination] = last_source;
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
    DOUBLE_LIST_ASSERT(list->size && "[ERROR] Can't split empty list.");
    DOUBLE_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size.");
    DOUBLE_LIST_ASSERT(size && "[ERROR] Size parameter can't be zero");
    DOUBLE_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t list_current = list->head;
    const size_t real_index = index < (list->size >> 1) ? index : list->size - index;
    const bool node_index = real_index == index ? DOUBLE_LIST_NEXT : DOUBLE_LIST_PREV;
    for (size_t i = 0; i < real_index; ++i) {
        list_current = list->node[node_index][list_current];
    }

    double_list_s split = { .head = 0, .size = 0, };

    size_t * split_current = &(split.head);
    for (; split.size < size; split.size++) {
        split.elements[split.size] = list->elements[list_current];
        (*split_current) = split.size; // set head and next nodes to next index
        split.node[DOUBLE_LIST_PREV][split.size] = split.size - 1; // set previous node indexes to one minus current
        list->size--;

        if (list->head == list->size) {
            list->head = list_current;
        }

        const size_t list_next = list->node[DOUBLE_LIST_NEXT][list_current] == list->size ? list_current : list->node[DOUBLE_LIST_NEXT][list_current];

        // cut current node and stitch its previous and next nodes
        list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][list_current]] = list->node[DOUBLE_LIST_NEXT][list_current];
        list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][list_current]] = list->node[DOUBLE_LIST_PREV][list_current];

        // replace element at current index with popped last element like in a stack
        list->elements[list_current] = list->elements[list->size];
        list->node[DOUBLE_LIST_NEXT][list_current] = list->node[DOUBLE_LIST_NEXT][list->size];
        list->node[DOUBLE_LIST_PREV][list_current] = list->node[DOUBLE_LIST_PREV][list->size];

        if (list_current != list->size) { // if current index is not last stitch last previous and next indexes to current
            list->node[DOUBLE_LIST_PREV][list->node[DOUBLE_LIST_NEXT][list->size]] = list_current;
            list->node[DOUBLE_LIST_NEXT][list->node[DOUBLE_LIST_PREV][list->size]] = list_current;
        }

        list_current = list_next; // go to next list node
        split_current = split.node[DOUBLE_LIST_NEXT] + split.size; // go to next split list node pointer
    }
    split.node[DOUBLE_LIST_PREV][0] = size - 1; // to make list circular first index in previous must point to last element
    (*split_current) = 0;

    if (!index || (index >= list->size)) {
        list->head = list_current;
    }

    return split;
}

/// @brief Iterates over elements in list and operates on each of them based on arguments, in proper order.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_next_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size && operate(list->elements + current, args); ++i) {
        current = list->node[DOUBLE_LIST_NEXT][current];
    }
}

/// @brief Iterates over elements in list and operates on each of them based on arguments, but in reverse order.
/// @param list Pointer of list to iterate over.
/// @param operate Function pointer to operate on each element in list based or arguments.
/// @param args Generic arguments to use in operate function, or can be NULL.
static inline void foreach_prev_double_list(double_list_s * list, const operate_double_list_fn operate, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size && operate(list->elements + list->node[DOUBLE_LIST_PREV][current], args); ++i) {
        current = list->node[DOUBLE_LIST_PREV][current];
    }
}

/// Maps list into array and manages it using list size and arguments.
/// @param list Pointer of list to map.
/// @param manage Function pointer to manage list as array using its size, and arguments.
/// @param args Generic arguments to use in manage function, or can be NULL.
static inline void map_double_list(double_list_s * list, const manage_double_list_fn manage, void * args) {
    DOUBLE_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    DOUBLE_LIST_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    DOUBLE_LIST_ASSERT(list->size <= DOUBLE_LIST_SIZE && "[ERROR] Invalid list state.");

    DOUBLE_LIST_DATA_TYPE elements_array[DOUBLE_LIST_SIZE];

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) { // copy elements in order into elements array
        elements_array[i] = list->elements[current];
        current = list->node[DOUBLE_LIST_NEXT][current];
    }

    manage(elements_array, list->size, args);

    for (size_t i = 0; i < list->size; ++i) {  // copy elements back in order to list
        list->elements[current] = elements_array[i];
        current = list->node[DOUBLE_LIST_NEXT][current];
    }
}

#else

#error Cannot include multiple headers in same unit.

#endif // DOUBLE_LIST_H
