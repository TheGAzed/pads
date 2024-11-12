add_executable(stack_test_ils main.c create_stack_test.c destroy_stack_test.c
)
target_compile_definitions(stack_test_ils PRIVATE TEST_STACK_MODE=0x1)
target_link_libraries(stack_test_ils PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_ILS COMMAND stack_test_ils)
set_tests_properties(STACK_TEST_ILS PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_fas main.c create_stack_test.c destroy_stack_test.c
)
target_compile_definitions(stack_test_fas PRIVATE TEST_STACK_MODE=0x2)
target_link_libraries(stack_test_fas PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_FAS COMMAND stack_test_fas)
set_tests_properties(STACK_TEST_FAS PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_irs main.c create_stack_test.c destroy_stack_test.c
)
target_compile_definitions(stack_test_irs PRIVATE TEST_STACK_MODE=0x3)
target_link_libraries(stack_test_irs PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_IRS COMMAND stack_test_irs)
set_tests_properties(STACK_TEST_IRS PROPERTIES LABELS "STACK_TEST")

add_executable(stack_test_fps main.c create_stack_test.c destroy_stack_test.c
)
target_compile_definitions(stack_test_fps PRIVATE TEST_STACK_MODE=0x4)
target_link_libraries(stack_test_fps PRIVATE greatest project_headers)
add_test(NAME STACK_TEST_FPS COMMAND stack_test_fps)
set_tests_properties(STACK_TEST_FPS PROPERTIES LABELS "STACK_TEST")
