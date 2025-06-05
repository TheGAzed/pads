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

// Deque data type to specify what datatype to deque.
// DEFAULT: void *
#ifndef DEQUE_DATA_TYPE

#define DEQUE_DATA_TYPE void*

#endif

#ifndef DEQUE_ASSERT

#include <assert.h>  // imports assert for debugging
#define DEQUE_ASSERT assert

#endif

/// Function pointer that creates a deep element copy.
typedef DEQUE_DATA_TYPE (*copy_deque_fn)    (const DEQUE_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_deque_fn) (DEQUE_DATA_TYPE * element);
/// Function pointer that changes an element pointer using void pointer arguments if needed.
typedef bool            (*operate_deque_fn) (DEQUE_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void            (*manage_deque_fn)  (DEQUE_DATA_TYPE * array, const size_t size, void * args);

#ifndef DEQUE_SIZE

#define DEQUE_SIZE (1 << 5)

#elif DEQUE_SIZE <= 0

#error 'DEQUE_SIZE' cannot be less than or equal to zero

#endif

typedef struct deque {
    DEQUE_DATA_TYPE elements[DEQUE_SIZE];
    size_t current, size;
} deque_s;

/// @brief Creates an empty deque.
/// @return Empty deque.
static inline deque_s create_deque(void) {
    return (deque_s) { .current = DEQUE_SIZE >> 1, .size = 0, }; // return empty deque with current set to middle
}

/// @brief Destroys deque with all its elements.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque needs to be created again after destroying it.
static inline void destroy_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    // calculate size of elements to the right of current index
    const size_t right_size = (deque->current + deque->size) > DEQUE_SIZE ? DEQUE_SIZE - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size; ++i) { // for each element from current to right size destroy it
        destroy(deque->elements + i);
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) { // for each element from 0 to left size destroy it
        destroy(deque->elements + i);
    }

    deque->size = deque->current = 0;
}

/// @brief Clears deque and all elements in it.
/// @param deque Deque structure to destroy.
/// @param destroy Function pointer to destroy each element in deque.
/// @note Deque needs to be created again after destroying it.
static inline void clear_deque(deque_s * deque, const destroy_deque_fn destroy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    // calculate size of elements to the right of current index
    const size_t right_size = (deque->current + deque->size) > DEQUE_SIZE ? DEQUE_SIZE - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size; ++i) { // for each element from current to right size destroy it
        destroy(deque->elements + i);
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) { // for each element from 0 to left size destroy it
        destroy(deque->elements + i);
    }

    deque->size = deque->current = 0;
}

/// @brief Copies the deque and all its elements into a new structure.
/// @param deque Deque structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in deque.
/// @return A copy of the specified 'deque' parameter.
static inline deque_s copy_deque(const deque_s * deque, const copy_deque_fn copy) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    deque_s replika = { .current = deque->current, .size = deque->size, };

    const size_t right_size = (deque->current + deque->size) > DEQUE_SIZE ? DEQUE_SIZE - deque->current : deque->size;
    for (size_t i = deque->current; i < right_size + deque->current; ++i) { // for each element from current to right size destroy it
        replika.elements[i] = copy(deque->elements[i]);
    }
    for (size_t i = 0; i < deque->size - right_size; ++i) { // for each element from 0 to left size destroy it
        replika.elements[i] = copy(deque->elements[i]);
    }

    return replika;
}

/// Checks if deque is empty.
/// @param deque Deque structure to check.
/// @return true if deque is empty, false otherwise.
static inline bool is_empty_deque(const deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    return deque->size == 0;
}

/// Checks if deque is full.
/// @param deque Deque structure to check.
/// @return true if deque is full, false otherwise.
static inline bool is_full_deque(const deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    return (deque->size == DEQUE_SIZE);
}

/// @brief Enqueues specified element to deque's front.
/// @param deque Deque data structure to enqueue element infront.
/// @param element Element to enqueue infront.
static inline void enqueue_front(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size < DEQUE_SIZE && "[ERROR] Deque is full.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    // if current underflows then circle it to max
    if (!(deque->current)) {
        deque->current = DEQUE_SIZE;
    }
    deque->current--;
    deque->size++;
    memcpy(deque->elements + deque->current, &element, sizeof(DEQUE_DATA_TYPE));
}

/// @brief Enqueues specified element to deque's back.
/// @param deque Deque data structure to enqueue element to back.
/// @param element lement to enqueue to back.
static inline void enqueue_rear(deque_s * deque, const DEQUE_DATA_TYPE element) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size < DEQUE_SIZE && "[ERROR] Deque is full.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t next_index = (deque->current + deque->size) % DEQUE_SIZE;
    deque->size++;
    memcpy(deque->elements + next_index, &element, sizeof(DEQUE_DATA_TYPE));
}

/// @brief Peeks element at front of deque.
/// @param deque Deque data structure to peek from front.
/// @return Peeked element at front of deque.
static inline DEQUE_DATA_TYPE peek_front(const deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    return deque->elements[deque->current];
}

/// @brief Peeks element at back of deque->
/// @param deque Deque data structure to peek from back.
/// @return Peeked element at back of deque->
static inline DEQUE_DATA_TYPE peek_rear(const deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t current_index = (deque->current + deque->size - 1) % DEQUE_SIZE;
    return deque->elements[current_index];
}

/// Dequeues element at front of deque.
/// @param deque Deque data structure to dequeue from front.
/// @return Dequeued element at front of deque.
static inline DEQUE_DATA_TYPE dequeue_front(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    DEQUE_DATA_TYPE removed = deque->elements[deque->current++];
    deque->size--;

    if (deque->current == DEQUE_SIZE) {
        deque->current = 0;
    }

    return removed;
}

/// Dequeues element at back of deque.
/// @param deque Deque data structure to dequeue from back.
/// @return Dequeued element at back of deque.
static inline DEQUE_DATA_TYPE dequeue_rear(deque_s * deque) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(deque->size && "[ERROR] Deque can't be empty.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t current_index = (deque->current + deque->size - 1) % DEQUE_SIZE;
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
static inline void foreach_front_deque(deque_s * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (deque->current + deque->size) > DEQUE_SIZE ? DEQUE_SIZE - deque->current : deque->size;
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
static inline void foreach_rear_deque(deque_s * deque, const operate_deque_fn operate, void * args) {
    DEQUE_ASSERT(deque && "[ERROR] 'deque' parameter is NULL.");
    DEQUE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    const size_t right_size = (deque->current + deque->size) > DEQUE_SIZE ? DEQUE_SIZE - deque->current : deque->size;
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

    DEQUE_ASSERT(deque->size <= DEQUE_SIZE && "[ERROR] Deque's size can't exceed its maximum size.");
    DEQUE_ASSERT(deque->current < DEQUE_SIZE && "[ERROR] Deque's current index must be less than maximum size.");

    DEQUE_DATA_TYPE elements_array[DEQUE_SIZE];

    const size_t right_size = (deque->current + deque->size) > DEQUE_SIZE ? DEQUE_SIZE - deque->current : deque->size;

    memcpy(elements_array, deque->elements + deque->current, right_size * sizeof(DEQUE_DATA_TYPE));
    memcpy(elements_array + right_size, deque->elements, (deque->size - right_size) * sizeof(DEQUE_DATA_TYPE));

    manage(elements_array, deque->size, args);

    memcpy(deque->elements, elements_array, deque->size * sizeof(DEQUE_DATA_TYPE));
    deque->current = 0;
}

#else

#error Cannot include multiple headers in same unit.

#endif //DEQUE_H
