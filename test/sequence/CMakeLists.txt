add_executable(sequence_test main.c
        suits/stack_test.c
        suits/queue_test.c
        suits/deque_test.c
)

target_include_directories(sequence_test PUBLIC .)
target_link_libraries(sequence_test PRIVATE greatest PADS functions)
add_test(NAME SEQUENCE_TEST COMMAND sequence_test)
