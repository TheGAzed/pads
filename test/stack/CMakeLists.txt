add_executable(stack_test_01 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
)
target_compile_definitions(stack_test_01 PRIVATE TEST_STACK_MODE=01)
target_link_libraries(stack_test_01 PRIVATE greatest project_headers)

add_executable(stack_test_02 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
)
target_compile_definitions(stack_test_02 PRIVATE TEST_STACK_MODE=02)
target_link_libraries(stack_test_02 PRIVATE greatest project_headers)

add_executable(stack_test_03 main.c
        create_stack_test.c
        destroy_stack_test.c
        is_full_stack_test.c
)
target_compile_definitions(stack_test_03 PRIVATE TEST_STACK_MODE=03)
target_link_libraries(stack_test_03 PRIVATE greatest project_headers)

add_test(
    NAME STACK_TEST_01 
    COMMAND stack_test_01 
)

add_test(
    NAME STACK_TEST_02
    COMMAND stack_test_02 
)

add_test(
    NAME STACK_TEST_03
    COMMAND stack_test_03 
)