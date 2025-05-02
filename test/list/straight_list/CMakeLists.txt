add_executable(straight_list_test main.c
        mode/infinite_allocated_straight_list_test.c
        mode/finite_allocated_straight_list_test.c
        mode/infinite_realloc_straight_list_test.c
        mode/finite_preprocessor_straight_list_test.c
)

target_include_directories(straight_list_test PUBLIC .)
target_link_libraries(straight_list_test PRIVATE functions greatest project_headers)
add_test(NAME STRAIGHT_LIST_TEST COMMAND straight_list_test)
