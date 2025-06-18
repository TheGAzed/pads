#ifndef SORT_HEAP_H
#define SORT_HEAP_H

#include <stddef.h>  // imports size_t
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy

/*
    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    sort, for any purpose, commercial or non-commercial, and by any
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

#ifndef SORT_HEAP_DATA_TYPE

// redefine using #define SORT_HEAP_DATA_TYPE [type]
#define SORT_HEAP_DATA_TYPE void*

#endif

#ifndef SORT_HEAP_ASSERT

#include <assert.h>  // imports assert for debugging

// redefine using #define SORT_HEAP_DATA_TYPE [assert]
#define SORT_HEAP_ASSERT assert

#endif

/// Function pointer that creates a deep element copy.
typedef SORT_HEAP_DATA_TYPE (*copy_sort_heap_fn)    (const SORT_HEAP_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void                (*destroy_sort_heap_fn) (SORT_HEAP_DATA_TYPE * element);
/// 'less than', else a positive number if 'more than'.
typedef int                 (*compare_sort_heap_fn) (const SORT_HEAP_DATA_TYPE one, const SORT_HEAP_DATA_TYPE two);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns true if operation should continue.
typedef bool                (*operate_sort_heap_fn) (SORT_HEAP_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of elements based on generic arguments.
typedef void                (*manage_sort_heap_fn)  (SORT_HEAP_DATA_TYPE * array, const size_t size, void * args);

#ifndef SORT_HEAP_SIZE

#define SORT_HEAP_SIZE (1 << 10)

#elif SORT_HEAP_SIZE <= 0

#error Size cannot be zero.

#endif

typedef struct sort_heap {
    manage_sort_heap_fn sort; // sorts the elements array when needed
    void * args; // compare function pointer parameters for sort, if needed
    size_t size, current; // size and current first element index
    SORT_HEAP_DATA_TYPE elements[SORT_HEAP_SIZE]; // elements array
    bool valid;
} sort_heap_s;

/// Creates a sort heap data structure.
/// @param sort Function pointer to sort elements for heap.
/// @param args Generic void pointer arguments for sort function.
/// @return New sort heap.
static inline sort_heap_s create_sort_heap(const manage_sort_heap_fn sort, void * args) {
    SORT_HEAP_ASSERT(args && "[ERROR] 'sort' parameter is NULL.");

    return (sort_heap_s) { .sort = sort, .args = args, .current = 0, .size = 0, .valid = true, };
}

/// Destroys the heap and all its elements.
/// @param heap Sort heap data structure.
/// @param destroy Function pointer to destroy each element in heap.
static inline void destroy_sort_heap(sort_heap_s * heap, const destroy_sort_heap_fn destroy) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // for each element in heap array destroy it, and increment it until last is reached
    for (SORT_HEAP_DATA_TYPE * e = heap->elements + heap->current; e < heap->elements + (heap->size + heap->current); e++) {
        destroy(e);
    }

    heap->args = heap->sort = NULL;
    heap->current = heap->size = 0;
    heap->valid = false;
}

/// Clears the heap and all its elements.
/// @param heap Sort heap data structure.
/// @param destroy Function pointer to destroy each element in heap.
static inline void clear_sort_heap(sort_heap_s * heap, const destroy_sort_heap_fn destroy) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // for each element in heap array destroy it, and increment it until last is reached
    for (SORT_HEAP_DATA_TYPE * e = heap->elements + heap->current; e < heap->elements + (heap->size + heap->current); e++) {
        destroy(e);
    }
}

/// Checks if heap is empty.
/// @param heap Sort heap data structure.
/// @return 'true' if heap is empty, 'false' otherwise.
static inline bool is_empty_sort_heap(const sort_heap_s * heap) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return !(heap->size);
}

/// Checks if heap is full.
/// @param heap Sort heap data structure.
/// @return 'true' if heap is full, 'false' otherwise.
static inline bool is_full_sort_heap(const sort_heap_s * heap) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    return (heap->size == SORT_HEAP_SIZE);
}

/// Creates a copy of the specified heap.
/// @param heap Sort heap data structure.
/// @param copy Function pointer to create a deep or shallow copy of each element in heap.
/// @return Copy of specified heap.
static inline sort_heap_s copy_sort_heap(const sort_heap_s * heap, const copy_sort_heap_fn copy) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    sort_heap_s replica = { .args = heap->args, .sort = heap->sort, .current = 0, .size = 0, .valid = heap->valid};

    // copy elements from heap into replica, but starting from replica's zeroth element in array
    for (replica.size = 0; replica.size < heap->size; replica.size++) {
        replica.elements[replica.size] = copy(heap->elements[heap->current + replica.size]);
    }

    return replica;
}

/// Iterates over each element in heap in in array index order.
/// @param heap Sort heap data structure.
/// @param operate Function pointer to operate on each element in heap using generic argumenst.
/// @param args Generic void pointer arguments for operate function pointer.
static inline void foreach_sort_heap(sort_heap_s * heap, const operate_sort_heap_fn operate, void * args) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // for each element in heap array destroy it, and increment it until last is reached
    for (SORT_HEAP_DATA_TYPE * e = heap->elements + heap->current; e < heap->elements + (heap->size + heap->current) && operate(e, args); e++) {}
}

/// Maps heap element into array to manage.
/// @param heap Sort heap data structure.
/// @param manage Function pointer to manage array of heap elements using heap's size and generic arguments.
/// @param args Generic void pointer arguments for manage function pointer.
static inline void map_sort_heap(sort_heap_s * heap, const manage_sort_heap_fn manage, void * args) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    manage(heap->elements + heap->current, heap->size, args);
}

/// Pushes element onto heap.
/// @param heap Sort heap data structure.
/// @param element Element to push into heap.
static inline void push_sort_heap(sort_heap_s * heap, const SORT_HEAP_DATA_TYPE element) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(heap->size != SORT_HEAP_SIZE && "[ERROR] Can't push to full heap.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    SORT_HEAP_DATA_TYPE * current_element = heap->current ? heap->elements + (--(heap->current)) : heap->elements + heap->size;
    memcpy(current_element, &element, sizeof(SORT_HEAP_DATA_TYPE));

    heap->valid = false; // invalidate heap since new element wasn't pushed in heap's sort order
    heap->size++;
}

/// Pops and returns root element from heap.
/// @param heap Sort heap data structure.
/// @return Root element in heap as specified by its compare function.
static inline SORT_HEAP_DATA_TYPE pop_sort_heap(sort_heap_s * heap) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(heap->size && "[ERROR] Can't pop from empty heap.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    if (!heap->valid) { // if heap is not sorted then sort it
        heap->sort(heap->elements + heap->current, heap->size, heap->args);
    }

    heap->valid = true; // validate that the heap is sorted
    heap->size--;
    return heap->elements[heap->current++]; // return removed head element by incrementing current after returning it
}

/// Returns root element in heap without removing it.
/// @param heap Sort heap data structure.
/// @return Root element in heap as specified by its compare function.
static inline SORT_HEAP_DATA_TYPE peep_sort_heap(sort_heap_s * heap) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(heap->size && "[ERROR] Can't pop from empty heap.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    if (!heap->valid) { // if heap is not sorted then sort it
        heap->sort(heap->elements + heap->current, heap->size, heap->args);
    }

    heap->valid = true; // validate that the heap is sorted and return head element without removing it
    return heap->elements[heap->current];
}

/// Replace the element at elements array index in heap while maintaining sort heap property.
/// @param heap Sort heap data structure.
/// @param index Index of element to replace.
/// @param element Element to replace and put at index.
/// @return replaced element.
static inline SORT_HEAP_DATA_TYPE replace_sort_heap(sort_heap_s * heap, const size_t index, const SORT_HEAP_DATA_TYPE element) {
    SORT_HEAP_ASSERT(heap && "[ERROR] 'heap' parameter is NULL.");
    SORT_HEAP_ASSERT(heap->size && "[ERROR] Can't pop from empty heap.");
    SORT_HEAP_ASSERT(index < heap->size && "[ERROR] Index out of heap size bounds.");

    SORT_HEAP_ASSERT(heap->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(heap->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    if (!heap->valid) { // if heap is not sorted then sort it
        heap->sort(heap->elements + heap->current, heap->size, heap->args);
    }

    // temporar save replaced/removed head element to not loose it
    SORT_HEAP_DATA_TYPE removed = heap->elements[heap->current + index];

    // replace with new element
    memcpy(heap->elements + heap->current + index, &element, sizeof(SORT_HEAP_DATA_TYPE));
    heap->valid = false; // invalidate heap since it may not be sorted properly after replacing element in it

    return removed;
}

/// Melds the source heap into the destination while keeping heap property.
/// @param destination Destination sort heap data structure.
/// @param source Source sort heap data structure.
static inline void meld_sort_heap(sort_heap_s * restrict destination, sort_heap_s * restrict source) {
    SORT_HEAP_ASSERT(destination && "[ERROR] 'destination' parameter is NULL.");
    SORT_HEAP_ASSERT(source && "[ERROR] 'source' parameter is NULL.");
    SORT_HEAP_ASSERT(destination != source && "[ERROR] Heaps can't be the same.");
    SORT_HEAP_ASSERT(destination->size + source->size <= SORT_HEAP_SIZE && "[ERROR] Merge will exceed maximum size.");
    SORT_HEAP_ASSERT(destination->args == source->args && "[ERROR] Compare functions must be the same.");
    SORT_HEAP_ASSERT(destination->sort == source->sort && "[ERROR] Compare functions must be the same.");

    SORT_HEAP_ASSERT(destination->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(destination->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    SORT_HEAP_ASSERT(source->sort && "[ERROR] Invalid sort function pointer.");
    SORT_HEAP_ASSERT(source->size <= SORT_HEAP_SIZE && "[ERROR] Invalid heap size.");

    // first add elements from source to destionation to the front until source isn't empty or destination's current index isn't 0
    for (; destination->current && source->size; source->size--, destination->size++) {
        destination->current--;
        destination->elements[destination->current] = source->elements[source->current++];
    }

    // then append the remaining source elements into destination if source isn't empty
    memcpy(destination->elements + destination->current + destination->size, source->elements + source->current, source->size * sizeof(SORT_HEAP_DATA_TYPE));
    destination->size += source->size;
    destination->valid = false; // invalidate destination since elements were added orderless

    // clear source
    source->size = source->current = 0;
    source->valid = true;
}

#endif // SORT_HEAP_H
