add_executable(priority_test main.c
        suits/binary_heap_test.c
)

target_include_directories(priority_test PUBLIC .)
target_link_libraries(priority_test PRIVATE greatest ${PROJECT_NAME} functions)
add_test(NAME PRIORITY_TEST COMMAND priority_test)
