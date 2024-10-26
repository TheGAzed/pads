add_executable(queue_test_0x08 main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_0x08 PRIVATE TEST_QUEUE_MODE=0x08)
target_link_libraries(queue_test_0x08 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_0x08 COMMAND queue_test_0x08)
set_tests_properties(QUEUE_TEST_0x08 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_0x0A main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_0x0A PRIVATE TEST_QUEUE_MODE=0x0A)
target_link_libraries(queue_test_0x0A PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_0x0A COMMAND queue_test_0x0A)
set_tests_properties(QUEUE_TEST_0x0A PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_0x18 main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_0x18 PRIVATE TEST_QUEUE_MODE=0x18)
target_link_libraries(queue_test_0x18 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_0x18 COMMAND queue_test_0x18)
set_tests_properties(QUEUE_TEST_0x18 PROPERTIES LABELS "QUEUE_TEST")

add_executable(queue_test_0x20 main.c
        create_queue_test.c
        destroy_queue_test.c
        is_full_queue_test.c
        peek_queue_test.c
        enqueue_test.c
        dequeue_test.c
        copy_queue_test.c
)
target_compile_definitions(queue_test_0x20 PRIVATE TEST_QUEUE_MODE=0x20)
target_link_libraries(queue_test_0x20 PRIVATE greatest project_headers)
add_test(NAME QUEUE_TEST_0x20 COMMAND queue_test_0x20)
set_tests_properties(QUEUE_TEST_0x20 PROPERTIES LABELS "QUEUE_TEST")
