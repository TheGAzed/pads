add_executable(deque_test main.c
        mode/infinite_list_deque_test.c
        mode/infinite_realloc_deque_test.c
        mode/finite_allocated_deque_test.c
        mode/finite_preprocessor_deque_test.c
)

target_include_directories(deque_test PUBLIC .)
target_link_libraries(deque_test PRIVATE greatest PADS functions)
add_test(NAME DEQUE_TEST COMMAND deque_test)
