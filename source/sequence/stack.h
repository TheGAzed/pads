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

#ifndef STACK_DATA_TYPE

// redefine using #define STACK_DATA_TYPE [type]
#define STACK_DATA_TYPE void*

#endif

#ifndef STACK_ASSERT

#include <assert.h>  // imports assert for debugging

// redefine using #define STACK_DATA_TYPE [assert]
#define STACK_ASSERT assert

#endif

/// Function pointer that creates a deep element copy.
typedef STACK_DATA_TYPE (*copy_stack_fn)    (const STACK_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_stack_fn) (STACK_DATA_TYPE * element);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns 'false' if foreach loop should break.
typedef bool            (*operate_stack_fn) (STACK_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void            (*manage_stack_fn)  (STACK_DATA_TYPE * array, const size_t size, void * args);

#ifndef STACK_SIZE

#define STACK_SIZE (1 << 10)

#elif STACK_SIZE <= 0

#error Size cannot be zero.

#endif

typedef struct stack {
    STACK_DATA_TYPE elements[STACK_SIZE]; // elements array
    size_t size;                          // size of stack
} stack_s;

/// @brief Creates an empty stack structure.
/// @return Stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { .size = 0, }; // only needs to initialize size == 0
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure.
/// @param destroy Function pointer that destroys an element.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    for (; stack->size; stack->size--) {
        destroy(stack->elements + (stack->size - 1));
    }
}

/// @brief Clears all elements in stack.
/// @param stack Stack structure.
/// @param destroy Function pointer that destroys an element.
static inline void clear_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(destroy && "[ERROR] 'destroy' parameter pointer is NULL.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    for (; stack->size; stack->size--) {
        destroy(stack->elements + (stack->size - 1));
    }
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    return !(stack->size);
}

/// @brief Checks if stack is full or if stack's '.size' will overflow.
/// @param stack Stack structure.
/// @return 'true' if stack size reached maximum, 'false' otherwise.
static inline bool is_full_stack(const stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    return (stack->size == STACK_SIZE);
}

/// @brief Gets element at the top of the stack without removing it.
/// @param stack Stack structure.
/// @return The top element in the stack.
static inline STACK_DATA_TYPE peep_stack(const stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(stack->size && "[ERROR] Can't peek empty stack");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    return stack->elements[stack->size - 1];
}

/// @brief Pushes the element to the top of the stack.
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL.");
    STACK_ASSERT((stack->size < STACK_SIZE) && "[ERROR] Stack reached maximum size.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    // treat size as next index, add element and increment size
    memcpy(stack->elements + (stack->size++), &element, sizeof(STACK_DATA_TYPE));
}

/// @brief Pops and removes the element at the top of the stack.
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' pointer is empty.");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    return stack->elements[--(stack->size)]; // treat decremented size as current index
}

/// @brief Copies the stack and all its elements into a new structure.
/// @param stack Stack structure to copy.
/// @param copy Function pointer to create a deep/shallow copy of an element in stack.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s * stack, const copy_stack_fn copy) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(copy && "[ERROR] 'copy' parameter pointer is NULL.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    stack_s stack_copy = { .size = stack->size, };

    for (size_t i = 0; i < stack->size; i++) {
        stack_copy.elements[i] = copy(stack->elements[i]);
    }

    return stack_copy;
}

/// @brief Iterates over and operates on each element in structure using generic arguments.
/// @param stack Stack structure pointer.
/// @param operate Function pointer that takes an element pointer and generic arguments as parameters.
/// @param args Generic void pointer arguments for operation function pointer.
static inline void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    for (size_t i = 0; i < stack->size && operate(stack->elements + (stack->size - i - 1), args); ++i) {}
}

/// @brief Map function that maps elements into array and manages it using size and args.
/// @param stack Stack structure pointer.
/// @param manage Function pointer that takes an array of stack elements, the number of elements and other arguments
/// in the form of a 'args' void pointer.
/// @param args Generic arguments for manage function pointer.
static inline void map_stack(stack_s * stack, const manage_stack_fn manage, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    STACK_ASSERT(stack->size <= STACK_SIZE && "[ERROR] Invalid stack size.");

    manage(stack->elements, stack->size, args);
}

#else

#error Cannot include multiple headers in same unit.

#endif // STACK_H
