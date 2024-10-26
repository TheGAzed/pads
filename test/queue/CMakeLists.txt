add_executable(queue_test_010 main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_010 PRIVATE TEST_QUEUE_MODE=010)
target_link_libraries(queue_test_010 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_010 COMMAND queue_test_010)
set_tests_properties(QUEUE_TEST_010 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_020 main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_020 PRIVATE TEST_QUEUE_MODE=020)
target_link_libraries(queue_test_020 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_020 COMMAND queue_test_020)
set_tests_properties(QUEUE_TEST_020 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_030 main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_030 PRIVATE TEST_QUEUE_MODE=030)
target_link_libraries(queue_test_030 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_030 COMMAND queue_test_030)
set_tests_properties(QUEUE_TEST_030 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_040 main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_040 PRIVATE TEST_QUEUE_MODE=040)
target_link_libraries(queue_test_040 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_040 COMMAND queue_test_040)
set_tests_properties(QUEUE_TEST_040 PROPERTIES LABELS "QUEUE_TEST")
