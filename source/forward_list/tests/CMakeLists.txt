add_executable(forward_list_test main.c
        infinite_allocated_forward_list_test.c
        finite_allocated_forward_list_test.c
        infinite_realloc_forward_list_test.c
        finite_preprocessor_forward_list_test.c
)
target_link_libraries(forward_list_test PRIVATE greatest project_headers)
add_test(NAME FORWARD_LIST_TEST COMMAND forward_list_test)
