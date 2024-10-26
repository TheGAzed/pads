add_executable(stack_test_0x1 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
        sort_stack_test.c
)
target_compile_definitions(stack_test_0x1 PRIVATE TEST_STACK_MODE=0x1)
target_link_libraries(stack_test_0x1 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_0x1 COMMAND stack_test_0x1)
set_tests_properties(STACK_TEST_0x1 PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_0x2 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
        sort_stack_test.c
)
target_compile_definitions(stack_test_0x2 PRIVATE TEST_STACK_MODE=0x2)
target_link_libraries(stack_test_0x2 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_0x2 COMMAND stack_test_0x2)
set_tests_properties(STACK_TEST_0x2 PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_0x3 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
        sort_stack_test.c
)
target_compile_definitions(stack_test_0x3 PRIVATE TEST_STACK_MODE=0x3)
target_link_libraries(stack_test_0x3 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_0x3 COMMAND stack_test_0x3)
set_tests_properties(STACK_TEST_0x3 PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_0x4 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
        sort_stack_test.c
)
target_compile_definitions(stack_test_0x4 PRIVATE TEST_STACK_MODE=0x4)
target_link_libraries(stack_test_0x4 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_0x4 COMMAND stack_test_0x4)
set_tests_properties(STACK_TEST_0x4 PROPERTIES LABELS "STACK_TEST")
