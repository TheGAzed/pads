add_executable(set_test main.c
        suits/binary_set_test.c
        suits/bitwise_set_test.c
        suits/hash_set_test.c
)

target_include_directories(set_test PUBLIC .)
target_link_libraries(set_test PRIVATE greatest PADS functions)
add_test(NAME SET_TEST COMMAND set_test)
