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
    vector<uint32_t> an(1), bn(1);
    an[0] = UINT32_MAX;
    bn[0] = UINT32_MAX;
    Integer a(an), b(bn);
    auto c = Integer::add(a, b);
    cout << "done";
}

void Test::test_sub() {
    vector<uint32_t> an(3), bn(1);
    an[0] = 0;
    an[1] = 0;
    an[2] = 1;
    bn[0] = 1;
    Integer a(an);
    Integer b(bn);
    auto c = Integer::sub(a, b);
    cout << "done";
}

void Test::test_mul() {
    vector<uint32_t> an(2), bn(2);
    an[0] = 0;
    bn[0] = 0;
    an[1] = 1;
    bn[1] = 1;
    Integer a(an);
    Integer b(bn);
    auto c = Integer::mul(a, b);
    cout << "done";
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
