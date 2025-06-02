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

// Queue data type to specify what datatype to queue.
// DEFAULT: void *
#ifndef QUEUE_DATA_TYPE

#define QUEUE_DATA_TYPE void*

#endif

#ifndef QUEUE_ASSERT

#include <assert.h>  // imports assert for debugging
#define QUEUE_ASSERT assert

#endif

/// Function pointer that creates a deep element copy.
typedef QUEUE_DATA_TYPE (*copy_queue_fn)    (const QUEUE_DATA_TYPE);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_queue_fn) (QUEUE_DATA_TYPE *);
/// Function pointer that changes an element pointer using void pointer arguments if needed.
typedef bool            (*operate_queue_fn) (QUEUE_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void            (*manage_queue_fn)  (QUEUE_DATA_TYPE *, const size_t, void *);

#ifndef QUEUE_SIZE

#define QUEUE_SIZE (1 << 10)

#elif QUEUE_SIZE <= 0

#error 'QUEUE_SIZE' cannot be less than or equal to zero

#endif

/// queue data structure
typedef struct queue {
    QUEUE_DATA_TYPE elements[QUEUE_SIZE]; // elements array
    size_t size, current;                 // size and current index of queue
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
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");
    QUEUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    const size_t right_size = (queue->current + queue->size) > QUEUE_SIZE ? QUEUE_SIZE - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        destroy(queue->elements + queue->current + i);
    }
    queue->size -= right_size;
    for (; queue->size; queue->size--) {
        destroy(queue->elements + (queue->size - 1));
    }

    queue->current = 0;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure to check.
/// @return true if queue size is zero, false otherwise.
static inline bool is_empty_queue(const queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    return !(queue->size);
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure to check.
/// @return true if queue is full, false otherwise.
/// @note This function also returns true if preprocessor defined size is reached.
static inline bool is_full_queue(const queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    return queue->size == QUEUE_SIZE;
}

/// @brief Gets element at the top of the queue without decrementing size (peek the first of the queue).
/// @param queue Queue structure to peek.
/// @return The first element of the queue.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't peek empty queue");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    return queue->elements[queue->current];
}

/// @brief Sets the next end element in queue array to 'element' parameter (enqueues element).
/// @param queue Queue structure pointer to enqueue into.
/// @param element Element to push to end of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");
    QUEUE_ASSERT((queue->size < QUEUE_SIZE) && "[ERROR] Queue reached maximum size");
    QUEUE_ASSERT((~queue->size) && "[ERROR] Queue's '.size' will overflow");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    memcpy(queue->elements + ((queue->current + queue->size) % QUEUE_SIZE), &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets and removes the start element in queue (dequeues start element).
/// @param queue Queue structure pointer to dequeue from.
/// @return The start element of the queue.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't pop empty queue");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    QUEUE_DATA_TYPE element = queue->elements[queue->current++];
    queue->size--;

    if (QUEUE_SIZE == queue->current) {
        queue->current = 0;
    }

    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure.
/// @param queue Queue structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in queue.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s * queue, const copy_queue_fn copy) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");
    QUEUE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    queue_s queue_copy = { .size = queue->size, .current = queue->current };

    const size_t right_size = (queue->current + queue->size) > QUEUE_SIZE ? QUEUE_SIZE - queue->current : queue->size;
    for (size_t i = 0; i < right_size; ++i) {
        queue_copy.elements[i + queue->current] = copy(queue->elements[i + queue->current]);
    }
    for (size_t i = 0; i < queue->size - right_size; ++i) {
        queue_copy.elements[i] = copy(queue->elements[i]);
    }

    return queue_copy;
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as a parameter.
/// @param queue Queue structure pointer to operate on.
/// @param operate Function pointer taht operates on single element pointer using 'args' as generic argument.
/// @param args Generic void pointer argument for 'operates' funtion pointer.
static inline void foreach_queue(queue_s * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    const size_t right_size = (queue->current + queue->size) > QUEUE_SIZE ? QUEUE_SIZE - queue->current : queue->size;
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

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param queue Queue structure pointer to manage.
/// @param manage Function pointer that takes an array of queue elements, the number of elements and other arguments
/// in the form of a 'args'.
/// @param args Generic void pointer arguments for manage function pointer.
static inline void map_queue(queue_s * queue, const manage_queue_fn manage, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter is NULL.");
    QUEUE_ASSERT(manage && "[ERROR] 'operate' parameter is NULL.");

    QUEUE_ASSERT(queue->size <= QUEUE_SIZE && "[ERROR] Invalid queue size.");

    QUEUE_DATA_TYPE elements_array[QUEUE_SIZE]; // declare array for temporary elements in queue

    // calculate right size of elements from current index to copy right and left elements into temporary array
    const size_t right_size = (queue->current + queue->size) > QUEUE_SIZE ? QUEUE_SIZE - queue->current : queue->size;

    memcpy(elements_array, queue->elements + queue->current, right_size * sizeof(QUEUE_DATA_TYPE));
    memcpy(elements_array + right_size, queue->elements, (queue->size - right_size) * sizeof(QUEUE_DATA_TYPE));

    manage(elements_array, queue->size, args); // manage elements in array

    memcpy(queue->elements, elements_array, queue->size * sizeof(QUEUE_DATA_TYPE)); // recopy elements back to queue's array but from queue's start
    queue->current = 0; // reset current index to 0
}

#else

#error Cannot include multiple headers in same unit.

#endif // QUEUE_H
