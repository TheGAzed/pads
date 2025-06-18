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
typedef BINARY_HEAP_DATA_TYPE (*copy_binary_heap_fn)    (const BINARY_HEAP_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void                  (*destroy_binary_heap_fn) (BINARY_HEAP_DATA_TYPE * element);
/// 'less than', else a positive number if 'more than'.
typedef int                   (*compare_binary_heap_fn) (const BINARY_HEAP_DATA_TYPE one, const BINARY_HEAP_DATA_TYPE two);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns true if operation should continue.
typedef bool                  (*operate_binary_heap_fn) (BINARY_HEAP_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                  (*manage_binary_heap_fn)  (BINARY_HEAP_DATA_TYPE * array, const size_t size, void * args);

#ifndef BINARY_HEAP_SIZE

#define BINARY_HEAP_SIZE (1 << 10)

#elif BINARY_HEAP_SIZE <= 0

#error Size cannot be zero.

#endif

typedef struct binary_heap {
    BINARY_HEAP_DATA_TYPE elements[BINARY_HEAP_SIZE]; // elements array
    compare_binary_heap_fn compare; // compare function to push, pop and heapify heap
    size_t size; // size of heap
} binary_heap_s;

/// Creates a binary heap data structure.
/// @param compare Function pointer to compare elements for heap.
/// @return New binary heap.
static inline binary_heap_s create_binary_heap(const compare_binary_heap_fn compare) {
    BINARY_HEAP_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");

    return (binary_heap_s) { .size = 0, .compare = compare };
}

/// Destroys the heap and all its elements.
/// @param heap Binary heap data structure.
/// @param destroy Function pointer to destroy each element in heap.
static inline void destroy_binary_heap(binary_heap_s * heap, const destroy_binary_heap_fn destroy) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    for (BINARY_HEAP_DATA_TYPE * e = heap->elements; e < heap->elements + heap->size; e++) {
        destroy(e);
    }

    heap->size = 0;
    heap->compare = NULL;
}

/// Clears the heap and all its elements.
/// @param heap Binary heap data structure.
/// @param destroy Function pointer to destroy each element in heap.
static inline void clear_binary_heap(binary_heap_s * heap, const destroy_binary_heap_fn destroy) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    for (BINARY_HEAP_DATA_TYPE * e = heap->elements; e < heap->elements + heap->size; e++) {
        destroy(e);
    }

    heap->size = 0;
}

/// Checks if heap is empty.
/// @param heap Binary heap data structure.
/// @return 'true' if heap is empty, 'false' otherwise.
static inline bool is_empty_binary_heap(const binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return !(heap->size);
}

/// Checks if heap is full.
/// @param heap Binary heap data structure.
/// @return 'true' if heap is full, 'false' otherwise.
static inline bool is_full_binary_heap(const binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return (heap->size == BINARY_HEAP_SIZE);
}

/// Creates a copy of the specified heap.
/// @param heap Binary heap data structure.
/// @param copy Function pointer to create a deep or shallow copy of each element in heap.
/// @return Copy of specified heap.
static inline binary_heap_s copy_binary_heap(const binary_heap_s * heap, const copy_binary_heap_fn copy) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    binary_heap_s replica = { .compare = heap->compare, .size = 0, };
    for (replica.size = 0; replica.size < heap->size; replica.size++) {
        replica.elements[replica.size] = copy(heap->elements[replica.size]);
    }

    return replica;
}

/// Iterates over each element in heap in in array index order.
/// @param heap Binary heap data structure.
/// @param operate Function pointer to operate on each element in heap using generic argumenst.
/// @param args Generic void pointer arguments for operate function pointer.
static inline void foreach_binary_heap(binary_heap_s * heap, const operate_binary_heap_fn operate, void * args) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // for each element in heap call operate function pointer on it until each element was operated successfully
    for (BINARY_HEAP_DATA_TYPE * e = heap->elements; (e < heap->elements + heap->size) && operate(e, args); e++) {}
}

/// Maps heap element into array to manage.
/// @param heap Binary heap data structure.
/// @param manage Function pointer to manage array of heap elements using heap's size and generic arguments.
/// @param args Generic void pointer arguments for manage function pointer.
static inline void map_binary_heap(binary_heap_s * heap, const manage_binary_heap_fn manage, void * args) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    manage(heap->elements, heap->size, args);
}

/// Pushes element onto heap.
/// @param heap Binary heap data structure.
/// @param element Element to push into heap.
static inline void push_binary_heap(binary_heap_s * heap, const BINARY_HEAP_DATA_TYPE element) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(heap->size != BINARY_HEAP_SIZE && "[ERROR] Can't push to full heap.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // push element to the top of the elements array
    memcpy(heap->elements + heap->size, &element, sizeof(BINARY_HEAP_DATA_TYPE));

    // while current top child index is not zero and current element is greater than its parent
    for (size_t child = heap->size, parent = (child - 1) / 2; child && heap->compare(heap->elements[child], heap->elements[parent]) < 0;) {
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

/// Pops and returns root element from heap.
/// @param heap Binary heap data structure.
/// @return Root element in heap as specified by its compare function.
static inline BINARY_HEAP_DATA_TYPE pop_binary_heap(binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(heap->size && "[ERROR] Can't pop from empty heap.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
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

/// Returns root element in heap without removing it.
/// @param heap Binary heap data structure.
/// @return Root element in heap as specified by its compare function.
static inline BINARY_HEAP_DATA_TYPE peep_binary_heap(const binary_heap_s * heap) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(heap->size && "[ERROR] Can't peep from empty heap.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return heap->elements[0];
}

/// Replace the element at elements array index in heap while maintaining binary heap property.
/// @param heap Binary heap data structure.
/// @param index Index of element to replace.
/// @param element Element to replace and put at index.
/// @return replaced element.
static inline BINARY_HEAP_DATA_TYPE replace_binary_heap(binary_heap_s * heap, const size_t index, const BINARY_HEAP_DATA_TYPE element) {
    BINARY_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    BINARY_HEAP_ASSERT(heap->size && "[ERROR] Can't change empty heap.");
    BINARY_HEAP_ASSERT(index < heap->size && "[ERROR] Index out of heap size bounds.");

    BINARY_HEAP_ASSERT(heap->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(heap->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    const BINARY_HEAP_DATA_TYPE replaced = element;
    memcpy(heap->elements + index, &element, sizeof(BINARY_HEAP_DATA_TYPE));

    if (heap->compare(replaced, element) > 0) { // if new element is decreased perform down-heapify
        // while current top child index is not zero and current element is greater than its parent
        for (size_t child = index, parent = (child - 1) / 2; child && heap->compare(heap->elements[child], heap->elements[parent]) < 0;) {
            // swap current child element with parent
            BINARY_HEAP_DATA_TYPE temporary = heap->elements[child];
            heap->elements[child] = heap->elements[parent];
            heap->elements[parent] = temporary;

            // change current child to parent and parent to grand-parent
            child = parent;
            parent = (child - 1) / 2;
        }
    } else { // else the element is increased and up-heapify is performed
        for (size_t parent = index, child = (2 * parent) + 1; child < heap->size; parent = child, child = (2 * parent) + 1) {
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
    }

    return replaced;
}

/// Melds the source heap into the destination while keeping heap property.
/// @param destination Destination binary heap data structure.
/// @param source Source binary heap data structure.
static inline void meld_binary_heap(binary_heap_s * restrict destination, binary_heap_s * restrict source) {
    BINARY_HEAP_ASSERT(destination && "[ERROR] 'destination' parameter is NULL.");
    BINARY_HEAP_ASSERT(source && "[ERROR] 'source' parameter is NULL.");
    BINARY_HEAP_ASSERT(destination != source && "[ERROR] Heaps can't be the same.");
    BINARY_HEAP_ASSERT(destination->size + source->size <= BINARY_HEAP_SIZE && "[ERROR] Merge will exceed maximum size.");
    BINARY_HEAP_ASSERT(destination->compare == source->compare && "[ERROR] Compare functions must be the same.");

    BINARY_HEAP_ASSERT(destination->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(destination->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    BINARY_HEAP_ASSERT(source->compare && "[ERROR] Invalid compare function pointer.");
    BINARY_HEAP_ASSERT(source->size <= BINARY_HEAP_SIZE && "[ERROR] Invalid heap size.");

    memcpy(destination->elements + destination->size, source->elements, sizeof(BINARY_HEAP_DATA_TYPE) * source->size);
    destination->size += source->size;
    source->size = 0;

    const size_t start_index = (destination->size / 2) - 1;
    for (size_t i = 0; i <= start_index; ++i) {
        const size_t reverse_index = start_index - i;
        for (size_t parent = reverse_index, child = (2 * parent) + 1; child < destination->size; parent = child, child = (2 * parent) + 1) {
            // if right child is a valid index and it is smaller than left child change left child to right one
            if ((child + 1) < destination->size && destination->compare(destination->elements[child], destination->elements[child + 1]) > 0) {
                child++;
            }
            // if child is greater, then parent is properly set and thus break from loop
            if (destination->compare(destination->elements[child], destination->elements[parent]) > 0) {
                break;
            }

            // swap current parent element with greatest child
            BINARY_HEAP_DATA_TYPE temporary = destination->elements[child];
            destination->elements[child] = destination->elements[parent];
            destination->elements[parent] = temporary;
        }
    }
}

#else

#error Cannot include multiple headers in same unit.

#endif // BINARY_HEAP_H
