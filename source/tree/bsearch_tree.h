#ifndef BSEARCH_TREE_H
#define BSEARCH_TREE_H

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

#ifndef BSEARCH_TREE_DATA_TYPE
// redefine using #define BSEARCH_TREE_DATA_TYPE [type]
#   define BSEARCH_TREE_DATA_TYPE void*
#endif

#ifndef BSEARCH_TREE_ASSERT
#   include <assert.h>  // imports assert for debugging
// redefine using #define BSEARCH_TREE_DATA_TYPE [assert]
#   define BSEARCH_TREE_ASSERT assert
#endif

#if !defined(BSEARCH_TREE_ALLOC) && !defined(BSEARCH_TREE_FREE)
#   include <stdlib.h>
#   define BSEARCH_TREE_ALLOC malloc
#   define BSEARCH_TREE_FREE free
#elif !defined(BSEARCH_TREE_ALLOC)
#   error Must also define BSEARCH_TREE_ALLOC.
#elif !defined(BSEARCH_TREE_FREE)
#   error Must also define BSEARCH_TREE_FREE.
#endif

#ifndef BSEARCH_TREE_SIZE
#   define BSEARCH_TREE_SIZE (1 << 10)
#elif BSEARCH_TREE_SIZE <= 0
#   error Size cannot be zero.
#endif

/// Function pointer that creates a deep element copy.
typedef BSEARCH_TREE_DATA_TYPE (*copy_bsearch_tree_fn)    (const BSEARCH_TREE_DATA_TYPE element);
/// Function pointer that destroys a deep element.
typedef void                   (*destroy_bsearch_tree_fn) (BSEARCH_TREE_DATA_TYPE * element);
/// 'less than', else a positive number if 'more than'.
typedef int                    (*compare_bsearch_tree_fn) (const BSEARCH_TREE_DATA_TYPE one, const BSEARCH_TREE_DATA_TYPE two);
/// Function pointer that changes an element pointer using void pointer arguments if needed. Returns 'false' if foreach loop should break.
typedef bool                   (*operate_bsearch_tree_fn) (BSEARCH_TREE_DATA_TYPE * element, void * args);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                   (*manage_bsearch_tree_fn)  (BSEARCH_TREE_DATA_TYPE * array, const size_t size, void * args);

#define BSEARCH_TREE_CHILD_COUNT 2
#define BSEARCH_TREE_LEFT  0
#define BSEARCH_TREE_RIGHT 1
typedef struct bsearch_tree {
    compare_bsearch_tree_fn compare;
    BSEARCH_TREE_DATA_TYPE * elements;
    size_t * node[BSEARCH_TREE_CHILD_COUNT];
    size_t * parent;
    size_t size, root;
} bsearch_tree_s;

static inline bsearch_tree_s create_bsearch_tree(const compare_bsearch_tree_fn compare) {
    BSEARCH_TREE_ASSERT(compare && "[ERROR] 'compare' parameter is NULL.");

    const bsearch_tree_s tree = {
        .elements = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(BSEARCH_TREE_DATA_TYPE)),
        .node[BSEARCH_TREE_LEFT]  = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(size_t)),
        .node[BSEARCH_TREE_RIGHT] = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(size_t)),
        .parent = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(size_t)),
        .size = 0, .compare = compare, .root = BSEARCH_TREE_SIZE,
    };

    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] Memory allocation failed.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] Memory allocation failed.");

    return tree;
}

static inline void destroy_bsearch_tree(bsearch_tree_s * tree, const destroy_bsearch_tree_fn destroy) {
    BSEARCH_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BSEARCH_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    for (BSEARCH_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    BSEARCH_TREE_FREE(tree->elements);
    BSEARCH_TREE_FREE(tree->node[BSEARCH_TREE_LEFT]);
    BSEARCH_TREE_FREE(tree->node[BSEARCH_TREE_RIGHT]);
    BSEARCH_TREE_FREE(tree->parent);

    tree->elements = NULL;
    tree->node[BSEARCH_TREE_LEFT] = NULL;
    tree->node[BSEARCH_TREE_RIGHT] = NULL;
    tree->parent = NULL;

    tree->root = BSEARCH_TREE_SIZE;
    tree->compare = NULL;
    tree->size = 0;
}

static inline void clear_bsearch_tree(bsearch_tree_s * tree, const destroy_bsearch_tree_fn destroy) {
    BSEARCH_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BSEARCH_TREE_ASSERT(destroy && "[ERROR] 'destroy' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    for (BSEARCH_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    tree->root = BSEARCH_TREE_SIZE;
    tree->size = 0;
}

static inline bsearch_tree_s copy_bsearch_tree(const bsearch_tree_s tree, const copy_bsearch_tree_fn copy) {
    BSEARCH_TREE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    const bsearch_tree_s replica = {
        .elements = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(BSEARCH_TREE_DATA_TYPE)),
        .node[BSEARCH_TREE_LEFT]  = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(size_t)),
        .node[BSEARCH_TREE_RIGHT] = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(size_t)),
        .parent = BSEARCH_TREE_ALLOC(BSEARCH_TREE_SIZE * sizeof(size_t)),
        .size = tree.size, .compare = tree.compare, .root = tree.root,
    };

    BSEARCH_TREE_ASSERT(replica.elements && "[ERROR] Memory allocation failed.");
    BSEARCH_TREE_ASSERT(replica.node[BSEARCH_TREE_LEFT] && "[ERROR] Memory allocation failed.");
    BSEARCH_TREE_ASSERT(replica.node[BSEARCH_TREE_RIGHT] && "[ERROR] Memory allocation failed.");
    BSEARCH_TREE_ASSERT(replica.parent && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < tree.size; ++i) {
        replica.elements[i] = copy(tree.elements[i]);
    }

    memcpy(replica.node[BSEARCH_TREE_LEFT], tree.node[BSEARCH_TREE_LEFT], tree.size * sizeof(size_t));
    memcpy(replica.node[BSEARCH_TREE_RIGHT], tree.node[BSEARCH_TREE_RIGHT], tree.size * sizeof(size_t));
    memcpy(replica.parent, tree.parent, tree.size * sizeof(size_t));

    return replica;
}

static inline bool is_empty_bsearch_tree(const bsearch_tree_s tree) {
    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    return !(tree.size);
}

static inline bool is_full_bsearch_tree(const bsearch_tree_s tree) {
    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    return (BSEARCH_TREE_SIZE == tree.size);
}

static inline void insert_bsearch_tree(bsearch_tree_s * tree, const BSEARCH_TREE_DATA_TYPE element) {
    BSEARCH_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BSEARCH_TREE_ASSERT(tree->size != BSEARCH_TREE_SIZE && "[ERROR] Can't insert into full tree.");

    BSEARCH_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t parent = BSEARCH_TREE_SIZE; // initially invalid for the head case when tree is empty
    size_t * child = &(tree->root); // pointer to later change actual index of the empty child
    while (BSEARCH_TREE_SIZE != (*child)) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree->compare(element, tree->elements[(*child)]);
        const size_t node_index = comparison <= 0 ? BSEARCH_TREE_LEFT : BSEARCH_TREE_RIGHT;

        // change parent to child and go to next child node
        parent = (*child);
        child = tree->node[node_index] + (*child);
    }

    (*child) = tree->size; // change child index from invalid value to next empty index in array
    memcpy(tree->elements + (*child), &element, sizeof(BSEARCH_TREE_DATA_TYPE));
    // make child's left and right indexes point to invalid value
    tree->node[BSEARCH_TREE_LEFT][(*child)] = tree->node[BSEARCH_TREE_RIGHT][(*child)] = BSEARCH_TREE_SIZE;
    // make child's parent into parent
    tree->parent[(*child)] = parent;

    tree->size++;
}

static inline BSEARCH_TREE_DATA_TYPE remove_bsearch_tree(bsearch_tree_s * tree, const BSEARCH_TREE_DATA_TYPE element) {
    BSEARCH_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    BSEARCH_TREE_ASSERT(tree->size && "[ERROR] Can't remove from empty tree.");
    BSEARCH_TREE_ASSERT(BSEARCH_TREE_SIZE != tree->root && "[ERROR] Invalid root node index.");

    BSEARCH_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t * node = &(tree->root); // pointer to later change actual index of the empty child
    while (BSEARCH_TREE_SIZE != (*node)) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree->compare(element, tree->elements[(*node)]);
        if (!comparison) {
            // go to, since remove logic in too long and nested
            goto REMOVE_ELEMENT;
        }

        const size_t node_index = comparison <= 0 ? BSEARCH_TREE_LEFT : BSEARCH_TREE_RIGHT;

        // change parent to child and go to next child node
        node = tree->node[node_index] + (*node);
    }

    // element was NOT found, thus return an error
    BSEARCH_TREE_ASSERT(false && "[ERROR] Element not found in tree.");
    exit(EXIT_FAILURE);

REMOVE_ELEMENT:

    BSEARCH_TREE_DATA_TYPE removed = tree->elements[(*node)];
    tree->size--;

    // calculate the rightmost depth of the left child
    size_t left_depth = 0, * left_node = node;
    for (size_t * l = tree->node[BSEARCH_TREE_LEFT] + (*left_node); BSEARCH_TREE_SIZE != (*l); l = tree->node[BSEARCH_TREE_RIGHT] + (*l)) {
        left_depth++;
        left_node = l;
    }

    // calculate the leftmost depth of the right child
    size_t right_depth = 0, * right_node = node;
    for (size_t * r = tree->node[BSEARCH_TREE_RIGHT] + (*right_node); BSEARCH_TREE_SIZE != (*r); r = tree->node[BSEARCH_TREE_LEFT] + (*r)) {
        right_depth++;
        right_node = r;
    }

    const size_t hole_index = left_depth > right_depth ? (*left_node) : (*right_node);
    tree->elements[(*node)] = tree->elements[hole_index];
    if (left_depth > right_depth) {
        if (BSEARCH_TREE_SIZE != tree->node[BSEARCH_TREE_LEFT][(*left_node)]) { // if right child exists cut off parent
            tree->parent[tree->node[BSEARCH_TREE_LEFT][(*left_node)]] = tree->parent[(*left_node)];
        }
        (*left_node) = tree->node[BSEARCH_TREE_LEFT][(*left_node)]; // cut off new hole index
    } else {
        if (BSEARCH_TREE_SIZE != tree->node[BSEARCH_TREE_RIGHT][(*right_node)]) { // if left child exists cut off parent
            tree->parent[tree->node[BSEARCH_TREE_RIGHT][(*right_node)]] = tree->parent[(*right_node)];
        }
        (*right_node) = tree->node[BSEARCH_TREE_RIGHT][(*right_node)]; // cut off new hole index
    }

    if (tree->size && tree->root == tree->size) { // if head node is last array element then change index to removed one
        tree->root = hole_index;
    }

    // cut hole node from the rest of the tree
    tree->node[BSEARCH_TREE_LEFT][hole_index] = tree->node[BSEARCH_TREE_RIGHT][hole_index] = tree->parent[hole_index] = hole_index;

    // replace removed element with rightmost array one (or fill hole with valid element)
    tree->elements[hole_index] = tree->elements[tree->size];
    tree->node[BSEARCH_TREE_LEFT][hole_index] = tree->node[BSEARCH_TREE_LEFT][tree->size];
    tree->node[BSEARCH_TREE_RIGHT][hole_index] = tree->node[BSEARCH_TREE_RIGHT][tree->size];
    tree->parent[hole_index] = tree->parent[tree->size];

    // redirect parent and children of rightmost array node if they dont overlap with removed index
    const size_t left_last = tree->node[BSEARCH_TREE_LEFT][tree->size];
    if (BSEARCH_TREE_SIZE != left_last) {
        tree->parent[left_last] = hole_index;
    }

    const size_t right_last = tree->node[BSEARCH_TREE_RIGHT][tree->size];
    if (BSEARCH_TREE_SIZE != right_last) {
        tree->parent[right_last] = hole_index;
    }

    const size_t parent_last = tree->parent[tree->size];
    if (BSEARCH_TREE_SIZE != parent_last) {
        const int comparison = tree->compare(tree->elements[tree->size], tree->elements[parent_last]);
        const size_t node_index = comparison <= 0 ? BSEARCH_TREE_LEFT : BSEARCH_TREE_RIGHT;
        tree->node[node_index][parent_last] = hole_index;
    }

    return removed;
}

static inline bool contains_bsearch_tree(const bsearch_tree_s tree, const BSEARCH_TREE_DATA_TYPE element) {
    BSEARCH_TREE_ASSERT(tree.size && "[ERROR] Can't check empty tree.");
    BSEARCH_TREE_ASSERT(BSEARCH_TREE_SIZE != tree.root && "[ERROR] Invalid root node index.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    for (size_t node = tree.root; BSEARCH_TREE_SIZE != node;) {
        // calculate and determine next child node, i.e. if left or right child
        const int comparison = tree.compare(tree.elements[node], element);
        if (!comparison) {
            return true;
        }

        const size_t node_index = comparison <= 0 ? BSEARCH_TREE_LEFT : BSEARCH_TREE_RIGHT;
        node = tree.node[node_index][node]; // go to next child node
    }

    return false;
}

static inline BSEARCH_TREE_DATA_TYPE get_min_bsearch_tree(const bsearch_tree_s tree) {
    BSEARCH_TREE_ASSERT(tree.size && "[ERROR] Can't get from empty tree.");
    BSEARCH_TREE_ASSERT(BSEARCH_TREE_SIZE != tree.root && "[ERROR] Invalid root node index.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t minimum_node = tree.root;
    for (size_t i = tree.node[BSEARCH_TREE_LEFT][minimum_node]; BSEARCH_TREE_SIZE != i; i = tree.node[BSEARCH_TREE_LEFT][i]) {
        minimum_node = i;
    }

    return tree.elements[minimum_node];
}

static inline BSEARCH_TREE_DATA_TYPE get_max_bsearch_tree(const bsearch_tree_s tree) {
    BSEARCH_TREE_ASSERT(tree.size && "[ERROR] Can't get from empty tree.");
    BSEARCH_TREE_ASSERT(BSEARCH_TREE_SIZE != tree.root && "[ERROR] Invalid root node index.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t maximum_node = tree.root;
    for (size_t i = tree.node[BSEARCH_TREE_RIGHT][maximum_node]; BSEARCH_TREE_SIZE != i; i = tree.node[BSEARCH_TREE_RIGHT][i]) {
        maximum_node = i;
    }

    return tree.elements[maximum_node];
}

static inline BSEARCH_TREE_DATA_TYPE remove_min_bsearch_tree(bsearch_tree_s * tree) {
    BSEARCH_TREE_ASSERT(tree->size && "[ERROR] Can't get from empty tree.");
    BSEARCH_TREE_ASSERT(BSEARCH_TREE_SIZE != tree->root && "[ERROR] Invalid root node index.");

    BSEARCH_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t * minimum_node = &(tree->root);
    for (size_t * i = tree->node[BSEARCH_TREE_LEFT] + (*minimum_node); BSEARCH_TREE_SIZE != (*i); i = tree->node[BSEARCH_TREE_LEFT] + (*i)) {
        minimum_node = i;
    }

    BSEARCH_TREE_DATA_TYPE removed = tree->elements[(*minimum_node)];
    tree->size--;

    const size_t hole_index = (*minimum_node);
    (*minimum_node) = tree->node[BSEARCH_TREE_RIGHT][(*minimum_node)];

    // cut hole node from the rest of the tree
    tree->node[BSEARCH_TREE_LEFT][hole_index] = tree->node[BSEARCH_TREE_RIGHT][hole_index] = tree->parent[hole_index] = hole_index;

    // replace removed element with rightmost array one (or fill hole with valid element)
    tree->elements[hole_index] = tree->elements[tree->size];
    tree->node[BSEARCH_TREE_LEFT][hole_index] = tree->node[BSEARCH_TREE_LEFT][tree->size];
    tree->node[BSEARCH_TREE_RIGHT][hole_index] = tree->node[BSEARCH_TREE_RIGHT][tree->size];
    tree->parent[hole_index] = tree->parent[tree->size];

    // redirect parent and children of rightmost last array node if they dont overlap with removed index
    const size_t left_last = tree->node[BSEARCH_TREE_LEFT][tree->size];
    if (BSEARCH_TREE_SIZE != left_last) {
        tree->parent[left_last] = hole_index;
    }

    const size_t right_last = tree->node[BSEARCH_TREE_RIGHT][tree->size];
    if (BSEARCH_TREE_SIZE != right_last) {
        tree->parent[right_last] = hole_index;
    }

    const size_t parent_last = tree->parent[tree->size];
    if (BSEARCH_TREE_SIZE != parent_last) {
        const int comparison = tree->compare(tree->elements[tree->size], tree->elements[parent_last]);
        const size_t node_index = comparison <= 0 ? BSEARCH_TREE_LEFT : BSEARCH_TREE_RIGHT;
        tree->node[node_index][parent_last] = hole_index;
    }

    return removed;
}

static inline BSEARCH_TREE_DATA_TYPE remove_max_bsearch_tree(bsearch_tree_s * tree) {
    BSEARCH_TREE_ASSERT(tree->size && "[ERROR] Can't get from empty tree.");
    BSEARCH_TREE_ASSERT(BSEARCH_TREE_SIZE != tree->root && "[ERROR] Invalid root node index.");

    BSEARCH_TREE_ASSERT(tree->compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree->elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree->size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    size_t * maximum_node = &(tree->root);
    for (size_t * i = tree->node[BSEARCH_TREE_RIGHT] + (*maximum_node); BSEARCH_TREE_SIZE != (*i); i = tree->node[BSEARCH_TREE_RIGHT] + (*i)) {
        maximum_node = i;
    }

    BSEARCH_TREE_DATA_TYPE removed = tree->elements[(*maximum_node)];
    tree->size--;

    const size_t hole_index = (*maximum_node);
    (*maximum_node) = tree->node[BSEARCH_TREE_LEFT][(*maximum_node)];

    // cut hole node from the rest of the tree
    tree->node[BSEARCH_TREE_LEFT][hole_index] = tree->node[BSEARCH_TREE_RIGHT][hole_index] = tree->parent[hole_index] = hole_index;

    // replace removed element with rightmost array one (or fill hole with valid element)
    tree->elements[hole_index] = tree->elements[tree->size];
    tree->node[BSEARCH_TREE_LEFT][hole_index] = tree->node[BSEARCH_TREE_LEFT][tree->size];
    tree->node[BSEARCH_TREE_RIGHT][hole_index] = tree->node[BSEARCH_TREE_RIGHT][tree->size];
    tree->parent[hole_index] = tree->parent[tree->size];

    // redirect parent and children of rightmost last array node if they dont overlap with removed index
    const size_t left_last = tree->node[BSEARCH_TREE_LEFT][tree->size];
    if (BSEARCH_TREE_SIZE != left_last) {
        tree->parent[left_last] = hole_index;
    }

    const size_t right_last = tree->node[BSEARCH_TREE_RIGHT][tree->size];
    if (BSEARCH_TREE_SIZE != right_last) {
        tree->parent[right_last] = hole_index;
    }

    const size_t parent_last = tree->parent[tree->size];
    if (BSEARCH_TREE_SIZE != parent_last) {
        const int comparison = tree->compare(tree->elements[tree->size], tree->elements[parent_last]);
        const size_t node_index = comparison <= 0 ? BSEARCH_TREE_LEFT : BSEARCH_TREE_RIGHT;
        tree->node[node_index][parent_last] = hole_index;
    }

    return removed;
}

static inline void inorder_bsearch_tree(const bsearch_tree_s tree, const operate_bsearch_tree_fn operate, void * args) {
    BSEARCH_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct in_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = BSEARCH_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    BSEARCH_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    // push root node onto stack and initially save it into variable
    size_t node = tree.root;
    while (stack.size || BSEARCH_TREE_SIZE != node) { // while stack is not empty OR node is valid
        if (BSEARCH_TREE_SIZE != node) { // if node is valid push it onto the stack and go to node's left child
            stack.elements[stack.size++] = node;
            node = tree.node[BSEARCH_TREE_LEFT][node];
        } else { // else node is invalid, thus pop a new node from the stack, operate on element, and go to node's right child
            node = stack.elements[--stack.size];

            if (!operate(tree.elements + node, args)) {
                break;
            }

            node = tree.node[BSEARCH_TREE_RIGHT][node];
        }
    }

    BSEARCH_TREE_FREE(stack.elements);
}

static inline void preorder_bsearch_tree(const bsearch_tree_s tree, const operate_bsearch_tree_fn operate, void * args) {
    BSEARCH_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct pre_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = BSEARCH_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    BSEARCH_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    if (tree.size) {
        stack.elements[stack.size++] = tree.root;
    }

    while (stack.size && operate(tree.elements + stack.elements[stack.size - 1], args)) {
        const size_t node = stack.elements[--stack.size];

        const size_t right_child = tree.node[BSEARCH_TREE_RIGHT][node];
        if (BSEARCH_TREE_SIZE != right_child) {
            stack.elements[stack.size++] = right_child;
        }

        const size_t left_child = tree.node[BSEARCH_TREE_LEFT][node];
        if (BSEARCH_TREE_SIZE != left_child) {
            stack.elements[stack.size++] = left_child;
        }
    }

    BSEARCH_TREE_FREE(stack.elements);
}

static inline void postorder_bsearch_tree(const bsearch_tree_s tree, const operate_bsearch_tree_fn operate, void * args) {
    BSEARCH_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple stack to manage depth first in-order traversal of node indexes
    struct post_stack { size_t size; size_t * elements; } stack = {
        .size = 0, .elements = BSEARCH_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    BSEARCH_TREE_ASSERT(stack.elements && "[ERROR] Memory allocation failed.");

    // push root node onto stack and initially save it into variable
    size_t node = tree.root;
    size_t last = BSEARCH_TREE_SIZE;
    while (stack.size || BSEARCH_TREE_SIZE != node) { // while stack is not empty OR node is valid
        if (BSEARCH_TREE_SIZE != node) { // if node is valid push it onto the stack and go to node's left child
            stack.elements[stack.size++] = node;
            node = tree.node[BSEARCH_TREE_LEFT][node];
        } else { // else node is invalid, thus pop a new node from the stack, operate on element, and go to node's right child
            const size_t peek = stack.elements[stack.size - 1];

            const size_t peek_right_child = tree.node[BSEARCH_TREE_RIGHT][peek];
            if (BSEARCH_TREE_SIZE != peek_right_child && peek_right_child != last) {
                node = peek_right_child;
            } else {
                if (!operate(tree.elements + node, args)) {
                    break;
                }

                last = stack.elements[--stack.size];
            }
        }
    }

    BSEARCH_TREE_FREE(stack.elements);
}

static inline void level_order_bsearch_tree(const bsearch_tree_s tree, const operate_bsearch_tree_fn operate, void * args) {
    BSEARCH_TREE_ASSERT(operate && "[ERROR] 'operate' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    // create simple queue to manage breath first level order traversal of node indexes
    struct level_queue { size_t size, current; size_t * elements; } queue = {
        .size = 0, .current = 0, .elements = BSEARCH_TREE_ALLOC(tree.size * sizeof(size_t)),
    };
    BSEARCH_TREE_ASSERT(queue.elements && "[ERROR] Memory allocation failed.");

    if (tree.size) { // if tree isn't empty push root node
        queue.elements[queue.current + queue.size++] = tree.root;
    }

    // while queue isn't empty operate on element, pop parent and push valid children
    while (queue.size && operate(tree.elements + queue.elements[queue.current], args)) {
        // pop index
        const size_t popped_index = queue.elements[queue.current++];
        queue.size--;

        // push left child of popped parent to the top of the queue
        const size_t left_child = tree.node[BSEARCH_TREE_LEFT][popped_index];
        if (BSEARCH_TREE_SIZE != left_child) {
            queue.elements[queue.current + queue.size++] = left_child;
        }

        // push right child of popped parent to the top of the queue
        const size_t right_child = tree.node[BSEARCH_TREE_RIGHT][popped_index];
        if (BSEARCH_TREE_SIZE != right_child) {
            queue.elements[queue.current + queue.size++] = right_child;
        }
    }

    BSEARCH_TREE_FREE(queue.elements);
}

static inline void map_bsearch_tree(const bsearch_tree_s tree, const manage_bsearch_tree_fn manage, void * args) {
    BSEARCH_TREE_ASSERT(manage && "[ERROR] 'manage' parameter is NULL.");

    BSEARCH_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    BSEARCH_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_LEFT] && "[ERROR] 'node[BSEARCH_TREE_LEFT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.node[BSEARCH_TREE_RIGHT] && "[ERROR] 'node[BSEARCH_TREE_RIGHT]' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    BSEARCH_TREE_ASSERT(tree.size <= BSEARCH_TREE_SIZE && "[ERROR] Invalid tree size.");

    manage(tree.elements, tree.size, args);
}

#endif // BSEARCH_TREE_H
