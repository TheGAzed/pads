add_executable(stack_test_01 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
)
target_compile_definitions(stack_test_01 PRIVATE TEST_STACK_MODE=01)
target_link_libraries(stack_test_01 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_01 COMMAND stack_test_01)
set_tests_properties(STACK_TEST_01 PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_02 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
)
target_compile_definitions(stack_test_02 PRIVATE TEST_STACK_MODE=02)
target_link_libraries(stack_test_02 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_02 COMMAND stack_test_02)
set_tests_properties(STACK_TEST_02 PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_03 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
)
target_compile_definitions(stack_test_03 PRIVATE TEST_STACK_MODE=03)
target_link_libraries(stack_test_03 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_03 COMMAND stack_test_03)
set_tests_properties(STACK_TEST_03 PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_04 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
        peep_stack_test.c
        push_stack_test.c
        pop_stack_test.c
        copy_stack_test.c
)
target_compile_definitions(stack_test_04 PRIVATE TEST_STACK_MODE=04)
target_link_libraries(stack_test_04 PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_04 COMMAND stack_test_04)
set_tests_properties(STACK_TEST_04 PROPERTIES LABELS "STACK_TEST")
