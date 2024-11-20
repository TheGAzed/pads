add_executable(stack_test main.c
        infinite_list_stack_test.c
)
target_link_libraries(stack_test PRIVATE greatest project_headers)
add_test(NAME STACK_TEST COMMAND stack_test)
