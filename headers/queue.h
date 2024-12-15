#ifndef QUEUE_H
#define QUEUE_H

#ifdef QUEUE_LICENCE

#error \
    This is free and unencumbered software released into the public domain. \
    \
    Anyone is free to copy, modify, publish, use, compile, sell, or         \
    distribute this software, either in source code form or as a compiled   \
    binary, for any purpose, commercial or non-commercial, and by any       \
    means.                                                                  \
    \
    In jurisdictions that recognize copyright laws, the author or authors   \
    of this software dedicate any and all copyright interest in the         \
    software to the public domain. We make this dedication for the benefit  \
    of the public at large and to the detriment of our heirs and            \
    successors. We intend this dedication to be an overt act of             \
    relinquishment in perpetuity of all present and future rights to this   \
    software under copyright law.                                           \
    \
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,         \
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF      \
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  \
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR       \
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,   \
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR   \
    OTHER DEALINGS IN THE SOFTWARE.                                         \
    \
    For more information, please refer to <https://unlicense.org>           \

#endif

// queue mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_LIST_QUEUE       0x5
#define FINITE_ALLOCATED_QUEUE    0x6
#define INFINITE_REALLOC_QUEUE    0x7
#define FINITE_PREPROCESSOR_QUEUE 0x8

#define INFINITE_QUEUE INFINITE_LIST_QUEUE
#define FINITE_QUEUE   FINITE_ALLOCATED_QUEUE

//#define QUEUE_MODE INFINITE_LIST_QUEUE
//#define QUEUE_MODE FINITE_ALLOCATED_QUEUE
//#define QUEUE_MODE INFINITE_REALLOC_QUEUE
//#define QUEUE_MODE FINITE_PREPROCESSOR_QUEUE
// Queue mode that can be set to INFINITE_LIST_QUEUE, FINITE_ALLOCATED_QUEUE, INFINITE_REALLOC_QUEUE or
// FINITE_PRERPOCESSOR_QUEUE.
// Default: INFINITE_LIST_QUEUE
#ifndef QUEUE_MODE

#define QUEUE_MODE INFINITE_QUEUE

#endif

#define IS_INFINITE_QUEUE ((bool)(QUEUE_MODE & 0x01))

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

#include <stdlib.h>  // imports size_t and malloc
#include <stdbool.h> // imports bool for conditional queue functions (is_[state]_queue())
#include <string.h>  // imports memcpy

#ifndef QUEUE_ASSERT

#include <assert.h>  // imports assert for debugging
#define QUEUE_ASSERT assert

#endif

#ifndef QUEUE_ALLOC

#define QUEUE_ALLOC malloc

#endif

#ifndef QUEUE_REALLOC

#define QUEUE_REALLOC realloc

#endif

#ifndef QUEUE_FREE

#define QUEUE_FREE free

#endif

/// Function pointer that creates a deep element copy.
typedef QUEUE_DATA_TYPE (*copy_queue_fn)    (const QUEUE_DATA_TYPE);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_queue_fn) (QUEUE_DATA_TYPE *);
/// Function pointer that changes an element pointer using void pointer arguments if needed.
typedef void            (*operate_queue_fn) (QUEUE_DATA_TYPE *, void *);

#if   QUEUE_MODE == INFINITE_LIST_QUEUE

// Queue list array size.
// DEFAULT: (1 << 10) or 1024
#ifndef LIST_ARRAY_QUEUE_CHUNK

#define LIST_ARRAY_QUEUE_CHUNK (1 << 10)

#elif LIST_ARRAY_QUEUE_CHUNK == 0

#error 'LIST_ARRAY_QUEUE_CHUNK' cannot be zero.

#endif

/// @brief Linked list of arrays that appends new list element at the end after array is full.
struct queue_list_array {
    QUEUE_DATA_TYPE elements[LIST_ARRAY_QUEUE_CHUNK]; // array to store elements
    struct queue_list_array * next; // next linked list array
};

/// @brief Queue implementation that uses appended lists of arrays and pushes elements based on the size.
typedef struct queue {
    struct queue_list_array * head; // head list element with the top of the queue
    struct queue_list_array * tail; // tail list element with the bottom of the queue
    size_t size, current; // size of queue and current index
} queue_s;

/// @brief Creates empty queue with everything set to zero/NULL.
/// @return Queue structure.
static inline queue_s create_queue(void) {
    return (queue_s) { 0 }; // queue.size and queue.current is 0 and head + tail pointers must be NULL
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer.
/// @param destroy function pointer to destroy (or free) elements in queue or NULL if queue element has
/// no allocated memory.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");

    if (queue->head == queue->tail) { // special case when first and last element are on the same list element array
        for (size_t s = queue->current; destroy && (s < queue->current + queue->size); s++) {
            destroy(&(queue->head->elements[s]));
        }
        QUEUE_FREE(queue->head); // frees head and tail at the same time, or does nothing if both are NULL
    } else {
        struct queue_list_array * list = queue->head;
        if (destroy) {
            size_t destroyed_size = LIST_ARRAY_QUEUE_CHUNK - queue->current;
            for (size_t s = queue->current; s < LIST_ARRAY_QUEUE_CHUNK; s++) {
                destroy(&(queue->head->elements[s]));
            }
            list = list->next;
            QUEUE_FREE(queue->head);

            while (list != queue->tail) {
                for (size_t s = 0; s < (destroyed_size += LIST_ARRAY_QUEUE_CHUNK); s++) {
                    destroy(&(list->elements[s]));
                }

                struct queue_list_array * temp = list;
                list = list->next;
                QUEUE_FREE(temp);
            }
            for (size_t s = 0; s < queue->size - destroyed_size; s++) {
                destroy(&(queue->tail->elements[s]));
            }
            QUEUE_FREE(queue->tail);
        } else {
            while (list != NULL) {
                struct queue_list_array * temp = list;
                list = list->next;
                QUEUE_FREE(temp);
            }
        }
    }

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure.
/// @return true if queue reached maximum size or overflows after incrementing it, false otherwise.
static inline bool is_full_queue(const queue_s queue) {
    return !(~queue.size); // checks if '.size' of type size_t won't overflown after pushing another element
}

/// @brief Gets element at the top of the queue without decrementing size (peek the first of the queue).
/// @param queue Queue structure.
/// @return The top element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");
    QUEUE_ASSERT(queue.head && "[ERROR] Queue head is NULL");

    return queue.head->elements[queue.current];
}

/// @brief Sets the next end element in queue array to 'element' parameter (enqueues element).
/// @param queue Queue structure pointer.
/// @param element Element to push to end of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(~(queue->size) && "[ERROR] Queue's '.size' will overflow");

    // index where the next element will be enqueued
    const size_t next_index = (queue->current + queue->size) % LIST_ARRAY_QUEUE_CHUNK;
    if (!next_index) { // if head list array is full (is divisible) adds new list element to head
        struct queue_list_array * temp = QUEUE_ALLOC(sizeof(struct queue_list_array));

        QUEUE_ASSERT(temp && "[ERROR] Memory allocation failed");
        temp->next = NULL; // prevent access to uninitialized memory

        if (queue->head == NULL) queue->head = queue->tail = temp;
        else queue->tail = queue->tail->next = temp;
    }

    memcpy(queue->tail->elements + next_index, &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues start element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't dequeue empty queue");
    QUEUE_ASSERT(queue->head && "[ERROR] Queue head is NULL");

    QUEUE_DATA_TYPE element = queue->head->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % LIST_ARRAY_QUEUE_CHUNK;

    if (!queue->size) { // queue is empty free memory and reset everything to zero
        QUEUE_FREE(queue->head);
        //queue->current = 0;
        queue->head = queue->tail = NULL;
    } else if (queue->current == 0) { // current index circles back, free start list element and shift to next
        struct queue_list_array * temp = queue->head->next;
        QUEUE_FREE(queue->head);
        queue->head = temp;
    }

    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy is NULL a shallow copy
/// will be created otherwise copy is called.
/// @param queue Queue structure.
/// @param copy Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    queue_s queue_copy = { .size = queue.size, .head = NULL, .tail = NULL, .current = queue.current };

    if (queue.head == queue.tail) {
        queue_copy.head = queue_copy.tail = QUEUE_ALLOC(sizeof(struct queue_list_array));
        QUEUE_ASSERT(queue_copy.head && "[ERROR] Memory allocation failed");
        queue_copy.head->next = NULL;

        for (size_t s = queue.current; s < queue.current + queue.size; s++) {
            queue_copy.head->elements[s] = copy ? copy(queue.head->elements[s]) : queue.head->elements[s];
        }
    } else {
        queue_copy.head = queue_copy.tail = QUEUE_ALLOC(sizeof(struct queue_list_array));
        QUEUE_ASSERT(queue_copy.head && "[ERROR] Memory allocation failed");

        for (size_t s = queue.current; s < LIST_ARRAY_QUEUE_CHUNK; s++) {
            queue_copy.head->elements[s] = copy ? copy(queue.head->elements[s]) : queue.head->elements[s];
        }
        size_t copied_size = LIST_ARRAY_QUEUE_CHUNK - queue.current;

        struct queue_list_array const * current_queue = queue.head->next;
        struct queue_list_array ** current_copy = &(queue_copy.head->next); // two pointer list to remove special .head case
        while (current_queue->next) {
            (*current_copy) = queue_copy.tail = QUEUE_ALLOC(sizeof(struct queue_list_array));
            QUEUE_ASSERT(*current_copy && "[ERROR] Memory allocation failed");

            for (size_t s = 0; s < LIST_ARRAY_QUEUE_CHUNK; s++) {
                queue_copy.head->elements[s] = copy ? copy(queue.head->elements[s]) : queue.head->elements[s];
            }
            copied_size += LIST_ARRAY_QUEUE_CHUNK;

            current_queue = current_queue->next;
        }

        (*current_copy) = queue_copy.tail = QUEUE_ALLOC(sizeof(struct queue_list_array));
        QUEUE_ASSERT(*current_copy && "[ERROR] Memory allocation failed");
        (*current_copy)->next = NULL; // only need to add NULL at the last node's next

        // calculate last node element count
        for (size_t s = 0; s < queue_copy.size - copied_size; s++) {
            queue_copy.tail->elements[s] = copy ? copy(queue.tail->elements[s]) : queue.tail->elements[s];
        }
    }

    return queue_copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    return queue.size == 0;
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer.
/// @param destroy Function pointer to destroy an element in queue.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");

    if (queue->head == queue->tail) { // special case when first and last element are on the same list element array
        for (size_t s = queue->current; destroy && (s < queue->current + queue->size); s++) {
            destroy(&(queue->head->elements[s]));
        }
        QUEUE_FREE(queue->head); // frees head and tail at the same time, or does nothing if both are NULL
    } else {
        struct queue_list_array * list = queue->head;
        if (destroy) {
            size_t destroyed_size = LIST_ARRAY_QUEUE_CHUNK - queue->current;
            for (size_t s = queue->current; s < LIST_ARRAY_QUEUE_CHUNK; s++) {
                destroy(&(queue->head->elements[s]));
            }
            list = list->next;
            QUEUE_FREE(queue->head);

            while (list != queue->tail) {
                for (size_t s = 0; s < (destroyed_size += LIST_ARRAY_QUEUE_CHUNK); s++) {
                    destroy(&(list->elements[s]));
                }

                struct queue_list_array * temp = list;
                list = list->next;
                QUEUE_FREE(temp);
            }
            for (size_t s = 0; s < queue->size - destroyed_size; s++) {
                destroy(&(queue->tail->elements[s]));
            }
            QUEUE_FREE(queue->tail);
        } else {
            while (list != NULL) {
                struct queue_list_array * temp = list;
                list = list->next;
                QUEUE_FREE(temp);
            }
        }
    }

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as parameters.
/// @param queue Queue structure pointer.
/// @param operate Function pointer taht operates on single element pointer using 'args' as arguments.
/// @param args Arguments for 'operates' funtion pointer.
static inline void foreach_queue(queue_s * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL");

    if (queue->head == queue->tail) { // if head and tail point to the same memory (including NULL)
        for (size_t i = queue->current; i < queue->current + queue->size; ++i) { // won't run if size is 0
            operate(queue->head->elements + i, args);
        }
    } else { // else queue is made up of more than one list node
        for (size_t i = queue->current; i < LIST_ARRAY_QUEUE_CHUNK; ++i) { // operate on head node
            operate(queue->head->elements + i, args);
        }
        size_t iterated_size = LIST_ARRAY_QUEUE_CHUNK - queue->current;
        struct queue_list_array * current = queue->head->next;
        while (current->next) { // operate on all nodes between head and tail node (excluding tail)
            for (size_t i = 0; i < LIST_ARRAY_QUEUE_CHUNK; ++i) {
                operate(current->elements + i, args);
            }
            iterated_size += LIST_ARRAY_QUEUE_CHUNK;
            current = current->next;
        }
        for (size_t i = 0; i < queue->size - iterated_size; ++i) { // operate on tail node
            operate(queue->tail->elements + i, args);
        }
    }
}

#elif QUEUE_MODE == FINITE_ALLOCATED_QUEUE

/// @brief Queue implementation that uses allocated memory array and pushes elements based on the current
/// and maximum size.
typedef struct queue {
    QUEUE_DATA_TYPE * elements; // pointer to allocated memory
    size_t max, size, current;  // maximum queue size, actual size and current index
} queue_s;

/// @brief Creates empty queue with '.size' and '.current' set to zero, elements with 'max' allocated memory
// and '.max' to parameter 'max'.
/// @param max Specifies maximum allocated size of queue structure.
/// @return Queue structure.
static inline queue_s create_queue(const size_t max) {
    QUEUE_ASSERT(max && "[ERROR] Maximum size can't be zero");
    const queue_s create = {
        .max = max, .elements = QUEUE_ALLOC(max * sizeof(QUEUE_DATA_TYPE)), .size = 0,
    };
    QUEUE_ASSERT(create.elements && "[ERROR] Memory allocation failed");
    return create;
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer.
/// @param destroy function pointer to destroy (or free) elements in queue or NULL if queue element has
/// no allocated memory.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL.");

    for(size_t s = queue->current; destroy && s < queue->current + queue->size; s++) {
        destroy(queue->elements + (s % queue->max));
    }

    QUEUE_FREE(queue->elements);
    *queue = (queue_s) { 0 };
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure.
/// @return true if queue size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_queue(const queue_s queue) {
    return !(queue.size < queue.max && ~queue.size);
}

/// @brief Gets element at the top of the queue without decrementing size (peeks the top of the queue).
/// @param queue Queue structure.
/// @return The top element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");
    QUEUE_ASSERT(queue.elements && "[ERROR] '.elements' is NULL");

    return queue.elements[queue.current];
}

/// @brief Sets the next end empty element in queue array to 'element' parameter (enqueues element to end).
/// @param queue Queue structure pointer.
/// @param element Element to push to top of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT((queue->size < queue->max) && "[ERROR] Queue reached maximum size");
    QUEUE_ASSERT((queue->size + 1) && "[ERROR] Queue's '.size' will overflow");
    QUEUE_ASSERT(queue->elements && "[ERROR] '.elements' is NULL");

    memcpy(queue->elements + ((queue->current + queue->size) % queue->max), &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't pop empty queue");
    QUEUE_ASSERT(queue->elements && "[ERROR] '.elements' is NULL");

    QUEUE_DATA_TYPE element = queue->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % queue->max;
    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy is null a shallow copy
/// will be created
/// otherwise copy is called.
/// @param queue Queue structure.
/// @param copy Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    QUEUE_ASSERT(queue.elements && "[ERROR] 'queue' has uninitialized memory.");
    QUEUE_ASSERT(queue.max >= queue.current && "[ERROR] Impossible queue state.");

    const queue_s queue_copy = {
        .size = queue.size, .current = queue.current, .max = queue.max,
        .elements = QUEUE_ALLOC(queue.max * sizeof(QUEUE_DATA_TYPE)),
    };
    QUEUE_ASSERT(queue_copy.elements && "[ERROR] Memory allocation failed");

    const size_t right_size =  queue.max - queue.current;
    if (queue.size > right_size) { // queue circles to beginning of elements array
        if (copy) {
            for (size_t s = queue.current; s < queue.max; s++) {
                queue_copy.elements[s] = copy(queue.elements[s]);
            }
            for (size_t s = 0; s < queue.size - right_size; s++) {
                queue_copy.elements[s] = copy(queue.elements[s]);
            }
        } else {
            const size_t copied_size = queue.max - queue.current;
            memcpy(queue_copy.elements + queue_copy.current, queue.elements + queue.current, sizeof(QUEUE_DATA_TYPE) * copied_size);
            memcpy(queue_copy.elements, queue.elements, sizeof(QUEUE_DATA_TYPE) * (queue.size - copied_size));
        }
    } else { // queue does not circle around to start
        if (copy) {
            for (size_t s = queue.current; s < queue.current + queue.size; s++) {
                queue_copy.elements[s] = copy(queue.elements[s]);
            }
        } else {
            memcpy(queue_copy.elements + queue_copy.current, queue.elements + queue.current, sizeof(QUEUE_DATA_TYPE) * queue.size);
        }
    }

    return queue_copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    return queue.size == 0;
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer.
/// @param destroy Function pointer to destroy an element in queue.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL.");

    for(size_t s = queue->current; destroy && s < queue->current + queue->size; s++) {
        destroy(queue->elements + (s % queue->max));
    }

    queue->size = 0;
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as parameters.
/// @param queue Queue structure pointer.
/// @param operate Function pointer taht operates on single element pointer using 'args' as arguments.
/// @param args Arguments for 'operates' funtion pointer.
static inline void foreach_queue(queue_s * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");
    QUEUE_ASSERT(queue->max >= queue->current && "[ERROR] Impossible queue state.");

    const size_t right_size = queue->max - queue->current;
    if (queue->size > right_size) { // if queue elements circle around
        for (size_t i = queue->current; i < queue->max; ++i) { // operates on elements right of current index
            operate(&(queue->elements[i]), args);
        }
        for (size_t i = 0; i < queue->size - right_size; i++) {// operates on elements left of current index
            operate(&(queue->elements[i]), args);
        }
    } else { // else elements are continuous in array (they don't circle around)
        for (size_t i = queue->current; i < queue->current + queue->size; ++i) {
            operate(&(queue->elements[i]), args);
        }
    }
}

#elif QUEUE_MODE == INFINITE_REALLOC_QUEUE

#ifndef REALLOC_QUEUE_CHUNK

#define REALLOC_QUEUE_CHUNK (1 << 10)

#endif

typedef struct queue {
    size_t size, current;
    QUEUE_DATA_TYPE * elements;
} queue_s;

/// @brief Creates empty queue with '.size' and '.current' set to zero and '.elements' set to NULL.
/// @return Queue structure.
static inline queue_s create_queue(void) {
    return (queue_s) { 0 };
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer.
/// @param destroy function pointer to destroy (or free) elements in queue or NULL if queue element
/// has no allocated memory.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");

    for(size_t s = 0; destroy && (s < queue->size); s++) {
        destroy(&(queue->elements[s + queue->current]));
    }

    QUEUE_FREE(queue->elements);

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Checks if queue's '.size' will overflow.
/// @param queue Queue structure.
/// @return true if queue size overflows after incrementing it, false otherwise
static inline bool is_full_queue(const queue_s queue) {
    return !(~queue.size);
}

/// @brief Gets element at the top of the queue without decrementing size (peeks the start of the queue).
/// @param queue Queue structure.
/// @return The top element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");
    QUEUE_ASSERT(queue.elements && "[ERROR] Queue's '.elements' is NULL");

    return queue.elements[queue.current];
}

/// @brief Sets the next top empty element in queue array to 'element' parameter (enqueues element to end).
/// @param queue Queue structure pointer.
/// @param element Element to enqueue to end of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT(~(queue->size) && "[ERROR] Queue's '.size' will overflow");

    // first expand memory if necessary and then add element
    const size_t actual_size = queue->current + queue->size;
    if ((actual_size % REALLOC_QUEUE_CHUNK) == 0) {
        queue->elements = QUEUE_REALLOC(queue->elements, (actual_size + REALLOC_QUEUE_CHUNK) * sizeof(QUEUE_DATA_TYPE));
        QUEUE_ASSERT(queue->elements && "[ERROR] Memory allocation failed");
    }
    memcpy(queue->elements + actual_size, &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues start element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't dequeue empty queue");
    QUEUE_ASSERT(queue->elements && "[ERROR] Can't dequeue NULL elements");

    // first remove element and then shrink memory if necessary
    QUEUE_DATA_TYPE element = queue->elements[queue->current++];
    queue->size--;
    if ((queue->size % REALLOC_QUEUE_CHUNK) == 0) {
        QUEUE_DATA_TYPE * temp = queue->size ? QUEUE_ALLOC(queue->size * sizeof(QUEUE_DATA_TYPE)) : NULL;

        // QUEUE_ASSERTion fails if allocation returns NULL on non-zero chunk size
        QUEUE_ASSERT((!queue->size || temp) && "[ERROR] Memory allocation failed.");

        memcpy(temp, &(queue->elements[queue->current]), queue->size * sizeof(QUEUE_DATA_TYPE));
        QUEUE_FREE(queue->elements);
        queue->elements = temp;
        queue->current = 0;
    }

    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy is null a shallow copy
/// will be created
/// otherwise 'copy' is called.
/// @param queue Queue structure.
/// @param copy Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    if (!queue.size) return (queue_s) { 0 };

    const size_t mod_size = queue.size % REALLOC_QUEUE_CHUNK;
    const size_t copy_size = mod_size ? queue.size - (mod_size) + REALLOC_QUEUE_CHUNK : queue.size;

    const queue_s queue_copy = {
        .size = queue.size, .current = queue.current,
        .elements = QUEUE_ALLOC(copy_size * sizeof(QUEUE_DATA_TYPE)),
    };
    QUEUE_ASSERT(queue_copy.elements && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t s = queue.current; s < queue.current + queue.size; s++) {
            queue_copy.elements[s] = copy(queue.elements[s]);
        }
    } else {
        memcpy(&(queue_copy.elements[queue.current]), &(queue.elements[queue.current]), sizeof(QUEUE_DATA_TYPE) * queue.size);
    }

    return queue_copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    return queue.size == 0;
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer.
/// @param destroy Function pointer to destroy an element in queue.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");

    for(size_t s = 0; destroy && (s < queue->size); s++) {
        destroy(&(queue->elements[s + queue->current]));
    }

    QUEUE_FREE(queue->elements);

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as parameters.
/// @param queue Queue structure pointer.
/// @param operate Function pointer taht operates on single element pointer using 'args' as arguments.
/// @param args Arguments for 'operates' funtion pointer.
static inline void foreach_queue(queue_s * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    for (size_t i = queue->current; i < queue->current + queue->size; ++i) {
        operate(&(queue->elements[i]), args);
    }
}

#elif QUEUE_MODE == FINITE_PREPROCESSOR_QUEUE

#ifndef PREPROCESSOR_QUEUE_SIZE

#define PREPROCESSOR_QUEUE_SIZE (1 << 10)

#elif PREPROCESSOR_QUEUE_SIZE <= 0

#error 'PREPROCESSOR_QUEUE_SIZE' cannot be less than or equal to zero

#endif

typedef struct queue {
    size_t size, current;                              // size and current index of queue
    QUEUE_DATA_TYPE elements[PREPROCESSOR_QUEUE_SIZE]; // elements array
} queue_s;

/// @brief Creates empty queue with '.size' set to zero.
/// @return Queue structure.
static inline queue_s create_queue(void) {
    return (queue_s) { .size = 0, .current = 0 }; // only needs to initialize size and current to 0
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer.
/// @param destroy function pointer to destroy (or free) elements in queue or NULL if queue element has
/// no allocated memory.
static inline void destroy_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");

    if (destroy) {
        if (queue->size > PREPROCESSOR_QUEUE_SIZE - queue->current) { // queue circles to beginning of elements array
            for(size_t s = queue->current; s < PREPROCESSOR_QUEUE_SIZE; s++) {
                destroy(queue->elements + s);
            }
            for(size_t s = 0; s < (queue->size - (PREPROCESSOR_QUEUE_SIZE - queue->current)); s++) {
                destroy(queue->elements + s);
            }
        } else { // queue has all element to the right
            for(size_t s = queue->current; s < queue->current + queue->size; s++) {
                destroy(queue->elements + s);
            }
        }
    }

    queue->size = 0;
    queue->current = 0;
}

/// @brief Checks if queue is full or if queue's '.size' will overflow.
/// @param queue Queue structure.
/// @return true if queue size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_queue(const queue_s queue) {
    return !((queue.size < PREPROCESSOR_QUEUE_SIZE) && (~queue.size));
}

/// @brief Gets element at the top of the queue without decrementing size (peeks the start of the queue).
/// @param queue Queue structure.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    QUEUE_ASSERT(queue.size && "[ERROR] Can't peek empty queue");

    return queue.elements[queue.current];
}

/// @brief Sets the next end empty element in queue array to 'element' parameter (enqueues element to end).
/// @param queue Queue structure pointer.
/// @param element Element to push to top of queue array.
static inline void enqueue(queue_s * queue, const QUEUE_DATA_TYPE element) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");
    QUEUE_ASSERT((queue->size < PREPROCESSOR_QUEUE_SIZE) && "[ERROR] Queue reached maximum size");
    QUEUE_ASSERT((~queue->size) && "[ERROR] Queue's '.size' will overflow");

    memcpy(queue->elements + ((queue->current + queue->size) % PREPROCESSOR_QUEUE_SIZE), &element, sizeof(QUEUE_DATA_TYPE));
    queue->size++;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' pointer is empty");
    QUEUE_ASSERT(queue->size && "[ERROR] Can't pop empty queue");

    QUEUE_DATA_TYPE element = queue->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % PREPROCESSOR_QUEUE_SIZE;
    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy is null a shallow copy
/// will be created
/// otherwise copy is called.
/// @param queue Queue structure.
/// @param copy Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, const copy_queue_fn copy) {
    queue_s queue_copy = { .size = queue.size, .current = queue.current };

    const size_t right_size = PREPROCESSOR_QUEUE_SIZE - queue.current;
    if (queue.size > right_size) { // queue circles to beginning of elements array
        const size_t left_size  = queue.size - right_size;

        if (copy) {
            for (size_t s = queue.current; s < right_size + queue.current; s++) {
                queue_copy.elements[s] = copy(queue.elements[s]);
            }
            for (size_t s = 0; s < left_size; s++) {
                queue_copy.elements[s] = copy(queue.elements[s]);
            }
        } else {
            memcpy(queue_copy.elements + queue_copy.current, queue.elements + queue.current, sizeof(QUEUE_DATA_TYPE) * right_size);
            memcpy(queue_copy.elements, queue.elements, sizeof(QUEUE_DATA_TYPE) * left_size);
        }
    } else { // queue has all element to the right
        if (copy) {
            for (size_t s = queue.current; s < queue.size + queue.current; s++) {
                queue_copy.elements[s] = copy(queue.elements[s]);
            }
        } else {
            memcpy(queue_copy.elements + queue_copy.current, queue.elements + queue.current, sizeof(QUEUE_DATA_TYPE) * queue.size);
        }
    }

    return queue_copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    return queue.size == 0;
}

/// @brief Clears all elements from the queue.
/// @param queue Queue structure pointer.
/// @param destroy Function pointer to destroy an element in queue.
static inline void clear_queue(queue_s * queue, const destroy_queue_fn destroy) {
    QUEUE_ASSERT(queue && "[ERROR] Queue pointer is NULL");

    if (destroy) {
        if (queue->size > PREPROCESSOR_QUEUE_SIZE - queue->current) { // queue circles to beginning of elements array
            for(size_t s = queue->current; s < PREPROCESSOR_QUEUE_SIZE; s++) {
                destroy(queue->elements + s);
            }
            for(size_t s = 0; s < (queue->size - (PREPROCESSOR_QUEUE_SIZE - queue->current)); s++) {
                destroy(queue->elements + s);
            }
        } else { // queue has all element to the right
            for(size_t s = queue->current; s < queue->current + queue->size; s++) {
                destroy(queue->elements + s);
            }
        }
    }

    queue->size = 0;
    queue->current = 0;
}

/// @brief Foreach funtion that iterates over all elements in queue and performs 'operate' function on them using 'args'
/// as parameters.
/// @param queue Queue structure pointer.
/// @param operate Function pointer taht operates on single element pointer using 'args' as arguments.
/// @param args Arguments for 'operates' funtion pointer.
static inline void foreach_queue(queue_s * queue, const operate_queue_fn operate, void * args) {
    QUEUE_ASSERT(queue && "[ERROR] 'queue' parameter pointer is NULL.");
    QUEUE_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    const size_t right_size = PREPROCESSOR_QUEUE_SIZE - queue->current;
    if (queue->size > right_size) { // if queue elements circle around
        for (size_t i = queue->current; i < PREPROCESSOR_QUEUE_SIZE; ++i) { // operates on elements right of current index
            operate(&(queue->elements[i]), args);
        }
        for (size_t i = 0; i < queue->size - right_size; i++) {// operates on elements left of current index
            operate(&(queue->elements[i]), args);
        }
    } else { // else elements are continuous in array (they don't circle around)
        for (size_t i = queue->current; i < queue->current + queue->size; ++i) {
            operate(&(queue->elements[i]), args);
        }
    }
}

#endif

#endif // QUEUE_H
