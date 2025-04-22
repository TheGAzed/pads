add_executable(stack_test main.c
        infinite_list_stack_test.c
        finite_allocated_stack_test.c
        infinite_realloc_stack_test.c
        finite_preprocessor_stack_test.c
)
target_link_libraries(stack_test PRIVATE greatest project_headers functions)
add_test(NAME STACK_TEST COMMAND stack_test)
