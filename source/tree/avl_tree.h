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

    const avl_tree_s tree = {
        .elements = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(AVL_TREE_DATA_TYPE)),
        .node[AVL_TREE_LEFT]  = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .node[AVL_TREE_RIGHT] = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .parent = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .height = AVL_TREE_ALLOC(AVL_TREE_SIZE * sizeof(size_t)),
        .size = 0, .compare = compare, .root = AVL_TREE_SIZE,
    };

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
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    for (AVL_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    AVL_TREE_FREE(tree->elements);
    AVL_TREE_FREE(tree->node[AVL_TREE_LEFT]);
    AVL_TREE_FREE(tree->node[AVL_TREE_RIGHT]);
    AVL_TREE_FREE(tree->parent);
    AVL_TREE_FREE(tree->height);

    tree->elements = NULL;
    tree->node[AVL_TREE_LEFT] = NULL;
    tree->node[AVL_TREE_RIGHT] = NULL;
    tree->parent = NULL;
    tree->height = NULL;

    tree->root = BSEARCH_TREE_SIZE;
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
    AVL_TREE_ASSERT(tree->size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    for (AVL_TREE_DATA_TYPE * e = tree->elements; e < tree->elements + tree->size; e++) {
        destroy(e);
    }

    tree->root = BSEARCH_TREE_SIZE;
    tree->size = 0;
}

static inline avl_tree_s copy_avl_tree(const avl_tree_s tree, const copy_avl_tree_fn copy) {
    AVL_TREE_ASSERT(tree && "[ERROR] 'tree' parameter is NULL.");
    AVL_TREE_ASSERT(copy && "[ERROR] 'copy' parameter is NULL.");

    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

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

    for (size_t i = 0; i < tree.size; ++i) {
        replica.elements[i] = copy(tree.elements[i]);
    }

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
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    return !(tree.size);
}
static inline bool is_full_avl_tree(const avl_tree_s tree) {
    AVL_TREE_ASSERT(tree.compare && "[ERROR] 'compare' function is NULL.");
    AVL_TREE_ASSERT(tree.elements && "[ERROR] 'elements' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_LEFT] && "[ERROR] 'node[AVL_TREE_LEFT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.node[AVL_TREE_RIGHT] && "[ERROR] 'node[AVL_TREE_RIGHT]' pointer is NULL.");
    AVL_TREE_ASSERT(tree.parent && "[ERROR] 'parent' pointer is NULL.");
    AVL_TREE_ASSERT(tree.size <= AVL_TREE_SIZE && "[ERROR] Invalid tree size.");

    return (AVL_TREE_SIZE == tree.size);
}

static inline void insert_avl_tree(avl_tree_s * tree, const AVL_TREE_DATA_TYPE element) {

}

static inline AVL_TREE_DATA_TYPE remove_avl_tree(avl_tree_s * tree, const AVL_TREE_DATA_TYPE element) {
    return (AVL_TREE_DATA_TYPE) { 0 };
}

static inline bool contains_avl_tree(const avl_tree_s tree, const AVL_TREE_DATA_TYPE element) {
    return false;
}

static inline AVL_TREE_DATA_TYPE get_min_avl_tree(const avl_tree_s tree) {
    return (AVL_TREE_DATA_TYPE) { 0 };
}

static inline AVL_TREE_DATA_TYPE get_max_avl_tree(const avl_tree_s tree) {
    return (AVL_TREE_DATA_TYPE) { 0 };
}

static inline AVL_TREE_DATA_TYPE remove_min_avl_tree(avl_tree_s * tree) {
    return (AVL_TREE_DATA_TYPE) { 0 };
}

static inline AVL_TREE_DATA_TYPE remove_max_avl_tree(avl_tree_s * tree) {
    return (AVL_TREE_DATA_TYPE) { 0 };
}

static inline void inorder_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {

}

static inline void preorder_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {

}

static inline void postorder_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {

}

static inline void level_order_avl_tree(const avl_tree_s tree, const operate_avl_tree_fn operate, void * args) {

}

static inline void map_avl_tree(const avl_tree_s tree, const manage_avl_tree_fn manage, void * args) {

}

#endif // AVL_TREE_H
