add_executable(binary_set_test main.c
        infinite_realloc_binary_set.c
        finite_allocated_binary_set.c
        finite_preprocessor_binary_set.c
)
target_link_libraries(binary_set_test PRIVATE greatest PADS)
add_test(NAME BINARY_SET_TEST COMMAND binary_set_test)
