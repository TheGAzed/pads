add_executable(queue_test main.c
        mode/infinite_list_queue_test.c
        mode/finite_allocated_queue_test.c
        mode/infinite_realloc_queue_test.c
        mode/finite_preprocessor_queue_test.c
)

target_include_directories(queue_test PUBLIC .)
target_link_libraries(queue_test PRIVATE greatest project_headers functions)
add_test(NAME QUEUE_TEST COMMAND queue_test)
