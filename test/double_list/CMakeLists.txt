add_executable(double_list_test main.c
        infinite_allocated_double_list_test.c
        finite_allocated_double_list_test.c
        finite_preprocessor_double_list_test.c
        infinite_realloc_double_list_test.c
)
target_link_libraries(double_list_test PRIVATE greatest project_headers)
add_test(NAME DOUBLE_LIST_TEST COMMAND double_list_test)
