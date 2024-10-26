add_executable(list_test_0100 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0100 PRIVATE TEST_LIST_MODE=0100)
target_link_libraries(list_test_0100 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0100 COMMAND list_test_0100)
set_tests_properties(LIST_TEST_0100 PROPERTIES LABELS "LIST_TEST")

add_executable(list_test_0200 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0200 PRIVATE TEST_LIST_MODE=0200)
target_link_libraries(list_test_0200 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0200 COMMAND list_test_0200)
set_tests_properties(LIST_TEST_0200 PROPERTIES LABELS "LIST_TEST")

add_executable(list_test_0300 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0300 PRIVATE TEST_LIST_MODE=0300)
target_link_libraries(list_test_0300 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0300 COMMAND list_test_0300)
set_tests_properties(LIST_TEST_0300 PROPERTIES LABELS "LIST_TEST")

add_executable(list_test_0400 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0400 PRIVATE TEST_LIST_MODE=0400)
target_link_libraries(list_test_0400 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0400 COMMAND list_test_0400)
set_tests_properties(LIST_TEST_0400 PROPERTIES LABELS "LIST_TEST")
