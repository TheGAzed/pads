add_executable(list_test_0x040 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0x040 PRIVATE TEST_LIST_MODE=0x040)
target_link_libraries(list_test_0x040 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0x040 COMMAND list_test_0x040)
set_tests_properties(LIST_TEST_0x040 PROPERTIES LABELS "LIST_TEST")

add_executable(list_test_0x080 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0x080 PRIVATE TEST_LIST_MODE=0x080)
target_link_libraries(list_test_0x080 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0x080 COMMAND list_test_0x080)
set_tests_properties(LIST_TEST_0x080 PROPERTIES LABELS "LIST_TEST")

add_executable(list_test_0x0C0 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0x0C0 PRIVATE TEST_LIST_MODE=0x0C0)
target_link_libraries(list_test_0x0C0 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0x0C0 COMMAND list_test_0x0C0)
set_tests_properties(LIST_TEST_0x0C0 PROPERTIES LABELS "LIST_TEST")

add_executable(list_test_0x100 main.c
        create_list_test.c
)
target_compile_definitions(list_test_0x100 PRIVATE TEST_LIST_MODE=0x100)
target_link_libraries(list_test_0x100 PRIVATE greatest project_headers)
add_test(NAME LIST_TEST_0x100 COMMAND list_test_0x100)
set_tests_properties(LIST_TEST_0x100 PROPERTIES LABELS "LIST_TEST")
