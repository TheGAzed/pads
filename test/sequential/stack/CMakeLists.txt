add_executable(stack_test main.c
        mode/infinite_list_stack_test.c
        mode/finite_allocated_stack_test.c
        mode/infinite_realloc_stack_test.c
        mode/finite_preprocessor_stack_test.c
)

target_include_directories(stack_test PUBLIC .)
target_link_libraries(stack_test PRIVATE greatest project_headers functions)
add_test(NAME STACK_TEST COMMAND stack_test)
