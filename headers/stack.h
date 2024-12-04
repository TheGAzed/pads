#ifndef STACK_H

#define STACK_H

#ifdef STACK_HELP

#error The stack.h file is a single header preprocesor abstracted implementation of the 'stack' data structure. The header has 4 implementations of a stack structure which can be divided into 2 categories: finite and infinite stacks (defined as macro's 'FINITE_STACK' and 'INFINITE_STACK'). The category 'INFINITE_STACK' uses the 'INFINITE_LIST_STACK' implementation as default. 'FINITE_STACK' uses 'FINITE_ALLOCATED_STACK' as default. The other two modes are 'INFINITE_REALLOC_STACK' and 'FINITE_PRERPOCESSOR_STACK'. In order to determine which category is selected the macro 'IS_INFINITE_STACK' can be used. The default stack mode is 'INFINITE_STACK' (or 'INFINITE_LIST_STACK' to be precise) as defined by 'STACK_MODE'. To use another of the available modes use '#define STACK_MODE [category or mode macro]' before including the header. To specify the data type to be stacked use '#define STACK_DATA_TYPE [data type]' before including the header (default is 'void*' or 'void pointer'). The 'INFINITE_LIST_STACK' mode uses a linked list implementation to create an infinite sized stacks. Since this mode's element is an array of 'STACK_DATA_TYPE' variables, the size of the allocated list element's array can be changed using 'LIST_ARRAY_STACK_CHUNK' macro like '#define LIST_ARRAY_STACK_CHUNK [size]' (default size is (1 << 10) or 1024). The 'FINITE_ALLOCATED_STACK' mode uses an allocated array, the user can specify the maximum size of the stack when calling 'create_stack([maximum size])' function, it is not necessary to define the stack's size using a macro (the user can create multiple stacks of variable length). The 'INFINITE_REALLOC_STACK' mode relies on the 'realloc()' function to guarantee infinite size, after the allocated array reaches its maximum length it is expanded (not doubled) by 'REALLOC_STACK_CHUNK', when the size shrinks to the point that a 'REALLOC_STACK_CHUNK' chunk is 'empty' the array also shrinks by 'REALLOC_STACK_CHUNK'. The user can use '#define REALLOC_STACK_CHUNK [size]' to define the chunk size. The 'FINITE_PRERPOCESSOR_STACK' mode uses the 'PREPROCESSOR_STACK_SIZE' macro to define the stack size. This mode does not use any memory allocation as the user can specify the size using '#define PREPROCESSOR_STACK_SIZE [size]'.

#endif

// stack mode macros in octal to prevent future overlap with other data structure modes
#define INFINITE_LIST_STACK       0x1
#define FINITE_ALLOCATED_STACK    0x2
#define INFINITE_REALLOC_STACK    0x3
#define FINITE_PRERPOCESSOR_STACK 0x4

#define INFINITE_STACK INFINITE_LIST_STACK
#define FINITE_STACK   FINITE_ALLOCATED_STACK

//#define STACK_MODE INFINITE_LIST_STACK
//#define STACK_MODE FINITE_ALLOCATED_STACK
//#define STACK_MODE INFINITE_REALLOC_STACK
//#define STACK_MODE FINITE_PRERPOCESSOR_STACK
// Stack mode that can be set to 'INFINITE_LIST_STACK', 'FINITE_ALLOCATED_STACK', 'INFINITE_REALLOC_STACK' or
// 'FINITE_PRERPOCESSOR_STACK'.
// Default: 'INFINITE_LIST_STACK'
#ifndef STACK_MODE
    #define STACK_MODE INFINITE_STACK
#endif

#define IS_INFINITE_STACK ((bool)(STACK_MODE & 0x1))

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
#include <stdbool.h> // imports bool for conditional stack functions (is_[state]_stack())
#include <string.h>  // imports memcpy

#ifndef STACK_ASSERT

#include <assert.h>  // imports assert for debugging

#define STACK_ASSERT assert
#endif

#ifndef STACK_ALLOC

#define STACK_ALLOC malloc

#endif

#ifndef STACK_FREE

#define STACK_FREE free

#endif

/// Function pointer that creates a deep element copy.
typedef STACK_DATA_TYPE (*copy_stack_fn)    (const STACK_DATA_TYPE);
/// Function pointer that destroys a deep element.
typedef void            (*destroy_stack_fn) (STACK_DATA_TYPE *);
/// Function pointer that compares two elements, used in sorting function.
typedef int             (*compare_stack_fn) (const void *, const void *);
/// Function pointer that sorts an array of elements, uses 'qsort()' function parameter template.
typedef void            (*sort_stack_fn)    (void * array, size_t number, size_t size, compare_stack_fn);
/// Function pointer that changes an element pointer using void pointer arguments if needed.
typedef void            (*operate_stack_fn) (STACK_DATA_TYPE *, void *);

#if   STACK_MODE == INFINITE_LIST_STACK

// Stack list array size.
// DEFAULT: (1 << 10) or 1024
#ifndef LIST_ARRAY_STACK_CHUNK

#define LIST_ARRAY_STACK_CHUNK (1 << 10)

#elif LIST_ARRAY_STACK_CHUNK <= 0

#error 'LIST_ARRAY_STACK_CHUNK' cannot be less than or equal to zero.

#endif

/// @brief Linked list of arrays that appends new list element at the start after array is full.
struct stack_list_array {
    struct stack_list_array * next; // next linked list array
    STACK_DATA_TYPE elements[LIST_ARRAY_STACK_CHUNK]; // array to store elements
};

/// @brief Stack implementation that uses appended lists of arrays and pushes elements based on the size.
typedef struct stack {
    struct stack_list_array * head; // head list element with the top of the stack
    size_t size;                    // size of stack
} stack_s;

/// @brief Creates empty stack.
/// @return Empty stack structure.
static inline stack_s create_stack(void) {
    return (stack_s) { .head = NULL, .size = 0, };
}

/// @brief Destroys a stack.
/// @param stack Pointer to stack structure.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");
    STACK_ASSERT(((stack->head && stack->size) || (!stack->head && !stack->size)) && "[ERROR] Invalid stack state.");

    struct stack_list_array * list = stack->head; // list pointer to head elements array
    const size_t mod_size = stack->size % LIST_ARRAY_STACK_CHUNK; // check if first elements array is full or partially filled
    if (mod_size) { // special case when list elements array is not full
        for (size_t s = 0; destroy && s < mod_size; s++) { // destroys stack elements
            destroy(&(list->elements[s])); // calls destroy element function if not NULL
        }

        struct stack_list_array * temp = list; // temporary pointer to not lose reference
        list = list->next; // go to next pointer
        STACK_FREE(temp); // free temporary
    }
    while (list) { // if first list elements array is full then starts here else it first destroys partially filled elements
        for (size_t s = 0; destroy && s < LIST_ARRAY_STACK_CHUNK; s++) { // destroys stack elements
            destroy(&(list->elements[s])); // calls destroy element function if not NULL
        }

        struct stack_list_array * temp = list; // temporary pointer to not lose reference
        list = list->next; // go to next pointer
        STACK_FREE(temp); // free temporary
    }

    *stack = (stack_s) { 0 }; // resets everything in stack to zero/NULL
}

/// @brief Checks if stack is full.
/// @param stack Readonly stack structure to check.
/// @return true if is full, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    STACK_ASSERT(((stack.head && stack.size) || (!stack.head && !stack.size)) && "[ERROR] Invalid stack state.");
    return !(~stack.size); // checks if stack's size will overflow
}

/// @brief Peeps the top element in stack.
/// @param stack Readonly stack structure to peep.
/// @return Element of type 'STACK_DATA_TYPE' at the top of stack.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    STACK_ASSERT(stack.size && "[ERROR] Can't peek empty stack");
    STACK_ASSERT(stack.head && "[ERROR] Stack head is NULL");
    STACK_ASSERT(((stack.head && stack.size) || (!stack.head && !stack.size)) && "[ERROR] Invalid stack state.");

    return stack.head->elements[(stack.size - 1) % LIST_ARRAY_STACK_CHUNK]; // returns top element at head elements array
}

/// @brief Pushes the specified element to top.
/// @param stack Stack structure to push to.
/// @param element Constant element of type 'STACK_DATA_TYPE' to push into stack.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");
    STACK_ASSERT((~stack->size) && "[ERROR] Stack size will overflow.");
    STACK_ASSERT(((stack->head && stack->size) || (!stack->head && !stack->size)) && "[ERROR] Invalid stack state.");

    const size_t next_index = stack->size % LIST_ARRAY_STACK_CHUNK; // index where the next element will be pushed
    if (next_index == 0) { // if head list array is full (is divisible) adds new list element to head
        struct stack_list_array * temp = STACK_ALLOC(sizeof(struct stack_list_array));

        STACK_ASSERT(temp && "[ERROR] Memory allocation failed");
        temp->next = NULL; // prevent access to uninitialized memory

        temp->next = stack->head;
        stack->head = temp;
    }

    // pushes element to head's top
    memcpy(stack->head->elements + next_index, &element, sizeof(STACK_DATA_TYPE));
    stack->size++; // increments stack size
}

/// @brief Pops the top element in stack.
/// @param stack Stack structure pointer to pop.
/// @return Popped elements of type 'STACK_DATA_TYPE' from stack.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer parameter is NULL");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack");
    STACK_ASSERT(((stack->head && stack->size) || (!stack->head && !stack->size)) && "[ERROR] Invalid stack state.");

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
/// @param stack Constant stack structure to copy.
/// @param copy Function pointer that returns a copy of an element.
/// @return New stack copy with copied elements.
static inline stack_s copy_stack(const stack_s stack, const copy_stack_fn copy) {
    STACK_ASSERT(((stack.head && stack.size) || (!stack.head && !stack.size)) && "[ERROR] Invalid stack state.");
    stack_s stack_copy = stack; // copy everything to new stack copy

    struct stack_list_array const * current_stack = stack.head;
    struct stack_list_array ** current_copy = &(stack_copy.head); // two pointer list to remove special head case
    const size_t copy_size = stack.size % LIST_ARRAY_STACK_CHUNK;
    if (copy_size) { // special case when head stack
        *current_copy = STACK_ALLOC(sizeof(struct stack_list_array));
        STACK_ASSERT(*current_copy && "[ERROR] Memory allocation failed");
        (*current_copy)->next = NULL;

        if (copy) {
            for (size_t s = 0; s < copy_size; s++) {
                (*current_copy)->elements[s] = copy(current_stack->elements[s]);
            }
        } else memcpy((*current_copy)->elements, current_stack->elements, copy_size * sizeof(STACK_DATA_TYPE));

        current_stack = current_stack->next;
        current_copy = &((*current_copy)->next);
    }
    while (current_stack) { // is not NULL
        *current_copy = STACK_ALLOC(sizeof(struct stack_list_array));
        STACK_ASSERT(*current_copy && "[ERROR] Memory allocation failed");
        (*current_copy)->next = NULL;

        if (copy) {
            for (size_t s = 0; s < LIST_ARRAY_STACK_CHUNK; s++) {
                (*current_copy)->elements[s] = copy(current_stack->elements[s]);
            }
        } else memcpy((*current_copy)->elements, current_stack->elements, LIST_ARRAY_STACK_CHUNK * sizeof(STACK_DATA_TYPE));

        current_stack = current_stack->next;
        current_copy = &((*current_copy)->next);
    }

    return stack_copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    STACK_ASSERT(((stack.head && stack.size) || (!stack.head && !stack.size)) && "[ERROR] Invalid stack state.");

    return !(stack.size);
}

/// @brief Sorts elements in stack based on provided function pointer sorter or bubble sort with memcmp if
/// parameter is NULL.
/// @param stack Stack structure pointer.
/// @param sort Sorting function pointer or NULL, to use bubble sort with 'compare'/'memcmp'.
/// @param compare non NULL function pointer that compares two STACK_DATA_TYPE elements as void pointers. Used as
/// parameter for sort function.
static inline void sort_stack(stack_s * stack, const sort_stack_fn sort, const compare_stack_fn compare) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(sort && "[ERROR] 'sort' parameter is NULL.");
    STACK_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    STACK_ASSERT(((stack->head && stack->size) || (!stack->head && !stack->size)) && "[ERROR] Invalid stack state.");

    STACK_DATA_TYPE * elements_array = STACK_ALLOC(stack->size * sizeof(STACK_DATA_TYPE));
    STACK_ASSERT((!(stack->size) || elements_array) && "[ERROR] Memory allocation failed.");

    struct stack_list_array * list = stack->head;
    size_t copied_size = stack->size % LIST_ARRAY_STACK_CHUNK;
    if (copied_size) { // initial case when first list can have size less than LIST_ARRAY_STACK_CHUNK
        memcpy(elements_array, list->elements, sizeof(STACK_DATA_TYPE) * copied_size);
        list = list->next;
    }
    while (list) { // all lists with full list arrays/chunks
        memcpy(elements_array + copied_size, list->elements, sizeof(STACK_DATA_TYPE) * LIST_ARRAY_STACK_CHUNK);
        copied_size += LIST_ARRAY_STACK_CHUNK;
        list = list->next;
    }

    sort(elements_array, stack->size, sizeof(STACK_DATA_TYPE), compare);

    list = stack->head;
    copied_size = stack->size % LIST_ARRAY_STACK_CHUNK;
    if (copied_size) {
        memcpy(list->elements, elements_array + (stack->size - copied_size), sizeof(STACK_DATA_TYPE) * copied_size);
        list = list->next;
    }
    while (list) {
        copied_size += LIST_ARRAY_STACK_CHUNK;
        memcpy(list->elements, elements_array + (stack->size - copied_size), sizeof(STACK_DATA_TYPE) * LIST_ARRAY_STACK_CHUNK);
        list = list->next;
    }

    STACK_FREE(elements_array);
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer.
/// @param operate Function pointer that takes an element pointer and 'args' as parameters
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL");
    STACK_ASSERT(((stack->head && stack->size) || (!stack->head && !stack->size)) && "[ERROR] Invalid stack state.");

    struct stack_list_array * current = stack->head;
    const size_t chunk_size = stack->size % LIST_ARRAY_STACK_CHUNK;
    if (chunk_size) {
        for (size_t i = 0; i < chunk_size; ++i) {
            operate(current->elements + i, args);
        }
        current = current->next;
    }
    while (current) {
        for (size_t i = 0; i < LIST_ARRAY_STACK_CHUNK; ++i) {
            operate(current->elements + i, args);
        }
        current = current->next;
    }
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

/// @brief Stack implementation that uses allocated memory array and pushes elements based on the current
/// and maximum size.
typedef struct stack {
    STACK_DATA_TYPE * elements; // pointer to allocated memory
    size_t max, size;           // current stack size and maximum size
} stack_s;

/// @brief Creates empty stack with '.size' set to zero, elements with 'max' allocated memory and '.max'
/// to parameter 'max'.
/// @param max Specifies maximum allocated size of stack structure.
/// @return Stack structure.
static inline stack_s create_stack(const size_t max) {
    STACK_ASSERT(max && "[ERROR] Maximum size can't be zero");

    const stack_s create = {
        .max = max, .elements = STACK_ALLOC(max * sizeof(STACK_DATA_TYPE)), .size = 0,
    };
    assert(create.elements && "[ERROR] Memory allocation failed.");

    return create;
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack->elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack->max && "[ERROR] Stack's max can't be zero.");

    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");

    for(size_t s = 0; destroy && (s < stack->size); s++) {
        destroy(&(stack->elements[s]));
    }

    STACK_FREE(stack->elements);
    *stack = (stack_s) { 0 };
}

/// @brief Checks if stack is full or if stack's .size will overflow.
/// @param stack Stack structure.
/// @return true if stack size reached maximum or overflows after incrementing it, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    STACK_ASSERT(stack.elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack.max && "[ERROR] Stack's max can't be zero.");

    return !(stack.size < stack.max && ~stack.size);
}

/// @brief Gets element at the top of the stack without decrementing size (peeps the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    STACK_ASSERT(stack.elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack.max && "[ERROR] Stack's max can't be zero.");
    STACK_ASSERT(stack.size && "[ERROR] Can't peep empty stack");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");
    STACK_ASSERT(stack->elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack->max && "[ERROR] Stack's max can't be zero.");
    STACK_ASSERT((stack->size < stack->max) && "[ERROR] Stack reached maximum size");
    STACK_ASSERT((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    memcpy(stack->elements + stack->size++, &element, sizeof(STACK_DATA_TYPE));
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro. 
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack->elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack->max && "[ERROR] Stack's max can't be zero.");
    STACK_ASSERT(stack && "[ERROR] 'stack' pointer is empty");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack");

    return stack->elements[((stack->size)--) - 1];
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy Function pointer to create a copy of an element or NULL if 'STACK_DATA_TYPE' is a basic type.
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, const copy_stack_fn copy) {
    STACK_ASSERT(stack.elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack.max && "[ERROR] Stack's max can't be zero.");

    stack_s stack_copy = stack;
    stack_copy.elements = STACK_ALLOC(stack.max * sizeof(STACK_DATA_TYPE));
    STACK_ASSERT(stack_copy.elements && "[ERROR] Memory allocation failed");

    if (copy) {
        for (size_t s = 0; s < stack.size; s++) {
            stack_copy.elements[s] = copy(stack.elements[s]);
        }
    } else { // memcpy can be used
        memcpy(stack_copy.elements, stack.elements, sizeof(STACK_DATA_TYPE) * stack.size);
    }

    return stack_copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    STACK_ASSERT(stack.elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack.max && "[ERROR] Stack's max can't be zero.");

    return (stack.size == 0);
}

/// @brief Sorts stack elements using a function specified by the user.
/// @param stack Queue structure pointer.
/// @param sort Function pointer to sorting algorithm.
/// @param compare Function pointer to compare two elements.
static inline void sort_stack(stack_s * stack, const sort_stack_fn sort, const compare_stack_fn compare) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    STACK_ASSERT(sort && "[ERROR] 'sort' parameter is NULL.");
    STACK_ASSERT(stack->elements && "[ERROR] Stack's element array can't be NULL.");
    STACK_ASSERT(stack->max && "[ERROR] Stack's max can't be zero.");

    sort(stack->elements, stack->size, sizeof(STACK_DATA_TYPE), compare);
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer.
/// @param operate Non NULL function pointer that takes an element pointer and 'args' as parameters.
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL");

    for (size_t i = 0; i < stack->size; ++i) {
        operate(stack->elements + i, args);
    }
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
    return (stack_s) { .size = 0, .elements = NULL, };
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");
    STACK_ASSERT(((stack->elements && stack->size) || (!stack->elements && !stack->size)) && "[ERROR] Invalid stack state.");

    for(size_t s = 0; destroy && (s < stack->size); s++) {
        destroy(&(stack->elements[s]));
    }

    STACK_FREE(stack->elements);

    *stack = (stack_s) { 0 }; // reset stack to zero
}

/// @brief Checks if stack's .size will overflow.
/// @param stack Stack structure.
/// @return true if stack size overflows after incrementing it, false otherwise
static inline bool is_full_stack(const stack_s stack) {
    STACK_ASSERT(((stack.elements && stack.size) || (!stack.elements && !stack.size)) && "[ERROR] Invalid stack state.");

    return !(~stack.size);
}

/// @brief Gets element at the top of the stack without decrementing size (peeks the top of the stack).
/// @param stack Stack structure.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE peep_stack(const stack_s stack) {
    STACK_ASSERT(((stack.elements && stack.size) || (!stack.elements && !stack.size)) && "[ERROR] Invalid stack state.");
    STACK_ASSERT(stack.size && "[ERROR] Can't peek empty stack");
    STACK_ASSERT(stack.elements && "[ERROR] Stack's '.elements' is NULL");

    return stack.elements[stack.size - 1];
}

/// @brief Sets the next top empty element in stack array to 'element' parameter (pushes element on top).
/// @param stack Stack structure pointer.
/// @param element Element to push to top of stack array.
static inline void push_stack(stack_s * stack, const STACK_DATA_TYPE element) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");
    STACK_ASSERT(((stack->elements && stack->size) || (!stack->elements && !stack->size)) && "[ERROR] Invalid stack state.");
    STACK_ASSERT((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");

    // first expand memory if necessary and then add element
    if ((stack->size % REALLOC_STACK_CHUNK) == 0) {
        stack->elements = realloc(stack->elements, (stack->size + REALLOC_STACK_CHUNK) * sizeof(STACK_DATA_TYPE));
        STACK_ASSERT(stack->elements && "[ERROR] Memory allocation failed");
    }
    memcpy(stack->elements + stack->size++, &element, sizeof(STACK_DATA_TYPE));
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro.
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' pointer is empty");
    STACK_ASSERT(((stack->elements && stack->size) || (!stack->elements && !stack->size)) && "[ERROR] Invalid stack state.");
    STACK_ASSERT(stack->elements && "[ERROR] Can't pop from NULL array.");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack");

    // first remove element and then shrink memory if necessary
    STACK_DATA_TYPE element = stack->elements[--(stack->size)];
    if ((stack->size % REALLOC_STACK_CHUNK) == 0) {
        STACK_DATA_TYPE * elements = realloc(stack->elements, (stack->size) * sizeof(STACK_DATA_TYPE));
        stack->elements = stack->size ? elements : NULL;
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
    STACK_ASSERT(((stack.elements && stack.size) || (!stack.elements && !stack.size)) && "[ERROR] Invalid stack state.");
    if (!stack.size) return (stack_s) { 0 };

    const size_t copy_size = stack.size - (stack.size % REALLOC_STACK_CHUNK) + REALLOC_STACK_CHUNK;
    const stack_s stack_copy = { .size = stack.size, .elements = STACK_ALLOC(copy_size * sizeof(STACK_DATA_TYPE)), };

    // assertion fails if alloc returns NULL on non-zero copy size
    STACK_ASSERT((stack_copy.elements) && "[ERROR] Memory allocation failed.");

    if (copy) {
        for (size_t s = 0; s < stack.size; s++) {
            stack_copy.elements[s] = copy(stack.elements[s]);
        }
    } else {
        memcpy(stack_copy.elements, stack.elements, sizeof(STACK_DATA_TYPE) * stack.size);
    }

    return stack_copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    STACK_ASSERT(((stack.elements && stack.size) || (!stack.elements && !stack.size)) && "[ERROR] Invalid stack state.");

    return stack.size == 0;
}

/// @brief Sorts stack elements using a function specified by the user.
/// @param stack Queue structure pointer.
/// @param sort Function pointer to sorting algorithm.
/// @param compare Function pointer to compare two elements.
static inline void sort_stack(stack_s * stack, const sort_stack_fn sort, const compare_stack_fn compare) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(sort && "[ERROR] 'sort' parameter is NULL.");
    STACK_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");
    STACK_ASSERT(((stack->elements && stack->size) || (!stack->elements && !stack->size)) && "[ERROR] Invalid stack state.");

    sort(stack->elements, stack->size, sizeof(STACK_DATA_TYPE), compare);
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer.
/// @param operate Function pointer that takes an element pointer and 'args' as parameters
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL");
    STACK_ASSERT(((stack->elements && stack->size) || (!stack->elements && !stack->size)) && "[ERROR] Invalid stack state.");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL");

    for (size_t i = 0; i < stack->size; ++i) {
        operate(stack->elements + i, args);
    }
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
    return (stack_s) { .size = 0, }; // only needs to initialize size == 0
}

/// @brief Destroys stack and all elements in it.
/// @param stack Stack structure pointer.
/// @param destroy Function pointer that destroys/frees an element reference.
static inline void destroy_stack(stack_s * stack, const destroy_stack_fn destroy) {
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");

    for(size_t s = 0; destroy && (s < stack->size); s++) {
        destroy(&(stack->elements[s]));
    }

    stack->size = 0;
}

/// @brief Checks if stack is full or if stack's '.size' will overflow.
/// @param stack Stack structure.
/// @return true if stack size reached maximum or overflows after incrementing it, false otherwise.
static inline bool is_full_stack(const stack_s stack) {
    return !((stack.size < PREPROCESSOR_STACK_SIZE) && (~stack.size));
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
    STACK_ASSERT(stack && "[ERROR] Stack pointer is NULL");
    STACK_ASSERT((stack->size < PREPROCESSOR_STACK_SIZE) && "[ERROR] Stack reached maximum size");
    STACK_ASSERT((stack->size + 1) && "[ERROR] Stack's '.size' will overflow");
    // treat size as next index, add element and increment size
    memcpy(stack->elements + stack->size++, &element, sizeof(STACK_DATA_TYPE));
}

/// @brief Gets the top element in stack and decrements stack size (pops top element).
/// @param stack Stack structure pointer.
/// @return The top element of the stack as defined by 'STACK_DATA_TYPE' macro. 
static inline STACK_DATA_TYPE pop_stack(stack_s * stack) {
    STACK_ASSERT(stack && "[ERROR] 'stack' pointer is empty");
    STACK_ASSERT(stack->size && "[ERROR] Can't pop empty stack");

    return stack->elements[--(stack->size)]; // treat decremented size as current index
}

/// @brief Copies the stack and all its elements into a new stack structure. If copy_element is null a shallow copy
/// will be created
/// otherwise copy_element is called.
/// @param stack Stack structure.
/// @param copy
/// @return A copy of the specified 'stack' parameter.
static inline stack_s copy_stack(const stack_s stack, const copy_stack_fn copy) {
    stack_s stack_copy = { .size = stack.size, };

    if (copy) {
        for (size_t s = 0; s < stack.size; s++) {
            stack_copy.elements[s] = copy(stack.elements[s]);
        }
    } else {
        memcpy(stack_copy.elements, stack.elements, stack.size * sizeof(STACK_DATA_TYPE));
    }

    return stack_copy;
}

/// @brief Checks if stack is empty.
/// @param stack Stack structure.
/// @return true if stack size is zero, false otherwise
static inline bool is_empty_stack(const stack_s stack) {
    return stack.size == 0;
}

/// @brief Sorts stack elements using a function specified by the user.
/// @param stack Queue structure pointer.
/// @param sort Function pointer to sorting algorithm.
/// @param compare Function pointer to compare two elements.
static inline void sort_stack(stack_s * stack, const sort_stack_fn sort, const compare_stack_fn compare) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL.");
    STACK_ASSERT(sort && "[ERROR] 'sort' parameter is NULL.");
    STACK_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");

    sort(stack->elements, stack->size, sizeof(STACK_DATA_TYPE), compare);
}

/// @brief For each function that does an operation on element reference specified by args.
/// @param stack Stack structure pointer.
/// @param operate Function pointer that takes an element pointer and 'args' as parameters
/// @param args Arguments for operation function pointer.
static inline void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args) {
    STACK_ASSERT(stack && "[ERROR] 'stack' parameter is NULL");
    STACK_ASSERT(operate && "[ERROR] 'operate' parameter is NULL");

    for (size_t i = 0; i < stack->size; ++i) {
        operate(stack->elements + i, args);
    }
}

#endif

#endif // STACK_H
