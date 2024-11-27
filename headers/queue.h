#ifndef QUEUE_H
#define QUEUE_H

// queue mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_LIST_QUEUE       0x08
#define FINITE_ALLOCATED_QUEUE    0x0A
#define INFINITE_REALLOC_QUEUE    0x18
#define FINITE_PRERPOCESSOR_QUEUE 0x20

#define INFINITE_QUEUE INFINITE_LIST_QUEUE
#define FINITE_QUEUE   FINITE_ALLOCATED_QUEUE

//#define QUEUE_MODE FINITE_ALLOCATED_QUEUE
// Queue mode that can be set to INFINITE_LIST_QUEUE, FINITE_ALLOCATED_QUEUE, INFINITE_REALLOC_QUEUE or
// FINITE_PRERPOCESSOR_QUEUE.
// Default: INFINITE_LIST_QUEUE
#ifndef QUEUE_MODE

#define QUEUE_MODE INFINITE_QUEUE

#endif

#define IS_INFINITE_QUEUE ((bool)(QUEUE_MODE & 0x08))

// Check to make sure a valid queue mode is selected.
#if (QUEUE_MODE != INFINITE_LIST_QUEUE)    && (QUEUE_MODE != FINITE_ALLOCATED_QUEUE) && \
    (QUEUE_MODE != INFINITE_REALLOC_QUEUE) && (QUEUE_MODE != FINITE_PRERPOCESSOR_QUEUE)

#error Invalid type of queue mode.

#endif

// Queue data type to specify what datatype to queue.
// DEFAULT: void *
#ifndef QUEUE_DATA_TYPE

#define QUEUE_DATA_TYPE void*

#endif

#include <stdlib.h>  // imports size_t and malloc
#include <assert.h>  // imports assert for debugging
#include <stdbool.h> // imports bool for conditional queue functions (is_[state]_queue())
#include <string.h>  // imports memcpy

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
    struct queue_list_array * next; // next linked list array
    QUEUE_DATA_TYPE elements[LIST_ARRAY_QUEUE_CHUNK]; // array to store elements
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
/// @param destroy_element function pointer to destroy (or free) elements in queue or NULL if queue element has
/// no allocated memory.
static inline void destroy_queue(queue_s * queue, void (*destroy_element)(QUEUE_DATA_TYPE *)) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] Queue pointer is NULL");

    if (queue->head == queue->tail) { // special case when first and last element are on the same list element array
        for (size_t s = queue->current; destroy_element && (s < queue->current + queue->size); s++) {
            destroy_element(&(queue->head->elements[s]));
        }
        free(queue->head); // frees head and tail at the same time, or does nothing if both are NULL
    } else {
        struct queue_list_array * list = queue->head;
        if (destroy_element) {
            size_t destroyed_size = LIST_ARRAY_QUEUE_CHUNK - queue->current;
            for (size_t s = queue->current; s < LIST_ARRAY_QUEUE_CHUNK; s++) {
                destroy_element(&(queue->head->elements[s]));
            }
            list = list->next;
            free(queue->head);

            while (list != queue->tail) {
                for (size_t s = 0; s < (destroyed_size += LIST_ARRAY_QUEUE_CHUNK); s++) {
                    destroy_element(&(list->elements[s]));
                }

                struct queue_list_array * temp = list;
                list = list->next;
                free(temp);
            }
            for (size_t s = 0; s < queue->size - destroyed_size; s++) {
                destroy_element(&(queue->tail->elements[s]));
            }
            free(queue->tail);
        } else {
            while (list != NULL) {
                struct queue_list_array * temp = list;
                list = list->next;
                free(temp);
            }
        }
    }

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure.
/// @return true if queue reached maximum size or overflows after incrementing it, false otherwise.
static inline bool is_full_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    return !(~queue.size); // checks if '.size' of type size_t won't overflown after pushing another element
}

/// @brief Gets element at the top of the queue without decrementing size (peek the first of the queue).
/// @param queue Queue structure.
/// @return The top element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue.size && "[ERROR] Can't peek empty queue");
    assert(queue.head && "[ERROR] Queue head is NULL");

    return queue.head->elements[queue.current];
}

/// @brief Sets the next end element in queue array to 'element' parameter (enqueues element).
/// @param queue Queue structure pointer.
/// @param element Element to push to end of queue array.
static inline void enqueue(queue_s * queue, QUEUE_DATA_TYPE element) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] Queue pointer is NULL");
    assert(~(queue->size) && "[ERROR] Queue's '.size' will overflow");

    // index where the next element will be enqueued
    const size_t next_index = (queue->current + queue->size) % LIST_ARRAY_QUEUE_CHUNK;
    if (0 == next_index) { // if head list array is full (is divisible) adds new list element to head
        struct queue_list_array * temp = malloc(sizeof(struct queue_list_array));

        assert(temp && "[ERROR] Memory allocation failed");
        temp->next = NULL; // prevent access to uninitialized memory

        if (queue->head == NULL) queue->head = queue->tail = temp;
        else queue->tail = queue->tail->next = temp;
    }

    queue->tail->elements[next_index] = element;
    queue->size++;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues start element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] 'queue' pointer is empty");
    assert(queue->size && "[ERROR] Can't dequeue empty queue");
    assert(queue->head && "[ERROR] Queue head is NULL");

    QUEUE_DATA_TYPE element = queue->head->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % LIST_ARRAY_QUEUE_CHUNK;

    if (!queue->size) { // queue is empty free memory and reset everything to zero
        free(queue->head);
        queue->current = 0;
        queue->head = queue->tail = NULL;
    } else if (queue->current == 0) { // current index circles back, free start list element and shift to next
        struct queue_list_array * temp = queue->head->next;
        free(queue->head);
        queue->head = temp;
    }

    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy_element is NULL a shallow copy
/// will be created otherwise copy_element is called.
/// @param queue Queue structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, QUEUE_DATA_TYPE (*copy_element)(QUEUE_DATA_TYPE)) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    queue_s copy = { .size = queue.size, .head = NULL, .tail = NULL, .current = queue.current };

    struct queue_list_array const * current_queue = queue.head;
    struct queue_list_array ** current_copy = &(copy.head); // two pointer list to remove special .head case
    while (current_queue) { // three special cases: head, middle, tail
        const size_t tail_size = (queue.current + queue.size) % LIST_ARRAY_QUEUE_CHUNK; // end/tail size

        const size_t start = current_queue == queue.head ? queue.current : 0; // start size current when head case
        const size_t end = current_queue != queue.tail || !tail_size ? LIST_ARRAY_QUEUE_CHUNK : tail_size;

        copy.tail = *current_copy = malloc(sizeof(struct queue_list_array));
        assert(*current_copy && "[ERROR] Memory allocation failed");
        (*current_copy)->next = NULL;

        if (copy_element) {
            for (size_t s = start; s < end; s++) {
                (*current_copy)->elements[s] = copy_element(current_queue->elements[s]);
            }
        } else {
            const size_t chunk_size = sizeof(QUEUE_DATA_TYPE) * (end - start);
            memcpy(&((*current_copy)->elements[start]), &(current_queue->elements[start]), chunk_size);
        }

        current_queue = current_queue->next;
        current_copy = &((*current_copy)->next);
    }

    return copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    return queue.size == 0;
}

/// @brief Sorts queue elements using a function specified by the user, if function parameter is NULL a bubble sort
/// implementation with 'memcmp' will be used.
/// @param queue Queue structure pointer.
/// @param sort_elements Function pointer to sorting algorithm or NULL, if bubble sort should be used.
static inline void sort_queue(queue_s const * queue, void (*sort_elements)(QUEUE_DATA_TYPE *, size_t)) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] 'queue' parameter is NULL");

    QUEUE_DATA_TYPE * elements_array = malloc(sizeof(QUEUE_DATA_TYPE) * queue->size);
    assert((!(queue->size) || elements_array) && "[ERROR] Memory allocation failed.");

    if (queue->head == queue->tail) { // special case where either the queue is empty or only one chunk has elements
        memcpy(elements_array, &(queue->head->elements[queue->current]), sizeof(QUEUE_DATA_TYPE) * queue->size);

        if (sort_elements) {
            sort_elements(elements_array, queue->size);
        } else {
            for (size_t s = 0; s < queue->size - 1; ++s) { // bubble sort bad !!!
                for (size_t i = 0; i < queue->size - s - 1; ++i) {
                    if (memcmp(&(elements_array[i]), &(elements_array[i + 1]), sizeof(QUEUE_DATA_TYPE)) > 0) {
                        QUEUE_DATA_TYPE temp = elements_array[i];
                        elements_array[i] = elements_array[i + 1];
                        elements_array[i + 1] = temp;
                    }
                }
            }
        }

        memcpy(&(queue->head->elements[queue->current]), elements_array, sizeof(QUEUE_DATA_TYPE) * queue->size);
    } else { // other case when more list chunks are allocated
        size_t copied_size = (LIST_ARRAY_QUEUE_CHUNK - queue->current); // filled size in one chunk

        memcpy(elements_array, &(queue->head->elements[queue->current]), sizeof(QUEUE_DATA_TYPE) * copied_size);
        struct queue_list_array * current = queue->head->next;
        while (current != queue->tail) { // copy other chunks between head and tail where elements arrays are full
            memcpy(&(elements_array[copied_size]), current->elements, copied_size += LIST_ARRAY_QUEUE_CHUNK);
            current = current->next;
        }
        memcpy(&(elements_array[copied_size]), queue->tail->elements, queue->size - copied_size); // copy tail

        if (sort_elements) {
            sort_elements(elements_array, queue->size);
        } else {
            for (size_t s = 0; queue->size && s < queue->size - 1; ++s) {
                for (size_t i = 0; i < queue->size - s - 1; ++i) {
                    if (memcmp(&(elements_array[i]), &(elements_array[i + 1]), sizeof(QUEUE_DATA_TYPE)) > 0) {
                        QUEUE_DATA_TYPE temp = elements_array[i];
                        elements_array[i] = elements_array[i + 1];
                        elements_array[i + 1] = temp;
                    }
                }
            }
        }

        copied_size = (LIST_ARRAY_QUEUE_CHUNK - queue->current); // reset copy size
        memcpy(&(queue->head->elements[queue->current]), elements_array, sizeof(QUEUE_DATA_TYPE) * copied_size);
        current = queue->head->next; // reset current pointer to head's next chunk
        while (current != queue->tail) {
            memcpy(current->elements, &(elements_array[copied_size]), copied_size += LIST_ARRAY_QUEUE_CHUNK);
            current = current->next;
        }
        memcpy(queue->tail->elements, &(elements_array[copied_size]), queue->size - copied_size);
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
    assert(max && "[ERROR] Maximum size can't be zero");
    const queue_s create = {
        .max = max, .elements = malloc(sizeof(QUEUE_DATA_TYPE) * max), .size = 0,
    };
    assert(create.elements && "[ERROR] Memory allocation failed");
    return create;
}

/// @brief Destroys queue and all elements in it.
/// @param queue Queue structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in queue or NULL if queue element has
/// no allocated memory.
static inline void destroy_queue(queue_s * queue, void (*destroy_element)(QUEUE_DATA_TYPE *)) {
    assert(queue && "[ERROR] Queue pointer is NULL.");
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue->max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");

    if (destroy_element) {
        for(size_t s = queue->current; s < queue->current + queue->size; s++) {
            destroy_element(queue->elements + (s % queue->max));
        }
    }

    free(queue->elements);
    *queue = (queue_s) { 0 };
}

/// @brief Checks if queue is full or if queue's .size will overflow.
/// @param queue Queue structure.
/// @return true if queue size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue.max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");

    return !(queue.size < queue.max && ~queue.size);
}

/// @brief Gets element at the top of the queue without decrementing size (peeks the top of the queue).
/// @param queue Queue structure.
/// @return The top element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue.max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");
    assert(queue.size && "[ERROR] Can't peek empty queue");
    assert(queue.elements && "[ERROR] '.elements' is NULL");

    return queue.elements[queue.current];
}

/// @brief Sets the next end empty element in queue array to 'element' parameter (enqueues element to end).
/// @param queue Queue structure pointer.
/// @param element Element to push to top of queue array.
static inline void enqueue(queue_s * queue, QUEUE_DATA_TYPE element) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue->max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");
    assert(queue && "[ERROR] Queue pointer is NULL");
    assert((queue->size < queue->max) && "[ERROR] Queue reached maximum size");
    assert((queue->size + 1) && "[ERROR] Queue's '.size' will overflow");
    assert(queue->elements && "[ERROR] '.elements' is NULL");

    queue->elements[(queue->current + queue->size++) % queue->max] = element;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue->max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");
    assert(queue && "[ERROR] 'queue' pointer is empty");
    assert(queue->size && "[ERROR] Can't pop empty queue");
    assert(queue->elements && "[ERROR] '.elements' is NULL");

    QUEUE_DATA_TYPE element = queue->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % queue->max;
    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param queue Queue structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, QUEUE_DATA_TYPE (*copy_element)(QUEUE_DATA_TYPE)) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue.max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");
    assert(queue.elements && "[ERROR] 'queue' has uninitialized memory.");

    const queue_s copy = {
        .size = queue.size, .current = queue.current, .max = queue.max,
        .elements = malloc(sizeof(QUEUE_DATA_TYPE) * queue.max),
    };
    assert(copy.elements && "[ERROR] Memory allocation failed");

    if (queue.size > queue.max - queue.current) { // queue circles to beginning of elements array
        if (copy_element) {
            for (size_t s = queue.current; s < queue.max; s++) {
                copy.elements[s] = copy_element(queue.elements[s]);
            }
            for (size_t s = 0; s < queue.size - (queue.max - queue.current); s++) {
                copy.elements[s] = copy_element(queue.elements[s]);
            }
        } else {
            const size_t copied_size = queue.max - queue.current;
            memcpy(&(copy.elements[copy.current]), &(queue.elements[queue.current]), sizeof(QUEUE_DATA_TYPE) * copied_size);
            memcpy(copy.elements, queue.elements, sizeof(QUEUE_DATA_TYPE) * (queue.size - copied_size));
        }
    } else { // queue does not circle around to start
        if (copy_element) {
            for (size_t s = queue.current; s < queue.current + queue.size; s++) {
                copy.elements[s] = copy_element(queue.elements[s]);
            }
        } else {
            memcpy(&(copy.elements[copy.current]), &(queue.elements[queue.current]), sizeof(QUEUE_DATA_TYPE) * queue.size);
        }
    }

    return copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue.max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");

    return queue.size == 0;
}

/// @brief Sorts queue elements using a function specified by the user, if function parameter is NULL a bubble sort
/// implementation with 'memcmp' will be used.
/// @param queue Queue structure pointer.
/// @param sort_elements Function pointer to sorting algorithm or NULL, if bubble sort should be used.
static inline void sort_queue(queue_s const * queue, void (*sort_elements)(QUEUE_DATA_TYPE *, size_t)) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue->max < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue max size.");
    assert(queue && "[ERROR] 'queue' parameter is NULL");

    if (queue->size > queue->max - queue->current) {
        QUEUE_DATA_TYPE * elements_array = malloc(sizeof(QUEUE_DATA_TYPE) * queue->size);
        assert((!(queue->size) || elements_array) && "[ERROR] Memory allocation failed.");

        const size_t copy_size = queue->max - queue->current;
        memcpy(elements_array, &(queue->elements[queue->current]), sizeof(QUEUE_DATA_TYPE) * copy_size);
        memcpy(&(elements_array[copy_size]), queue->elements, queue->size - copy_size);

        if (sort_elements) {
            sort_elements(elements_array, queue->size);
        } else {
            for (size_t s = 0; queue->size && s < queue->size - 1; ++s) {
                for (size_t i = 0; i < queue->size - s - 1; ++i) {
                    if (memcmp(&(elements_array[i]), &(elements_array[i + 1]), sizeof(QUEUE_DATA_TYPE)) > 0) {
                        QUEUE_DATA_TYPE temp = elements_array[i];
                        elements_array[i] = elements_array[i + 1];
                        elements_array[i + 1] = temp;
                    }
                }
            }
        }

        memcpy(&(queue->elements[queue->current]), elements_array, sizeof(QUEUE_DATA_TYPE) * copy_size);
        memcpy(queue->elements, &(elements_array[copy_size]), queue->size - copy_size);
    } else {
        if (sort_elements) {
            sort_elements(queue->elements, queue->size);
        } else {
            for (size_t s = queue->current; queue->size && s < queue->current + queue->size - 1; ++s) {
                for (size_t i = queue->current; i < queue->current + queue->size - s - 1; ++i) {
                    if (memcmp(&(queue->elements[i]), &(queue->elements[i + 1]), sizeof(QUEUE_DATA_TYPE)) > 0) {
                        QUEUE_DATA_TYPE temp = queue->elements[i];
                        queue->elements[i] = queue->elements[i + 1];
                        queue->elements[i + 1] = temp;
                    }
                }
            }
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
/// @param destroy_element function pointer to destroy (or free) elements in queue or NULL if queue element
/// has no allocated memory.
static inline void destroy_queue(queue_s * queue, void (*destroy_element)(QUEUE_DATA_TYPE *)) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] Queue pointer is NULL");

    for(size_t s = 0; destroy_element && (s < queue->size); s++) {
        destroy_element(&(queue->elements[s + queue->current]));
    }

    free(queue->elements);

    *queue = (queue_s) { 0 }; // reset queue to zero
}

/// @brief Checks if queue's '.size' will overflow.
/// @param queue Queue structure.
/// @return true if queue size overflows after incrementing it, false otherwise
static inline bool is_full_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    return !(~queue.size);
}

/// @brief Gets element at the top of the queue without decrementing size (peeks the start of the queue).
/// @param queue Queue structure.
/// @return The top element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue.size && "[ERROR] Can't peek empty queue");
    assert(queue.elements && "[ERROR] Queue's '.elements' is NULL");

    return queue.elements[queue.current];
}

/// @brief Sets the next top empty element in queue array to 'element' parameter (enqueues element to end).
/// @param queue Queue structure pointer.
/// @param element Element to enqueue to end of queue array.
static inline void enqueue(queue_s * queue, QUEUE_DATA_TYPE element) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] Queue pointer is NULL");
    assert(~(queue->size) && "[ERROR] Queue's '.size' will overflow");

    // first expand memory if necessary and then add element
    size_t actual_size = queue->current + queue->size;
    if ((actual_size % REALLOC_QUEUE_CHUNK) == 0) {
        queue->elements = realloc(queue->elements, (actual_size + REALLOC_QUEUE_CHUNK) * sizeof(QUEUE_DATA_TYPE));
        assert(queue->elements && "[ERROR] Memory allocation failed");
    }
    queue->elements[queue->size++] = element;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues start element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] 'queue' pointer is empty");
    assert(queue->size && "[ERROR] Can't dequeue empty queue");
    assert(queue->elements && "[ERROR] Can't dequeue NULL elements");

    // first remove element and then shrink memory if necessary
    QUEUE_DATA_TYPE element = queue->elements[queue->current++];
    queue->size--;
    if ((queue->size % REALLOC_QUEUE_CHUNK) == 0) {
        QUEUE_DATA_TYPE * temp = queue->size ? malloc(queue->size * sizeof(QUEUE_DATA_TYPE)) : NULL;

        // assertion fails if malloc returns NULL on non-zero chunk size
        assert((!queue->size || temp) && "[ERROR] Memory allocation failed.");

        memcpy(temp, &(queue->elements[queue->current]), queue->size * sizeof(QUEUE_DATA_TYPE));
        free(queue->elements);
        queue->elements = temp;
        queue->current = 0;
    }

    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param queue Queue structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, QUEUE_DATA_TYPE (*copy_element)(QUEUE_DATA_TYPE)) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    if (!queue.size) return (queue_s) { 0 };

    const size_t mod_size = queue.size % REALLOC_QUEUE_CHUNK;
    const size_t copy_size = mod_size ? queue.size - (mod_size) + REALLOC_QUEUE_CHUNK : queue.size;

    const queue_s copy = {
        .size = queue.size, .current = queue.current,
        .elements = malloc(sizeof(QUEUE_DATA_TYPE) * copy_size),
    };
    assert(copy.elements && "[ERROR] Memory allocation failed.");

    if (copy_element) {
        for (size_t s = queue.current; s < queue.current + queue.size; s++) {
            copy.elements[s] = copy_element(queue.elements[s]);
        }
    } else {
        memcpy(&(copy.elements[queue.current]), &(queue.elements[queue.current]), sizeof(QUEUE_DATA_TYPE) * queue.size);
    }

    return copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    return queue.size == 0;
}

/// @brief Sorts queue elements using a function specified by the user, if function parameter is NULL a bubble sort
/// implementation with 'memcmp' will be used.
/// @param queue Queue structure pointer.
/// @param sort_elements Function pointer to sorting algorithm or NULL, if bubble sort should be used.
static inline void sort_queue(queue_s const * queue, void (*sort_elements)(QUEUE_DATA_TYPE *, size_t)) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] 'queue' parameter is NULL");

    if (sort_elements) {
        sort_elements(&(queue->elements[queue->current]), queue->size);
    } else {
        for (size_t s = queue->current; queue->size && s < queue->current + queue->size - 1; ++s) {
            for (size_t i = queue->current; i < queue->current + queue->size - s - 1; ++i) {
                if (memcmp(&(queue->elements[i]), &(queue->elements[i + 1]), sizeof(QUEUE_DATA_TYPE)) > 0) {
                    QUEUE_DATA_TYPE temp = queue->elements[i];
                    queue->elements[i] = queue->elements[i + 1];
                    queue->elements[i + 1] = temp;
                }
            }
        }
    }
}

#elif QUEUE_MODE == FINITE_PRERPOCESSOR_QUEUE

#ifndef PREPROCESSOR_QUEUE_SIZE

#define PREPROCESSOR_QUEUE_SIZE (1 << 10)

#elif PREPROCESSOR_QUEUE_SIZE == 0

#error 'PREPROCESSOR_QUEUE_SIZE' cannot be zero

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
/// @param destroy_element function pointer to destroy (or free) elements in queue or NULL if queue element has
/// no allocated memory.
static inline void destroy_queue(queue_s * queue, void (*destroy_element)(QUEUE_DATA_TYPE *)) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] Queue pointer is NULL");

    if (destroy_element) {
        if (queue->size > PREPROCESSOR_QUEUE_SIZE - queue->current) { // queue circles to beginning of elements array
            for(size_t s = queue->current; s < PREPROCESSOR_QUEUE_SIZE; s++) {
                destroy_element(queue->elements + s);
            }
            for(size_t s = 0; s < (queue->size - (PREPROCESSOR_QUEUE_SIZE - queue->current)); s++) {
                destroy_element(queue->elements + s);
            }
        } else { // queue has all element to the right
            for(size_t s = queue->current; s < queue->current + queue->size; s++) {
                destroy_element(queue->elements + s);
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
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    return !((queue.size < PREPROCESSOR_QUEUE_SIZE) && (~queue.size));
}

/// @brief Gets element at the top of the queue without decrementing size (peeks the start of the queue).
/// @param queue Queue structure.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE peek_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue.size && "[ERROR] Can't peek empty queue");

    return queue.elements[queue.current];
}

/// @brief Sets the next end empty element in queue array to 'element' parameter (enqueues element to end).
/// @param queue Queue structure pointer.
/// @param element Element to push to top of queue array.
static inline void enqueue(queue_s * queue, QUEUE_DATA_TYPE element) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] Queue pointer is NULL");
    assert((queue->size < PREPROCESSOR_QUEUE_SIZE) && "[ERROR] Queue reached maximum size");
    assert((queue->size + 1) && "[ERROR] Queue's '.size' will overflow");
    assert(queue->elements && "[ERROR] '.elements' is NULL");

    queue->elements[(queue->current + queue->size) % PREPROCESSOR_QUEUE_SIZE] = element;
    queue->size++;
}

/// @brief Gets the start element in queue and decrements queue size (dequeues element).
/// @param queue Queue structure pointer.
/// @return The start element of the queue as defined by 'QUEUE_DATA_TYPE' macro.
static inline QUEUE_DATA_TYPE dequeue(queue_s * queue) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] 'queue' pointer is empty");
    assert(queue->size && "[ERROR] Can't pop empty queue");
    assert(queue->elements && "[ERROR] '.elements' is NULL");

    QUEUE_DATA_TYPE element = queue->elements[queue->current];
    queue->size--;
    queue->current = (queue->current + 1) % PREPROCESSOR_QUEUE_SIZE;
    return element;
}

/// @brief Copies the queue and all its elements into a new queue structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param queue Queue structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'QUEUE_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'queue' parameter.
static inline queue_s copy_queue(const queue_s queue, QUEUE_DATA_TYPE (*copy_element)(QUEUE_DATA_TYPE)) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    queue_s copy = { .size = queue.size, .current = queue.current };

    if (queue.size > PREPROCESSOR_QUEUE_SIZE - queue.current) { // queue circles to beginning of elements array
        const size_t right_size = PREPROCESSOR_QUEUE_SIZE - queue.current;
        const size_t left_size  = queue.size - right_size;

        if (copy_element) {
            for (size_t s = queue.current; s < right_size + queue.current; s++) {
                copy.elements[s] = copy_element(queue.elements[s]);
            }
            for (size_t s = 0; s < left_size; s++) {
                copy.elements[s] = copy_element(queue.elements[s]);
            }
        } else {
            memcpy(&(copy.elements[queue.current]), &(queue.elements[queue.current]), sizeof(QUEUE_DATA_TYPE) * right_size);
            memcpy(copy.elements, queue.elements, sizeof(QUEUE_DATA_TYPE) * left_size);
        }
    } else { // queue has all element to the right
        if (copy_element) {
            for (size_t s = queue.current; s < queue.size + queue.current; s++) {
                copy.elements[s] = copy_element(queue.elements[s]);
            }
        } else {
            memcpy(&(copy.elements[queue.current]), &(queue.elements[queue.current]), sizeof(QUEUE_DATA_TYPE) * queue.size);
        }
    }

    return copy;
}

/// @brief Checks if queue is empty.
/// @param queue Queue structure.
/// @return true if queue size is zero, false otherwise
static inline bool is_empty_queue(const queue_s queue) {
    assert(queue.size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");

    return queue.size == 0;
}

/// @brief Sorts queue elements using a function specified by the user, if function parameter is NULL a bubble sort
/// implementation with 'memcmp' will be used.
/// @param queue Queue structure pointer.
/// @param sort_elements Function pointer to sorting algorithm or NULL, if bubble sort should be used.
static inline void sort_queue(queue_s * queue, void (*sort_elements)(QUEUE_DATA_TYPE *, size_t)) {
    assert(queue->size < (~((size_t)(0)) / sizeof(QUEUE_DATA_TYPE)) && "[ERROR] Impossible queue size.");
    assert(queue && "[ERROR] 'queue' parameter is NULL");

    if (queue->size > PREPROCESSOR_QUEUE_SIZE - queue->current) { // queue circles to beginning of elements array
        QUEUE_DATA_TYPE elements_array[PREPROCESSOR_QUEUE_SIZE];

        const size_t copy_size = LIST_ARRAY_QUEUE_CHUNK - queue->current;
        memcpy(elements_array, &(queue->elements[queue->current]), sizeof(QUEUE_DATA_TYPE) * copy_size);
        memcpy(&(elements_array[copy_size]), queue->elements, queue->size - copy_size);

        if (sort_elements) {
            sort_elements(elements_array, queue->size);
        } else {
            for (size_t s = 0; queue->size && s < queue->size - 1; ++s) {
                for (size_t i = 0; i < queue->size - s - 1; ++i) {
                    if (memcmp(&(elements_array[i]), &(elements_array[i + 1]), sizeof(QUEUE_DATA_TYPE)) > 0) {
                        QUEUE_DATA_TYPE temp = elements_array[i];
                        elements_array[i] = elements_array[i + 1];
                        elements_array[i + 1] = temp;
                    }
                }
            }
        }

        memcpy(&(queue->elements[queue->current]), elements_array, sizeof(QUEUE_DATA_TYPE) * copy_size);
        memcpy(queue->elements, &(elements_array[copy_size]), queue->size - copy_size);
    } else {
        if (sort_elements) {
            sort_elements(queue->elements, queue->size);
        } else {
            for (size_t s = queue->current; queue->size && s < queue->current + queue->size - 1; ++s) {
                for (size_t i = queue->current; i < queue->current + queue->size - s - 1; ++i) {
                    if (memcmp(&(queue->elements[i]), &(queue->elements[i + 1]), sizeof(QUEUE_DATA_TYPE)) > 0) {
                        QUEUE_DATA_TYPE temp = queue->elements[i];
                        queue->elements[i] = queue->elements[i + 1];
                        queue->elements[i + 1] = temp;
                    }
                }
            }
        }
    }
}

#endif

#endif //QUEUE_H
