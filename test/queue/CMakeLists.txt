add_executable(queue_test_010 main.c
        create_queue_test.c
        destroy_queue_test.c
)
target_compile_definitions(queue_test_010 PRIVATE TEST_QUEUE_MODE=010)
target_link_libraries(queue_test_010 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_01 COMMAND queue_test_010)
set_tests_properties(QUEUE_TEST_01 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_020 main.c
        create_queue_test.c
        destroy_queue_test.c
)
target_compile_definitions(queue_test_020 PRIVATE TEST_QUEUE_MODE=020)
target_link_libraries(queue_test_020 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_02 COMMAND queue_test_020)
set_tests_properties(QUEUE_TEST_02 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_030 main.c
        create_queue_test.c
        destroy_queue_test.c
)
target_compile_definitions(queue_test_030 PRIVATE TEST_QUEUE_MODE=030)
target_link_libraries(queue_test_030 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_03 COMMAND queue_test_030)
set_tests_properties(QUEUE_TEST_03 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_040 main.c
        create_queue_test.c
        destroy_queue_test.c
)
target_compile_definitions(queue_test_040 PRIVATE TEST_QUEUE_MODE=040)
target_link_libraries(queue_test_040 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_04 COMMAND queue_test_040)
set_tests_properties(QUEUE_TEST_04 PROPERTIES LABELS "QUEUE_TEST")
