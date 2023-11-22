#include "unit_tests.h"

TestSuite(student_tests, .timeout=TEST_TIMEOUT);

Test(student_tests, val_test1) {
    execute_test("val_test1", "e 63 31 31 31");
}

Test(student_tests, val_test2) {
    execute_test("val_test2", "Deg 0x01f11b9d");
}

Test(student_tests, val_test3) {
    execute_test("val_test3", "D 0x04212710 10");
}

Test(student_tests, val_test4) {
    execute_test("val_test4", "P 91MAb 10");
}

Test(student_tests, i_test1) {
    execute_test("i_test1", "E 33 17 17 32769");
}

Test(student_tests, i_test2) {
    execute_test("i_test2", "E 01 15 17 00100");
}

Test(student_tests, i_test3) {
    execute_test("i_test3", "E 10 01 05 99999");
}

Test(student_tests, i_test4) {
    execute_test("i_test4", "E 99 00 00 00000");
}

Test(student_tests, d_test1) {
    execute_test("d_test1", "D 0xffffffff");
}

Test(student_tests, d_test2) {
    execute_test("d_test2", "D 0x04210001");
}

Test(student_tests, d_test3) {
    execute_test("d_test3", "D 86318001");
}

Test(student_tests, d_test4) {
    execute_test("d_test4", "D 0X8631801");
}

Test(student_tests, d_test5) {
    execute_test("d_test5", "D 0x8631801d5");
}

Test(student_tests, d_test6) {
    execute_test("d_test6", "D 0x8631801=");
}

Test(student_tests, poker_test1) {
    execute_test("poker_test1", "P 1BSd5");
}

Test(student_tests, poker_test2) {
    execute_test("poker_test2", "P URYW1");
}

Test(student_tests, poker_test3) {
    execute_test("poker_test3", "P 91MAm");
}

Test(student_tests, poker_test4) {
    execute_test("poker_test4", "P 91MAB");
}

Test(student_tests, poker_test5) {
    execute_test("poker_test5", "P ASaBb");
}

Test(student_tests, poker_test6) {
    execute_test("poker_test6", "P 12345");
}

Test(student_tests, poker_test7) {
    execute_test("poker_test7", "P kmjli");
}

Test(student_tests, poker_test8) {
    execute_test("poker_test8", "P =1342");
}

Test(student_tests, poker_test9) {
    execute_test("poker_test9", "P AQaB1");
}