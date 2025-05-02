add_executable(list_test main.c
        infinite_allocated_list_test.c
        finite_allocated_list_test.c
        finite_preprocessor_list_test.c
        infinite_realloc_list_test.c
)
target_link_libraries(list_test PRIVATE functions greatest PADS)
add_test(NAME LIST_TEST COMMAND list_test)
