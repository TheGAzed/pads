add_executable(queue_test main.c
)
target_link_libraries(queue_test PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST COMMAND queue_test)
