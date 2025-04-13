#ifndef STACK_H
#define STACK_H

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

#define INFINITE_LIST_STACK_MODE       1
#define FINITE_ALLOCATED_STACK_MODE    2
#define INFINITE_REALLOC_STACK_MODE    3
#define FINITE_PRERPOCESSOR_STACK_MODE 4

//#define STACK_MODE INFINITE_LIST_STACK_MODE
//#define STACK_MODE FINITE_ALLOCATED_STACK_MODE
//#define STACK_MODE INFINITE_REALLOC_STACK_MODE
//#define STACK_MODE FINITE_PRERPOCESSOR_STACK_MODE
// Stack mode that can be set to 'INFINITE_LIST_STACK_MODE', 'FINITE_ALLOCATED_STACK_MODE', 'INFINITE_REALLOC_STACK_MODE' or
// 'FINITE_PRERPOCESSOR_STACK_MODE'.
// Default: 'INFINITE_LIST_STACK_MODE'
#ifndef STACK_MODE

#define STACK_MODE INFINITE_REALLOC_STACK_MODE

#endif

// Check to make sure a valid stack mode is selected.
#if (STACK_MODE != INFINITE_LIST_STACK_MODE)    && (STACK_MODE != FINITE_ALLOCATED_STACK_MODE)    && \
    (STACK_MODE != INFINITE_REALLOC_STACK_MODE) && (STACK_MODE != FINITE_PRERPOCESSOR_STACK_MODE)

#error Invalid type of stack mode.

#endif

// Stack data type to specify what datatype to stack.
// DEFAULT: void *
#ifndef STACK_DATA_TYPE

#define STACK_DATA_TYPE void*

#endif

#ifndef STACK_ASSERT

#include <assert.h>  // imports assert for debugging

#define STACK_ASSERT assert

#endif

#if !defined(STACK_REALLOC) && !defined(STACK_FREE)

#include <stdlib.h>

#ifndef STACK_REALLOC

#define STACK_REALLOC realloc

#endif

#ifndef STACK_FREE

#define STACK_FREE free

#endif

#elif !defined(STACK_REALLOC)

#error Stack reallocator macro is not defined!

#elif !defined(STACK_FREE)

#error Stack free macro is not defined!

#endif

/// Function pointer that creates a deep element copy.
typedef STACK_DATA_TYPE (*copy_stack_fn)    (const STACK_DATA_TYPE);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_stack_fn) (STACK_DATA_TYPE *);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns true if operation should continue.
typedef bool            (*operate_stack_fn) (STACK_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void            (*manage_stack_fn)  (STACK_DATA_TYPE *, const size_t, void *);

#if   STACK_MODE == INFINITE_LIST_STACK_MODE

/// @brief Stack list array size.
#ifndef LIST_ARRAY_STACK_CHUNK

#define LIST_ARRAY_STACK_CHUNK (1 << 5)

#elif LIST_ARRAY_STACK_CHUNK <= 0

#error 'LIST_ARRAY_STACK_CHUNK' cannot be less than or equal to zero.

#endif

/// @brief Linked list of arrays that appends new list element at the start after array is full.
struct stack_list_array {
    STACK_DATA_TYPE elements[LIST_ARRAY_STACK_CHUNK]; // array to store elements
    struct stack_list_array * next;                   // next linked list array
};

/// @brief Stack implementation that uses appended lists of arrays and pushes elements based on the size.
typedef struct stack {
    struct stack_list_array * head; // head list element with the top of the stack
    size_t size;                    // size of stack
} stack_s;

/// @brief Creates empty stack.
/// @return Empty stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { 0 }; // creates a list structure set to zero
}

/// @brief Destroys a stack.
/// @param stack Pointer to stack structure.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    const size_t modulo = stack->size % LIST_ARRAY_STACK_CHUNK;
    for (size_t destroy_size = modulo ? modulo : LIST_ARRAY_STACK_CHUNK; stack->head; destroy_size = LIST_ARRAY_STACK_CHUNK) {
        for (size_t i = 0; i < destroy_size; i++) { // destroys stack elements
            destroy(stack->head->elements + i); // calls destroy element function pointer
        }

        struct stack_list_array * temp = stack->head; // temporary pointer to not lose reference
        stack->head = stack->head->next; // go to next pointer
        STACK_FREE(temp); // free temporary
    }
    stack->size = 0; // only set size to zero since head will be NULL by while loop
}

/// @brief Checks if stack is full.
/// @param stack Stack structure to check.
/// @return true if is full, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    return !(~stack.size); // checks if stack's size will overflow
}

/// @brief Peeps the top element in stack.
/// @param stack Stack structure to peep.
/// @return Element of type 'STACK_DATA_TYPE' at the top of stack.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    STACK_ASSERT(stack.size && "[ERROR] Can't peek empty stack.");
    STACK_ASSERT(stack.head && "[ERROR] Stack head is NULL.");

    return stack.head->elements[(stack.size - 1) % LIST_ARRAY_STACK_CHUNK]; // returns top element at head elements array
}

/// @brief Pushes the specified element to top.
/// @param stack Stack structure to push to.
/// @param element Constant element of type 'STACK_DATA_TYPE' to push into stack.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT((~stack->size) && "[ERROR] Stack size will overflow.");

    const size_t next_index = stack->size % LIST_ARRAY_STACK_CHUNK; // index where the next element will be pushed
    if (next_index == 0) { // if head list array is full (is divisible) adds new list element to head
        struct stack_list_array * temp = STACK_REALLOC(NULL, sizeof(struct stack_list_array)); // create new node
        STACK_ASSERT(temp && "[ERROR] Memory allocation failed.");

        temp->next = stack->head; // make new node's next into stack's head
        stack->head = temp; // reset stack's head to new node
    }

    // pushes element to head's top
    memcpy(stack->head->elements + next_index, &element, sizeof(STACK_DATA_TYPE));
    stack->size++; // increments stack size
}

/// @brief Pops the top element in stack.
/// @param stack Stack structure pointer to pop.
/// @return Popped elements of type 'STACK_DATA_TYPE' from stack.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer parameter is NULL.");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack.");

    const size_t current_index = (--stack->size) % LIST_ARRAY_STACK_CHUNK; // decrementing size gets top element
    STACK_DATA_TYPE element = { 0 }; // get the top element
    memcpy(&element, stack->head->elements + current_index, sizeof(STACK_DATA_TYPE));
    // if head has one element in array (index at 0) pop will make it empty and head can be freed
    if (current_index == 0) { // check if head elements array is empty
        struct stack_list_array * temp = stack->head->next; // temporary pointer to not lose reference
        STACK_FREE(stack->head);
        stack->head = temp; // change head pointer to its next member
    }

    return element;
}

/// @bried Creates and returns a copy of a stack using copy element function.
/// @param stack Stack structure to copy.
/// @param copy Function pointer that returns a deep or shallow copy of an element.
/// @return New stack copy with copied elements.
static inline stack_s copy_stack(const stack_s stack, const copy_stack_fn copy) {
    STACK_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    stack_s replica =  { .head = NULL, .size = stack.size };

    struct stack_list_array const * current_stack = stack.head;
    struct stack_list_array ** current_copy = &(replica.head); // two pointer list to remove special head case
    const size_t modulo =  stack.size % LIST_ARRAY_STACK_CHUNK;
    size_t copy_size = modulo ? modulo : LIST_ARRAY_STACK_CHUNK;
    while (current_stack) { // while stack's current node is not NULL
        (*current_copy) = STACK_REALLOC(NULL, sizeof(struct stack_list_array)); // allocate new node to copy's current address
        STACK_ASSERT((*current_copy) && "[ERROR] Memory allocation failed.");
        (*current_copy)->next = NULL; // end copy's current node with NULL

        for (size_t i = 0; i < copy_size; i++) { // copy all elements from start to last element at note, at first iteration size may not be equal to chunk
            (*current_copy)->elements[i] = copy(current_stack->elements[i]);
        }
        copy_size = LIST_ARRAY_STACK_CHUNK; // after the first iteration make copy size equal to entire chunk

        current_stack = current_stack->next;
        current_copy = &((*current_copy)->next);
    }

    return replica;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure to check.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return !(stack.size);
}

/// @brief Clears all elements from the stack.
/// @param stack Stack structure pointer to clear.
/// @param destroy Function pointer to destroy an element in stack.
static inline void clear_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    const size_t modulo = stack->size % LIST_ARRAY_STACK_CHUNK;
    for (size_t destroy_size = modulo ? modulo : LIST_ARRAY_STACK_CHUNK; stack->head; destroy_size = LIST_ARRAY_STACK_CHUNK) {
        for (size_t i = 0; i < destroy_size; i++) { // destroys stack elements
            destroy(stack->head->elements + i); // calls destroy element function pointer
        }

        struct stack_list_array * temp = stack->head; // temporary pointer to not lose reference
        stack->head = stack->head->next; // go to next pointer
        STACK_FREE(temp); // free temporary
    }
    stack->size = 0; // only set size to zero since head will be NULL by while loop
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer to iterate.
/// @param operate Function pointer that takes an element pointer and 'args' as parameters and returns true if
/// foreach loop should continue after operation, false if break.
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s const * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    const size_t modulo = stack->size % LIST_ARRAY_STACK_CHUNK; // calculate elements count at start node
    size_t foreach_size = modulo ? modulo : LIST_ARRAY_STACK_CHUNK; // adjust start node size if modulo is zero
    for (struct stack_list_array * current = stack->head; current; current = current->next) { // for each node
        for (size_t i = 0; i < foreach_size; ++i) { // for each element in node
            if (!operate(current->elements + (foreach_size - i - 1), args)) { // operate on elements until main loop ends or it returns false
                return;
            }
        }
        foreach_size = LIST_ARRAY_STACK_CHUNK; // reset size to chunk after special start case was taken care of
    }
}

/// @brief For every function that manages every element as an array using args.
/// @param stack Stack structure pointer ot manage.
/// @param manage Function pointer that takes an array of stack elements, the number of elements and other arguments
/// in the form of arguments.
/// @param args Generic arguments for manage function pointer.
static inline void forevery_stack(stack_s const * stack, const manage_stack_fn manage, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    STACK_DATA_TYPE * elements = STACK_REALLOC(NULL, sizeof(STACK_DATA_TYPE) * stack->size); // allocate an array for 'manage' function as parameter
    STACK_ASSERT(elements && "[ERROR] Memory allocation failed.");

    const size_t modulo =  stack->size % LIST_ARRAY_STACK_CHUNK;
    const size_t first_chunk_size = modulo ? modulo : LIST_ARRAY_STACK_CHUNK; // calculate chunk at first node because it is not full

    size_t chunk_size = first_chunk_size; // set chunk size to first special chunk size
    size_t start_index = stack->size - first_chunk_size; // get start index from end to turn list based stack into an array one
    for (struct stack_list_array const * current = stack->head; current; current = current->next) {
        memcpy(elements + start_index, current->elements, chunk_size * sizeof(STACK_DATA_TYPE)); // copy elements in node into array
        chunk_size = LIST_ARRAY_STACK_CHUNK; // set new chunk size as special case does not apply to second until last nodes
        start_index -= LIST_ARRAY_STACK_CHUNK; // set new start index to the left based on stack modes chunk size
    }

    manage(elements, stack->size, args); // manage elements in array form

    chunk_size = first_chunk_size; // reset shunk size to first chunk size
    start_index = stack->size - first_chunk_size; // reset start index to begin from the right side again
    for (struct stack_list_array * current = stack->head; current; current = current->next) {
        memcpy(current->elements, elements + start_index, chunk_size * sizeof(STACK_DATA_TYPE));
        chunk_size = LIST_ARRAY_STACK_CHUNK;
        start_index -= LIST_ARRAY_STACK_CHUNK;
    }

    STACK_FREE(elements); // free elements array after copying element back into stack
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK_MODE

/// @brief Stack implementation that uses allocated memory array and pushes elements based on the current
/// and maximum size.
typedef struct stack {
    STACK_DATA_TYPE * elements; // pointer to allocated memory
    size_t max, size;           // current stack size and maximum size
} stack_s;

/// @brief Creates empty stack with '.size' set to zero, elements with 'max' allocated memory and '.max'
/// to parameter 'max'.
/// @param max Specifies maximum allocated size of stack structure.
/// @return Created stack structure.
static inline stack_s create_stack(const size_t max) {
    STACK_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const stack_s create = {
        .max = max, .elements = STACK_REALLOC(NULL, max * sizeof(STACK_DATA_TYPE)), .size = 0,
    };
    STACK_ASSERT(create.elements && "[ERROR] Memory allocation failed.");

    return create;
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer to destroy.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STACK_ASSERT(stack->max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack->elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack->size <= stack->max && "[ERROR] Deque's size can't exceed its maximum size.");

    for(size_t i = 0; i < stack->size; i++) {
        destroy(stack->elements + i);
    }

    STACK_FREE(stack->elements);
    *stack = (stack_s) { 0 };
}

/// @brief Checks if stack is full or if stack's .size will overflow.
/// @param stack Stack structure to check.
/// @return true if stack size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    STACK_ASSERT(stack.max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack.elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack.size <= stack.max && "[ERROR] Deque's size can't exceed its maximum size.");

    return (stack.size == stack.max);
}

/// @brief Gets element at the top of the stack without decrementing size (peeps the top of the stack).
/// @param stack Stack structure to peep.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    STACK_ASSERT(stack.size && "[ERROR] Can't peep empty stack.");

    STACK_ASSERT(stack.max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack.elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack.size <= stack.max && "[ERROR] Deque's size can't exceed its maximum size.");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer to push into.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(stack->size < stack->max && "[ERROR] Stack reached maximum size.");

    STACK_ASSERT(stack->max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack->elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack->size <= stack->max && "[ERROR] Deque's size can't exceed its maximum size.");

    memcpy(stack->elements + (stack->size++), &element, sizeof(STACK_DATA_TYPE));
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer to pop from.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' pointer is empty.");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack.");

    STACK_ASSERT(stack->max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack->elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack->size <= stack->max && "[ERROR] Deque's size can't exceed its maximum size.");

    return stack->elements[((stack->size)--) - 1];
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param stack Stack structure to copy.
/// @param copy Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, const copy_stack_fn copy) {
    STACK_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    STACK_ASSERT(stack.max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack.elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack.size <= stack.max && "[ERROR] Deque's size can't exceed its maximum size.");

    stack_s stack_copy = stack;
    stack_copy.elements = STACK_REALLOC(NULL, stack.max * sizeof(STACK_DATA_TYPE));
    STACK_ASSERT(stack_copy.elements && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < stack.size; i++) {
        stack_copy.elements[i] = copy(stack.elements[i]);
    }

    return stack_copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure check.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    STACK_ASSERT(stack.max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack.elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack.size <= stack.max && "[ERROR] Deque's size can't exceed its maximum size.");

    return (stack.size == 0);
}

/// @brief Clears all elements from the stack.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer to destroy an element in stack.
static inline void clear_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STACK_ASSERT(stack->max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack->elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack->size <= stack->max && "[ERROR] Deque's size can't exceed its maximum size.");

    for(size_t s = 0; s < stack->size; s++) {
        destroy(stack->elements + s);
    }

    stack->size = 0;
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer to iterate over.
/// @param operate Function pointer that takes an element pointer and 'args' as parameters and returns true if
/// loop should continue, false if break
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s const * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    STACK_ASSERT(stack->max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack->elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack->size <= stack->max && "[ERROR] Deque's size can't exceed its maximum size.");

    for (size_t i = 0; i < stack->size && operate(stack->elements + (stack->size - i - 1), args); ++i) {}
}

/// @brief For every function that manages every element as an array using args.
/// @param stack Stack structure pointer to manage elements.
/// @param manage Function pointer that takes an array of stack elements, the number of elements and other arguments
/// in the form of a 'args' void pointer.
/// @param args Generic arguments for manage function pointer.
static inline void forevery_stack(stack_s const * stack, const manage_stack_fn manage, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    STACK_ASSERT(stack->max && "[ERROR] Deque's maximum size can't be zero.");
    STACK_ASSERT(stack->elements && "[ERROR] Deque's elements array can't be NULL.");
    STACK_ASSERT(stack->size <= stack->max && "[ERROR] Deque's size can't exceed its maximum size.");

    manage(stack->elements, stack->size, args);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK_MODE

#if !defined(IS_REALLOC_CAPACITY_STACK) && !defined(EXPAND_REALLOC_CAPACITY_STACK)

#ifndef REALLOC_STACK_CHUNK

#define REALLOC_STACK_CHUNK (1 << 5)

#elif REALLOC_STACK_CHUNK <= 0

#error 'REALLOC_STACK_CHUNK' cannot be less than or equal to 0

#endif

/// @brief Checks if stack's 'size' has reached capacity.
#define IS_REALLOC_CAPACITY_STACK(size) (!(size % REALLOC_STACK_CHUNK))

/// @brief Calculates next stack's capacity based on 'size'.
#define EXPAND_REALLOC_CAPACITY_STACK(capacity) (capacity + REALLOC_STACK_CHUNK)

#elif !defined(IS_REALLOC_CAPACITY_STACK)

#error Stack capacity reached check is not defined.

#elif !defined(EXPAND_REALLOC_CAPACITY_STACK)

#error Stack capacity expanded size is not defined.

#endif

typedef struct stack {
    size_t size;
    STACK_DATA_TYPE * elements;
} stack_s;

/// @brief Creates empty stack with '.size' set to zero and '.elements' set to NULL.
/// @return Stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { .size = 0, .elements = NULL, };
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    for(size_t i = 0; i < stack->size; i++) {
        destroy(stack->elements + i);
    }

    STACK_FREE(stack->elements);

    *stack = (stack_s) { 0 }; // reset stack to zero
}

/// @brief Checks if stack's .size will overflow.
/// @param stack Stack structure.
/// @return true if stack size overflows after incrementing it, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    return !(~stack.size);
}

/// @brief Gets element at the top of the stack without decrementing size (peeks the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    STACK_ASSERT(stack.size && "[ERROR] Can't peek empty stack");
    STACK_ASSERT(stack.elements && "[ERROR] Stack's '.elements' is NULL.");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT((stack->size + 1) && "[ERROR] Stack size will overflow.");

    // first expand memory if necessary and then add element
    if (IS_REALLOC_CAPACITY_STACK(stack->size)) {
        stack->elements = STACK_REALLOC(stack->elements, (EXPAND_REALLOC_CAPACITY_STACK(stack->size)) * sizeof(STACK_DATA_TYPE));
        STACK_ASSERT(stack->elements && "[ERROR] Memory allocation failed");
    }
    memcpy(stack->elements + (stack->size++), &element, sizeof(STACK_DATA_TYPE));
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' pointer is empty.");
    STACK_ASSERT(stack->elements && "[ERROR] Can't pop from NULL array.");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack.");

    // first remove element and then shrink memory if necessary
    STACK_DATA_TYPE element = stack->elements[--(stack->size)];
    if (IS_REALLOC_CAPACITY_STACK(stack->size)) {
        stack->elements = STACK_REALLOC(stack->elements, stack->size * sizeof(STACK_DATA_TYPE));
        if (!stack->size) {
            STACK_FREE(stack->elements);
            stack->elements = NULL;
        }
    }

    return element;
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, const copy_stack_fn copy) {
    STACK_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    stack_s stack_copy = { 0 };

    for (; stack_copy.size < stack.size; stack_copy.size++) { // for loop until stack copy's size reaches stack's size
        if (IS_REALLOC_CAPACITY_STACK(stack_copy.size)) { // if size reached maximum chunk size, expand elements array
            stack_copy.elements = STACK_REALLOC(stack_copy.elements, (EXPAND_REALLOC_CAPACITY_STACK(stack_copy.size)) * sizeof(STACK_DATA_TYPE));
            STACK_ASSERT((stack_copy.elements) && "[ERROR] Memory allocation failed.");
        }

        stack_copy.elements[stack_copy.size] = copy(stack.elements[stack_copy.size]);
    }

    return stack_copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

/// @brief Clears all elements from the stack.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer to destroy an element in stack.
static inline void clear_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    for(size_t s = 0; s < stack->size; s++) {
        destroy(stack->elements + s);
    }
    STACK_FREE(stack->elements);

    *stack = (stack_s) { 0 }; // reset stack to zero
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer.
/// @param operate Function pointer that takes an element pointer and 'args' as parameters and returns true if
/// loop should continue after operation, false if break
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s const * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    for (size_t i = 0; i < stack->size && operate(stack->elements + (stack->size - i - 1), args); ++i) {}
}

/// @brief For every function that manages every element as an array using args.
/// @param stack Stack structure pointer.
/// @param manage Function pointer that takes an array of stack elements, the number of elements and other arguments
/// in the form of a 'args' void pointer.
/// @param args Generic arguments for manage function pointer.
static inline void forevery_stack(stack_s const * stack, const manage_stack_fn manage, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL");
    STACK_ASSERT(manage && "[ERROR] 'manage' parameter is NULL");

    manage(stack->elements, stack->size, args);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK_MODE

#ifndef PREPROCESSOR_STACK_SIZE

#define PREPROCESSOR_STACK_SIZE (1 << 5)

#elif PREPROCESSOR_STACK_SIZE == 0

#error 'PREPROCESSOR_STACK_SIZE' cannot be zero

#endif

typedef struct stack {
    STACK_DATA_TYPE elements[PREPROCESSOR_STACK_SIZE]; // elements array
    size_t size;                                       // size of stack
} stack_s;

/// @brief Creates empty stack with '.size' set to zero.
/// @return Stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { .size = 0, }; // only needs to initialize size == 0
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    for(size_t i = 0; i < stack->size; i++) {
        destroy(stack->elements + i);
    }

    stack->size = 0;
}

/// @brief Checks if stack is full or if stack's '.size' will overflow.
/// @param stack Stack structure.
/// @return true if stack size reached maximum or overflows after incrementing it, false otherwise.
static inline bool is_full_stack(const stack_s stack) {
    return stack.size == PREPROCESSOR_STACK_SIZE;
}

/// @brief Gets element at the top of the stack without decrementing size (peeks the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    STACK_ASSERT(stack.size && "[ERROR] Can't peek empty stack");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT((stack->size < PREPROCESSOR_STACK_SIZE) && "[ERROR] Stack reached maximum size.");
    STACK_ASSERT(~(stack->size) && "[ERROR] Stack size will overflow.");
    // treat size as next index, add element and increment size
    memcpy(stack->elements + (stack->size++), &element, sizeof(STACK_DATA_TYPE));
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' pointer is empty.");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack.");

    return stack->elements[--(stack->size)]; // treat decremented size as current index
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, const copy_stack_fn copy) {
    STACK_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    stack_s stack_copy = { .size = stack.size, };

    for (size_t i = 0; i < stack.size; i++) {
        stack_copy.elements[i] = copy(stack.elements[i]);
    }

    return stack_copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

/// @brief Clears all elements from the stack.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer to destroy an element in stack.
static inline void clear_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    for(size_t s = 0; s < stack->size; s++) {
        destroy(stack->elements + s);
    }

    stack->size = 0;
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer.
/// @param operate Function pointer that takes an element pointer and 'args' as parameters and returns true if
/// loop should continue after operation, false if break
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    for (size_t i = 0; i < stack->size && operate(stack->elements + (stack->size - i - 1), args); ++i) {}
}

/// @brief For every function that manages every element as an array using args.
/// @param stack Stack structure pointer.
/// @param manage Function pointer that takes an array of stack elements, the number of elements and other arguments
/// in the form of a 'args' void pointer.
/// @param args Generic arguments for manage function pointer.
static inline void forevery_stack(stack_s * stack, const manage_stack_fn manage, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    manage(stack->elements, stack->size, args);
}

#endif

#else

#error Cannot include multiple headers in same unit.

#endif // STACK_H
