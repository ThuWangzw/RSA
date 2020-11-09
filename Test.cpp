//
// Created by wangzw on 2020/10/27.
//

#include "Test.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

void Test::test_add() {
    Integer a = Integer::get_Integer_from_input();
    Integer b = Integer::get_Integer_from_input();
    Integer c = Integer::get_Integer_from_input();
    Integer res = Integer::add(a, b);
    bool eq = Integer::equal(c, res);
    return;;
}

void Test::test_sub() {
    Integer a = Integer::get_Integer_from_input();
    Integer b = Integer::get_Integer_from_input();
    Integer c = Integer::get_Integer_from_input();
    Integer res = Integer::sub(a, b);
    bool eq = Integer::equal(c, res);
}

void Test::test_mul() {
    Integer a = Integer::get_Integer_from_input();
    Integer b = Integer::get_Integer_from_input();
    Integer c = Integer::get_Integer_from_input();
    Integer res = Integer::mul(a, b);
    bool eq = Integer::equal(c, res);
}

void Test::test_div() {
    vector<uint32_t> an(2), bn(1);
    an[0] = UINT32_MAX;
    bn[0] = 2;
    an[1] = 1;
    Integer a(an);
    Integer b(bn);
    auto c = Integer::div(a, b);
    cout << "done";
}

void Test::test_inverse() {
    vector<uint32_t> an(1), bn(1);
    an[0] = 117;
    bn[0] = 5;
    Integer a(an);
    Integer b(bn);
    auto c = Integer::inverse(a, b);
    cout << "done";
}

void Test::test_mod() {
    vector<uint32_t> an(1), bn(1), en(1);
    an[0] = 25;
    bn[0] = 187;
    en[0] = 107;
    Integer a(an);
    Integer b(bn);
    Integer e(en);
    auto c = Integer::mod_in_exp(a, e, b);
    cout << "done";
}

void Test::test_crt() {
    Integer n(15), p(3), q(5), rp(2), rq(3);
    auto c = Integer::crt(n, p, q, rp, rq);
    cout << "done";
}

void Test::test_simple_decry_encry() {
    Integer p(43), q(59);
    Integer M(999);
    RSA rsa;
    rsa.set_up(p, q);
    Integer C = rsa.encryption(M);
    Integer RM = rsa.decryption(C);
    cout << "done";
}

void Test::test_big_prime() {
    uint32_t digit = 384;
    RSA rsa;
    Integer p = rsa.find_prime(digit);
    cout << "done";
}

void Test::test_right_shift() {
    Integer a = Integer::get_Integer_from_input();
    Integer c = Integer::get_Integer_from_input();
    a.rightShift(768);
    bool eq = Integer::equal(c, a);
    return;
}

void Test::test_left_shift() {
    vector<uint32_t> nn(3, 0);
    nn[0]=UINT32_MAX;
    nn[1]=UINT32_MAX;
    nn[2]=UINT32_MAX;
    Integer n(nn);
    n.leftShift(48);
    cout << "done";
}

void Test::test_reciprocalNewton() {
    vector<uint32_t> nn(1, 0);
    nn[0]=8;
    Integer n(nn);
    n.getReciprocalNewton();
    cout << "done";
}

void Test::test_fast_mod() {
    vector<uint32_t> an(7, 0), bn(1, 0);
    an[0] = 3711959039;
    an[1] = 2225340415;
    an[2] = 1477443583;
    an[3] = 3773431807;
    an[4] = 2640576511;
    an[5] = 3250192383;
    an[6] = 2866020351;
    bn[0] = 3711959039;
    bn[1] = 2225340415;
    bn[2] = 1477443583;
    bn[3] = 3773431807;
    Integer a(an);
    Integer b(bn);
    auto c = Integer::fast_mod_in_exp(a, b);
    cout << "done";
}

void Test::test_decry_encry() {
    RSA rsa;
    rsa.set_up();
    Integer M(123456789);
    Integer C = rsa.encryption(M);
    Integer RM = rsa.decryption(C);
    Integer::print(RM);
    return;
}

void Test::test_mul64() {
    Integer a = Integer::get_Integer_from_input();
    Integer b = Integer::get_Integer_from_input();
    Integer c = Integer::get_Integer_from_input();
    Integer res = Integer::mul64(a, b);
    Integer orires = Integer::mul(a, b);
    bool eq = Integer::equal(c, res);
    bool orieq = Integer::equal(c, orires);
    cout << "done" <<endl;
}
