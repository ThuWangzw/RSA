//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_TEST_H
#define RSA_TEST_H

#include "RSA.h"
#include "Integer.h"
#include <cstdint>

class Test {
    static Integer random_generate_integer(uint32_t digit);

public:
    static void test_add();
    static void test_sub();
    static void test_mul();
    static void test_div();
    static void test_inverse();
    static void test_mod();
    static void test_crt();
    static void test_simple_decry_encry();
    static void test_big_prime();
    static void test_right_shift();
    static void test_left_shift();
    static void test_reciprocalNewton();
    static void test_fast_mod();
    static void test_decry_encry();
    static void test_decry_encry_str();
    static void test_mul64();
    static void test_tostring();
    static void test_time(uint32_t digit = 768, int iterations = 100);
};


#endif //RSA_TEST_H
