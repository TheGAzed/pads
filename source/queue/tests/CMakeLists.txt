add_executable(queue_test main.c
        infinite_list_queue_test.c
        finite_allocated_queue_test.c
        infinite_realloc_queue_test.c
        finite_preprocessor_queue_test.c
)
target_link_libraries(queue_test PRIVATE greatest project_headers functions)
add_test(NAME QUEUE_TEST COMMAND queue_test)
