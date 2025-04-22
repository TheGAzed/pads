add_executable(deque_test main.c
        infinite_list_deque_test.c
        infinite_realloc_deque_test.c
        finite_allocated_deque_test.c
        finite_preprocessor_deque_test.c
)
target_link_libraries(deque_test PRIVATE greatest project_headers functions)
add_test(NAME DEQUE_TEST COMMAND deque_test)
