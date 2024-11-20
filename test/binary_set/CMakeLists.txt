add_executable(binary_set_test main.c
)
target_link_libraries(binary_set_test PRIVATE greatest project_headers)
add_test(NAME BINARY_SET_TEST COMMAND binary_set_test)
