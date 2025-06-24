#ifndef BINARY_TREE_H
#define BINARY_TREE_H

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

#ifndef BINARY_TREE_DATA_TYPE
// redefine using #define BINARY_TREE_DATA_TYPE [type]
#   define BINARY_TREE_DATA_TYPE void*
#endif

#ifndef BINARY_TREE_ASSERT
#   include <assert.h>  // imports assert for debugging
// redefine using #define BINARY_TREE_DATA_TYPE [assert]
#   define BINARY_TREE_ASSERT assert
#endif

#if !defined(BINARY_TREE_ALLOC) && !defined(BINARY_TREE_FREE)
#   include <stdlib.h>
#   define BINARY_TREE_ALLOC malloc
#   define BINARY_TREE_FREE free
#elif !defined(BINARY_TREE_ALLOC)
#   error Must also define BINARY_TREE_ALLOC.
#elif !defined(BINARY_TREE_FREE)
#   error Must also define BINARY_TREE_FREE.
#endif

#ifndef BINARY_TREE_SIZE
#   define BINARY_TREE_SIZE (1 << 10)
#elif BINARY_TREE_SIZE <= 0
#   error Size cannot be zero.
#endif

/// Function pointer that creates a deep element copy.
typedef BINARY_TREE_DATA_TYPE (*copy_binary_tree_fn)    (const BINARY_TREE_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void                  (*destroy_binary_tree_fn) (BINARY_TREE_DATA_TYPE * element);
/// 'less than', else a positive number if 'more than'.
typedef int                   (*compare_binary_tree_fn) (const BINARY_TREE_DATA_TYPE one, const BINARY_TREE_DATA_TYPE two);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns 'false' if foreach loop should break.
typedef bool                  (*operate_binary_tree_fn) (BINARY_TREE_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                  (*manage_binary_tree_fn)  (BINARY_TREE_DATA_TYPE * array, const size_t size, void * args);

#define BINARY_TREE_CHILD_COUNT 2
#define BINARY_TREE_LEFT  0
#define BINARY_TREE_RIGHT 1
typedef struct binary_tree {
    compare_binary_tree_fn compare;
    BINARY_TREE_DATA_TYPE * elements;
    size_t * node[BINARY_TREE_CHILD_COUNT];
    size_t * parent;
    size_t size, head;
} binary_tree_s;

static inline binary_tree_s create_binary_tree(const compare_binary_tree_fn compare) {
    BINARY_TREE_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");

    const binary_tree_s tree = {
        .elements = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(BINARY_TREE_DATA_TYPE)),
        .node[BINARY_TREE_LEFT]  = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(size_t)),
        .node[BINARY_TREE_RIGHT] = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(size_t)),
        .parent = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(size_t)),
        .size = 0, .compare = compare, .head = BINARY_TREE_SIZE,
    };

    BINARY_TREE_ASSERT(tree.elements && "[ERROR] Memory allocation failed.");
    BINARY_TREE_ASSERT(tree.node[BINARY_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    BINARY_TREE_ASSERT(tree.node[BINARY_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    BINARY_TREE_ASSERT(tree.parent && "[ERROR] Memory allocation failed.");

    return tree;
}

static inline void destroy_binary_tree(binary_tree_s * tree, const destroy_binary_tree_fn destroy) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

    for (BINARY_TREE_DATA_TYPE e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    BINARY_TREE_FREE(tree->elements);
    BINARY_TREE_FREE(tree->node[BINARY_TREE_LEFT]);
    BINARY_TREE_FREE(tree->node[BINARY_TREE_RIGHT]);
    BINARY_TREE_FREE(tree->parent);

    tree->compare = NULL;
    tree->size = 0;
}

static inline void clear_binary_tree(binary_tree_s * tree, const destroy_binary_tree_fn destroy) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

    for (BINARY_TREE_DATA_TYPE e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    tree->size = 0;
}

static inline binary_tree_s copy_binary_tree(const binary_tree_s * tree, const copy_binary_tree_fn copy) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

    const binary_tree_s replica = {
        .elements = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(BINARY_TREE_DATA_TYPE)),
        .node[BINARY_TREE_LEFT]  = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(size_t)),
        .node[BINARY_TREE_RIGHT] = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(size_t)),
        .parent = BINARY_TREE_ALLOC(BINARY_TREE_SIZE * sizeof(size_t)),
        .size = tree->size, .compare = tree->compare, .head = tree->head,
    };

    BINARY_TREE_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    BINARY_TREE_ASSERT(replica.node[BINARY_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    BINARY_TREE_ASSERT(replica.node[BINARY_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    BINARY_TREE_ASSERT(replica.parent && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < tree->size; ++i) {
        replica.elements[i] = copy(tree->elements[i]);
    }

    memcpy(replica.node[BINARY_TREE_LEFT], tree->node[BINARY_TREE_LEFT], tree->size * sizeof(size_t));
    memcpy(replica.node[BINARY_TREE_RIGHT], tree->node[BINARY_TREE_RIGHT], tree->size * sizeof(size_t));
    memcpy(replica.parent, tree->parent, tree->size * sizeof(size_t));

    return replica;
}

static inline void insert_binary_tree(binary_tree_s * tree, const BINARY_TREE_DATA_TYPE element) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

    size_t parent = 0; // initially zero for the head case when tree is empty
    size_t * child = &(tree->head); // pointer to later change actual index of the empty child
    while (BINARY_TREE_SIZE != (*child)) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree->compare(tree->elements[(*child)], element);
        const size_t node_index = comparison <= 0 ? BINARY_TREE_LEFT : BINARY_TREE_RIGHT;

        // change parent to child and go to next child node
        parent = (*child);
        child = tree->node[node_index] + (*child);
    }

    (*child) = tree->size; // change child index from invalid value to next empty index in array
    memcpy(tree->elements + (*child), &element, sizeof(BINARY_TREE_DATA_TYPE));
    // make child's left and right indexes point to invalid value
    tree->node[BINARY_TREE_LEFT][(*child)] = tree->node[BINARY_TREE_RIGHT][(*child)] = BINARY_TREE_SIZE;
    // make child's parent into parent
    tree->parent[(*child)] = parent;
}

static inline void remove_binary_tree(binary_tree_s * tree, const BINARY_TREE_DATA_TYPE element) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void contains_binary_tree(binary_tree_s * tree, const BINARY_TREE_DATA_TYPE element) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void inorder_binary_tree(binary_tree_s * tree, const operate_binary_tree_fn operate, void * args) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void preorder_binary_tree(binary_tree_s * tree, const operate_binary_tree_fn operate, void * args) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void postorder_binary_tree(binary_tree_s * tree, const operate_binary_tree_fn operate, void * args) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void reverse_inorder_binary_tree(binary_tree_s * tree, const operate_binary_tree_fn operate, void * args) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void reverse_preorder_binary_tree(binary_tree_s * tree, const operate_binary_tree_fn operate, void * args) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void reverse_postorder_binary_tree(binary_tree_s * tree, const operate_binary_tree_fn operate, void * args) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

static inline void level_order_binary_tree(binary_tree_s * tree, const operate_binary_tree_fn operate, void * args) {
    BINARY_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BINARY_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BINARY_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BINARY_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_LEFT] && "[ERROR] 'node[BINARY_TREE_LEFT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->node[BINARY_TREE_RIGHT] && "[ERROR] 'node[BINARY_TREE_RIGHT]' pointer is NULL.");
    BINARY_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");

}

#endif // BINARY_TREE_H
