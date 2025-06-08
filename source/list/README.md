# LIST DATA STRUCTURES

List data structures are structures where each node contains an element and reference to its next neighbours.

<details>

<summary style="font-size: 2em; font-weight: bold">STRAIGHT LIST</summary>

The straight list is a simple array based linked list implementation where each node only points to its next neighbor until an end is reached.

```c++
// macro settings to define straight list properties before including library
#define STRAIGHT_LIST_DATA_TYPE [type]   // defines the data type to store
#define STRAIGHT_LIST_SIZE      [size]   // defines the maximum positive array size
#define STRAIGHT_LIST_ASSERT    [assert] // defines the assert function for invalid states
#include "straight_list.h"
```

The straight list is made out of an elements array and another next indexes array that maps to each element. Apart from the list size the structure also has a head index variable. Underneath the structure relies on a linked list based stack implementation to save removed empty indexes, or holes.

```c++
typedef struct straight_list {
    STRAIGHT_LIST_DATA_TYPE elements[STRAIGHT_LIST_SIZE]; // array to store elements
    size_t next[STRAIGHT_LIST_SIZE]; // array to store next indexes
    size_t size, head; // list size and head index parameter
    size_t empty_size, empty_head; // empty stack's size and head
} straight_list_s;
```

<details>

<summary style="font-size: 1.5em;">create</summary>

Creates an empty list structure.

```c++
straight_list_s create_straight_list(void);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">destroy</summary>

Destroys list and all elements in it.

```c++
typedef void (*destroy_straight_list_fn) (STRAIGHT_LIST_DATA_TYPE * element);
void destroy_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE char*
#include "straight_list.h"

#include <stdlib.h>

void destroy_string(STRAIGHT_LIST_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    destroy_straight_list(&list, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">clear</summary>

Clears all elements in list.

```c++
typedef void (*destroy_straight_list_fn) (STRAIGHT_LIST_DATA_TYPE * element);
void clear_straight_list(straight_list_s * list, const destroy_straight_list_fn destroy);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE char*
#include "straight_list.h"

#include <stdlib.h>

void destroy_string(STRAIGHT_LIST_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    clear_straight_list(&list, destroy_string);
    
    // do something anew
    
    destroy_straight_list(&list, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">copy</summary>

Copies the list and all its elements into a new structure.

```c++
typedef STRAIGHT_LIST_DATA_TYPE (*copy_straight_list_fn) (const STRAIGHT_LIST_DATA_TYPE element);
straight_list_s copy_straight_list(const straight_list_s * list, const copy_straight_list_fn copy);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

STRAIGHT_LIST_DATA_TYPE copy_int(const STRAIGHT_LIST_DATA_TYPE integer) {
    return integer;
}

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    straight_list_s copy = copy_straight_list(&list, copy_int);
    
    // do something with list and copy

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is empty</summary>

Checks if list is empty.

```c++
bool is_empty_straight_list(const straight_list_s * list);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    while (!is_empty_straight_list(&list)) {
        // do something while list is not empty
    }

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is full</summary>

Checks if list is full.

```c++
bool is_full_straight_list(const straight_list_s * list);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
        
    while (!is_full_straight_list(&list)) {
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
typedef bool (*operate_straight_list_fn) (STRAIGHT_LIST_DATA_TYPE * element, void * args);
void foreach_straight_list(straight_list_s * list, const operate_straight_list_fn operate, void * args);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

bool increment(STRAIGHT_LIST_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    int value = 42;
    foreach_straight_list(&list, increment, &value);
    
    // do something with incremented straight_list elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">map</summary>

Map function that maps elements into array and manages it using size and args.

```c++
void (*manage_straight_list_fn) (STRAIGHT_LIST_DATA_TYPE * array, const size_t size, void * args);
void map_straight_list(straight_list_s * list, const manage_straight_list_fn manage, void * args);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

#include <stdlib.h>

int compare_int(const void * a, const void * b) {
    return (*(STRAIGHT_LIST_DATA_TYPE*)(a)) - (*(STRAIGHT_LIST_DATA_TYPE*)(b));
}

void sort_int(STRAIGHT_LIST_DATA_TYPE * array, const size_t size, void * compare) {
    qsort(array, size, sizeof(STRAIGHT_LIST_DATA_TYPE), compare);
}

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    map_straight_list(&list, sort_int, compare_int);
    
    // do something with sorted straight_list elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">insert at</summary>

Inserts element at index position less than or equal to list's size.

```c++
void insert_at_straight_list(straight_list_s * list, const size_t index, const STRAIGHT_LIST_DATA_TYPE element);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
    
    STRAIGHT_LIST_DATA_TYPE element = { 0 };
    insert_at_straight_list(&list, 0, element);
    
    // do something
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">get</summary>

Gets element at index position less than list's size without removing it.

```c++
STRAIGHT_LIST_DATA_TYPE get_straight_list(const straight_list_s * list, const size_t index);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
        
    STRAIGHT_LIST_DATA_TYPE element = get_straight_list(&list, 0);
    
    // do something with element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">remove first</summary>

Removes first instance of element based on zero equal comparison.
Returns false assertion and exit failure if no element is found.

```c++
typedef int (*compare_straight_list_fn) (const STRAIGHT_LIST_DATA_TYPE one, const STRAIGHT_LIST_DATA_TYPE two);
STRAIGHT_LIST_DATA_TYPE remove_first_straight_list(straight_list_s * list, const STRAIGHT_LIST_DATA_TYPE element, const compare_straight_list_fn compare);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int compare_int(const STRAIGHT_LIST_DATA_TYPE a, const STRAIGHT_LIST_DATA_TYPE b) {
    return a - b;
}

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    STRAIGHT_LIST_DATA_TYPE element = { 0 };
    STRAIGHT_LIST_DATA_TYPE removed = remove_first_straight_list(&list, element);
    
    // do something with removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">remove at</summary>

Removes element at index less than list's size.

```c++
STRAIGHT_LIST_DATA_TYPE remove_at_straight_list(straight_list_s * list, const size_t index);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    STRAIGHT_LIST_DATA_TYPE removed = remove_at_straight_list(&list, 0);
    
    // do something with first removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">reverse</summary>

Reverses list (I mean, yeah).

```c++
void reverse_straight_list(straight_list_s * list);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    reverse_straight_list(&list);
    
    // do something with reversed list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">splice</summary>

Splices source into destination list while clearing source list.

```c++
void splice_straight_list(straight_list_s * restrict destination, straight_list_s * restrict source, const size_t index);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s one = create_straight_list();
    straight_list_s two = create_straight_list();
    
    // do something
    
    splice_straight_list(&one, &two, one.size); // one's size to concatenate
    
    // do something with concatenated or empty list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">split</summary>

Splits list and returns smaller list based on index less than list's size and new size.

```c++
straight_list_s split_straight_list(straight_list_s * list, const size_t index, const size_t size);
```

```c++
#define STRAIGHT_LIST_DATA_TYPE int
#include "straight_list.h"

int main() {
    straight_list_s list = create_straight_list();
    
    // do something
    
    straight_list_s split = split_straight_list(&list, 0, list.size / 2); // halve list
    
    // do something with first and second half

    return 0;
}
```

</details>

</details>

<details>

<summary style="font-size: 2em; font-weight: bold">CIRCULAR LIST</summary>

The circular list is a simple array based circular linked list implementation where each node points to its next neighbor and then reverts back to the beginning.

```c++
// macro settings to define circular list properties before including library
#define CIRCULAR_LIST_DATA_TYPE [type]   // defines the data type to store
#define CIRCULAR_LIST_SIZE      [size]   // defines the maximum positive array size
#define CIRCULAR_LIST_ASSERT    [assert] // defines the assert function for invalid states
#include "circular_list.h"
```

The circular list is made out of an elements array and another next indexes array that maps to each element. Apart from the list size the structure also has a tail index to guarantee faster element appending to its end. Underneath the structure relies on a linked list based stack implementation to save removed empty indexes, or holes.

```c++
typedef struct circular_list {
    size_t next[CIRCULAR_LIST_SIZE];
    size_t size, tail; // list size and tail index parameter
    size_t empty_size, empty_head; // empty stack's size and head
    CIRCULAR_LIST_DATA_TYPE elements[CIRCULAR_LIST_SIZE];
} circular_list_s;
```

<details>

<summary style="font-size: 1.5em;">create</summary>

Creates an empty list structure.

```c++
circular_list_s create_circular_list(void);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">destroy</summary>

Destroys list and all elements in it.

```c++
typedef void (*destroy_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE * element);
void destroy_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE char*
#include "circular_list.h"

#include <stdlib.h>

void destroy_string(CIRCULAR_LIST_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    destroy_circular_list(&list, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">clear</summary>

Clears all elements in list.

```c++
typedef void (*destroy_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE * element);
void clear_circular_list(circular_list_s * list, const destroy_circular_list_fn destroy);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE char*
#include "circular_list.h"

#include <stdlib.h>

void destroy_string(CIRCULAR_LIST_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    clear_circular_list(&list, destroy_string);
    
    // do something anew
    
    destroy_circular_list(&list, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">copy</summary>

Copies the list and all its elements into a new structure.

```c++
typedef CIRCULAR_LIST_DATA_TYPE (*copy_circular_list_fn) (const CIRCULAR_LIST_DATA_TYPE element);
circular_list_s copy_circular_list(const circular_list_s * list, const copy_circular_list_fn copy);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

CIRCULAR_LIST_DATA_TYPE copy_int(const CIRCULAR_LIST_DATA_TYPE integer) {
    return integer;
}

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    circular_list_s copy = copy_circular_list(&list, copy_int);
    
    // do something with list and copy

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is empty</summary>

Checks if list is empty.

```c++
bool is_empty_circular_list(const circular_list_s * list);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    while (!is_empty_circular_list(&list)) {
        // do something while list is not empty
    }

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is full</summary>

Checks if list is full.

```c++
bool is_full_circular_list(const circular_list_s * list);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
        
    while (!is_full_circular_list(&list)) {
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
typedef bool (*operate_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE * element, void * args);
void foreach_circular_list(circular_list_s * list, const operate_circular_list_fn operate, void * args);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

bool increment(CIRCULAR_LIST_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    int value = 42;
    foreach_circular_list(&list, increment, &value);
    
    // do something with incremented circular_list elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">map</summary>

Map function that maps elements into array and manages it using size and args.

```c++
void (*manage_circular_list_fn) (CIRCULAR_LIST_DATA_TYPE * array, const size_t size, void * args);
void map_circular_list(circular_list_s * list, const manage_circular_list_fn manage, void * args);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

#include <stdlib.h>

int compare_int(const void * a, const void * b) {
    return (*(CIRCULAR_LIST_DATA_TYPE*)(a)) - (*(CIRCULAR_LIST_DATA_TYPE*)(b));
}

void sort_int(CIRCULAR_LIST_DATA_TYPE * array, const size_t size, void * compare) {
    qsort(array, size, sizeof(CIRCULAR_LIST_DATA_TYPE), compare);
}

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    map_circular_list(&list, sort_int, compare_int);
    
    // do something with sorted circular_list elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">insert at</summary>

Inserts element at index position less than or equal to list's size.

```c++
void insert_at_circular_list(circular_list_s * list, const size_t index, const CIRCULAR_LIST_DATA_TYPE element);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    CIRCULAR_LIST_DATA_TYPE element = { 0 };
    insert_at_circular_list(&list, 0, element);
    
    // do something
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">get</summary>

Gets element at index position less than list's size without removing it.

```c++
CIRCULAR_LIST_DATA_TYPE get_circular_list(const circular_list_s * list, const size_t index);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
        
    CIRCULAR_LIST_DATA_TYPE element = get_circular_list(&list, 0);
    
    // do something with element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">remove first</summary>

Removes first instance of element based on zero equal comparison.
Returns false assertion and exit failure if no element is found.

```c++
typedef int (*compare_circular_list_fn) (const CIRCULAR_LIST_DATA_TYPE one, const CIRCULAR_LIST_DATA_TYPE two);
CIRCULAR_LIST_DATA_TYPE remove_first_circular_list(circular_list_s * list, const CIRCULAR_LIST_DATA_TYPE element, const compare_circular_list_fn compare);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int compare_int(const CIRCULAR_LIST_DATA_TYPE a, const CIRCULAR_LIST_DATA_TYPE b) {
    return a - b;
}

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    CIRCULAR_LIST_DATA_TYPE element = { 0 };
    CIRCULAR_LIST_DATA_TYPE removed = remove_first_circular_list(&list, element);
    
    // do something with removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">remove at</summary>

Removes element at index less than list's size.

```c++
CIRCULAR_LIST_DATA_TYPE remove_at_circular_list(circular_list_s * list, const size_t index);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    CIRCULAR_LIST_DATA_TYPE removed = remove_at_circular_list(&list, 0);
    
    // do something with first removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">reverse</summary>

Reverses list (I mean, yeah).

```c++
void reverse_circular_list(circular_list_s * list);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    reverse_circular_list(&list);
    
    // do something with reversed list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">shift</summary>

Shifts list to next number of elements.

```c++
void shift_circular_list(circular_list_s * list, const size_t shift);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    shift_circular_list(&list, list.size / 2);
    
    // do something with reversed list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">splice</summary>

Splices source into destination list while clearing source list.

```c++
void splice_circular_list(circular_list_s * restrict destination, circular_list_s * restrict source, const size_t index);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s one = create_circular_list();
    circular_list_s two = create_circular_list();
    
    // do something
    
    splice_circular_list(&one, &two, one.size); // one's size to concatenate
    
    // do something with concatenated or empty list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">split</summary>

Splits list and returns smaller list based on index less than list's size and new size.

```c++
circular_list_s split_circular_list(circular_list_s * list, const size_t index, const size_t size);
```

```c++
#define CIRCULAR_LIST_DATA_TYPE int
#include "circular_list.h"

int main() {
    circular_list_s list = create_circular_list();
    
    // do something
    
    circular_list_s split = split_circular_list(&list, 0, list.size / 2); // halve list
    
    // do something with first and second half

    return 0;
}
```

</details>

</details>

<details>

<summary style="font-size: 2em; font-weight: bold">DOUBLE LIST</summary>

The double list is a simple array based circular doubly linked list implementation where each node points to its next and previous neighbor until it reverts back to the beginning.

```c++
// macro settings to define double list properties before including library
#define DOUBLE_LIST_DATA_TYPE [type]   // defines the data type to store
#define DOUBLE_LIST_SIZE      [size]   // defines the maximum positive array size
#define DOUBLE_LIST_ASSERT    [assert] // defines the assert function for invalid states
#include "double_list.h"
```

The double list is made out of an elements array and another next indexes array that maps to each element. Apart from the list size the structure also has a head index. The structure removes elements by switching them with the last element in the array and properly fixing pointers to guarantee the absence of holes.

```c++
typedef struct double_list {
    size_t node[DOUBLE_LIST_NODE_COUNT][DOUBLE_LIST_SIZE];
    size_t size, head;
    DOUBLE_LIST_DATA_TYPE elements[DOUBLE_LIST_SIZE];
} double_list_s;
```

<details>

<summary style="font-size: 1.5em;">create</summary>

Creates an empty list structure.

```c++
double_list_s create_double_list(void);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">destroy</summary>

Destroys list and all elements in it.

```c++
typedef void (*destroy_double_list_fn) (DOUBLE_LIST_DATA_TYPE * element);
void destroy_double_list(double_list_s * list, const destroy_double_list_fn destroy);
```

```c++
#define DOUBLE_LIST_DATA_TYPE char*
#include "double_list.h"

#include <stdlib.h>

void destroy_string(DOUBLE_LIST_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    destroy_double_list(&list, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">clear</summary>

Clears all elements in list.

```c++
typedef void (*destroy_double_list_fn) (DOUBLE_LIST_DATA_TYPE * element);
void clear_double_list(double_list_s * list, const destroy_double_list_fn destroy);
```

```c++
#define DOUBLE_LIST_DATA_TYPE char*
#include "double_list.h"

#include <stdlib.h>

void destroy_string(DOUBLE_LIST_DATA_TYPE * string) {
    free(*string);
    (*string) = NULL;
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    clear_double_list(&list, destroy_string);
    
    // do something anew
    
    destroy_double_list(&list, destroy_string);
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">copy</summary>

Copies the list and all its elements into a new structure.

```c++
typedef DOUBLE_LIST_DATA_TYPE (*copy_double_list_fn) (const DOUBLE_LIST_DATA_TYPE element);
double_list_s copy_double_list(const double_list_s * list, const copy_double_list_fn copy);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

DOUBLE_LIST_DATA_TYPE copy_int(const DOUBLE_LIST_DATA_TYPE integer) {
    return integer;
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    double_list_s copy = copy_double_list(&list, copy_int);
    
    // do something with list and copy

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is empty</summary>

Checks if list is empty.

```c++
bool is_empty_double_list(const double_list_s * list);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    while (!is_empty_double_list(&list)) {
        // do something while list is not empty
    }

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">is full</summary>

Checks if list is full.

```c++
bool is_full_double_list(const double_list_s * list);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
        
    while (!is_full_double_list(&list)) {
        // do something while stack is not full
    }

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">foreach next</summary>

Iterates over and operates on each element in structure using generic arguments, in proper order.

```c++
typedef bool (*operate_double_list_fn) (DOUBLE_LIST_DATA_TYPE * element, void * args);
void foreach_next_double_list(double_list_s * list, const operate_double_list_fn operate, void * args);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

bool increment(DOUBLE_LIST_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    int value = 42;
    foreach_next_double_list(&list, increment, &value);
    
    // do something with incremented double_list elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">foreach previous</summary>

Iterates over and operates on each element in structure using generic arguments, but in reverse order.

```c++
typedef bool (*operate_double_list_fn) (DOUBLE_LIST_DATA_TYPE * element, void * args);
void foreach_prev_double_list(double_list_s * list, const operate_double_list_fn operate, void * args);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

bool increment(DOUBLE_LIST_DATA_TYPE * integer, void * value) {
    int * true_value = value;
    (*integer) += (*true_value);
    
    return true; // to iterate over each element
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    int value = 42;
    foreach_prev_double_list(&list, increment, &value);
    
    // do something with incremented double_list elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">map</summary>

Map function that maps elements into array and manages it using size and args.

```c++
void (*manage_double_list_fn) (DOUBLE_LIST_DATA_TYPE * array, const size_t size, void * args);
void map_double_list(double_list_s * list, const manage_double_list_fn manage, void * args);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

#include <stdlib.h>

int compare_int(const void * a, const void * b) {
    return (*(DOUBLE_LIST_DATA_TYPE*)(a)) - (*(DOUBLE_LIST_DATA_TYPE*)(b));
}

void sort_int(DOUBLE_LIST_DATA_TYPE * array, const size_t size, void * compare) {
    qsort(array, size, sizeof(DOUBLE_LIST_DATA_TYPE), compare);
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    map_double_list(&list, sort_int, compare_int);
    
    // do something with sorted double_list elements

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">insert at</summary>

Inserts element at index position less than or equal to list's size.

```c++
void insert_at_double_list(double_list_s * list, const size_t index, const DOUBLE_LIST_DATA_TYPE element);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    DOUBLE_LIST_DATA_TYPE element = { 0 };
    insert_at_double_list(&list, 0, element);
    
    // do something
    
    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">get</summary>

Gets element at index position less than list's size without removing it.

```c++
DOUBLE_LIST_DATA_TYPE get_double_list(const double_list_s * list, const size_t index);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
        
    DOUBLE_LIST_DATA_TYPE element = get_double_list(&list, 0);
    
    // do something with element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">remove first</summary>

Removes first instance of element based on zero equal comparison.
Returns false assertion and exit failure if no element is found.

```c++
typedef int (*compare_double_list_fn) (const DOUBLE_LIST_DATA_TYPE one, const DOUBLE_LIST_DATA_TYPE two);
DOUBLE_LIST_DATA_TYPE remove_first_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int compare_int(const DOUBLE_LIST_DATA_TYPE a, const DOUBLE_LIST_DATA_TYPE b) {
    return a - b;
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    DOUBLE_LIST_DATA_TYPE element = { 0 };
    DOUBLE_LIST_DATA_TYPE removed = remove_first_double_list(&list, element);
    
    // do something with removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">remove last</summary>

Removes Last instance of element based on zero equal comparison.
Returns false assertion and exit failure if no element is found.

```c++
typedef int (*compare_double_list_fn) (const DOUBLE_LIST_DATA_TYPE one, const DOUBLE_LIST_DATA_TYPE two);
DOUBLE_LIST_DATA_TYPE remove_last_double_list(double_list_s * list, const DOUBLE_LIST_DATA_TYPE element, const compare_double_list_fn compare);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int compare_int(const DOUBLE_LIST_DATA_TYPE a, const DOUBLE_LIST_DATA_TYPE b) {
    return a - b;
}

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    DOUBLE_LIST_DATA_TYPE element = { 0 };
    DOUBLE_LIST_DATA_TYPE removed = remove_last_double_list(&list, element);
    
    // do something with removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">remove at</summary>

Removes element at index less than list's size.

```c++
DOUBLE_LIST_DATA_TYPE remove_at_double_list(double_list_s * list, const size_t index);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    DOUBLE_LIST_DATA_TYPE removed = remove_at_double_list(&list, 0);
    
    // do something with first removed element

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">reverse</summary>

Reverses list (I mean, yeah).

```c++
void reverse_double_list(double_list_s * list);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    reverse_double_list(&list);
    
    // do something with reversed list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">shift next</summary>

Shifts list to next number of elements starting from head.

```c++
void shift_next_double_list(double_list_s * list, const size_t shift);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    shift_next_double_list(&list, list.size / 2);
    
    // do something with reversed list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">shift previous</summary>

Shifts list to previous number of elements starting from head.

```c++
void shift_prev_double_list(double_list_s * list, const size_t shift);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    shift_prev_double_list(&list, list.size / 2);
    
    // do something with reversed list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">splice</summary>

Splices source into destination list while clearing source list.

```c++
void splice_double_list(double_list_s * restrict destination, double_list_s * restrict source, const size_t index);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s one = create_double_list();
    double_list_s two = create_double_list();
    
    // do something
    
    splice_double_list(&one, &two, one.size); // one's size to concatenate
    
    // do something with concatenated or empty list

    return 0;
}
```

</details>

<details>

<summary style="font-size: 1.5em;">split</summary>

Splits list and returns smaller list based on index less than list's size and new size.

```c++
double_list_s split_double_list(double_list_s * list, const size_t index, const size_t size);
```

```c++
#define DOUBLE_LIST_DATA_TYPE int
#include "double_list.h"

int main() {
    double_list_s list = create_double_list();
    
    // do something
    
    double_list_s split = split_double_list(&list, 0, list.size / 2); // halve list
    
    // do something with first and second half

    return 0;
}
```

</details>

</details>
