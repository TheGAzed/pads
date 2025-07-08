#ifndef AVL_TREE_H
#define AVL_TREE_H

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

#ifndef AVL_TREE_DATA_TYPE
// redefine using #define AVL_TREE_DATA_TYPE [type]
#   define AVL_TREE_DATA_TYPE void*
#endif

#ifndef AVL_TREE_ASSERT
#   include <assert.h>  // imports assert for debugging
// redefine using #define AVL_TREE_DATA_TYPE [assert]
#   define AVL_TREE_ASSERT assert
#endif

#if !defined(AVL_TREE_ALLOC) && !defined(AVL_TREE_FREE)
#   include <stdlib.h>
#   define AVL_TREE_ALLOC malloc
#   define AVL_TREE_FREE free
#elif !defined(AVL_TREE_ALLOC)
#   error Must also define AVL_TREE_ALLOC.
#elif !defined(AVL_TREE_FREE)
#   error Must also define AVL_TREE_FREE.
#endif

#ifndef AVL_TREE_SIZE
#   define AVL_TREE_SIZE (1 << 10)
#elif AVL_TREE_SIZE <= 0
#   error Size cannot be zero.
#endif

/// Function pointer that creates a deep element copy.
typedef AVL_TREE_DATA_TYPE (*copy_avl_tree_fn)    (const AVL_TREE_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void               (*destroy_avl_tree_fn) (AVL_TREE_DATA_TYPE * element);
/// 'less than', else a positive number if 'more than'.
typedef int                (*compare_avl_tree_fn) (const AVL_TREE_DATA_TYPE one, const AVL_TREE_DATA_TYPE two);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns 'false' if foreach loop should break.
typedef bool               (*operate_avl_tree_fn) (AVL_TREE_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void               (*manage_avl_tree_fn)  (AVL_TREE_DATA_TYPE * array, const size_t size, void * args);

#define AVL_TREE_CHILD_COUNT 2
#define AVL_TREE_LEFT  0
#define AVL_TREE_RIGHT 1
typedef struct avl_tree {
    compare_avl_tree_fn compare;
    AVL_TREE_DATA_TYPE * elements;
    size_t * node[AVL_TREE_CHILD_COUNT];
    size_t * parent;
    size_t * height;
    size_t size, root;
} avl_tree_s;

static inline avl_tree_s create_avl_tree(const compare_avl_tree_fn compare) {
    AVL_TREE_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");

    // initialize and allocate memory for tree
    const avl_tree_s tree = {
        .elements = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(AVL_TREE_DATA_TYPE)),
        .node[AVL_TREE_LEFT]  = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .node[AVL_TREE_RIGHT] = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .parent = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .height = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .size = 0, .compare = compare, .root = AVL_TREE_SIZE,
    };

    // check if memory allocation succeeded
    AVL_TREE_ASSERT(tree.elements && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.height && "[ERROR] Memory allocation failed.");

    return tree;
}

static inline void destroy_avl_tree(avl_tree_s * tree, const destroy_avl_tree_fn destroy) {
    AVL_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    AVL_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    AVL_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree->height && "[ERROR] 'height' pointer is NULL.");
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    // for each element in tree elements array call destroy function
    for (AVL_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    // free allocated memory
    AVL_TREE_FREE(tree->elements);
    AVL_TREE_FREE(tree->node[AVL_TREE_LEFT]);
    AVL_TREE_FREE(tree->node[AVL_TREE_RIGHT]);
    AVL_TREE_FREE(tree->parent);
    AVL_TREE_FREE(tree->height);

    // set pointers to NULL
    tree->elements = NULL;
    tree->node[AVL_TREE_LEFT] = NULL;
    tree->node[AVL_TREE_RIGHT] = NULL;
    tree->parent = NULL;
    tree->height = NULL;

    // other cleanup stuff
    tree->root = AVL_TREE_SIZE;
    tree->compare = NULL;
    tree->size = 0;
}

static inline void clear_avl_tree(avl_tree_s * tree, const destroy_avl_tree_fn destroy) {
    AVL_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    AVL_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    AVL_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree->height && "[ERROR] 'height' pointer is NULL.");
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    // since the elements are continuosly in an array just iterate through each and call destroy on it
    for (AVL_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    // clearing cleanup
    tree->root = AVL_TREE_SIZE;
    tree->size = 0;
}

static inline avl_tree_s copy_avl_tree(const avl_tree_s tree, const copy_avl_tree_fn copy) {
    AVL_TREE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.height && "[ERROR] 'height' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create replica/copy to return
    const avl_tree_s replica = {
        .compare = tree.compare, .root = tree.root, .size = tree.size,
        .elements = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(AVL_TREE_DATA_TYPE)),
        .height = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .parent = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .node[AVL_TREE_LEFT] = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .node[AVL_TREE_RIGHT] = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
    };

    AVL_TREE_ASSERT(tree.elements && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] Memory allocation failed.");
    AVL_TREE_ASSERT(tree.height && "[ERROR] Memory allocation failed.");

    // copy each element either as a deep or shallow copy based on function pointer
    for (size_t i = 0; i < tree.size; ++i) {
        replica.elements[i] = copy(tree.elements[i]);
    }

    // copy node and parent indexes, and heights since everything is continuous in memory
    const size_t copy_size = tree.size * sizeof(size_t);
    memcpy(replica.node[AVL_TREE_LEFT], tree.node[AVL_TREE_LEFT], copy_size);
    memcpy(replica.node[AVL_TREE_RIGHT], tree.node[AVL_TREE_RIGHT], copy_size);
    memcpy(replica.parent, tree.parent, copy_size);
    memcpy(replica.height, tree.height, copy_size);

    return replica;
}

static inline bool is_empty_avl_tree(const avl_tree_s tree) {
    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.height && "[ERROR] 'height' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    return !(tree.size);
}

static inline bool is_full_avl_tree(const avl_tree_s tree) {
    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.height && "[ERROR] 'height' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    return (AVL_TREE_SIZE == tree.size);
}

static inline void insert_avl_tree(avl_tree_s * tree, const AVL_TREE_DATA_TYPE element) {
    AVL_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    AVL_TREE_ASSERT(tree->size != AVL_TREE_SIZE && "[ERROR] Can't insert into full tree.");

    AVL_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree->height && "[ERROR] 'height' pointer is NULL.");
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t previous = AVL_TREE_SIZE; // initially invalid for the head case when tree is empty
    size_t * node = &(tree->root); // pointer to later change actual index of the empty child
    while (AVL_TREE_SIZE != (*node)) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree->compare(element, tree->elements[(*node)]);
        const size_t node_index = comparison <= 0 ? AVL_TREE_LEFT : AVL_TREE_RIGHT;

        previous = (*node); // change parent to child
        node = tree->node[node_index] + (*node); // change child to proper gradnchild
    }

    (*node) = tree->size; // change child index from invalid value to next empty index in array
    tree->parent[(*node)] = previous; // make child's parent into parent
    tree->node[AVL_TREE_LEFT][(*node)] = tree->node[AVL_TREE_RIGHT][(*node)] = AVL_TREE_SIZE; // make child's left and right indexes invalid

    memcpy(tree->elements + (*node), &element, sizeof(AVL_TREE_DATA_TYPE));
    tree->size++;

    for (size_t n = (*node), p = tree->parent[n]; AVL_TREE_SIZE != n; n = p, p = tree->parent[n]) {
        // calculate left child's height
        const size_t left_child = tree->node[AVL_TREE_LEFT][n];
        const size_t left_child_height = (AVL_TREE_SIZE == left_child) ? 0 : tree->height[left_child];

        // calculate right child's height
        const size_t right_child = tree->node[AVL_TREE_RIGHT][n];
        const size_t right_child_height = (AVL_TREE_SIZE == right_child) ? 0 : tree->height[right_child];

        // set new height for each element popped from stack
        tree->height[n] = 1 + (left_child_height > right_child_height ? left_child_height : right_child_height);

        // calculate absolute difference of left and right child's heights
        const size_t abs_balance = left_child_height > right_child_height ? left_child_height - right_child_height : right_child_height - left_child_height;

        if (abs_balance < 2) { // if tree is balanced continue, else perform rotation/s
            continue;
        }

        if (left_child_height < right_child_height) {
            const size_t left_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_LEFT][right_child]];
            const size_t right_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][right_child]];

            if (left_grand_height > right_grand_height) {
                { // RIGHT ROTATE RIGHT CHILD
                    const size_t x = right_child, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

                    tree->node[AVL_TREE_LEFT][x] = z;
                    if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                    tree->parent[y] = tree->parent[x];

                    if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                    else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                    else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                    tree->node[AVL_TREE_RIGHT][y] = x;
                    tree->parent[x] = y;

                    const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                    const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                    tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                    const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                    const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                    tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
                }
            }
            { // LEFT ROTATE CURRENT NODE
                const size_t x = n, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

                tree->node[AVL_TREE_RIGHT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_LEFT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }
        }

        if (left_child_height > right_child_height) {
            const size_t left_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_LEFT][left_child]];
            const size_t right_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][left_child]];

            if (left_grand_height < right_grand_height) {
                { // LEFT ROTATE LEFT CHILD
                    const size_t x = left_child, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

                    tree->node[AVL_TREE_RIGHT][x] = z;
                    if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                    tree->parent[y] = tree->parent[x];

                    if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                    else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                    else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                    tree->node[AVL_TREE_LEFT][y] = x;
                    tree->parent[x] = y;

                    const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                    const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                    tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                    const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                    const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                    tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
                }
            }
            { // RIGHT ROTATE CURRENT NODE
                const size_t x = n, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

                tree->node[AVL_TREE_LEFT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_RIGHT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }
        }
    }
}

static inline AVL_TREE_DATA_TYPE remove_avl_tree(avl_tree_s * tree, const AVL_TREE_DATA_TYPE element) {
    AVL_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    AVL_TREE_ASSERT(tree->size && "[ERROR] Can't remove from empty tree.");
    AVL_TREE_ASSERT(AVL_TREE_SIZE != tree->root && "[ERROR] Invalid root node index.");

    AVL_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");
    AVL_TREE_ASSERT(tree->root != AVL_TREE_SIZE && "[ERROR] Invalid tree root index.");
    AVL_TREE_ASSERT(tree->root < tree->size && "[ERROR] Invalid tree root index.");
    AVL_TREE_ASSERT(tree->parent[tree->root] == AVL_TREE_SIZE && "[ERROR] Invalid tree root parent.");

    size_t * node = &(tree->root); // pointer to later change actual index of the empty child
    while (AVL_TREE_SIZE != (*node)) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree->compare(element, tree->elements[(*node)]);
        if (!comparison) {
            break;
        }

        const size_t node_index = comparison <= 0 ? AVL_TREE_LEFT : AVL_TREE_RIGHT;

        // change parent to child and go to next child node
        node = tree->node[node_index] + (*node);
    }

    if (BSEARCH_TREE_SIZE == (*node)) {
        // element was NOT found, thus return an error
        BSEARCH_TREE_ASSERT(false && "[ERROR] Element not found in tree.");
        exit(EXIT_FAILURE);
    }

    AVL_TREE_DATA_TYPE removed = tree->elements[(*node)];
    tree->size--;

    // calculate the rightmost depth of the left child
    size_t left_depth = 0, * left_node = node;
    for (size_t * l = tree->node[AVL_TREE_LEFT] + (*left_node); AVL_TREE_SIZE != (*l); l = tree->node[AVL_TREE_RIGHT] + (*l)) {
        left_depth++;
        left_node = l;
    }

    // calculate the leftmost depth of the right child
    size_t right_depth = 0, * right_node = node;
    for (size_t * r = tree->node[AVL_TREE_RIGHT] + (*right_node); AVL_TREE_SIZE != (*r); r = tree->node[AVL_TREE_LEFT] + (*r)) {
        right_depth++;
        right_node = r;
    }

    const size_t hole_index = left_depth > right_depth ? (*left_node) : (*right_node);
    tree->elements[(*node)] = tree->elements[hole_index];
    if (left_depth > right_depth) {
        if (AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][(*left_node)]) { // if right child exists cut off parent
            tree->parent[tree->node[AVL_TREE_LEFT][(*left_node)]] = tree->parent[(*left_node)];
        }
        (*left_node) = tree->node[AVL_TREE_LEFT][(*left_node)]; // cut off new hole index
    } else {
        if (AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][(*right_node)]) { // if left child exists cut off parent
            tree->parent[tree->node[AVL_TREE_RIGHT][(*right_node)]] = tree->parent[(*right_node)];
        }
        (*right_node) = tree->node[AVL_TREE_RIGHT][(*right_node)]; // cut off new hole index
    }

    if (tree->size && tree->root == tree->size) { // if head node is last array element then change index to removed one
        tree->root = hole_index;
    }

    // cut hole node from the rest of the tree
    tree->node[AVL_TREE_LEFT][hole_index] = tree->node[AVL_TREE_RIGHT][hole_index] = tree->parent[hole_index] = hole_index;

    // replace removed element with rightmost array one (or fill hole with valid element)
    tree->elements[hole_index] = tree->elements[tree->size];
    tree->node[AVL_TREE_LEFT][hole_index] = tree->node[AVL_TREE_LEFT][tree->size];
    tree->node[AVL_TREE_RIGHT][hole_index] = tree->node[AVL_TREE_RIGHT][tree->size];
    tree->parent[hole_index] = tree->parent[tree->size];

    // redirect parent and children of rightmost array node if they dont overlap with removed index
    const size_t left_last = tree->node[AVL_TREE_LEFT][tree->size];
    if (AVL_TREE_SIZE != left_last) {
        tree->parent[left_last] = hole_index;
    }

    const size_t right_last = tree->node[AVL_TREE_RIGHT][tree->size];
    if (AVL_TREE_SIZE != right_last) {
        tree->parent[right_last] = hole_index;
    }

    const size_t parent_last = tree->parent[tree->size];
    if (AVL_TREE_SIZE != parent_last) {
        const int comparison = tree->compare(tree->elements[tree->size], tree->elements[parent_last]);
        const size_t node_index = comparison <= 0 ? AVL_TREE_LEFT : AVL_TREE_RIGHT;
        tree->node[node_index][parent_last] = hole_index;
    }

    for (size_t n = (*node), p = tree->parent[n]; AVL_TREE_SIZE != n; n = p, p = tree->parent[n]) {
        // calculate left child's height
        const size_t left_child = tree->node[AVL_TREE_LEFT][n];
        const size_t left_child_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][n]) ? 0 : tree->height[tree->node[AVL_TREE_LEFT][n]];

        // calculate right child's height
        const size_t right_child = tree->node[AVL_TREE_RIGHT][n];
        const size_t right_child_height = (AVL_TREE_SIZE == right_child) ? 0 : tree->height[right_child];

        // set new height for each element popped from stack
        tree->height[n] = 1 + (left_child_height > right_child_height ? left_child_height : right_child_height);

        // calculate absolute difference of left and right child's heights
        const size_t abs_balance = left_child_height > right_child_height ? left_child_height - right_child_height : right_child_height - left_child_height;

        if (abs_balance < 2) { // if tree is balanced continue, else perform rotation/s
            continue;
        }

        if (left_child_height < right_child_height) {
            const size_t left_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_LEFT][right_child]];
            const size_t right_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][right_child]];

            if (left_grand_height > right_grand_height) {
                const size_t x = right_child, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

                tree->node[AVL_TREE_LEFT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_RIGHT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }

            const size_t x = n, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

            tree->node[AVL_TREE_RIGHT][x] = z;
            if (AVL_TREE_SIZE != z) tree->parent[z] = x;
            tree->parent[y] = tree->parent[x];

            if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
            else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
            else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

            tree->node[AVL_TREE_LEFT][y] = x;
            tree->parent[x] = y;

            const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
            const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
            tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

            const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
            const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
            tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
        }

        if (left_child_height > right_child_height) {
            const size_t left_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_LEFT][left_child]];
            const size_t right_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][left_child]];

            if (left_grand_height > right_grand_height) {
                const size_t x = left_child, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

                tree->node[AVL_TREE_RIGHT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_LEFT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }

            const size_t x = n, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

            tree->node[AVL_TREE_LEFT][x] = z;
            if (AVL_TREE_SIZE != z) tree->parent[z] = x;
            tree->parent[y] = tree->parent[x];

            if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
            else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
            else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

            tree->node[AVL_TREE_RIGHT][y] = x;
            tree->parent[x] = y;

            const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
            const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
            tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

            const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
            const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
            tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
        }
    }

    return removed;
}

static inline bool contains_avl_tree(const avl_tree_s tree, const AVL_TREE_DATA_TYPE element) {
    AVL_TREE_ASSERT(tree.size && "[ERROR] Can't check empty tree.");
    AVL_TREE_ASSERT(AVL_TREE_SIZE != tree.root && "[ERROR] Invalid root node index.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    for (size_t node = tree.root; AVL_TREE_SIZE != node;) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree.compare(tree.elements[node], element);
        if (!comparison) {
            return true;
        }

        const size_t node_index = comparison <= 0 ? AVL_TREE_LEFT : AVL_TREE_RIGHT;
        node = tree.node[node_index][node]; // go to next child node
    }

    return false;
}

static inline AVL_TREE_DATA_TYPE get_min_avl_tree(const avl_tree_s tree) {
    AVL_TREE_ASSERT(tree.size && "[ERROR] Can't get from empty tree.");
    AVL_TREE_ASSERT(AVL_TREE_SIZE != tree.root && "[ERROR] Invalid root node index.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t minimum_node = tree.root;
    for (size_t i = tree.node[AVL_TREE_LEFT][minimum_node]; AVL_TREE_SIZE != i; i = tree.node[AVL_TREE_LEFT][i]) {
        minimum_node = i;
    }

    return tree.elements[minimum_node];
}

static inline AVL_TREE_DATA_TYPE get_max_avl_tree(const avl_tree_s tree) {
    AVL_TREE_ASSERT(tree.size && "[ERROR] Can't get from empty tree.");
    AVL_TREE_ASSERT(AVL_TREE_SIZE != tree.root && "[ERROR] Invalid root node index.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t maximum_node = tree.root;
    for (size_t i = tree.node[AVL_TREE_RIGHT][maximum_node]; AVL_TREE_SIZE != i; i = tree.node[AVL_TREE_RIGHT][i]) {
        maximum_node = i;
    }

    return tree.elements[maximum_node];
}

static inline AVL_TREE_DATA_TYPE remove_min_avl_tree(avl_tree_s * tree) {
    AVL_TREE_ASSERT(tree->size && "[ERROR] Can't get from empty tree.");
    AVL_TREE_ASSERT(AVL_TREE_SIZE != tree->root && "[ERROR] Invalid root node index.");

    AVL_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");
    AVL_TREE_ASSERT(tree->root != AVL_TREE_SIZE && "[ERROR] Invalid tree root index.");
    AVL_TREE_ASSERT(tree->root < tree->size && "[ERROR] Invalid tree root index.");
    AVL_TREE_ASSERT(tree->parent[tree->root] == AVL_TREE_SIZE && "[ERROR] Invalid tree root parent.");

    size_t * minimum_node = &(tree->root);
    for (size_t * i = tree->node[AVL_TREE_LEFT] + (*minimum_node); AVL_TREE_SIZE != (*i); i = tree->node[AVL_TREE_LEFT] + (*i)) {
        minimum_node = i;
    }

    AVL_TREE_DATA_TYPE removed = tree->elements[(*minimum_node)];
    tree->size--;

    const size_t hole_index = (*minimum_node);
    const size_t right_node = tree->node[AVL_TREE_RIGHT][(*minimum_node)];
    if (AVL_TREE_SIZE != right_node) {
        tree->parent[right_node] = tree->parent[(*minimum_node)];
    }
    (*minimum_node) = right_node;

    // cut hole node from the rest of the tree
    tree->node[AVL_TREE_LEFT][hole_index] = tree->node[AVL_TREE_RIGHT][hole_index] = tree->parent[hole_index] = hole_index;

    // replace removed element with rightmost array one (or fill hole with valid element)
    tree->elements[hole_index] = tree->elements[tree->size];
    tree->node[AVL_TREE_LEFT][hole_index] = tree->node[AVL_TREE_LEFT][tree->size];
    tree->node[AVL_TREE_RIGHT][hole_index] = tree->node[AVL_TREE_RIGHT][tree->size];
    tree->parent[hole_index] = tree->parent[tree->size];

    // redirect parent and children of rightmost last array node if they dont overlap with removed index
    const size_t left_last = tree->node[AVL_TREE_LEFT][tree->size];
    if (AVL_TREE_SIZE != left_last) {
        tree->parent[left_last] = hole_index;
    }

    const size_t right_last = tree->node[AVL_TREE_RIGHT][tree->size];
    if (AVL_TREE_SIZE != right_last) {
        tree->parent[right_last] = hole_index;
    }

    const size_t parent_last = tree->parent[tree->size];
    if (AVL_TREE_SIZE != parent_last) {
        const int comparison = tree->compare(tree->elements[tree->size], tree->elements[parent_last]);
        const size_t node_index = comparison <= 0 ? AVL_TREE_LEFT : AVL_TREE_RIGHT;
        tree->node[node_index][parent_last] = hole_index;
    }

    for (size_t n = (*minimum_node), p = tree->parent[n]; AVL_TREE_SIZE != n; n = p, p = tree->parent[n]) {
        // calculate left child's height
        const size_t left_child = tree->node[AVL_TREE_LEFT][n];
        const size_t left_child_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][n]) ? 0 : tree->height[tree->node[AVL_TREE_LEFT][n]];

        // calculate right child's height
        const size_t right_child = tree->node[AVL_TREE_RIGHT][n];
        const size_t right_child_height = (AVL_TREE_SIZE == right_child) ? 0 : tree->height[right_child];

        // set new height for each element popped from stack
        tree->height[n] = 1 + (left_child_height > right_child_height ? left_child_height : right_child_height);

        // calculate absolute difference of left and right child's heights
        const size_t abs_balance = left_child_height > right_child_height ? left_child_height - right_child_height : right_child_height - left_child_height;

        if (abs_balance < 2) { // if tree is balanced continue, else perform rotation/s
            continue;
        }

        if (left_child_height < right_child_height) {
            const size_t left_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_LEFT][right_child]];
            const size_t right_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][right_child]];

            if (left_grand_height > right_grand_height) {
                const size_t x = right_child, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

                tree->node[AVL_TREE_LEFT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_RIGHT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }

            const size_t x = n, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

            tree->node[AVL_TREE_RIGHT][x] = z;
            if (AVL_TREE_SIZE != z) tree->parent[z] = x;
            tree->parent[y] = tree->parent[x];

            if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
            else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
            else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

            tree->node[AVL_TREE_LEFT][y] = x;
            tree->parent[x] = y;

            const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
            const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
            tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

            const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
            const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
            tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
        }

        if (left_child_height > right_child_height) {
            const size_t left_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_LEFT][left_child]];
            const size_t right_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][left_child]];

            if (left_grand_height > right_grand_height) {
                const size_t x = left_child, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

                tree->node[AVL_TREE_RIGHT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_LEFT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }

            const size_t x = n, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

            tree->node[AVL_TREE_LEFT][x] = z;
            if (AVL_TREE_SIZE != z) tree->parent[z] = x;
            tree->parent[y] = tree->parent[x];

            if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
            else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
            else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

            tree->node[AVL_TREE_RIGHT][y] = x;
            tree->parent[x] = y;

            const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
            const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
            tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

            const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
            const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
            tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
        }
    }

    return removed;
}

static inline AVL_TREE_DATA_TYPE remove_max_avl_tree(avl_tree_s * tree) {
    AVL_TREE_ASSERT(tree->size && "[ERROR] Can't get from empty tree.");
    AVL_TREE_ASSERT(AVL_TREE_SIZE != tree->root && "[ERROR] Invalid root node index.");

    AVL_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");
    AVL_TREE_ASSERT(tree->root != AVL_TREE_SIZE && "[ERROR] Invalid tree root index.");
    AVL_TREE_ASSERT(tree->root < tree->size && "[ERROR] Invalid tree root index.");
    AVL_TREE_ASSERT(tree->parent[tree->root] == AVL_TREE_SIZE && "[ERROR] Invalid tree root parent.");

    size_t * maximum_node = &(tree->root);
    for (size_t * i = tree->node[AVL_TREE_RIGHT] + (*maximum_node); AVL_TREE_SIZE != (*i); i = tree->node[AVL_TREE_RIGHT] + (*i)) {
        maximum_node = i;
    }

    AVL_TREE_DATA_TYPE removed = tree->elements[(*maximum_node)];
    tree->size--;

    const size_t hole_index = (*maximum_node);
    const size_t left_node = tree->node[AVL_TREE_LEFT][(*maximum_node)];
    if (AVL_TREE_SIZE != left_node) {
        tree->parent[left_node] = tree->parent[(*maximum_node)];
    }
    (*maximum_node) = left_node;

    // cut hole node from the rest of the tree
    tree->node[AVL_TREE_LEFT][hole_index] = tree->node[AVL_TREE_RIGHT][hole_index] = tree->parent[hole_index] = hole_index;

    // replace removed element with rightmost array one (or fill hole with valid element)
    tree->elements[hole_index] = tree->elements[tree->size];
    tree->node[AVL_TREE_LEFT][hole_index] = tree->node[AVL_TREE_LEFT][tree->size];
    tree->node[AVL_TREE_RIGHT][hole_index] = tree->node[AVL_TREE_RIGHT][tree->size];
    tree->parent[hole_index] = tree->parent[tree->size];

    // redirect parent and children of rightmost last array node if they dont overlap with removed index
    const size_t left_last = tree->node[AVL_TREE_LEFT][tree->size];
    if (AVL_TREE_SIZE != left_last) {
        tree->parent[left_last] = hole_index;
    }

    const size_t right_last = tree->node[AVL_TREE_RIGHT][tree->size];
    if (AVL_TREE_SIZE != right_last) {
        tree->parent[right_last] = hole_index;
    }

    const size_t parent_last = tree->parent[tree->size];
    if (AVL_TREE_SIZE != parent_last) {
        const int comparison = tree->compare(tree->elements[tree->size], tree->elements[parent_last]);
        const size_t node_index = comparison <= 0 ? AVL_TREE_LEFT : AVL_TREE_RIGHT;
        tree->node[node_index][parent_last] = hole_index;
    }

    for (size_t n = (*maximum_node), p = tree->parent[n]; AVL_TREE_SIZE != n; n = p, p = tree->parent[n]) {
        // calculate left child's height
        const size_t left_child = tree->node[AVL_TREE_LEFT][n];
        const size_t left_child_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][n]) ? 0 : tree->height[tree->node[AVL_TREE_LEFT][n]];

        // calculate right child's height
        const size_t right_child = tree->node[AVL_TREE_RIGHT][n];
        const size_t right_child_height = (AVL_TREE_SIZE == right_child) ? 0 : tree->height[right_child];

        // set new height for each element popped from stack
        tree->height[n] = 1 + (left_child_height > right_child_height ? left_child_height : right_child_height);

        // calculate absolute difference of left and right child's heights
        const size_t abs_balance = left_child_height > right_child_height ? left_child_height - right_child_height : right_child_height - left_child_height;

        if (abs_balance < 2) { // if tree is balanced continue, else perform rotation/s
            continue;
        }

        if (left_child_height < right_child_height) {
            const size_t left_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_LEFT][right_child]];
            const size_t right_grand_height = (AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][right_child]) ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][right_child]];

            if (left_grand_height > right_grand_height) {
                const size_t x = right_child, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

                tree->node[AVL_TREE_LEFT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_RIGHT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }

            const size_t x = n, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

            tree->node[AVL_TREE_RIGHT][x] = z;
            if (AVL_TREE_SIZE != z) tree->parent[z] = x;
            tree->parent[y] = tree->parent[x];

            if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
            else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
            else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

            tree->node[AVL_TREE_LEFT][y] = x;
            tree->parent[x] = y;

            const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
            const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
            tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

            const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
            const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
            tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
        }

        if (left_child_height > right_child_height) {
            const size_t left_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_LEFT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_LEFT][left_child]];
            const size_t right_grand_height = AVL_TREE_SIZE == tree->node[AVL_TREE_RIGHT][left_child] ? 0 : tree->height[tree->node[AVL_TREE_RIGHT][left_child]];

            if (left_grand_height > right_grand_height) {
                const size_t x = left_child, y = tree->node[AVL_TREE_RIGHT][x], z = tree->node[AVL_TREE_LEFT][y];

                tree->node[AVL_TREE_RIGHT][x] = z;
                if (AVL_TREE_SIZE != z) tree->parent[z] = x;
                tree->parent[y] = tree->parent[x];

                if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
                else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
                else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

                tree->node[AVL_TREE_LEFT][y] = x;
                tree->parent[x] = y;

                const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
                const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
                tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

                const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
                const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
                tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
            }

            const size_t x = n, y = tree->node[AVL_TREE_LEFT][x], z = tree->node[AVL_TREE_RIGHT][y];

            tree->node[AVL_TREE_LEFT][x] = z;
            if (AVL_TREE_SIZE != z) tree->parent[z] = x;
            tree->parent[y] = tree->parent[x];

            if (AVL_TREE_SIZE == tree->parent[x]) tree->root = y;
            else if (x == tree->node[AVL_TREE_LEFT][tree->parent[x]]) tree->node[AVL_TREE_LEFT][tree->parent[x]] = y;
            else tree->node[AVL_TREE_RIGHT][tree->parent[x]] = y;

            tree->node[AVL_TREE_RIGHT][y] = x;
            tree->parent[x] = y;

            const size_t x_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][x] ? tree->height[tree->node[AVL_TREE_LEFT][x]] : 0;
            const size_t x_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][x] ? tree->height[tree->node[AVL_TREE_RIGHT][x]] : 0;
            tree->height[x] = 1 + (x_right_height > x_left_height ? x_right_height : x_left_height);

            const size_t y_left_height = AVL_TREE_SIZE != tree->node[AVL_TREE_LEFT][y] ? tree->height[tree->node[AVL_TREE_LEFT][y]] : 0;
            const size_t y_right_height = AVL_TREE_SIZE != tree->node[AVL_TREE_RIGHT][y] ? tree->height[tree->node[AVL_TREE_RIGHT][y]] : 0;
            tree->height[y] = 1 + (y_right_height > y_left_height ? y_right_height : y_left_height);
        }
    }
    return removed;
}

static inline void inorder_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {
    AVL_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    bool left_done = false;
    size_t node = tree.root;
    while (AVL_TREE_SIZE != node) {
        while (!left_done && AVL_TREE_SIZE != tree.node[AVL_TREE_LEFT][node]) {
            node = tree.node[AVL_TREE_LEFT][node];
        }

        if (!operate(tree.elements + node, args)) {
            break;
        }

        left_done = true;
        if (AVL_TREE_SIZE != tree.node[AVL_TREE_RIGHT][node]) {
            left_done = false;
            node = tree.node[AVL_TREE_RIGHT][node];
        } else if (AVL_TREE_SIZE != tree.parent[node]) {
            while (AVL_TREE_SIZE != tree.parent[node] && node == tree.node[AVL_TREE_RIGHT][tree.parent[node]]) {
                node = tree.parent[node];
            }

            if (AVL_TREE_SIZE == tree.parent[node]) {
                break;
            }

            node = tree.parent[node];
        } else {
            break;
        }
    }
}

static inline void preorder_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {
    AVL_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct pre_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = AVL_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    AVL_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    if (tree.size) {
        stack.elements[stack.size++] = tree.root;
    }

    while (stack.size && operate(tree.elements + stack.elements[stack.size - 1], args)) {
        const size_t node = stack.elements[--stack.size];

        const size_t right_child = tree.node[AVL_TREE_RIGHT][node];
        if (AVL_TREE_SIZE != right_child) {
            stack.elements[stack.size++] = right_child;
        }

        const size_t left_child = tree.node[AVL_TREE_LEFT][node];
        if (AVL_TREE_SIZE != left_child) {
            stack.elements[stack.size++] = left_child;
        }
    }

    AVL_TREE_FREE(stack.elements);
}

static inline void postorder_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {
    AVL_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct post_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = AVL_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    AVL_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    // push root node onto stack and initially save it into variable
    size_t node = tree.root;
    size_t last = AVL_TREE_SIZE;
    while (stack.size || AVL_TREE_SIZE != node) { // while stack is not empty OR node is valid
        if (AVL_TREE_SIZE != node) { // if node is valid push it onto the stack and go to node's left child
            stack.elements[stack.size++] = node;
            node = tree.node[AVL_TREE_LEFT][node];
        } else { // else node is invalid, thus pop a new node from the stack, operate on element, and go to node's right child
            const size_t peek = stack.elements[stack.size - 1];

            const size_t peek_right_child = tree.node[AVL_TREE_RIGHT][peek];
            if (AVL_TREE_SIZE != peek_right_child && peek_right_child != last) {
                node = peek_right_child;
            } else {
                if (!operate(tree.elements + node, args)) {
                    break;
                }

                last = stack.elements[--stack.size];
            }
        }
    }

    AVL_TREE_FREE(stack.elements);
}

static inline void level_order_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {
    AVL_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple queue to manage breath first level order traversal of node indexes
    struct level_queue { size_t size, current; size_t * elements; } queue = {
        .size = 0, .current = 0, .elements = AVL_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    AVL_TREE_ASSERT(queue.elements && "[ERROR] Memory allocation failed.");

    if (tree.size) { // if tree isn't empty push root node
        queue.elements[queue.current + queue.size++] = tree.root;
    }

    // while queue isn't empty operate on element, pop parent and push valid children
    while (queue.size && operate(tree.elements + queue.elements[queue.current], args)) {
        // pop index
        const size_t popped_index = queue.elements[queue.current++];
        queue.size--;

        // push left child of popped parent to the top of the queue
        const size_t left_child = tree.node[AVL_TREE_LEFT][popped_index];
        if (AVL_TREE_SIZE != left_child) {
            queue.elements[queue.current + queue.size++] = left_child;
        }

        // push right child of popped parent to the top of the queue
        const size_t right_child = tree.node[AVL_TREE_RIGHT][popped_index];
        if (AVL_TREE_SIZE != right_child) {
            queue.elements[queue.current + queue.size++] = right_child;
        }
    }

    AVL_TREE_FREE(queue.elements);
}

static inline void map_avl_tree(const avl_tree_s tree, const manage_avl_tree_fn manage, void * args) {
    AVL_TREE_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    manage(tree.elements, tree.size, args);
}

#endif // AVL_TREE_H
