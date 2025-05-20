add_executable(binary_set_test main.c
        mode/infinite_realloc_binary_set.c
        mode/finite_allocated_binary_set.c
        mode/finite_preprocessor_binary_set.c
)

target_include_directories(binary_set_test PUBLIC .)
target_link_libraries(binary_set_test PRIVATE greatest PADS functions)
add_test(NAME BINARY_SET_TEST COMMAND binary_set_test)
