add_executable(list_test main.c
)
target_link_libraries(list_test PRIVATE greatest project_headers)
add_test(NAME LIST_TEST COMMAND list_test)
