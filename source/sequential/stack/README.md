# [STACK](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

The stack is a last in first out (LIFO) data structure. Here it is made in four implementation modes each defined by a special value.

### List of special modes and their values:

```C
#define INFINITE_LIST_STACK_MODE       1 // infinite linked list mode
#define FINITE_ALLOCATED_STACK_MODE    2 // finite preallocated memory mode
#define INFINITE_REALLOC_STACK_MODE    3 // infinite re-allocatable mode
#define FINITE_PREPROCESSOR_STACK_MODE 4 // finite preprocessor defined mode
```

The implementation also includes the following macros that can be used by other modes:

### List of special stack macros:

> [!WARNING]
> Each stack and mode macro mentioned below must be defined before including the stack header.

```C
#define STACK_DATA_TYPE [type] // default '(void*)'
#include "stack.h"
```
Defines the element type to use in stack.

```C
#define STACK_ASSERT [assert] // default 'assert'
#include "stack.h"
```
Defines the function that should be called when an assertion or condition fails. If no function is defined then ```assert.h``` will be included and ```assert()``` will be used instead.

```C
#define STACK_REALLOC [reallocate] // default 'realloc'
#define STACK_FREE [free] // default 'free'
#include "stack.h" // will generate error if both are not defined
```
Defines the reallocate and free functions that should be called when a memory chunk needs to be changed, created or freed. If no reallocate is defined then ```stdlib.h``` will be included and ```realloc()``` will be used. If no free is defined then stdlib.h will be included and ```free()``` will be used.


> [!WARNING]
> If either ```STACK_REALLOC``` or ```STACK_FREE``` is newly defined then the other MUST also be defined.

> [!NOTE]
> The finite preprocessor defined mode DOES NOT use memory allocation. Thus, it is unnecessary to define a new ```STACK_REALLOC``` and ```STACK_FREE``` for it.

```C
#define STACK_MODE [mode] // default 'INFINITE_REALLOC_STACK_MODE'
#include "stack.h"
```
Defines the mode from the specified list of available stack modes.

## 1. Infinite linked list mode

The infinite list mode is a mode of the stack.h file which uses a linked list of a predefined array of element nodes.

```C
struct stack_list_array {
    STACK_DATA_TYPE elements[LIST_ARRAY_STACK_CHUNK]; // array to store elements
    struct stack_list_array * next;                   // next linked list array
};

typedef struct stack {
    struct stack_list_array * head; // head list element with the top of the stack
    size_t size;                    // size of stack
} stack_s;
```

### List node array size
The mode itself comes with a macro to specify the chunk size of elements to use for each list node.

```C
#define LIST_ARRAY_STACK_CHUNK [size] // default '(1 << 5)' or 32
#define STACK_MODE INFINITE_LIST_STACK_MODE
#include "stack.h"
```

## 2. Finite pre-allocated memory mode

The finite pre-allocated list is a mode of the stack.h file which uses an array of elements to store them next to each other from index 0.

```C
typedef struct stack {
    STACK_DATA_TYPE * elements; // pointer to allocated memory
    size_t max, size;           // current stack size and maximum size
} stack_s;
```

```C
#define STACK_MODE FINITE_ALLOCATED_STACK_MODE
#include "stack.h"
```

## 3. Infinite re-allocatable mode

The infinite pre-allocated mode is a mode of the stack.h file which uses a expandable array of elements to store them next to each other from index 0.

```C
typedef struct stack {
    size_t size;                // size of stack
    STACK_DATA_TYPE * elements; // pointer to array of elements
} stack_s;
```

### Expand array if capacity is reached macros
The mode comes with two macros where one can be used to check if the stack size has reached its capacity and the other to get the next capacity to reallocate and expand.

```C
#define IS_CAPACITY_STACK(size) [check size] // default below
#define EXPAND_CAPACITY_STACK(capacity) [expand capacity] // default below
#define STACK_MODE INFINITE_REALLOC_STACK_MODE
#include "stack.h"
```

### Linear expansion size
The default macros expand the stack linearly using the predefined macro value:
```C
// chunk used to expand reached stack capacity size
#define REALLOC_STACK_CHUNK [size] // default '(1 << 5)' or 32
#define STACK_MODE INFINITE_REALLOC_STACK_MODE
#include "stack.h"

// IS_CAPACITY_STACK and EXPAND_CAPACITY_STACK default
// #define IS_CAPACITY_STACK(size) (!((size) % REALLOC_STACK_CHUNK))
// #define EXPAND_CAPACITY_STACK(capacity) ((capacity) + REALLOC_STACK_CHUNK)
```

> [!WARNING]
> If either ```IS_CAPACITY_STACK``` or ```EXPAND_CAPACITY_STACK``` is defined then the other MUST also be defined.

## 4. Finite preprocessor defined mode

The finite preprocessor stack is a mode of the stack.h file which uses a predefined array of elements to store them next to each other from index 0.

```C
typedef struct stack {
    STACK_DATA_TYPE elements[PREPROCESSOR_STACK_SIZE]; // elements array
    size_t size;                                       // size of stack
} stack_s;
```
### Predefine size of elements array

```C
// predefiend size of stack's elements array
#define PREPROCESSOR_STACK_SIZE [size] // default '(1 << 5)' or 32
#define STACK_MODE FINITE_PREPROCESSOR_STACK_MODE
#include "stack.h"
```
## Main Functionality

### create_stack

```C
stack_s create_stack(void);
stack_s create_stack(size_t max); // in FINITE_ALLOCATED_STACK_MODE
```

The create stack function is used to create and return a new empty stack. It may use a maximum size parameter when in ```FINITE_ALLOCATED_STACK_MODE``` mode.

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();
    
    /* do something with created stack */
    
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### destroy_stack

```C
typedef void (*destroy_stack_fn) (STACK_DATA_TYPE *);
void destroy_stack(stack_s * stack, const destroy_stack_fn destroy);
```

The destroy stack function destroys a stack and all its elements using the ```destroy``` function pointer parameter. After the function is called the specified stack may not be used and ```create_stack()``` needs to be called again.

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();
    
    /* do something with stack */
    
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### clear_stack

```C
typedef void (*destroy_stack_fn) (STACK_DATA_TYPE *);
void clear_stack(stack_s * stack, const destroy_stack_fn destroy);
```

The clear stack function, similar to destroy counterpart, destroys a stack and all its elements using the ```destroy``` function pointer parameter. After the function is called however, the specified stack is only emptied and can still be used.

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();
    
    /* do something with stack */
    
    clear_stack(&stack, destroy_element);
  
    /* do some other thing with emptied stack */
    
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### copy_stack

```C
typedef STACK_DATA_TYPE (*copy_stack_fn) (const STACK_DATA_TYPE);
void copy_stack(const stack_s stack, const copy_stack_fn copy);
```

The copy stack function creates a replica of the specified stack and all its elements using the copy function pointer. The function pointer allows for the ability to create both deep and shallow copies of elements.

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

STACK_DATA_TYPE copy_element(const STACK_DATA_TYPE element) {
    STACK_DATA_TYPE copy = element;
    
    /* create a deep or shallow copy of element */
    
    return copy;
}

int main(void) {
    stack_s stack = create_stack();
    
    /* do something with stack */
    
    stack_s copy = copy_stack(stack, copy_element);
  
    /* do something with both stack and its copy */
    
    destroy_stack(&stack, destroy_element);
    destroy_stack(&copy, destroy_element);
    
    return 0;
}
```

### foreach_stack

```C
typedef bool (*operate_stack_fn) (STACK_DATA_TYPE *, void *);
void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args);
```

The foreach stack function simulates a for loop that iterates over each element in stack from top to bottom. It calls the ```operate``` function pointer on each element reference together with the specified generic arguments. If ```operate``` returns ```true``` the iteration continues, else it breaks.

```C
#include <stdio.h> // import printf

#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

bool print_element(STACK_DATA_TYPE * element, void * format) {
    printf(format, (*element));
    
    return true;
}

int main(void) {
    stack_s stack = create_stack();
    
    /* do something with stack */
    
    // prints stack elements from top to bottom
    foreach_stack(&stack, print_element, "%d\n");
    
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### map_stack

```C
typedef void (*manage_stack_fn) (STACK_DATA_TYPE *, const size_t, void *);
void map_stack(stack_s const * stack, const manage_stack_fn manage, void * args);
```

The map stack function maps a stack into an array and back with top being last. It then calls a ```manage``` function pointer to manage all elements using stack's size and generic arguments. The created array gets freed at the end of the map function.

```C
#include <stdlib.h> // import qsort
#include <string.h> // import memcmp

#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();
    
    /* do something with stack */
    
    // sorts stack elements with top being the last one
    map_stack(&stack, sort_elements, compare_elements);
    
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### is_empty_stack

```C
bool is_empty_stack(const stack_s stack);
```

The is empty stack function checks if the stack has no elements stored.

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();

    /* do something with stack */
    
    while (!is_empty_stack(stack)) {
        /* do something with stack while it isn't empty */
    }
    
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### is_full_stack

```C
bool is_full_stack(const stack_s stack);
```

The is full stack function checks if the stack can't store any more elements. In the case of infinite mode stacks the function checks if the stack size value will overflow before push.

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();

    /* do something with stack */
    
    while (!is_full_stack(stack)) {
        /* do something with stack while it is not full */
    }
    
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### push_stack

```C
void push_stack(stack_s * stack, const STACK_DATA_TYPE element);
```

The push stack function pushes an element to the top of the specified stack.

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();

    /* do something with stack */
    
    push_stack(&stack, 42);
    
    /* do something with stack and 42 at its top */
        
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### peep_stack

```C
STACK_DATA_TYPE peep_stack(const stack_s stack);
```

The peep stack function gets the element at the top of the stack without removing it. 

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();

    /* do something with stack */
    
    if (42 == peep_stack(stack)) {
        /* do something with unchanged stack when top element is 42 */
    }
        
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```

### pop_stack

```C
STACK_DATA_TYPE pop_stack(stack_s * stack);
```

The pop stack function gets and removes the element at the top of the stack. 

```C
#define STACK_DATA_TYPE int
#include "stack.h"

void destroy_element(STACK_DATA_TYPE * element) {
    /* destroy or free the element */
}

int main(void) {
    stack_s stack = create_stack();

    /* do something with stack */
    
    STACK_DATA_TYPE removed = pop_stack(&stack);
    if (42 == removed) {
        /* do something with stack when top removed element is 42 */
    }
        
    destroy_stack(&stack, destroy_element);
    
    return 0;
}
```
