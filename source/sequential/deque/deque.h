#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>  // imports size_t and NULL
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


#define INFINITE_LIST_DEQUE_MODE       201
#define FINITE_ALLOCATED_DEQUE_MODE    202
#define INFINITE_REALLOC_DEQUE_MODE    203
#define FINITE_PREPROCESSOR_DEQUE_MODE 204

//#define DEQUE_MODE INFINITE_LIST_DEQUE_MODE
//#define DEQUE_MODE FINITE_ALLOCATED_DEQUE_MODE
//#define DEQUE_MODE INFINITE_REALLOC_DEQUE_MODE
//#define DEQUE_MODE FINITE_PREPROCESSOR_DEQUE_MODE
// Queue mode that can be set to INFINITE_LIST_DEQUE_MODE, FINITE_ALLOCATED_DEQUE_MODE, INFINITE_REALLOC_DEQUE_MODE or
// FINITE_PRERPOCESSOR_DEQUE.
// Default: INFINITE_LIST_DEQUE_MODE
#ifndef DEQUE_MODE

#define DEQUE_MODE INFINITE_LIST_DEQUE_MODE

#endif

// Check to make sure a valid deque mode is selected.
#if (DEQUE_MODE != INFINITE_LIST_DEQUE_MODE)    && (DEQUE_MODE != FINITE_ALLOCATED_DEQUE_MODE) && \
(DEQUE_MODE != INFINITE_REALLOC_DEQUE_MODE) && (DEQUE_MODE != FINITE_PREPROCESSOR_DEQUE_MODE)

#error Invalid type of deque mode.

#endif

// Queue data type to specify what datatype to deque.
// DEFAULT: void *
#ifndef DEQUE_DATA_TYPE

#define DEQUE_DATA_TYPE void*

#endif

#ifndef DEQUE_ASSERT

#include <assert.h>  // imports assert for debugging
#define DEQUE_ASSERT assert

#endif

#if !defined(DEQUE_REALLOC) && !defined(DEQUE_FREE)

#include <stdlib.h>

#ifndef DEQUE_REALLOC

#define DEQUE_REALLOC realloc

#endif

#ifndef DEQUE_FREE

#define DEQUE_FREE free

#endif

#elif !defined(DEQUE_REALLOC)

#error Queue reallocator macro is not defined!

#elif !defined(DEQUE_FREE)

#error Queue free macro is not defined!

#endif

/// Function pointer that creates a deep element copy.
typedef DEQUE_DATA_TYPE (*copy_deque_fn)    (const DEQUE_DATA_TYPE);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_deque_fn) (DEQUE_DATA_TYPE *);
/// Function pointer that changes an element pointer using void pointer arguments if needed.
typedef bool            (*operate_deque_fn) (DEQUE_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void            (*manage_deque_fn)  (DEQUE_DATA_TYPE *, const size_t, void *);

#if   DEQUE_MODE == INFINITE_LIST_DEQUE_MODE

// Queue list array size.
// DEFAULT: (1 << 5) or 1024
#ifndef LIST_ARRAY_DEQUE_CHUNK

#define LIST_ARRAY_DEQUE_CHUNK (1 << 5)

#elif LIST_ARRAY_DEQUE_CHUNK <= 0

#error 'LIST_ARRAY_DEQUE_CHUNK' cannot be less than or equal to 0.

#endif

/// @brief Linked list of arrays that appends new list element at the end after array is full.
struct deque_list_array {
    struct deque_list_array * next; // next linked list array
    struct deque_list_array * prev; // previous linked list array
    DEQUE_DATA_TYPE elements[LIST_ARRAY_DEQUE_CHUNK]; // array to store elements
};

/// @brief Deque circular doubly linked list data structure that allows constant removal from its front and back.
typedef struct deque {
    struct deque_list_array * head; // head node pointer of doubly linked list
    size_t current, size; // current index in node array and deque size
} deque_s;

/// @brief Creates an empty deque.
/// @return Empty deque.
static inline deque_s create_deque(void) {
    return (deque_s) { 0 };
}

/// @brief Destroys deque with all its elements using a destroy function pointer.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque needs to be created again after destroying it.
static inline void destroy_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    struct deque_list_array * current = deque->head; // save head index as current node
    for (size_t start = deque->current; deque->size; start = 0) { // for every node in deque list until size is not zero
        size_t i = start; // set i outside of nested for loop to save its value
        for (; i < (deque->size + start) && i < LIST_ARRAY_DEQUE_CHUNK; ++i) { // destroy each element in node
            destroy(current->elements + i);
        }
        deque->size -= (i - start); // subtract absolute value of i and start from deque's size

        struct deque_list_array * temp = current; // save current node as temporary to free later
        current = current->next; // go to next node
        DEQUE_FREE(temp); // free temporary current node
    }

    (*deque) = (deque_s) { 0 }; // set everything to zero
}

/// Clears deque with all its elements using a destroy function pointer to later use without creating a new deque.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque DOES NOT need to be created again after destroying it.
static inline void clear_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    struct deque_list_array * current = deque->head; // save head index as current node
    for (size_t start = deque->current; deque->size; start = 0) { // for every node in deque list until size is not zero
        size_t i = start; // set i outside of nested for loop to save its value
        for (; i < (deque->size + start) && i < LIST_ARRAY_DEQUE_CHUNK; ++i) { // destroy each element in node
            destroy(current->elements + i);
        }

        deque->size -= (i - start); // subtract absolute value of i and start from deque's size

        struct deque_list_array * temp = current; // save current node as temporary to free later
        current = current->next; // go to next node
        DEQUE_FREE(temp); // free temporary current node
    }

    (*deque) = (deque_s) { 0 }; // set everything to zero
}

/// @brief Copies the deque and all its elements into a new structure.
/// @param deque Deque structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in deque.
/// @return A copy of the specified 'deque' parameter.
static inline deque_s copy_deque(const deque_s deque, const copy_deque_fn copy) {
    DEQUE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    deque_s replika = { .current = deque.current, .head = NULL, .size = deque.size, };

    struct deque_list_array const * current_deque = deque.head; // save head index as current node
    struct deque_list_array ** current_replika = &(replika.head);
    size_t remaining_size = deque.size; // save remaining size as parameter to decrement for loop
    for (size_t start = deque.current; remaining_size; start = 0) { // while remaining size is not zero
        struct deque_list_array * node = DEQUE_REALLOC(NULL, sizeof(struct deque_list_array));
        DEQUE_ASSERT(node && "[ERROR] Memory allocation failed.");

        size_t i = start;
        for (; i < remaining_size + start && i < LIST_ARRAY_DEQUE_CHUNK; ++i) { // operate on each element in node
            node->elements[i] = copy(current_deque->elements[i]);
        }

        (*current_replika) = node->prev = node; // *current_copy and node's prev will point to node
        node->next = replika.head; // node's next points to head (if *current_copy is head then node's next points to node)
        // node's prev points to list_copy.head's prev (if *current_copy is head then head/node->prev is node, else node->prev is previous node)
        node->prev = replika.head->prev;
        replika.head->prev = node; // head's prev points to node (if *current_copy is head then head/node prev is node, else head prev is last node)

        remaining_size -= (i - start); // decrement remaining size by operated size of current node

        current_replika = &((*current_replika)->next); // go to next's node pointer
        current_deque = current_deque->next; // go to next node
    }

    return replika;
}

/// Checks if deque is empty.
/// @param deque Deque structure to check.
/// @return true if deque is empty, false otherwise.
static inline bool is_empty_deque(const deque_s deque) {
    return (deque.size == 0);
}

/// Checks if deque is full.
/// @param deque Deque structure to check.
/// @return true if deque is full, false otherwise.
static inline bool is_full_deque(const deque_s deque) {
    return !(~(deque.size));
}

/// @brief Enqueues specified element to deque's front.
/// @param deque Deque data structure to enqueue element infront.
/// @param element Element to enqueue infront.
static inline void enqueue_front(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");

    if (!(deque->current)) { // if deque's previous current 'underflows' in node array due to inserting element to front
        deque->current = LIST_ARRAY_DEQUE_CHUNK; // make current into list array chunk size to prevent future underflow

        struct deque_list_array * node = DEQUE_REALLOC(NULL, sizeof(struct deque_list_array));
        DEQUE_ASSERT(node && "[ERROR] Memory allocation failed.");

        if (deque->head) { // if head exists
            node->next = deque->head; // node's next is head
            node->prev = deque->head->prev; // node's previous is tail/head's previous

            deque->head = deque->head->prev = node; // head's previous is node and node becomes head
        } else { // else head does not exist
            deque->head = node->next = node->prev = node; // node's next and previous is node and node becomes head
        }
    }

    deque->size++; // increment size for new element insertion
    deque->current--; // if current was 0 then current will be 'LIST_ARRAY_DEQUE_CHUNK - 1'
    memcpy(deque->head->elements + deque->current, &element, sizeof(DEQUE_DATA_TYPE)); // copy element into deque's head
}

/// @brief Enqueues specified element to deque's back.
/// @param deque Deque data structure to enqueue element to back.
/// @param element lement to enqueue to back.
static inline void enqueue_back(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");

    const size_t next_index = ((deque->current + deque->size) % LIST_ARRAY_DEQUE_CHUNK);
    if (!next_index) { // if next index to insert into is zero
        struct deque_list_array * node = DEQUE_REALLOC(NULL, sizeof(struct deque_list_array));
        DEQUE_ASSERT(node && "[ERROR] Memory allocation failed.");

        if (deque->head) { // if head exists
            node->next = deque->head; // node's next is head
            node->prev = deque->head->prev; // node's previous is tail/head's previous

            deque->head->prev = deque->head->prev->next = node; // node is tail's next and head's previous, and node becomes tail
        } else { // else head does not exist
            deque->head = node->next = node->prev = node; // node's next and previous is node and node becomes head
        }
    }

    deque->size++; // increment size for new element insertion
    memcpy(deque->head->prev->elements + next_index, &element, sizeof(DEQUE_DATA_TYPE)); // copy element into deque's tail
}

/// @brief Peeks element at front of deque.
/// @param deque Deque data structure to peek from front.
/// @return Peeked element at front of deque.
static inline DEQUE_DATA_TYPE peek_front(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Can't peek empty deque.");
    DEQUE_ASSERT(deque.head && "[ERROR] Can't peek empty deque.");

    return deque.head->elements[deque.current]; // return element at current index
}

/// @brief Peeks element at back of deque.
/// @param deque Deque data structure to peek from back.
/// @return Peeked element at back of deque.
static inline DEQUE_DATA_TYPE peek_back(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Can't peek empty deque.");
    DEQUE_ASSERT(deque.head && "[ERROR] Can't peek empty deque.");
    DEQUE_ASSERT(deque.head->prev && "[ERROR] Can't peek empty deque.");

    return deque.head->prev->elements[(deque.current + deque.size - 1) % LIST_ARRAY_DEQUE_CHUNK]; // return element at last index
}

/// Dequeues element at front of deque.
/// @param deque Deque data structure to dequeue from front.
/// @return Dequeued element at front of deque.
static inline DEQUE_DATA_TYPE dequeue_front(deque_s * deque) {
    DEQUE_ASSERT(deque->size && "[ERROR] Can't dequeue empty deque.");
    DEQUE_ASSERT(deque->head && "[ERROR] Can't dequeue empty deque.");

    DEQUE_DATA_TYPE removed = deque->head->elements[deque->current]; // save dequeued element
    deque->current++; // increment current index since it's removing from front (like a queue)
    deque->size--; // decrement deque's size since front elements gets removed (like a queue)
    // if deque's current index is equal to list chunk or deque is empty free head node
    if ((LIST_ARRAY_DEQUE_CHUNK == deque->current) || !(deque->size)) {
        struct deque_list_array * empty_head = deque->head; // temporary save pointer to head node

        deque->head->next->prev = deque->head->prev; // set head next's previous pointer to tail/head's previous
        deque->head->prev->next = deque->head->next; // set tail's next node to head's next node

        deque->head = deque->size ? deque->head->next : NULL; // if deque's size is zero then set head to NULL, else it's head's next node
        DEQUE_FREE(empty_head); // free temporary saved head node
        deque->current = 0; // reset current index to zero/beginning
    }

    return removed;
}

/// Dequeues element at back of deque.
/// @param deque Deque data structure to dequeue from back.
/// @return Dequeued element at back of deque.
static inline DEQUE_DATA_TYPE dequeue_back(deque_s * deque) {
    DEQUE_ASSERT(deque->size && "[ERROR] Can't dequeue empty deque.");
    DEQUE_ASSERT(deque->head && "[ERROR] Can't dequeue empty deque.");

    const size_t current_index = (deque->current + deque->size - 1) % LIST_ARRAY_DEQUE_CHUNK; // calculate back element's index
    DEQUE_DATA_TYPE removed = deque->head->prev->elements[current_index]; // tempoorary save dequeued back element
    deque->size--; // decrement only size since it's removing from the back (like a stack)

    if (!current_index || !(deque->size)) { // if current index at back is zero or deque is empty remove empty tail/head
        struct deque_list_array * empty_tail = deque->head->prev; // temporary save pointer to head node

        deque->head->prev = deque->head->prev->prev; // head's tail pointer equals tail's previous
        deque->head->prev->prev->next = deque->head; // tail previous' next equals head

        if (!deque->size) { // if deque's size is zero then make its head NULL
            deque->head = NULL;
        }

        DEQUE_FREE(empty_tail); // free temporary saved tail node
    }

    return removed;
}

/// Iterates over each element in deque from front to back and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_deque(deque_s const * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'deque' parameter is NULL.");

    struct deque_list_array * current = deque->head; // save head node as current pointer
    size_t remaining_size = deque->size; // save remaining size as parameter to decrement for loop
    for (size_t start = deque->current; remaining_size; start = 0) { // while remaining size is not zero
        size_t i = start;
        for (; i < remaining_size && i < LIST_ARRAY_DEQUE_CHUNK; ++i) { // operate on each element in node
            if (!operate(current->elements + i, args)) { // if operate returns false then terminate main function
                return;
            }
        }

        remaining_size -= (i - start); // decrement remaining size by operated size of current node
        current = current->next; // go to next node
    }
}

/// Iterates over each element in deque from back to front and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_reverse_deque(deque_s const * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'deque' parameter is NULL.");

    struct deque_list_array * current = deque->head; // save head node as current pointer
    size_t remaining_size = deque->size; // save remaining size as parameter to decrement for loop
    size_t end = (deque->current + deque->size) % LIST_ARRAY_DEQUE_CHUNK; // calculate end index
    // for loop starts from tail backwards until remaining size starting from current index is not less than chunk size
    for (;(deque->current + remaining_size) >= LIST_ARRAY_DEQUE_CHUNK; end = LIST_ARRAY_DEQUE_CHUNK) {
        current = current->prev; // early go to previous node to start from tail

        size_t i = 0; // extract i index to use in subtraction
        const size_t smaller_size = end < remaining_size ? end : remaining_size;
        for (; i < smaller_size; ++i) { // while i is less than the smaller size
            if (!operate(current->elements + (smaller_size - i - 1), args)) { // operate on
                return;
            }
        }

        remaining_size -= i;
    }

    for (size_t i = 0; i < remaining_size; ++i) { // if remaining size remains at head node
        if (!operate(current->elements + (remaining_size - i - 1) + deque->current, args)) { // operate on current/head node
            return;
        }
    }
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param deque Deque data structure to manage its every element.
/// @param manage Manage function pointer to manage deque's elements as an array using deque's size and generic arguments.
/// @param args Generic void pointer arguments to manage array of elements with, can be NULL.
static inline void map_deque(deque_s const * deque, const manage_deque_fn manage, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(manage && "[ERROR] 'deque' parameter is NULL.");

    DEQUE_DATA_TYPE * elements_array = DEQUE_REALLOC(NULL, deque->size * sizeof(DEQUE_DATA_TYPE));
    DEQUE_ASSERT(elements_array && "[ERROR] Memory alloction failed.");

    size_t index = 0;
    struct deque_list_array * current = deque->head;
    size_t remaining_size = deque->size;
    for (size_t start = deque->current; remaining_size; start = 0) {
        size_t i = start;
        for (; i < remaining_size && i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
            elements_array[index++] = current->elements[i];
        }

        remaining_size -= (i - start);
        current = current->next;
    }

    manage(elements_array, deque->size, args);

    index = 0;
    current = deque->head;
    remaining_size = deque->size;
    for (size_t start = deque->current; remaining_size; start = 0) {
        size_t i = start;
        for (; i < remaining_size && i < LIST_ARRAY_DEQUE_CHUNK; ++i) {
            current->elements[i] = elements_array[index++];
        }

        remaining_size -= (i - start);
        current = current->next;
    }

    DEQUE_FREE(elements_array);
}

#elif DEQUE_MODE == FINITE_ALLOCATED_DEQUE_MODE

typedef struct deque {
    size_t current, max, size;
    DEQUE_DATA_TYPE * elements;
} deque_s;

/// @brief Creates an empty deque.
/// @return Empty deque.
/// @param max Maximum deque size.
static inline deque_s create_deque(const size_t max) {
    DEQUE_ASSERT(max && "[ERROR] Deque's maximum size can't be zero."); // check if maximum is not zero

    const deque_s deque = { // create deque with allocated memory array of max parameter size
        .current = max >> 1, .max = max, .size = 0,
        .elements = DEQUE_REALLOC(NULL, max * sizeof(DEQUE_DATA_TYPE)),
    };
    DEQUE_ASSERT(deque.elements && "[ERROR] Memory allocation failed."); // check if memory allocation succeeded

    return deque; // return initialied deque
}

/// @brief Destroys deque with all its elements using a destroy function pointer.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque needs to be created again after destroying it.
static inline void destroy_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    // calculate size of elements to the right of current index
    const size_t right_size = (deque->current + deque->size) > deque->max ? deque->max - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size; ++i) { // for each element from current to right size destroy it
        destroy(deque->elements + i);
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) { // for each element from 0 to left size destroy it
        destroy(deque->elements + i);
    }

    DEQUE_FREE(deque->elements); // free elements array created by create function

    deque->size = 0;
    deque->elements = NULL;
}

/// Clears deque with all its elements using a destroy function pointer to later use without creating a new deque.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque DOES NOT need to be created again after destroying it.
static inline void clear_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    // calculate size of elements to the right of current index
    const size_t right_size = (deque->current + deque->size) > deque->max ? deque->max - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size; ++i) { // for each element from current to right size destroy it
        destroy(deque->elements + i);
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) { // for each element from 0 to left size destroy it
        destroy(deque->elements + i);
    }

    deque->current = deque->max >> 1; // set current index to middle of maximum size
    deque->size = 0; // set current index and
}

/// @brief Copies the deque and all its elements into a new structure.
/// @param deque Deque structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in deque.
/// @return A copy of the specified 'deque' parameter.
static inline deque_s copy_deque(const deque_s deque, const copy_deque_fn copy) {
    DEQUE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    DEQUE_ASSERT(deque.max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque.elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque.size <= deque.max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < deque.max && "[ERROR] Deque's current index must be less than maximum size.");

    const deque_s replika = {
        .current = deque.current, .max = deque.max, .size = deque.size,
        .elements = DEQUE_REALLOC(NULL, sizeof(DEQUE_DATA_TYPE) * deque.max),
    };
    DEQUE_ASSERT(replika.elements && "[ERROR] Memory allocation failed.");

    const size_t right_size = (deque.current + deque.size) > deque.max ? deque.max - deque.current : deque.size;
    for (size_t i = deque.current; i < right_size + deque.current; ++i) { // for each element from current to right size destroy it
        replika.elements[i] = copy(deque.elements[i]);
    }
    for (size_t i = 0; i < deque.size - right_size; ++i) { // for each element from 0 to left size destroy it
        replika.elements[i] = copy(deque.elements[i]);
    }

    return replika;
}

/// Checks if deque is empty.
/// @param deque Deque structure to check.
/// @return true if deque is empty, false otherwise.
static inline bool is_empty_deque(const deque_s deque) {
    DEQUE_ASSERT(deque.max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque.elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque.size <= deque.max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < deque.max && "[ERROR] Deque's current index must be less than maximum size.");

    return (0 == deque.size);
}

/// Checks if deque is full.
/// @param deque Deque structure to check.
/// @return true if deque is full, false otherwise.
static inline bool is_full_deque(const deque_s deque) {
    DEQUE_ASSERT(deque.max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque.elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque.size <= deque.max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < deque.max && "[ERROR] Deque's current index must be less than maximum size.");

    return (deque.size == deque.max);
}

/// @brief Enqueues specified element to deque's front.
/// @param deque Deque data structure to enqueue element infront.
/// @param element Element to enqueue infront.
static inline void enqueue_front(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size < deque->max && "[ERROR] Deque is full.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    // if current underflows then circle it to max
    if (!(deque->current)) {
        deque->current = deque->max;
    }
    deque->current--;
    deque->size++;
    memcpy(deque->elements + deque->current, &element, sizeof(DEQUE_DATA_TYPE));
}

/// @brief Enqueues specified element to deque's back.
/// @param deque Deque data structure to enqueue element to back.
/// @param element lement to enqueue to back.
static inline void enqueue_back(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size < deque->max && "[ERROR] Deque is full.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t next_index = (deque->current + deque->size) % deque->max;
    deque->size++;
    memcpy(deque->elements + next_index, &element, sizeof(DEQUE_DATA_TYPE));
}

/// @brief Peeks element at front of deque.
/// @param deque Deque data structure to peek from front.
/// @return Peeked element at front of deque.
static inline DEQUE_DATA_TYPE peek_front(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque.max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque.elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque.size <= deque.max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < deque.max && "[ERROR] Deque's current index must be less than maximum size.");

    return deque.elements[deque.current];
}

/// @brief Peeks element at back of deque.
/// @param deque Deque data structure to peek from back.
/// @return Peeked element at back of deque.
static inline DEQUE_DATA_TYPE peek_back(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque.max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque.elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque.size <= deque.max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < deque.max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t current_index = (deque.current + deque.size - 1) % deque.max;
    return deque.elements[current_index];
}

/// Dequeues element at front of deque.
/// @param deque Deque data structure to dequeue from front.
/// @return Dequeued element at front of deque.
static inline DEQUE_DATA_TYPE dequeue_front(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    DEQUE_DATA_TYPE removed = deque->elements[deque->current++];
    deque->size--;

    if (deque->current == deque->max) {
        deque->current = 0;
    }

    return removed;
}

/// Dequeues element at back of deque.
/// @param deque Deque data structure to dequeue from back.
/// @return Dequeued element at back of deque.
static inline DEQUE_DATA_TYPE dequeue_back(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t current_index = (deque->current + deque->size - 1) % deque->max;
    DEQUE_DATA_TYPE removed = deque->elements[current_index];
    deque->size--;

    return removed;
}

/// Iterates over each element in deque from front to back and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_deque(deque_s const * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (deque->current + deque->size) > deque->max ? deque->max - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size + deque->current; ++i) {
        if (!operate(deque->elements + i, args)) {
            return;
        }
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) {
        if (!operate(deque->elements + i, args)) {
            return;
        }
    }
}

/// Iterates over each element in deque from back to front and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_reverse_deque(deque_s const * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (deque->current + deque->size) > deque->max ? deque->max - deque->current : deque->size;
    const size_t left_size = deque->size - right_size;
    for (size_t i = 0; i < left_size; ++i) {
        if (!operate(deque->elements + (left_size - i - 1), args)) {
            return;
        }
    }
    for (size_t i = 0; i < right_size; ++i) {
        if (!operate(deque->elements + (right_size - i - 1) + deque->current, args)) {
            return;
        }
    }
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param deque Deque data structure to manage its every element.
/// @param manage Manage function pointer to manage deque's elements as an array using deque's size and generic arguments.
/// @param args Generic void pointer arguments to manage array of elements with, can be NULL.
static inline void map_deque(deque_s * deque, const manage_deque_fn manage, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(manage && "[ERROR] 'operate' parameter is NULL.");

    DEQUE_ASSERT(deque->max && "[ERROR] Deque's maximum size can't be zero.");
    DEQUE_ASSERT(deque->elements && "[ERROR] Deque's elements array can't be NULL.");
    DEQUE_ASSERT(deque->size <= deque->max && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < deque->max && "[ERROR] Deque's current index must be less than maximum size.");

    DEQUE_DATA_TYPE * elements_array = DEQUE_REALLOC(NULL, deque->size * sizeof(DEQUE_DATA_TYPE));
    DEQUE_ASSERT(elements_array && "[ERROR] Memory allocation failed.");

    const size_t right_size = (deque->current + deque->size) > deque->max ? deque->max - deque->current : deque->size;

    memcpy(elements_array, deque->elements + deque->current, right_size * sizeof(DEQUE_DATA_TYPE));
    memcpy(elements_array + right_size, deque->elements, (deque->size - right_size) * sizeof(DEQUE_DATA_TYPE));

    manage(elements_array, deque->size, args);

    memcpy(deque->elements, elements_array, deque->size * sizeof(DEQUE_DATA_TYPE));
    deque->current = 0;

    DEQUE_FREE(elements_array);
}

#elif DEQUE_MODE == INFINITE_REALLOC_DEQUE_MODE

#if !defined(IS_CAPACITY_DEQUE) && !defined(EXPAND_CAPACITY_DEQUE)

#ifndef REALLOC_DEQUE_CHUNK

#define REALLOC_DEQUE_CHUNK (1 << 5)

#elif REALLOC_DEQUE_CHUNK <= 0

#error 'REALLOC_DEQUE_CHUNK' cannot be less than or equal to 0

#endif

/// @brief Checks if stack's 'size' has reached capacity.
#define IS_CAPACITY_DEQUE(size) (!((size) % REALLOC_DEQUE_CHUNK))

/// @brief Calculates next stack's capacity based on 'size'.
#define EXPAND_CAPACITY_DEQUE(capacity) ((capacity) + REALLOC_DEQUE_CHUNK)

#elif !defined(IS_CAPACITY_DEQUE)

#error Stack capacity reached check is not defined.

#elif !defined(EXPAND_CAPACITY_DEQUE)

#error Stack capacity expanded size is not defined.

#endif

typedef struct deque {
    size_t current, size;
    DEQUE_DATA_TYPE * elements;
} deque_s;

/// @brief Creates an empty deque.
/// @return Empty deque.
static inline deque_s create_deque(void) {
    return (deque_s) { 0 };
}

/// @brief Destroys deque with all its elements using a destroy function pointer.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque needs to be created again after destroying it.
static inline void destroy_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    for (size_t i = 0; i < deque->size; ++i) {
        destroy(deque->elements + deque->current + i);
    }

    DEQUE_FREE(deque->elements);
    (*deque) = (deque_s) { 0 };
}

/// Clears deque with all its elements using a destroy function pointer to later use without creating a new deque.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque DOES NOT need to be created again after destroying it.
static inline void clear_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    for (size_t i = 0; i < deque->size; ++i) {
        destroy(deque->elements + deque->current + i);
    }

    DEQUE_FREE(deque->elements);
    (*deque) = (deque_s) { 0 };
}

/// @brief Copies the deque and all its elements into a new structure.
/// @param deque Deque structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in deque.
/// @return A copy of the specified 'deque' parameter.
static inline deque_s copy_deque(const deque_s deque, const copy_deque_fn copy) {
    DEQUE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    deque_s replika = { .current = 0, .elements = NULL, .size = 0, };

    size_t capacity = 0; // set capacity of replika to 0
    for (; replika.size < deque.size; ++replika.size) { // for each element expand replika and copy deque's elements to it
        if (capacity == replika.size) { // if replika's size reached capacity expand and save new capacity
            capacity = EXPAND_CAPACITY_DEQUE(deque.size); // expand and save capacity

            replika.elements = DEQUE_REALLOC(replika.elements, capacity * sizeof(DEQUE_DATA_TYPE)); // reallocate new memory
            DEQUE_ASSERT(replika.elements && "[ERROR] Memory allocation failed."); // check if memory was allocated
        }
        // copy element from deque's current index into replika's start
        replika.elements[replika.size] = copy(deque.elements[deque.current + replika.size]);
    }
    // set current to index where array with active elements will be in the center of the allocated chunk and move it there
    replika.current = (capacity >> 1) - (replika.size >> 1);
    memmove(replika.elements + replika.current, replika.elements, sizeof(DEQUE_DATA_TYPE) * replika.size);

    return replika;
}

/// Checks if deque is empty.
/// @param deque Deque structure to check.
/// @return true if deque is empty, false otherwise.
static inline bool is_empty_deque(const deque_s deque) {
    return deque.size == 0;
}

/// Checks if deque is full.
/// @param deque Deque structure to check.
/// @return true if deque is full, false otherwise.
static inline bool is_full_deque(const deque_s deque) {
    return !(~(deque.size));
}

/// @brief Enqueues specified element to deque's front.
/// @param deque Deque data structure to enqueue element infront.
/// @param element Element to enqueue infront.
static inline void enqueue_front(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");

    if ((IS_CAPACITY_DEQUE(deque->size))) {
        const size_t expanded_size = EXPAND_CAPACITY_DEQUE(deque->size);

        DEQUE_DATA_TYPE * elements_array = DEQUE_REALLOC(NULL, expanded_size * sizeof(DEQUE_DATA_TYPE));
        DEQUE_ASSERT(elements_array && "[ERROR] Memory allocation failed.");

        const size_t start_index = (expanded_size >> 1) - (deque->size >> 1);
        memcpy(elements_array + start_index, deque->elements + deque->current, sizeof(DEQUE_DATA_TYPE) * deque->size);

        deque->current = start_index ? start_index : start_index + 1;

        DEQUE_FREE(deque->elements);
        deque->elements = elements_array;
    } else if (!(deque->current)) {
        deque->current++;
        memmove(deque->elements + deque->current, deque->elements + deque->current - 1, sizeof(DEQUE_DATA_TYPE) * deque->size);
    }

    deque->current--;
    memcpy(deque->elements + deque->current, &element, sizeof(DEQUE_DATA_TYPE));
    deque->size++;
}

/// @brief Enqueues specified element to deque's back.
/// @param deque Deque data structure to enqueue element to back.
/// @param element lement to enqueue to back.
static inline void enqueue_back(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");

    if ((IS_CAPACITY_DEQUE(deque->size))) {
        const size_t expanded_size = EXPAND_CAPACITY_DEQUE(deque->size);

        DEQUE_DATA_TYPE * elements_array = DEQUE_REALLOC(NULL, expanded_size * sizeof(DEQUE_DATA_TYPE));
        DEQUE_ASSERT(elements_array && "[ERROR] Memory allocation failed.");

        const size_t center_start = (expanded_size >> 1) - (deque->size >> 1);
        //const size_t start_index = center_start ? center_start - 1 : center_start;
        memcpy(elements_array + center_start, deque->elements + deque->current, sizeof(DEQUE_DATA_TYPE) * deque->size);

        deque->current = center_start;

        DEQUE_FREE(deque->elements);
        deque->elements = elements_array;
    } else if ((IS_CAPACITY_DEQUE(deque->current + deque->size))) {
        deque->current--;
        memmove(deque->elements + deque->current, deque->elements + deque->current + 1, sizeof(DEQUE_DATA_TYPE) * deque->size);
    }

    memcpy(deque->elements + (deque->current + deque->size), &element, sizeof(DEQUE_DATA_TYPE));
    deque->size++;
}

/// @brief Peeks element at front of deque.
/// @param deque Deque data structure to peek from front.
/// @return Peeked element at front of deque.
static inline DEQUE_DATA_TYPE peek_front(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Can't peek empty deque.");

    return deque.elements[deque.current];
}

/// @brief Peeks element at back of deque.
/// @param deque Deque data structure to peek from back.
/// @return Peeked element at back of deque.
static inline DEQUE_DATA_TYPE peek_back(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Can't peek empty deque.");

    return deque.elements[deque.current + deque.size - 1];
}

/// Dequeues element at front of deque.
/// @param deque Deque data structure to dequeue from front.
/// @return Dequeued element at front of deque.
static inline DEQUE_DATA_TYPE dequeue_front(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Can't dequeue empty deque.");

    DEQUE_DATA_TYPE removed = deque->elements[deque->current++];
    deque->size--;

    if (deque->size && IS_CAPACITY_DEQUE(deque->size)) {
        DEQUE_DATA_TYPE * elements_array = DEQUE_REALLOC(NULL, deque->size * sizeof(DEQUE_DATA_TYPE));
        DEQUE_ASSERT((!deque->size || elements_array) && "[ERROR] Memory allocation failed.");

        memcpy(elements_array, deque->elements + deque->current, deque->size * sizeof(DEQUE_DATA_TYPE));
        deque->current = 0;

        DEQUE_FREE(deque->elements);
        deque->elements = elements_array;
    } else if (!(deque->size)) {
        DEQUE_FREE(deque->elements);
        deque->elements = NULL;
    }

    return removed;
}

/// Dequeues element at back of deque.
/// @param deque Deque data structure to dequeue from back.
/// @return Dequeued element at back of deque.
static inline DEQUE_DATA_TYPE dequeue_back(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Can't dequeue empty deque.");

    DEQUE_DATA_TYPE removed = deque->elements[deque->current + (--deque->size)];

    if (deque->size && IS_CAPACITY_DEQUE(deque->size)) {
        DEQUE_DATA_TYPE * elements_array = DEQUE_REALLOC(NULL, deque->size * sizeof(DEQUE_DATA_TYPE));
        DEQUE_ASSERT((!deque->size || elements_array) && "[ERROR] Memory allocation failed.");

        memcpy(elements_array, deque->elements + deque->current, deque->size * sizeof(DEQUE_DATA_TYPE));
        deque->current = 0;

        DEQUE_FREE(deque->elements);
        deque->elements = elements_array;
    } else if (!(deque->size)) {
        DEQUE_FREE(deque->elements);
        deque->elements = NULL;
    }

    return removed;
}

/// Iterates over each element in deque from front to back and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_deque(deque_s const * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    for (size_t i = 0; i < deque->size && operate(deque->elements + i + deque->current, args); ++i) {}
}

/// Iterates over each element in deque from back to front and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_reverse_deque(deque_s const * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    for (size_t i = 0; i < deque->size && operate(deque->elements + (deque->size - 1 - i) + deque->current, args); ++i) {}
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param deque Deque data structure to manage its every element.
/// @param manage Manage function pointer to manage deque's elements as an array using deque's size and generic arguments.
/// @param args Generic void pointer arguments to manage array of elements with, can be NULL.
static inline void map_deque(deque_s const * deque, const manage_deque_fn manage, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(manage && "[ERROR] 'operate' parameter is NULL.");

    manage(deque->elements + deque->current, deque->size, args);
}

#elif DEQUE_MODE == FINITE_PREPROCESSOR_DEQUE_MODE

#ifndef PREPROCESSOR_DEQUE_SIZE

#define PREPROCESSOR_DEQUE_SIZE (1 << 5)

#elif PREPROCESSOR_DEQUE_SIZE <= 0

#error 'PREPROCESSOR_DEQUE_SIZE' cannot be less than or equal to zero

#endif

typedef struct deque {
    size_t current, size;
    DEQUE_DATA_TYPE elements[PREPROCESSOR_DEQUE_SIZE];
} deque_s;

/// @brief Creates an empty deque.
/// @return Empty deque.
static inline deque_s create_deque(void) {
    return (deque_s) { .current = PREPROCESSOR_DEQUE_SIZE >> 1, .size = 0, }; // return empty deque with current set to middle
}

/// @brief Destroys deque with all its elements using a destroy function pointer.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque needs to be created again after destroying it.
static inline void destroy_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    // calculate size of elements to the right of current index
    const size_t right_size = (deque->current + deque->size) > PREPROCESSOR_DEQUE_SIZE ? PREPROCESSOR_DEQUE_SIZE - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size; ++i) { // for each element from current to right size destroy it
        destroy(deque->elements + i);
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) { // for each element from 0 to left size destroy it
        destroy(deque->elements + i);
    }

    deque->size = 0;
}

/// Clears deque with all its elements using a destroy function pointer to later use without creating a new deque.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque DOES NOT need to be created again after destroying it.
static inline void clear_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    // calculate size of elements to the right of current index
    const size_t right_size = (deque->current + deque->size) > PREPROCESSOR_DEQUE_SIZE ? PREPROCESSOR_DEQUE_SIZE - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size; ++i) { // for each element from current to right size destroy it
        destroy(deque->elements + i);
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) { // for each element from 0 to left size destroy it
        destroy(deque->elements + i);
    }

    deque->current = PREPROCESSOR_DEQUE_SIZE >> 1; // set current index to middle of preprocessor size size
    deque->size = 0; // set current index and
}

/// @brief Copies the deque and all its elements into a new structure.
/// @param deque Deque structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in deque.
/// @return A copy of the specified 'deque' parameter.
static inline deque_s copy_deque(const deque_s deque, const copy_deque_fn copy) {
    DEQUE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    DEQUE_ASSERT(deque.size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    deque_s replika = { .current = deque.current, .size = deque.size, };

    const size_t right_size = (deque.current + deque.size) > PREPROCESSOR_DEQUE_SIZE ? PREPROCESSOR_DEQUE_SIZE - deque.current : deque.size;
    for (size_t i = deque.current; i < right_size + deque.current; ++i) { // for each element from current to right size destroy it
        replika.elements[i] = copy(deque.elements[i]);
    }
    for (size_t i = 0; i < deque.size - right_size; ++i) { // for each element from 0 to left size destroy it
        replika.elements[i] = copy(deque.elements[i]);
    }

    return replika;
}

/// Checks if deque is empty.
/// @param deque Deque structure to check.
/// @return true if deque is empty, false otherwise.
static inline bool is_empty_deque(const deque_s deque) {
    DEQUE_ASSERT(deque.size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    return deque.size == 0;
}

/// Checks if deque is full.
/// @param deque Deque structure to check.
/// @return true if deque is full, false otherwise.
static inline bool is_full_deque(const deque_s deque) {
    DEQUE_ASSERT(deque.size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    return (deque.size == PREPROCESSOR_DEQUE_SIZE);
}

/// @brief Enqueues specified element to deque's front.
/// @param deque Deque data structure to enqueue element infront.
/// @param element Element to enqueue infront.
static inline void enqueue_front(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque is full.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    // if current underflows then circle it to max
    if (!(deque->current)) {
        deque->current = PREPROCESSOR_DEQUE_SIZE;
    }
    deque->current--;
    deque->size++;
    memcpy(deque->elements + deque->current, &element, sizeof(DEQUE_DATA_TYPE));
}

/// @brief Enqueues specified element to deque's back.
/// @param deque Deque data structure to enqueue element to back.
/// @param element lement to enqueue to back.
static inline void enqueue_back(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque is full.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t next_index = (deque->current + deque->size) % PREPROCESSOR_DEQUE_SIZE;
    deque->size++;
    memcpy(deque->elements + next_index, &element, sizeof(DEQUE_DATA_TYPE));
}

/// @brief Peeks element at front of deque.
/// @param deque Deque data structure to peek from front.
/// @return Peeked element at front of deque.
static inline DEQUE_DATA_TYPE peek_front(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque.size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    return deque.elements[deque.current];
}

/// @brief Peeks element at back of deque.
/// @param deque Deque data structure to peek from back.
/// @return Peeked element at back of deque.
static inline DEQUE_DATA_TYPE peek_back(const deque_s deque) {
    DEQUE_ASSERT(deque.size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque.size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque.current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t current_index = (deque.current + deque.size - 1) % PREPROCESSOR_DEQUE_SIZE;
    return deque.elements[current_index];
}

/// Dequeues element at front of deque.
/// @param deque Deque data structure to dequeue from front.
/// @return Dequeued element at front of deque.
static inline DEQUE_DATA_TYPE dequeue_front(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    DEQUE_DATA_TYPE removed = deque->elements[deque->current++];
    deque->size--;

    if (deque->current == PREPROCESSOR_DEQUE_SIZE) {
        deque->current = 0;
    }

    return removed;
}

/// Dequeues element at back of deque.
/// @param deque Deque data structure to dequeue from back.
/// @return Dequeued element at back of deque.
static inline DEQUE_DATA_TYPE dequeue_back(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t current_index = (deque->current + deque->size - 1) % PREPROCESSOR_DEQUE_SIZE;
    DEQUE_DATA_TYPE removed = deque->elements[current_index];
    deque->size--;

    return removed;
}

/// Iterates over each element in deque from front to back and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_deque(deque_s * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (deque->current + deque->size) > PREPROCESSOR_DEQUE_SIZE ? PREPROCESSOR_DEQUE_SIZE - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size + deque->current; ++i) {
        if (!operate(deque->elements + i, args)) {
            return;
        }
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) {
        if (!operate(deque->elements + i, args)) {
            return;
        }
    }
}

/// Iterates over each element in deque from back to front and calls operate on it using generic arguments until
/// all elements are reached or operate function returns false.
/// @param deque Deque data structure to operate on each of its elements.
/// @param operate Operate function pointer to operate on each of deque's elements until it returns false or each
/// element was operated on.
/// @param args Generic void pointer arguments for operate funtion pointer, can be NULL.
static inline void foreach_reverse_deque(deque_s * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (deque->current + deque->size) > PREPROCESSOR_DEQUE_SIZE ? PREPROCESSOR_DEQUE_SIZE - deque->current : deque->size;
    const size_t left_size = deque->size - right_size;
    for (size_t i = 0; i < left_size; ++i) {
        if (!operate(deque->elements + (left_size - i - 1), args)) {
            return;
        }
    }
    for (size_t i = 0; i < right_size; ++i) {
        if (!operate(deque->elements + (right_size - i - 1) + deque->current, args)) {
            return;
        }
    }
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param deque Deque data structure to manage its every element.
/// @param manage Manage function pointer to manage deque's elements as an array using deque's size and generic arguments.
/// @param args Generic void pointer arguments to manage array of elements with, can be NULL.
static inline void map_deque(deque_s * deque, const manage_deque_fn manage, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < PREPROCESSOR_DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    DEQUE_DATA_TYPE elements_array[PREPROCESSOR_DEQUE_SIZE];

    const size_t right_size = (deque->current + deque->size) > PREPROCESSOR_DEQUE_SIZE ? PREPROCESSOR_DEQUE_SIZE - deque->current : deque->size;

    memcpy(elements_array, deque->elements + deque->current, right_size * sizeof(DEQUE_DATA_TYPE));
    memcpy(elements_array + right_size, deque->elements, (deque->size - right_size) * sizeof(DEQUE_DATA_TYPE));

    manage(elements_array, deque->size, args);

    memcpy(deque->elements, elements_array, deque->size * sizeof(DEQUE_DATA_TYPE));
    deque->current = 0;
}

#endif

#else

#error Cannot include multiple headers in same unit.

#endif //DEQUE_H
