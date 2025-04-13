add_executable(deque_test main.c
)
target_link_libraries(deque_test PRIVATE greatest project_headers)
add_test(NAME DEQUE_TEST COMMAND deque_test)
