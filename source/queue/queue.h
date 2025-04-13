#ifndef QUEUE_H
#define QUEUE_H

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

#define INFINITE_LIST_QUEUE       101
#define FINITE_ALLOCATED_QUEUE    102
#define INFINITE_REALLOC_QUEUE    103
#define FINITE_PREPROCESSOR_QUEUE 104

//#define QUEUE_MODE INFINITE_LIST_QUEUE
//#define QUEUE_MODE FINITE_ALLOCATED_QUEUE
//#define QUEUE_MODE INFINITE_REALLOC_QUEUE
//#define QUEUE_MODE FINITE_PREPROCESSOR_QUEUE
// Queue mode that can be set to INFINITE_LIST_QUEUE, FINITE_ALLOCATED_QUEUE, INFINITE_REALLOC_QUEUE or
// FINITE_PRERPOCESSOR_QUEUE.
// Default: INFINITE_LIST_QUEUE
#ifndef QUEUE_MODE

#define QUEUE_MODE INFINITE_LIST_QUEUE

#endif

// Check to make sure a valid queue mode is selected.
#if (QUEUE_MODE != INFINITE_LIST_QUEUE)    && (QUEUE_MODE != FINITE_ALLOCATED_QUEUE) && \
    (QUEUE_MODE != INFINITE_REALLOC_QUEUE) && (QUEUE_MODE != FINITE_PREPROCESSOR_QUEUE)

#error Invalid type of queue mode.

#endif

// Queue data type to specify what datatype to queue.
// DEFAULT: void *
#ifndef QUEUE_DATA_TYPE

#define QUEUE_DATA_TYPE void*

#endif

#ifndef QUEUE_ASSERT

#include <assert.h>  // imports assert for debugging
#define QUEUE_ASSERT assert

#endif

#if !defined(QUEUE_REALLOC) && !defined(QUEUE_FREE)

#include <stdlib.h>

#ifndef QUEUE_REALLOC

#define QUEUE_REALLOC realloc

#endif

#ifndef QUEUE_FREE

#define QUEUE_FREE free

#endif

#elif !defined(QUEUE_REALLOC)

#error Queue reallocator macro is not defined!

#elif !defined(QUEUE_FREE)

#error Queue free macro is not defined!

#endif

/// Function pointer that creates a deep element copy.
typedef QUEUE_DATA_TYPE (*copy_queue_fn)    (const QUEUE_DATA_TYPE);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_queue_fn) (QUEUE_DATA_TYPE *);
/// Function pointer that changes an element pointer using void pointer arguments if needed.
typedef bool            (*operate_queue_fn) (QUEUE_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void            (*manage_queue_fn)  (QUEUE_DATA_TYPE *, const size_t, void *);

#if   QUEUE_MODE == INFINITE_LIST_QUEUE

// Queue list array size.
// DEFAULT: (1 << 10) or 1024
#ifndef LIST_ARRAY_QUEUE_CHUNK

#define LIST_ARRAY_QUEUE_CHUNK (1 << 10)

#elif LIST_ARRAY_QUEUE_CHUNK <= 0

#error 'LIST_ARRAY_QUEUE_CHUNK' cannot be less than or equal to 0.

#endif

/// @brief Linked list of arrays that appends new list element at the end after array is full.
struct queue_list_array {
    QUEUE_DATA_TYPE elements[LIST_ARRAY_QUEUE_CHUNK]; // array to store elements
    struct queue_list_array * next; // next linked list array
};

/// @brief Queue implementation that uses circled appended lists of arrays and pushes elements based on the size.
typedef struct queue {
    //struct queue_list_array * head; // head list element with the top of the queue
    struct queue_list_array * tail; // tail list element with the bottom of the queue
    size_t size, current; // size of queue and current index
} queue_s;

/// @brief Creates empty queue.
/// @return Created queue structure.
static inline queue_s create_queue(void) {
    return (queue_s) { 0 }; // queue.size and queue.current is 0 and tail pointer must be NULL
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer to destroy.
/// @param destroy Function pointer to destroy (or free) elements in queue.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL.");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer is NULL.");

    struct queue_list_array * previous = queue->tail;
    for (size_t start = queue->current; queue->size; start = 0) {
        size_t i = start;
        for (; i < queue->size && i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
            destroy(previous->next->elements + i);
        }
        queue->size -= (i - start);

        struct queue_list_array * temp = previous->next;
        previous->next = previous->next->next;
        QUEUE_FREE(temp);
    }

    queue->current = 0;
    queue->tail = NULL;
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure to check.
/// @return true if queue is full, false otherwise.
static inline bool is_full_queue(const queue_s queue) {
    return !(~queue.size); // checks if '.size' of type size_t won't overflown after pushing another element
}

/// @brief Gets element at the top of the queue without decrementing size (peek the first of the queue).
/// @param queue Queue structure to peek.
/// @return The first element of the queue.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");
    QUEUE_ASSERT(queue.tail && "[ERROR] Queue tail is NULL");
    QUEUE_ASSERT(queue.tail->next && "[ERROR] Queue tail's next node is NULL");

    return queue.tail->next->elements[queue.current]; // tail's next node is queue's head
}

/// @brief Sets the next end element in queue array to 'element' parameter (enqueues element).
/// @param queue Queue structure pointer to enqueue into.
/// @param element Element to push to end of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(~(queue->size) && "[ERROR] Queue's '.size' will overflow");

    // index where the next element will be enqueued
    const size_t next_index = (queue->current + queue->size) % LIST_ARRAY_QUEUE_CHUNK;
    if (!next_index) { // if head list array is full (is divisible) adds new list element to head
        struct queue_list_array * temp = QUEUE_REALLOC(NULL, sizeof(struct queue_list_array));
        QUEUE_ASSERT(temp && "[ERROR] Memory allocation failed");

        if (queue->tail == NULL) {
            temp->next = temp; // create initial circle
        } else {
            temp->next = queue->tail->next; // make temp's next node head node
            queue->tail->next = temp; // make previous tail's next node point to temp
        }
        queue->tail = temp;
    }

    memcpy(queue->tail->elements + next_index, &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets and removes the start element in queue (dequeues start element).
/// @param queue Queue structure pointer to dequeue from.
/// @return The start element of the queue.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't dequeue empty queue");
    QUEUE_ASSERT(queue->tail && "[ERROR] Queue tail is NULL");
    QUEUE_ASSERT(queue->tail->next && "[ERROR] Queue tail's next node is NULL");

    QUEUE_DATA_TYPE element = queue->tail->next->elements[queue->current]; // extract element at head's current index
    queue->size--; // decrement queue size
    queue->current = (queue->current + 1) % LIST_ARRAY_QUEUE_CHUNK; // set current to next index in node array

    if (!queue->size) { // if queue is empty after extracting element thne free memory and reset everything to zero
        QUEUE_FREE(queue->tail); // free empty tail/head node
        queue->tail = NULL; // set tail to NULL
    } else if (queue->current == 0) { // else if current index circles back, free start list element and shift to next
        struct queue_list_array * temp = queue->tail->next; // get empty head node
        queue->tail->next = queue->tail->next->next; // set new head node to its next node
        QUEUE_FREE(temp); // free previous head node
    }

    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure.
/// @param queue Queue structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in queue.
/// @return A 'copy' of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    QUEUE_ASSERT(copy && "[ERROR] 'copy' function pointer is NULL.");

    queue_s queue_copy = { .size = queue.size, .tail = NULL, .current = queue.current };

    struct queue_list_array const * current_queue = queue.tail;
    struct queue_list_array ** current_copy = &(queue_copy.tail); // two pointer list to remove special .head case

    size_t remaining_size = queue.size;
    size_t start_index = queue.current;
    struct queue_list_array * last_added = NULL;
    while (remaining_size) {
        last_added = (*current_copy) = QUEUE_REALLOC(NULL, sizeof(struct queue_list_array));
        QUEUE_ASSERT((*current_copy) && "[ERROR] Memory allocation failed");

        (*current_copy)->next = queue_copy.tail; // make current/last node's next pointer point to tail
        current_queue = current_queue->next;

        // outside for loop to get copied chunk size, since it can either be 'remaining_size' or 'LIST_ARRAY_QUEUE_CHUNK'
        size_t i = start_index;
        for (; i < remaining_size && i < LIST_ARRAY_QUEUE_CHUNK; ++i) { // while i is less than both 'remaining_size' and 'LIST_ARRAY_QUEUE_CHUNK'
            (*current_copy)->elements[i] = copy(current_queue->elements[i]);
        }
        remaining_size -= i; // subtract copied size from remaining size using i
        start_index = 0; // set start index to zero since we only need start index startinf from queue's currrent in tail node

        current_copy = &((*current_copy)->next);
    }
    queue_copy.tail = last_added;

    return queue_copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure to check.
/// @return true if queue size is zero, false otherwise.
static inline bool is_empty_queue(const queue_s queue) {
    return (queue.size == 0);
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer to clear.
/// @param destroy Function pointer to destroy an element in queue.
/// @note This function in this mode is just a copy of the 'destroy_queue' function.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer is NULL.");

    struct queue_list_array * previous = queue->tail; // save previous node, relative to head, as tail
    // create start index and while queue size isn't zero destroy elements from start, set start to 0 after special case first iteration
    for (size_t start = queue->current; queue->size; start = 0) {
        struct queue_list_array * current = previous->next; // save previous' next node as current (to iterate from head instead of tail)
        size_t i = start; // set i index before for loop to save its value for subtraction later
        // while i is less than either queue size or list array chunk destroy each element
        for (; i < queue->size && i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
            destroy(current->elements + i); // destroy each element in current node
        }
        queue->size -= (i - start); // subtract absolute value of i and start from queue size, i.e. the actual destroyed element count

        previous->next = current->next; // set previous' next node to current's next
        QUEUE_FREE(current);
    }

    queue->current = 0;
    queue->tail = NULL;
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as a parameter.
/// @param queue Queue structure pointer to operate on.
/// @param operate Function pointer taht operates on single element pointer using 'args' as generic argument.
/// @param args Generic void pointer argument for 'operates' funtion pointer.
static inline void foreach_queue(queue_s const * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL");

    size_t remaining_size = queue->size; // save queue size as remaining size for iteration
    struct queue_list_array const * previous = queue->tail;
    for (size_t start = queue->current; remaining_size; start = 0, previous = previous->next) { // while remaining size wasn't decremented to zero
        struct queue_list_array * current = previous->next;

        size_t i = start; // save i outside loop to later use it in subtraction
        for (;i < remaining_size && i < LIST_ARRAY_QUEUE_CHUNK; ++i) { // while i is less than either remaining size or node's array size
            if (!operate(current->elements + i, args)) { // operate on element and if zero is returned then end main function
                return;
            }
        }
        remaining_size -= (i - start); // subtract absolute value of i and start from remaining size
    }
}

/// @brief Forevery function that manages every element as an array with 'manage' function using queue's size and 'args'
/// as parameters.
/// @param queue Queue structure pointer to manage.
/// @param manage Function pointer that takes an array of queue elements, the number of elements and other arguments
/// in the form of a 'args'.
/// @param args Generic void pointer arguments for manage function pointer.
static inline void forevery_queue(queue_s const * queue, const manage_queue_fn manage, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL");
    // create elements array to temporary save element from circular linked list nodes
    QUEUE_DATA_TYPE * elements_array = QUEUE_REALLOC(NULL, queue->size * sizeof(QUEUE_DATA_TYPE));
    QUEUE_ASSERT(elements_array && "[ERROR] Memory allocation failed.");

    size_t remaining_size = queue->size; // temporary variable to save queue's size
    size_t index = 0; // start index for 'elements_array'
    struct queue_list_array const * previous = queue->tail; // create node pointer to save previous nodes into
    for (size_t start = queue->current; remaining_size; start = 0, previous = previous->next) {
        size_t i = start; // extract i from for loop to later subtract it from remaining size
        for (;i < remaining_size && i < LIST_ARRAY_QUEUE_CHUNK; ++i) { // while i is less than remaining size and node array size
            // save previous' next elements (so current) to elements array at index, and increment index
            elements_array[index++] = previous->next->elements[i];
        }
        remaining_size -= (i - start); // subtract absolute value of i and start from remaining size
    }

    manage(elements_array, queue->size, args); // manage initialized elements array

    remaining_size = queue->size;
    previous = queue->tail;
    index = 0;
    for (size_t start = queue->current; remaining_size; start = 0, previous = previous->next) { // save elements array back into queue
        size_t i = start; // extract i from for loop to later subtract it from remaining size
        for (;i < remaining_size && i < LIST_ARRAY_QUEUE_CHUNK; ++i) { // while i is less than remaining size and node array size
            previous->next->elements[i] = elements_array[index++];
        }
        remaining_size -= (i - start); // subtract absolute value of i and start from remaining size
    }

    QUEUE_FREE(elements_array);
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Queue implementation that uses allocated memory array and pushes elements based on the current
/// and maximum size.
typedef struct queue {
    QUEUE_DATA_TYPE * elements; // pointer to allocated memory
    size_t max, size, current;  // maximum queue size, actual size and current index
} queue_s;

/// @brief Creates empty queue.
/// @return Created queue structure.
/// @param max Specifies maximum allocated size of queue structure.
static inline queue_s create_queue(const size_t max) {
    QUEUE_ASSERT(max && "[ERROR] Maximum size can't be zero");

    const queue_s create = {
        .max = max, .elements = QUEUE_REALLOC(NULL, max * sizeof(QUEUE_DATA_TYPE)), .size = 0,
    };
    QUEUE_ASSERT(create.elements && "[ERROR] Memory allocation failed");

    return create;
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer to destroy.
/// @param destroy Function pointer to destroy (or free) elements in queue.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL.");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer parameter is NULL.");

    QUEUE_ASSERT(queue->max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue->elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue->size <= queue->max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue->current < queue->max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (queue->current + queue->size) > queue->max ? queue->max - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        destroy(queue->elements + queue->current + i);
    }
    for (size_t i = 0; i < queue->size - right_size; ++i) {
        destroy(queue->elements + i);
    }

    QUEUE_FREE(queue->elements);
    *queue = (queue_s) { 0 };
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure to check.
/// @return true if queue is full, false otherwise.
/// @note This function also returns true if maximum size is reached.
static inline bool is_full_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue.elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue.size <= queue.max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue.current < queue.max && "[ERROR] Deque's current index must be less than maximum size.");

    return queue.size == queue.max;
}

/// @brief Gets element at the top of the queue without decrementing size (peek the first of the queue).
/// @param queue Queue structure to peek.
/// @return The first element of the queue.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");

    QUEUE_ASSERT(queue.max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue.elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue.size <= queue.max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue.current < queue.max && "[ERROR] Deque's current index must be less than maximum size.");

    return queue.elements[queue.current];
}

/// @brief Sets the next end element in queue array to 'element' parameter (enqueues element).
/// @param queue Queue structure pointer to enqueue into.
/// @param element Element to push to end of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(queue->size < queue->max && "[ERROR] Queue reached maximum size");

    QUEUE_ASSERT(queue->max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue->elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue->size <= queue->max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue->current < queue->max && "[ERROR] Deque's current index must be less than maximum size.");

    memcpy(queue->elements + ((queue->current + queue->size) % queue->max), &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets and removes the start element in queue (dequeues start element).
/// @param queue Queue structure pointer to dequeue from.
/// @return The start element of the queue.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't pop empty queue");

    QUEUE_ASSERT(queue->max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue->elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue->size <= queue->max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue->current < queue->max && "[ERROR] Deque's current index must be less than maximum size.");

    QUEUE_DATA_TYPE element = queue->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % queue->max;
    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure.
/// @param queue Queue structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in queue.
/// @return A 'copy' of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    QUEUE_ASSERT(copy && "[ERROR] 'copy' function pointer parameter is NULL.");

    QUEUE_ASSERT(queue.max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue.elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue.size <= queue.max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue.current < queue.max && "[ERROR] Deque's current index must be less than maximum size.");

    const queue_s queue_copy = {
        .size = queue.size, .current = queue.current, .max = queue.max,
        .elements = QUEUE_REALLOC(NULL, queue.max * sizeof(QUEUE_DATA_TYPE)),
    };
    QUEUE_ASSERT(queue_copy.elements && "[ERROR] Memory allocation failed");

    const size_t right_size = (queue.current + queue.size) > queue.max ? queue.max - queue.current : queue.size;
    for (size_t i = 0; i < right_size; ++i) {
        queue_copy.elements[i + queue.current] = copy(queue.elements[i + queue.current]);
    }
    for (size_t i = 0; i < queue.size - right_size; ++i) {
        queue_copy.elements[i] = copy(queue.elements[i]);
    }

    return queue_copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure to check.
/// @return true if queue size is zero, false otherwise.
static inline bool is_empty_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue.elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue.size <= queue.max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue.current < queue.max && "[ERROR] Deque's current index must be less than maximum size.");

    return queue.size == 0;
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer to clear.
/// @param destroy Function pointer to destroy an element in queue.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL.");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer parameter is NULL.");

    QUEUE_ASSERT(queue->max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue->elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue->size <= queue->max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue->current < queue->max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (queue->current + queue->size) > queue->max ? queue->max - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        destroy(queue->elements + queue->current + i);
    }
    for (size_t i = 0; i < queue->size - right_size; ++i) {
        destroy(queue->elements + i);
    }

    queue->size = 0;
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as a parameter.
/// @param queue Queue structure pointer to operate on.
/// @param operate Function pointer taht operates on single element pointer using 'args' as generic argument.
/// @param args Generic void pointer argument for 'operates' funtion pointer.
static inline void foreach_queue(queue_s const * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    QUEUE_ASSERT(queue->max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue->elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue->size <= queue->max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue->current < queue->max && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (queue->current + queue->size) > queue->max ? queue->max - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        if (!operate(queue->elements + queue->current + i, args)) {
            return;
        }
    }
    for (size_t i = 0; i < queue->size - right_size; ++i) {
        if (!operate(queue->elements + i, args)) {
            return;
        }
    }
}

/// @brief Forevery function that manages every element as an array with 'manage' function using queue's size and 'args'
/// as parameters.
/// @param queue Queue structure pointer to manage.
/// @param manage Function pointer that takes an array of queue elements, the number of elements and other arguments
/// in the form of a 'args'.
/// @param args Generic void pointer arguments for manage function pointer.
static inline void forevery_queue(queue_s * queue, const manage_queue_fn manage, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    QUEUE_ASSERT(queue->max && "[ERROR] Deque's maximum size can't be zero.");
    QUEUE_ASSERT(queue->elements && "[ERROR] Deque's elements array can't be NULL.");
    QUEUE_ASSERT(queue->size <= queue->max && "[ERROR] Deque's size can't exceed its maximum size.");
    QUEUE_ASSERT(queue->current < queue->max && "[ERROR] Deque's current index must be less than maximum size.");

    QUEUE_DATA_TYPE * elements_array = QUEUE_REALLOC(NULL, queue->size * sizeof(QUEUE_DATA_TYPE)); // allocate memory for temporary elements in queue
    QUEUE_ASSERT(elements_array && "[ERROR] Memory allocation failed."); // check if allocation failed

    // calculate right size of elements from current index to copy right and left elements into temporary array
    const size_t right_size = (queue->current + queue->size) > queue->max ? queue->max - queue->current : queue->size;

    memcpy(elements_array, queue->elements + queue->current, right_size * sizeof(QUEUE_DATA_TYPE));
    memcpy(elements_array + right_size, queue->elements, (queue->size - right_size) * sizeof(QUEUE_DATA_TYPE));

    manage(elements_array, queue->size, args); // manage elements in array

    memcpy(queue->elements, elements_array, queue->size * sizeof(QUEUE_DATA_TYPE)); // recopy elements back to queue's array but from queue's start
    queue->current = 0; // reset current index to 0

    QUEUE_FREE(elements_array); // free allocated memory
}

#elif QUEUE_MODE == INFINITE_REALLOC_QUEUE

#if !defined(IS_REALLOC_CAPACITY_QUEUE) && !defined(EXPAND_REALLOC_CAPACITY_QUEUE)

#ifndef REALLOC_QUEUE_CHUNK

#define REALLOC_QUEUE_CHUNK (1 << 5)

#elif REALLOC_QUEUE_CHUNK <= 0

#error 'REALLOC_QUEUE_CHUNK' cannot be less than or equal to 0

#endif

/// @brief Checks if stack's 'size' has reached capacity.
#define IS_REALLOC_CAPACITY_QUEUE(size) (!(size % REALLOC_QUEUE_CHUNK))

/// @brief Calculates next stack's capacity based on 'size'.
#define EXPAND_REALLOC_CAPACITY_QUEUE(capacity) (capacity + REALLOC_QUEUE_CHUNK)

#elif !defined(IS_REALLOC_CAPACITY_QUEUE)

#error Stack capacity reached check is not defined.

#elif !defined(EXPAND_REALLOC_CAPACITY_QUEUE)

#error Stack capacity expanded size is not defined.

#endif

typedef struct queue {
    size_t size, current;
    QUEUE_DATA_TYPE * elements;
} queue_s;

/// @brief Creates empty queue.
/// @return Created queue structure.
static inline queue_s create_queue(void) {
    return (queue_s) { 0 };
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer to destroy.
/// @param destroy Function pointer to destroy (or free) elements in queue.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer is NULL.");

    for(size_t s = 0; s < queue->size; s++) {
        destroy(&(queue->elements[s + queue->current]));
    }

    QUEUE_FREE(queue->elements);

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure to check.
/// @return true if queue is full, false otherwise.
static inline bool is_full_queue(const queue_s queue) {
    return !(~queue.size);
}

/// @brief Gets element at the top of the queue without decrementing size (peek the first of the queue).
/// @param queue Queue structure to peek.
/// @return The first element of the queue.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");
    QUEUE_ASSERT(queue.elements && "[ERROR] Queue's '.elements' is NULL");

    return queue.elements[queue.current];
}

/// @brief Sets the next end element in queue array to 'element' parameter (enqueues element).
/// @param queue Queue structure pointer to enqueue into.
/// @param element Element to push to end of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(~(queue->size) && "[ERROR] Queue's '.size' will overflow");

    // first expand memory if necessary and then add element
    const size_t actual_size = queue->current + queue->size;
    if (IS_REALLOC_CAPACITY_QUEUE(actual_size)) {
        queue->elements = QUEUE_REALLOC(queue->elements, (EXPAND_REALLOC_CAPACITY_QUEUE(actual_size)) * sizeof(QUEUE_DATA_TYPE));
        QUEUE_ASSERT(queue->elements && "[ERROR] Memory allocation failed");
    }
    memcpy(queue->elements + actual_size, &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets and removes the start element in queue (dequeues start element).
/// @param queue Queue structure pointer to dequeue from.
/// @return The start element of the queue.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't dequeue empty queue");
    QUEUE_ASSERT(queue->elements && "[ERROR] Can't dequeue NULL elements");

    // first remove element and then shrink memory if necessary
    QUEUE_DATA_TYPE element = queue->elements[queue->current++];
    queue->size--;
    if (IS_REALLOC_CAPACITY_QUEUE(queue->size)) {
        QUEUE_DATA_TYPE * temp = queue->size ? QUEUE_REALLOC(NULL, queue->size * sizeof(QUEUE_DATA_TYPE)) : NULL;
        QUEUE_ASSERT((!queue->size || temp) && "[ERROR] Memory allocation failed."); // fails if allocation returns NULL on non-zero chunk size

        memcpy(temp, queue->elements + queue->current, queue->size * sizeof(QUEUE_DATA_TYPE));
        QUEUE_FREE(queue->elements);
        queue->elements = temp;
        queue->current = 0;
    }

    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure.
/// @param queue Queue structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in queue.
/// @return A 'copy' of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    QUEUE_ASSERT(copy && "[ERROR] 'copy' function pointer parameter is NULL");

    queue_s replica = { .current = 0, .elements = NULL, .size = 0 };
    for (; replica.size < queue.size; ++(replica.size)) {
        if (IS_REALLOC_CAPACITY_QUEUE(replica.size)) {
            replica.elements = QUEUE_REALLOC(replica.elements, (EXPAND_REALLOC_CAPACITY_QUEUE(replica.size)) * sizeof(QUEUE_DATA_TYPE));
            QUEUE_ASSERT(replica.elements && "[ERROR] Memory allocation failed");
        }
        replica.elements[replica.size] = copy(queue.elements[replica.size + queue.current]);
    }

    return replica;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure to check.
/// @return true if queue size is zero, false otherwise.
static inline bool is_empty_queue(const queue_s queue) {
    return queue.size == 0;
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer to clear.
/// @param destroy Function pointer to destroy an element in queue.
/// @note This function in this mode is just a copy of the 'destroy_queue' function.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL.");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer parameter is NULL.");

    for (size_t i = 0; i < queue->size; ++i) {
        destroy(queue->elements + i + queue->current);
    }

    QUEUE_FREE(queue->elements);

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as a parameter.
/// @param queue Queue structure pointer to operate on.
/// @param operate Function pointer taht operates on single element pointer using 'args' as generic argument.
/// @param args Generic void pointer argument for 'operates' funtion pointer.
static inline void foreach_queue(queue_s const * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    for (size_t i = queue->current; i < queue->current + queue->size; ++i) {
        if (!operate(queue->elements + i, args)) return;
    }
}

/// @brief Forevery function that manages every element as an array with 'manage' function using queue's size and 'args'
/// as parameters.
/// @param queue Queue structure pointer to manage.
/// @param manage Function pointer that takes an array of queue elements, the number of elements and other arguments
/// in the form of a 'args'.
/// @param args Generic void pointer arguments for manage function pointer.
static inline void forevery_queue(queue_s const * queue, const manage_queue_fn manage, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    manage(queue->elements + queue->current, queue->size, args);
}

#elif QUEUE_MODE == FINITE_PREPROCESSOR_QUEUE

#ifndef PREPROCESSOR_QUEUE_SIZE

#define PREPROCESSOR_QUEUE_SIZE (1 << 10)

#elif PREPROCESSOR_QUEUE_SIZE <= 0

#error 'PREPROCESSOR_QUEUE_SIZE' cannot be less than or equal to zero

#endif

/// queue data structure
typedef struct queue {
    size_t size, current;                              // size and current index of queue
    QUEUE_DATA_TYPE elements[PREPROCESSOR_QUEUE_SIZE]; // elements array
} queue_s;

/// @brief Creates empty queue.
/// @return Created queue structure.
static inline queue_s create_queue(void) {
    return (queue_s) { .size = 0, .current = 0 }; // only needs to initialize size and current to 0
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer to destroy.
/// @param destroy Function pointer to destroy (or free) elements in queue.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer is NULL.");

    const size_t right_size = (queue->current + queue->size) > PREPROCESSOR_QUEUE_SIZE ? PREPROCESSOR_QUEUE_SIZE - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        destroy(queue->elements + queue->current + i);
    }
    for (size_t i = 0; i < queue->size - right_size; ++i) {
        destroy(queue->elements + i);
    }

    queue->size = 0;
    queue->current = 0;
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure to check.
/// @return true if queue is full, false otherwise.
/// @note This function also returns true if preprocessor defined size is reached.
static inline bool is_full_queue(const queue_s queue) {
    return queue.size == PREPROCESSOR_QUEUE_SIZE;
}

/// @brief Gets element at the top of the queue without decrementing size (peek the first of the queue).
/// @param queue Queue structure to peek.
/// @return The first element of the queue.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");

    return queue.elements[queue.current];
}

/// @brief Sets the next end element in queue array to 'element' parameter (enqueues element).
/// @param queue Queue structure pointer to enqueue into.
/// @param element Element to push to end of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT((queue->size < PREPROCESSOR_QUEUE_SIZE) && "[ERROR] Queue reached maximum size");
    QUEUE_ASSERT((~queue->size) && "[ERROR] Queue's '.size' will overflow");

    memcpy(queue->elements + ((queue->current + queue->size) % PREPROCESSOR_QUEUE_SIZE), &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets and removes the start element in queue (dequeues start element).
/// @param queue Queue structure pointer to dequeue from.
/// @return The start element of the queue.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't pop empty queue");

    QUEUE_DATA_TYPE element = queue->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % PREPROCESSOR_QUEUE_SIZE;
    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure.
/// @param queue Queue structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in queue.
/// @return A 'copy' of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    QUEUE_ASSERT(copy && "[ERROR] 'copy' function pointer is NULL.");

    queue_s queue_copy = { .size = queue.size, .current = queue.current };

    const size_t right_size = (queue.current + queue.size) > PREPROCESSOR_QUEUE_SIZE ? PREPROCESSOR_QUEUE_SIZE - queue.current : queue.size;
    for (size_t i = 0; i < right_size; ++i) {
        queue_copy.elements[i + queue.current] = copy(queue.elements[i + queue.current]);
    }
    for (size_t i = 0; i < queue.size - right_size; ++i) {
        queue_copy.elements[i] = copy(queue.elements[i]);
    }

    return queue_copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure to check.
/// @return true if queue size is zero, false otherwise.
static inline bool is_empty_queue(const queue_s queue) {
    return queue.size == 0;
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer to clear.
/// @param destroy Function pointer to destroy an element in queue.
/// @note This function in this mode is just a copy of the 'destroy_queue' function.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' function pointer is NULL.");

    const size_t right_size = (queue->current + queue->size) > PREPROCESSOR_QUEUE_SIZE ? PREPROCESSOR_QUEUE_SIZE - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        destroy(queue->elements + queue->current + i);
    }
    for (size_t i = 0; i < queue->size - right_size; ++i) {
        destroy(queue->elements + i);
    }

    queue->size = 0;
    queue->current = 0;
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as a parameter.
/// @param queue Queue structure pointer to operate on.
/// @param operate Function pointer taht operates on single element pointer using 'args' as generic argument.
/// @param args Generic void pointer argument for 'operates' funtion pointer.
static inline void foreach_queue(queue_s * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    const size_t right_size = (queue->current + queue->size) > PREPROCESSOR_QUEUE_SIZE ? PREPROCESSOR_QUEUE_SIZE - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        if (!operate(queue->elements + queue->current + i, args)) {
            return;
        }
    }
    for (size_t i = 0; i < queue->size - right_size; ++i) {
        if (!operate(queue->elements + i, args)) {
            return;
        }
    }
}

/// @brief Forevery function that manages every element as an array with 'manage' function using queue's size and 'args'
/// as parameters.
/// @param queue Queue structure pointer to manage.
/// @param manage Function pointer that takes an array of queue elements, the number of elements and other arguments
/// in the form of a 'args'.
/// @param args Generic void pointer arguments for manage function pointer.
static inline void forevery_queue(queue_s * queue, const manage_queue_fn manage, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    QUEUE_DATA_TYPE elements_array[PREPROCESSOR_QUEUE_SIZE]; // declare array for temporary elements in queue

    // calculate right size of elements from current index to copy right and left elements into temporary array
    const size_t right_size = (queue->current + queue->size) > PREPROCESSOR_QUEUE_SIZE ? PREPROCESSOR_QUEUE_SIZE - queue->current : queue->size;

    memcpy(elements_array, queue->elements + queue->current, right_size * sizeof(QUEUE_DATA_TYPE));
    memcpy(elements_array + right_size, queue->elements, (queue->size - right_size) * sizeof(QUEUE_DATA_TYPE));

    manage(elements_array, queue->size, args); // manage elements in array

    memcpy(queue->elements, elements_array, queue->size * sizeof(QUEUE_DATA_TYPE)); // recopy elements back to queue's array but from queue's start
    queue->current = 0; // reset current index to 0
}

#endif

#else

#error Cannot include multiple headers in same unit.

#endif // QUEUE_H
