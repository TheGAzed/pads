# SEQUENTIAL DATA STRUCTURES

Sequential data structures are structures where the element can be inserted and removed in a sequence.

## List of structures:

<details>

<summary style="font-size: 1.25em; font-weight: bold">STACK</summary>

The stack is a last element in and first out data structure that can be customized using the preprocessor.

```c++
// macro settings to define stack properties before including library
#define STACK_DATA_TYPE [type]   // defines the data type to store
#define STACK_SIZE      [size]   // defines the maximum positive array size
#define STACK_ASSERT    [assert] // defines the assert function for invalid states
#include "stack.h"
```

The stack structure is made out of the array that stores the elements and a size variable to get the current element count.

```c++
typedef struct stack {
    STACK_DATA_TYPE elements[STACK_SIZE]; // elements array
    size_t size;                          // size of stack
} stack_s;
```

### Create

Creates an empty stack structure.

```c++
stack_s create_stack(void);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    return 0;
}
```

### Destroy

Destroys stack and all elements in it.

```c++
typedef void (*destroy_stack_fn) (STACK_DATA_TYPE * element);
void destroy_stack(stack_s * stack, const destroy_stack_fn destroy);
```

```c++
#define STACK_DATA_TYPE char*
#include "stack.h"

#include <stdlib.h>

void destroy_string(STACK_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    destroy_stack(&stack, destroy_string);
    
    return 0;
}
```

### Clear

Clears all elements in stack.

```c++
typedef void (*destroy_stack_fn) (STACK_DATA_TYPE * element);
void clear_stack(stack_s * stack, const destroy_stack_fn destroy);
```

```c++
#define STACK_DATA_TYPE char*
#include "stack.h"

#include <stdlib.h>

void destroy_string(STACK_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    clear_stack(&stack, destroy_string);
    
    // do something anew
    
    destroy_stack(&stack, destroy_string);
    
    return 0;
}
```

### Is empty

Checks if stack is empty.

```c++
bool is_empty_stack(const stack_s * stack);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    while (!is_empty_stack(&stack)) {
        // do something while stack is not empty
    }

    return 0;
}
```

### Is full

Checks if stack is full.

```c++
bool is_full_stack(const stack_s * stack);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

int main() {
    stack_s stack = create_stack();
        
    while (!is_full_stack(&stack)) {
        // do something while stack is not full
    }

    return 0;
}
```

### Peep

Gets element at the top of the stack without removing it.

```c++
STACK_DATA_TYPE peep_stack(const stack_s * stack);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    STACK_DATA_TYPE element = peep_stack(&stack);
    
    // do something with top element

    return 0;
}
```

### Push

Pushes the element to the top of the stack.

```c++
void push_stack(stack_s * stack, const STACK_DATA_TYPE element);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

int main() {
    stack_s stack = create_stack();
    
    STACK_DATA_TYPE element = { 0 };
    push_stack(&stack, element);
    
    // do something

    return 0;
}
```

### Pop

Pops and removes the element at the top of the stack.

```c++
STACK_DATA_TYPE pop_stack(stack_s * stack);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    STACK_DATA_TYPE element = pop_stack(&stack);
    
    // do something with removed element

    return 0;
}
```

### Copy

Copies the stack and all its elements into a new structure.

```c++
typedef STACK_DATA_TYPE (*copy_stack_fn) (const STACK_DATA_TYPE element);
stack_s copy_stack(const stack_s * stack, const copy_stack_fn copy);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

STACK_DATA_TYPE copy_int(const STACK_DATA_TYPE integer) {
    return integer;
}

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    stack_s copy = copy_stack(&stack, copy_int);
    
    // do something with stack and copy

    return 0;
}
```

### Foreach

Iterates over and operates on each element in structure using generic arguments.

```c++
typedef bool (*operate_stack_fn) (STACK_DATA_TYPE * element, void * args);
void foreach_stack(stack_s * stack, const operate_stack_fn operate, void * args);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

bool increment(STACK_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    int value = 42;
    foreach_stack(&stack, increment, &value);
    
    // do something with incremented stack elements

    return 0;
}
```

### Map

Map function that maps elements into array and manages it using size and args.

```c++
void (*manage_stack_fn) (STACK_DATA_TYPE * array, const size_t size, void * args);
void map_stack(stack_s * stack, const manage_stack_fn manage, void * args);
```

```c++
#define STACK_DATA_TYPE int
#include "stack.h"

#include <stdlib.h>

int compare_int(const void * a, const void * b) {
    return (*(STACK_DATA_TYPE*)(a)) - (*(STACK_DATA_TYPE*)(b));
}

void sort_int(STACK_DATA_TYPE * array, const size_t size, void * compare) {
    qsort(array, size, sizeof(STACK_DATA_TYPE), compare);
}

int main() {
    stack_s stack = create_stack();
    
    // do something
    
    map_stack(&stack, sort_int, compare_int);
    
    // do something with sorted stack elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.25em; font-weight: bold">QUEUE</summary>

The queue is a first element in and first out data structure that can be customized using the preprocessor.

```c++
// macro settings to define queue properties before including library
#define QUEUE_DATA_TYPE [type]   // defines the data type to store
#define QUEUE_SIZE      [size]   // defines the maximum positive array size
#define QUEUE_ASSERT    [assert] // defines the assert function for invalid states
#include "queue.h"
```

The queue structure is made out of the array that stores the elements, a size variable to get the current element count and a current index to retrieve the first added element. The structure relies on a circular array mechanism.

```c++
typedef struct queue {
    QUEUE_DATA_TYPE elements[QUEUE_SIZE]; // elements array
    size_t size;                          // size of structure
    size_t current;                       // current index of first element
} queue_s;

```

### Create

Creates an empty queue structure.

```c++
queue_s create_queue(void);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    return 0;
}
```

### Destroy

Destroys queue and all elements in it.

```c++
typedef void (*destroy_queue_fn) (QUEUE_DATA_TYPE * element);
void destroy_queue(queue_s * queue, const destroy_queue_fn destroy);
```

```c++
#define QUEUE_DATA_TYPE char*
#include "queue.h"

#include <stdlib.h>

void destroy_string(QUEUE_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    destroy_queue(&queue, destroy_string);
    
    return 0;
}
```

### Clear

Clears all elements in queue.

```c++
typedef void (*destroy_queue_fn) (QUEUE_DATA_TYPE * element);
void clear_queue(queue_s * queue, const destroy_queue_fn destroy);
```

```c++
#define QUEUE_DATA_TYPE char*
#include "queue.h"

#include <stdlib.h>

void destroy_string(QUEUE_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    clear_queue(&queue, destroy_string);
    
    // do something anew
    
    destroy_queue(&queue, destroy_string);
    
    return 0;
}
```

### Is empty

Checks if queue is empty.

```c++
bool is_empty_queue(const queue_s * queue);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    while (!is_empty_queue(&queue)) {
        // do something while queue is not empty
    }

    return 0;
}
```

### Is full

Checks if queue is full.

```c++
bool is_full_queue(const queue_s * queue);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

int main() {
    queue_s queue = create_queue();
        
    while (!is_full_queue(&queue)) {
        // do something while queue is not full
    }

    return 0;
}
```

### Peek

Gets element at the beginning of the queue without removing it.

```c++
QUEUE_DATA_TYPE peek_queue(const queue_s * queue);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    QUEUE_DATA_TYPE element = peek_queue(&queue);
    
    // do something with top element

    return 0;
}
```

### Enqueue

Enqueues the element to the end of the queue.

```c++
void enqueue_queue(queue_s * queue, const QUEUE_DATA_TYPE element);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

int main() {
    queue_s queue = create_queue();
    
    QUEUE_DATA_TYPE element = { 0 };
    enqueue_queue(&queue, element);
    
    // do something

    return 0;
}
```

### Dequeue

Dequeues and removes the element at the beginning of the queue.

```c++
QUEUE_DATA_TYPE dequeue_queue(queue_s * queue);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    QUEUE_DATA_TYPE element = dequeue_queue(&queue);
    
    // do something with removed element

    return 0;
}
```

### Copy

Copies the queue and all its elements into a new structure.

```c++
typedef QUEUE_DATA_TYPE (*copy_queue_fn) (const QUEUE_DATA_TYPE element);
queue_s copy_queue(const queue_s * queue, const copy_queue_fn copy);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

QUEUE_DATA_TYPE copy_int(const QUEUE_DATA_TYPE integer) {
    return integer;
}

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    queue_s copy = copy_queue(&queue, copy_int);
    
    // do something with queue and copy

    return 0;
}
```

### Foreach

Iterates over and operates on each element in structure using generic arguments.

```c++
typedef bool (*operate_queue_fn) (QUEUE_DATA_TYPE * element, void * args);
void foreach_queue(queue_s * queue, const operate_queue_fn operate, void * args);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

bool increment(QUEUE_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    int value = 42;
    foreach_queue(&queue, increment, &value);
    
    // do something with incremented queue elements

    return 0;
}
```

### Map

Map function that maps elements into array and manages it using size and args.

```c++
void (*manage_queue_fn) (QUEUE_DATA_TYPE * array, const size_t size, void * args);
void map_queue(queue_s * queue, const manage_queue_fn manage, void * args);
```

```c++
#define QUEUE_DATA_TYPE int
#include "queue.h"

#include <stdlib.h>

int compare_int(const void * a, const void * b) {
    return (*(QUEUE_DATA_TYPE*)(a)) - (*(QUEUE_DATA_TYPE*)(b));
}

void sort_int(QUEUE_DATA_TYPE * array, const size_t size, void * compare) {
    qsort(array, size, sizeof(QUEUE_DATA_TYPE), compare);
}

int main() {
    queue_s queue = create_queue();
    
    // do something
    
    map_queue(&queue, sort_int, compare_int);
    
    // do something with sorted queue elements

    return 0;
}
```

</details>
