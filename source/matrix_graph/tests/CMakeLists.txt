add_executable(matrix_graph_test main.c
)
target_link_libraries(matrix_graph_test PRIVATE greatest project_headers)
add_test(NAME MATRIX_GRAPH_TEST COMMAND matrix_graph_test)
