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
Defines the function that should be called when an assertion or condition fails. If no function is defined then assert.h will be included and ```assert()``` will be used instead.

```C
#define STACK_REALLOC [reallocate] // default 'realloc'
```
Defines the reallocate function that should be called when a memory chunk needs to be changed or created. If no reallocate is defined then stdlib.h will be included and ```realloc()``` will be used.

```C
#define STACK_FREE [free] // default 'free'
#include "stack.h"
```
Defines the free function that should be called when a memory chunk needs to be freed/removed. If no free is defined then stdlib.h will be included and ```free()``` will be used.

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
