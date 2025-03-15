#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include <stdlib.h>  // imports size_t, malloc, realloc, free
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy, memmove

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

// list mode macros in octal to prevent future overlap with other data structure modes
#define FINITE_ALLOCATED_MATRIX_GRAPH    72
#define INFINITE_REALLOC_MATRIX_GRAPH    73
#define FINITE_PRERPOCESSOR_MATRIX_GRAPH 74

#define INFINITE_MATRIX_GRAPH INFINITE_REALLOC_MATRIX_GRAPH
#define FINITE_MATRIX_GRAPH   FINITE_ALLOCATED_MATRIX_GRAPH

#define MATRIX_GRAPH_MODE FINITE_ALLOCATED_MATRIX_GRAPH
//#define MATRIX_GRAPH_MODE INFINITE_REALLOC_MATRIX_GRAPH
//#define MATRIX_GRAPH_MODE FINITE_PRERPOCESSOR_MATRIX_GRAPH
// Graph mode that can be set to FINITE_ALLOCATED_MATRIX_GRAPH, INFINITE_REALLOC_MATRIX_GRAPH or FINITE_PRERPOCESSOR_MATRIX_GRAPH
// Default: INFINITE_ALLOCATED_MATRIX_GRAPH
#ifndef MATRIX_GRAPH_MODE

#define MATRIX_GRAPH_MODE INFINITE_MATRIX_GRAPH

#endif

// Check to make sure a valid list mode is selected.
#if (MATRIX_GRAPH_MODE != FINITE_ALLOCATED_MATRIX_GRAPH) && (MATRIX_GRAPH_MODE != INFINITE_REALLOC_MATRIX_GRAPH) && (MATRIX_GRAPH_MODE != FINITE_PRERPOCESSOR_MATRIX_GRAPH)

#error Invalid type of list mode.

#endif

#ifndef MATRIX_GRAPH_VERTEX_DATA_TYPE

/// @brief Vartex element datatype macro that can be changed via '#define MATRIX_GRAPH_VERTEX_DATA_TYPE [datatype]'.
#define MATRIX_GRAPH_VERTEX_DATA_TYPE void*

#endif

#ifndef MATRIX_GRAPH_EDGE_DATA_TYPE

/// @brief Edge value datatype macro that can be changed via '#define MATRIX_GRAPH_VERTEX_DATA_TYPE [datatype]'.
#define MATRIX_GRAPH_EDGE_DATA_TYPE int

#endif

#ifndef EMPTY_MATRIX_GRAPH_EDGE

#define EMPTY_MATRIX_GRAPH_EDGE (MATRIX_GRAPH_EDGE_DATA_TYPE) { 0 }

#endif

#ifndef MATRIX_GRAPH_ASSERT

#include <assert.h>  // imports assert for debugging
/// @brief Assertion macro that can be changed  via '#define MATRIX_GRAPH_ALLOC [assert]'.
#define MATRIX_GRAPH_ASSERT assert

#endif

#ifndef MATRIX_GRAPH_ALLOC

/// @brief Memory allocation macro that can be changed via '#define MATRIX_GRAPH_ALLOC [allocator]'.
#define MATRIX_GRAPH_ALLOC malloc

#endif

#ifndef MATRIX_GRAPH_REALLOC

/// @brief Memory reallocation macro that can be changed via '#define MATRIX_GRAPH_REALLOC [reallocator]'.
#define MATRIX_GRAPH_REALLOC realloc

#endif

#ifndef MATRIX_GRAPH_FREE

/// @brief Memory freeing macro that can be changed via '#define MATRIX_GRAPH_FREE [free]'.
#define MATRIX_GRAPH_FREE free

#endif

/// @brief Function pointer to create a deep/shallow copy for graph vertex/element.
typedef MATRIX_GRAPH_VERTEX_DATA_TYPE (*copy_vertex_matrix_graph_fn)    (const MATRIX_GRAPH_VERTEX_DATA_TYPE);
/// @brief Function pointer to destroy/free a vertex element for graph element.
typedef void                          (*destroy_vertex_matrix_graph_fn) (MATRIX_GRAPH_VERTEX_DATA_TYPE *);
/// @brief Function pointer to comapre two graph elements. Returns zero if they're equal, a negative number if
/// 'less than', else a positive number if 'more than'.
typedef int                           (*compare_vertex_matrix_graph_fn) (const MATRIX_GRAPH_VERTEX_DATA_TYPE, const MATRIX_GRAPH_VERTEX_DATA_TYPE);
/// @brief Function pointer to operate on a single graph element based on generic arguments.
typedef bool                          (*operate_vertex_matrix_graph_fn) (MATRIX_GRAPH_VERTEX_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                          (*manage_vertex_matrix_graph_fn)  (MATRIX_GRAPH_VERTEX_DATA_TYPE *, const size_t, void *);

#if   FINITE_ALLOCATED_MATRIX_GRAPH    == MATRIX_GRAPH_MODE

typedef struct graph {
    size_t size, max;
    MATRIX_GRAPH_VERTEX_DATA_TYPE * vertices;
    MATRIX_GRAPH_EDGE_DATA_TYPE   * edges;
} graph_s;

/// @brief Creates an empty graph of zero size. Edges are automatically set to zero using memset.
/// @param max Maximum positive nonzero size of graph.
/// @return Graph structure.
static inline graph_s create_matrix_graph(const size_t max) {
    MATRIX_GRAPH_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const size_t matrix_size = (max * (max - 1)) >> 1; // we only need half the matrix without index x==y elements
    const graph_s graph = {
        .vertices = MATRIX_GRAPH_ALLOC(max * sizeof(MATRIX_GRAPH_VERTEX_DATA_TYPE)),
        .edges = MATRIX_GRAPH_ALLOC(matrix_size * sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)),
        .max = max, .size = 0,
    };
    const MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    for (size_t i = 0; i < matrix_size; i++) {
        graph.edges[i] = empty;
    }

    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Memory allocation failed.");

    return graph;
}

/// @brief Destroys the graph and sets size to zero. The destroyed graph should not be used after calling this
/// function, else create a new graph.
/// @param graph Pointer to graph structure.
/// @param destroy Function pointer to destroy/free each element in graph. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_matrix_graph(graph_s * graph, const destroy_vertex_matrix_graph_fn destroy_vertex) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");

    for (size_t i = 0; destroy_vertex && i < graph->size; i++) {
        destroy_vertex(graph->vertices + i);
    }
    
    MATRIX_GRAPH_FREE(graph->vertices);
    MATRIX_GRAPH_FREE(graph->edges);
    (*graph) = (graph_s) { 0 };
}

/// @brief Inserts a vertex element into graph.
/// @param graph Pointer to graph structure.
/// @param element Vertex element to insert into graph.
/// @return iondex of inserted vertex element.
static inline size_t insert_vertex_matrix_graph(graph_s * graph, const MATRIX_GRAPH_VERTEX_DATA_TYPE element) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(graph->size < graph->max && "[ERROR] Maximum size reached.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph elements array is NULL.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph matrix array is NULL.");

    memcpy(graph->vertices + graph->size, &element, sizeof(MATRIX_GRAPH_VERTEX_DATA_TYPE));  // copy element into graph element array

    return (graph->size)++; // return element index and increment size
}

/// @brief Removes vertex element based on its index.
/// @param graph Pointer to graph structure.
/// @param index Special index of vertex.
/// @return Removed element vertex.
/// @note When element vertex is removed 
static inline MATRIX_GRAPH_VERTEX_DATA_TYPE remove_vertex_matrix_graph(graph_s * graph, const size_t index) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(graph->size && "[ERROR] Can't remove vertex from empty graph.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph elements array is NULL.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph matrix array is NULL.");
    MATRIX_GRAPH_ASSERT(index < graph->size && "[ERRRO] index parameter must be less than graph size.");

    MATRIX_GRAPH_VERTEX_DATA_TYPE found = graph->vertices[index];
    graph->size--;

    const size_t last_start  = ((graph->size) * (graph->size - 1)) >> 1;
    MATRIX_GRAPH_EDGE_DATA_TYPE * last_edges = graph->edges + last_start;
    if (index != graph->size) { // if index doesn't point to last element
        const size_t row_index_start = (index * (index - 1)) >> 1;

        memcpy(graph->edges + row_index_start, last_edges, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE) * index);

        size_t col_index_start = index + (index * (index + 1) >> 1);
        for (size_t i = index + 1; i < graph->size; i++) {
            graph->edges[col_index_start + i - 1] = last_edges[i];
            col_index_start += i - 1;
        }
        graph->vertices[index] = graph->vertices[graph->size];
    }

    MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    for (size_t i = 0; i < graph->size; i++) {
        memcpy(last_edges + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE));
    }

    return found;
}

static inline void insert_edge_matrix_graph(const graph_s graph, const size_t index_one, const size_t index_two, const MATRIX_GRAPH_EDGE_DATA_TYPE value) {
    MATRIX_GRAPH_ASSERT(index_one < graph.size && "[ERRRO] 'index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(index_two < graph.size && "[ERRRO] 'index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph elements array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph matrix array is NULL.");

    const size_t exlude = index_one ^ index_two;
    const size_t maximum = index_one > index_two ? exlude ^ index_one : exlude ^ index_two;
    const size_t minimum = exlude ^ maximum;
    
    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;
    memcpy(graph.edges + row_maximum_start + minimum, &value, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE));
}

static inline MATRIX_GRAPH_EDGE_DATA_TYPE remove_edge_matrix_graph(const graph_s graph, const size_t index_one, const size_t index_two) {
    MATRIX_GRAPH_ASSERT(index_one < graph.size && "[ERRRO] 'index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(index_two < graph.size && "[ERRRO] 'index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph elements array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph matrix array is NULL.");

    const size_t exlude = index_one ^ index_two;
    const size_t maximum = index_one > index_two ? exlude ^ index_one : exlude ^ index_two;
    const size_t minimum = exlude ^ maximum;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;
    MATRIX_GRAPH_EDGE_DATA_TYPE found = graph.edges[row_maximum_start + minimum];
    graph.edges[row_maximum_start + minimum] = EMPTY_MATRIX_GRAPH_EDGE;

    return found;
}

static inline bool is_edge_matrix_graph(const graph_s graph, const size_t index_one, const size_t index_two) {
    MATRIX_GRAPH_ASSERT(index_one < graph.size && "[ERRRO] 'index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(index_two < graph.size && "[ERRRO] 'index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph elements array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph matrix array is NULL.");

    const size_t exlude = index_one ^ index_two;
    const size_t maximum = index_one > index_two ? exlude ^ index_one : exlude ^ index_two;
    const size_t minimum = exlude ^ maximum;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;

    MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    return memcmp(graph.edges + row_maximum_start + minimum, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE));
}

static inline void breadth_first_search_matrix_graph(graph_s * graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(start_index < graph->size && "[ERROR] 'start_index' parameter must be less than graph size.");

    bool * visited_vertex_array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(bool));
    MATRIX_GRAPH_ASSERT(visited_vertex_array && "[ERROR] Memory allocation failed.");
    for (size_t i = 0; i < graph->size; i++) {
        visited_vertex_array[i] = false;
    }
    
    struct breadth_first_search_queue { size_t * array; size_t size, current; } queue = {
        .array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)), .current = 0, .size = 0,
    };
    MATRIX_GRAPH_ASSERT(queue.array && "[ERROR] Memory allocation failed.");

    if (graph->size) {
        queue.array[queue.current + queue.size++] = start_index;
        visited_vertex_array[start_index] = true;
    }

    MATRIX_GRAPH_VERTEX_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    while (queue.size) {
        const size_t current_index = queue.array[queue.current++];
        queue.size--;

        if (!operate(graph->vertices + current_index, args)) {
            break;
        }

        const size_t row_index_start = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < current_index; i++) {
            if (memcmp(graph->edges + row_index_start + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && visited_vertex_array[i] != true) {
                visited_vertex_array[i] = true;
                queue.array[queue.current + queue.size++] = i;
            }
        }
        
        for (size_t i = current_index + 1; i < graph->size - 1; i++) {
            const size_t col_index_start = ((i * (i - 1)) >> 1) + current_index;
            if (memcmp(graph->edges + col_index_start, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && visited_vertex_array[i] != true) {
                visited_vertex_array[i] = true;
                queue.array[queue.current + queue.size++] = i;
            }
        }
    }

    MATRIX_GRAPH_FREE(visited_vertex_array);
    MATRIX_GRAPH_FREE(queue.array);
}

static inline void depth_first_search_matrix_graph(graph_s * graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(start_index < graph->size && "[ERROR] 'start_index' parameter must be less than graph size.");

    bool * visited_vertex_array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(bool));
    MATRIX_GRAPH_ASSERT(visited_vertex_array && "[ERROR] Memory allocation failed.");
    for (size_t i = 0; i < graph->size; i++) {
        visited_vertex_array[i] = false;
    }

    struct depth_first_search_stack { size_t * array; size_t size; } stack = {
        .array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)), .size = 0,
    };
    MATRIX_GRAPH_ASSERT(stack.array && "[ERROR] Memory allocation failed.");

    if (graph->size) {
        stack.array[stack.size++] = start_index;
        visited_vertex_array[start_index] = true;
    }

    MATRIX_GRAPH_VERTEX_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    while (stack.size) {
        const size_t current_index = stack.array[--stack.size];

        if (!operate(graph->vertices + current_index, args)) {
            break;
        }

        const size_t row_index_start = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < current_index; i++) {
            if (memcmp(graph->edges + row_index_start + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && visited_vertex_array[i] != true) {
                visited_vertex_array[i] = true;
                stack.array[stack.size++] = i;
            }
        }

        for (size_t i = current_index + 1; i < graph->size - 1; i++) {
            const size_t col_index_start = ((i * (i - 1)) >> 1) + current_index;
            if (memcmp(graph->edges + col_index_start, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && visited_vertex_array[i] != true) {
                visited_vertex_array[i] = true;
                stack.array[stack.size++] = i;
            }
        }
    }
    
    MATRIX_GRAPH_FREE(visited_vertex_array);
    MATRIX_GRAPH_FREE(stack.array);
}

#elif INFINITE_REALLOC_MATRIX_GRAPH    == MATRIX_GRAPH_MODE
#elif FINITE_PRERPOCESSOR_MATRIX_GRAPH == MATRIX_GRAPH_MODE
#endif

#endif // MATRIX_GRAPH_H