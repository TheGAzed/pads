#ifndef STRAIGHT_LIST_H
#define STRAIGHT_LIST_H

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
#define INFINITE_ALLOCATED_STRAIGHT_LIST  41
#define FINITE_ALLOCATED_STRAIGHT_LIST    42
#define INFINITE_REALLOC_STRAIGHT_LIST    43
#define FINITE_PRERPOCESSOR_STRAIGHT_LIST 44

#define INFINITE_STRAIGHT_LIST INFINITE_ALLOCATED_STRAIGHT_LIST
#define FINITE_STRAIGHT_LIST   FINITE_ALLOCATED_STRAIGHT_LIST

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

#define IS_INFINITE_STRAIGHT_LIST (STRAIGHT_LIST_MODE & 0x01)

// Check to make sure a valid list mode is selected.
#if (STRAIGHT_LIST_MODE != INFINITE_ALLOCATED_STRAIGHT_LIST) && (STRAIGHT_LIST_MODE != FINITE_ALLOCATED_STRAIGHT_LIST)    && \
(STRAIGHT_LIST_MODE != INFINITE_REALLOC_STRAIGHT_LIST)   && (STRAIGHT_LIST_MODE != FINITE_PRERPOCESSOR_STRAIGHT_LIST)

#error Invalid type of list mode.

#endif

#ifndef STRAIGHT_LIST_DATA_TYPE

/// @brief Element datatype macro that can be changed  via '#define STRAIGHT_LIST_DATA_TYPE [datatype]'.
#define STRAIGHT_LIST_DATA_TYPE void*

#endif

#ifndef STRAIGHT_LIST_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief Assertion macro that can be changed  via '#define STRAIGHT_LIST_ALLOC [assert]'.
#define STRAIGHT_LIST_ASSERT assert

#endif

#ifndef STRAIGHT_LIST_ALLOC

/// @brief Memory allocation macro that can be changed via '#define STRAIGHT_LIST_ALLOC [allocator]'.
#define STRAIGHT_LIST_ALLOC malloc

#endif

#ifndef STRAIGHT_LIST_REALLOC

/// @brief Memory reallocation macro that can be changed via '#define STRAIGHT_LIST_REALLOC [reallocator]'.
#define STRAIGHT_LIST_REALLOC realloc

#endif

#ifndef STRAIGHT_LIST_FREE

/// @brief Memory freeing macro that can be changed via '#define STRAIGHT_LIST_FREE [free]'.
#define STRAIGHT_LIST_FREE free

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

// many functions use Linus Torvalds' Tastes in code for linked lists from his TED Talk
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

/// @brief Destroys the straight list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to straight list structure.
/// @param destroy Function pointer to destroy/free each element in straight list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    while (list->head) { // change head to head's next node after every iteration until NULL is reached
        if (destroy) { // if destroy function pointer is specified then destroys element
            destroy(&(list->head->element));
        }
        // free current head node
        struct straight_list_node * temp = list->head->next;
        STRAIGHT_LIST_FREE(list->head);
        list->head = temp;
    }
    list->size = 0; // need to only set list size to zero since head will be NULL after while loop ends
}

/// @brief Inserts an element to any place in the list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    STRAIGHT_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    struct straight_list_node ** current = &(list->head);
    for (size_t i = 0; i < index; ++i) { // iterate until pointer index node is reached
        current = &((*current)->next);
    }

    // creates node and copies element parameter into the node element
    struct straight_list_node * node = STRAIGHT_LIST_ALLOC(sizeof(struct straight_list_node));
    STRAIGHT_LIST_ASSERT(node && "[ERROR] Memory allocation failed.");
    memcpy(&(node->element), &element, sizeof(STRAIGHT_LIST_DATA_TYPE));

    node->next = (*current); // make new node's next pointer point to current
    (*current) = node; // change pointer to current node to new node
    list->size++;
}

/// @brief Removes first element in straight list based on element parameter comparison.
/// @param list Pointer to straight list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    struct straight_list_node ** current = &(list->head);
    while ((*current)) {
        const int comparison = compare ? compare((*current)->element, element) : memcmp(&((*current)->element), &element, sizeof(STRAIGHT_LIST_DATA_TYPE));

        if (0 == comparison) {
            list->size--;
            STRAIGHT_LIST_DATA_TYPE found = (*current)->element;

            struct straight_list_node * temp = (*current);
            (*current) = (*current)->next;
            STRAIGHT_LIST_FREE(temp);

            return found;
        }
        current = &((*current)->next);
    }

    STRAIGHT_LIST_ASSERT(0 && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned. Since the function returns the removed element that can contain allocated memory an element must be returned
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index in straight list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    struct straight_list_node ** current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = &((*current)->next);
    }

    list->size--;
    STRAIGHT_LIST_DATA_TYPE found = (*current)->element;

    struct straight_list_node * temp = (*current);
    (*current) = (*current)->next;
    STRAIGHT_LIST_FREE(temp);

    return found;
}

/// @brief Reverses straight list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    struct straight_list_node * previous = NULL;
    struct straight_list_node * current = list->head;
    struct straight_list_node * next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    list->head = previous;
}

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to straight list structure to splice into.
/// @param source Pointer to straight list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index) {
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    struct straight_list_node ** current_dest = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        current_dest = &((*current_dest)->next);
    }

    struct straight_list_node ** last_source = &(source->head);
    while ((*last_source)) { // iterate while pointer to node dereferenced is not NULL to get pointer to last source node
        last_source = &((*last_source)->next);
    }

    (*last_source) = (*current_dest); // change last source node pointer to destination's current
    (*current_dest) = source->head; // change destination's index node pointer to source's head

    destination->size += source->size;

    (*source) = (straight_list_s) { 0 }; // set source list to zero (i. e. destroy it)
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    struct straight_list_node ** current = &(list->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index
        current = &((*current)->next);
    }

    straight_list_s split = { .head = NULL, .size = size, }; // set initial split head to NULL

    struct straight_list_node * last = (*current); // create pointer to node to point to node after split's last note
    struct straight_list_node ** current_split = &(split.head); // create pointer to node to add nodes to split list
    for (size_t i = 0; i < size; ++i) {
        (*current_split) = last; // set split's pointer-to node to last
        last = last->next; // increment last's pointer to node to next pointer to node
        (*current_split)->next = NULL; // set split's last node next pointer to NULL
        current_split = &((*current_split)->next); // increment split's pointer to node to next pointer to node
    }

    (*current) = last; // set previous' next node to last list's node (if size parameter is 0 then nothing changes)

    list->size -= size;

    return split;
}

/// @brief Gets element at index.
/// @param list Straight list structure.
/// @param index Zero based index of element in list.
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

/// @brief Checks if list is empty.
/// @param list Straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Straight list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero
    // and negating it makes function return true only if full
    return !(~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Straight list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    straight_list_s list_copy = { .head = NULL, .size = list.size };

    struct straight_list_node const * current_list = list.head;
    // double pointer since this also works on copying straight list
    struct straight_list_node ** current_copy = &(list_copy.head);
    for (size_t i = 0; i < list.size; ++i) {
        // create new node and copy element from source list based on copy function pointer parameter
        struct straight_list_node * node = STRAIGHT_LIST_ALLOC(sizeof(struct straight_list_node));
        STRAIGHT_LIST_ASSERT(node && "[ERROR] Memory allocation failed.");
        // if copy is specified call it, else just assign it to variable
        node->element = copy ? copy(current_list->element) : current_list->element;
        node->next = NULL;

        (*current_copy) = node; // change previous copy's node pointer to node

        current_list = current_list->next; // go to next list node
        current_copy = &((*current_copy)->next); // go to next copy list's pointer to node
    }

    return list_copy;
}

/// @brief Clears the list of elements.  Similar to 'destroy_straight_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    while (list->head) { // change head to head's next node after every iteration until NULL is reached
        if (destroy) { // if destroy function pointer is specified then destroys element
            destroy(&(list->head->element));
        }

        struct straight_list_node * temp = list->head->next;
        STRAIGHT_LIST_FREE(list->head);
        list->head = temp;
    }
    list->size = 0; // need to only set list size to zero since head will be NULL after while loop ends
}

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to straight list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering WILL remain.
/// This may not apply for other straight list 'forevery_straight_list' implementations and a note will reflect that.
static inline void forevery_straight_list(straight_list_s const * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    // create continuos array to store lis elements
    STRAIGHT_LIST_DATA_TYPE * elements_array = STRAIGHT_LIST_ALLOC(sizeof(STRAIGHT_LIST_DATA_TYPE) * list->size);
    STRAIGHT_LIST_ASSERT((!(list->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct straight_list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        elements_array[i] = current->element;
        current = current->next; // go to next node to add elements from head instead of from tail
    }

    manage(elements_array, list->size, args);

    current = list->head;
    for (size_t i = 0; i < list->size; ++i) { // loop to re-add new list element's ordering
        current->element = elements_array[i];
        current = current->next;
    }

    STRAIGHT_LIST_FREE(elements_array);
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Straight list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'forevery_straight_list' can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    struct straight_list_node const * base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        struct straight_list_node const * current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = current->next;
        }

        const int comparison = compare ? compare(element, current->element) : memcmp(&element, &(current->element), sizeof(STRAIGHT_LIST_DATA_TYPE));

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

/// @brief Iterates through straight list elements without changing list ordering.
/// @param list Pointer to straight list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s const * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    struct straight_list_node * current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(&current->element, args)) { // if operate returns false then stop loop
            return;
        }

        current = current->next;
    }
}

#elif STRAIGHT_LIST_MODE == FINITE_ALLOCATED_STRAIGHT_LIST

/// @note The FINITE_ALLOCATED_STRAIGHT_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the straight_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when there are no holes (meaning 'empty stack' is empty) the straight list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The straight list is a linked list.
typedef struct straight_list {
    size_t size, empty_size, head, empty_head, max;
    STRAIGHT_LIST_DATA_TYPE * elements;
    size_t * next;
} straight_list_s;

/// @brief Creates an empty straight list of zero size.
/// @param max Maximum positive nonzero size of straight list.
/// @return Straight list structure.
static inline straight_list_s create_straight_list(const size_t max) {
    STRAIGHT_LIST_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const straight_list_s list = {
        .elements = STRAIGHT_LIST_ALLOC(max * sizeof(STRAIGHT_LIST_DATA_TYPE)),
        .next = STRAIGHT_LIST_ALLOC(max * sizeof(size_t)),
        .head = 0, .max = max, .size = 0, .empty_head = 0, .empty_size = 0,
    };

    // check if memory allocation failed
    STRAIGHT_LIST_ASSERT(list.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(list.next && "[ERROR] Memory allocation failed.");

    return list; // sets straight list to zero
}

/// @brief Destroys the straight list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to straight list structure.
/// @param destroy Function pointer to destroy/free each element in straight list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; destroy && s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }

    STRAIGHT_LIST_FREE(list->elements); // free elements array
    STRAIGHT_LIST_FREE(list->next); // free next index array
    *list = (straight_list_s) { 0 }; // set everything to zero
}

/// @brief Inserts an element to any place in the list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size < list->max && "[ERROR] List reached maximum size.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    STRAIGHT_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

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

/// @brief Removes first element in straight list based on element parameter comparison.
/// @param list Pointer to straight list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < list->size; ++i) {
        const int comparison = compare ? compare(list->elements[(*current)], element) : memcmp(list->elements + (*current), &element, sizeof(STRAIGHT_LIST_DATA_TYPE));

        if (0 != comparison) { // early continue in order to remove one needless nesting level
            current = list->next + (*current);
            continue;
        }

        list->size--;
        STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)];

        if (list->next[(*current)] != list->size) { // push empty index to 'empty stack'
            list->next[(*current)] = list->empty_head;
            list->empty_head = (*current);
            list->empty_size++;
        }

        (*current) = list->next[(*current)];

        if (!list->size) { // if list is empty set empty stack elements to zero
            list->empty_head = list->empty_size = 0;
        }

        return found;
    }

    STRAIGHT_LIST_ASSERT(0 && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned, since the function returns the removed element, element can contain allocated memory
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index in straight list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = list->next + (*current);
    }

    list->size--;
    STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)];

    if (list->next[(*current)] != list->size) { // push empty index to 'empty stack'
        list->next[(*current)] = list->empty_head;
        list->empty_head = (*current);
        list->empty_size++;
    }

    (*current) = list->next[(*current)];

    if (!list->size) { // if list is empty set empty stack elements to zero
        list->empty_head = list->empty_size = 0;
    }

    return found;
}

/// @brief Reverses straight list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

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

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to straight list structure to splice into.
/// @param source Pointer to straight list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
/// @param max New maximum positive nonzero size of destination list.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index, const size_t max) {
    STRAIGHT_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(destination->size + source->size <= max && "[ERROR] Combined lists' sizes exceed max size of new list.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    destination->elements = STRAIGHT_LIST_REALLOC(destination->elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * max);
    STRAIGHT_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed.");
    destination->next = STRAIGHT_LIST_REALLOC(destination->next, sizeof(size_t) * max);
    STRAIGHT_LIST_ASSERT(destination->next && "[ERROR] Memory allocation failed.");

    size_t * current_dest = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        current_dest = destination->next + (*current_dest);
    }

    size_t * last_source = &(source->head);
    while (source->size && destination->empty_size) {
        memcpy(destination->elements + destination->empty_head, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->size++;

        const size_t temp = destination->empty_head;
        destination->empty_head = destination->next[destination->empty_head];

        destination->next[temp] = (*current_dest);
        (*current_dest) = temp;

        destination->empty_size--;

        source->size--;
        current_dest = destination->next + (*current_dest);
        last_source = source->next + (*last_source);
    }

    while (source->size) {
        memcpy(destination->elements + destination->size, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->next[destination->size] = (*current_dest);
        (*current_dest) = destination->size;
        destination->size++;

        source->size--;
        current_dest = destination->next + (*current_dest);
        last_source = source->next + (*last_source);
    }

    STRAIGHT_LIST_FREE(source->elements);
    STRAIGHT_LIST_FREE(source->next);
    (*source) = (straight_list_s) { 0 }; // set source list to zero (i. e. destroy it)
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @param max Maximum positive nonzero size of returned split list.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size, const size_t max) {
    STRAIGHT_LIST_ASSERT(max && "[ERROR] maximum size can't be zero.");
    STRAIGHT_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    straight_list_s split = {
        .elements = STRAIGHT_LIST_ALLOC(max * sizeof(STRAIGHT_LIST_DATA_TYPE)), .empty_head = 0, .empty_size = 0,
        .next = STRAIGHT_LIST_ALLOC(max * sizeof(size_t)), .size = size, .head = 0, .max = max,
    };
    STRAIGHT_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index
        current = list->next + (*current);
    }

    size_t last = (*current); // create pointer to node to point to node after split's last note
    size_t * current_split = &(split.head); // create pointer to node to add nodes to split list
    for (size_t i = 0; i < size; ++i) {
        split.elements[i] = list->elements[last];
        (*current_split) = i; // set split's pointer-to node to last

        last = list->next[last]; // increment last's pointer to node to next pointer to node
        current_split = split.next + (*current_split); // increment split's pointer to node to next pointer to node
    }

    (*current) = last; // set previous' next node to last list's node (if size parameter is 0 then nothing changes)

    return split;
}

/// @brief Gets element at index.
/// @param list Straight list structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list.head && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    for (size_t i = 0; i < index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Checks if list is empty.
/// @param list Straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Straight list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero
    // and negating it makes function return true only if full
    return !(list.size < list.max && ~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Straight list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    straight_list_s list_copy = {
        .next = STRAIGHT_LIST_ALLOC(list.max * sizeof(size_t)), .head = 0, .size = list.size,
        .elements = STRAIGHT_LIST_ALLOC(list.max * sizeof(STRAIGHT_LIST_DATA_TYPE)), .empty_head = 0, .empty_size = 0,
    };
    STRAIGHT_LIST_ASSERT(list_copy.elements && "[ERROR] Memory allocation failed.");
    STRAIGHT_LIST_ASSERT(list_copy.next && "[ERROR] Memory allocation failed.");

    size_t current_list = list.head;
    // double pointer since this also works on copying straight list
    size_t * current_copy = &(list_copy.head);
    for (size_t i = 0; i < list.size; ++i) {
        // set element copy to list copy at index i to automatically remove holes from copy
        list_copy.elements[i] = copy ? copy(list.elements[current_list]) : list.elements[current_list];
        (*current_copy) = i; // set head and indexes at list copy's next array to proper index

        current_list = list.next[current_list]; // go to next list node
        current_copy = list_copy.next + (*current_copy); // go to next copy list's pointer to node
    }

    return list_copy;
}

/// @brief Clears the list of elements.  Similar to 'destroy_straight_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; destroy && s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }

    // set cleared list's empty stack and head to zero and keep allocated memory
    list->empty_head = list->empty_size = list->head = 0;
}

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to straight list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering may NOT remain
/// (it may change if there are holes in the list). This may not apply for other forward list 'forevery_forward_list'
/// implementations and a note will reflect that.
static inline void forevery_straight_list(straight_list_s * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (list->empty_size) { // removes holes at the expense of breaking the list
        stack_size--;

        if (empty_index > stack_size) {
            empty_index = list->next[empty_index];
        }

        STRAIGHT_LIST_DATA_TYPE element = list->elements[empty_index];
        list->elements[empty_index] = list->elements[stack_size];
        list->elements[stack_size] = element;

        const size_t index = list->next[empty_index];
        list->next[empty_index] = list->next[stack_size];
        list->next[stack_size] = empty_index;
        empty_index = index;

        list->empty_size--;
    }

    manage(list->elements, list->size, args);

    size_t * current = (&list->head);
    for (size_t i = 0; i < list->size; ++i) {
        (*current) = i;
        current = list->next + (*current);
    }
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Straight list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'forevery_straight_list' can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    size_t base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        size_t current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(element, list.elements + current) : memcmp(&element, list.elements + current, sizeof(STRAIGHT_LIST_DATA_TYPE));

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

/// @brief Iterates through straight list elements without changing list ordering.
/// @param list Pointer to straight list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s const * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(list->elements + current, args)) { // if operate returns false then stop loop
            return;
        }

        current = list->next[current];
    }
}

#elif STRAIGHT_LIST_MODE == INFINITE_REALLOC_STRAIGHT_LIST

#ifndef REALLOC_STRAIGHT_LIST_CHUNK

/// @brief Chunk size to expand/shrink elements array.
#define REALLOC_STRAIGHT_LIST_CHUNK (1 << 10)

#elif REALLOC_STRAIGHT_LIST_CHUNK <= 0

#error 'REALLOC_STRAIGHT_LIST_CHUNK' cannot be zero

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

/// @brief Destroys the straight list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to straight list structure.
/// @param destroy Function pointer to destroy/free each element in straight list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; destroy && s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }

    STRAIGHT_LIST_FREE(list->elements); // free elements array
    STRAIGHT_LIST_FREE(list->next); // free next index array
    *list = (straight_list_s) { 0 }; // set everything to zero
}

/// @brief Inserts an element to any place in the list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    STRAIGHT_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

    if (!(list->size % REALLOC_STRAIGHT_LIST_CHUNK)) {
        list->elements = STRAIGHT_LIST_REALLOC(list->elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * (list->size + REALLOC_STRAIGHT_LIST_CHUNK));
        list->next = STRAIGHT_LIST_REALLOC(list->next, sizeof(size_t) * (list->size + REALLOC_STRAIGHT_LIST_CHUNK));
    }

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

/// @brief Removes first element in straight list based on element parameter comparison.
/// @param list Pointer to straight list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    size_t * current = &(list->head);
    for (size_t s = 0; s < list->size; ++s) {
        const int comparison = compare ? compare(list->elements[(*current)], element) : memcmp(list->elements + (*current), &element, sizeof(STRAIGHT_LIST_DATA_TYPE));

        if (0 != comparison) { // early continue in order to remove one needless nesting level
            current = list->next + (*current);
            continue;
        }

        list->size--;
        STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)];

        if (list->next[(*current)] != list->size) { // push empty index to 'empty stack'
            list->next[(*current)] = list->empty_head;
            list->empty_head = (*current);
            list->empty_size++;
        }

        (*current) = list->next[(*current)];

        if (0 == (list->size % REALLOC_STRAIGHT_LIST_CHUNK)) { // turn list into continuous array and reduce size via realloc
            straight_list_s temp_list = {
                .elements = STRAIGHT_LIST_ALLOC(sizeof(STRAIGHT_LIST_DATA_TYPE) * list->size), .size = list->size, .head = 0,
                .next = STRAIGHT_LIST_ALLOC(sizeof(size_t) * list->size), .empty_head = 0, .empty_size = 0,
            };
            STRAIGHT_LIST_ASSERT((!(list->size) || temp_list.elements) && "[ERROR] Memory allocation failed.");
            STRAIGHT_LIST_ASSERT((!(list->size) || temp_list.next) && "[ERROR] Memory allocation failed.");

            size_t * temp_current  = &(temp_list.head);
            size_t realloc_index = list->head;
            for (size_t i = 0; i < list->size; ++i) {
                temp_list.elements[i] = list->elements[realloc_index];
                (*temp_current) = i;

                temp_current = temp_list.next + (*temp_current);
                realloc_index = list->next[realloc_index];
            }

            STRAIGHT_LIST_FREE(list->elements);
            STRAIGHT_LIST_FREE(list->next);

            if (!list->size) {
                STRAIGHT_LIST_FREE(temp_list.elements);
                STRAIGHT_LIST_FREE(temp_list.next);
                temp_list.elements = NULL;
                temp_list.next = NULL;
            }

            (*list) = temp_list;
        }

        return found;
    }

    STRAIGHT_LIST_ASSERT(0 && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned, since the function returns the removed element, element can contain allocated memory
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index in straight list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = list->next + (*current);
    }

    list->size--;
    STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)];

    if (list->next[(*current)] != list->size) { // push empty index to 'empty stack'
        list->next[(*current)] = list->empty_head;
        list->empty_head = (*current);
        list->empty_size++;
    }

    (*current) = list->next[(*current)];

    if (0 == (list->size % REALLOC_STRAIGHT_LIST_CHUNK)) { // turn list into continuous array and reduce size via realloc
        straight_list_s temp_list = {
            .elements = STRAIGHT_LIST_ALLOC(sizeof(STRAIGHT_LIST_DATA_TYPE) * list->size), .size = list->size, .head = 0,
            .next = STRAIGHT_LIST_ALLOC(sizeof(size_t) * list->size), .empty_head = 0, .empty_size = 0,
        };
        STRAIGHT_LIST_ASSERT((!(list->size) || temp_list.elements) && "[ERROR] Memory allocation failed.");
        STRAIGHT_LIST_ASSERT((!(list->size) || temp_list.next) && "[ERROR] Memory allocation failed.");

        size_t * temp_current  = &(temp_list.head);
        size_t realloc_index = list->head;
        for (size_t i = 0; i < list->size; ++i) {
            temp_list.elements[i] = list->elements[realloc_index];
            (*temp_current) = i;

            temp_current = temp_list.next + (*temp_current);
            realloc_index = list->next[realloc_index];
        }

        STRAIGHT_LIST_FREE(list->elements);
        STRAIGHT_LIST_FREE(list->next);

        if (!list->size) {
            STRAIGHT_LIST_FREE(temp_list.elements);
            STRAIGHT_LIST_FREE(temp_list.next);
            temp_list.elements = NULL;
            temp_list.next = NULL;
        }

        (*list) = temp_list;
    }

    return found;
}

/// @brief Reverses straight list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

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

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to straight list structure to splice into.
/// @param source Pointer to straight list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index) {
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    size_t * current_dest = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        current_dest = destination->next + (*current_dest);
    }

    size_t * last_source = &(source->head);
    while (source->size && destination->empty_size) {
        memcpy(destination->elements + destination->empty_head, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->size++;

        const size_t temp = destination->empty_head;
        destination->empty_head = destination->next[destination->empty_head];

        destination->next[temp] = (*current_dest);
        (*current_dest) = temp;

        destination->empty_size--;

        source->size--;
        current_dest = destination->next + (*current_dest);
        last_source = source->next + (*last_source);
    }

    while (source->size) {
        const size_t temp = (*current_dest); // if realloc is performed we may loose the pointer to destinations's current index
        (*current_dest) = destination->size; // before reallocation may happen we change the index at current destination's pointer

        if (!(destination->size % REALLOC_STRAIGHT_LIST_CHUNK)) {
            destination->elements = STRAIGHT_LIST_REALLOC(destination->elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * (destination->size + REALLOC_STRAIGHT_LIST_CHUNK));
            STRAIGHT_LIST_ASSERT(destination->elements && "[ERROR] Memory allocation failed");
            destination->next = STRAIGHT_LIST_REALLOC(destination->next, sizeof(size_t) * (destination->size + REALLOC_STRAIGHT_LIST_CHUNK));
            STRAIGHT_LIST_ASSERT(destination->next && "[ERROR] Memory allocation failed");
        }

        memcpy(destination->elements + destination->size, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->next[destination->size] = temp;
        destination->size++;

        source->size--;
        current_dest = destination->next + (*current_dest);
        last_source = source->next + (*last_source);
    }

    STRAIGHT_LIST_FREE(source->elements);
    STRAIGHT_LIST_FREE(source->next);
    (*source) = (straight_list_s) { 0 }; // set source list to zero (i. e. destroy it)
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    straight_list_s split = { 0 };

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index
        current = list->next + (*current);
    }

    size_t last = (*current); // create pointer to node to point to node after split's last note
    size_t * current_split = &(split.head); // create pointer to node to add nodes to split list
    for (size_t i = 0; i < size; ++i) {
        (*current_split) = i; // set split's pointer-to node to last

        if (!(split.size % REALLOC_STRAIGHT_LIST_CHUNK)) {
            split.elements = STRAIGHT_LIST_REALLOC(split.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * (split.size + REALLOC_STRAIGHT_LIST_CHUNK));
            STRAIGHT_LIST_ASSERT(split.elements && "[ERROR] Memory allocation failed");
            split.next = STRAIGHT_LIST_REALLOC(split.next, sizeof(size_t) * (split.size + REALLOC_STRAIGHT_LIST_CHUNK));
            STRAIGHT_LIST_ASSERT(split.next && "[ERROR] Memory allocation failed");
        }
        split.size++;

        split.elements[i] = list->elements[last];

        last = list->next[last]; // increment last's pointer to node to next pointer to node
        current_split = split.next + (*current_split); // increment split's pointer to node to next pointer to node
    }

    (*current) = last; // set previous' next node to last list's node (if size parameter is 0 then nothing changes)

    return split;
}

/// @brief Gets element at index.
/// @param list Straight list structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list.head && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    for (size_t i = 0; i < index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Checks if list is empty.
/// @param list Straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Straight list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero
    // and negating it makes function return true only if full
    return !(~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Straight list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    straight_list_s replica = { 0 };

    size_t current_list = list.head;
    // double pointer since this also works on copying straight list
    size_t * current_copy = &(replica.head);
    for (size_t i = 0; i < list.size; ++i) {
        (*current_copy) = i; // set head and indexes at list copy's next array to proper index

        if (!(replica.size % REALLOC_STRAIGHT_LIST_CHUNK)) {
            replica.elements = STRAIGHT_LIST_REALLOC(replica.elements, sizeof(STRAIGHT_LIST_DATA_TYPE) * (replica.size + REALLOC_STRAIGHT_LIST_CHUNK));
            STRAIGHT_LIST_ASSERT(replica.elements && "[ERROR] Memory allocation failed");
            replica.next = STRAIGHT_LIST_REALLOC(replica.next, sizeof(size_t) * (replica.size + REALLOC_STRAIGHT_LIST_CHUNK));
            STRAIGHT_LIST_ASSERT(replica.next && "[ERROR] Memory allocation failed");
        }
        replica.size++;

        // set element copy to list copy at index i to automatically remove holes from copy
        replica.elements[i] = copy ? copy(list.elements[current_list]) : list.elements[current_list];

        current_list = list.next[current_list]; // go to next list node
        current_copy = replica.next + (*current_copy); // go to next copy list's pointer to node
    }

    return replica;
}

/// @brief Clears the list of elements.  Similar to 'destroy_straight_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; destroy && s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }

    // set cleared list's empty stack and head to zero and keep allocated memory
    list->empty_head = list->empty_size = list->head = 0;
}

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to straight list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering may NOT remain
/// (it may change if there are holes in the list). This may not apply for other forward list 'forevery_forward_list'
/// implementations and a note will reflect that.
static inline void forevery_straight_list(straight_list_s * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (list->empty_size) { // removes holes at the expense of breaking the list
        stack_size--;

        if (empty_index > stack_size) {
            empty_index = list->next[empty_index];
        }

        STRAIGHT_LIST_DATA_TYPE element = list->elements[empty_index];
        list->elements[empty_index] = list->elements[stack_size];
        list->elements[stack_size] = element;

        const size_t index = list->next[empty_index];
        list->next[empty_index] = list->next[stack_size];
        list->next[stack_size] = empty_index;
        empty_index = index;

        list->empty_size--;
    }

    manage(list->elements, list->size, args);

    size_t * current = (&list->head);
    for (size_t i = 0; i < list->size; ++i) {
        (*current) = i;
        current = list->next + (*current);
    }
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Straight list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'forevery_straight_list' can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    size_t base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        size_t current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(element, list.elements[current]) : memcmp(&element, list.elements + current, sizeof(STRAIGHT_LIST_DATA_TYPE));

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

/// @brief Iterates through straight list elements without changing list ordering.
/// @param list Pointer to straight list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s const * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(list->elements + current, args)) { // if operate returns false then stop loop
            return;
        }

        current = list->next[current];
    }
}

#elif STRAIGHT_LIST_MODE == FINITE_PRERPOCESSOR_STRAIGHT_LIST

#ifndef PREPROCESSOR_FORWARD_LIST_SIZE

#define PREPROCESSOR_FORWARD_LIST_SIZE (1 << 10)

#elif PREPROCESSOR_FORWARD_LIST_SIZE <= 0

#error 'PREPROCESSOR_FORWARD_LIST_SIZE' cannot be zero

#endif

/// @note The FINITE_ALLOCATED_STRAIGHT_LIST is a list that uses two stack implementations, a linked list based
/// 'empty stack' for empty elements that make up holes in the straight_list elements' array and an array based
/// 'load stack' with holes. When adding an element the linked list first check if it can pop from the 'empty stack'
/// to fill in the holes, when there are no holes (meaning 'empty stack' is empty) the straight list pushes the element
/// to the top of the array based 'loaded stack'
/// @brief The straight list is a linked list.
typedef struct straight_list {
    size_t size, empty_size, head, empty_head;
    STRAIGHT_LIST_DATA_TYPE elements[PREPROCESSOR_FORWARD_LIST_SIZE];
    size_t next[PREPROCESSOR_FORWARD_LIST_SIZE];
} straight_list_s;

/// @brief Creates an empty straight list of zero size.
/// @return Straight list structure.
static inline straight_list_s create_straight_list(void) {
    const straight_list_s list = { .empty_head = 0, .empty_size = 0, .head = 0, .size = 0, };
    return list;
}

/// @brief Destroys the straight list and sets size to zero. The destroyed list should not be used after calling this
/// function, else create a new list.
/// @param list Pointer to straight list structure.
/// @param destroy Function pointer to destroy/free each element in straight list. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; destroy && s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }

    list->empty_head = list->empty_size = list->head = list->size = 0;
}

/// @brief Inserts an element to any place in the list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to insert element at.
/// @param element Element to insert into list.
static inline void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size < PREPROCESSOR_FORWARD_LIST_SIZE && "[ERROR] List reached maximum size.");
    STRAIGHT_LIST_ASSERT(index <= list->size && "[ERROR] Index bigger than size");
    STRAIGHT_LIST_ASSERT(~list->size && "[ERROR] List size will overflow.");

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

/// @brief Removes first element in straight list based on element parameter comparison.
/// @param list Pointer to straight list structure.
/// @param element Element to remove from list.
/// @param compare Function pointer that compares element parameter to elements in list.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");

    size_t * current = &(list->head);
    for (size_t i = 0; i < list->size; ++i) {
        const int comparison = compare ? compare(list->elements[(*current)], element) : memcmp(list->elements + (*current), &element, sizeof(STRAIGHT_LIST_DATA_TYPE));

        if (0 != comparison) { // early continue in order to remove one needless nesting level
            current = list->next + (*current);
            continue;
        }

        list->size--;
        STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)];

        if (list->next[(*current)] != list->size) { // push empty index to 'empty stack'
            list->next[(*current)] = list->empty_head;
            list->empty_head = (*current);
            list->empty_size++;
        }

        (*current) = list->next[(*current)];

        if (!list->size) { // if list is empty set empty stack elements to zero
            list->empty_head = list->empty_size = 0;
        }

        return found;
    }

    STRAIGHT_LIST_ASSERT(0 && "[ERROR] Element not found in list."); // if element is not found in list then that is an error
    // and exit failure is returned, since the function returns the removed element, element can contain allocated memory
    exit(EXIT_FAILURE);
}

/// @brief Removes element at index in straight list.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to remove element at.
/// @return Removed element from list.
static inline STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");
    STRAIGHT_LIST_ASSERT(list->size && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(list->head && "[ERROR] Can't remove from empty list.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Index greater than size");

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) {
        current = list->next + (*current);
    }

    list->size--;
    STRAIGHT_LIST_DATA_TYPE found = list->elements[(*current)];

    if (list->next[(*current)] != list->size) { // push empty index to 'empty stack'
        list->next[(*current)] = list->empty_head;
        list->empty_head = (*current);
        list->empty_size++;
    }

    (*current) = list->next[(*current)];

    if (!list->size) { // if list is empty set empty stack elements to zero
        list->empty_head = list->empty_size = 0;
    }

    return found;
}

/// @brief Reverses straight list.
/// @param list Pointer to straight list structure.
static inline void reverse_straight_list(straight_list_s * list) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

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

/// @brief Splices/joins/merges two lists together while destroying source list.
/// @param destination Pointer to straight list structure to splice into.
/// @param source Pointer to straight list structure to splice from. If source is zero destination list does not change.
/// @param index Index at destination list to splice source list into.
static inline void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index) {
    STRAIGHT_LIST_ASSERT(destination && "[ERROR] 'list_one' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(source && "[ERROR] 'list_two' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(destination != source && "[ERROR] Lists can't be the same.");
    STRAIGHT_LIST_ASSERT(destination->size + source->size <= PREPROCESSOR_FORWARD_LIST_SIZE && "[ERROR] Combined lists' sizes exceed max size of new list.");
    STRAIGHT_LIST_ASSERT(index <= destination->size && "[ERROR] index can't exceed list_one's size");

    size_t * current_dest = &(destination->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index position
        current_dest = destination->next + (*current_dest);
    }

    size_t * last_source = &(source->head);
    while (source->size && destination->empty_size) {
        memcpy(destination->elements + destination->empty_head, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->size++;

        const size_t temp = destination->empty_head;
        destination->empty_head = destination->next[destination->empty_head];

        destination->next[temp] = (*current_dest);
        (*current_dest) = temp;

        destination->empty_size--;

        source->size--;
        current_dest = destination->next + (*current_dest);
        last_source = source->next + (*last_source);
    }

    while (source->size) {
        memcpy(destination->elements + destination->size, source->elements + (*last_source), sizeof(STRAIGHT_LIST_DATA_TYPE));
        destination->next[destination->size] = (*current_dest);
        (*current_dest) = destination->size;
        destination->size++;

        source->size--;
        current_dest = destination->next + (*current_dest);
        last_source = source->next + (*last_source);
    }

    STRAIGHT_LIST_FREE(source->elements);
    STRAIGHT_LIST_FREE(source->next);
    (*source) = (straight_list_s) { 0 }; // set source list to zero (i. e. destroy it)
}

/// @brief Splits list and returns new list with specified elements.
/// @param list Pointer to straight list structure.
/// @param index Zero based index to start split from.
/// @param size Size to remove list by. If size is zero an empty list is returned.
/// @return New split list.
static inline straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] List pointer is NULL");
    STRAIGHT_LIST_ASSERT(size <= list->size && "[ERROR] Size parameter bigger than list size.");
    STRAIGHT_LIST_ASSERT(index < list->size && "[ERROR] Can only split at index less than list size");
    STRAIGHT_LIST_ASSERT(index + size <= list->size && "[ERROR] Can't split at index and size beyond list's size");

    straight_list_s split = { .empty_head = 0, .empty_size = 0, .size = size, .head = 0, };

    size_t * current = &(list->head);
    for (size_t i = 0; i < index; ++i) { // iterate to pointer to node at index
        current = list->next + (*current);
    }

    size_t last = (*current); // create pointer to node to point to node after split's last note
    size_t * current_split = &(split.head); // create pointer to node to add nodes to split list
    for (size_t i = 0; i < size; ++i) {
        split.elements[i] = list->elements[last];
        (*current_split) = i; // set split's pointer-to node to last

        last = list->next[last]; // increment last's pointer to node to next pointer to node
        current_split = split.next + (*current_split); // increment split's pointer to node to next pointer to node
    }

    (*current) = last; // set previous' next node to last list's node (if size parameter is 0 then nothing changes)

    return split;
}

/// @brief Gets element at index.
/// @param list Straight list structure.
/// @param index Zero based index of element in list.
/// @return Element at index in list.
static inline STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s list, const size_t index) {
    STRAIGHT_LIST_ASSERT(list.head && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(list.size && "[ERROR] Can't get element from empty list.");
    STRAIGHT_LIST_ASSERT(index < list.size && "[ERROR] 'index' parameter exceeds list size.");

    size_t current = list.head;
    for (size_t i = 0; i < index; ++i) {
        current = list.next[current];
    }

    return list.elements[current];
}

/// @brief Checks if list is empty.
/// @param list Straight list structure.
/// @return 'true' if list is empty, 'false' otherwise.
static inline bool is_empty_straight_list(const straight_list_s list) {
    return (list.size == 0);
}

/// @brief Checks if list is full.
/// @param list Straight list structure.
/// @return true if list is full, 'false' otherwise.
static inline bool is_full_straight_list(const straight_list_s list) {
    // if size has all bits set to 1 it is considered full, therefore switching bits will make them all zero
    // and negating it makes function return true only if full
    return !(list.size < PREPROCESSOR_FORWARD_LIST_SIZE && ~list.size);
}

/// @brief Creates a deep or shallow copy of a list based on copy function pointer.
/// @param list Straight list structure.
/// @param copy Function pointer to create a copy of an element. Can be NULL if copying by assignment operator.
/// @return Returns a copy of a list.
static inline straight_list_s copy_straight_list(const straight_list_s list, const copy_straight_list_fn copy) {
    straight_list_s replice = {.head = 0, .size = list.size, .empty_head = 0, .empty_size = 0, };

    size_t current_list = list.head;
    // double pointer since this also works on copying straight list
    size_t * current_copy = &(replice.head);
    for (size_t i = 0; i < list.size; ++i) {
        // set element copy to list copy at index i to automatically remove holes from copy
        replice.elements[i] = copy ? copy(list.elements[current_list]) : list.elements[current_list];
        (*current_copy) = i; // set head and indexes at list copy's next array to proper index

        current_list = list.next[current_list]; // go to next list node
        current_copy = replice.next + (*current_copy); // go to next copy list's pointer to node
    }

    return replice;
}

/// @brief Clears the list of elements.  Similar to 'destroy_straight_list', but the list can continue to be used normally.
/// @param list Forward list structure.
/// @param destroy Function pointer to destroy/free each element in straight list.
static inline void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter is NULL.");

    size_t current = list->head; // pointer to tail since ordering does not matter while destroying list
    for (size_t s = 0; destroy && s < list->size; ++s) { // check if destroy function is specified to destroy elements
        destroy(list->elements + current);
        current = list->next[current];
    }

    // set cleared list's empty stack and head to zero and keep allocated memory
    list->empty_head = list->empty_size = list->head = 0;
}

/// @brief Creates a continuous array of list elements to manage using function pointer.
/// @param list Pointer to straight list structure.
/// @param manage Function pointer to manage the array of elements based on element count/size and specified args.
/// @param args Void pointer arguments for 'manage' function.
/// @note If 'manage' does not change the order of elements then the original element ordering may NOT remain
/// (it may change if there are holes in the list). This may not apply for other forward list 'forevery_forward_list'
/// implementations and a note will reflect that.
static inline void forevery_straight_list(straight_list_s * list, const manage_straight_list_fn manage, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t empty_index = list->empty_head;
    size_t stack_size = list->size + list->empty_size;
    while (list->empty_size) { // removes holes at the expense of breaking the list
        stack_size--;

        if (empty_index > stack_size) {
            empty_index = list->next[empty_index];
        }

        STRAIGHT_LIST_DATA_TYPE element = list->elements[empty_index];
        list->elements[empty_index] = list->elements[stack_size];
        list->elements[stack_size] = element;

        const size_t index = list->next[empty_index];
        list->next[empty_index] = list->next[stack_size];
        list->next[stack_size] = empty_index;
        empty_index = index;

        list->empty_size--;
    }

    manage(list->elements, list->size, args);

    size_t * current = (&list->head);
    for (size_t i = 0; i < list->size; ++i) {
        (*current) = i;
        current = list->next + (*current);
    }
}

/// @brief Performs a binary search on sorted straight list.
/// @param list Straight list structure.
/// @param element Element to search in list.
/// @param compare Function pointer to compare elements in list. Zero if they're the same, negative if less than,
/// positive if greater than.
/// @return 'true' if element was found, 'false' otherwise.
/// @note The list must be sorted based on 'compare' function pointer. 'forevery_straight_list' can be used to sort the list.
static inline bool binary_search_straight_list(const straight_list_s list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare) {
    // this implementation is based on a similar array based binary search algorithm:
    // https://github.com/gcc-mirror/gcc/blob/master/libiberty/bsearch.c
    size_t base = list.head; // base starting from list tail
    for (size_t limit = list.size; limit != 0; limit >>= 1) {
        // start from next element to move from tail and to ignore alread compared elements
        size_t current = base;
        for (size_t i = 0; i < limit >> 1; ++i) { // iterate to middle element in list
            current = list.next[current];
        }

        const int comparison = compare ? compare(element, list.elements[current]) : memcmp(&element, list.elements + current, sizeof(STRAIGHT_LIST_DATA_TYPE));

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

/// @brief Iterates through straight list elements without changing list ordering.
/// @param list Pointer to straight list structure.
/// @param operate Function pointer to operate on every single element pointer while using arguments.
/// @param args Arguments for 'operate' function pointer.
static inline void foreach_straight_list(straight_list_s * list, const operate_straight_list_fn operate, void * args) {
    STRAIGHT_LIST_ASSERT(list && "[ERROR] 'list' parameter pointer is NULL.");
    STRAIGHT_LIST_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    size_t current = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (!operate(list->elements + current, args)) { // if operate returns false then stop loop
            return;
        }

        current = list->next[current];
    }
}

#endif

#endif // STRAIGHT_LIST_H
