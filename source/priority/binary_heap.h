#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

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

#ifndef BINARY_HEAP_DATA_TYPE

// redefine using #define BINARY_HEAP_DATA_TYPE [type]
#define BINARY_HEAP_DATA_TYPE void*

#endif


#ifndef BINARY_HEAP_ASSERT

#include <assert.h>  // imports assert for debugging

// redefine using #define BINARY_HEAP_DATA_TYPE [assert]
#define BINARY_HEAP_ASSERT assert

#endif

/// Function pointer that creates a deep element copy.
typedef BINARY_HEAP_DATA_TYPE (*copy_binary_heap_fn)    (const BINARY_HEAP_DATA_TYPE);
/// Function pointer that destroys a deep element.
typedef void                  (*destroy_binary_heap_fn) (BINARY_HEAP_DATA_TYPE *);
/// 'less than', else a positive number if 'more than'.
typedef int                   (*compare_binary_heap_fn) (const BINARY_HEAP_DATA_TYPE, const BINARY_HEAP_DATA_TYPE);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns true if operation should continue.
typedef bool                  (*operate_binary_heap_fn) (BINARY_HEAP_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                  (*manage_binary_heap_fn)  (BINARY_HEAP_DATA_TYPE *, const size_t, void *);

#ifndef BINARY_HEAP_SIZE

#define BINARY_HEAP_SIZE (1 << 10)

#elif BINARY_HEAP_SIZE == 0

#error Size cannot be zero.

#endif

typedef struct binary_heap {
    BINARY_HEAP_DATA_TYPE elements[BINARY_HEAP_SIZE];
    compare_binary_heap_fn compare;
    size_t size;
} binary_heap_s;

static inline binary_heap_s create_binary_heap(const compare_binary_heap_fn compare) {
    return (binary_heap_s) { .size = 0, .compare = compare };
}

static inline void destroy_binary_heap(binary_heap_s * heap, const destroy_binary_heap_fn destroy) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    for (size_t i = 0; i < heap->size; ++i) {
        destroy(heap->elements + i);
    }
}

static inline bool is_empty_binary_heap(const binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return !(heap->size);
}

static inline bool is_full_binary_heap(const binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return (heap->size == BINARY_HEAP_SIZE);
}

static inline binary_heap_s copy_binary_heap(const binary_heap_s * heap, const copy_binary_heap_fn copy) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    binary_heap_s replica = { .compare = heap->compare, .size = 0, };
    for (replica.size = 0; replica.size < heap->size; replica.size++) {
        replica.elements[replica.size] = copy(heap->elements[replica.size]);
    }

    return replica;
}

static inline void foreach_binary_heap(binary_heap_s * heap, const operate_binary_heap_fn operate, void * args) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    for (size_t i = 0; i < heap->size && operate(heap->elements + i, args); i++) {}
}

static inline void map_binary_heap(binary_heap_s * heap, const manage_binary_heap_fn manage, void * args) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    manage(heap->elements, heap->size, args);
}

static inline void push_binary_heap(binary_heap_s * heap, const BINARY_HEAP_DATA_TYPE element) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(heap->size != BINARY_HEAP_SIZE && "[ERROR] Can't push to full heap.");

    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // push element to the top of the elements array
    memcpy(heap->elements + heap->size, &element, sizeof(BINARY_HEAP_DATA_TYPE));

    // while current top child index is not zero and current element is greater than its parent
    for (size_t child = heap->size, parent = (child - 1) / 2; child && heap->compare(heap->elements[child], heap->elements[parent]) > 0;) {
        // swap current child element with parent
        BINARY_HEAP_DATA_TYPE temporary = heap->elements[child];
        heap->elements[child] = heap->elements[parent];
        heap->elements[parent] = temporary;

        // change current child to parent and parent to grand-parent
        child = parent;
        parent = (child - 1) / 2;
    }
    heap->size++;
}

static inline BINARY_HEAP_DATA_TYPE pop_binary_heap(binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(heap->size && "[ERROR] Can't pop from empty heap.");

    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // save root element and put last element in its place
    BINARY_HEAP_DATA_TYPE removed = heap->elements[0];
    heap->size--;
    heap->elements[0] = heap->elements[heap->size];

    for (size_t parent = 0, child = (2 * parent) + 1; child < heap->size; parent = child, child = (2 * parent) + 1) {
        // if right child is a valid index and it is smaller than left child change left child to right one
        if ((child + 1) < heap->size && heap->compare(heap->elements[child], heap->elements[child + 1]) > 0) {
            child++;
        }
        // if child is greater, then parent is properly set and thus break from loop
        if (heap->compare(heap->elements[child], heap->elements[parent]) > 0) {
            break;
        }

        // swap current parent element with greatest child
        BINARY_HEAP_DATA_TYPE temporary = heap->elements[child];
        heap->elements[child] = heap->elements[parent];
        heap->elements[parent] = temporary;
    }

    return removed;
}

static inline BINARY_HEAP_DATA_TYPE peep_binary_heap(const binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(heap->size && "[ERROR] Can't peep from empty heap.");

    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return heap->elements[0];
}

#else

#error Cannot include multiple headers in same unit.

#endif // BINARY_HEAP_H
