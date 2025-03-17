#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include <stdlib.h>  // imports size_t, malloc, realloc, free
#include <stdbool.h> // imports bool
#include <string.h>  // imports memcpy, memmove
#include <limits.h>  // imports MAX values

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
#define MATRIX_GRAPH_EDGE_DATA_TYPE size_t

#endif

#ifndef EMPTY_MATRIX_GRAPH_EDGE

/// @brief Defines special edge used to denote a non-edge (or lack of edge) between any vertices.
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
/// @brief Function pointer to operate on a single graph vertex based on generic arguments.
typedef bool                          (*operate_vertex_matrix_graph_fn) (MATRIX_GRAPH_VERTEX_DATA_TYPE *, void *);
/// @brief Function pointer to manage an array of graph elements based on generic arguments.
typedef void                          (*manage_vertex_matrix_graph_fn)  (MATRIX_GRAPH_VERTEX_DATA_TYPE *, const size_t, void *);

#if   FINITE_ALLOCATED_MATRIX_GRAPH    == MATRIX_GRAPH_MODE

typedef struct matrix_graph {
    size_t size, max;
    MATRIX_GRAPH_VERTEX_DATA_TYPE * vertices;
    MATRIX_GRAPH_EDGE_DATA_TYPE   * edges;
} matrix_graph_s;

typedef struct dijkstra_table {
    size_t * previous;
    long double * distance;
} dijkstra_table_s;

/// @brief Creates an empty graph of zero size. Edges are automatically set to zero using memset.
/// @param max Maximum positive nonzero size of graph.
/// @return Graph structure.
static inline matrix_graph_s create_matrix_graph(const size_t max) {
    MATRIX_GRAPH_ASSERT(max && "[ERROR] Maximum size can't be zero.");

    const size_t matrix_size = (max * (max - 1)) >> 1; // we only need half the matrix without index x==y elements
    const matrix_graph_s graph = { // create and allocated memory for graph structure
        .vertices = MATRIX_GRAPH_ALLOC(max * sizeof(MATRIX_GRAPH_VERTEX_DATA_TYPE)),
        .edges = MATRIX_GRAPH_ALLOC(matrix_size * sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)),
        .max = max, .size = 0,
    };
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Memory allocation failed.");

    const MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    for (size_t i = 0; i < matrix_size; i++) { // sets every edge to non-edge
        graph.edges[i] = empty;
    }

    return graph;
}

/// @brief Destroys the graph and sets size to zero. The destroyed graph should not be used after calling this
/// function, else create a new graph.
/// @param graph Pointer to graph structure.
/// @param destroy Function pointer to destroy/free each element in graph. Can be NULL if element mustn't be
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
/// @return Removed element vertex.
/// @note When element vertex is removed, the last element based on index will replace the removed vertex element.
static inline MATRIX_GRAPH_VERTEX_DATA_TYPE remove_vertex_matrix_graph(matrix_graph_s * graph, const size_t index) {
    MATRIX_GRAPH_ASSERT(graph && "[ERROR] 'graph' parameter pointer is NULL.");
    MATRIX_GRAPH_ASSERT(graph->size && "[ERROR] Can't remove vertex from empty graph.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph edges matrix is NULL.");
    MATRIX_GRAPH_ASSERT(index < graph->size && "[ERRRO] index parameter must be less than graph size.");

    MATRIX_GRAPH_VERTEX_DATA_TYPE removed = graph->vertices[index];
    graph->size--;

    const size_t last_start  = ((graph->size) * (graph->size - 1)) >> 1;
    MATRIX_GRAPH_EDGE_DATA_TYPE * last_edges = graph->edges + last_start;
    if (index != graph->size) { // if index doesn't point to last element
        const size_t row_index_start = (index * (index - 1)) >> 1;
        // copy row edges of last vartex to index vertex
        memcpy(graph->edges + row_index_start, last_edges, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE) * index);

        size_t col_index_start = (index * (index + 1)) >> 1;
        for (size_t i = index + 1; i < graph->size; i++) { // copy row edges of last vertex to column edges of removed
            graph->edges[col_index_start + i - 1] = last_edges[i];
            col_index_start += i;
        }
        graph->vertices[index] = graph->vertices[graph->size]; // copy last vertex into vertex at index
    }

    MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    for (size_t i = 0; i < graph->size; i++) { // set edges at last element to empty edge
        memcpy(last_edges + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE));
    }

    return removed;
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
/// @param index_one Index of first vertex element.
/// @param index_two Index of second vertex element.
/// @param value Edge value to insert.
static inline void insert_edge_matrix_graph(const matrix_graph_s graph, const size_t index_one, const size_t index_two, const MATRIX_GRAPH_EDGE_DATA_TYPE value) {
    MATRIX_GRAPH_ASSERT(index_one != index_two && "[ERROR] Indexes can't be the same.");
    MATRIX_GRAPH_ASSERT(index_one < graph.size && "[ERRRO] 'index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(index_two < graph.size && "[ERRRO] 'index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph veritces array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph edges matrix is NULL.");

    const size_t exlude = index_one ^ index_two;
    const size_t maximum = index_one < index_two ? exlude ^ index_one : exlude ^ index_two;
    const size_t minimum = exlude ^ maximum;
    
    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;
    memcpy(graph.edges + row_maximum_start + (minimum), &value, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE));
}

/// @brief Remove and return edge value between two specified vertex indexes, if there is one, else error occures and program exits.
/// @param graph Graph structure.
/// @param index_one Index of first vertex element.
/// @param index_two Index of second vertex element.
/// @return Removed edge value.
static inline MATRIX_GRAPH_EDGE_DATA_TYPE remove_edge_matrix_graph(const matrix_graph_s graph, const size_t index_one, const size_t index_two) {
    MATRIX_GRAPH_ASSERT(index_one != index_two && "[ERROR] Indexes can't be the same.");
    MATRIX_GRAPH_ASSERT(index_one < graph.size && "[ERRRO] 'index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(index_two < graph.size && "[ERRRO] 'index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph veritces array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph edges matrix is NULL.");

    const size_t exlude = index_one ^ index_two;
    const size_t maximum = index_one < index_two ? exlude ^ index_one : exlude ^ index_two;
    const size_t minimum = exlude ^ maximum;

    MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;
    MATRIX_GRAPH_EDGE_DATA_TYPE removed = graph.edges[row_maximum_start + minimum];
    graph.edges[row_maximum_start + minimum] = empty;

    MATRIX_GRAPH_ASSERT(memcmp(graph.edges + row_maximum_start + minimum, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && "[ERROR] No graph edge exists.");

    return removed;
}

/// @brief Checks if there is an edge between two vertex indexes.
/// @param graph Graph structure.
/// @param index_one Index of first vertex element.
/// @param index_two Index of second vertex element.
/// @return 'true' if edge exists, 'false' if no edge present, i.e. there is an empty edge.
static inline bool is_edge_matrix_graph(const matrix_graph_s graph, const size_t index_one, const size_t index_two) {
    MATRIX_GRAPH_ASSERT(index_one < graph.size && "[ERROR] 'index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(index_two < graph.size && "[ERROR] 'index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph edges matrix is NULL.");
    // find minimum and maximum vertex index
    const size_t exlude = index_one ^ index_two;
    const size_t maximum = index_one > index_two ? exlude ^ index_one : exlude ^ index_two;
    const size_t minimum = exlude ^ maximum;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;

    MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    // return true if indexes are not the same and 'edge' isn't an empty/non edge
    return index_one != index_two && memcmp(graph.edges + row_maximum_start + minimum, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE));
}

/// @brief Gets the edge value as specified by vertex indexes, if there is one, else error occures.
/// @param graph Graph structure.
/// @param index_one Index of first vertex element.
/// @param index_two Index of second vertex element.
/// @return Edge value based on index.
static inline MATRIX_GRAPH_EDGE_DATA_TYPE get_edge_matrix_graph(const matrix_graph_s graph, const size_t index_one, const size_t index_two) {
    MATRIX_GRAPH_ASSERT(index_one != index_two && "[ERROR] Indexes can't be the same.");
    MATRIX_GRAPH_ASSERT(index_one < graph.size && "[ERRRO] 'index_one' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(index_two < graph.size && "[ERRRO] 'index_two' parameter must be less than graph size.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph vertices array is NULL.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph edges matrix is NULL.");

    const size_t exlude = index_one ^ index_two;
    const size_t maximum = index_one > index_two ? exlude ^ index_one : exlude ^ index_two;
    const size_t minimum = exlude ^ maximum;

    const size_t row_maximum_start = (maximum * (maximum - 1)) >> 1;

    MATRIX_GRAPH_EDGE_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    MATRIX_GRAPH_ASSERT(memcmp(graph.edges + row_maximum_start + minimum, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && "[ERROR] No graph edge exists.");

    return graph.edges[row_maximum_start + minimum];
}

/// @brief Breadth first search algorithm.
/// @param graph Pointer to graph structure.
/// @param start_index Index of vertex to start breadth first search.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
static inline void breadth_first_search_matrix_graph(matrix_graph_s * graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
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

    MATRIX_GRAPH_VERTEX_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    while (queue.size) { // while queue is not empty
        const size_t current_index = queue.array[queue.current++];
        queue.size--;

        if (!operate(graph->vertices + current_index, args)) { // operate on vertex and break loop if operate should stop
            break;
        }

        const size_t row_index_start = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < current_index; i++) { // iterate for row indexes from first to index before current
            if (memcmp(graph->edges + row_index_start + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i]) {
                visited_vertex_array[i] = true;
                queue.array[queue.current + queue.size++] = i;
            }
        }
        
        size_t col_index_start = ((current_index * (current_index + 1)) >> 1);
        for (size_t i = current_index + 1; i < graph->size; i++) { // iterate for column indexes from after current index to last
            if (memcmp(graph->edges + col_index_start, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i]) {
                visited_vertex_array[i] = true;
                queue.array[queue.current + queue.size++] = i;
            }
            col_index_start += current_index;
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
static inline void depth_first_search_matrix_graph(matrix_graph_s * graph, const size_t start_index, const operate_vertex_matrix_graph_fn operate, void * args) {
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

    MATRIX_GRAPH_VERTEX_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE;
    while (stack.size) {
        const size_t current_index = stack.array[--stack.size];

        if (!operate(graph->vertices + current_index, args)) {
            break;
        }

        const size_t row_index_start = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < current_index; i++) {
            if (memcmp(graph->edges + row_index_start + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i]) {
                visited_vertex_array[i] = true;
                stack.array[stack.size++] = i;
            }
        }

        size_t col_index_start = ((current_index * (current_index + 1)) >> 1);
        for (size_t i = current_index + 1; i < graph->size; i++) {
            if (memcmp(graph->edges + col_index_start, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i]) {
                visited_vertex_array[i] = true;
                stack.array[stack.size++] = i;
            }
            col_index_start += current_index;
        }
    }
    
    MATRIX_GRAPH_FREE(visited_vertex_array);
    MATRIX_GRAPH_FREE(stack.array);
}

/// @brief First part if Dijkstra's table algorithm where the table for shortest paths between start and any other vertex index
/// is created.
/// @param graph Graph structure.
/// @param start_index Index of vertex to start shortest path from.
/// @return Table to lookup distances.
static inline dijkstra_table_s create_dijkstra_table_matrix_graph(const matrix_graph_s graph, const size_t start_index) {
    MATRIX_GRAPH_ASSERT(graph.size && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph.edges && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph.vertices && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(start_index < graph.size && "[ERROR] 'start_index' parameter must be less than graph size.");

    bool * visited_vertex_array = MATRIX_GRAPH_ALLOC(graph.size * sizeof(bool)); // create visited boolean array
    MATRIX_GRAPH_ASSERT(visited_vertex_array && "[ERROR] Memory allocation failed.");
    memset(visited_vertex_array, 0, sizeof(bool) * graph.size); // set al visited vertices to 'false' (or zero)
    // create table by allocating memory
    dijkstra_table_s table = {
        .previous = MATRIX_GRAPH_ALLOC(graph.size * sizeof(size_t)),
        .distance = MATRIX_GRAPH_ALLOC(graph.size * sizeof(long double)),
    };
    MATRIX_GRAPH_ASSERT(table.distance && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(table.previous && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < graph.size; i++) { // set table sizes and previous nodes to 'infinity'
        table.distance[i] = 1.0L / 0.0L;
    }

    MATRIX_GRAPH_EDGE_DATA_TYPE minimum_distance = table.distance[start_index] = 0; // set start index' distance to itself to zero and first minimum distance too
    size_t current_index = start_index; // set current index to start
    size_t s = 0; // set graph size index for iteration to 0
    MATRIX_GRAPH_VERTEX_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE; // create empty/non edge to check for every matrix edge
    do {
        visited_vertex_array[current_index] = true; // set visited vertex at current index to true

        const size_t row_index_start = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < current_index; i++) { // iterate for every row edge except current edge in 1D array
            MATRIX_GRAPH_ASSERT(graph.edges[row_index_start + i] > (MATRIX_GRAPH_EDGE_DATA_TYPE)(0) && "[ERROR] Dijkstra's algorithm does not work with negative edge values.");
            MATRIX_GRAPH_EDGE_DATA_TYPE alternative = table.distance[current_index] + graph.edges[row_index_start + i];
            if (memcmp(graph.edges + row_index_start + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i] && alternative < table.distance[i]) {
                table.distance[i] = alternative;
                table.previous[i] = current_index;
            }
        }

        size_t col_index_start = ((current_index * (current_index + 1)) >> 1);
        for (size_t i = current_index + 1; i < graph.size; i++) {
            MATRIX_GRAPH_ASSERT(graph.edges[col_index_start] > (MATRIX_GRAPH_EDGE_DATA_TYPE)(0) && "[ERROR] Dijkstra's algorithm does not work with negative edge values.");
            MATRIX_GRAPH_EDGE_DATA_TYPE alternative = table.distance[current_index] + graph.edges[col_index_start];
            if (memcmp(graph.edges + col_index_start, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i] && alternative < table.distance[i]) {
                table.distance[i] = alternative;
                table.previous[i] = current_index;
            }
            col_index_start += current_index;
        }

        minimum_distance = 1.0L / 0.0L; // set minimum distance to 'infinity'
        for (size_t i = 0; i < graph.size; i++) { // find smallest distance
            if (!visited_vertex_array[i] && table.distance[i] < table.distance[current_index]) {
                current_index = i;
                minimum_distance = table.distance[i];
            }
        }
    } while (++s < graph.size && minimum_distance != 1.0L / 0.0L); 
    // while not all graph vertices were checked and minimum distance isn't 'infinite' (a path from current index to next exists)

    MATRIX_GRAPH_FREE(visited_vertex_array); // free visited vertices array
    
    return table; // return initialized table
}

/// @brief Destroys table with allocated memory.
/// @param table Dijkstra table to lookup distances and paths to start vertex index.
static inline void destroy_dijkstra_table_matrix_graph(dijkstra_table_s * table) {
    MATRIX_GRAPH_ASSERT(table && "[ERROR] 'table' parameter pointer is NULL.");

    MATRIX_GRAPH_FREE(table->distance);
    MATRIX_GRAPH_FREE(table->previous);

    table->distance = NULL;
    table->previous = NULL;
}

/// @brief Second part of Dijkstra's table algorithm where the shortest path between the start index and any end vertex index is searched.
/// @param graph Graph structure pointer.
/// @param table Dijkstra lookup table for distances between vertex indexes.
/// @param end_index End index of vertex to search distance to start.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
/// @return true if shortest path exists, false if not.
static inline bool dijkstra_table_search_matrix_graph(matrix_graph_s * graph, const dijkstra_table_s table, const size_t end_index, const operate_vertex_matrix_graph_fn operate, void * args) {
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
    
    while (stack.size) {
        if (!operate(graph->vertices + stack.array[--(stack.size)], args)) {
            break;
        }
    }

    MATRIX_GRAPH_FREE(stack.array);

    return is_path;
}

/// @brief Real Dijkstra's algorithm where the user can specify the start and end vertex indexes to traverse the graph.
/// @param graph Graph structure pointer.
/// @param start_index Start index of vertex where to begin path search.
/// @param end_index End index of vertex where to end path search.
/// @param operate Operate function pointer to operate on vertex elements using arguments.
/// @param args Arguments for operate function pointer.
/// @return true if shortest path exists, false if not.
static inline bool dijkstra_algorithm_search_matrix_graph(matrix_graph_s * graph, const size_t start_index, const size_t end_index, const operate_vertex_matrix_graph_fn operate, void * args) {
    MATRIX_GRAPH_ASSERT(graph->size && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph->edges && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(graph->vertices && "[ERROR] Graph is empty.");
    MATRIX_GRAPH_ASSERT(start_index < graph->size && "[ERROR] 'start_index' parameter must be less than graph size.");

    bool * visited_vertex_array = MATRIX_GRAPH_ALLOC(graph->size * sizeof(bool)); // create visited vertex boolean array
    MATRIX_GRAPH_ASSERT(visited_vertex_array && "[ERROR] Memory allocation failed.");
    memset(visited_vertex_array, 0, sizeof(bool) * graph->size); // set al visited vertices to 'false' (or zero)
    // create table by allocating memory
    dijkstra_table_s table = {
        .previous = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)),
        .distance = MATRIX_GRAPH_ALLOC(graph->size * sizeof(size_t)),
    };
    MATRIX_GRAPH_ASSERT(table.distance && "[ERROR] Memory allocation failed.");
    MATRIX_GRAPH_ASSERT(table.previous && "[ERROR] Memory allocation failed.");

    for (size_t i = 0; i < graph->size; i++) { // set table sizes and previous nodes to 'infinity'
        table.distance[i] = 1.0L / 0.0L;
    }

    size_t minimum_distance = table.distance[start_index] = 0; // set start index' distance to itself to zero and first minimum distance too
    size_t current_index = start_index; // set current index to start
    visited_vertex_array[current_index] = true; // set visited vertex at current index to true
    size_t s = 0; // set graph size index for iteration to 0
    MATRIX_GRAPH_VERTEX_DATA_TYPE empty = EMPTY_MATRIX_GRAPH_EDGE; // create empty/non edge to check for every matrix edge
    do {
        const size_t row_index_start = (current_index * (current_index - 1)) >> 1;
        for (size_t i = 0; i < current_index; i++) { // iterate for every row edge except current edge in 1D array
            MATRIX_GRAPH_ASSERT(graph->edges[row_index_start + i] > (MATRIX_GRAPH_EDGE_DATA_TYPE)(0) && "[ERROR] Dijkstra's algorithm does not work with negative edge values.");
            MATRIX_GRAPH_EDGE_DATA_TYPE alternative = table.distance[current_index] + graph->edges[row_index_start + i];
            if (memcmp(graph->edges + row_index_start + i, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i] && alternative < table.distance[i]) {
                table.distance[i] = alternative;
                table.previous[i] = current_index;
            }
        }

        size_t col_index_start = ((current_index * (current_index + 1)) >> 1);
        for (size_t i = current_index + 1; i < graph->size; i++) {
            MATRIX_GRAPH_ASSERT(graph->edges[col_index_start] > (MATRIX_GRAPH_EDGE_DATA_TYPE)(0) && "[ERROR] Dijkstra's algorithm does not work with negative edge values.");
            MATRIX_GRAPH_EDGE_DATA_TYPE alternative = table.distance[current_index] + graph->edges[col_index_start];
            if (memcmp(graph->edges + col_index_start, &empty, sizeof(MATRIX_GRAPH_EDGE_DATA_TYPE)) && !visited_vertex_array[i] && alternative < table.distance[i]) {
                table.distance[i] = alternative;
                table.previous[i] = current_index;
            }
            col_index_start += current_index;
        }

        minimum_distance = 1.0L / 0.0L; // set minimum distance to 'infinity'
        for (size_t i = 0; i < graph->size; i++) { // find smallest distance
            if (!visited_vertex_array[i] && table.distance[i] < table.distance[current_index]) {
                current_index = i;
                minimum_distance = table.distance[i];
            }
        }

        visited_vertex_array[current_index] = true; // set visited vertex at current index to true
    } while (++s < graph->size && minimum_distance != 1.0L / 0.0L && !visited_vertex_array[end_index]); 
    // while not all graph vertices were checked and minimum distance isn't 'infinite' (a path from current index to next exists)

    MATRIX_GRAPH_FREE(visited_vertex_array); // free visited vertices array

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
    
    while (stack.size) {
        if (!operate(graph->vertices + stack.array[--(stack.size)], args)) {
            break;
        }
    }

    MATRIX_GRAPH_FREE(stack.array);

    return is_path;
}

#elif INFINITE_REALLOC_MATRIX_GRAPH    == MATRIX_GRAPH_MODE
#elif FINITE_PRERPOCESSOR_MATRIX_GRAPH == MATRIX_GRAPH_MODE
#endif

#endif // MATRIX_GRAPH_H
