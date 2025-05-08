add_executable(circular_list_test main.c
        mode/infinite_allocated_circular_list_test.c
        mode/finite_allocated_circular_list_test.c
        mode/infinite_realloc_circular_list_test.c
        mode/finite_preprocessor_circular_list_test.c
)

target_include_directories(circular_list_test PUBLIC .)
target_link_libraries(circular_list_test PRIVATE greatest PADS functions)
add_test(NAME CIRCULAR_LIST_TEST COMMAND circular_list_test)
