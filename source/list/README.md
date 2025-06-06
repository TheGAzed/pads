# LIST DATA STRUCTURES

List data structures are structures where each node contains an element and reference to its next neighbours.

## List of structures:

<details>

<summary style="font-size: 1.25em; font-weight: bold">STRAIGHT LIST</summary>

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

### create

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

### destroy

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

### clear

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

### copy

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

### is empty

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

### is full

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

### foreach

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

### map

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

### insert at

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

### get

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

### remove first

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

### remove at

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

### reverse

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

### splice

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

### split

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
