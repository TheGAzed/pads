add_executable(straight_list_test main.c
        infinite_allocated_straight_list_test.c
        finite_allocated_straight_list_test.c
        infinite_realloc_straight_list_test.c
        finite_preprocessor_straight_list_test.c
)
target_link_libraries(straight_list_test PRIVATE greatest project_headers)
add_test(NAME STRAIGHT_LIST_TEST COMMAND straight_list_test)
