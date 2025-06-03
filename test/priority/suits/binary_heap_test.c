#include <suits.h>

#define BINARY_HEAP_DATA_TYPE DATA_TYPE
#define BINARY_HEAP_SIZE (1 << 4)
#include <priority/binary_heap.h>

TEST CREATE_01(void) {
    binary_heap_s test = create_binary_heap(compare_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);
    ASSERT_NEQm("[ERROR] Expected function pointer to not be NULL.", NULL, test.compare);

    destroy_binary_heap(&test, destroy_int);

    PASS();
}

TEST DESTROY_01(void) {
    binary_heap_s test = create_binary_heap(compare_int);

    destroy_binary_heap(&test, destroy_int);

    ASSERT_EQm("[ERROR] Expected size to be zero.", 0, test.size);
    ASSERT_EQm("[ERROR] Expected function pointer to be NULL.", NULL, test.compare);

    PASS();
}

SUITE (binary_heap_test) {
    // create
    RUN_TEST(CREATE_01);
    // destroy
    RUN_TEST(DESTROY_01);
}
