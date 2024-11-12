#ifndef TEST_STACK_MODE

#error 'TEST_STACK_MODE' not defined.

#else

#define STACK_MODE TEST_STACK_MODE

#endif

#include <greatest.h>

//#define STACK_MODE INFINITE_LIST_STACK
#include "stack.h"

STACK_DATA_TYPE copy_element_cst(const STACK_DATA_TYPE element) {
    STACK_DATA_TYPE copy = { 0 };
    memcpy(&copy, &element, sizeof(STACK_DATA_TYPE));
    return copy;
}

void destroy_element_cst(STACK_DATA_TYPE * element) {
    *element = (STACK_DATA_TYPE) { 0 };
}

#if   STACK_MODE == INFINITE_LIST_STACK

/// Tests if stack's head parameter is NULL.
TEST ILS_01(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[ILS-TEST] Stack's head parameter is not NULL.", NULL, test_stack.head);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's size parameter is zero.
TEST ILS_02(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[ILS-TEST] Stack's size parameter is not zero.", 0, test_stack.size);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is NULL.
TEST ILS_03(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[ILS-TEST] Stack's copy_element parameter is not NULL.", NULL, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is NULL.
TEST ILS_04(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[ILS-TEST] Stack's destroy_element parameter is not NULL.", NULL, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is 'copy_element_cst'.
TEST ILS_05(void) {
    stack_s test_stack = create_stack(copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[ILS-TEST] Stack's copy_element parameter is not NULL.", copy_element_cst, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is 'destroy_element_cst'.
TEST ILS_06(void) {
    stack_s test_stack = create_stack(copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[ILS-TEST] Stack's destroy_element parameter is not NULL.", destroy_element_cst, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(ILS_01); RUN_TEST(ILS_02);
    RUN_TEST(ILS_03); RUN_TEST(ILS_04);
    RUN_TEST(ILS_05); RUN_TEST(ILS_06);
}

#elif STACK_MODE == FINITE_ALLOCATED_STACK

#define FINITE_STACK_SIZE 10

/// Tests if stack's elements parameter is NULL.
TEST FAS_01(void) {
    stack_s test_stack = create_stack(FINITE_STACK_SIZE, NULL, NULL);
    ASSERT_NEQm("[FAS-TEST] Stack's element parameter is NULL.", NULL, test_stack.elements);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's size parameter is zero.
TEST FAS_02(void) {
    stack_s test_stack = create_stack(FINITE_STACK_SIZE, NULL, NULL);
    ASSERT_EQm("[FAS-TEST] Stack's size parameter is not zero.", 0, test_stack.size);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's max parameter is not 'FINITE_STACK_SIZE'.
TEST FAS_03(void) {
    stack_s test_stack = create_stack(FINITE_STACK_SIZE, NULL, NULL);
    ASSERT_EQm("[FAS-TEST] Stack's copy_element parameter is not 'FINITE_STACK_SIZE'.", FINITE_STACK_SIZE, test_stack.max);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is NULL.
TEST FAS_04(void) {
    stack_s test_stack = create_stack(FINITE_STACK_SIZE, NULL, NULL);
    ASSERT_EQm("[FAS-TEST] Stack's copy_element parameter is not NULL.", NULL, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is NULL.
TEST FAS_05(void) {
    stack_s test_stack = create_stack(FINITE_STACK_SIZE, NULL, NULL);
    ASSERT_EQm("[FAS-TEST] Stack's destroy_element parameter is not NULL.", NULL, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is 'copy_element_cst'.
TEST FAS_06(void) {
    stack_s test_stack = create_stack(FINITE_STACK_SIZE, copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[FAS-TEST] Stack's copy_element parameter is not NULL.", copy_element_cst, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is 'destroy_element_cst'.
TEST FAS_07(void) {
    stack_s test_stack = create_stack(FINITE_STACK_SIZE, copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[FAS-TEST] Stack's destroy_element parameter is not NULL.", destroy_element_cst, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(FAS_01); RUN_TEST(FAS_02);
    RUN_TEST(FAS_03); RUN_TEST(FAS_04);
    RUN_TEST(FAS_05); RUN_TEST(FAS_06);
    RUN_TEST(FAS_07);
}

#elif STACK_MODE == INFINITE_REALLOC_STACK

/// Tests if stack's elements parameter is NULL.
TEST IRS_01(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[IRS-TEST] Stack's element parameter is not NULL.", NULL, test_stack.elements);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's size parameter is zero.
TEST IRS_02(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[IRS-TEST] Stack's size parameter is not zero.", 0, test_stack.size);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is NULL.
TEST IRS_03(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[IRS-TEST] Stack's copy_element parameter is not NULL.", NULL, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is NULL.
TEST IRS_04(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[IRS-TEST] Stack's destroy_element parameter is not NULL.", NULL, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is 'copy_element_cst'.
TEST IRS_05(void) {
    stack_s test_stack = create_stack(copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[IRS-TEST] Stack's copy_element parameter is not NULL.", copy_element_cst, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is 'destroy_element_cst'.
TEST IRS_06(void) {
    stack_s test_stack = create_stack(copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[IRS-TEST] Stack's destroy_element parameter is not NULL.", destroy_element_cst, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(IRS_01); RUN_TEST(IRS_02);
    RUN_TEST(IRS_03); RUN_TEST(IRS_04);
    RUN_TEST(IRS_05); RUN_TEST(IRS_06);
}

#elif STACK_MODE == FINITE_PRERPOCESSOR_STACK

/// Tests if stack's size parameter is zero.
TEST FPS_01(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[FPS-TEST] Stack's size parameter is not zero.", 0, test_stack.size);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is NULL.
TEST FPS_02(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[FPS-TEST] Stack's copy_element parameter is not NULL.", NULL, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is NULL.
TEST FPS_03(void) {
    stack_s test_stack = create_stack(NULL, NULL);
    ASSERT_EQm("[FPS-TEST] Stack's destroy_element parameter is not NULL.", NULL, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's copy_element parameter is 'copy_element_cst'.
TEST FPS_04(void) {
    stack_s test_stack = create_stack(copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[FPS-TEST] Stack's copy_element parameter is not NULL.", copy_element_cst, test_stack.copy_element);
    destroy_stack(&test_stack);

    PASS();
}

/// Tests if stack's destroy_element parameter is 'destroy_element_cst'.
TEST FPS_05(void) {
    stack_s test_stack = create_stack(copy_element_cst, destroy_element_cst);
    ASSERT_EQm("[FPS-TEST] Stack's destroy_element parameter is not NULL.", destroy_element_cst, test_stack.destroy_element);
    destroy_stack(&test_stack);

    PASS();
}

SUITE (create_stack_test) {
    RUN_TEST(FPS_01); RUN_TEST(FPS_02);
    RUN_TEST(FPS_03); RUN_TEST(FPS_04);
    RUN_TEST(FPS_05);
}

#endif
