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

#define FINITE_ALLOCATED_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH    71
#define INFINITE_REALLOC_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH    72
#define FINITE_PRERPOCESSOR_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH 73
#define FINITE_ALLOCATED_MATRIX_GRAPH                              74
#define INFINITE_REALLOC_MATRIX_GRAPH                              75
#define FINITE_PRERPOCESSOR_MATRIX_GRAPH                           76

#define INFINITE_MATRIX_GRAPH INFINITE_REALLOC_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH
#define FINITE_MATRIX_GRAPH   FINITE_ALLOCATED_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH

#define MATRIX_GRAPH_MODE FINITE_ALLOCATED_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH
//#define MATRIX_GRAPH_MODE INFINITE_REALLOC_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH
//#define MATRIX_GRAPH_MODE FINITE_PRERPOCESSOR_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH
// Graph mode that can be set to FINITE_ALLOCATED_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH, INFINITE_REALLOC_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH
// or FINITE_PRERPOCESSOR_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH
// Default: INFINITE_ALLOCATED_MATRIX_GRAPH
#ifndef MATRIX_GRAPH_MODE

#define MATRIX_GRAPH_MODE INFINITE_MATRIX_GRAPH

#endif

// Check to make sure a valid double_list mode is selected.
#if (MATRIX_GRAPH_MODE != FINITE_ALLOCATED_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH) && (MATRIX_GRAPH_MODE != INFINITE_REALLOC_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH) && (MATRIX_GRAPH_MODE != FINITE_PRERPOCESSOR_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH)

#error Invalid type of list mode.

#endif

#ifndef MATRIX_GRAPH_VERTEX_DATA_TYPE

/// @brief Vartex element datatype macro that can be changed via '#define MATRIX_GRAPH_VERTEX_DATA_TYPE [datatype]'.
#define MATRIX_GRAPH_VERTEX_DATA_TYPE void*

#endif

#ifndef MATRIX_GRAPH_EDGE_WEIGHT_DATA_TYPE

#define MATRIX_GRAPH_EDGE_WEIGHT_DATA_TYPE size_t

#endif

typedef struct matrix_graph_edge {
    MATRIX_GRAPH_EDGE_WEIGHT_DATA_TYPE weight;

#ifdef MATRIX_GRAPH_EDGE_VALUE_DATA_TYPE
    MATRIX_GRAPH_EDGE_VALUE_DATA_TYPE value;
#endif
} matrix_graph_edge_s;

typedef struct matrix_graph_pair {
    size_t vertex_index_one;
    size_t vertex_index_two;
} matrix_graph_pair_s;

/// @brief Defines special edge used to denote a non-edge (or lack of edge) between any vertices.
#define EMPTY_MATRIX_GRAPH_EDGE (matrix_graph_edge_s) { 0 }

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

/// @brief Function pointer to create a deep/shallow copy for graph vertex/element.
typedef MATRIX_GRAPH_VERTEX_DATA_TYPE (*copy_edge_matrix_graph_fn)      (const matrix_graph_edge_s);
/// @brief Function pointer to destroy/free a vertex element for graph element.
typedef void                          (*destroy_vertex_matrix_graph_fn) (MATRIX_GRAPH_VERTEX_DATA_TYPE *);
/// @brief Function pointer to destroy/free a vertex element for graph element.
typedef void                          (*destroy_edge_matrix_graph_fn)   (matrix_graph_edge_s *);
/// @brief Function pointer to operate on a single graph vertex based on generic arguments.
typedef bool                          (*operate_vertex_matrix_graph_fn) (MATRIX_GRAPH_VERTEX_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                          (*manage_vertex_matrix_graph_fn)  (MATRIX_GRAPH_VERTEX_DATA_TYPE *, const size_t, void *);

#if   FINITE_ALLOCATED_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH    == MATRIX_GRAPH_MODE

typedef struct matrix_graph {
    size_t size, max;
    MATRIX_GRAPH_VERTEX_DATA_TYPE * vertices;
    matrix_graph_edge_s * edges;
} matrix_graph_s;

#if !defined(MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE) && !defined(MATRIX_GRAPH_TABLE_INFINITE_DISTANCE)

#define MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE long double

#define MATRIX_GRAPH_TABLE_INFINITE_DISTANCE (1.0L / 0.0L)

#elif !defined(MATRIX_GRAPH_TABLE_INFINITE_DISTANCE)

#error Infinite distance is not defined.

#elif !defined(MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE)

#error Distance data type is not defined.

#endif

typedef struct matrix_graph_table {
    size_t * previous;
    MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE * distance;
} matrix_graph_table_s;

typedef struct matrix_graph_table_array {
    size_t size;
    matrix_graph_table_s * path_array;
} matrix_graph_table_array_s;

/// @brief Creates an empty graph of zero size. Edges are automatically set to zero using memset.
/// @param max Maximum positive nonzero size of graph.
/// @return Graph structure.
static inline matrix_graph_s create_matrix_graph(const size_t max) {
    MATRIX_GRAPH_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const size_t matrix_size = (max * (max - 1)) >> 1; // we only need half the matrix without index x==y elements
    const matrix_graph_s graph = { // create and allocated memory for graph structure
        .vertices = MATRIX_GRAPH_ALLOC(max * sizeof(MATRIX_GRAPH_VERTEX_DATA_TYPE)),
        .edges = MATRIX_GRAPH_ALLOC(matrix_size * sizeof(matrix_graph_edge_s)),
        .max = max, .size = 0,
    };
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Memory allocation failed.");

    memset(graph.edges, 0, matrix_size * sizeof(matrix_graph_edge_s));

    return graph;
}

/// @brief Destroys the graph and sets size to zero. The destroyed graph should not be used after calling this
/// function, else create a new graph.
/// @param graph Pointer to graph structure.
/// @param destroy_vertex Function pointer to destroy/free each element in graph. Can be NULL if element mustn't be
/// destroyed.
static inline void destroy_matrix_graph(matrix_graph_s * graph, const destroy_vertex_matrix_graph_fn destroy_vertex) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");

    for (size_t i = 0; destroy_vertex && i < graph->size; i++) { // call destroy function pointer on every veertex in graph
        destroy_vertex(graph->vertices + i);
    }
    // free vertices and edges arrays
    MATRIX_GRAPH_FREE(graph->vertices);
    MATRIX_GRAPH_FREE(graph->edges);

    (*graph) = (matrix_graph_s) { 0 }; // set graph to zero
}

/// @brief Checks if matrix graph is empty.
/// @param graph Graph strucutre.
/// @return 'true' if graph is empty, 'false' if not.
static inline bool is_empty_matrix_graph(const matrix_graph_s graph) {
    return !graph.size;
}

/// @brief Checks if matrix graph is full.
/// @param graph Graph strucutre.
/// @return 'true' if graph size is equal to max or size reached maximum capacity, 'false' if neither.
static inline bool is_full_matrix_graph(const matrix_graph_s graph) {
    return !(graph.size < graph.max && ~graph.size);
}

/// @brief Inserts a vertex element into graph.
/// @param graph Pointer to graph structure.
/// @param element Vertex element to insert into graph.
/// @return iondex of inserted vertex element.
static inline size_t insert_vertex_matrix_graph(matrix_graph_s * graph, const MATRIX_GRAPH_VERTEX_DATA_TYPE element) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(~graph->size && "[ERROR] Graph size will overflow.");
    MATRIX_GRAPH_ASSERT(graph->size < graph->max && "[ERROR] Maximum size reached.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph edges matrix is NULL.");

    memcpy(graph->vertices + graph->size, &element, sizeof(MATRIX_GRAPH_VERTEX_DATA_TYPE));  // copy element into graph element array

    return (graph->size)++; // return element index as size before incrementing it
}

/// @brief Removes vertex element based on its index.
/// @param graph Pointer to graph structure.
/// @param index Special index of vertex.
/// @param destroy_edge Function pointer to destroy index vertex' edges.
/// @return Removed element vertex.
/// @note When element vertex is removed, the last element based on index will replace the removed vertex element.
static inline MATRIX_GRAPH_VERTEX_DATA_TYPE remove_vertex_matrix_graph(matrix_graph_s * graph, const size_t index, const destroy_edge_matrix_graph_fn destroy_edge) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(graph->size && "[ERROR] Can't remove vertex from empty graph.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph edges matrix is NULL.");
    MATRIX_GRAPH_ASSERT(index < graph->size && "[ERRRO] index parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(destroy_edge && "[ERROR] 'destroy_edge' function pointer parameter is NULL.");

    const size_t start_last = (graph->size * (graph->size - 1)) >> 1;
    for (size_t i = 0, start_current = (index * (index - 1)) >> 1; i < index; ++i) { // remove and replace row edges
        matrix_graph_edge_s * current_edge = graph->edges + start_current + i; // current vertex row edge
        matrix_graph_edge_s * last_edge = graph->edges + start_last + i; // last vertex rwo edge

        if (current_edge->weight) { // if edge exists via having weight destroy it
            destroy_edge(current_edge);
        }

        (*current_edge) = (*last_edge); // replace current edge with last edge at same position
        (*last_edge) = EMPTY_MATRIX_GRAPH_EDGE; // set edge at last vertex to empty
    }

    for (size_t i = index, current = (index + (index + 1)) >> 1; i < graph->size - 1; ++i, current += i) { // remove and replace column edges
        matrix_graph_edge_s * current_edge = graph->edges + current; // current vertex row edge
        matrix_graph_edge_s * last_edge = graph->edges + start_last + i + 1; // last vertex rwo edge

        if (current_edge->weight) { // if edge exists via having weight destroy it
            destroy_edge(current_edge);
        }

        (*current_edge) = (*last_edge); // replace current edge with last edge at next position
        (*last_edge) = EMPTY_MATRIX_GRAPH_EDGE; // set edge at last vertex to empty
    }

    graph->edges[start_last + index] = EMPTY_MATRIX_GRAPH_EDGE; // set index and last vertex' edge empty

    MATRIX_GRAPH_VERTEX_DATA_TYPE removed = graph->vertices[index]; // store index vertex to return
    graph->vertices[index] = graph->vertices[graph->size - 1]; // set index vertex to last vertex

    graph->size--; // decrement vertex size

    return removed; // return removed vertex
}

/// @brief Gets the specified vertex based on its index.
/// @param graph Graph structure.
/// @param index Index of vertex.
/// @return Vertex element as specified by index parameter.
static inline MATRIX_GRAPH_VERTEX_DATA_TYPE get_vertex_matrix_graph(const matrix_graph_s graph, const size_t index) {
    MATRIX_GRAPH_ASSERT(graph.size && "[ERROR] Can't remove vertex from empty graph.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph edges matrix is NULL.");
    MATRIX_GRAPH_ASSERT(index < graph.size && "[ERRRO] index parameter must be less than graph size.");

    return graph.vertices[index];
}

/// @brief Inserts an edge value between two specified vertex indexes.
/// @param graph Graph structure.
/// @param pair A pair of vertex indices.
/// @param edge Edge to insert.
static inline size_t insert_edge_matrix_graph(matrix_graph_s const * graph, const matrix_graph_pair_s pair, const matrix_graph_edge_s edge) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_one != pair.vertex_index_two && "[ERROR] Indexes can't be the same.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_one < graph->size && "[ERRRO] 'pair.index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_two < graph->size && "[ERRRO] 'pair.index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph veritces array is NULL.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph edges matrix is NULL.");

    const size_t exlude = pair.vertex_index_one ^ pair.vertex_index_two;
    const size_t maximum = pair.vertex_index_one < pair.vertex_index_two ? exlude ^ pair.vertex_index_one : exlude ^ pair.vertex_index_two;
    const size_t minimum = exlude ^ maximum;
    
    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;
    memcpy(graph->edges + row_maximum_start + (minimum), &edge, sizeof(matrix_graph_edge_s));

    return row_maximum_start + (minimum);
}

/// @brief Remove and return edge value between two specified vertex indexes, if there is one, else error occures and program exits.
/// @param graph Graph structure.
/// @param pair A pair of vertex indices.
/// @return Removed edge value.
static inline matrix_graph_edge_s remove_edge_matrix_graph(matrix_graph_s const * graph, const matrix_graph_pair_s pair) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_one != pair.vertex_index_two && "[ERROR] Indexes can't be the same.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_one < graph->size && "[ERRRO] 'pair.index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_two < graph->size && "[ERRRO] 'pair.index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph veritces array is NULL.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph edges matrix is NULL.");

    const size_t exlude = pair.vertex_index_one ^ pair.vertex_index_two;
    const size_t maximum = pair.vertex_index_one < pair.vertex_index_two ? exlude ^ pair.vertex_index_one : exlude ^ pair.vertex_index_two;
    const size_t minimum = exlude ^ maximum;

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;
    const matrix_graph_edge_s removed = graph->edges[row_maximum_start + minimum];
    graph->edges[row_maximum_start + minimum] = empty;

    MATRIX_GRAPH_ASSERT(graph->edges[row_maximum_start + minimum].weight != empty.weight && "[ERROR] No graph edge exists.");

    return removed;
}

/// @brief Checks if there is an edge between two vertex indexes.
/// @param graph Graph structure.
/// @param pair A pair of vertex indices.
/// @return 'true' if edge exists, 'false' if no edge present, i.e. there is an empty edge.
static inline bool is_edge_matrix_graph(const matrix_graph_s graph, const matrix_graph_pair_s pair) {
    MATRIX_GRAPH_ASSERT(pair.vertex_index_one < graph.size && "[ERROR] 'pair.index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_two < graph.size && "[ERROR] 'pair.index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph edges matrix is NULL.");
    // find minimum and maximum vertex index
    const size_t exlude = pair.vertex_index_one ^ pair.vertex_index_two;
    const size_t maximum = pair.vertex_index_one > pair.vertex_index_two ? exlude ^ pair.vertex_index_one : exlude ^ pair.vertex_index_two;
    const size_t minimum = exlude ^ maximum;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE;
    // return true if indexes are not the same and 'edge' isn't an empty/non edge
    return pair.vertex_index_one != pair.vertex_index_two && graph.edges[row_maximum_start + minimum].weight != empty.weight;
}

/// @brief Gets the edge value as specified by vertex indexes, if there is one, else error occures.
/// @param graph Graph structure.
/// @param pair A pair of vertex indices.
/// @return Edge value based on index.
static inline matrix_graph_edge_s get_edge_matrix_graph(const matrix_graph_s graph, const matrix_graph_pair_s pair) {
    MATRIX_GRAPH_ASSERT(pair.vertex_index_one != pair.vertex_index_two && "[ERROR] Indexes can't be the same.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_one < graph.size && "[ERRRO] 'pair.index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(pair.vertex_index_two < graph.size && "[ERRRO] 'pair.index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph edges matrix is NULL.");

    const size_t exlude = pair.vertex_index_one ^ pair.vertex_index_two;
    const size_t maximum = pair.vertex_index_one > pair.vertex_index_two ? exlude ^ pair.vertex_index_one : exlude ^ pair.vertex_index_two;
    const size_t minimum = exlude ^ maximum;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE;
    MATRIX_GRAPH_ASSERT(graph.edges[row_maximum_start + minimum].weight != empty.weight && "[ERROR] No graph edge exists.");

    return graph.edges[row_maximum_start + minimum];
}

/// @brief Breadth first search algorithm.
/// @param graph Pointer to graph structure.
/// @param start_index Index of vertex to start breadth first search.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
static inline void breadth_first_search_matrix_graph(matrix_graph_s const * graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(start_index < graph->size && "[ERROR] 'start_index' parameter must be less than graph size.");

    bool * visited_vertex_array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(bool)); // create visited vertex array
    MATRIX_GRAPH_ASSERT(visited_vertex_array && "[ERROR] Memory allocation failed.");
    memset(visited_vertex_array, false, sizeof(bool) * graph->size); // set visited vertex array to false (or zero)
    
    struct breadth_first_search_queue { size_t * array; size_t size, current; } queue = { // breath first search queue
        .array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)), .current = 0, .size = 0,
    };
    MATRIX_GRAPH_ASSERT(queue.array && "[ERROR] Memory allocation failed.");

    visited_vertex_array[start_index] = true; // set first visited 
    queue.array[queue.size++] = start_index; // insert first/start index to queue

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE;
    while (queue.size && operate(graph->vertices + queue.array[queue.current], args)) { // while queue is not empty
        const size_t current_index = queue.array[queue.current++];
        queue.size--;

        size_t edge_index = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < graph->size; edge_index += i < current_index ? 1 : i, i++) {
            if (graph->edges[edge_index].weight != empty.weight && !visited_vertex_array[i]) {
                visited_vertex_array[i] = true;
                queue.array[queue.current + queue.size++] = i;
            }
        }
    }

    MATRIX_GRAPH_FREE(visited_vertex_array);
    MATRIX_GRAPH_FREE(queue.array);
}

/// @brief Depth first search algorithm.
/// @param graph Pointer to graph structure.
/// @param start_index Index of vertex to start depth first search.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
static inline void depth_first_search_matrix_graph(matrix_graph_s const * graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(start_index < graph->size && "[ERROR] 'start_index' parameter must be less than graph size.");

    bool * visited_vertex_array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(bool));
    MATRIX_GRAPH_ASSERT(visited_vertex_array && "[ERROR] Memory allocation failed.");
    memset(visited_vertex_array, false, sizeof(bool) * graph->size);

    struct depth_first_search_stack { size_t * array; size_t size; } stack = {
        .array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)), .size = 0,
    };
    MATRIX_GRAPH_ASSERT(stack.array && "[ERROR] Memory allocation failed.");

    stack.array[stack.size++] = start_index;
    visited_vertex_array[start_index] = true;

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE;
    while (stack.size && operate(graph->vertices + stack.array[stack.size - 1], args)) {
        const size_t current_index = stack.array[--stack.size];

        size_t edge_index = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < graph->size; edge_index += i < current_index ? 1 : i, i++) {
            if (graph->edges[edge_index].weight != empty.weight && !visited_vertex_array[i]) {
                visited_vertex_array[i] = true;
                stack.array[stack.size++] = i;
            }
        }
    }
    
    MATRIX_GRAPH_FREE(visited_vertex_array);
    MATRIX_GRAPH_FREE(stack.array);
}

/// @brief Dijkstra's algorithm where it is possible to iterate through each reachable vertex using the operate function.
/// @param graph Pointer to graph structure.
/// @param start_index Start index of vertex where to begin path search.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
/// @return Table to lookup shortest distances and paths from start to any end vertex index.
static inline matrix_graph_table_s dijkstra_matrix_graph(matrix_graph_s const * graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph->size && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(start_index < graph->size && "[ERROR] 'start_index' parameter must be less than graph size.");

    bool * visited_index = MATRIX_GRAPH_ALLOC(graph->size * sizeof(bool)); // create visited vertex boolean array
    MATRIX_GRAPH_ASSERT(visited_index && "[ERROR] Memory allocation failed.");
    memset(visited_index, 0, sizeof(bool) * graph->size); // set al visited vertices to 'false' (or zero)
    // create table by allocating memory
    const matrix_graph_table_s table = {
        .previous = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)),
        .distance = MATRIX_GRAPH_ALLOC(graph->size * sizeof(MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE)),
    };
    MATRIX_GRAPH_ASSERT(table.distance && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(table.previous && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < graph->size; i++) { // set table sizes and previous nodes to 'infinity'
        table.distance[i] = MATRIX_GRAPH_TABLE_INFINITE_DISTANCE;
    }

    table.distance[start_index] = 0.0L; // set start index
    struct dijkstra_node { size_t index; MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE distance; } current_node = { .distance = 0.0L, .index = start_index, };

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE; // create empty/non edge to check for every matrix edge
    for (size_t i = 0; (i < graph->size - 1) && (current_node.distance != MATRIX_GRAPH_TABLE_INFINITE_DISTANCE) && operate(graph->vertices + current_node.index, args); i++) {
        const size_t current_index = current_node.index;

        visited_index[current_index] = true; // set current dequeued index as visited
        current_node.distance = MATRIX_GRAPH_TABLE_INFINITE_DISTANCE;

        size_t edge_index = (current_index * (current_index - 1)) >> 1;
        for (size_t j = 0; j < graph->size; edge_index += j < current_index ? 1 : j, j++) {
            if (visited_index[j]) { continue; }
            MATRIX_GRAPH_ASSERT(graph->edges[edge_index].weight >= (MATRIX_GRAPH_EDGE_WEIGHT_DATA_TYPE)(0) && "[ERROR] Dijkstra's algorithm does not work with negative edge values.");

            const MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE alternative = table.distance[current_index] + graph->edges[edge_index].weight;
            if (graph->edges[edge_index].weight != empty.weight && alternative < table.distance[j]) {
                table.distance[j] = alternative;
                table.previous[j] = current_index;
            }
            // if current node distance is greater than table's at index j, then change it to j's
            if (current_node.distance > table.distance[j]) { current_node = (struct dijkstra_node) { .distance = table.distance[j], .index = j, }; }
        }
    }

    MATRIX_GRAPH_FREE(visited_index); // free visited index

    return table;
}

/// @brief Bellman-Ford table algorithm where the table for shortest paths between start and any other vertex index is created.
/// @param graph Graph structure.
/// @param start_index Index of vertex to start shortest path from.
/// @return Table to lookup shortest distances and paths from start to any end vertex index.
static inline matrix_graph_table_s bellman_ford_matrix_graph(const matrix_graph_s graph, const size_t start_index) {
    MATRIX_GRAPH_ASSERT(graph.size && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(start_index < graph.size && "[ERROR] 'start_index' parameter must be less than graph size.");

    // create table by allocating memory
    const matrix_graph_table_s table = {
        .previous = MATRIX_GRAPH_ALLOC(graph.size * sizeof(size_t)),
        .distance = MATRIX_GRAPH_ALLOC(graph.size * sizeof(MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE)),
    };
    MATRIX_GRAPH_ASSERT(table.distance && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(table.previous && "[ERROR] Memory allocation failed.");
    // set table sizes and previous nodes to 'infinity'
    for (size_t i = 0; i < graph.size; i++) {
        table.distance[i] = MATRIX_GRAPH_TABLE_INFINITE_DISTANCE;
    }

    table.distance[start_index] = 0.0L;

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE; // create empty/non edge to check for every matrix edge
    for (size_t i = 0; i < graph.size; i++) {
        size_t edge_index = (i * (i - 1)) >> 1;
        for (size_t j = 0; j < graph.size; edge_index += j < i ? 1 : j, j++) {
            if (graph.edges[edge_index].weight == empty.weight) { // if there is no edge continue
                continue;
            }

            const MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE alternative = table.distance[i] + graph.edges[edge_index].weight;
            // if alternative distance is less than current table distance between ith and jth vertex update to new shorter distance
            if (alternative < table.distance[j]) {
                MATRIX_GRAPH_ASSERT(i == (graph.size - 1) && "[ERROR] Negative cycle detected.");

                table.distance[j] = alternative;
                table.previous[j] = i;
            }
        }
    }

    return table;
}

/// @brief Prim algorithm where the table for minimum spanning tree from a start index is created.
/// @param graph Graph structure.
/// @param start_index Index of vertex to minimum spanning tree from.
/// @param operate Function pointer to operate on vertex using arguments.
/// @param args Generci arguments for operate function.
/// @return Table to lookup minimum spanning tree from start vertex index.
static inline matrix_graph_table_s prim_matrix_graph(const matrix_graph_s graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(start_index < graph.size && "'end_index' parameter must be less than graph size.");

    bool * visited_vertex_array = MATRIX_GRAPH_ALLOC(graph.size * sizeof(bool));
    MATRIX_GRAPH_ASSERT(visited_vertex_array && "[ERROR] Memory allocation failed.");

    // create table by allocating memory
    const matrix_graph_table_s table = {
        .previous = MATRIX_GRAPH_ALLOC(graph.size * sizeof(size_t)),
        .distance = MATRIX_GRAPH_ALLOC(graph.size * sizeof(MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE)),
    };
    MATRIX_GRAPH_ASSERT(table.distance && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(table.previous && "[ERROR] Memory allocation failed.");
    // set table sizes and previous nodes to 'infinity'
    for (size_t i = 0; i < graph.size; i++) {
        table.distance[i] = MATRIX_GRAPH_TABLE_INFINITE_DISTANCE;
    }

    struct prim_node { size_t index; MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE distance; } current_node = {
        .distance = table.distance[start_index] = 0.0L, .index = start_index,
    };

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE; // create empty/non edge to check for every matrix edge
    for (size_t i = 0; i < graph.size - 1 && operate(graph.vertices + current_node.index, args); i++) {
        const size_t current_index = current_node.index;
        visited_vertex_array[current_index] = true;

        current_node.distance = MATRIX_GRAPH_TABLE_INFINITE_DISTANCE;
       
        size_t edge_index = (current_index * (current_index - 1)) >> 1;
        for (size_t j = 0; j < graph.size; edge_index += j < current_index ? 1 : j, j++) {
            if (visited_vertex_array[j]) {
                continue;
            }

            const MATRIX_GRAPH_EDGE_WEIGHT_DATA_TYPE weight = graph.edges[edge_index].weight;
            if (graph.edges[edge_index].weight != empty.weight && weight < table.distance[j]) {
                table.distance[j] = weight;
                table.previous[j] = current_index;
            }

            if (table.distance[j] < current_node.distance) {
                current_node = (struct prim_node) { .distance = table.distance[j], .index = j, };
            }
        }
    }

    MATRIX_GRAPH_FREE(visited_vertex_array);
    
    return table;
}

/// @brief Kruskal's algorithm where the table for a minimum spanning tree is created.
/// @param graph Graph structure.
/// @param operate Function pointer that allows operations on all merged vertecies of the smallest edges based on arguments.
/// If operate function returns false Kruskal's algorithm stops, else it continues until minimum spanning tree table is
/// created.
/// @param args Operate function arguments.
/// @return Table to lookup minimum spanning tree from start vertex index.
/// @note This code is based on https://github.com/OpenGenus/cosmos/blob/master/code/greedy_algorithms/src/kruskal_minimum_spanning_tree/kruskal.c,
/// but with no recursion and
static inline matrix_graph_table_s kruskal_matrix_graph(const matrix_graph_s graph, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph.size && "Graph is empty.");

    struct kruskal_edge {
        size_t source, destination;
        MATRIX_GRAPH_EDGE_WEIGHT_DATA_TYPE weight;
    };

    struct kruskal_edges_array {
        size_t size;
        struct kruskal_edge * edges;
    } edges_array = { .size = 0, .edges = MATRIX_GRAPH_ALLOC(graph.size * sizeof(struct kruskal_edge)) };
    MATRIX_GRAPH_ASSERT(edges_array.edges && "[ERROR] Memory allocation failed.");

    const matrix_graph_edge_s empty = EMPTY_MATRIX_GRAPH_EDGE;
    for (size_t i = 0; i < graph.size; ++i) {
        for (size_t j = i + 1; j < graph.size; ++j) {
            const size_t row_maximum_start = (j * (j - 1)) >> 1;

            const MATRIX_GRAPH_EDGE_WEIGHT_DATA_TYPE edge_weight = graph.edges[row_maximum_start + i].weight;
            if (edge_weight != empty.weight) {
                edges_array.edges[edges_array.size].source = i;
                edges_array.edges[edges_array.size].destination = j;
                edges_array.edges[edges_array.size].weight = edge_weight;
                edges_array.size++;
            }
        }
    }

    for (size_t i = 0; edges_array.size && i < edges_array.size - 1; ++i) {
        size_t minimum = i;
        for (size_t j = i + 1; j < edges_array.size; ++j) {
            if (edges_array.edges[j].weight < edges_array.edges[minimum].weight) {
                minimum = j;
            }
        }
        const struct kruskal_edge temp = edges_array.edges[i];
        edges_array.edges[i] = edges_array.edges[minimum];
        edges_array.edges[minimum] = temp;
    }

    // create table by allocating memory
    const matrix_graph_table_s table = {
        .previous = MATRIX_GRAPH_ALLOC(graph.size * sizeof(size_t)),
        .distance = MATRIX_GRAPH_ALLOC(graph.size * sizeof(MATRIX_GRAPH_TABLE_DISTANCE_DATA_TYPE)),
    };
    MATRIX_GRAPH_ASSERT(table.distance && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(table.previous && "[ERROR] Memory allocation failed.");
    // set table sizes and previous nodes to 'infinity'
    for (size_t i = 0; i < graph.size; i++) {
        table.previous[i] = i;
        table.distance[i] = 0;
    }

    for (int i = 0; i < edges_array.size && operate(graph.vertices + edges_array.edges[i].source, args) && operate(graph.vertices + edges_array.edges[i].destination, args); ++i) {
        const struct kruskal_edge smallest = edges_array.edges[i]; // get the next smallest edge from sorted array of edges

        size_t find_source = smallest.source;
        while (find_source != table.previous[find_source]) {
            find_source = table.previous[find_source];
        }
        size_t find_destination = smallest.destination;
        while (find_destination != table.previous[find_destination]) {
            find_destination = table.previous[find_destination];
        }

        if (find_source == find_destination) {
            continue;
        }

        size_t find_source_root = find_source;
        while (find_source_root != table.previous[find_source_root]) {
            find_source_root = table.previous[find_source_root];
        }
        size_t find_destination_root = find_destination;
        while (find_destination_root != table.previous[find_destination_root]) {
            find_destination_root = table.previous[find_destination_root];
        }

        if (table.distance[find_source_root] < table.distance[find_destination_root]) {
            table.previous[find_source_root] = find_destination_root;
        } else if (table.distance[find_source_root] > table.distance[find_destination_root]) {
            table.previous[find_destination_root] = find_source_root;
        } else {
            table.previous[find_destination_root] = find_source_root;
            table.distance[find_source_root]++;
        }
    }

    MATRIX_GRAPH_FREE(edges_array.edges);

    return table;
}

/// @brief Destroys table with allocated memory.
/// @param table Array table to lookup shortest distances and paths from start to any end vertex index.
static inline void destroy_table_matrix_graph(matrix_graph_table_s * table) {
    MATRIX_GRAPH_ASSERT(table && "[ERROR] 'table' parameter pointer is NULL.");

    MATRIX_GRAPH_FREE(table->distance);
    MATRIX_GRAPH_FREE(table->previous);

    table->distance = NULL;
    table->previous = NULL;
}

/// @brief Creates a subgraph copy of original graph based on its lookup table.
/// @param graph Graph structure.
/// @param table Table structure to chack edge between any current and previous vertex for subgraph.
/// @param copy Copy function pointer to copy create copy of each vertex into subgraph.
/// @return A subgraph of graph based on lookup table.
/// @note Its main purpose is to create a minimum spanning tree for Prim's and Kruskal’s tables based on graph. It can also be used to generate Dijkstra's 
/// and other table subgraphs, which might have some uses I am not aware of, idk.
static inline matrix_graph_s create_table_subgraph_matrix_graph(const matrix_graph_s graph, const matrix_graph_table_s table, const copy_vertex_matrix_graph_fn copy) {
    const size_t matrix_size = (graph.max * (graph.max - 1)) >> 1;
    const matrix_graph_s subgraph = {
        .max = graph.max, .size = graph.size,
        .vertices = MATRIX_GRAPH_ALLOC(graph.max * sizeof(MATRIX_GRAPH_VERTEX_DATA_TYPE)),
        .edges = MATRIX_GRAPH_ALLOC(matrix_size * sizeof(matrix_graph_edge_s)),
    };
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Memory allocation failed.");

    memset(graph.edges, 0, matrix_size * sizeof(matrix_graph_edge_s));

    for (size_t i = 0; i < graph.size; i++) {
        subgraph.vertices[i] = copy ? copy(graph.vertices[i]) : graph.vertices[i];

        if (table.distance[i] && table.distance[i] != MATRIX_GRAPH_TABLE_INFINITE_DISTANCE) {
            const size_t exlude = i ^ table.previous[i];
            const size_t maximum = i < table.previous[i] ? exlude ^ i : exlude ^ table.previous[i];
            const size_t minimum = exlude ^ maximum;

            const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;

            subgraph.edges[row_maximum_start + minimum] = graph.edges[row_maximum_start + minimum];
        }
    }
    
    return subgraph;
}

/// @brief Array table path algorithm where the path between the start index and any end vertex index is searched.
/// @param graph Graph structure pointer.
/// @param table Lookup array table for distances between vertex indexes.
/// @param end_index End index of vertex to search distance to start.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
/// @return true if path exists, false if not.
static inline bool table_search_matrix_graph(matrix_graph_s const * graph, const matrix_graph_table_s table, const size_t end_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(operate && "[ERROR] 'operator' parameter function pointer is NULL.");
    MATRIX_GRAPH_ASSERT(end_index < graph->size && "'end_index' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(table.distance && "[ERROR] table's distance array is NULL.");
    MATRIX_GRAPH_ASSERT(table.previous && "[ERROR] table's previous array is NULL.");
    // create stack to remove the need for recursion since Dijkstra's algorithm starts from end index to start
    struct dijkstra_search_stack { size_t size; size_t * array; } stack = {
        .array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)), .size = 0,
    };
    MATRIX_GRAPH_ASSERT(stack.array && "[ERROR] Memory allocation failed.");

    size_t current_index = end_index;
    stack.array[(stack.size)++] = current_index;
    while (table.distance[current_index]) {
        current_index = table.previous[current_index];
        stack.array[(stack.size)++] = current_index;
    }
    
    // if index at top of stack has zero distance to start index, i.e. it is the start index, then a path exists
    const bool is_path = !table.distance[stack.array[stack.size - 1]];
    
    while (stack.size && operate(graph->vertices + stack.array[--(stack.size)], args)){};

    MATRIX_GRAPH_FREE(stack.array);

    return is_path;
}

/// @brief Iterates over each vertex element in graph.
/// @param graph Graph structure pointer.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
static inline void foreach_matrix_graph(matrix_graph_s const * graph, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(operate && "[ERROR] 'operate' parameter pointer is NULL.");

    for (size_t i = 0; i < graph->size && operate(graph->vertices + i, args); i++);
}

/// @brief Manages array of vertex elements based on graph size.
/// @param graph Graph structure pointer.
/// @param manage Manage function pointer to manage vertex elements array using arguments.
/// @param args Arguments for manage function pointer.
static inline void forevery_matrix_graph(matrix_graph_s const * graph, const manage_vertex_matrix_graph_fn manage, void * args) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(manage && "[ERROR] 'operate' parameter pointer is NULL.");

    manage(graph->vertices, graph->size, args);
}

#elif INFINITE_REALLOC_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH    == MATRIX_GRAPH_MODE
#elif FINITE_PRERPOCESSOR_STRICTLY_LOWER_TRIANGULAR_MATRIX_GRAPH == MATRIX_GRAPH_MODE
#elif FINITE_ALLOCATED_MATRIX_GRAPH                              == MATRIX_GRAPH_MODE
#elif INFINITE_REALLOC_MATRIX_GRAPH                              == MATRIX_GRAPH_MODE
#elif FINITE_PRERPOCESSOR_MATRIX_GRAPH                           == MATRIX_GRAPH_MODE
#endif

#endif // MATRIX_GRAPH_H
