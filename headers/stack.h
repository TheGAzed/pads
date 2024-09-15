#ifndef STACK_H

#define STACK_H

#ifdef STACK_HELP

#error The stack.h file is a single header preprocesor abstracted implementation of the 'stack' data structure. The header has 4 implementations of a stack structure which can be divided into 2 categories: finite and infinite stacks (defined as macro's 'FINITE_STACK' and 'INFINITE_STACK'). The category 'INFINITE_STACK' uses the 'INFINITE_LIST_STACK' implementation as default. 'FINITE_STACK' uses 'FINITE_ALLOCATED_STACK' as default. The other two modes are 'INFINITE_REALLOC_STACK' and 'FINITE_PRERPOCESSOR_STACK'. In order to determine which category is selected the macro 'IS_INFINITE_STACK' can be used. The default stack mode is 'INFINITE_STACK' (or 'INFINITE_LIST_STACK' to be precise) as defined by 'STACK_MODE'. To use another of the available modes use '#define STACK_MODE [category or mode macro]' before including the header. To specify the data type to be stacked use '#define STACK_DATA_TYPE [data type]' before including the header (default is 'void*' or 'void pointer'). The 'INFINITE_LIST_STACK' mode uses a linked list implementation to create an infinite sized stacks. Since this mode's element is an array of 'STACK_DATA_TYPE' variables, the size of the allocated list element's array can be changed using 'LIST_ARRAY_STACK_CHUNK' macro like '#define LIST_ARRAY_STACK_CHUNK [size]' (default size is (1 << 10) or 1024). The 'FINITE_ALLOCATED_STACK' mode uses an allocated array, the user can specify the maximum size of the stack when calling 'create_stack([maximum size])' function, it is not necessary to define the stack's size using a macro (the user can create multiple stacks of variable length). The 'INFINITE_REALLOC_STACK' mode relies on the 'realloc()' function to guarantee infinite size, after the allocated array reaches its maximum length it is expanded (not doubled) by
'REALLOC_STACK_CHUNK', when the size shrinks to the point that a 'REALLOC_STACK_CHUNK' chunk is 'empty' the array also shrinks by 'REALLOC_STACK_CHUNK'. The user can use '#define REALLOC_STACK_CHUNK [size]' to define the chunk size. The 'FINITE_PRERPOCESSOR_STACK' mode uses the 'PREPROCESSOR_STACK_SIZE' macro to define the stack size. This mode does not use any memory allocation as the user can specify the size using '#define PREPROCESSOR_STACK_SIZE [size]'.

#endif

// stack mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_LIST_STACK       01
#define FINITE_ALLOCATED_STACK    02
#define INFINITE_REALLOC_STACK    03
#define FINITE_PRERPOCESSOR_STACK 04

#define INFINITE_STACK INFINITE_LIST_STACK
#define FINITE_STACK   FINITE_ALLOCATED_STACK

// Stack mode that can be set to INFINITE_LIST_STACK, FINITE_ALLOCATED_STACK, INFINITE_REALLOC_STACK or FINITE_PRERPOCESSOR_STACK.
// Default: INFINITE_LIST_STACK
#ifndef STACK_MODE

#define STACK_MODE INFINITE_STACK

#endif

#define IS_INFINITE_STACK ((bool)(STACK_MODE & 01))

// Check to make sure a valid stack mode is selected.
#if (STACK_MODE != INFINITE_LIST_STACK)    && (STACK_MODE != FINITE_ALLOCATED_STACK) && \
    (STACK_MODE != INFINITE_REALLOC_STACK) && (STACK_MODE != FINITE_PRERPOCESSOR_STACK)

#error Invalid type of stack mode.

#endif

// Stack data type to specify what datatype to stack.
// DEFAULT: void *
#ifndef STACK_DATA_TYPE

#define STACK_DATA_TYPE void*

#endif

#include <stdlib.h>  // imports size_t and malloc
#include <assert.h>  // imports assert for debugging
#include <stdbool.h> // imports bool for conditional stack functions (is_[state]_stack())

#if   STACK_MODE == INFINITE_LIST_STACK

// Stack list array size.
// DEFAULT: (1 << 10) or 1024
#ifndef LIST_ARRAY_STACK_CHUNK

#define LIST_ARRAY_STACK_CHUNK (1 << 10)

#elif LIST_ARRAY_STACK_CHUNK == 0

#error 'LIST_ARRAY_STACK_CHUNK' cannot be zero.

#endif

/// @brief Linked list of arrays that appends new list element at the start after array is full.
struct stack_list_array {
    struct stack_list_array * next; // next linked list array
    STACK_DATA_TYPE elements[LIST_ARRAY_STACK_CHUNK]; // array to store elements
};

/// @brief Stack implementation that uses appended lists of arrays and pushes elements based on the size.
typedef struct stack {
    struct stack_list_array * head; // head list element with the top of the stack
    size_t size; // size of stack
} stack_s;

/// @brief Creates empty stack with everything (.size, .head) set to zero/NULL.
/// @return Stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { 0 }; // stack.size is 0 and head must be NULL
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in stack or NULL if stack element has no allocated memory.
static inline void destroy_stack(stack_s * stack, void (*destroy_element)(STACK_DATA_TYPE *)) {
    assert(stack && "[ERROR] Stack pointer is NULL");

    struct stack_list_array * list = stack->head;
    const size_t mod_size = stack->size % LIST_ARRAY_STACK_CHUNK;
    if (list && mod_size) {
        if (destroy_element) {
            for (size_t s = 0; s < mod_size; s++) {
                destroy_element(&(list->elements[s]));
            }
        }

        struct stack_list_array * temp = list;
        list = list->next;
        free(temp);
    }

    while (list) {
        if (destroy_element) {
            for (size_t s = 0; s < LIST_ARRAY_STACK_CHUNK; s++) {
                destroy_element(&(list->elements[s]));
            }
        }

        struct stack_list_array * temp = list;
        list = list->next;
        free(temp);
    }

    *stack = (stack_s) { 0 }; // reset stack.size to 0 and .head to NULL
}

/// @brief Checks if stack is full or if stack's .size will overflow.
/// @param stack Stack structure.
/// @return true if stack reached maximum size or overflows after incrementing it, false otherwise.
static inline bool is_full_stack(const stack_s stack) {
    return !(~stack.size); // checks if '.size' of type size_t won't overflown after pushing another element
}

/// @brief Gets element at the top of the stack without decrementing size (peek the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    assert(stack.size && "[ERROR] Can't peek empty stack");
    assert(stack.head && "[ERROR] Stack head is NULL");

    return stack.head->elements[(stack.size - 1) % LIST_ARRAY_STACK_CHUNK]; // return element at head list
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, STACK_DATA_TYPE element) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    assert((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    const size_t next_index = stack->size % LIST_ARRAY_STACK_CHUNK; // index where the next element will be pushed
    if (next_index == 0) { // if head list array is full (is divisible) adds new list element to head
        struct stack_list_array * temp = malloc(sizeof(struct stack_list_array));

        assert(temp && "[ERROR] Memory allocation failed");
        temp->next = NULL; // prevent access to uninitialized memory

        temp->next = stack->head;
        stack->head = temp;
    }

    stack->head->elements[next_index] = element;
    stack->size++;
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro. 
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    assert(stack && "[ERROR] 'stack' pointer is empty");
    assert(stack->size && "[ERROR] Can't pop empty stack");
    assert(stack->head && "[ERROR] Stack head is NULL");

    const size_t current_index = (--stack->size) % LIST_ARRAY_STACK_CHUNK; // decrementing size gives top element index
    STACK_DATA_TYPE element = stack->head->elements[current_index];

    // if head has one element in array (index at 0) pop will make it empty and head can be freed
    if (current_index == 0) {
        struct stack_list_array * temp = stack->head->next;
        free(stack->head);
        stack->head = temp;
    }

    return element;
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy will be created 
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, STACK_DATA_TYPE (*copy_element)(STACK_DATA_TYPE)) {
    stack_s copy = { .size = stack.size, .head = NULL };

    struct stack_list_array * current_stack = stack.head;
    struct stack_list_array ** current_copy = &(copy.head); // two pointer list to remove special .head case

    const size_t copy_size = stack.size % LIST_ARRAY_STACK_CHUNK; // index of last element in head
    if (current_stack && copy_size) {
        *current_copy = malloc(sizeof(struct stack_list_array));
        assert(*current_copy && "[ERROR] Memory allocation failed");
        (*current_copy)->next = NULL;

        if (copy_element) {
            for (size_t s = 0; s < copy_size; s++) {
                (*current_copy)->elements[s] = copy_element(current_stack->elements[s]);
            }
        } else {
            memcpy((*current_copy)->elements, current_stack->elements, copy_size * sizeof(STACK_DATA_TYPE));
        }

        current_stack = current_stack->next;
        current_copy = &((*current_copy)->next);
    }

    while (current_stack) { // the other elements must have full arrays
        *current_copy = malloc(sizeof(struct stack_list_array));
        assert(*current_copy && "[ERROR] Memory allocation failed");
        (*current_copy)->next = NULL;

        if (copy_element) {
            for (size_t s = 0; s < LIST_ARRAY_STACK_CHUNK; s++) {
                (*current_copy)->elements[s] = copy_element(current_stack->elements[s]);
            }
        } else {
            memcpy((*current_copy)->elements, current_stack->elements, LIST_ARRAY_STACK_CHUNK * sizeof(STACK_DATA_TYPE));
        }

        current_stack = current_stack->next;
        current_copy = &((*current_copy)->next);
    }

    return copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Stack implementation that uses allocated memory array and pushes elements based on the current and maximum size.
typedef struct stack {
    STACK_DATA_TYPE * elements; // pointer to allocated memory
    size_t max;                 // maximum stack size
    size_t size;                // current stack size
} stack_s;

/// @brief Creates empty stack with '.size' set to zero, elements with 'max' allocated memory and '.max' to parameter 'max'.
/// @param max Specifies maximum allocated size of stack structure.
/// @return Stack structure.
static inline stack_s create_stack(const size_t max) {
    assert(max && "[ERROR] Maximum size can't be zero");
    const stack_s create = {
        .max = max, .elements = malloc(sizeof(STACK_DATA_TYPE) * max), .size = 0,
    };
    assert(create.elements && "[ERROR] Memory allocation failed");
    return create;
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in stack or NULL if stack element has no allocated memory.
static inline void destroy_stack(stack_s * stack, void (*destroy_element)(STACK_DATA_TYPE *)) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    if (destroy_element) {
        for(size_t s = 0; s < stack->size; s++) {
            destroy_element(&(stack->elements[s]));
        }
    }

    free(stack->elements);
    *stack = (stack_s) { 0 };
}

/// @brief Checks if stack is full or if stack's .size will overflow.
/// @param stack Stack structure.
/// @return true if stack size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    return !(stack.size < stack.max && ~stack.size);
}

/// @brief Gets element at the top of the stack without decrementing size (peeks the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    assert(stack.size && "[ERROR] Can't peek empty stack");
    assert(stack.elements && "[ERROR] '.elements' is NULL");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, STACK_DATA_TYPE element) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    assert((stack->size < stack->max) && "[ERROR] Stack reached maximum size");
    assert((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");
    assert(stack->elements && "[ERROR] '.elements' is NULL");

    stack->elements[stack->size] = element;
    stack->size++;
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro. 
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    assert(stack && "[ERROR] 'stack' pointer is empty");
    assert(stack->size && "[ERROR] Can't pop empty stack");
    assert(stack->elements && "[ERROR] '.elements' is NULL");

    return stack->elements[((stack->size)--) - 1];
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy will be created 
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, STACK_DATA_TYPE (*copy_element)(STACK_DATA_TYPE)) {
    stack_s copy = stack;
    copy.elements = malloc(sizeof(STACK_DATA_TYPE) * stack.max);
    assert(copy.elements && "[ERROR] Memory allocation failed");

    if (copy_element) {
        for (size_t s = 0; s < stack.size; s++) {
            copy.elements[s] = copy_element(stack.elements[s]);
        }
    } else {
        memcpy(copy.elements, stack.elements, sizeof(STACK_DATA_TYPE) * stack.size);
    }

    return copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

#ifndef REALLOC_STACK_CHUNK

#define REALLOC_STACK_CHUNK (1 << 10)

#endif

typedef struct stack {
    size_t size;
    STACK_DATA_TYPE * elements;
} stack_s;

/// @brief Creates empty stack with '.size' set to zero and '.elements' set to NULL.
/// @return Stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { 0 };
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in stack or NULL if stack element
/// has no allocated memory.
static inline void destroy_stack(stack_s * stack, void (*destroy_element)(STACK_DATA_TYPE *)) {
    assert(stack && "[ERROR] Stack pointer is NULL");

    if (destroy_element) {
        for(size_t s = 0; s < stack->size; s++) {
            destroy_element(&(stack->elements[s]));
        }
    }

    free(stack->elements);

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
    assert(stack.size && "[ERROR] Can't peek empty stack");
    assert(stack.elements && "[ERROR] Stack's '.elements' is NULL");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, STACK_DATA_TYPE element) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    assert((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    // first expand memory if necessary and then add element
    if ((stack->size % REALLOC_STACK_CHUNK) == 0) {
        stack->elements = realloc(stack->elements, (stack->size + REALLOC_STACK_CHUNK) * sizeof(STACK_DATA_TYPE));
        assert(stack->elements && "[ERROR] Memory allocation failed");
    }
    stack->elements[stack->size++] = element;
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    assert(stack && "[ERROR] 'stack' pointer is empty");
    assert(stack->size && "[ERROR] Can't pop empty stack");

    // first remove element and then shrink memory if necessary
    STACK_DATA_TYPE element = stack->elements[((stack->size)--) - 1];
    if ((stack->size % REALLOC_STACK_CHUNK) == 0) {
        stack->elements = realloc(stack->elements, (stack->size) * sizeof(STACK_DATA_TYPE));
    }

    return element;
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, STACK_DATA_TYPE (*copy_element)(STACK_DATA_TYPE)) {
    if (!stack.size) return (stack_s) { 0 };
    assert(stack.elements && "[ERROR] Stack's '.elements' is NULL");

    const stack_s copy = {
        .size = stack.size,
        .elements = malloc(sizeof(STACK_DATA_TYPE) * (stack.size - (stack.size % REALLOC_STACK_CHUNK) + REALLOC_STACK_CHUNK)),
    };
    assert(copy.elements && "[ERROR] Memory allocation failed");

    if (copy_element) {
        for (size_t s = 0; s < stack.size; s++) {
            copy.elements[s] = copy_element(stack.elements[s]);
        }
    } else {
        memcpy(copy.elements, stack.elements, sizeof(STACK_DATA_TYPE) * stack.size);
    }

    return copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

#ifndef PREPROCESSOR_STACK_SIZE

#define PREPROCESSOR_STACK_SIZE (1 << 10)

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
    return (stack_s) { .size = 0 }; // only needs to initialize size == 0
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in stack or NULL if stack element has no allocated memory.
static inline void destroy_stack(stack_s * stack, void (*destroy_element)(STACK_DATA_TYPE *)) {
    assert(stack && "[ERROR] Stack pointer is NULL");

    if (destroy_element) {
        for(size_t s = 0; s < stack->size; s++) {
            destroy_element(&(stack->elements[s]));
        }
    }

    *stack = (stack_s) { .size = 0 };
}

/// @brief Checks if stack is full or if stack's '.size' will overflow.
/// @param stack Stack structure.
/// @return true if stack size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    return !((stack.size < PREPROCESSOR_STACK_SIZE) && (~stack.size));
}

/// @brief Gets element at the top of the stack without decrementing size (peeks the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    assert(stack.size && "[ERROR] Can't peek empty stack");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, STACK_DATA_TYPE element) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    assert((stack->size < PREPROCESSOR_STACK_SIZE) && "[ERROR] Stack reached maximum size");
    assert((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    stack->elements[(stack->size)++] = element;
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro. 
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    assert(stack && "[ERROR] 'stack' pointer is empty");
    assert(stack->size && "[ERROR] Can't pop empty stack");

    return stack->elements[(((stack->size)--) - 1)];
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy will be created 
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, STACK_DATA_TYPE (*copy_element)(STACK_DATA_TYPE)) {
    stack_s copy = { .size = stack.size, };

    if (copy_element) {
        for (size_t s = 0; s < stack.size; s++) {
            copy.elements[s] = copy_element(stack.elements[s]);
        }
    } else {
        memcpy(copy.elements, stack.elements, stack.size * sizeof(STACK_DATA_TYPE));
    }

    return copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

#endif

#endif // STACK_H
