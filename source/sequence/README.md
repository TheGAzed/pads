# SEQUENTIAL DATA STRUCTURES

Sequential data structures are structures where the element can be inserted and removed in a sequence.

<details>

<summary style="font-size: 2em; font-weight: bold">STACK</summary>

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

<details>

<summary style="font-size: 1.5em;">create</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">destroy</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">clear</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">copy</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">is empty</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">is full</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">foreach</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">map</summary>

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

<summary style="font-size: 1.5em;">peep</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">push</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">pop</summary>

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

</details>

</details>

<details>

<summary style="font-size: 2em; font-weight: bold">QUEUE</summary>

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

<details>

<summary style="font-size: 1.5em;">create</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">destroy</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">clear</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">copy</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">is empty</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">is full</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">foreach</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">map</summary>

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

<details>

<summary style="font-size: 1.5em;">peek</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">enqueue</summary>

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

</details>

<details>

<summary style="font-size: 1.5em;">dequeue</summary>

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

</details>

</details>

<details>

<summary style="font-size: 2em; font-weight: bold">DEQUE</summary>

The deque is a double ended queue that allows elements to be added and removed from its front and rear. It can be customized using the preprocessor.

```c++
// macro settings to define deque properties before including library
#define DEQUE_DATA_TYPE [type]   // defines the data type to store
#define DEQUE_SIZE      [size]   // defines the maximum positive array size
#define DEQUE_ASSERT    [assert] // defines the assert function for invalid states
#include "deque.h"
```

The deque structure is made out of the array that stores the elements, a size variable to get the element count and a current index to retrieve the rear element. The structure relies on a circular array mechanism.

```c++
typedef struct deque {
    DEQUE_DATA_TYPE elements[DEQUE_SIZE]; // elements array
    size_t size;                          // size of structure
    size_t current;                       // current index of first element
} deque_s;

```

<details>

<summary style="font-size: 1.5em;">create</summary>

Creates an empty deque structure.

```c++
deque_s create_deque(void);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">destroy</summary>

Destroys deque and all elements in it.

```c++
typedef void (*destroy_deque_fn) (DEQUE_DATA_TYPE * element);
void destroy_deque(deque_s * deque, const destroy_deque_fn destroy);
```

```c++
#define DEQUE_DATA_TYPE char*
#include "deque.h"

#include <stdlib.h>

void destroy_string(DEQUE_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    destroy_deque(&deque, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">clear</summary>

Clears all elements in deque.

```c++
typedef void (*destroy_deque_fn) (DEQUE_DATA_TYPE * element);
void clear_deque(deque_s * deque, const destroy_deque_fn destroy);
```

```c++
#define DEQUE_DATA_TYPE char*
#include "deque.h"

#include <stdlib.h>

void destroy_string(DEQUE_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    clear_deque(&deque, destroy_string);
    
    // do something anew
    
    destroy_deque(&deque, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">copy</summary>

Copies the deque and all its elements into a new structure.

```c++
typedef DEQUE_DATA_TYPE (*copy_deque_fn) (const DEQUE_DATA_TYPE element);
deque_s copy_deque(const deque_s * deque, const copy_deque_fn copy);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

DEQUE_DATA_TYPE copy_int(const DEQUE_DATA_TYPE integer) {
    return integer;
}

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    deque_s copy = copy_deque(&deque, copy_int);
    
    // do something with deque and copy

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is empty</summary>

Checks if deque is empty.

```c++
bool is_empty_deque(const deque_s * deque);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    while (!is_empty_deque(&deque)) {
        // do something while deque is not empty
    }

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is full</summary>

Checks if deque is full.

```c++
bool is_full_deque(const deque_s * deque);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
        
    while (!is_full_deque(&deque)) {
        // do something while deque is not full
    }

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">foreach front</summary>

Iterates over and operates on each element in structure using generic arguments from the front.

```c++
typedef bool (*operate_deque_fn) (DEQUE_DATA_TYPE * element, void * args);
void foreach_front_deque(deque_s * deque, const operate_deque_fn operate, void * args);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

bool increment(DEQUE_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    int value = 42;
    foreach_front_deque(&deque, increment, &value);
    
    // do something with incremented deque elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">foreach rear</summary>

Iterates over and operates on each element in structure using generic arguments from the rear.

```c++
typedef bool (*operate_deque_fn) (DEQUE_DATA_TYPE * element, void * args);
void foreach_rear_deque(deque_s * deque, const operate_deque_fn operate, void * args);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

bool increment(DEQUE_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    int value = 42;
    foreach_rear_deque(&deque, increment, &value);
    
    // do something with incremented deque elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">map</summary>

Map function that maps elements into array and manages it using size and args.

```c++
void (*manage_deque_fn) (DEQUE_DATA_TYPE * array, const size_t size, void * args);
void map_deque(deque_s * deque, const manage_deque_fn manage, void * args);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

#include <stdlib.h>

int compare_int(const void * a, const void * b) {
    return (*(DEQUE_DATA_TYPE*)(a)) - (*(DEQUE_DATA_TYPE*)(b));
}

void sort_int(DEQUE_DATA_TYPE * array, const size_t size, void * compare) {
    qsort(array, size, sizeof(DEQUE_DATA_TYPE), compare);
}

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    map_deque(&deque, sort_int, compare_int);
    
    // do something with sorted deque elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">peek front</summary>

Gets element at the front of the deque without removing it.

```c++
DEQUE_DATA_TYPE peek_front_deque(const deque_s * deque);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    DEQUE_DATA_TYPE element = peek_front_deque(&deque);
    
    // do something with top element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">peek rear</summary>

Gets element at the rear of the deque without removing it.

```c++
DEQUE_DATA_TYPE peek_rear_deque(const deque_s * deque);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    DEQUE_DATA_TYPE element = peek_rear_deque(&deque);
    
    // do something with top element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">enqueue front</summary>

Enqueue the element to the front of the deque.

```c++
void enqueue_front_deque(deque_s * deque, const DEQUE_DATA_TYPE element);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    DEQUE_DATA_TYPE element = { 0 };
    enqueue_front_deque(&deque, element);
    
    // do something

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">enqueue rear</summary>

Enqueue the element to the rear of the deque.

```c++
void enqueue_rear_deque(deque_s * deque, const DEQUE_DATA_TYPE element);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    DEQUE_DATA_TYPE element = { 0 };
    enqueue_rear_deque(&deque, element);
    
    // do something

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">dequeue front</summary>

Dequeues and removes the element at the front of the deque.

```c++
DEQUE_DATA_TYPE dequeue_front_deque(deque_s * deque);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    DEQUE_DATA_TYPE element = dequeue_front_deque(&deque);
    
    // do something with removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">dequeue rear</summary>

Dequeues and removes the element at the rear of the deque.

```c++
DEQUE_DATA_TYPE dequeue_rear_deque(deque_s * deque);
```

```c++
#define DEQUE_DATA_TYPE int
#include "deque.h"

int main() {
    deque_s deque = create_deque();
    
    // do something
    
    DEQUE_DATA_TYPE element = dequeue_rear_deque(&deque);
    
    // do something with removed element

    return 0;
}
```

</details>

</details>
