#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

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

#include <stddef.h>  // imports size_t
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy

#ifndef RED_BLACK_TREE_DATA_TYPE
// redefine using #define RED_BLACK_TREE_DATA_TYPE [type]
#   define RED_BLACK_TREE_DATA_TYPE void*
#endif

#ifndef RED_BLACK_TREE_ASSERT
#   include <assert.h>  // imports assert for debugging
// redefine using #define RED_BLACK_TREE_DATA_TYPE [assert]
#   define RED_BLACK_TREE_ASSERT assert
#endif

#if !defined(RED_BLACK_TREE_ALLOC) && !defined(RED_BLACK_TREE_FREE)
#   include <stdlib.h>
#   define RED_BLACK_TREE_ALLOC malloc
#   define RED_BLACK_TREE_FREE free
#elif !defined(RED_BLACK_TREE_ALLOC)
#   error Must also define RED_BLACK_TREE_ALLOC.
#elif !defined(RED_BLACK_TREE_FREE)
#   error Must also define RED_BLACK_TREE_FREE.
#endif

#ifndef RED_BLACK_TREE_SIZE
#   define RED_BLACK_TREE_SIZE (1 << 10)
#elif RED_BLACK_TREE_SIZE <= 0
#   error Size cannot be zero.
#endif

/// Function pointer that creates a deep element copy.
typedef RED_BLACK_TREE_DATA_TYPE (*copy_red_black_tree_fn)    (const RED_BLACK_TREE_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void                     (*destroy_red_black_tree_fn) (RED_BLACK_TREE_DATA_TYPE * element);
/// 'less than', else a positive number if 'more than'.
typedef int                      (*compare_red_black_tree_fn) (const RED_BLACK_TREE_DATA_TYPE one, const RED_BLACK_TREE_DATA_TYPE two);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns 'false' if foreach loop should break.
typedef bool                     (*operate_red_black_tree_fn) (RED_BLACK_TREE_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                     (*manage_red_black_tree_fn)  (RED_BLACK_TREE_DATA_TYPE * array, const size_t size, void * args);

#define RED_BLACK_TREE_CHILD_COUNT 2
#define RED_BLACK_TREE_LEFT  0
#define RED_BLACK_TREE_RIGHT 1
#define RED_TREE_COLOR   true
#define BLACK_TREE_COLOR false
typedef struct red_black_tree {
    compare_red_black_tree_fn compare;
    RED_BLACK_TREE_DATA_TYPE * elements;
    size_t * node[RED_BLACK_TREE_CHILD_COUNT];
    size_t * parent;
    bool * color;
    size_t size, root;
} red_black_tree_s;

static inline red_black_tree_s create_red_black_tree(const compare_red_black_tree_fn compare) {
    RED_BLACK_TREE_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");

    // initialize and allocate memory for tree
    const red_black_tree_s tree = {
        .elements = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(RED_BLACK_TREE_DATA_TYPE)),
        .node[RED_BLACK_TREE_LEFT]  = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(size_t)),
        .node[RED_BLACK_TREE_RIGHT] = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(size_t)),
        .parent = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(size_t)),
        .color = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(bool)),
        .size = 0, .compare = compare, .root = RED_BLACK_TREE_SIZE,
    };

    // check if memory allocation succeeded
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.color && "[ERROR] Memory allocation failed.");

    return tree;
}

static inline void destroy_red_black_tree(red_black_tree_s * tree, const destroy_red_black_tree_fn destroy) {
    RED_BLACK_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    RED_BLACK_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->color && "[ERROR] 'color' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    // for each element in tree elements array call destroy function
    for (RED_BLACK_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    // free allocated memory
    RED_BLACK_TREE_FREE(tree->elements);
    RED_BLACK_TREE_FREE(tree->node[RED_BLACK_TREE_LEFT]);
    RED_BLACK_TREE_FREE(tree->node[RED_BLACK_TREE_RIGHT]);
    RED_BLACK_TREE_FREE(tree->parent);
    RED_BLACK_TREE_FREE(tree->color);

    // set pointers to NULL
    tree->elements = NULL;
    tree->node[RED_BLACK_TREE_LEFT] = NULL;
    tree->node[RED_BLACK_TREE_RIGHT] = NULL;
    tree->parent = NULL;
    tree->color = NULL;

    // other cleanup stuff
    tree->root = RED_BLACK_TREE_SIZE;
    tree->compare = NULL;
    tree->size = 0;
}

static inline void clear_red_black_tree(red_black_tree_s * tree, const destroy_red_black_tree_fn destroy) {
    RED_BLACK_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    RED_BLACK_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->color && "[ERROR] 'color' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    // since the elements are continuosly in an array just iterate through each and call destroy on it
    for (RED_BLACK_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    // clearing cleanup
    tree->root = RED_BLACK_TREE_SIZE;
    tree->size = 0;
}

static inline red_black_tree_s copy_red_black_tree(const red_black_tree_s tree, const copy_red_black_tree_fn copy) {
    RED_BLACK_TREE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.color && "[ERROR] 'color' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create replica/copy to return
    const red_black_tree_s replica = {
        .compare = tree.compare, .root = tree.root, .size = tree.size,
        .elements = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(RED_BLACK_TREE_DATA_TYPE)),
        .parent = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(size_t)),
        .node[RED_BLACK_TREE_LEFT] = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(size_t)),
        .node[RED_BLACK_TREE_RIGHT] = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(size_t)),
        .color = RED_BLACK_TREE_ALLOC(RED_BLACK_TREE_SIZE * sizeof(bool)),
    };

    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] Memory allocation failed.");
    RED_BLACK_TREE_ASSERT(tree.color && "[ERROR] Memory allocation failed.");

    // copy each element either as a deep or shallow copy based on function pointer
    for (size_t i = 0; i < tree.size; ++i) {
        replica.elements[i] = copy(tree.elements[i]);
    }

    // copy node and parent indexes, and color since everything is continuous in memory
    const size_t copy_size = tree.size * sizeof(size_t);
    memcpy(replica.node[RED_BLACK_TREE_LEFT], tree.node[RED_BLACK_TREE_LEFT], copy_size);
    memcpy(replica.node[RED_BLACK_TREE_RIGHT], tree.node[RED_BLACK_TREE_RIGHT], copy_size);
    memcpy(replica.parent, tree.parent, copy_size);
    memcpy(replica.color, tree.color, tree.size * sizeof(bool));

    return replica;
}

static inline bool is_empty_red_black_tree(const red_black_tree_s tree) {
    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.color && "[ERROR] 'color' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    return !(tree.size);
}

static inline bool is_full_red_black_tree(const red_black_tree_s tree) {
    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.color && "[ERROR] 'color' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    return (RED_BLACK_TREE_SIZE == tree.size);
}

static inline void rotate_left_red_black_tree(red_black_tree_s * tree, const size_t node) {
    const size_t x = node, y = tree->node[RED_BLACK_TREE_RIGHT][x], z = tree->node[RED_BLACK_TREE_LEFT][y];

    tree->node[RED_BLACK_TREE_RIGHT][x] = z;
    if(RED_BLACK_TREE_SIZE != z) tree->parent[z] = x;
    tree->parent[y] = tree->parent[x];

    if (RED_BLACK_TREE_SIZE == tree->parent[x]) tree->root = y;
    else if (x == tree->node[RED_BLACK_TREE_LEFT][tree->parent[x]]) tree->node[RED_BLACK_TREE_LEFT][tree->parent[x]] = y;
    else tree->node[RED_BLACK_TREE_RIGHT][tree->parent[x]] = y;

    tree->node[RED_BLACK_TREE_LEFT][y] = x;
    tree->parent[x] = y;
}

static inline void rotate_right_red_black_tree(red_black_tree_s * tree, const size_t node) {
    const size_t x = node, y = tree->node[RED_BLACK_TREE_LEFT][x], z = tree->node[RED_BLACK_TREE_RIGHT][y];
    tree->node[RED_BLACK_TREE_LEFT][x] = z;

    if(RED_BLACK_TREE_SIZE != z) tree->parent[z] = x;
    tree->parent[y] = tree->parent[x];

    if (RED_BLACK_TREE_SIZE == tree->parent[x]) tree->root = y;
    else if (x == tree->node[RED_BLACK_TREE_LEFT][tree->parent[x]]) tree->node[RED_BLACK_TREE_LEFT][tree->parent[x]] = y;
    else tree->node[RED_BLACK_TREE_RIGHT][tree->parent[x]] = y;

    tree->node[RED_BLACK_TREE_RIGHT][y] = x;
    tree->parent[x] = y;
}

static inline void insert_red_black_tree(red_black_tree_s * tree, const RED_BLACK_TREE_DATA_TYPE element) {
    RED_BLACK_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    RED_BLACK_TREE_ASSERT(tree->size != RED_BLACK_TREE_SIZE && "[ERROR] Can't insert into full tree.");

    RED_BLACK_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->color && "[ERROR] 'color' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree->size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t previous = RED_BLACK_TREE_SIZE; // initially invalid for the head case when tree is empty
    size_t * node = &(tree->root); // pointer to later change actual index of the empty child
    while (RED_BLACK_TREE_SIZE != (*node)) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree->compare(element, tree->elements[(*node)]);
        const size_t node_index = comparison <= 0 ? RED_BLACK_TREE_LEFT : RED_BLACK_TREE_RIGHT;

        previous = (*node); // change parent to child
        node = tree->node[node_index] + (*node); // change child to proper gradnchild
    }

    (*node) = tree->size; // change child index from invalid value to next empty index in array
    tree->parent[(*node)] = previous; // make child's parent into parent
    tree->node[RED_BLACK_TREE_LEFT][(*node)] = tree->node[RED_BLACK_TREE_RIGHT][(*node)] = RED_BLACK_TREE_SIZE; // make child's left and right indexes invalid
    tree->color[(*node)] = RED_TREE_COLOR;

    memcpy(tree->elements + (*node), &element, sizeof(RED_BLACK_TREE_DATA_TYPE));
    tree->size++;

    size_t child = (*node), parent = RED_BLACK_TREE_SIZE, grand = RED_BLACK_TREE_SIZE;
    while (child != tree->root && tree->color[child] != BLACK_TREE_COLOR && tree->color[tree->parent[child]] == RED_TREE_COLOR) {
        parent = tree->parent[child];
        grand = tree->parent[parent];

        if (parent == tree->node[RED_BLACK_TREE_LEFT][grand]) {
            const size_t uncle = tree->node[RED_BLACK_TREE_RIGHT][grand];

            if (RED_BLACK_TREE_SIZE != uncle && tree->color[uncle] == RED_TREE_COLOR) {
                tree->color[grand] = RED_TREE_COLOR;
                tree->color[parent] = tree->color[uncle] = BLACK_TREE_COLOR;
                child = grand;
            } else {
                if (child == tree->node[RED_BLACK_TREE_RIGHT][parent]) {
                    rotate_left_red_black_tree(tree, parent);
                    child = parent;
                    parent = tree->parent[child];
                }
                rotate_right_red_black_tree(tree, grand);

                tree->color[parent] = BLACK_TREE_COLOR;
                tree->color[grand] = RED_TREE_COLOR;
                child = parent;
            }
        } else {
            const size_t uncle = tree->node[RED_BLACK_TREE_LEFT][grand];

            if (RED_BLACK_TREE_SIZE != uncle && tree->color[uncle] == RED_TREE_COLOR) {
                tree->color[grand] = RED_TREE_COLOR;
                tree->color[parent] = tree->color[uncle] = BLACK_TREE_COLOR;
                child = grand;
            } else {
                if (child == tree->node[RED_BLACK_TREE_LEFT][parent]) {
                    rotate_right_red_black_tree(tree, parent);
                    child = parent;
                    parent = tree->parent[child];
                }
                rotate_left_red_black_tree(tree, grand);

                tree->color[parent] = BLACK_TREE_COLOR;
                tree->color[grand] = RED_TREE_COLOR;
                child = parent;
            }
        }
    }

    tree->color[tree->root] = BLACK_TREE_COLOR;
}

static inline RED_BLACK_TREE_DATA_TYPE remove_red_black_tree(red_black_tree_s * tree, const RED_BLACK_TREE_DATA_TYPE element) {
    return (RED_BLACK_TREE_DATA_TYPE) { 0 };
}

static inline bool contains_red_black_tree(const red_black_tree_s tree, const RED_BLACK_TREE_DATA_TYPE element) {
    return false;
}

static inline RED_BLACK_TREE_DATA_TYPE get_min_red_black_tree(const red_black_tree_s tree) {
    return (RED_BLACK_TREE_DATA_TYPE) { 0 };
}

static inline RED_BLACK_TREE_DATA_TYPE get_max_red_black_tree(const red_black_tree_s tree) {
    return (RED_BLACK_TREE_DATA_TYPE) { 0 };
}

static inline RED_BLACK_TREE_DATA_TYPE remove_min_red_black_tree(red_black_tree_s * tree) {
    return (RED_BLACK_TREE_DATA_TYPE) { 0 };
}

static inline RED_BLACK_TREE_DATA_TYPE remove_max_red_black_tree(red_black_tree_s * tree) {
    return (RED_BLACK_TREE_DATA_TYPE) { 0 };
}

static inline void inorder_red_black_tree(const red_black_tree_s tree, const operate_red_black_tree_fn operate, void * args) {
    RED_BLACK_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct in_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = RED_BLACK_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    RED_BLACK_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    // push root node onto stack and initially save it into variable
    size_t node = tree.root;
    while (stack.size || RED_BLACK_TREE_SIZE != node) { // while stack is not empty OR node is valid
        if (RED_BLACK_TREE_SIZE != node) { // if node is valid push it onto the stack and go to node's left child
            stack.elements[stack.size++] = node;
            node = tree.node[RED_BLACK_TREE_LEFT][node];
        } else { // else node is invalid, thus pop a new node from the stack, operate on element, and go to node's right child
            node = stack.elements[--stack.size];

            if (!operate(tree.elements + node, args)) {
                break;
            }

            node = tree.node[RED_BLACK_TREE_RIGHT][node];
        }
    }

    RED_BLACK_TREE_FREE(stack.elements);
}

static inline void preorder_red_black_tree(const red_black_tree_s tree, const operate_red_black_tree_fn operate, void * args) {
    RED_BLACK_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct pre_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = RED_BLACK_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    RED_BLACK_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    if (tree.size) {
        stack.elements[stack.size++] = tree.root;
    }

    while (stack.size && operate(tree.elements + stack.elements[stack.size - 1], args)) {
        const size_t node = stack.elements[--stack.size];

        const size_t right_child = tree.node[RED_BLACK_TREE_RIGHT][node];
        if (RED_BLACK_TREE_SIZE != right_child) {
            stack.elements[stack.size++] = right_child;
        }

        const size_t left_child = tree.node[RED_BLACK_TREE_LEFT][node];
        if (RED_BLACK_TREE_SIZE != left_child) {
            stack.elements[stack.size++] = left_child;
        }
    }

    RED_BLACK_TREE_FREE(stack.elements);
}

static inline void postorder_red_black_tree(const red_black_tree_s tree, const operate_red_black_tree_fn operate, void * args) {
    RED_BLACK_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct post_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = RED_BLACK_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    RED_BLACK_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    // push root node onto stack and initially save it into variable
    size_t node = tree.root;
    size_t last = RED_BLACK_TREE_SIZE;
    while (stack.size || RED_BLACK_TREE_SIZE != node) { // while stack is not empty OR node is valid
        if (RED_BLACK_TREE_SIZE != node) { // if node is valid push it onto the stack and go to node's left child
            stack.elements[stack.size++] = node;
            node = tree.node[RED_BLACK_TREE_LEFT][node];
        } else { // else node is invalid, thus pop a new node from the stack, operate on element, and go to node's right child
            const size_t peek = stack.elements[stack.size - 1];

            const size_t peek_right_child = tree.node[RED_BLACK_TREE_RIGHT][peek];
            if (RED_BLACK_TREE_SIZE != peek_right_child && peek_right_child != last) {
                node = peek_right_child;
            } else {
                if (!operate(tree.elements + node, args)) {
                    break;
                }

                last = stack.elements[--stack.size];
            }
        }
    }

    RED_BLACK_TREE_FREE(stack.elements);
}

static inline void level_order_red_black_tree(const red_black_tree_s tree, const operate_red_black_tree_fn operate, void * args) {
    RED_BLACK_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple queue to manage breath first level order traversal of node indexes
    struct level_queue { size_t size, current; size_t * elements; } queue = {
        .size = 0, .current = 0, .elements = RED_BLACK_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    RED_BLACK_TREE_ASSERT(queue.elements && "[ERROR] Memory allocation failed.");

    if (tree.size) { // if tree isn't empty push root node
        queue.elements[queue.current + queue.size++] = tree.root;
    }

    // while queue isn't empty operate on element, pop parent and push valid children
    while (queue.size && operate(tree.elements + queue.elements[queue.current], args)) {
        // pop index
        const size_t popped_index = queue.elements[queue.current++];
        queue.size--;

        // push left child of popped parent to the top of the queue
        const size_t left_child = tree.node[RED_BLACK_TREE_LEFT][popped_index];
        if (RED_BLACK_TREE_SIZE != left_child) {
            queue.elements[queue.current + queue.size++] = left_child;
        }

        // push right child of popped parent to the top of the queue
        const size_t right_child = tree.node[RED_BLACK_TREE_RIGHT][popped_index];
        if (RED_BLACK_TREE_SIZE != right_child) {
            queue.elements[queue.current + queue.size++] = right_child;
        }
    }

    RED_BLACK_TREE_FREE(queue.elements);
}

static inline void map_red_black_tree(const red_black_tree_s tree, const manage_red_black_tree_fn manage, void * args) {
    RED_BLACK_TREE_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    RED_BLACK_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    RED_BLACK_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_LEFT] && "[ERROR] 'node[RED_BLACK_TREE_LEFT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.node[RED_BLACK_TREE_RIGHT] && "[ERROR] 'node[RED_BLACK_TREE_RIGHT]' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    RED_BLACK_TREE_ASSERT(tree.size <= RED_BLACK_TREE_SIZE && "[ERROR] Invalid tree size.");

    manage(tree.elements, tree.size, args);
}

#endif // RED_BLACK_TREE_H
