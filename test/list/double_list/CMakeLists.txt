add_executable(double_list_test main.c
        mode/infinite_allocated_double_list_test.c
        mode/finite_allocated_double_list_test.c
        mode/finite_preprocessor_double_list_test.c
        mode/infinite_realloc_double_list_test.c
)

target_include_directories(double_list_test PUBLIC .)
target_link_libraries(double_list_test PRIVATE greatest PADS functions)
add_test(NAME DOUBLE_LIST_TEST COMMAND double_list_test)
