add_executable(sequential_test main.c
        suits/stack_test.c
        suits/queue_test.c
        suits/deque_test.c
)

target_include_directories(sequential_test PUBLIC .)
target_link_libraries(sequential_test PRIVATE greatest PADS functions)
add_test(NAME SEQUENTIAL_TEST COMMAND sequential_test)
