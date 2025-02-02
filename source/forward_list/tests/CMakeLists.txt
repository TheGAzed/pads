add_executable(forward_list_test main.c
)
target_link_libraries(forward_list_test PRIVATE greatest project_headers)
add_test(NAME FORWARD_LIST_TEST COMMAND forward_list_test)
