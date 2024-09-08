#ifndef STACK_H

#define STACK_H

#ifdef STACK_HELP

#error The stack.h file is a single header preprocesor abstracted implementation of the 'stack' data structure. The structure uses 3 modes - 'INFINITE_STACK' (stack of indefinite size), 'FINITE_STACK' (stack of finite size where the user can specify allocated size) and PREDEFINED_STACK (stack of finite preprocessor defined size that can be changed by defining the 'PREDEFINED_STACK_SIZE' macro). The default mode is 'INFINITE_STACK', to specify another one use '#define STACK_MODE [mode]'. To specify the data type to stack use '#define STACK_DATA_TYPE [type]' (default being void*). When using 'INFINITE_STACK' mode the user can define the size of the finite array that gets linked after a new element is pushed and does not fit into the previous one by using '#define STACK_LIST_ARRAY_SIZE [value]', default size is (1 << 10) or 1024 (it does not have to be a power of two). When using 'PREDEFINED_STACK' the user can specify the predefined size of the stack array by adding '#define PREDEFINED_STACK_SIZE [value]', default size is (1 << 10) or 1024 (it does not have to be a power of two).

#endif

// stack mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_STACK   01
#define FINITE_STACK     02
#define PREDEFINED_STACK 03

// Stack mode that can be set to INFINITE_STACK or FINITE_STACK or PREDEFINED_STACK.
// Default: INFINITE_STACK
#ifndef STACK_MODE

#define STACK_MODE INFINITE_STACK

#endif

// Check to make sure a valid stack mode is selected.
#if STACK_MODE != INFINITE_STACK && STACK_MODE != FINITE_STACK &&  STACK_MODE != PREDEFINED_STACK

#error invalid type of stack mode

#endif

// Stack data type to specify what datatype to stack.
// DEFAULT: void *
#ifndef STACK_DATA_TYPE

#define STACK_DATA_TYPE void*

#endif

#include <stdlib.h>  // imports size_t and malloc
#include <assert.h>  // imports assert for debugging
#include <stdbool.h> // imports bool for conditional stack functions (is_[state]_stack())

#if   STACK_MODE == INFINITE_STACK

// Stack list array size.
// DEFAULT: (1 << 10) or 1024
#ifndef STACK_LIST_ARRAY_SIZE

#define STACK_LIST_ARRAY_SIZE (1 << 10)

#elif STACK_LIST_ARRAY_SIZE == 0

#error 'STACK_LIST_ARRAY_SIZE' cannot be zero.

#endif

/// @brief Linked list of arrays that appends new list element at the start after array is full.
struct stack_list_array
{
    struct stack_list_array * next; // next linked list array
    STACK_DATA_TYPE elements[STACK_LIST_ARRAY_SIZE]; // array to store elements
};

/// @brief Stack implementation that uses appended lists of arrays and pushes elements based on the size.
typedef struct stack
{
    struct stack_list_array * head; // head list element with the top of the stack
    size_t size; // size of stack
} stack_s;


/// @brief Creates empty stack with everything (.size, .head) set to zero/NULL.
/// @return Stack structure.
static inline stack_s create_stack(void) {
    return (stack_s){0};
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in stack or NULL if stack element has no allocated memory.
static inline void destroy_stack(stack_s * stack, void (*destroy_element)(STACK_DATA_TYPE *)) {
    struct stack_list_array * list = stack->head;
    if (destroy_element) {
        size_t mod_size = stack->size % STACK_LIST_ARRAY_SIZE;
        if (list && mod_size) {
            for (size_t s = 0; s < mod_size; s++) {
                destroy_element(&(list->elements[s]));
            }

            struct stack_list_array * temp = list;
            list = list->next;
            free(temp);
        }

        while (list) {
            for (size_t s = 0; s < STACK_LIST_ARRAY_SIZE; s++) {
                destroy_element(&(list->elements[s]));
            }

            struct stack_list_array * temp = list;
            list = list->next;
            free(temp);
        }
    } else {
        while (list) {
            struct stack_list_array * temp = list;
            list = list->next;
            free(temp);
        }
    }

    *stack = (stack_s){0};
}

/// @brief Checks if stack is full or if stack's .size will overflow.
/// @param stack Stack structure.
/// @return true if stack reached maximum size or overflows after incrementing it, false otherwise.
static inline bool is_full_stack(const stack_s stack) {
    return !(~stack.size); // checks if '.size' of type size_t hasn't overflown
}

/// @brief Gets element at the top of the stack without decrementing size (peek the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peek_stack(const stack_s stack) {
    assert(stack.size && "[ERROR] Can't peek empty stack");

    return stack.head->elements[(stack.size - 1) % STACK_LIST_ARRAY_SIZE];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, STACK_DATA_TYPE element) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    assert((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    size_t next_index = stack->size % STACK_LIST_ARRAY_SIZE;

    if (next_index == 0) {
        struct stack_list_array * temp = malloc(sizeof(struct stack_list_array));

        assert(temp && "[ERROR] Memory allocation failed");
        temp->next = NULL;

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

    const size_t current_index = (stack->size - 1) % STACK_LIST_ARRAY_SIZE;

    STACK_DATA_TYPE element = stack->head->elements[current_index];

    if (current_index == 0) {
        struct stack_list_array * temp = stack->head->next;
        free(stack->head);
        stack->head = temp;
    }
    stack->size--;

    return element;
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy will be created 
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, STACK_DATA_TYPE (*copy_element)(STACK_DATA_TYPE)) {
    stack_s copy = {0};

    struct stack_list_array * current = stack.head;
    if (copy_element) {
        for (size_t i = stack.size - 1; current;) {
            struct stack_list_array * temp = malloc(sizeof(struct stack_list_array));

            assert(temp && "[ERROR] Memory allocation failed");
            temp->next = NULL;

            temp->next = copy.head;
            copy.head = temp;

            for (size_t j = i % STACK_LIST_ARRAY_SIZE;; i--, j--) {
                copy.head->elements[j] = copy_element(current->elements[j]);
                copy.size++;
            }

            current = current->next;
        }
    } else {
        for (size_t i = stack.size - 1; current;) {
            struct stack_list_array * temp = malloc(sizeof(struct stack_list_array));

            assert(temp && "[ERROR] Memory allocation failed");
            temp->next = NULL;

            temp->next = copy.head;
            copy.head = temp;

            for (size_t j = i % STACK_LIST_ARRAY_SIZE;; i--, j--) {
                copy.head->elements[j] = current->elements[j];
                copy.size++;
            }

            current = current->next;
        }
    }

    return copy;
}

#elif STACK_MODE == FINITE_STACK

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
    stack_s create = {
        .max = max, .elements = malloc(sizeof(STACK_DATA_TYPE) * max), .size = 0,
    };
    assert(create.elements && "[ERROR] Memory allocation failed");
    return create;
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in stack or NULL if stack element has no allocated memory.
static inline void destroy_stack(stack_s * stack, void (*destroy_element)(STACK_DATA_TYPE *)) {
    if (destroy_element) {
        for(size_t s = 0; s < stack->size; s++) {
            destroy_element(&(stack->elements[s]));
        }
    }

    if (stack->max) free(stack->elements);
    *stack = (stack_s) { 0 };
}

/// @brief Checks if stack is full or if stack's .size will overflow.
/// @param stack Stack structure.
/// @return true if stack size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_stack(stack_s stack) {
    return !(stack.size < stack.max) || !(~stack.size);
}

/// @brief Gets element at the top of the stack without decrementing size (peeks the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peek_stack(stack_s stack) {
    assert(stack.size && "[ERROR] Can't peek empty stack");

    return stack.elements[(stack.size - 1) % stack.max];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, STACK_DATA_TYPE element) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    assert((stack->size < stack->max) && "[ERROR] Stack reached maximum size");
    assert((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    stack->elements[stack->size % stack->max] = element;
    stack->size++;
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro. 
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    assert(stack && "[ERROR] 'stack' pointer is empty");
    assert(stack->size && "[ERROR] Can't pop empty stack");

    STACK_DATA_TYPE element = stack->elements[(stack->size - 1) % stack->max];
    stack->size--;
    
    return element;
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy will be created 
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(stack_s stack, STACK_DATA_TYPE (*copy_element)(STACK_DATA_TYPE)) {
    stack_s copy = { .size = stack.size, .max = stack.max, };
    copy.elements = malloc(sizeof(STACK_DATA_TYPE) * stack.max);
    assert(copy.elements && "[ERROR] Memory allocation failed");

    if (copy_element) {
        for (size_t s = 0; s < stack.size; s++) {
            copy.elements[s] = copy_element(stack.elements[s]);
        }
    } else {
        for (size_t s = 0; s < stack.size; s++) {
            copy.elements[s] = stack.elements[s];
        }
    }
}

#elif STACK_MODE == PREDEFINED_STACK

#ifndef PREDEFINED_STACK_SIZE

#define PREDEFINED_STACK_SIZE (1 << 10)

#elif PREDEFINED_STACK_SIZE == 0

#error 'PREDEFINED_STACK_SIZE' cannot be zero

#endif

typedef struct stack {
    STACK_DATA_TYPE elements[PREDEFINED_STACK_SIZE];
    size_t size;
} stack_s;

/// @brief Creates empty stack with '.size' set to zero.
/// @return Stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { .size = 0 };
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy_element function pointer to destroy (or free) elements in stack or NULL if stack element has no allocated memory.
static inline void destroy_stack(stack_s * stack, void (*destroy_element)(STACK_DATA_TYPE *)) {
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
static inline bool is_full_stack(stack_s stack) {
    return !(stack.size < PREDEFINED_STACK_SIZE) || !(~stack.size);
}

/// @brief Gets element at the top of the stack without decrementing size (peeks the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peek_stack(stack_s stack) {
    assert(stack.size && "[ERROR] Can't peek empty stack");

    return stack.elements[(stack.size - 1) % PREDEFINED_STACK_SIZE];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, STACK_DATA_TYPE element) {
    assert(stack && "[ERROR] Stack pointer is NULL");
    assert((stack->size < PREDEFINED_STACK_SIZE) && "[ERROR] Stack reached maximum size");
    assert((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    stack->elements[stack->size % PREDEFINED_STACK_SIZE] = element;
    stack->size++;
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro. 
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    assert(stack && "[ERROR] 'stack' pointer is empty");
    assert(stack->size && "[ERROR] Can't pop empty stack");

    STACK_DATA_TYPE element = stack->elements[(stack->size - 1) % PREDEFINED_STACK_SIZE];
    stack->size--;
    
    return element;
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy will be created 
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy_element Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(stack_s stack, STACK_DATA_TYPE (*copy_element)(STACK_DATA_TYPE)) {
    stack_s copy = { .size = stack.size, };

    if (copy_element) {
        for (size_t s = 0; s < stack.size; s++) {
            copy.elements[s] = copy_element(stack.elements[s]);
        }
    } else {
        for (size_t s = 0; s < stack.size; s++) {
            copy.elements[s] = stack.elements[s];
        }
    }
}

#endif

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

#endif //STACK_H
