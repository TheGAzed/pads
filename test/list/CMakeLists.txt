add_executable(list_test main.c
        suits/straight_list_test.c
        suits/circular_list_test.c
        suits/double_list_test.c
)

target_include_directories(list_test PUBLIC .)
target_link_libraries(list_test PRIVATE greatest PADS functions)
add_test(NAME LIST_TEST COMMAND list_test)
